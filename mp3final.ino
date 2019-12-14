#include <SoftwareSerial.h>
SoftwareSerial Geno(7, 8); // Rx , Tx

unsigned char Data[10];
unsigned char i;
boolean song;

void setup() {
  delay(1000);
  Geno.begin(9600);
  Serial.begin(9600);
  delay(1000);
  SetVolume(30);
  pinMode(2, INPUT);
}

void playTrack(int num) {

  Data[0] = 0x7E;
  Data[1] = 0x04;
  Data[2] = 0xA2;
  Data[3] = 0x00;
  Data[4] = 0x02;
  Data[5] = 0x7E;
  Command(Data, 5);
  play_pause();
  



}

void repeat_song(){
  Data[0] = 0x7E;
  Data[1] = 0x02;
  Data[2] = 0xA9;
  Data[3] = 0x01;
  Data[4] = 0x7E;
  Command(Data, 5);
}

void SetVolume( int vol) {
  Data[0] = 0x7E; // START
  Data[1] = 0x04; // Length Not 0x02
  Data[2] = 0xA7; // Command
  Data[3] = vol; // new volume
  Data[4] = 0x7E; // END
  Command(Data, 5);
}
void play_pause() {
  Data[0] = 0x7E; // START
  Data[1] = 0x02; // Length
  Data[2] = 0xA3; // Command
  Data[3] = 0x7E; //Mode parameter
  Command(Data, 4);
}

void stop_playing() {
  Data[0] = 0x7E;
  Data[1] = 0x02;
  Data[2] = 0xA4;
  Data[3] = 0x7E;
  Command(Data, 4);
}

void next_song() {
  Data[0] = 0x7E;
  Data[1] = 0x02;
  Data[2] = 0xA5;
  Data[3] = 0x7E;
  Command(Data, 4);
}
void Command(unsigned char *Data, int length) {

  for (int i = 0; i < length; i++) {
    Geno.write(Data[i]);
  }

}

void loop() {

  ///photo///
  //  SetVolume(30);
  int track = 1;
//  repeat_song();
  playTrack(track);
  if (analogRead(A0) < 800) {
    play_pause();
  }
  else if (analogRead(A0) > 800 && digitalRead(2) == 1) {

    next_song();
  }
  Serial.println(analogRead(A0));
  Serial.println(digitalRead(2));
}
