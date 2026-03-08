# Partie 2 – Classification de composants électroniques

## Présentation
Cette deuxième partie du projet consiste à développer un système capable de reconnaître différents composants électroniques à partir d’images capturées par une caméra connectée à une carte **Arduino Nano 33 BLE**. Pour réaliser cette tâche, la plateforme **Edge Impulse** est utilisée afin d’entraîner un modèle de vision embarquée capable de classifier des images de composants électroniques. Une fois entraîné, le modèle est exporté et exécuté directement sur l’Arduino afin de réaliser l’inférence en temps réel. Les résultats de classification sont ensuite transmis à **Node-RED**, qui permet de compter les composants détectés et d’afficher ces informations dans un tableau de bord.

## Objectif
L’objectif de cette partie est de concevoir un système capable de capturer une image avec une caméra OV7670, identifier le composant électronique présent dans l’image, envoyer la classe détectée via le port série, recevoir ces données dans Node-RED et afficher le nombre de composants détectés dans un dashboard.

## Fonctionnement du système
Le système fonctionne selon les étapes suivantes : la caméra OV7670 capture une image du composant électronique, l’image est traitée par le modèle de classification entraîné avec **Edge Impulse**, le modèle prédit la classe du composant présent dans l’image, Arduino envoie la classe détectée via le port série, Node-RED reçoit cette information et incrémente le compteur correspondant afin de mettre à jour le dashboard.

## Structure du dossier
PARTIE_2_ClassificationComposants  
│  
├── README.md  
├── 1-EdgeImpulse  
│   ├── link_to_edge_impulse.md  
│   └── instructions.md  
├── 2-ArduinoCamera  
│   └── arduino_camera_classification.ino  
├── 3-NodeRED  
│   ├── flows.json  
│   └── dashboard  
└── doc  
    └── documentation.md  

## Entraînement du modèle avec Edge Impulse
Le modèle de classification d’images a été entraîné à l’aide de la plateforme **Edge Impulse**. Edge Impulse permet d’importer et organiser un dataset d’images, créer un pipeline de traitement appelé **Impulse**, entraîner un modèle de classification d’images, optimiser le modèle pour microcontrôleur et exporter une bibliothèque compatible Arduino. Le lien vers le projet Edge Impulse est fourni dans `1-EdgeImpulse/link_to_edge_impulse.md` et les étapes détaillées de création du projet sont décrites dans `1-EdgeImpulse/instructions.md`.

## Inférence sur Arduino
Le modèle généré par Edge Impulse est intégré dans le programme Arduino `2-ArduinoCamera/arduino_camera_classification.ino`. Ce programme réalise l’initialisation de la caméra OV7670, capture une image, exécute le modèle Edge Impulse, détermine la classe prédite et envoie le résultat via le port série. Exemple de sortie dans le Serial Monitor : Prediction: resistor Score: 0.96 – CLASS:resistor.

## Communication avec Node-RED
Les résultats envoyés par Arduino sont reçus par **Node-RED** via un port série. Node-RED permet de recevoir les classes détectées, incrémenter un compteur pour chaque type de composant et afficher les résultats dans un dashboard. Le flow Node-RED utilisé dans ce projet est disponible dans `3-NodeRED/flows.json`.

## Technologies utilisées
Ce projet utilise les technologies suivantes : Arduino Nano 33 BLE, caméra OV7670, Edge Impulse, TensorFlow Lite, Arduino IDE et Node-RED.
