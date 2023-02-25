//3.402823466e+38F FLT_MAX
#define MAXFLT 1000000

#define PinVa A0
#define R1 5.f

//class responsible for serial monitor printing and time delaying
//i.e communication with PC
class PCCommunication
{
public:
  PCCommunication()
  :timer(0), delayMicro(5000)
  {
    
  }
  ~PCCommunication()
  {
    
  }
  void printLine(const float* val);
  void timeDelay();
private:
  unsigned long timer;
  const unsigned long delayMicro;
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  //create global PCCommunication object
  static PCCommunication PCCom1 = PCCommunication();

  //delay time 5 milliseconds
  PCCom1.timeDelay();

  //read voltage and shift the value to resistance
  const int VaRead = analogRead(PinVa);
  const float Rsensor = (1023!=VaRead) ? R1*static_cast<float>(VaRead/(1023.f-VaRead)) : MAXFLT;

  //print the Rsensor value in serial monitor for PC communication
  PCCom1.printLine(&Rsensor);
}

void PCCommunication::timeDelay()
{
  unsigned long Timepassed = micros();
  long TimetoDelay = this->delayMicro - (Timepassed - this->timer);

  if(TimetoDelay > 1001)
  {
    delay(TimetoDelay / 1000);
    delayMicroseconds(TimetoDelay % 1000); //delayMicroseconds() can delay until 16383 microseconds
  }
  else if(TimetoDelay > 0)
  {
    delayMicroseconds(TimetoDelay);
  }

  this->timer = Timepassed + TimetoDelay;
}

void PCCommunication::printLine(const float* val)
{
  const byte* byteVal = reinterpret_cast<const byte*>(val);
  Serial.write(byteVal, 4);
}
