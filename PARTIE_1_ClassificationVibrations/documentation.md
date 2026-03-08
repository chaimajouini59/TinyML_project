
# Documentation détaillée – Classification des vibrations

## 1. Introduction

Cette partie du projet vise à développer un système capable de détecter différents niveaux de vibration à l’aide de la carte Arduino Nano 33 BLE.

Le capteur IMU intégré à la carte permet de mesurer :

- l'accélération sur les axes X, Y et Z
- la vitesse angulaire (gyroscope) sur les axes X, Y et Z

Ces données sont utilisées pour entraîner un modèle de classification capable de reconnaître trois niveaux de vibration.

## 2. Classes de vibration

Le dataset est constitué de trois classes :

| Classe | Description |
|------|-------------|
| no_vibration | aucune vibration détectée |
| low_vibration | vibration faible |
| high_vibration | vibration forte |

Chaque classe correspond à un fichier CSV contenant les données du capteur IMU.
exemple : 
no_vibration.csv
low_vibration.csv
high_vibration.csv

Chaque ligne contient :


où :

- aX, aY, aZ : accélération
- gX, gY, gZ : gyroscope

---

# 3. Matériel utilisé

Le système utilise les composants suivants :

- Arduino Nano 33 BLE
- capteur IMU intégré
- ordinateur pour la collecte des données et l'entraînement

---

# 4. Collecte des données

La première étape consiste à collecter les données du capteur IMU.


permet de lire les données de l'IMU et de les envoyer au PC via le port série.

Les données sont ensuite enregistrées dans des fichiers CSV afin de constituer le dataset d'entraînement.


Chaque fichier contient plusieurs milliers de mesures.

Ces données sont ensuite utilisées pour entraîner le modèle de classification.

---

# 6. Prétraitement des données

Les signaux IMU sont des séries temporelles.  
Avant l'entraînement du modèle, plusieurs étapes de prétraitement sont appliquées.

## 6.1 Découpage en fenêtres

Les signaux sont découpés en fenêtres de taille fixe.


Chaque fenêtre contient : 100 mesures × 6 variables



## 6.2 Extraction de caractéristiques

Pour simplifier le modèle embarqué, des caractéristiques statistiques sont extraites :

- moyenne
- écart-type
- maximum

Ces caractéristiques sont calculées pour :

- la magnitude de l'accélération
- la magnitude du gyroscope

On obtient ainsi un vecteur de **6 features**.

---

# 7. Entraînement du modèle

L'entraînement est réalisé dans un notebook Python.

Fichier : training_vibrations.ipynb


Le modèle utilisé est un réseau de neurones simple.

Architecture :
- ![Architecture projet](https://drive.google.com/uc?export=download&id=1RiNiM5yaC6usWci1T33r6Xys5TAi-x-v)
  




