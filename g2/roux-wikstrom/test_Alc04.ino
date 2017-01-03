#include <rgb_lcd.h>
#include <Wire.h>

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
#define greenLEDPin 2
#define redLEDPin 3
const int mq3AnalogPin = A0;
const int button = A1;
bool button_status = false;
char messagePrincipal[38] = "Appuyez sur le bouton pour commencer";
char messageContinue[47] = "Vous pouvez continuer de consommer sans risque";

// TODO make program that will tell person to press button to start the program
// which will tell person to blow when the light is red until the light is green (until value is stable maybe?)
// then give advices on what to do, drink more or stay


void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(47, 2);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(redLEDPin, OUTPUT);
    Serial.begin(9600); // open serial at 9600 bps
    
    lcd.setRGB(colorR, colorG, colorB);
    lcd.setRGB(colorR, colorG, colorB);

    
    // Print a message to the LCD.

    delay(1000);
}

void scroll(int time){
  for (int i=0; i<time/200; i++){
    lcd.scrollDisplayLeft();
    delay(200);
  }
}
    
    
void loop() 
{
      button_status = false;
      digitalWrite(greenLEDPin, LOW);
      lcd.setCursor(4, 0);
      lcd.print(messagePrincipal);
      while (!button_status) {
        button_status = digitalRead(button);
        lcd.scrollDisplayLeft();
        delay(200);
      }
      lcd.clear();
      
      
      
      int j;
      for (j=5; j>0; j--){
        lcd.setCursor(0, 0);
        lcd.print("Soufflez dans :");
        delay(250);
        lcd.setCursor(0,1);
        lcd.print(j);
        delay(750);
        lcd.clear();
      }
      lcd.print("Soufflez !");
      delay(250);
      digitalWrite(redLEDPin, HIGH);
      float avAlcValue = 0.0;
      int temp;
      int i= 0;
      float mq3ValueTot = 0.0;
      

    
     
      
      for (i=0; i<300; i++) {
        float sensorValue = analogRead(A0);
        float sensor_volt=sensorValue/1024.0*5.0;
        float RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL
        
        /*-Replace the name "R0" with the value of R0 in the demo of First Test -*/
        float ratio = RS_gas/6.407;  // ratio = RS/R0
        /*-----------------------------------------------------------------------*/
        
        mq3ValueTot = mq3ValueTot + ratio;
        delay(10);
        
       }
       lcd.clear();
       digitalWrite(redLEDPin, LOW);
       lcd.print("C'est bon !");
       delay(1000);
       lcd.clear();
       avAlcValue = mq3ValueTot / 300.0;
       lcd.setCursor(0,0);
       if (avAlcValue > 2.2) { 
        lcd.print("Alcoolemie");
        lcd.setCursor(0,1);
        lcd.print("estimee:<0,1mg/L");
        delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(messageContinue);
        lcd.setCursor(0,1);
        lcd.print("inuer de consommer sans risque");
        scroll(7000);
       }else if(avAlcValue > 1.2 && avAlcValue <= 2.2) { //First degree, Behavior nearly normal by ordinary observation
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("0,1 mg/L");
        delay(300);
       }else if(avAlcValue > 0.9 && avAlcValue <= 1.2) { //second degree, mild euphoria, sociability, talkitiveness etc
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("0,3 mg/L");
       } else if (avAlcValue > 0.55 && avAlcValue <= 0.9) {
        /*Emotional instability; loss of critical judgment
          Impairment of perception, memory and comprehension
          Decreased sensitory response; increased reaction time
          Reduced visual acuity; peripheral vision and glare recovery
          Sensory-motor incoordination; impaired balance
          Drowsiness
         */
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("0,8 mg/L");
       } else if(avAlcValue > 0.5 && avAlcValue <= 0.55) {
        /*Disorientation, mental confusion; dizziness
          Exaggerated emotional states
          Disturbances of vision and of perception of color, form, motion and dimensions
          Increased pain threshold
          Increased muscular incoordination; staggering gait; slurred speech
          Apathy, lethargy
         */
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("1,0 mg/L");
       } else if (avAlcValue > 0.35 && avAlcValue <= 0.5) {
        /*General inertia; approaching loss of motor functions
          Markedly decreased response to stimuli
          Marked muscular incoordination; inability to stand or walk
          Vomiting; incontinence
          Impaired consciousness; sleep or stupor
         */
        lcd.print("Alcoolemie estimee : ");
        lcd.setCursor(0,1);
        lcd.print("1,5 mg/L");
       } else if (avAlcValue > 0.3 && avAlcValue <= 0.35) {
        // DONT DRINK ANYTHING ELSE (than water)
        lcd.print("Alcoolemie estimee : ");
       // lcd.setCursor(0,1);
        lcd.print("2,2 mg/L");
       } else {
        lcd.print("Danger de mort !.");
       }
       delay(3000);
//       lcd.setCursor(0,0);
//       i=0;
//       while(i<100){
//       lcd.scrollDisplayLeft();
//       delay(200);
//       i++;
//       }
//       delay(3000);
       lcd.clear();
  
}
