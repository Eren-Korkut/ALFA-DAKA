 #include <Servo.h>
Servo myServos[10]; //10 tane servo motor
const int sagx_eks = A8;
const int sagy_eks = A9;
int sagx_durum;   //sağ joyistick x ekseni
int sagy_durum;   //sol joyistick y ekseni
float pi=3.14159; //rulmanlar yuvarlak olduğu için pinin değerini yazdık
int TotalNumberofServos=10; //gerektiği gibi değişebilir 
int ServosPerSide=TotalNumberofServos/2;
float shift = 2*pi/ServosPerSide; // segmenteler arasında zaman gecikmesi
int amplitude = 50;
int offset = 0;
float rads;
float Speed=2;
float Wavelengths=1.5;
int Multiplier;

void setup() {
  Serial.begin(9600);
  myServos[0].attach(A0);
  myServos[1].attach(A1);
  myServos[2].attach(A2);
  myServos[3].attach(A3);
  myServos[4].attach(A4);
  myServos[5].attach(A5);
  myServos[6].attach(4);
  myServos[7].attach(3);
  myServos[8].attach(8);
  myServos[9].attach(7);

}


void sidewind(String Direction){
   //works best with Wavelengths=1.5
  if(Direction=="Left"){ Multiplier=1; }
  else if(Direction=="Right"){ Multiplier=-1; }
  for(int i=0; i<360; i++){
   rads=i*pi/180.0;     //dereceden radyana geçirmek
   for(int j=0; j<5; j++){  
      myServos[2*j+1].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/4)); //servoları dikey düzlemde haraket ettirir //60 derece pi/3 de olur
      myServos[2*j].write(90+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/4)); //servoları yatay düzlemde haraket ettirir ama bu kod 360 dönmesi içindir
   }
   delay(10);
  }
}

void sidewindTurn(String Direction){
  if(Direction=="Left"){ Multiplier=1; }
  else if(Direction=="Right"){ Multiplier=-1; }
  for(int i=0; i<360; i++){
   rads=i*pi/180.0;     //dereceden radyana geçirmek
   for(int j=0; j<3; j++){  
     myServos[2*j+1].write(60+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift+(Multiplier+1)*pi/3)); // servoları "Left" olunca sola "Right" olunca sağa döndürür
     myServos[2*j].write(60+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/3)); 
   }
   for(int j=3; j<5; j++){  
     myServos[2*j+1].write(60+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/3));
     myServos[2*j].write(60+offset+amplitude*sin(Speed*rads+j*Wavelengths*shift-(Multiplier-1)*pi/3)); 
   }
   delay(10);
  }

}


void strike(){
  myServos[0].write(90);//0 olursa ileri gidebilir
  delay(10);
  myServos[1].write(0);//30-60-90
  delay(10);
  myServos[2].write(90);//0
  delay(10);
  myServos[3].write(180);//30-60-90
  delay(10);
  myServos[4].write(90);//0
  delay(10);
  myServos[5].write(0);//30-60-90
  delay(10);
  myServos[6].write(0);//0
  delay(10);
  myServos[7].write(130);//30-60-90
  delay(10);
  myServos[8].write(90);//0
  delay(10);
  myServos[9].write(180);//30-60-90
  delay(10);

  //vurmadan 5 saniye önce bekler
  delay(5000);    
  //ön kısmı yani kafası ileri gidip eline çak yapar
  myServos[7].write(80);
  delay(10);
  myServos[9].write(120);
  delay(200);

  //vurduktan sonra bekleme posisyonu
 
}

void loop() {
sagx_durum = analogRead(sagx_eks);
sagy_durum = analogRead(sagy_eks);
int solx=analogRead(A6);
int soly=analogRead(A7);
int solxmap=map(solx,0,1023,0,180);
int solymap=map(soly,0,1023,0,180);
myServos[9].write(solxmap);
myServos[8].write(solymap);

if(sagx_durum >1020){ // İLERİ GİTMEK İÇİN 
  sidewindTurn("Left");
  }

    else if(sagx_durum<50) { // GERİTMEK İÇİN
    sidewindTurn("Right");
    
  }
    else if(sagy_durum>1020){ //SAGA GITMEK İÇİN 

 sidewind("Right");
  
 }


 else if(sagy_durum<50) { // SOLA GITMEK ICIN 

  sidewind("Left");
  
 }

 else { // EĞRER JEOSTİK KULANILMAZ ISE 
  
  
 }
  //sidewind("Left");  //sol
  //sidewind("Right"); //sağ
  //sidewindTurn("Left"); //ileri
  //sidewindTurn("Right"); //geri
  //strike(); // çak beşlik
  
  //istediğiniz haraketi "//" bu işareti kaldırarak aktifleştirebilirsiniz
}
