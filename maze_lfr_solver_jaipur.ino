//1st ldr is left....2nd for front ldr.....3rd for right ldr
//0 for white,1 for black
//3,6 are for left motor....9,11 are for right motor
////long distance, timeTaken;
////int trigPin = 2; // trigger pin is for output....we r sending waves from here
////int echoPin = 3; // echo pin is for input....we r receiving waves here

int i, j;
int A[3] = {0, 0, 0};
int Avg[3];
int Pin[3] = {A0, A1, A2};//pin[0] for left ldr...so pin[0]=A7.....front ldr as 2nd at A4....right as 3rd at A[5]
int sensorMax[3] = {0, 0, 0};
int sensorMin[3] = {1023, 1023, 1023};
int sensorValue[3];
int r1 = 5, r2 = 6, l1 = 9, l2 = 11;
////int f = 0;

void sensorCalibrate()
{
  digitalWrite(13, HIGH);
  Serial.println("Calibrating....");
  for (int i = 1; i < 2000; i++)
  {
    sensorValue[0] = analogRead(Pin[0]);
    sensorValue[1] = analogRead(Pin[1]);
    sensorValue[2] = analogRead(Pin[2]);

    for (int j = 0; j < 3; j++)
    {
      if (sensorValue[j] > sensorMax[j])
        sensorMax[j] = sensorValue[j];
      if (sensorValue[j] < sensorMin[j])
        sensorMin[j] = sensorValue[j];
      //      Serial.print(sensorValue[j]);
      //      Serial.print(" ");

      delay(1);
    }
    //    Serial.println(" ");
    //if delay is not written then due to high speed of microcontroller it will skip/oerwrite some of the values
  }
  for (int j = 0; j < 3; j++)
  {
    Avg[j] = (sensorMax[j] + sensorMin[j]) / 2;
    Serial.print(Avg[j]);
    Serial.print("  ");
  }

  digitalWrite(13, LOW);
}

void straight()
{
  analogWrite(r1, 143);
  analogWrite(r2, 0);
  analogWrite(l1, 142);
  analogWrite(l2, 0);
}
void ninetyleft()
{
  analogWrite(r1, 80);
  analogWrite(r2, 0);
  analogWrite(l1, 0);
  analogWrite(l2, 100);
}


void ninetyright()
{
  analogWrite(r1, 0);
  analogWrite(r2, 80);
  analogWrite(l1, 180);
  analogWrite(l2, 0);
}

void backright()
{
  analogWrite(r1, 0);
  analogWrite(r2, 60);
  analogWrite(l1, 150);
  analogWrite(l2, 0);
}


void backleft()
{
  analogWrite(r1, 150);
  analogWrite(r2, 0);
  analogWrite(l1, 0);
  analogWrite(l2, 60);
}


void curveright()
{
  analogWrite(r1, 60);
  analogWrite(r2, 0);
  analogWrite(l1, 90);
  analogWrite(l2, 0);
}


void curveleft()
{
  analogWrite(r1, 90);
  analogWrite(r2, 0);
  analogWrite(l1, 60);
  analogWrite(l2, 0);
}

void deadend()
{
  analogWrite(r1, 0);
  analogWrite(r2, 180);
  analogWrite(l1, 180);
  analogWrite(l2, 0);
}

void stopping()
{
  analogWrite(r1, 0);
  analogWrite(r2, 0);
  analogWrite(l1, 0);
  analogWrite(l2, 0);
}



void setup()
{
  Serial.begin(9600); // put your setup code here, to run once:
  pinMode(Pin[0], INPUT);
  pinMode(Pin[1], INPUT);
  pinMode(Pin[2], INPUT);

  // pinMode(A6, INPUT);

  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(13, OUTPUT);
  sensorCalibrate();
  ////  pinMode(trigPin, OUTPUT);
  ////  pinMode(echoPin, INPUT);

}
int count = 0;
void loop()
{
  //int x = analogRead(A6);
  A[0] = analogRead(Pin[0]);
  A[1] = analogRead(Pin[1]);
  A[2] = analogRead(Pin[2]);


  for (i = 0; i < 3; i++)
  {
    if (A[i] < Avg[i])
      A[i] = 1;//black
    else
      A[i] = 0;//white
  }

  for (i = 0; i < 3; i++)
  {
    Serial.print(A[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  if (A[0] == 1 && A[1] == 0 && A[2] == 1)
  {
    digitalWrite(2,LOW);
    straight();
  }
  else if (A[0] == 1 && A[1] == 1 && A[2] == 0) //90 right or right wobble
    backright();

  else if (A[0] == 0 && A[1] == 1 && A[2] == 1) //90 left or right wobble
    backleft();

  else if (A[0] == 0 && A[1] == 1 && A[2] == 0) //T-Ponit and Y-shape
    backleft();

  else if (A[0] == 0 && A[1] == 0 && A[2] == 0) //plus point
  {
    digitalWrite(2, HIGH); 
    backleft();
  }
  else if (A[0] == 1 && A[1] == 0 && A[2] == 0) //right T or right angular curve
  {
    straight();
  }
  else if (A[0] == 0 && A[1] == 0 && A[2] == 1) //left T or left angular curve
  {
    backleft();
  }
  else// if (A[0] == 1 && A[1] == 1 && A[2] == 1) //black to 180 degree....dead end
  {
    do
    {
      deadend();
    } while (A[0] == 1 && A[1] == 0 && A[2] == 1);
  }

}
////}
