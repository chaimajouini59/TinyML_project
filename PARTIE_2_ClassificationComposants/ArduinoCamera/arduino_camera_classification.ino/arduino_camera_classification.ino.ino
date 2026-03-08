/*
========================================================
TinyML Component Classification
Board: Arduino Nano 33 BLE
Camera: OV7670
Model: Edge Impulse

Fonctionnement :
1. Capture une image avec la caméra
2. Lance l'inférence Edge Impulse
3. Trouve la classe la plus probable
4. Envoie la classe à Node-RED via Serial
========================================================
*/

#include <electronics_inferencing.h>
#include <Arduino_OV767X.h>

#define CAMERA_WIDTH 160
#define CAMERA_HEIGHT 120

static bool camera_initialised = false;
static uint8_t *snapshot_buf;

/* Initialisation caméra */
bool camera_init() {

    if (camera_initialised) return true;

    if (!Camera.begin(QQVGA, RGB565, 1)) {
        Serial.println("Camera init failed");
        return false;
    }

    camera_initialised = true;
    return true;
}

/* Capture image */
bool camera_capture(uint32_t width, uint32_t height, uint8_t *out_buf) {

    if (!camera_initialised) {
        Serial.println("Camera not initialized");
        return false;
    }

    Camera.readFrame(out_buf);

    return true;
}

/* Convert image pour Edge Impulse */
int ei_camera_cutout_get_data(size_t offset, size_t length, float *out_ptr) {

    size_t pixel_ix = offset * 2;
    size_t bytes_left = length;
    size_t out_ptr_ix = 0;

    while (bytes_left != 0) {

        uint16_t pixel = (snapshot_buf[pixel_ix] << 8) | snapshot_buf[pixel_ix + 1];

        uint8_t r = ((pixel >> 11) & 0x1f) << 3;
        uint8_t g = ((pixel >> 5) & 0x3f) << 2;
        uint8_t b = (pixel & 0x1f) << 3;

        out_ptr[out_ptr_ix] = (r << 16) + (g << 8) + b;

        pixel_ix += 2;
        out_ptr_ix++;
        bytes_left--;
    }

    return 0;
}

void setup() {

    Serial.begin(115200);
    while (!Serial);

    Serial.println("Edge Impulse Camera Classification");

    if (!camera_init()) {
        Serial.println("Camera initialization failed");
        while (1);
    }

    snapshot_buf = (uint8_t*)malloc(CAMERA_WIDTH * CAMERA_HEIGHT * 2);
}

void loop() {

    Serial.println("Capturing image...");

    if (!camera_capture(CAMERA_WIDTH, CAMERA_HEIGHT, snapshot_buf)) {
        Serial.println("Capture failed");
        delay(2000);
        return;
    }

    ei::signal_t signal;

    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &ei_camera_cutout_get_data;

    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR err = run_classifier(&signal, &result, false);

    if (err != EI_IMPULSE_OK) {
        Serial.println("Inference failed");
        delay(2000);
        return;
    }

    /* Trouver la meilleure classe */

    int best_index = 0;
    float best_score = result.classification[0].value;

    for (int i = 1; i < EI_CLASSIFIER_LABEL_COUNT; i++) {

        if (result.classification[i].value > best_score) {

            best_score = result.classification[i].value;
            best_index = i;
        }
    }

    const char* best_label = ei_classifier_inferencing_categories[best_index];

    /* Affichage dans Serial Monitor */

    Serial.print("Prediction: ");
    Serial.print(best_label);
    Serial.print("  Score: ");
    Serial.println(best_score, 4);

    /* Envoi vers Node-RED */

    if (best_score > 0.6) {

        Serial.print("CLASS:");
        Serial.println(best_label);

    } else {

        Serial.println("CLASS:Unknown");

    }

    delay(2000);
}