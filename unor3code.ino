#include <MQUnifiedsensor.h>

// Multiplexer pins
const int s0 = 5;
const int s1 = 6;
const int s2 = 9;
const int s3 = 10;
const int muxSIG = A0;

// Sensor configurations
#define Board "Arduino UNO"
#define Voltage_Resolution 5
#define ADC_Bit_Resolution 10
#define RL 10000  // Load resistance 10K ohm

// Define R0 values for clean air (calibrated)
float R0_MQ4 = 10000;   // For Methane
float R0_MQ6 = 10000;   // For LPG
float R0_MQ7 = 10000;   // For CO
float R0_MQ8 = 10000;   // For Hydrogen-
float R0_MQ135 = 10000; // For Air Quality

// Create MQ objects
MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-4");
MQUnifiedsensor MQ6(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-6");
MQUnifiedsensor MQ7(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-7");
MQUnifiedsensor MQ8(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-8");
MQUnifiedsensor MQ135[4] = {
  MQUnifiedsensor(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-135"),
  MQUnifiedsensor(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-135"),
  MQUnifiedsensor(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-135"),
  MQUnifiedsensor(Board, Voltage_Resolution, ADC_Bit_Resolution, muxSIG, "MQ-135")
};

void selectMuxChannel(byte channel) {
  digitalWrite(s0, bitRead(channel, 0));
  digitalWrite(s1, bitRead(channel, 1));
  digitalWrite(s2, bitRead(channel, 2));
  digitalWrite(s3, bitRead(channel, 3));
  delay(10);
}

float readMuxChannel(byte channel) {
  selectMuxChannel(channel);
  delay(100);
  int rawValue = analogRead(muxSIG);
  float voltage = (rawValue * 5.0) / 1023.0;
  if (voltage <= 0.01) {
    return -1; // Prevent invalid readings
  }
  float RS = ((5.0 * RL) / voltage) - RL;
  return RS;
}

// PPM calculation functions
float getMQ4PPM(float ratio) {
  float m = -0.318;
  float b = 1.133;
  return pow(10, (log10(ratio) - b) / m);
}

float getMQ6PPM(float ratio) {
  float m = -0.47; // Adjusted for better accuracy
  float b = 1.28;
  return pow(10, (log10(ratio) - b) / m);
}

float getMQ7PPM(float ratio) {
  float m = -0.6527;
  float b = 1.30;
  return pow(10, (log10(ratio) - b) / m);
}

float getMQ8PPM(float ratio) {
  float m = -0.421;
  float b = 1.542;
  return pow(10, (log10(ratio) - b) / m);
}

float getMQ135PPM(float ratio) {
  float m = -0.318;
  float b = 1.460;
  return pow(10, (log10(ratio) - b) / m);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);

  // Initialize sensors with regression method
  MQ4.setRegressionMethod(1);
  MQ6.setRegressionMethod(1);
  MQ7.setRegressionMethod(1);
  MQ8.setRegressionMethod(1);
  for (int i = 0; i < 4; i++) {
    MQ135[i].setRegressionMethod(1);
  }

  // Set R0 values
  MQ4.setR0(R0_MQ4);
  MQ6.setR0(R0_MQ6);
  MQ7.setR0(R0_MQ7);
  MQ8.setR0(R0_MQ8);
  for (int i = 0; i < 4; i++) {
    MQ135[i].setR0(R0_MQ135);
  }

  delay(2500);  // Wait for sensors to warm up
}

void loop() {
  // Read and calculate for MQ4 (Methane)
  float rs_mq4 = readMuxChannel(0);
  float ppm_mq4 = (rs_mq4 > 0) ? getMQ4PPM(rs_mq4 / R0_MQ4) : -1;

  // Read and calculate for MQ6 (LPG)
  float rs_mq6 = readMuxChannel(1);
  float ppm_mq6 = (rs_mq6 > 0) ? getMQ6PPM(rs_mq6 / R0_MQ6) : -1;

  // Read and calculate for MQ7 (CO)
  float rs_mq7 = readMuxChannel(2);
  float ppm_mq7 = (rs_mq7 > 0) ? getMQ7PPM(rs_mq7 / R0_MQ7) : -1;

  // Read and calculate for MQ8 (Hydrogen)
  float rs_mq8 = readMuxChannel(3);
  float ppm_mq8 = (rs_mq8 > 0) ? getMQ8PPM(rs_mq8 / R0_MQ8) : -1;

  // Read and calculate for MQ135 sensors
  float ppm_mq135[4];
  for (int i = 0; i < 4; i++) {
    float rs = readMuxChannel(i + 4);
    ppm_mq135[i] = (rs > 0) ? getMQ135PPM(rs / R0_MQ135) : -1;
  }

  // Prepare the output string
  String output = "CO:" + String(ppm_mq7) + 
                  ",NO:" + String(ppm_mq7) +  // Same sensor for NO, change as necessary
                  ",CO2:" + String(ppm_mq4) + 
                  ",NO2:" + String(ppm_mq6) + 
                  ",NH3:" + String(ppm_mq6) + 
                  ",CH4:" + String(ppm_mq4) + 
                  ",H2:" + String(ppm_mq8) + 
                  ",LPG:" + String(ppm_mq6);
  
  // Print the data to the Serial Monitor
  Serial.println(output);

  delay(2500);  // Delay before the next reading
}
