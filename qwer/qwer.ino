#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 accgyro;
Servo srv;
Servo srvX;
int16_t defax, defay, defaz;
int16_t ax, ay, az, gx, gy, gz;
String defx;
String defy;

float toDeg(int angle) {
  return angle / 32768.0 * 180;
}

int lim(int x, int mn, int mx){
  return (x > mx)? mx : ((x < mn) ? mn : x);
}

void setup() {
  srv.attach(6);
  srvX.attach(5);
  Serial.begin(9600);
  Serial.println("steel alive");
  accgyro.initialize();
  srv.write(90);
  srvX.write(90);
//  delay(1000);
//  srv.write(0);
//  delay(1000);
//  srv.write(90);
  delay(1000);
  accgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  defax = ax;
  defay = ay;
  defaz = az;
  delay(100);
  accgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  defax = (defax + ax) / 2;
  defay = (defay + ay) / 2;
  defaz = (defaz + az) / 2;
  delay(100);
  defx = String(toDeg(defax));
  defy = String(toDeg(defay));
}

void loop() {
  accgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  srv.write(90 - toDeg(ay-defay));
  srvX.write(90 - toDeg(ax-defax));
  Serial.print(String(90 - toDeg(ay-defay)) + "\t" + defy);
  Serial.println("\t|\t" + String(90 - toDeg(ax-defax)) + "\t" + defx);
//  delay(1);

}
