#include <SoftwareSerial.h>
#include <EEPROM.h>

const int pinoRX = 0; // PINO DIGITAL (RX)
const int pinoTX = 1; // PINO DIGITAL (TX)

int Vodka = 2;
int CranberryJuice = 3;
int LemonJuice = 4;
int SugarWater = 5;
int BlueCur = 6;
int Gin = 7;
int Mixer = 8;
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

  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
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

      if (sendInitialSetup())
        ;
      else if (setupDrinks())
        ;
      else if (makeDrink())
        ;
      else if (makeYourOwnDrink())
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
  if (message.equals("Make Caipirinha"))
  {
    mix(5000, 0, 10000, 0, 0, 0);
    return true;
  }
  else if (message.equals("Make Blue Lagoon"))
  {
    mix(5000, 0, 10000, 0, 2500, 0);
    return true;
  }
  else if (message.equals("Make Cosmo"))
  {
    mix(4000, 3000, 1500, 0, 0, 0);
    return true;
  }
  else if (message.equals("Make Lemon Drop"))
  {
    mix(5000, 0, 3000, 3000, 0, 0);
    return true;
  }
  else if (message.equals("Make Blue Moon"))
  {
    mix(3000, 5000, 3000, 2000, 2000, 0);
    return true;
  }
  else if (message.equals("Make Blue Gin Moon"))
  {
    mix(0, 5000, 3000, 2000, 2000, 3000);
    return true;
  }
  else if (message.equals("Make Double Strike"))
  {
    mix(3000, 5000, 3000, 0, 2000, 0);
    return true;
  }
  else if (message.equals("Make Tom Collins"))
  {
    mix(0, 0, 3000, 1500, 0, 3000);
    return true;
  }
  else if (message.equals("Make Flying Dutchman"))
  {
    mix(0, 0, 2000, 1500, 0, 3000);
    return true;
  }
  else if (message.equals("Make London Cosmo"))
  {
    mix(0, 8000, 0, 0, 0, 3000);
    return true;
  }
  else if (message.equals("Make Vodka Cranberry"))
  {
    mix(3000, 8000, 0, 2000, 0, 0);
    return true;
  }
  else if (message.equals("Make Cranberry Gin"))
  {
    mix(0, 8000, 3000, 0, 0, 3500);
    return true;
  }

  return false;
}

boolean makeYourOwnDrink()
{
  String msg = message.substring(0, 16);
  if (msg.equals("MakeYourOwnDrink"))
  {
    int delayTimes[6];
    for (int i = 1; i < 7; i++)
    {
      String quantity = getValue(message, ':', i);

      if (quantity.length() > 0)
      {
        int quantityInt = quantity.toInt();
        delayTimes[i - 1] = quantityInt * 100;
      }
      else
        delayTimes[i - 1] = 0;
    }

    mix(delayTimes[0], delayTimes[1], delayTimes[2], delayTimes[3], delayTimes[4], delayTimes[5]);

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

    String initialSetup = "InitialSetup";
    String separator = ":";
    String initialDrinksSetup = initialSetup + separator +
                                drinkOne.name + separator +
                                drinkOne.quantity + separator +
                                drinkTwo.name + separator +
                                drinkTwo.quantity + separator +
                                drinkThree.name + separator +
                                drinkThree.quantity + separator +
                                drinkFour.name + separator +
                                drinkFour.quantity + separator +
                                drinkFive.name + separator +
                                drinkFive.quantity + separator +
                                drinkSix.name + separator +
                                drinkSix.quantity;

    Serial.println(initialDrinksSetup);
    bluetooth.println(initialDrinksSetup);

    return true;
  }

  return false;
}

boolean setupDrinks()
{
  String msg = message.substring(0, 10);
  if (msg.equals("DrinkSetup"))
  {
    int addressList[6] = {
        drinkOneAddress,
        drinkTwoAddress,
        drinkThreeAddress,
        drinkFourAddress,
        drinkFiveAddress,
        drinkSixAddress};
    for (int i = 1, j = 0; i < 13; i += 2, j++)
    {
      String drinkName = getValue(message, ':', i);
      String drinkQuantityString = getValue(message, ':', i + 1);

      int quantityDrink = drinkQuantityString.toInt();

      if (drinkName.length() > 0 && quantityDrink > 0)
        saveDrinkSetup(drinkName, quantityDrink, addressList[j]);
    }

    Serial.println("DrinksUpdatedSuccessfully");
    bluetooth.println("DrinksUpdatedSuccessfully");

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

void updateDrinkQuantity(int delayTime, int address)
{
  Drink drink = getDrinkSetup(address);
  drink.quantity -= delayTime / 100;

  saveDrinkSetup(drink.name, drink.quantity, address);
}

// 1000ms == 10ml
void mix(int DelayTimeVodka, int DelayTimeCranberryJuice, int DelayTimeLemonJuice, int DelayTimeSugarWater, int DelayTimeBlueCur, int DelayTimeGin)
{
  String drinkName = message.substring(0, 5);
  String makingMessage = drinkName + " in the making";
  String doneMessage = drinkName + " done";

  Serial.println(makingMessage);
  bluetooth.println(makingMessage);

  delay(800);
  digitalWrite(Vodka, LOW);
  delay(DelayTimeVodka);
  digitalWrite(Vodka, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(CranberryJuice, LOW);
  delay(DelayTimeCranberryJuice);
  digitalWrite(CranberryJuice, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(LemonJuice, LOW);
  delay(DelayTimeLemonJuice);
  digitalWrite(LemonJuice, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(SugarWater, LOW);
  delay(DelayTimeSugarWater);
  digitalWrite(SugarWater, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(BlueCur, LOW);
  delay(DelayTimeBlueCur);
  digitalWrite(BlueCur, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(Gin, LOW);
  delay(DelayTimeGin);
  digitalWrite(Gin, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(Mixer, LOW);
  delay(5000);
  digitalWrite(Mixer, HIGH);
  delay(TimeBetweenPours);

  Serial.println(doneMessage);
  bluetooth.println(doneMessage);

  if (DelayTimeVodka > 0)
    updateDrinkQuantity(DelayTimeVodka, drinkOneAddress);
  if (DelayTimeCranberryJuice > 0)
    updateDrinkQuantity(DelayTimeCranberryJuice, drinkTwoAddress);
  if (DelayTimeLemonJuice > 0)
    updateDrinkQuantity(DelayTimeLemonJuice, drinkThreeAddress);
  if (DelayTimeSugarWater > 0)
    updateDrinkQuantity(DelayTimeSugarWater, drinkFourAddress);
  if (DelayTimeBlueCur > 0)
    updateDrinkQuantity(DelayTimeBlueCur, drinkFiveAddress);
  if (DelayTimeGin > 0)
    updateDrinkQuantity(DelayTimeGin, drinkSixAddress);
}
