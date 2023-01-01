const int BUSSER_PIN = 23;
void BUSSER_setup()
{
  pinMode(BUSSER_PIN, OUTPUT);
}
void BUSSER_output(int frequency)
{
  if (frequency == 0)
  {
    noTone(BUSSER_PIN);
  }
  else
  {
    tone(BUSSER_PIN, frequency);
  }
}

int scaleFrequency(float x0)
{
  int min = /**1500**/ 100;
  int max = /**2000**/ 3500;
  float y = 1900.0 * x0 / (min-max) + 100.0 - 1900.0 * max / (min-max);
  return (int)y;
}

/** --------------------------- main ------------------------ */
void setup()
{
  Serial.begin(115200);
  BUSSER_setup();
}

void Buss(int d)
{
  BUSSER_output(3000 - d);
  delay(0.1 * d);
  BUSSER_output(0);
}

int power = 0;

void loop()
{
  int button = analogRead(A3);
  if (button > 1000)
  {
    if (power == 0) power = 1;
    else power = 0;
  }
  if (power == 0) {
    delay(200);
    return;  
  }    
  int volt = analogRead(A0);
  int d = scaleFrequency(volt);
  delay(100);
  Serial.print("Smell is ");
  if (volt >= 3000)
  {
    Serial.print("stincky!! ");
    d = scaleFrequency(1500);
    delay(500);
  }
  if (volt <= 100)
  {
    Serial.print("nice - ");
    delay(150);
  }
  Serial.print(volt);
  Serial.print("<- This is strength of smell");
  Serial.println();
  Serial.print(d);
  Serial.print("   ");
  Buss(d);
}
