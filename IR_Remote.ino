#include "IRremote.h"

int receiver = 11;

IRrecv irrecv(receiver);
decode_results results;

void setup()
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode");
  irrecv.enableIRIn();
}


void loop()
{
  if (irrecv.decode(&results))
  {
    translateIR();
    irrecv.resume();
  }
}

void translateIR()
{
  switch(results.value)
  {
    case 0xFF629D: Serial.println(" 2"); break;   //THE REAL 2
    case 0xFF22DD: Serial.println(" 4"); break;
    case 0xFF02FD: Serial.println(" 5"); break;
    case 0xFFC23D: Serial.println(" 6"); break;
    case 0xFFA857: Serial.println(" 8"); break;
    case 0xFF42BD: Serial.println(" REVERSE"); break;   //NOT REAL 1
    case 0xFF9867: Serial.println(" 0"); break;
    case 0xFFB04F: Serial.println(" #"); break;
    case 0xFF30CF: Serial.println(" LEFT"); break;
    case 0xFF18E7: Serial.println(" FORWARD"); break;
    //case 0xFF7A85: Serial.println(" REVERSE"); break;   //FAKE RIGHT
    case 0xFF10EF: Serial.println(" LEFT"); break;
    case 0xFF38C7: Serial.println(" -OK-"); break;
    case 0xFF5AA5: Serial.println(" RIGHT"); break;
    //case 0xFF42BD: Serial.println(" REVERSE"); break;     //NOT REAL 1
    //case 0xFF4ABD: Serial.println(" REVERSE"); break;
    //case 0xFF52AD: Serial.println(" REVERSE"); break;       //NOT REAL 3
    case 0xFFFFFFFF: Serial.println(" REPEAT"); break;




    case 0xFFA25D: Serial.println(" 1"); break;
    case 0xFFE21D: Serial.println(" 3"); break;
    case 0xFFE01F: Serial.println(" 7"); break;
    case 0xFF906F: Serial.println(" 9"); break;
    case 0xFF6897: Serial.println(" *"); break;
    case 0xFF4AB5: Serial.println(" REVERSE"); break;

    default:
      Serial.println(" other number ");

    }

    delay(300);
    
}

