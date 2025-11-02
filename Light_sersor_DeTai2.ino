#include <Servo.h>

// Khởi tạo Servo
Servo servo_9;

// Định nghĩa chân
const int lightPin = A3; // Chân đọc giá trị analog từ cảm biến ánh sáng
int lastState = -1;      // Biến lưu trạng thái trước (0: ánh sáng yếu, 1: ánh sáng mạnh)

void setup() {
  // Khởi tạo Serial Monitor với tốc độ 9600 baud
  Serial.begin(9600);

  // Định nghĩa chân D0 là input (nếu dùng digital)
  pinMode(2, INPUT);

  // Khởi tạo Servo
  servo_9.attach(9, 500, 2500); // Chân 9, pulse width min 500µs, max 2500µs
  servo_9.write(90);            // Đặt servo về 90° ban đầu (mở cửa sổ)
}
//debo
void loop() {
  // Đọc giá trị analog từ cảm biến ánh sáng
  int sensorValue = analogRead(lightPin);

  // Đọc giá trị digital từ D0 (nếu có)
  int digitalValue = digitalRead(2);

  // Hiển thị kết quả trên Serial Monitor
  Serial.print("Light Value (A3): ");
  Serial.println(sensorValue); // Giá trị 0-1023, thấp hơn khi ánh sáng yếu
  // Serial.print("Digital Value (A3): ");
  // Serial.println(digitalValue); // Giá trị 0-1023, thấp hơn khi ánh sáng yếu

  Serial.println("-------------------");

  // Kiểm tra trạng thái ánh sáng
  if (sensorValue < 900) {
    if (lastState != 0) { // Chỉ quay nếu trạng thái thay đổi
      // Servo quay từ 90° về 0° (đóng cửa sổ khi ánh sáng yếu)
      for (int pos = 90; pos >= 0; pos -= 1) {
        servo_9.write(pos);
        Serial.print("State: ");
        Serial.println(lastState); 
        delay(5); // Đợi 5ms để servo di chuyển
      }
      lastState = 0; // Cập nhật trạng thái (ánh sáng yếu)
    }
  } else {
    if (lastState != 1) { // Chỉ quay nếu trạng thái thay đổi
      // Servo quay từ 0° về 90° (mở cửa sổ khi ánh sáng mạnh)
      for (int pos = 0; pos <= 90; pos += 1) {
        servo_9.write(pos);
        Serial.print("State: ");
        Serial.println(lastState); 
        delay(5); // Đợi 5ms để servo di chuyển
      }
      lastState = 1; // Cập nhật trạng thái (ánh sáng mạnh)
    }
  }

  delay(500); // Dừng 0.5 giây trước khi lặp lại
}