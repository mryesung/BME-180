//3.402823466e+38F FLT_MAX
#define MAXFLT 1000000

#define PinVa A0
#define R1 5.f

#include <float.h>

void setup() {
  Serial.begin(9600);
}

void loop() {
  //wait until python script requires to read the voltage
  if(Serial.available() > 0)
  {
    if(Serial.read() == 'w')
    {
      const int VaRead = analogRead(PinVa);

      const float Rsensor = (1023!=VaRead) ? R1*static_cast<float>(VaRead/(1023.f-VaRead)) : MAXFLT;
  
      Serial.println(Rsensor);
    }
  }
}
