#define BLYNK_PRINT Serial //library Blynk
#include <ESP8266_Lib.h> //library ESP8266
#include <BlynkSimpleShieldEsp8266.h> //library blynk untuk Arduino + ESP8266

char auth[] = "qrAA0EweKfttsk6v1EgTa1uaU5ADYlgh"; //token server (dapet dari Blynk)
char ssid[] = "iPhone"; //nama wifi
char pass[] = "Pa55word"; //passwordnya

#define EspSerial Serial1 //untuk arduino mega RX TX

#define ESP8266_BAUD 9600 //serial baud buat ESP8266

ESP8266 wifi(&EspSerial); //setting serial baud esp

BlynkTimer timer; //timer buat ngelakuin satu fungsi setiap 1 detik (Blynk g bisa pake delay

/*pin (ruang 1 genap,  ruang 2 ganjil):
   suhu = 0 dan 1
   api = 2 DAN 3
   gas = A0 DAN A1
   servo = 4 dan 5
   relay = 6 dan 7
   lampu darurat = 8 dan 9
   buzzer = 10,11
*/

#include <DHT.h> //library dht 
#define DHTPIN1 0  //pin dht ruang 1
#define DHTPIN2 1  //pin dht ruang 2
#define DHTTYPE1 DHT22 //tipe jenis dht (DHT11,DHT21,DHT22)
#define DHTTYPE2 DHT22
DHT dht1(DHTPIN1, DHTTYPE1); //object dht ruang 1 di pin 0 dan jenisnya dht22
DHT dht2(DHTPIN2, DHTTYPE2);

//pin IR Flame sensor
int flamePin1 = 2; 
int flamePin2 = 3;
//pin sensor gas
int gasPin1 = A0;
int gasPin2 = A1;

int flame1, flame2; //variabel yang berisi data dari sensor api
int gas1, gas2; //variabel yang berisi data dari sensor gas
float suhu1, suhu2; //variabel yang berisi data temperature (Celsius)
float kelembapan1, kelembapan2; //variabel yang berisi data tingkat kelembapan
float heatIndex1, heatIndex2; //variabel yang berisi data tingkat panas

#include <Servo.h> //library servo
//setting servo
Servo myservo1;
Servo myservo2;

String debugText1, debugText2; //variabel berisi text yang akan muncul di aplikasi

//pin relay
int relay1 = 6;
int relay2 = 7;
//pin buzzer
int buzzer = 11;
//pin lampu darurat
int lampuD1 = 8;
int lampuD2 = 9;

bool aktif1, aktif2; //variabel berisi data jika alat diaktifkan melalui aplikasi

String error1, error2; //variabel yang berisi data jika terjadi error

bool adaApi; //jika ada api

void getData() {  //fungsi untuk mendapatkan data dari sensor
  //mendapatkan data dari sensor api
  flame1 = digitalRead(flamePin1);
  flame2 = digitalRead(flamePin2);
  //mendapatkan data dari sensor gas
  gas1 = analogRead(gasPin1);
  gas2 = analogRead(gasPin2);
  //mendapatkan data dari sensor dht (temperature celsius)
  suhu1 = dht1.readTemperature();
  suhu2 = dht2.readTemperature();
  //mendapatkan data dari snesor dht (kelembapan)
  kelembapan1 = dht1.readHumidity();
  kelembapan2 = dht2.readHumidity();
  //menghitung tingkat panas dengan mengkalkulasikan temperatur dan kelembapan
  heatIndex1 = dht1.computeHeatIndex(suhu1, kelembapan1, false);
  heatIndex2 = dht2.computeHeatIndex(suhu2, kelembapan2, false);
}

BLYNK_CONNECTED() { //mengkonek Virtual pin di aplikasi
  Blynk.syncVirtual(V2); //mengkonek tombol on/off di ruang 1 dalam aplikasi
  Blynk.syncVirtual(V3); //mengkonek tombol on/off di ruang 2 dalam aplikasi
}

BLYNK_WRITE(V2) {
  int i = param.asInt(); //mendapatkan data dari tombol 1 atau 0
  if (i == 1) { //jika 1
    aktif1 = true;  //aktif1 menjadi true
  } else { //atau jika tidak
    aktif1 = false; //aktif1 akan jadi false
  }
}

BLYNK_WRITE(V3) { //sama kayak diatas cuma ini untuk ruang 2
  int i = param.asInt();
  if (i == 1) {
    aktif2 = true;
  } else {
    aktif2 = false;
  }
}

void sendData() { //mengirim data ke server blynk dengan metode push
  Blynk.virtualWrite(V0, debugText1); //mengirim data text debug di ruang 1
  Blynk.virtualWrite(V1, debugText2);

  if(adaApi == true){ //jika ada api
    Blynk.notify("FIRE DETECTED"); //menotifikasi aplikasi
  }
}

void setup() {
  // put your setup code here, to run once:
  // Debug console
  Serial.begin(9600); //memulai serial di baud 9600

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD); //memulai serial untuk esp
  delay(10); //delay 10 (delay diatas 10 akan menyebabkan esp tidka konek ke server

  Blynk.begin(auth, wifi, ssid, pass); //mengkonek esp ke wifi

  dht1.begin(); //memulai sensor dht di ruang 1
  dht2.begin();

  myservo1.attach(4); //pin servo digital
  myservo2.attach(5);

  timer.setInterval(1000L, sendData); //menjalankan fungsi "sendData" untuk mengirim data ke server setiap 1 detik (1000L) L adalah tipe data "long"

  debugText1 = "start"; //menulis "start" di aplikasi
  debugText2 = "start";

  pinMode(relay1, OUTPUT); //pin relay menjadi output
  pinMode(relay2, OUTPUT);

  pinMode(buzzer, OUTPUT); //pin buzzer menjadi output

  digitalWrite(relay1, HIGH); //mensetting lampu ruangan agar nyala di awal
  digitalWrite(relay2, HIGH);

  digitalWrite(buzzer, LOW); //mematikan buzzer diawal

  pinMode(lampuD1, OUTPUT); //pin lampu darurat sebagai output
  pinMode(lampuD2, OUTPUT);

  digitalWrite(lampuD1, LOW); //mematikan lampu darurat di awal
  digitalWrite(lampuD2, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run(); //mengkonek esp ke server
  getData(); //mendapatkan data dari sensor
  timer.run(); //memulai mengirim data setiap 1 detik

  if (aktif1 == 1) { //jika diaktifkan dari aplikasi
    if (heatIndex1 > 50 || gas1 > 400 || flame1 == 0) { //jika suhu > 50 atau gas > 400 atau flame = 0
      debugText1 = "detected";
      myservo1.write(180); //memutar servo 180 derajat
      adaApi = true; //ada api menjadi true
      digitalWrite(relay1, LOW); //mematikan listrik lampu
      digitalWrite(buzzer, HIGH); //menyalakan buzzer
      digitalWrite(lampuD1, HIGH); //menyalakan lampu darurat
    } else { //jika tidak
      debugText1 = "none";
      myservo1.write(0); //memutar servo kembali ke 0 derajat
      adaApi = false; //ada apu jadi false
      digitalWrite(relay1, HIGH); //menyambung listrik lampu
      digitalWrite(buzzer, LOW); //mematikan buzzer
      digitalWrite(lampuD1, LOW); //mematikan lampu darurat
    }
  } else { //jika tidak aktif
    debugText1 = "--"; 
    myservo1.write(0); //memutar servo ke awal
    adaApi = false; //tidak ada api
    digitalWrite(relay1, HIGH); //menyambung listrik
    digitalWrite(buzzer, LOW); //mematikan buzzer
    digitalWrite(lampuD1, LOW); //mematikan lampu darurat
  }

  if (aktif2 == true) { //sma kaya di atas
    if (heatIndex2 > 50 || gas2 > 400 || flame2 == 0) {
      debugText2 = "detected";
      myservo2.write(180);
      adaApi = true;
      digitalWrite(relay2, LOW);
      digitalWrite(buzzer, HIGH);
      digitalWrite(lampuD2, HIGH);
    } else {
      debugText2 = "none";
      myservo2.write(0);
      adaApi = false;
      digitalWrite(relay2, HIGH);
      digitalWrite(buzzer, LOW);
      digitalWrite(lampuD2, LOW);
    }
  } else {
    debugText2 = "--";
    adaApi = false;
    myservo2.write(0);
    digitalWrite(relay2, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(lampuD2, LOW);
  }

  if (isnan(suhu1) || isnan(kelembapan1)) { //jika sensro dht error
    error1 = "DHT err";
  } else { //jika tidak
    error1 = "OK";
  }

  if (isnan(suhu2) || isnan(kelembapan2)) {
    error2 = "DHT err";
  } else {
    error2 = "OK";
  }
}
