#include <SoftwareSerial.h>
#include <EEPROM.h>

const int pinoRX = 0; // PINO DIGITAL (RX)
const int pinoTX = 1; // PINO DIGITAL (TX)

int Vodka = 2;
int Cointreau = 3;
int CranberryJuice = 4;
int Sprite = 5;
int LemonJuice = 6;
int SugarWater = 7;
int BlueCur = 8;
int Gin = 9;
int TimeBetweenPours = 500;

String message;
char character;
boolean isMessageComplete = false;

struct Drink
{
  char name[32];
  int quantity;
};

int drinkOneAddress = 0;
int drinkTwoAddress = drinkOneAddress + sizeof(Drink);
int drinkThreeAddress = drinkTwoAddress + sizeof(Drink);
int drinkFourAddress = drinkThreeAddress + sizeof(Drink);
int drinkFiveAddress = drinkFourAddress + sizeof(Drink);
int drinkSixAddress = drinkFiveAddress + sizeof(Drink);

SoftwareSerial bluetooth(pinoRX, pinoTX);

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!");

  // Set pin 2-9 to output pins to drive the relay board
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void loop()
{
  if (bluetooth.available())
  {
    readMessage();

    if (isMessageComplete)
    {
      message.remove(0, 2);
      Serial.println("Comando recebido: " + message);

      if (printAvailableSpaceMemory())
        ;
      else if (sendInitialSetup())
        ;
      else if (setupDrinks())
        ;
      else if (makeDrink())
        ;
      else
      {
        Serial.println("Invalid Command");
        bluetooth.println("Invalid Command");
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

boolean makeDrink()
{
  if (message.equals("Make Vodka Sprite"))
  {
    mix(3000, 0, 0, 0, 5000, 0, 0, 0);
    return true;
  }
  else if (message.equals("Make Blue Lagoon"))
  {
    mix(2000, 0, 0, 5000, 1800, 1000, 1800, 0);
    return true;
  }
  else if (message.equals("Make Cosmo"))
  {
    mix(2500, 1500, 3800, 0, 1200, 1200, 0, 0);
    return true;
  }
  else if (message.equals("Make Lemon Drop"))
  {
    mix(1500, 1500, 0, 0, 1800, 1200, 0, 0);
    return true;
  }
  else if (message.equals("Make Blue Moon"))
  {
    mix(2000, 0, 3000, 0, 1800, 1200, 1200, 0);
    return true;
  }
  else if (message.equals("Make Blue Gin Moon"))
  {
    mix(0, 0, 3000, 0, 1800, 1200, 1200, 2000);
    return true;
  }
  else if (message.equals("Make Double Strike"))
  {
    mix(2000, 0, 3000, 0, 1800, 0, 1200, 0);
    return true;
  }
  else if (message.equals("Make Tom Collins"))
  {
    mix(0, 0, 0, 4000, 1800, 1800, 0, 2200);
    return true;
  }
  else if (message.equals("Make Flying Dutchman"))
  {
    mix(0, 2000, 0, 0, 1200, 1000, 0, 2000);
    return true;
  }
  else if (message.equals("Make London Cosmo"))
  {
    mix(0, 2000, 5000, 1800, 0, 0, 0, 2000);
    return true;
  }
  else if (message.equals("Make Vodka Cranberry"))
  {
    mix(2000, 0, 5000, 0, 0, 1200, 0, 0);
    return true;
  }
  else if (message.equals("Make Cranberry Gin"))
  {
    mix(0, 0, 5000, 0, 2000, 0, 0, 2200);
    return true;
  }

  return false;
}

boolean printAvailableSpaceMemory()
{
  if (message.equals("Print Available Space Memory"))
  {
    Serial.print("EEPROM.length(): ");
    Serial.println(EEPROM.length());

    bluetooth.print("EEPROM.length(): ");
    bluetooth.println(EEPROM.length());
    return true;
  }

  return false;
}

boolean sendInitialSetup()
{
  if (message.equals("InitialSetup"))
  {
    Drink drinkOne = getDrinkSetup(drinkOneAddress);
    Drink drinkTwo = getDrinkSetup(drinkTwoAddress);
    Drink drinkThree = getDrinkSetup(drinkThreeAddress);
    Drink drinkFour = getDrinkSetup(drinkFourAddress);
    Drink drinkFive = getDrinkSetup(drinkFiveAddress);
    Drink drinkSix = getDrinkSetup(drinkSixAddress);

    String separator = ":";
    String initialSetup = drinkOne.name + separator + drinkOne.quantity + separator + drinkTwo.name + separator + drinkTwo.quantity + separator + drinkThree.name + separator + drinkThree.quantity + separator + drinkFour.name + separator + drinkFour.quantity + separator + drinkFive.name + separator + drinkFive.quantity + separator + drinkSix.name + separator + drinkSix.quantity;

    bluetooth.print(initialSetup);

    return true;
  }

  return false;
}

void setupDrink(int drinkAddress)
{
  String nameDrink = getValue(message, ':', 1);
  String quantityDrinkString = getValue(message, ':', 2);
  int quantityDrink = quantityDrinkString.toInt();

  saveDrinkSetup(nameDrink, quantityDrink, drinkAddress);

  Serial.println("Drink" + nameDrink + "Changed");
  bluetooth.println("Drink" + nameDrink + "Changed");
}

boolean setupDrinks()
{
  if (message.substring(0, 13) == "drinkOneSetup")
  {
    setupDrink(drinkOneAddress);
    return true;
  }
  else if (message.substring(0, 13) == "drinkTwoSetup")
  {
    setupDrink(drinkTwoAddress);
    return true;
  }
  else if (message.substring(0, 15) == "drinkThreeSetup")
  {
    setupDrink(drinkThreeAddress);
    return true;
  }
  else if (message.substring(0, 14) == "drinkFourSetup")
  {
    setupDrink(drinkFourAddress);
    return true;
  }
  else if (message.substring(0, 14) == "drinkFiveSetup")
  {
    setupDrink(drinkFiveAddress);
    return true;
  }
  else if (message.substring(0, 13) == "drinkSixSetup")
  {
    setupDrink(drinkSixAddress);
    return true;
  }

  return false;
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void saveDrinkSetup(String name, int quantity, int address)
{
  Drink drink;

  name.toCharArray(drink.name, 32);
  drink.quantity = quantity;

  EEPROM.put(address, drink);

  Serial.print("Drink ");
  Serial.print(drink.name);
  Serial.print(" saved to address ");
  Serial.println(address);
}

Drink getDrinkSetup(int address)
{
  Drink drink;

  EEPROM.get(address, drink);

  return drink;
}

void mix(int DelayTimeVodka, int DelayTimeCointreau, int DelayTimeCranberryJuice, int DelayTimeSprite, int DelayTimeLemonJuice, int DelayTimeSugarWater, int DelayTimeBlueCur, int DelayTimeGin)
{
  String drinkName = message.substring(5);
  String makingMessage = drinkName + " in the making";
  String doneMessage = drinkName + " done";

  Serial.println(makingMessage);
  bluetooth.println(makingMessage);

  delay(800);
  digitalWrite(Vodka, HIGH);
  delay(DelayTimeVodka);
  digitalWrite(Vodka, LOW);
  delay(TimeBetweenPours);

  digitalWrite(Cointreau, HIGH);
  delay(DelayTimeCointreau);
  digitalWrite(Cointreau, LOW);
  delay(TimeBetweenPours);

  digitalWrite(CranberryJuice, HIGH);
  delay(DelayTimeCranberryJuice);
  digitalWrite(CranberryJuice, LOW);
  delay(TimeBetweenPours);

  digitalWrite(Sprite, HIGH);
  delay(DelayTimeSprite);
  digitalWrite(Sprite, LOW);
  delay(TimeBetweenPours);

  digitalWrite(LemonJuice, HIGH);
  delay(DelayTimeLemonJuice);
  digitalWrite(LemonJuice, LOW);
  delay(TimeBetweenPours);

  digitalWrite(SugarWater, HIGH);
  delay(DelayTimeSugarWater);
  digitalWrite(SugarWater, LOW);
  delay(TimeBetweenPours);

  digitalWrite(BlueCur, HIGH);
  delay(DelayTimeBlueCur);
  digitalWrite(BlueCur, LOW);
  delay(TimeBetweenPours);

  digitalWrite(Gin, HIGH);
  delay(DelayTimeGin);
  digitalWrite(Gin, LOW);
  delay(TimeBetweenPours);

  Serial.println(doneMessage);
  bluetooth.println(doneMessage);
}
