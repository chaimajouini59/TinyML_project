# Instructions pour reproduire le projet Edge Impulse

Cette section explique comment le projet de classification de composants électroniques a été configuré sur Edge Impulse.

## 1. Création du projet

Un nouveau projet Edge Impulse a été créé avec les paramètres suivants :

- Nom du projet : TinyML Components Classification
- Plateforme cible : Arduino Nano 33 BLE Sense
- Type de données : Image

---

## 2. Collecte du dataset

Les images utilisées pour l'entraînement ont été collectées à l’aide de la caméra **OV7670** connectée à l’Arduino Nano 33 BLE.

Chaque image contient un composant électronique placé devant la caméra.

Les classes utilisées dans le dataset sont :

- background
- capacitor
- diode
- led
- resistor

Les images ont été téléchargées dans **Edge Impulse Data Acquisition** puis annotées avec la classe correspondante.

---

## 3. Création de l’Impulse

Dans la section **Impulse Design**, un pipeline de traitement a été configuré.

### Image Processing Block
Le bloc utilisé pour le prétraitement des images est :

Image processing

Ce bloc transforme l’image brute en caractéristiques utilisables par le modèle.

### Learning Block

Le bloc d’apprentissage utilisé est :

Classification (Neural Network)

---

## 4. Entraînement du modèle

Le modèle de réseau de neurones utilisé est un CNN composé des couches suivantes :

- Input layer
- 2D convolution layer
- Pooling layer
- Flatten layer
- Dropout layer
- Output layer

Le modèle est entraîné directement dans Edge Impulse.

Les résultats obtenus sont environ :

Accuracy : ~92–95 %

---

## 5. Test du modèle

Après l’entraînement, le modèle a été testé avec :

Model testing

Cette étape permet de vérifier la précision du modèle sur des données jamais vues.

---

## 6. Déploiement du modèle

Le modèle a été exporté depuis Edge Impulse via :

Deployment → Arduino Library

Le fichier généré contient :

- le modèle TensorFlow Lite
- les fichiers d’inférence
- les bibliothèques nécessaires

Ce modèle est ensuite utilisé dans le programme Arduino :

2-ArduinoCamera/arduino_camera_classification.ino

Ce programme :

1. Capture une image avec la caméra
2. Exécute l’inférence avec Edge Impulse
3. Détermine la classe prédite
4. Envoie le résultat vers Node-RED via la communication série
