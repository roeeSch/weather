#include "getHttpData.h"

float temps[30];

void setup() {
  Serial.begin(115200);
  delay(10);
  setup_wifi();
  // put your setup code here, to run once:

}

void loop() {
  int nTemps = 0;
  // put your main code here, to run repeatedly:
  delay(5000);
  nTemps = get_tempArray(temps);

  Serial.print("num of elements read = "); Serial.println(nTemps);

  for (int i=0; i< nTemps; i++){
      Serial.println(temps[i]);
    }

}
