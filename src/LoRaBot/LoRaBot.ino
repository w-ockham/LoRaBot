/*
 * LoRa Automatic Responder
 * 
 * by JL1NIE 2019/12/24
 */
 #include <SPI.h>
 #include <LoRa.h>

const int csPin = 8;         // LoRa radio chip select.
const int resetPin = 4;      // LoRa radio reset
const int irqPin = 7;        // LoRa radio IRQ

const long freq_low = 438e6;
const long freq_high = 439e6;
long frequency = 438.2E6;
int power = 20;
int spreadingFactor = 10;
long bandWidthTable[] = { 7.8e3, 10.4e3, 15.6e3, 20.8e3, 31.25e3, 41.7e3, 62.5e3, 125e3, 250e3};
int bandWidth = 6;
int prlen = 8;
bool crc = false;
bool codingRate = 5;
int syncWord = 0x12;
enum {
  MODE_NORM,
  MODE_BOT,
  MODE_CONT
};
int mode = MODE_BOT;
bool remote_set = false;
bool verbose = false;

String mycall,hiscall;
String line_buffer;
String remote_command;

void Initialize_LoRaParam() {
  frequency = 438.2e6;
  if (!LoRa.begin(frequency)) {              // initialize ratio at 438.2 MHz
      Serial.println("LoRa init failed. Check your connections.");
      while (true);                       // if failed, do nothing
  }
  bandWidth = 4;
  LoRa.setSignalBandwidth(bandWidthTable[bandWidth]);     // BW = 31.25kHz
  spreadingFactor = 10;
  LoRa.setSpreadingFactor(spreadingFactor);  // SF = 10
  power = 20;
  LoRa.setTxPower(power);
  codingRate = 5;
  LoRa.setCodingRate4(codingRate);
  prlen = 8;
  LoRa.setPreambleLength(prlen);
  syncWord = 0x12;
  LoRa.setSyncWord(syncWord);
  mycall = "JL1NIE";
}

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing LoRa module");
  LoRa.setPins(csPin, resetPin, irqPin);     // set CS, reset, IRQ pin
  Initialize_LoRaParam();
  LoRa.onReceive(onReceive);
  LoRa.receive();
  Serial.println("LoRa init succeeded.");
  String f = String(frequency);
  Serial.println("Listening freq = " + f);
  Serial.print(mycall + "> ");
  line_buffer = "";
}

int split(String buf, char delim, String *dst) {
  int index = 0;
  int arySize = (sizeof(buf)/sizeof((buf)[0]));
  int len = buf.length();

  for (int i = 0; i < len; i++) {
    char tmp = buf.charAt(i);
    if (tmp == delim) {
      index++;
      if ( index > (arySize -1)) return -1;
    }
    else dst[index] += tmp;
  }
  return (index + 1);
}

void do_command(String buffer) {
  String cmds[3] = {"\0"};

  buffer.toUpperCase();
  buffer.trim();
  
  int index = split(buffer, ' ', cmds);
  if ( index == 1 ) {
    String s = String(frequency);
    Serial.println("Freq = " + s);
    s = String(spreadingFactor);
    Serial.println("SF = " + s);
    s = String(bandWidthTable[bandWidth]);
    Serial.println("BW = " + s);
    s = String(power);
    Serial.println("TX Power = " + s);
    return;
  } else if ( index != 3 ) {
    if ( cmds[1] == "INIT" ) {
      LoRa.end();
      Initialize_LoRaParam();
      return;
    } 
    Serial.println("Command error: " + buffer);
    return;
  }
  
  if ( cmds[1] == "FREQ" ) {
    int freq = cmds[2].toInt();
    if ( freq >= freq_low && freq <= freq_high ) {
      frequency = freq;
      LoRa.setFrequency(frequency);
      Serial.println("Set frequency = " + cmds[2]);
    } else {
      Serial.println("frequency error : " + cmds[2]);
    }
    return;
  }
  
  if ( cmds[1] == "PWR" ) {
    int p = cmds[2].toInt();
    if ( p >= 2 && p <= 20 ) {
      power = p;
      LoRa.setTxPower(power);
      Serial.println("Set TX power = " + cmds[2]);
    } else {
      Serial.println("TX power error = " + cmds[2]);
    }
    return;
  }
  
  if ( cmds[1] == "SF" ) {
    int sf = cmds[2].toInt();
    if ( sf >= 6 && sf <= 12 ) {
      spreadingFactor = sf;
      LoRa.setSpreadingFactor(spreadingFactor);
      Serial.println("Set Spreading Factor = " + cmds[2]);
    } else {
      Serial.println("Spreading Factor error = " + cmds[2]);
    }
    return;
  }
  
  if ( cmds[1] == "BW" ) {
    int bw = cmds[2].toInt();
    if ( bw >= 0 && bw <= 8 ) {
        bandWidth = bw;
        String bws = String(bandWidthTable[bw]);
        LoRa.setSignalBandwidth(bandWidthTable[bw]);
        Serial.println("Set BW = " + bws + "Hz");
        return;
    }
    Serial.println("BW error = " + cmds[2]);
    return;
  }
     
  if ( cmds[1] == "CALL") {
    mycall = cmds[2];
    Serial.println("Set my callsign = " + cmds[2]);
    return;
  }

  if ( cmds[1] == "MODE") {
    if ( cmds[2] == "NORM" ) {
      mode = MODE_NORM;
      Serial.println("Normal Mode");
      return;
    }
    if ( cmds[2] == "BOT" ) {
      mode = MODE_BOT;
      Serial.println("Robot Mode");
      return;
    }
    if ( cmds[2] == "CONT" ) {
      mode = MODE_CONT;
      Serial.println("Continuous Signal Output mode.");
      return;
    }
    if ( cmds[2] == "VERB" ) {
    verbose = ! verbose;
    if ( verbose )
      Serial.println("Verbose Mode");
    else
      Serial.println("Simple Mode");
    return;
    }
  }
}

void loop() {
  char c;
  if ( Serial.available() ) {
       c = Serial.read();
       if ( c == '\r' ) {
          Serial.read();// Skip LF
          if ( line_buffer.indexOf("rset") == 0){
              LoRa.beginPacket();
              LoRa.print(line_buffer);
              LoRa.endPacket();
              LoRa.receive();
              do_command(line_buffer);
          } else if ( line_buffer.indexOf("set") == 0) {
              do_command(line_buffer);
          } else {
            if ( mode == MODE_CONT ) {
              Serial.println("Sending 255 bytes of Zero...");
              for (int i = 0; i < 128; i++ ) {
                LoRa.beginPacket();
                for (int j = 0; j < 255; j++ ) 
                  LoRa.write(0);
                LoRa.endPacket();
                if ( Serial.available() ) 
                    break;
                Serial.println("*");
              };
              Serial.println("done.");
              LoRa.receive();
            } else {
              String msg = mycall + " " +line_buffer;
              LoRa.beginPacket();
              LoRa.print(msg);
              LoRa.endPacket();
              if ( verbose )
                Serial.println("Send: " + msg);
              LoRa.receive();
            }
          }
          Serial.print(mycall + "> ");   
          line_buffer = "";
       } else {
        line_buffer += c;
       }
  }
  if (remote_set) {
   remote_set =false;
   do_command(remote_command);
   for ( int i = 0; i < 3 ; i++) {
    delay(2000);
    LoRa.beginPacket();
    LoRa.print(mycall + " VVV VVV VVV ");
    LoRa.endPacket();
   }
   LoRa.beginPacket();
   LoRa.print(mycall + " " + "done.");
   LoRa.endPacket();
   LoRa.receive();
  }
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;

  String incoming = "";
  
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
  String hiscall = incoming.substring(0,incoming.indexOf(" "));
  String message = incoming.substring(incoming.indexOf(" ")+1);
  String rssi = String(LoRa.packetRssi());
  String snr = String(LoRa.packetSnr());
  String ferr = String(LoRa.packetFrequencyError());
  String rprt = "RSSI=" + rssi + " SNR=" + snr + " Ferr=" + ferr;

  if ( incoming.indexOf("rset") >= 0) {
    remote_set = true;
    remote_command = incoming;
  };

  Serial.println("");
  if ( verbose ) 
    Serial.println(message + " <" + hiscall + "(" + rprt + ")");
  else
    Serial.println(message  + " <" + hiscall + "("+rssi+", "+snr+", "+ferr+")");
  Serial.print(mycall + "> ");
  if ( mode == MODE_BOT && !hiscall.equalsIgnoreCase(mycall)) {
    LoRa.beginPacket();
    LoRa.print(mycall + " UR "+ rprt + " Msg=" + incoming);
    LoRa.endPacket();
    LoRa.receive();
  }     
}
