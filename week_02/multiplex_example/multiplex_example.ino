
const int ledPin = 13; // the number of the LED pin
int ledState = LOW; // ledState used to set the LED
long previousMillis = 0; // will store last time LED was updated
long interval = 1000; // interval at which to blink (milliseconds)

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin_buttom =  10;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

void setup()
{
    // initialize the LED pin as an output:
    pinMode(ledPin_buttom, OUTPUT);

    // initialize the pushbutton pin as an input:
    pinMode(buttonPin, INPUT);
    pinMode(ledPin, OUTPUT); // set the digital pin as output:
}
void loop()
{
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (buttonState == HIGH)
    {
        // turn LED on:
        digitalWrite(ledPin_buttom, HIGH);
    }
    else
    {
        // turn LED off:
        digitalWrite(ledPin_buttom, LOW);
    }

    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis > interval)
    {
        previousMillis = currentMillis; // save the last time you blinked the LED
        if (ledState == LOW) // if the LED is off turn it on and vice-versa
            ledState = HIGH;
        else
            ledState = LOW;
        digitalWrite(ledPin, ledState);
    }

}
