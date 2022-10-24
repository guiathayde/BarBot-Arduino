#include <SoftwareSerial.h> //INCLUSÃO DE BIBLIOTECA

const int pinoRX = 2; // PINO DIGITAL 2 (RX)
const int pinoTX = 3; // PINO DIGITAL 3 (TX)

String message;
char character;
boolean isMessageComplete = false;

SoftwareSerial bluetooth(pinoRX, pinoTX); // PINOS QUE EMULAM A SERIAL, ONDE
// O PINO 2 É O RX E O PINO 3 É O TX

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!");
}

void loop()
{
  if (bluetooth.available())
  {
    readMessage();

    if (isMessageComplete)
    {
      if (message.length() > 0)
        Serial.println(message);

      // Vodka sprite
      if (message == "Make Vodka Sprite")
      {
        Serial.println("Vodka Sprite in the making");
        bluetooth.println("Vodka Sprite");
      }
      else if (message == "Make Blue Lagoon")
      {
        Serial.println("Blue Lagoon in the making");
        bluetooth.println("Blue Lagoon");
      }
      else if (message == "Make Cosmo")
      {
        Serial.println("Cosmo in the making");
        bluetooth.println("Cosmo");
      }
      else if (message == "Make Lemon Drop")
      {
        Serial.println("Lemon Drop in the making");
        bluetooth.println("Lemon Drop");
      }
      else if (message == "Make Blue Moon")
      {
        Serial.println("Blue Moon in the making");
        bluetooth.println("Blue Moon");
      }
      else if (message == "Make Blue Gin Moon")
      {
        Serial.println("Blue Gin Moon in the making");
        bluetooth.println("Blue Gin Moon");
      }

      message = "";
      isMessageComplete = false;
    }
  }
}

void readMessage()
{
  while (bluetooth.available())
  {
    character = bluetooth.read();
    if (character != '#')
      message.concat(character);
    else
      isMessageComplete = true;
  }
}

// void readMessage()
// {
//   while (bluetooth.available())
//   {
//     character = bluetooth.read();
//     message.concat(character);
//     if (character == '#')
//     {
//       Serial.println(message);
//       message = "";
//     }
//   }
// }