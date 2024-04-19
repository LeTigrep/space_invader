#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define HAUTEUR 30
#define LARGEUR 50
#define NUM_ITER_DFT 30


int ecran1[HAUTEUR][LARGEUR];
int ecran2[HAUTEUR][LARGEUR];

int (*ecran_a_afficher)[HAUTEUR][LARGEUR];
int (*ecran_a_modifier)[HAUTEUR][LARGEUR];

sem_t mutex;

void effacer_lignes(int num_lignes);

pthread_t id[2];


int x=0;

void * calculer(void *arg)
{
    int numIter=*((int *)arg);
    int i,j,n;
    int (*ecran_swap)[HAUTEUR][LARGEUR];

    for (n = 0; n < numIter; ++n)
    {
        /* calcul de l'affichage suivant */
        for ( i = HAUTEUR - 1; i > 0; --i)
            for (j = 0; j < LARGEUR; ++j)
                (*ecran_a_modifier)[i][j] = (*ecran_a_afficher)[i - 1][j];
        for (j = 0; j < LARGEUR; ++j)
            (*ecran_a_modifier)[0][j] = 0;
        (*ecran_a_modifier)[0][rand() % LARGEUR] = 1;

        usleep(500000);

        // echanges des ecrans
        sem_wait(&mutex);
        ecran_swap=ecran_a_afficher;
        ecran_a_afficher=ecran_a_modifier;
        ecran_a_modifier=ecran_swap;
        sem_post(&mutex);


    }
}

void * afficher(void *arg)
{
    int numIter=*((int *)arg);
    int i,j,n;

    for (n = 0; n < numIter; ++n)
    {
        /* affichage de l'écran modifié */

        //faire attendre l'afficheur un peu pour marcher au rythme du thread calculer
        usleep(500000);


        sem_wait(&mutex);

        effacer_lignes(HAUTEUR);

        for (i = 0; i < HAUTEUR; ++i)
        {
            for (j = 0; j < LARGEUR; ++j)
            {
                if ((*ecran_a_afficher)[i][j] == 0)
                    putchar(' ');
                else
                    putchar('*');
            }
            putchar('\n');
        }
        sem_post(&mutex);

    }
}

int main(int argc, char *argv[])
{
    int num_iter = argc > 1 ? atoi(argv[1]) : NUM_ITER_DFT;
    int n, i, j;

    // initialisation des ecrans

    for (i = 0; i < HAUTEUR; i++)
    {
        for (j = 0; j < LARGEUR; j++)
        {
            ecran1[i][j]=0;
            ecran2[i][j]=0;
        }
    }

    ecran_a_afficher=&ecran2;
    ecran_a_modifier=&ecran1;


    // initialisation du semaphore
    sem_init(&mutex,0,1); // 0=> semaphore partage, 1=> initialise a 1


    // creation des threads
    pthread_create(&id[0],NULL, calculer,&num_iter);
    pthread_create(&id[1],NULL, afficher,&num_iter);


    pthread_join(id[0],NULL);
    pthread_join(id[1],NULL);

    sem_destroy(&mutex);

    puts("YOU LOSE.\n");
    return 0;
}

void effacer_lignes(int num_lignes)
{
    printf("\033[2K");
    for(; num_lignes > 0; --num_lignes)
    {
        printf("\033[F");
        printf("\033[2K");
    }
}
