// defining the pins used for each drink, you can changes this depending how you connect the pumps and the drinks.
int Vodka = 2;
int Cointreau = 3;
int CranberryJuice = 4;
int Sprite = 5;
int LemonJuice = 6;
int SugarWater = 7;
int BlueCur = 8;
int Gin = 9;

int state = 0;

// how much time there is between switching to the next pump.
int TimeBetweenPours = 500;

void setup()
{
  Serial.begin(9600);
  Serial.println("The bluetooth gates are open.\n Connect to HC-05 from any other bluetooth device with 1234 as pairing key!");

  // Set pin 2-9 to output pins to drive the relay board
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  // My relayboard is a "low true" board. So setting the output to low energize the relay's. You don't want that they all switch on when powering on the cocktailmaker...
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
}

void loop()

{
  if (Serial.available() > 0)
  {                        // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
    Serial.println(state);
  }

  // Cocktails:

  // Vodka sprite
  if (state == 'a')
  {
    Serial.println("Vodka Sprite in the making");
    Mix(3000, 0, 0, 0, 5000, 0, 0, 0); // Vodka, Sprite, Lime juice
  }

  // Blue Lagoon
  if (state == 'b')
  {
    Serial.println("Blue Lagoon in the making");
    Mix(2000, 0, 0, 5000, 1800, 1000, 1800, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Cosmo
  if (state == 'c')
  {
    Serial.println("Cosmo in the making");
    Mix(2500, 1500, 3800, 0, 1200, 1200, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Lemon drop
  if (state == 'd')
  {
    Serial.println("Lemon drop in the making");
    Mix(1500, 1500, 0, 0, 1800, 1200, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Blue Moon
  if (state == 'e')
  {
    Serial.println("Blue Moon in the making");
    Mix(2000, 0, 3000, 0, 1800, 1200, 1200, 0); // Vodka, Cranberry juice, Lime juice, Sugar water, Blue Curacao
  }

  // Blue Gin Moon
  if (state == 'f')
  {
    Serial.println("Blue Gin Moon in the making");
    Mix(0, 0, 3000, 0, 1800, 1200, 1200, 2000); // Cranberry juice, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Double Strike
  if (state == 'i')
  {
    Serial.println("Double Strike in the making");
    Mix(2000, 0, 3000, 0, 1800, 0, 1200, 0); // Vodka, Cranberry juice, Lime juice, Blue Curacao
  }

  // Tom Collins
  if (state == 'h')
  {
    Serial.println("Tom Collins in the making");
    Mix(0, 0, 0, 4000, 1800, 1800, 0, 2200); // Sprite, Lime juice, Sugar water, Gin
  }

  // Flying Dutchman
  if (state == 'g')
  {
    Serial.println("Flying Dutchman in the making");
    Mix(0, 2000, 0, 0, 1200, 1000, 0, 2000); // Triple Sec, Lime juice, Sugar water, Gin
  }

  // London Cosmo
  if (state == 'j')
  {
    Serial.println("London Cosmo in the making");
    Mix(0, 2000, 5000, 1800, 0, 0, 0, 2000); // Triple Sec, Cranberry juice, Sprite, Gin
  }

  // Vodka Cranberry
  if (state == 'k')
  {
    Serial.println("Vodka Cranberry in the making");
    Mix(2000, 0, 5000, 0, 0, 1200, 0, 0); // Vodka, Cranberry juice, Sugar water
  }

  // Cranberry Gin
  if (state == 'l')
  {
    Serial.println("Cranberry Gin in the making");
    Mix(0, 0, 5000, 0, 2000, 0, 0, 2200); // Cranberry juice, Lime juice, Gin
  }

  // Testin and maintenance options

  // Set-up Vodka
  if (state == 'm')
  {
    Serial.println("Set-up Vodka");
    Mix(1100, 0, 0, 0, 0, 0, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Tripple Sec
  if (state == 'n')
  {
    Serial.println("Set-up Tripple Sec");
    Mix(0, 1100, 0, 0, 0, 0, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Cranberry juice
  if (state == 'o')
  {
    Serial.println("Set-up Cranberry juice");
    Mix(0, 0, 1000, 0, 0, 0, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Sprite
  if (state == 'p')
  {
    Serial.println("Set-up Sprite");
    Mix(0, 0, 0, 1000, 0, 0, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Lime juice
  if (state == 'q')
  {
    Serial.println("Set-up Lime juice");
    Mix(0, 0, 0, 0, 1100, 0, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Sugar water
  if (state == 'v')
  {
    Serial.println("Set-up Sugar water");
    Mix(0, 0, 0, 0, 0, 1200, 0, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Blue curacao
  if (state == 'r')
  {
    Serial.println("Set-up Blue curacao");
    Mix(0, 0, 0, 0, 0, 0, 800, 0); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up Gin
  if (state == 's')
  {
    Serial.println("Set-up Gin");
    Mix(0, 0, 0, 0, 0, 0, 0, 1000); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Cleaning
  if (state == 't')
  {
    Serial.println("Set-up Gin");
    Mix(4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }

  // Set-up all (intial first time after cleaning)
  if (state == 'u')
  {
    Serial.println("Set-up All");
    Mix(800, 800, 800, 800, 1000, 1600, 800, 800); // Vodka, Triple Sec, Cranberry juice, Sprite, Lime juice, Sugar water, Blue Curacao, Gin
  }
}

void Mix(int DelayTimeVodka, int DelayTimeCointreau, int DelayTimeCranberryJuice, int DelayTimeSprite, int DelayTimeLemonJuice, int DelayTimeSugarWater, int DelayTimeBlueCur, int DelayTimeGin)
{

  state = 0;
  delay(800);
  digitalWrite(Vodka, LOW);
  delay(DelayTimeVodka);
  digitalWrite(Vodka, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(Cointreau, LOW);
  delay(DelayTimeCointreau);
  digitalWrite(Cointreau, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(CranberryJuice, LOW);
  delay(DelayTimeCranberryJuice);
  digitalWrite(CranberryJuice, HIGH);
  delay(TimeBetweenPours);

  digitalWrite(Sprite, LOW);
  delay(DelayTimeSprite);
  digitalWrite(Sprite, HIGH);
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

  Serial.println("Drink is done!");
  state = 0;
}