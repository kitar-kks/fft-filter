// Our Global Sample Rate, 2000hz
#define LIN_OUT 1 // use the lin output function
#define FFT_N 256 // set to 256 point fft
#define SAMPLEPERIODUS 3300 // Sampling frequency = 1/SAMPLEPERIODUS, where SAMPLEPERIODUS is the sampling period in microsec.

#define Fs 2000
#define Freq 100

#include <FFT.h> // include the library

int inPin = 0; // voltage connected to analog pin

int ampMax = 0;
int pos = 0;
int checkPos = 0;
 
void setup() {
    pinMode(13, OUTPUT);
    pinMode(inPin,INPUT);
    Serial.begin(115200); // use the serial port
}

void loop() {
    unsigned long time = micros(); // Used to track rate

    // Add your program here

    for (int i = 0 ; i < 512 ; i += 2) { // save 256 samples
      
      fft_input[i] = analogRead(inPin);
      fft_input[i+1] = 0;

      // Consume excess clock cycles, to keep at desired sampling frequency
      for(unsigned long up = time+SAMPLEPERIODUS; time > 0 && time < up-20; time = micros());
       
    }

    fft_reorder(); // reorder the data before doing the fft
    fft_run(); // process the data in the fft
    fft_mag_lin(); // take the output of the fft
    
    pos = 0;
    ampMax = 0;
    
    for(int i = 0 ; i < 128 ; i ++) {
   
     if((i != 0)&&(fft_lin_out[i] > ampMax)){
      ampMax = fft_lin_out[i];
      pos = i;
     }
    }

    checkPos =150*128/150;

    Serial.print("checkPos      ");
    Serial.print(checkPos);
    Serial.print("         Pos        ");
    Serial.println(pos);
   
    
    if(pos == 126){
      digitalWrite(13, HIGH);
    }else{
      digitalWrite(13, LOW);
    }
    
     
    
}
