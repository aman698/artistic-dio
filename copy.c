#include "config.h"

unsigned long time2;
float distanceK = 600;
float distanceU = 0;
float speedVeh = 0;
int loopAc = 0;
unsigned int axil1 = 0;
unsigned int axil2 = 0;
unsigned int Prev_axil1 = 0;
unsigned int Prev_axil2 = 0;

int prev = 1;
int hit = 0;

int hardrst = 13;

String incom = "";

int lanid = 0;
long   EmbeddedSeqN = 0;

String AVCNE = "START,AVCC,";
String AliveN = "START,ALIVE,";

int forward = 0;
int height = 0;

String readString;


int loopact = 0;
int t1po = 0;
int t2po = 0;
unsigned long t1 = 0;
unsigned long t2 = 0;
float velocity;

int h1 = 0;
int h2 = 0;
int h3 = 0;
int h4 = 0;

String getMessageUART();

int parseCommand(String str);
void updateRelayState(int relay, int state);
void printAlive();

void avcc() {
  if (loopAc == 1) {
    if (digitalRead(DI2) == 1) {

      if (prev == 0) {
        prev = 1;
        prev = digitalRead(DI2);
        hit++;
        if (hit == 1) {
          time1 = millis();
        }
        if (hit == 2) {
          time2 = millis();
        }
      }
    } else {
      prev = 0;
    }
  }

  if (digitalRead(DI1) == 1) {
    loopAc = 1;
    if (loopact == 0)
    {
      loopact = 1;
    }
    if (digitalRead(DI4) == 1) {
      h1 = 1;
    }

    h2 = 0;
    h3 = 0;
    h4 = 0;
    height = h1;

    if (digitalRead(DI1) == 1) { //edited DI2
      if (t1po == 0) {
        t1po = 1;
        t1 = millis();
      }
      if (Prev_axil1 == 0) {
        Prev_axil1 = 1;
        axil1 = axil1 + 1;
      }
    } else {
      Prev_axil1 = 0;
    }
    if (digitalRead(DI3) == 1) {
      if (t2po == 0) {
        t2po = 1;
        t2 = millis();
      }
      if (Prev_axil2 == 0) {
        Prev_axil2 = 1;
        axil2 = axil2 + 1;
      }
    }
    else {
      Prev_axil2 = 0;
    }
  } else {
    if (loopAc == 1) {
      hit = hit * 2;
      loopAc = 0;
      t2po = 0;
      t1po = 0;
      if (t2 < t1) {
        velocity = t1 - t2;
        velocity = velocity / 1000;       //convert millisecond to second
        velocity = (0.75 / velocity) * 3.6; // km/s//0.2 meters ||-----||
        //distanceU=(speedVeh*(time3-time1));
      } else {
        velocity = t2 - t1;
        velocity = velocity / 1000;       //convert millisecond to second
        velocity = (0.75 / velocity) * 3.6; // km/s//0.2 meters ||-----||
      }

      //Serial.println(velocity);

      if (t1 < time2) {
        forward = 1;
        float diff = (float)time2 - (float)t1;
        speedVeh = (float)distanceK / (float)diff;
        distanceU = (velocity * (time2 - t1)) / 10;
      } else {
        forward = 0;
        float diff = (float)t1 - (float)time2;
        speedVeh = (float)distanceK / (float)diff;
        distanceU = (velocity * (t1 - time2)) / 10;
      }
      //checked till here
      

      indexlen = 11;
      loopact = 0;

      AVCNE = AVCNE + "0,";
      AVCNE = AVCNE + String(lanid) + ",";
      AVCNE = AVCNE + String(EmbeddedSeqN) + ",";
      if (distanceU <= 2700 && distanceU >= 1200 && ((hit) / 2) <= 2) {
        if (height >= 2) {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,LCV," + stry + "," + fv + ",";

        } else {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,CAR," + stry + "," + fv + ",";
        }

      } else if (distanceU <= 3500 && distanceU >= 2700 && ((hit) / 2) <= 2) {
        if (height == 1)
        {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,CAR," + stry + "," + fv + ",";

        } else {

          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "2,LCV," + stry + "," + fv + ",";

        }
      } else if (distanceU <= 7500 && distanceU >= 3500 && ((hit) / 2) <= 2) {
        String stry = String(((hit) / 2));
        String fv = (forward == 1) ? "F" : "R";
        AVCNE = AVCNE + "3,TRUCK," + stry + "," + fv + ",";

      } else if (((hit) / 2) == 3) {
        if (height <= 1) {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,CAR," + stry + "," + fv + ",";
        } else {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "5,MAV," + stry + "," + fv + ",";
        }
      } else if (((hit) / 2) == 4) {
        if (height <= 1) {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,CAR," + stry + "," + fv + ",";
        } else {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "6,MAV," + stry + "," + fv + ",";
        }
      } else if (((hit) / 2) == 5) {
        if (height <= 1) {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,CAR," + stry + "," + fv + ",";
        } else {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "6,MAV," + stry + "," + fv + ",";
        }

      } else if (((hit) / 2) == 6) {
        if (height <= 1) {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "1,CAR," + stry + "," + fv + ",";
        } else {
          String stry = String(((hit) / 2));
          String fv = (forward == 1) ? "F" : "R";
          AVCNE = AVCNE + "6,MAV," + stry + "," + fv + ",";
        }

      } else if (((hit) / 2) == 7) {
        String stry = String(((hit) / 2));
        String fv = (forward == 1) ? "F" : "R";
        AVCNE = AVCNE + "7,MAV," + stry + "," + fv + ",";

      } else if (((hit) / 2) == 8) {
        String stry = String(((hit) / 2));
        String fv = (forward == 1) ? "F" : "R";
        AVCNE = AVCNE + "8,MAV," + stry + "," + fv + ",";

      } else if (((hit) / 2) >= 9 && ((hit) / 2) <= 10) {
        String stry = String(((hit) / 2));
        String fv = (forward == 1) ? "F" : "R";
        AVCNE = AVCNE + "9,MAV," + stry + "," + fv + ",";

      } else {
        String stry = String(((hit) / 2));
        String fv = (forward == 1) ? "F" : "R";
        AVCNE = AVCNE + "0,III," + stry + "," + fv + ",";


      }

      AVCNE = AVCNE + String(distanceU) + ",";

      if (height == 1) {
        AVCNE = AVCNE + "050" + ",";
        String speeder = String(velocity);
        AVCNE = AVCNE + speeder + "," + "1,0,0,0" + ",";
      }
      if (height == 2) {
        AVCNE = AVCNE + "100" + ",";
        String speeder = String(velocity);
        AVCNE = AVCNE + speeder + "," + "1,1,0,0" + ",";
      }
      if (height == 3) {
        AVCNE = AVCNE + "150" + ",";
        String speeder = String(velocity);
        AVCNE = AVCNE + speeder + "," + "1,1,1,0" + ",";
      }
      if (height == 4) {
        AVCNE = AVCNE + "200" + ",";

        String speeder = String(velocity);
        AVCNE = AVCNE + speeder + "," + "1,1,1,1" + ",";

      }
      if (height == 0) {
        AVCNE = AVCNE + "0" + ",";
        String speeder = String(velocity);
        AVCNE = AVCNE + speeder + "," + "0,0,0,0" + ",";

      }
      AVCNE = AVCNE + "END";

      SerialInterface.println(AVCNE);
      //newLineWrt(AVCNE);
      EmbeddedSeqN++;

      AVCNE = "START,AVCC,";
      hit = 0;
      hit2 = 0;
      hit3 = 0;
      axil1 = 0;

      height = 0;
      h1 = 0;
      h2 = 0;
      h3 = 0;
      h4 = 0;
      t1 = 0;
      t2 = 0;
    }
    time1 = 0;
    time2 = 0;
    time3 = 0;
    distanceU = 0;
    speedVeh = 0;
    loopAc = 0;
    axil1 = 0;
    axil2 = 0;
    Prev_loopAc = 0;
    Prev_axil1 = 0;
    Prev_axil2 = 0;
    hit = 0;
  }
}

String getMessageUART() {
  String str = "";
  while (SerialInterface.available()) {
    char ch = SerialInterface.read();
    if (ch == '\n') {
      break;
    }
    if (ch != '\r') {
      str += ch;
    }
  }
  return str;
}
int parseCommand(String str)
{
    if (str == "")
        return -1;

    int commaIndex = str.indexOf(',');

    if (commaIndex < 0)
        return -1;

    String cmd   = str.substring(0, commaIndex);
    String value = str.substring(commaIndex + 1);

    if (cmd == "R1") {
        updateRelayState(RELAY1, value.toInt());
    }
    else if (cmd == "R2") {
        updateRelayState(RELAY2, value.toInt());
    }
    else if (cmd == "R3") {
        updateRelayState(RELAY3, value.toInt());
    }
    else if (cmd == "R4") {
        updateRelayState(RELAY4, value.toInt());
    }
    else if (cmd == "R5") {
        updateRelayState(RELAY5, value.toInt());
    }
    else if (cmd == "R6") {
        updateRelayState(RELAY6, value.toInt());
    }

    return 0;
}

void updateRelayState(int relay, int state) {
  digitalWrite(relay, state);
}

void printAlive() {
  delay(50);

  AliveN = AliveN + ((digitalRead(DI1) == 1) ? '1' : '0');
  AliveN = AliveN + ((digitalRead(DI2) == 1) ? '1' : '0');
  AliveN = AliveN + ((digitalRead(DI3) == 1) ? '1' : '0');
  AliveN = AliveN + ((digitalRead(DI4) == 1) ? '1' : '0');

  AliveN = AliveN + ",";
  AliveN = AliveN + "E";
  AliveN = AliveN + "N";
  AliveN = AliveN + "D";
  AliveN = AliveN + "\0";

  SerialInterface.println(AliveN);
  AliveN = "START,ALIVE,";
}

void setup() {
  SerialInterface.begin(SERIAL_BAUDRATE);
  SerialInterface.println("SETUP");

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);

  pinMode(DI1, INPUT_PULLDOWN);
  pinMode(DI2, INPUT_PULLDOWN);
  pinMode(DI3, INPUT_PULLDOWN);
  pinMode(DI4, INPUT_PULLDOWN);

  pinMode(HARDRST, INPUT_PULLUP);

  lanid = 125;

  updateRelayState(RELAY1, HIGH);
  updateRelayState(RELAY2, HIGH);
  updateRelayState(RELAY3, HIGH);
  updateRelayState(RELAY4, HIGH);
  updateRelayState(RELAY5, HIGH);
  updateRelayState(RELAY6, HIGH);
}

void loop() {
  String str = getMessageUART();
  parseCommand(str);
  printAlive();
  avcc();
}
