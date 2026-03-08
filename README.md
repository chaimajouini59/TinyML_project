# TinyML Project

## Présentation

Ce dépôt regroupe deux projets réalisés dans le cadre d’un travail autour du TinyML avec la carte Arduino Nano 33 BLE.

Le premier projet consiste à reconnaître différents niveaux de vibration à partir des données de l’IMU intégrée.  
Le second projet consiste à reconnaître des composants électroniques à partir d’images capturées par une caméra OV7670, avec un modèle entraîné sur Edge Impulse.

L’objectif général est de montrer comment un système embarqué peut collecter des données, entraîner un modèle léger, puis exécuter l’inférence directement sur une carte Arduino.

## Objectifs

Ce projet vise à :

- collecter des données capteurs ou images,
- entraîner un modèle de classification adapté à l’embarqué,
- convertir ce modèle dans un format compatible avec Arduino,
- effectuer l’inférence en temps réel sur microcontrôleur,
- documenter l’ensemble de la démarche.

## Structure du dépôt

Le dépôt est organisé en deux parties principales :

- **PARTIE_1_ClassificationVibrations** : classification de niveaux de vibration à partir des données IMU.
- **PARTIE_2_ClassificationComposants** : classification de composants électroniques par vision embarquée avec Edge Impulse.

## Partie 1 – Classification des vibrations

Cette partie du projet repose sur l’utilisation de l’IMU intégrée de l’Arduino Nano 33 BLE pour mesurer les vibrations.

Le système suit les étapes suivantes :

1. collecte des données d’accélération et de gyroscope,
2. création du dataset,
3. entraînement d’un modèle de classification,
4. conversion en TensorFlow Lite,
5. déploiement du modèle sur Arduino pour l’inférence en temps réel.

## Partie 2 – Classification des composants

Cette partie du projet repose sur l’analyse d’images capturées avec une caméra OV7670.

Le système suit les étapes suivantes :

1. création du projet sur Edge Impulse,
2. import et annotation des images,
3. entraînement du modèle de classification,
4. export du modèle pour Arduino,
5. exécution de l’inférence sur la carte,
6. transmission des résultats vers Node-RED pour le comptage.

## Technologies utilisées

Les principaux outils utilisés dans ce projet sont :

- Arduino Nano 33 BLE
- capteur IMU intégré
- caméra OV7670
- Python
- TensorFlow Lite
- Edge Impulse
- Arduino IDE
- Node-RED

## Remarque

Chaque sous-partie contient son propre code source, ses fichiers de configuration et sa documentation détaillée.
