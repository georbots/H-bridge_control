// setting pins connected to H-Bridge
int enB = 5;
int in3 = 7;
int in4 = 6;

// setting pins connected to the buttons
const int buttonPin1 = 2;
const int buttonPin2 = 8;         

int buttonState1 = 0;         // variables for button states
int buttonState2 = 0;


int x = 0;// variable for speed and direction
int y = 15;// variable for acceleration

void setup()
{
  // output pins
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //input pins
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);

  Serial.begin(9600);

}
void loop()
{
  buttonState1 = digitalRead(buttonPin1); //read button inputs
  buttonState2 = digitalRead(buttonPin2);

    while (buttonState1==HIGH){ // as button one is pressed speed is gradually reduced until the button isn't pressed or the minimum value is reached
      if (x>-255) x--;
      Serial.println(x); // print speed on the computer
      if (x<0){       //change direction of rotation depending on the speed
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      else{
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }
      analogWrite(enB, abs(x)); 
	  
       buttonState1 = digitalRead(buttonPin1);
       buttonState2 = digitalRead(buttonPin2);
       if (buttonState1==HIGH && buttonState2==HIGH) {//if both buttons are pressed the motor stops
        x=0;
        delay(100);
       }
       delay(y); //this delay defines the value of acceleration of the rotation
      }
      
    while (buttonState2==HIGH){// speeding up while button two is pressed
      if (x<255) x++;
      Serial.println(x);
      if (x<0){
        digitalWrite(in3, HIGH);
        digitalWrite(in4, LOW);
      }
      else{
        digitalWrite(in3, LOW);
        digitalWrite(in4, HIGH);
      }
      analogWrite(enB, abs(x));
	  
       buttonState2 = digitalRead(buttonPin2);
       buttonState1 = digitalRead(buttonPin1);
       if (buttonState1==HIGH && buttonState2==HIGH){
        x=0;
        delay(100);
       }
       delay(y); 
      }
      
     while (buttonState1==LOW && buttonState2==LOW){// if no button is pushed the speed remains unchanged
       analogWrite(enB, abs(x));
       Serial.println(x);//
       buttonState1 = digitalRead(buttonPin1);
       buttonState2 = digitalRead(buttonPin2);
     }
}
