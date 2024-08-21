#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
Servo myservo;

const int submit_button = 2;     // the number of the pushbutton pin
const int gram_increase = 3;
const int gram_decrease = 4;
const int spice_increase = 5;
const int spice_decrease = 6;
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int submit_button_state = 0;         // variable for reading the pushbutton status
int gram_increase_state = 0;
int gram_decrease_state = 0;
int spice_increase_state = 0;
int spice_decrease_state = 0;
int var = 0; //switch case

int buttonstate = 0;
int servo_delay = 0;
int spice = 0;
int pos = 0;    // variable to store the servo position

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(submit_button, INPUT);
  digitalWrite(submit_button, HIGH);
  pinMode(gram_increase, INPUT);
  digitalWrite(gram_increase, HIGH);
  pinMode(gram_decrease, INPUT);
  digitalWrite(gram_decrease, HIGH);
  pinMode(spice_increase, INPUT);
  digitalWrite(spice_increase, HIGH);
  pinMode(spice_decrease, INPUT);
  digitalWrite(spice_decrease, HIGH);

  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Spice:");
  lcd.setCursor(0, 1);
  lcd.print("Amount(g):");

  Serial.begin(9600);

}

void loop() {
  // read the state of the pushbutton value:
  submit_button_state = digitalRead(submit_button);
  gram_increase_state = digitalRead(gram_increase);
  gram_decrease_state = digitalRead(gram_decrease);
  spice_increase_state = digitalRead(spice_increase);
  spice_decrease_state = digitalRead(spice_decrease);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

  if (submit_button_state == LOW) {
    Serial.println("Submitted");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dispensing...");
    if (spice == 1) {
      myservo.write(0);              // tell servo to go to position in variable 'pos'
      delay(300);
      delay(servo_delay);

      myservo.write(90);              // tell servo to go to position in variable 'pos'
      delay(300);
    }

    else if (spice == 2) {
      myservo.write(180);              // tell servo to go to position in variable 'pos'
      delay(300);
      delay(servo_delay);

      myservo.write(90);              // tell servo to go to position in variable 'pos'
      delay(300);
      delay(servo_delay);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Spice:");
    lcd.print(spice);
    lcd.setCursor(0, 1);
    lcd.print("Amount(g):");
    lcd.print(servo_delay);
    delay(300);
  }
  else if (gram_increase_state == LOW) {

    servo_delay = servo_delay + 150;
    Serial.println("gram increase");
    Serial.print("Servo delay:");
    Serial.println(servo_delay);

    lcd.setCursor(10, 1);
    lcd.print("      ");
    lcd.setCursor(10, 1);
    lcd.print(servo_delay);
    delay(300);
  }

  else if (gram_decrease_state == LOW) {

    servo_delay = servo_delay - 150;
    Serial.println("gram decrease");
    Serial.print("Servo delay:");
    Serial.println(servo_delay);

    lcd.setCursor(10, 1);
    lcd.print("      ");
    lcd.setCursor(10, 1);
    lcd.print(servo_delay);
    delay(300);
  }

  else if (spice_increase_state == LOW) {

    spice++;
    Serial.println("spice increase");
    Serial.print("spice value:");
    Serial.println(spice);

    lcd.setCursor(6, 0);
    lcd.print("      ");
    lcd.setCursor(6, 0);
    lcd.print(spice);
    delay(300);
  }
  else if (spice_decrease_state == LOW) {
    spice--;
    Serial.println("spice decrease");
    Serial.print("spice value:");
    Serial.println(spice);

    lcd.setCursor(6, 0);
    lcd.print("      ");
    lcd.setCursor(6, 0);
    lcd.print(spice);
    delay(300);
  }
}



