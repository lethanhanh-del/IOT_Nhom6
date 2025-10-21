#include <Servo.h>

// Khởi tạo Servo
Servo servo_9;

// Định nghĩa chân
const int rainPin = A3; // Chân đọc giá trị analog từ Rain Sensor
int lastState = -1;     // Biến lưu trạng thái trước (0: mưa, 1: không mưa)

void setup() {
  // Khởi tạo Serial Monitor với tốc độ 9600 baud
  Serial.begin(9600);

  // Định nghĩa chân D0 là input (nếu dùng digital)
  pinMode(2, INPUT);

  // Khởi tạo Servo
  servo_9.attach(9, 500, 2500); // Chân 9, pulse width min 500µs, max 2500µs
  servo_9.write(90);            // Đặt servo về 90° ban đầu (mở cửa sổ)
}

void loop() {
  // Đọc giá trị analog từ Rain Sensor
  int sensorValue = analogRead(rainPin);

  // Đọc giá trị digital từ D0 (nếu có)
  int digitalValue = digitalRead(2);

  // Hiển thị kết quả trên Serial Monitor
  Serial.print("Analog Value (A0): ");
  Serial.println(sensorValue); // Giá trị 0-1023, thấp hơn khi có mưa

  Serial.println("-------------------");

  // Kiểm tra trạng thái mưa
  if (sensorValue < 600 ) {
    if (lastState != 0) { // Chỉ quay nếu trạng thái thay đổi
      // Servo quay lên 180° (đóng cửa sổ)
      for (int pos = 90; pos >= 0; pos -= 1) {
        servo_9.write(pos);
        Serial.print("State: ");
        Serial.println(lastState); 

        delay(5); // Đợi 15ms để servo di chuyển
      }
      lastState = 0; // Cập nhật trạng thái
    }
  } else {
    if (lastState != 1 ) { // Chỉ quay nếu trạng thái thay đổi
      // Servo quay về 90° (mở cửa sổ)
      for (int pos = 0; pos <= 90; pos += 1) {
        servo_9.write(pos);
        Serial.print("State: ");
        Serial.println(lastState); 
        delay(5); // Đợi 15ms để servo di chuyển
      }
      lastState = 1; // Cập nhật trạng thái
    }
  }

  delay(500); // Dừng 0.5 giây trước khi lặp lại
}