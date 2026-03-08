# Partie 1 – Classification des vibrations

## Présentation

Cette partie du projet consiste à développer un système de classification de vibrations à partir des données du capteur IMU intégré dans la carte Arduino Nano 33 BLE.

Les données d'accélération et de gyroscope sont collectées avec l'Arduino, puis utilisées pour entraîner un modèle de classification capable de reconnaître différents niveaux de vibration.

Le modèle entraîné est ensuite converti au format TensorFlow Lite afin de pouvoir être exécuté directement sur la carte Arduino.

## Objectif

L'objectif du projet est de détecter automatiquement le niveau de vibration à partir des mesures du capteur IMU.

Trois classes de vibration sont utilisées :

- **no_vibration** : aucune vibration détectée
- **low_vibration** : vibration faible
- **high_vibration** : vibration forte

Le système doit être capable de reconnaître ces états en temps réel.

## Organisation du dossier

Le dossier est organisé en plusieurs sous-parties.

### 1. Data generation Arduino

Le dossier `1-DataGeneration_Arduino/` contient le code Arduino utilisé pour collecter les données du capteur IMU.

Ce programme lit les valeurs d'accélération et de gyroscope et les envoie vers l'ordinateur via le port série afin de construire le dataset.

### 2. Training

Le dossier `2-Training/` contient :

- le dataset de vibrations collecté (`no_vibration.csv`, `low_vibration.csv`, `high_vibration.csv`)
- le notebook utilisé pour entraîner le modèle
- les fichiers générés après l'entraînement (modèle TensorFlow Lite, paramètres de normalisation, etc.)

### 3. Inference Arduino

Le dossier `3-Inference_Arduino/` contient le code Arduino permettant d'exécuter le modèle entraîné directement sur la carte.

Le programme lit les données IMU en temps réel, applique les mêmes transformations que pendant l'entraînement et prédit la classe de vibration.

### 4. Documentation

Le dossier `doc/` contient une documentation détaillée expliquant toutes les étapes du projet.

## Méthode utilisée

Les étapes principales du projet sont les suivantes :

1. Collecte des données IMU avec l'Arduino Nano 33 BLE  
2. Enregistrement des données dans des fichiers CSV  
3. Découpage des signaux en fenêtres temporelles  
4. Extraction de caractéristiques statistiques  
5. Entraînement du modèle de classification  
6. Conversion du modèle en TensorFlow Lite  
7. Déploiement du modèle sur Arduino  
8. Inférence en temps réel

## Matériel utilisé

- Arduino Nano 33 BLE
- capteur IMU intégré

## Logiciels utilisés

- Arduino IDE
- Python
- TensorFlow / TensorFlow Lite
- Google Colab
