#include <107-Arduino-BMP388.h>

#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
    Serial.println("Failed to find BMP280 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("BMP280 Found!");
}
void loop() {
  float altitude0 = bmp.readAltitude(); // pengukuran awal altitude
  delay(1000);
  float altitude1 = bmp.readAltitude();
  delay(1000);
  float altitude2 = bmp.readAltitude();

  float pressure0 = bmp.readPressure();
  float pressure1 = bmp.readPressure();
  float pressure2 = bmp.readPressure();

  float gradientTekananUmum = (pressure2 - pressure1) / (altitude2 - altitude1);
  float gradientTekananNumerik = (pressure2 - pressure0) / (2 * (altitude2 - altitude0));

  Serial.print("Gradient Tekanan Umum: ");
  Serial.print(gradientTekananUmum);
  Serial.println(" Pa/m");

  Serial.print("Gradient Tekanan Numerik: ");
  Serial.print(gradientTekananNumerik);
  Serial.println(" Pa/m");
 

  delay(1000);
}#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;  // Inisialisasi sensor BMP280

void setup() {
  Serial.begin(115200);
  
  if (!bmp.begin(0x76)) {  // Pastikan alamat I2C benar (0x76 atau 0x77)
    Serial.println("Failed to find BMP280 chip");
    while (1) {
      delay(10);
    }
  }
  
  Serial.println("BMP280 Found!");
  delay(2000); // Tunggu sensor stabil
}

void loop() {
  // Menggunakan tekanan referensi standar laut (1013.25 hPa) untuk pembacaan ketinggian
  float altitude0 = bmp.readAltitude(1013.25);
  float pressure0 = bmp.readPressure(); // Tekanan dalam Pascal (Pa)

  delay(1000);

  float altitude1 = bmp.readAltitude(1013.25);
  float pressure1 = bmp.readPressure();

  delay(1000);

  float altitude2 = bmp.readAltitude(1013.25);
  float pressure2 = bmp.readPressure();

  // Pastikan tidak ada pembagian dengan nol
  if ((altitude2 - altitude1) != 0 && (altitude2 - altitude0) != 0) {
    float gradientTekananUmum = (pressure2 - pressure1) / (altitude2 - altitude1);
    float gradientTekananNumerik = (pressure2 - pressure0) / (2 * (altitude2 - altitude0));

    Serial.print("Gradient Tekanan Umum: ");
    Serial.print(gradientTekananUmum);
    Serial.println(" Pa/m");

    Serial.print("Gradient Tekanan Numerik: ");
    Serial.print(gradientTekananNumerik);
    Serial.println(" Pa/m");
  } else {
    Serial.println("Peringatan: Perbedaan ketinggian nol, hasil ti
