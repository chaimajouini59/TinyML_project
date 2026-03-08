# Documentation – Classification de composants électroniques

## 1. Introduction

Cette deuxième partie du projet consiste à développer un système de classification d’images capable de reconnaître différents composants électroniques à l’aide d’une caméra connectée à une carte Arduino.

Le système utilise la plateforme **Edge Impulse** pour entraîner un modèle de vision embarquée, puis déploie ce modèle sur l’Arduino afin d’effectuer l’inférence directement sur le microcontrôleur.

Les résultats de classification sont ensuite transmis à **Node-RED**, qui permet de compter les composants détectés et de les afficher sur un tableau de bord.

---

# 2. Objectif du système

L'objectif est de créer un système capable de :

1. Capturer une image avec la caméra OV7670
2. Identifier le composant électronique présent dans l'image
3. Envoyer la classe détectée à Node-RED
4. Mettre à jour un compteur pour chaque type de composant

---

# 3. Matériel utilisé

Le système repose sur les composants suivants :

- Arduino Nano 33 BLE
- caméra OV7670
- ordinateur pour l’entraînement du modèle
- Node-RED pour la visualisation des résultats

---

# 4. Entraînement du modèle avec Edge Impulse

L'entraînement du modèle est réalisé sur la plateforme **Edge Impulse**.

Le processus se déroule en plusieurs étapes :

### 4.1 Création du projet

Un projet a été créé sur la plateforme Edge Impulse.

Insérer ici une capture du **dashboard Edge Impulse**.

---

### 4.2 Import des images

Les images des composants électroniques sont importées dans Edge Impulse.

Chaque image est associée à une **étiquette (label)** correspondant au type de composant.

Exemple de labels :

- LED
- Resistance
- Capacitor

Insérer ici une capture du **dataset dans Edge Impulse**.

---

### 4.3 Création de l'impulse

L'impulse définit le pipeline de traitement du modèle.

Il contient généralement :

1. **Image preprocessing**
2. **Feature extraction**
3. **Classification**

Insérer ici une capture du **pipeline Edge Impulse**.

---

### 4.4 Entraînement du modèle

Le modèle est ensuite entraîné sur les images du dataset.

Edge Impulse entraîne automatiquement un réseau de neurones optimisé pour les systèmes embarqués.

Insérer ici une capture :

- de l'entraînement
- de la précision du modèle

---

# 5. Export du modèle pour Arduino

Une fois le modèle entraîné, Edge Impulse permet de l’exporter sous forme d'une **bibliothèque Arduino**.

Cette bibliothèque contient :

- le modèle TensorFlow Lite
- les fonctions nécessaires pour exécuter l’inférence
- les fichiers de configuration du modèle

Le modèle est ensuite intégré dans le projet Arduino.

---

# 6. Inférence sur Arduino

Le programme principal utilisé pour la classification est :
arduino_camera_classification.ino


Ce programme réalise les étapes suivantes :

1. Initialisation de la caméra OV7670
2. Capture d'une image
3. Prétraitement de l'image
4. Exécution du modèle Edge Impulse
5. Obtention de la classe prédite

---

# 7. Envoi des résultats à Node-RED

Après la classification, la classe prédite est envoyée à Node-RED via la communication série.

Exemple de message envoyé :
- ![Architecture projet](https://drive.google.com/uc?export=download&id=1Xn27bgO0XYV5KzZxmSAzZ-f-a2Dn8a8R)
  
Node-RED reçoit cette information et met à jour les compteurs correspondants.

---

# 8. Visualisation avec Node-RED

Node-RED permet de créer une interface graphique affichant :

- le nombre de LED détectées
- le nombre de résistances détectées
- le nombre de condensateurs détectés

Un **dashboard Node-RED** est utilisé pour afficher ces informations en temps réel.

Insérer ici une capture :

- du flow Node-RED
- du dashboard Node-RED

---

# 9. Résultat du système

Le système est capable de :

- capturer une image
- identifier le composant électronique
- transmettre la classe détectée
- mettre à jour un compteur dans Node-RED

Les résultats sont affichés en temps réel sur le tableau de bord.

---

# 10. Conclusion

Cette deuxième partie du projet démontre qu'il est possible d'utiliser des techniques de vision embarquée pour reconnaître des objets à l'aide d'un microcontrôleur.

L'utilisation de Edge Impulse facilite la création de modèles optimisés pour les systèmes embarqués, tandis que Node-RED permet de visualiser les résultats et d'interagir avec les données produites par le système.
