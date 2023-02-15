//3.402823466e+38F FLT_MAX
#define MAXFLT 1000000

#include <float.h>

const short PinVa = A0;
const float R1 = 5.f;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  const int VaRead = analogRead(PinVa);

  for(size_t i = 0;i<10;++i)
  {
    const float Rsensor = (1023!=VaRead) ? R1*static_cast<float>(VaRead/(1023.f-VaRead)) : MAXFLT;
    Serial.println(Rsensor);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
