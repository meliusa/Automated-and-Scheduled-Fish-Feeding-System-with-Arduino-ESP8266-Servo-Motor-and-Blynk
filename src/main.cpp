#include <Arduino.h>
#include <Servo.h>
// include library blynk
#include <BlynkSimpleEsp8266.h>

// ambil template_id, device_id, dan token dari aplikasi blynk
#define BLYNK_TEMPLATE_ID "TMPL6vUH5dFit"
#define BLYNK_TEMPLATE_NAME "Pakan Ikan"
#define BLYNK_AUTH_TOKEN "I5Sz_D1udF-ROnWTOKXF38dDElvI4OEl"

// buat sebuah object untuk servonya
Servo myservo;

// buat sebuah variabel untuk menampung datastream StatusPakan
int StatusPakan;

void BeriPakan()
{
  // proses perputaran t4 pakan secara halus
  for (int posisi = 0; posisi <= 180; posisi++)
  {
    // set posisi servo berdasarkan variabel posisi
    myservo.write(posisi);
    delay(10);
  }

  // proses perputaran t4 pakan kembali ke posisi awal
  for (int posisi = 180; posisi >= 0; posisi--)
  {
    myservo.write(posisi);
    delay(10);
  }
}

void setup()
{
  // pin yang digunakan untuk servo = D2  = 4
  myservo.attach(4);
  // posisi servo awal
  myservo.write(0);

  Serial.begin(115200);

  // koneksi ke wifi
  WiFi.begin("iPhone Meliusa", "anuanuanu");
  // uji apakah berhasil konek atau tidak
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Terkoneksi");

  // apabila terkoneksi, koneksikan perangkat ke blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, "iPhone Meliusa", "anuanuanu");

  Serial.println("Blynk Terkoneksi");
}

void loop()
{
  // jalankan aplikasi blynk dari NodeMCU
  Blynk.run();

  // tampilkan StatusPakan di serial monitor
  Serial.println("Status Pakan : " + String(StatusPakan));

  // jika StatusPakan = 1 maka beri pakan
  if (StatusPakan == 1)
  {
    // panggil void BeriPakan, 1 siklus perputaran sampai kembali ke
    // posisi awal
    BeriPakan();
    // kembalikan StatusPakan menjadi 0 setelah diberi pakan
    Blynk.virtualWrite(V0, 0);
    StatusPakan = 0;
    delay(2000);
  }
}

// baca datastream StatusPakan
BLYNK_WRITE(V0)
{
  // baca datastream kemudian tampung kedalam variabel StatusPakan
  StatusPakan = param.asInt();
}
