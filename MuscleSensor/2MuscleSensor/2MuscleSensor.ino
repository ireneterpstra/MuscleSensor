int analogPin = A5;
int analogPin2 = A4;


uint16_t counter = 0; 

double val = 0;
double val2 = 0;
double last = 0;
double avgVol = 0;
double avgBump = 0;

double minVal = 0;
double lastMin = 0;
double avgMin = 0;
double avgMinBump = 0;

double maxVal = 0;
double lastMax = 0;
double avgMax = 0;
double avgMaxBump = 0;


boolean bump = false;



void setup()
{
  Serial.begin(9600);              //  setup serial
}

void loop(){
  val = analogRead(analogPin);     // read the input pin
  val2 = analogRead(analogPin2);     // read the input pin

  avgVol = (avgVol*.95 + val*.05);
  avgMin = (avgMin*.95 + minVal*.05);
  avgMax = (avgMax*.95 + maxVal*.05);

  if (val > maxVal) {
    maxVal = val;
  }
  if (val < minVal){
    minVal = val;
  }

  if (val - last > avgVol - last && avgVol - last > 0){
    avgBump = (avgBump + (val - last)) / 2.0;
  }

  if (maxVal - lastMax > avgMax - lastMax && avgMax - lastMax > 0){
    avgMaxBump = avgMaxBump*.95 + (maxVal - lastMax)*.05;
  }

  
  maxVal = maxVal*.95 + val*.05;
  minVal = minVal*.95 + val*.05;

  //bump = (val - last) > (avgBump + 10) || (val - last) < (avgBumpU + 10);

  if (bump){
    bump = false;
  } else{
    bump = (maxVal - lastMax) > avgMaxBump + 5;
  }


  if (counter < 5) {
    minVal = val;
    maxVal = val;
  } 
//  else if (counter < 10){
//    
//  }

  counter++;

  if(bump){
    Serial.println("Bump");
  }

  
//  Serial.print(maxVal - lastMax);
//  Serial.print(" ");
//  Serial.println(avgMaxBump + 5);
//  Serial.print(" ");
  Serial.print(val);
  Serial.print(" ");
  Serial.println(val2);
//  Serial.print(" ");
//  Serial.println(maxVal);
}

