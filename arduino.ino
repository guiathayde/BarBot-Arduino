#include <SoftwareSerial.h> //INCLUSÃO DE BIBLIOTECA

const int pinoRX = 2;    // PINO DIGITAL 2 (RX)
const int pinoTX = 3;    // PINO DIGITAL 3 (TX)
const int pinoLed = 12;  // PINO DIGITAL UTILIZADO PELO LED
int dadoBluetooth = 0;   // VARIÁVEL QUE ARMAZENA O VALOR ENVIADO PELO BLUETOOTH
boolean loopLED = false; // VARIÁVEL BOOLEANA QUE FAZ O CONTROLE DE ATIVAÇÃO DO LOOP DO LED

SoftwareSerial bluetooth(pinoRX, pinoTX); // PINOS QUE EMULAM A SERIAL, ONDE
// O PINO 2 É O RX E O PINO 3 É O TX

void setup()
{
  Serial.begin(9600);       // INICIALIZA A SERIAL
  bluetooth.begin(9600);    // INICIALIZA A SERIAL DO BLUETOOTH
  bluetooth.print("$");     // IMPRIME O CARACTERE
  bluetooth.print("$");     // IMPRIME O CARACTERE
  bluetooth.print("$");     // IMPRIME O CARACTERE
  pinMode(pinoLed, OUTPUT); // DEFINE O PINO COMO SAÍDA
}

void loop()
{
  if (bluetooth.available())
  {                                   // SE O BLUETOOTH ESTIVER HABILITADO, FAZ
    dadoBluetooth = bluetooth.read(); // VARIÁVEL RECEBE O VALOR ENVIADO PELO BLUETOOTH

    if (dadoBluetooth == 'm')
    {
      Serial.println("Set-up Vodka");
    }

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
  }
}