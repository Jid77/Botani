#include <DHT.h>  //library DHT kedalam program

#define DHTPIN 11 // sensor pin 11
#define DHTTYPE DHT11 // jenis sensor DHT11, ubah kalau mau pake sensor lain  DHT22 (AM2302) atau DHT21 (AM2301)

DHT dht(DHTPIN, DHTTYPE); //deklarasi pin sensor dengan jenis sensor yang dipilih

#include <LiquidCrystal.h>//library LCD

LiquidCrystal lcd(7, 6, 5, 4, 3, 2); //pin yang dipadakai LCD

int kipas= 8; //kita menggunakan pin 10 untuk kipas
int air=9;//kita menggunakan pin 9 untuk air
int lampu=10;//kita menggunakan pin 8 untuk lampu

int b_kipas= 12; 
int b_air=A1;
int b_lampu=A2;


int a=0;//variable air
int b=0;//variable lampu
int c=0;//variable kipas
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); //mengatur ukuran lcd yang dipakai
  lcd.print("   Monitoring   ");
  lcd.setCursor(0, 1);
  lcd.print("     Jamur    "); 
  delay(2000);
  dht.begin(); //program komunikasi atau setup untuk sensor DHT 
  
  pinMode(kipas, OUTPUT); //mengatur relay sebagai OUTPUT
  pinMode(air, OUTPUT); 
  pinMode(lampu, OUTPUT); 
  
  pinMode(b_kipas, INPUT);//Tombol Manual
  pinMode(b_air, INPUT); 
  pinMode(b_lampu, INPUT);
  
  pinMode(b_kipas, LOW);//Tombol Manual
  pinMode(b_air, LOW); 
  pinMode(b_lampu, LOW);
  
}

void loop() {
  float kelembaban = dht.readHumidity(); //menyimpan nilai kelembaban pada variabel kelembaban  
  float suhu = dht.readTemperature(); //menyimpan nilai suhu pada variabel suhu
  delay(200); //mengatur jeda waktu pembacaan sensor selama 200 milidetik
  Serial.print("Kelembaban: "); 
  Serial.print(kelembaban); //menampilkan nilai kelembaban pada Serial Monitor
  Serial.print(" "); //menambahkan spasi
  Serial.print("Suhu: ");
  Serial.println(suhu); //menampilkan nilai suhu pada Serial Monitor
  
  //menampilkan nilai kelembaban pada LCD
  lcd.setCursor(0, 0); //
  lcd.print("Kelembaban.: ");
  lcd.print((int) kelembaban);
  lcd.print("%");
  //menampilkan nilai suhu pada LCD
  lcd.setCursor(0, 1);
  lcd.print("Suhu.: ");
  lcd.print((int) suhu);
  lcd.println("Celcius ");



 //Kelembaban melebihi atau kurang dari batas normal
if(a==1){digitalWrite(lampu, HIGH);
Serial.println("LAMPU");}
else{digitalWrite(lampu, LOW);}
if (b==1){digitalWrite(air, HIGH);
Serial.println("AIR");}
else{digitalWrite(air, LOW);}
if (c==1){digitalWrite(kipas, HIGH);
Serial.println("KIPAS");}
else{digitalWrite(kipas, LOW);}

 
 if ( kelembaban > 87.50 || suhu < 23.50)
     {a=1;}
     else{a=0;}
 if ( kelembaban < 73.10 || suhu > 28.90 ) 
     {b=1;}
     else{b=0;}
 if ( suhu > 26.50  )
     {c=1;}
     else{c=0;}
}
