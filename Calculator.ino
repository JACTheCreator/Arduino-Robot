#include <LiquidCrystal.h>
#include <Keypad.h>

void addTextToScreenBottom(String);
void doMath();
void clearScreen();
void backspace();
bool startsWith(char*, char*);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int buzzerPin = 13;
const byte ROWS = 5;
const byte COLS = 4;
char keys[ROWS][COLS] = {{'C','E','N','+'},
                         {'9','8','7','-'},
                         {'4','5','6','*'},
                         {'1','2','3','/'},
                         {'0','.','M','='}};

byte rowPins[ROWS] = {A0, A1, A2, A3, A4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9, 10}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String numStr = "0";

void setup()
{
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.setCursor(15, 1);
    lcd.print(numStr);

    /*tone(buzzerPin, 50);*/
}

void loop()
{
    char key = keypad.getKey();

    switch(key)
    {
        case 'C':
        break;

        case 'E':
        break;

        case 'N':
        break;

        case 'M':
        break;

        case '.':
        break;

        case '+':
        break;

        case '-':
        break;

        case '*':
        break;

        case '/':
        break;

        case '=':
        break;

        case '9':
          addTextToScreenBottom("9");
        break;
        
        case '8':
          addTextToScreenBottom("8");
        break;
        
        case '7':
          addTextToScreenBottom("7");
        break;
        
        case '6':
          addTextToScreenBottom("6");
        break;
        
        case '5':
          addTextToScreenBottom("5");
        break;
        
        case '4':
          addTextToScreenBottom("4");
        break;
               
        case '3':
          addTextToScreenBottom("3");
        break;
        
        case '2':
          addTextToScreenBottom("2");
        break;
        
        case '1':
          addTextToScreenBottom("1");        
        break;
        
        case '0':
          addTextToScreenBottom("0");
        break;
    }
}

void addTextToScreenBottom(String buttonPressed)
{
    if (numStr.startsWith("0"))
    {
      numStr = buttonPressed + "";
    }
    else
    {
      numStr += buttonPressed;
    }
    lcd.clear();
    lcd.print(numStr);
}
