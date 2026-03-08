
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

- 
La fonction d'activation utilisée est **ReLU**.

La couche de sortie utilise **Softmax**.

---
## 8. Entraînement du modèle

Après la définition de l'architecture du réseau de neurones, le modèle est entraîné à l'aide des données préparées dans le notebook Google Colab.

L'entraînement consiste à ajuster les poids du réseau afin de minimiser l'erreur de prédiction sur les données d'entraînement.

Le modèle est entraîné avec les paramètres suivants :

- Optimizer : Adam
- Fonction de perte : sparse categorical crossentropy
- Nombre d'epochs : 70
- Batch size : 8

Pendant l'entraînement, deux métriques principales sont suivies :

- **Accuracy**
- **Loss**

L'accuracy représente la proportion de prédictions correctes réalisées par le modèle.

La loss mesure l'erreur entre les prédictions du modèle et les classes réelles.

---

## 8.1 Évolution de l'accuracy

Le graphique suivant montre l'évolution de l'accuracy pendant l'entraînement.

On observe deux courbes :

- **train accuracy** : précision sur les données d'entraînement
- **validation accuracy** : précision sur les données de validation


 ![Architecture projet](https://drive.google.com/uc?export=download&id=19zZfevbuZPXRwwN31-OigXTEgD8cusdp)

Ce graphique permet de vérifier que le modèle apprend correctement et que l'accuracy augmente progressivement au cours des epochs.

---

## 8.2 Évolution de la loss

La loss permet de mesurer l'erreur du modèle.

Plus la valeur de la loss est faible, plus les prédictions du modèle sont proches des valeurs attendues.

Le graphique suivant montre l'évolution de la loss pendant l'entraînement.


 ![Architecture projet](https://drive.google.com/uc?export=download&id=1UK_fT8qEFc5Zl1dWE-UPt4RlkdbBiYML)

On observe généralement que la loss diminue progressivement lorsque le modèle apprend correctement.

---

## 8.3 Évaluation du modèle

Après l'entraînement, le modèle est évalué sur le dataset de test.

Cela permet de vérifier que le modèle est capable de généraliser sur des données qu'il n'a jamais vues pendant l'entraînement.

Les métriques utilisées pour l'évaluation sont :

- accuracy
- confusion matrix
- classification report

---

## 8.4 Matrice de confusion

La matrice de confusion permet d'observer les performances du modèle pour chaque classe.

Elle montre combien de prédictions sont correctes ou incorrectes pour chaque catégorie de vibration.

Insérer ici la capture d'écran de la matrice de confusion générée dans le notebook.

 ![Architecture projet](https://drive.google.com/uc?export=download&id=1b4VgHHlsahgimpSmaEjwQcAz-5ekDSFf)

Cette matrice permet d'identifier les classes qui peuvent être confondues par le modèle.
## 9. Export du modèle

Après l’entraînement et l’évaluation du modèle dans le notebook, plusieurs fichiers sont générés afin de permettre le déploiement sur Arduino.


| Fichier | Description |
|-------|-------------|
| vibration_model.tflite | Modèle TensorFlow Lite optimisé pour l'exécution sur microcontrôleur |
| model_data.h | Modèle converti en tableau C pour être compilé dans le programme Arduino |
| labels.txt | Liste des classes reconnues par le modèle : no_vibration, low_vibration, high_vibration |
| mean.npy / std.npy | Paramètres de normalisation utilisés pendant le prétraitement des données |

Le fichier `.tflite` est le modèle final exporté depuis TensorFlow.  
Pour pouvoir l’utiliser dans Arduino, il est converti en tableau C et stocké dans le fichier `model_data.h`.

Ce fichier est ensuite inclus dans le programme Arduino afin que le modèle puisse être chargé directement sur la carte.

---

## 10. Déploiement sur Arduino

Le modèle entraîné est ensuite utilisé dans le programme Arduino suivant :
Inference_Arduino/inference_vibrations.ino
  
Ce programme permet d’exécuter le modèle directement sur la carte Arduino Nano 33 BLE.

Le fonctionnement est le suivant :

1. Lecture des données du capteur IMU en temps réel
2. Création d’une fenêtre de mesures
3. Extraction des caractéristiques utilisées pendant l’entraînement
4. Normalisation des données avec les paramètres `mean` et `std`
5. Exécution du modèle TensorFlow Lite
6. Affichage de la classe prédite dans le Serial Monitor

---

## 11. Résultat sur Arduino

Après le déploiement du modèle, les prédictions peuvent être observées dans le **Serial Monitor** de l’Arduino IDE.

Le programme affiche la classe de vibration détectée ainsi que le score associé.

Exemple de résultat obtenu lors du test du système :



 ![Architecture projet](https://drive.google.com/uc?export=download&id=19SLXJ5AcfQeNp3wdEPJ1jgYl5Y-07f58)

 ## 12. Fichiers importants du projet

Les fichiers principaux utilisés dans cette partie du projet sont :

| Fichier | Rôle |
|-------|------|
| data_generation.ino | Programme Arduino utilisé pour collecter les données IMU |
| training_vibrations.ipynb | Notebook utilisé pour l'entraînement du modèle et la génération des fichiers |
| inference_vibrations.ino | Programme Arduino permettant d’exécuter le modèle et de prédire la classe de vibration |

