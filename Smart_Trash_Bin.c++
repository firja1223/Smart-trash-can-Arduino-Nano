#include <Servo.h>

/* ====== Diketahui ====== */
const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 7;

const int jarakBuka = 15;    // cm
const int sudutTutup = 0;    // derajat
const int sudutBuka = 90;    // derajat
const int durasiBuka = 3000; // ms

/* ====== Variabel ====== */
Servo myServo;
long durasi;
int jarak;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    myServo.attach(servoPin);
    myServo.write(sudutTutup);
}

void loop()
{
    jarak = bacaUltrasonic();

    if (jarak > 0 && jarak <= jarakBuka)
    {
        myServo.write(sudutBuka);  // buka tutup
        delay(durasiBuka);         // tahan terbuka
        myServo.write(sudutTutup); // tutup kembali
        delay(1000);               // jeda agar tidak berulang cepat
    }
}

/* ====== Fungsi Ultrasonic ====== */
int bacaUltrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    durasi = pulseIn(echoPin, HIGH, 25000); // timeout ±4 m
    if (durasi == 0)
        return -1;

    // Rumus jarak
    // jarak = (durasi × 0.034) / 2
    int jarakCm = durasi * 0.034 / 2;
    return jarakCm;
}
