#include <SoftwareSerial.h> //INCLUSÃO DE BIBLIOTECA

const int pinoRX = 2;  // PINO DIGITAL 2 (RX)
const int pinoTX = 3;  // PINO DIGITAL 3 (TX)
int dadoBluetooth = 0; // VARIÁVEL QUE ARMAZENA O VALOR ENVIADO PELO BLUETOOTH

SoftwareSerial bluetooth(pinoRX, pinoTX); // PINOS QUE EMULAM A SERIAL, ONDE
// O PINO 2 É O RX E O PINO 3 É O TX

void setup()
{
  Serial.begin(9600);    // INICIALIZA A SERIAL
  bluetooth.begin(9600); // INICIALIZA A SERIAL DO BLUETOOTH
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!");
}

void loop()
{
  if (bluetooth.available())
  {                                   // SE O BLUETOOTH ESTIVER HABILITADO, FAZ
    dadoBluetooth = bluetooth.read(); // VARIÁVEL RECEBE O VALOR ENVIADO PELO BLUETOOTH

    // Vodka sprite
    if (dadoBluetooth == 'a')
    {
      Serial.println("Vodka Sprite in the making");
    }

    // Blue Lagoon
    if (dadoBluetooth == 'b')
    {
      Serial.println("Blue Lagoon in the making");
    }

    // Cosmo
    if (dadoBluetooth == 'c')
    {
      Serial.println("Cosmo in the making");
    }

    // Lemon drop
    if (dadoBluetooth == 'd')
    {
      Serial.println("Lemon drop in the making");
    }

    // Blue Moon
    if (dadoBluetooth == 'e')
    {
      Serial.println("Blue Moon in the making");
    }

    // Blue Gin Moon
    if (dadoBluetooth == 'f')
    {
      Serial.println("Blue Gin Moon in the making");
    }
  }
}