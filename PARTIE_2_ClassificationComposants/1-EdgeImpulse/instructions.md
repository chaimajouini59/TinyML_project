# Instructions pour reproduire le projet Edge Impulse

Ce document décrit les étapes suivies pour créer le modèle de **classification d’images de composants électroniques** en utilisant la plateforme **Edge Impulse**.

L'objectif du projet est de reconnaître automatiquement plusieurs composants électroniques à partir d’images capturées par une caméra **OV7670** connectée à une carte **Arduino Nano 33 BLE**.

---

# 1. Création du projet Edge Impulse

La première étape consiste à créer un nouveau projet sur la plateforme **Edge Impulse**.

Étapes :

1. Aller sur la plateforme Edge Impulse  
https://studio.edgeimpulse.com

2. Cliquer sur **Create new project**

3. Donner un nom au projet :

TinyML Components Classification

4. Sélectionner le type de données :

Image

5. Choisir la plateforme cible :

Arduino Nano 33 BLE Sense

Une fois le projet créé, Edge Impulse ouvre automatiquement le **dashboard du projet**.

---

# 2. Importation du dataset

Les images utilisées pour entraîner le modèle ont été importées dans la section :

Data Acquisition

Chaque image représente un composant électronique placé devant la caméra.

Les classes utilisées dans le projet sont :

- background  
- capacitor  
- diode  
- led  
- resistor  

Chaque image a été associée à la bonne classe lors de l'import.

Cette étape permet de constituer le **dataset d'entraînement**.

---

# 3. Vérification du dataset

Après l'importation des images, il est important de vérifier que :

- chaque image est correctement étiquetée  
- chaque classe possède suffisamment d'exemples  
- les images sont bien visibles et correctement cadrées  

Cette vérification se fait directement dans **Data Acquisition**.

Un dataset équilibré améliore les performances du modèle.

---

# 4. Création de l’Impulse

La configuration du pipeline de traitement est réalisée dans la section :

Impulse Design

Un **impulse** définit la manière dont les données seront traitées par le modèle.

Le pipeline utilisé dans ce projet contient les blocs suivants :

### Bloc 1 : Image

Ce bloc définit les paramètres d’entrée du modèle :

- résolution de l’image  
- format de l’image  

### Bloc 2 : Image Processing

Le bloc **Image processing** transforme les images en caractéristiques exploitables par le modèle.

Edge Impulse applique automatiquement ce prétraitement.

### Bloc 3 : Classification

Le bloc **Classification** entraîne un modèle de **réseau de neurones** pour reconnaître les différentes classes.

---

# 5. Entraînement du modèle

L'entraînement du modèle est réalisé dans la section :

Classifier

Edge Impulse entraîne automatiquement un **réseau de neurones convolutif (CNN)** adapté à la classification d'images.

La structure du modèle comprend :

- Input layer  
- 2D convolution layers  
- Pooling layers  
- Flatten layer  
- Dropout layer  
- Output layer  

La couche de sortie contient **5 neurones**, correspondant aux classes :

- background  
- capacitor  
- diode  
- led  
- resistor  

---

# 6. Résultats de l'entraînement

Après l'entraînement, Edge Impulse fournit plusieurs indicateurs :

- accuracy du modèle  
- matrice de confusion  
- visualisation des erreurs  
- performance sur microcontrôleur  

Les résultats obtenus dans ce projet sont environ :

Accuracy : 92 % à 95 %

Performances embarquées :

Latency : environ 55 ms  
RAM usage : environ 18 KB  
Flash usage : environ 41.8 KB  

Ces résultats montrent que le modèle peut fonctionner sur **Arduino Nano 33 BLE**.

---

# 7. Test du modèle

Le modèle peut être testé dans la section :

Model Testing

Cette étape permet de vérifier les performances du modèle sur des données qui n'ont pas été utilisées pendant l'entraînement.

Cela permet de valider la capacité du modèle à **généraliser sur de nouvelles images**.

---

# 8. Déploiement du modèle

Une fois l'entraînement terminé, le modèle peut être exporté depuis la section :

Deployment

Le format choisi est :

Arduino Library

Edge Impulse génère automatiquement une bibliothèque Arduino contenant :

- le modèle TensorFlow Lite  
- le code d’inférence  
- les dépendances nécessaires  

Cette bibliothèque est ensuite importée dans **Arduino IDE**.

---

# 9. Utilisation du modèle sur Arduino

Le modèle est utilisé dans le fichier :

2-ArduinoCamera/arduino_camera_classification.ino

Le programme Arduino effectue les opérations suivantes :

1. initialisation de la caméra OV7670  
2. capture d’une image  
3. exécution du modèle Edge Impulse  
4. détermination de la classe prédite  
5. envoi du résultat via le port série  

Exemple de sortie dans le Serial Monitor :

Prediction: capacitor  Score: 0.98  
CLASS:capacitor

---

# 10. Communication avec Node-RED

Les résultats envoyés par Arduino sont transmis à **Node-RED** via la communication série.

Node-RED :

- reçoit la classe détectée  
- incrémente un compteur pour chaque type de composant  
- affiche les résultats dans un **dashboard**

Cela permet de suivre en temps réel le nombre de composants détectés.

---

# Conclusion

La plateforme **Edge Impulse** permet de simplifier le développement d'applications TinyML embarquées.

Elle permet de :

- importer et organiser un dataset d’images  
- entraîner un modèle de classification  
- optimiser le modèle pour microcontrôleur  
- exporter une bibliothèque Arduino  
- déployer le modèle sur un système embarqué.

