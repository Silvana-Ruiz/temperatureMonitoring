/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL2XkKoOtSt"
#define BLYNK_TEMPLATE_NAME "BAMX"
#define BLYNK_AUTH_TOKEN "1X8E65qKdqIqvryIURKoGE7sDYh8KJpH"

char auth[] = BLYNK_AUTH_TOKEN;

// Select your modem:
//#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_MODEM_SIM900
//#define TINY_GSM_MODEM_M590
//#define TINY_GSM_MODEM_A6
//#define TINY_GSM_MODEM_A7
//#define TINY_GSM_MODEM_BG96
//#define TINY_GSM_MODEM_XBEE

// Default heartbeat interval for GSM is 60
// If you want override this value, uncomment and set this option:
//#define BLYNK_HEARTBEAT 30

#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>


// Your GPRS credentials
// Leave empty, if missing user or pass
char apn[]  = "internet.itelcel.com";
char user[] = "";
char pass[] = "";

// Hardware Serial on Mega, Leonardo, Micro
//#define SerialAT Serial1

// Define los pines para SoftwareSerial
#include <SoftwareSerial.h>
const int RX = 5; // Conectar al TX del SIM808
const int TX = 4; // Conectar al RX del SIM808

SoftwareSerial SerialAT(RX, TX);

TinyGsm modem(SerialAT);


#include <DHT.h>
BlynkTimer timer;

#define DHT22PIN 2      //pin D4
#define DHT22TYPE DHT22

DHT dht22(DHT22PIN, DHT22TYPE);

float h22;
float t22;


void setup()
{
  // Debug console
  Serial.begin(9600);
  dht22.begin();
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(115200);
  delay(3000);
  Serial.println("Initializing modem...");
  //modem.restart();
    modem.init();

  
  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

 // for ( int i =0; i < 15; i++){

//    Serial.println(i);  
//    delay(1000);
//  }

  
  Blynk.begin(auth, modem, apn, user, pass);  
  delay(10);
  timer.setInterval(1000L, Data_send);
}

void loop()
{
  Blynk.run();
    timer.run();
  dht_sensors();
}

//----------------------------------------------------------------------------------------------//

void dht_sensors()
{

  h22 = dht22.readHumidity();
  t22 = dht22.readTemperature();


    if (isnan(h22) || isnan(t22)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

    Serial.println("humedad: ");
    Serial.print(h22);
    Serial.println(" ");
    Serial.println(" ");
    Serial.println("Temperatura: ");
    Serial.print(t22); 
    Serial.println(" ");

    delay(3000);
}


void Data_send() // Envía datos a Blynk
{

  Blynk.virtualWrite(V0, t22);
  Blynk.virtualWrite(V1, h22);

}
