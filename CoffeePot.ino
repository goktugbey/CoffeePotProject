#include <ESP8266WiFi.h>
#include <ESP8266TelegramBOT.h>

const char* ssid = "AndroidAP";
const char* password = "12345678";

// Initialize Telegram BOT
#define BOTtoken "299468991:AAGYEWVlkO5zFllIPjp4Fze3P1Mja1lmAE8"  //token of TestBOT
#define BOTname "CoffeePot"
#define BOTusername "coffeepot_bot"
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;


void Bot_ExecMessages() {
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    bot.message[i][5]=bot.message[i][5].substring(1,bot.message[i][5].length());
    if (bot.message[i][5] == "\/coffeetime") {
      digitalWrite(14, HIGH);   // turn the LED on (HIGH is the voltage level)
      bot.sendMessage(bot.message[i][4], "Your coffee is getting ready", "");
    }
    if (bot.message[i][5] == "\/thanks") {
      digitalWrite(14, LOW);    // turn the LED off (LOW is the voltage level)
      bot.sendMessage(bot.message[i][4], "Your coffee is ready, see you later, sir.", "");
    }
    if (bot.message[i][5] == "\/start") {
      String wellcome = "Greetings from your CoffeePot";
      String wellcome1 = "/coffeetime : to switch the CoffeePot ON";
      String wellcome2 = "/thanks : to switch the CoffeePot OFF";
      bot.sendMessage(bot.message[i][4], wellcome, "");
      bot.sendMessage(bot.message[i][4], wellcome1, "");
      bot.sendMessage(bot.message[i][4], wellcome2, "");
      Start = true;
    }
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}


// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  bot.begin();      // launch Bot functionalities
  pinMode(14, OUTPUT); // initialize digital pin 14 as an output.

  
}

void loop() {
  
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message
    Bot_ExecMessages();   
    Bot_lasttime = millis();
  }
}


