# Affichage space invader Multithreadé

## Vue d'ensemble
Ce projet a été réalisé lors de ma 2e année de licence informatique.
Ce programme en C démontre une simulation d'affichage multithreadée simple en utilisant des sémaphores pour la synchronisation entre les threads. L'application utilise deux matrices pour représenter les écrans, une pour l'affichage et une pour les modifications. Le programme permet de spécifier le nombre d'itérations de simulation de manière dynamique via l'entrée de l'utilisateur ou utilise un nombre par défaut prédéfini.

## Caractéristiques
- **Synchronisation des Threads** : Utilise des sémaphores pour synchroniser deux threads responsables du calcul et de l'affichage.
- **Affichage Dynamique** : Alterne entre deux "écrans" pour simuler une animation où chaque pixel peut être soit un espace vide soit un astérisque.
- **Contrôle des Itérations** : Le nombre d'itérations peut être ajusté en passant un argument lors du lancement du programme. Sinon, une valeur par défaut est utilisée.

## Prérequis
- Un compilateur C.
- Un système d'exploitation supportant les pthreads et les sémaphores POSIX.

## Compilation et Exécution
Pour compiler et exécuter le programme :

`gcc -o space_invader space_invader.c -lpthread`

`./simulation [nombre_iterations]`

Remplacez `[nombre_iterations]` par le nombre d'itérations que vous souhaitez exécuter, ou laissez vide pour utiliser la valeur par défaut.

## Fonctionnement
Le programme initialise deux matrices pour les écrans et les threads. Chaque thread effectue les tâches suivantes :
- **Thread Calculateur** : Met à jour l'écran à modifier en fonction des valeurs de l'écran à afficher.
- **Thread Afficheur** : Affiche l'écran mis à jour à chaque itération après un délai synchronisé.

