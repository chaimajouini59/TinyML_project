#include <Arduino_LSM9DS1.h>
#include "model_data.h"

#include <TensorFlowLite.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/schema/schema_generated.h>
#include <tensorflow/lite/version.h>

#define WINDOW_SIZE 100
#define NUM_FEATURES 6
#define NUM_CLASSES 3

const char* labels[NUM_CLASSES] = {
  "no_vibration",
  "low_vibration",
  "high_vibration"
};

float ax_buffer[WINDOW_SIZE];
float ay_buffer[WINDOW_SIZE];
float az_buffer[WINDOW_SIZE];
float gx_buffer[WINDOW_SIZE];
float gy_buffer[WINDOW_SIZE];
float gz_buffer[WINDOW_SIZE];

int sample_index = 0;

tflite::MicroErrorReporter micro_error_reporter;
tflite::ErrorReporter* error_reporter = &micro_error_reporter;

const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;

TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int tensor_arena_size = 10 * 1024;
uint8_t tensor_arena[tensor_arena_size];

void setup() {

  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("IMU failed");
    while (1);
  }

  model = tflite::GetModel(model_data);

  static tflite::AllOpsResolver resolver;

  static tflite::MicroInterpreter static_interpreter(
    model, resolver, tensor_arena, tensor_arena_size, error_reporter
  );

  interpreter = &static_interpreter;

  interpreter->AllocateTensors();

  input = interpreter->input(0);
  output = interpreter->output(0);

  Serial.println("Model ready");
}

void loop() {

  if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {

    float ax, ay, az;
    float gx, gy, gz;

    IMU.readAcceleration(ax, ay, az);
    IMU.readGyroscope(gx, gy, gz);

    ax_buffer[sample_index] = ax;
    ay_buffer[sample_index] = ay;
    az_buffer[sample_index] = az;

    gx_buffer[sample_index] = gx;
    gy_buffer[sample_index] = gy;
    gz_buffer[sample_index] = gz;

    sample_index++;

    if (sample_index >= WINDOW_SIZE) {

      float acc_mag_sum = 0;
      float gyro_mag_sum = 0;

      float acc_mag_sq_sum = 0;
      float gyro_mag_sq_sum = 0;

      float acc_max = 0;
      float gyro_max = 0;

      for (int i = 0; i < WINDOW_SIZE; i++) {

        float acc_mag = sqrt(
          ax_buffer[i]*ax_buffer[i] +
          ay_buffer[i]*ay_buffer[i] +
          az_buffer[i]*az_buffer[i]
        );

        float gyro_mag = sqrt(
          gx_buffer[i]*gx_buffer[i] +
          gy_buffer[i]*gy_buffer[i] +
          gz_buffer[i]*gz_buffer[i]
        );

        acc_mag_sum += acc_mag;
        gyro_mag_sum += gyro_mag;

        acc_mag_sq_sum += acc_mag*acc_mag;
        gyro_mag_sq_sum += gyro_mag*gyro_mag;

        if (acc_mag > acc_max) acc_max = acc_mag;
        if (gyro_mag > gyro_max) gyro_max = gyro_mag;
      }

      float mean_acc = acc_mag_sum / WINDOW_SIZE;
      float std_acc = sqrt(acc_mag_sq_sum/WINDOW_SIZE - mean_acc*mean_acc);

      float mean_gyro = gyro_mag_sum / WINDOW_SIZE;
      float std_gyro = sqrt(gyro_mag_sq_sum/WINDOW_SIZE - mean_gyro*mean_gyro);

      input->data.f[0] = mean_acc;
      input->data.f[1] = std_acc;
      input->data.f[2] = acc_max;
      input->data.f[3] = mean_gyro;
      input->data.f[4] = std_gyro;
      input->data.f[5] = gyro_max;

      interpreter->Invoke();

      int best_index = 0;
      float best_score = output->data.f[0];

      for (int i = 1; i < NUM_CLASSES; i++) {
        if (output->data.f[i] > best_score) {
          best_score = output->data.f[i];
          best_index = i;
        }
      }

      Serial.print("Prediction: ");
      Serial.print(labels[best_index]);
      Serial.print("  Score: ");
      Serial.println(best_score);

      sample_index = 0;
    }
  }
}