// Temperature sensing using LM35 sensor without using delay(),milli() or macros()

#define tempSensor A0 // temperature sensor output is connected to A0 pin of arduino

void Delay_250(); // function declaration
void Delay_500(); // function declaration

float tempC;  // variable to store temperature in degree celsius
float vout;   // variable to store temporary output voltage of lm35 sensor

void setup() {
  Serial.begin(9600);         // baut rate is to communication between serial monitor and arduino
  pinMode(tempSensor,INPUT);  // tempSensor used as INPUT to take input from sensor
  pinMode(LED_BUILTIN,OUTPUT); // LED_BUILTIN is used to blink on board led and used as output 

}
void loop() {
  
  vout = analogRead(tempSensor);   // it maps the input voltage of sensor in between 0 to 1023
  vout = vout * (5000/1024);      // this convert number 0-1023 from ADC into 0-5v
  tempC = vout / 10;              //convert into degree celsius
  Serial.print("\nTemperature : "); 
  Serial.print("\t");
  Serial.print(tempC);               // printing temperature on serial monitor
  Serial.print("  degree celsius\n"); 
  if(tempC <= 30)                     // if temperature less than or equal to 30 degree celsius then blink led at 250 milli seconds
  {
    Serial.println("less than 30 degree");
    digitalWrite(LED_BUILTIN,HIGH);   // on board led ON
    Delay_250();                      // custom delay funcion called for 250 milli seconds
    digitalWrite(LED_BUILTIN,LOW);    // on board led OFF
    Delay_250();
  }
  else if(tempC > 30)               // if temperature greater than 30 degree celsius then blink led at 500 milli seconds
  {
    Serial.println("greater than 30");
    digitalWrite(LED_BUILTIN,HIGH);   // on board led ON
    Delay_500();                     // custom delay funcion called for 250 milli seconds
    digitalWrite(LED_BUILTIN,LOW);   // on board led OFF
    Delay_500();   
  }
  else                               // if above two conditions false
  {
    digitalWrite(LED_BUILTIN,LOW);   // on board led OFF
  }

}

//clockCyclesPerMicrosecond() return number of cycles per microseconds, here 16 for 16 MHz

void Delay_250()                
{
  uint32_t cycles = clockCyclesPerMicrosecond()*25000/4; // multiply by  25000 to get number of cycles for 250 milliseconds. divide by 4 because each loop iteration takes 4 cycles
  
  volatile uint32_t i;     // volatile variable to prevent compiler optimization 
  for(i=0; i<cycles; i++)  //loop until the cycles are consumed
  {
    //do nothing
  }
}
void Delay_500()
{
  uint32_t cycles = clockCyclesPerMicrosecond()*50000/4; // multiply by  25000 to get number of cycles for 250 milliseconds
  
  volatile uint32_t i;
  for(i=0; i<cycles; i++)
  {
    //do nothing
  }

}