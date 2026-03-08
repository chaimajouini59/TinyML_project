/*
========================================================
DATA GENERATION - TinyML Vibration Classification
Carte : Arduino Nano 33 BLE
Capteur : IMU intégré (LSM9DS1)

Ce programme lit :
- l'accélération (aX,aY,aZ)
- le gyroscope (gX,gY,gZ)

et envoie les données vers le PC via Serial.
Ces données seront enregistrées dans des fichiers CSV
pour entraîner le modèle Machine Learning.
========================================================
*/

#include <Arduino_LSM9DS1.h>   // bibliothèque pour utiliser l'IMU

void setup() {

  // Initialisation de la communication série
  Serial.begin(115200);

  // attendre que le port série soit prêt
  while (!Serial);

  // initialiser le capteur IMU
  if (!IMU.begin()) {
    Serial.println("Erreur : IMU non detectee !");
    while (1); // arrêter le programme
  }

  Serial.println("IMU initialisee avec succes");

  // afficher l'entête CSV
  Serial.println("aX,aY,aZ,gX,gY,gZ");
}

void loop() {

  // vérifier si de nouvelles données sont disponibles
  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {

    float ax, ay, az;
    float gx, gy, gz;

    // lire les valeurs d'accélération
    IMU.readAcceleration(ax, ay, az);

    // lire les valeurs du gyroscope
    IMU.readGyroscope(gx, gy, gz);

    // envoyer les données vers le PC sous format CSV
    Serial.print(ax); Serial.print(",");
    Serial.print(ay); Serial.print(",");
    Serial.print(az); Serial.print(",");
    Serial.print(gx); Serial.print(",");
    Serial.print(gy); Serial.print(",");
    Serial.println(gz);

    // délai pour obtenir environ 50 Hz
    delay(20);
  }
}