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
char apn[] = "internet.itelcel.com";
char user[] = "";
char pass[] = "";

// Hardware Serial on Mega, Leonardo, Micro
//#define SerialAT Serial1

// Define los pines para SoftwareSerial
#include <SoftwareSerial.h>
const int RX = 5;  // Conectar al TX del SIM808
const int TX = 4;  // Conectar al RX del SIM808

SoftwareSerial SerialAT(RX, TX);

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

#include <DHT.h>
BlynkTimer timer;

#define DHT22PIN 2  //pin D4
#define DHT22TYPE DHT22

DHT dht22(DHT22PIN, DHT22TYPE);

float h22;
float t22;

String temp = "Temperatura del camion 4 esta fuera de rango - La temperatura es: ";
String temp2 = "Reporte de temperatura actual del camion 4 - La Temperatura es: ";
void setup() {
  Serial.begin(9600);
  delay(100);
  SerialAT.begin(115200);
  delay(5000);
  dht22.begin();
  delay(3000);

 Serial.println("Reiniciando módem...");
  modem.restart();

  Serial.println("Conectando a GPRS...");
  if (!modem.gprsConnect(apn, user, pass)) {
    Serial.println("Fallo en la conexión GPRS");
    while (true);
  }
  Serial.println("Conexión GPRS establecida");

  Serial.println(" ");
  Serial.println("Dirección IP obtenida: ");
   sendATCommand("AT+CIFSR");

 timer.setInterval(10000L, dht_sensors);
 timer.setInterval(3600000L, dht_sensors2);
  //ESP.deepSleep(30e6);
  
}

void loop() {
  timer.run();
  }

//----------------------------------------------------------------------------------------------//

void dht_sensors() {
    h22 = dht22.readHumidity();
    t22 = dht22.readTemperature();
    Serial.println(" ");
    Serial.print("Humedad actual: ");
    Serial.print(h22);
    Serial.println(" ");
    Serial.println(" ");
    Serial.print("Temperatura actual: ");
    Serial.print(t22);
    Serial.println(" ");

      if (t22 > 7 || t22 < 3){

        temp.concat(t22);
        //Serial.println(modem.sendSMS("+526621238110","Hola MUNDO")?"OK":"FAIL");
        Serial.println(" ");
        Serial.println(" ");
        Serial.println(modem.sendSMS("+526623168087",temp)?"El mensaje envíado a Omar  Cañedo fue enviado con éxito":"El Mensaje enviado a Omar Cañedo no fue entregado");
        Serial.println(modem.sendSMS("+526623449296",temp)?"El mensaje envíado a Carlos Iribe fue enviado con éxito":"El Mensaje enviado a Carlos Iribe no fue entregado");
        Serial.println(modem.sendSMS("+526624794971",temp)?"El mensaje envíado a Francisco Gonzalez fue enviado con éxito":"El Mensaje enviado a Francisco Gonzalez no fue entregado");       
        Serial.println(modem.sendSMS("+526621031467",temp)?"El mensaje envíado a Juan Grimaldo fue enviado con éxito":"El Mensaje enviado a Juan Grimaldo no fue entregado");        
        Serial.println(modem.sendSMS("+526621484550",temp)?"El mensaje envíado a Artemio Galvez fue enviado con éxito":"El Mensaje enviado a Artemio Galvez no fue entregado");       
        Serial.println(modem.sendSMS("+526622950857",temp)?"El mensaje envíado a Daniel Salazar fue enviado con éxito":"El Mensaje enviado a Daniel Salazar no fue entregado");      
        Serial.println(modem.sendSMS("+526623998869",temp)?"El mensaje envíado a César Félix fue enviado con éxito":"El Mensaje enviado a César Félix no fue entregado");       
        Serial.println(modem.sendSMS("+526629489364",temp)?"El mensaje envíado a Reynaldo Hernandez fue enviado con éxito":"El Mensaje enviado a Reynaldo Hernandez no fue entregado");       
        Serial.println(modem.sendSMS("+526623265240",temp)?"El mensaje envíado a Adrian León fue enviado con éxito":"El Mensaje enviado a Adrian León no fue entregado");       
        Serial.println(modem.sendSMS("+526622339962",temp)?"El mensaje envíado a Gerardo Lara fue enviado con éxito":"El Mensaje enviado a Gerardo Lara no fue entregado");       
        Serial.println(modem.sendSMS("+526621400317",temp)?"El mensaje envíado a Marcelo Cota fue enviado con éxito":"El Mensaje enviado a Marcelo Cota no fue entregado");   
        Serial.println(modem.sendSMS("+526624703498",temp)?"El mensaje envíado a Francisco Pérez fue enviado con éxito":"El Mensaje enviado a Francisco Pérez no fue entregado");
        temp = "Temperatura del camion 4 esta fuera de rango - La temperatura es: ";
        Serial.println(" ");
        Serial.println(" ");
      }










  


    if (isnan(h22) || isnan(t22)) {
    Serial.println("No fue posible leer los datos del sensor DHT22");
    //return;
  }

   
 // Serial.println(modem.callNumber("+526621238110")?"OK":"FAIL");

}


void sendATCommand(String command) {
  //Serial.print("Enviando comando: ");
  //Serial.print(command);
  SerialAT.println(command); // Enviar el comando al SIM808
  delay(1000); // Esperar una respuesta
  while (SerialAT.available()) {
    char c = SerialAT.read(); // Leer la respuesta del SIM808
    Serial.write(c); // Mostrar la respuesta en el monitor serial
  }
  Serial.println();
}



void dht_sensors2() {
    h22 = dht22.readHumidity();
    t22 = dht22.readTemperature();
    Serial.println("Humedad: ");
    Serial.print(h22);
    Serial.println(" ");
    Serial.println(" ");
    Serial.println("Temperatura: ");
    Serial.print(t22);
    Serial.println(" ");

        temp2.concat(t22);
        //Serial.println(modem.sendSMS("+526621238110","Hola MUNDO")?"OK":"FAIL");
        Serial.println(" ");
        Serial.println(" ");
        Serial.println(modem.sendSMS("+526623168087",temp)?"El mensaje envíado a Omar  Cañedo fue enviado con éxito":"El Mensaje enviado a Omar Cañedo no fue entregado");
        Serial.println(modem.sendSMS("+526623449296",temp)?"El mensaje envíado a Carlos Iribe fue enviado con éxito":"El Mensaje enviado a Carlos Iribe no fue entregado");
        Serial.println(modem.sendSMS("+526624794971",temp)?"El mensaje envíado a Francisco Gonzalez fue enviado con éxito":"El Mensaje enviado a Francisco Gonzalez no fue entregado");       
        Serial.println(modem.sendSMS("+526621031467",temp)?"El mensaje envíado a Juan Grimaldo fue enviado con éxito":"El Mensaje enviado a Juan Grimaldo no fue entregado");        
        Serial.println(modem.sendSMS("+526621484550",temp)?"El mensaje envíado a Artemio Galvez fue enviado con éxito":"El Mensaje enviado a Artemio Galvez no fue entregado");       
        Serial.println(modem.sendSMS("+526622950857",temp)?"El mensaje envíado a Daniel Salazar fue enviado con éxito":"El Mensaje enviado a Daniel Salazar no fue entregado");      
        Serial.println(modem.sendSMS("+526623998869",temp)?"El mensaje envíado a César Félix fue enviado con éxito":"El Mensaje enviado a César Félix no fue entregado");       
        Serial.println(modem.sendSMS("+526629489364",temp)?"El mensaje envíado a Reynaldo Hernandez fue enviado con éxito":"El Mensaje enviado a Reynaldo Hernandez no fue entregado");       
        Serial.println(modem.sendSMS("+526623265240",temp)?"El mensaje envíado a Adrian León fue enviado con éxito":"El Mensaje enviado a Adrian León no fue entregado");       
        Serial.println(modem.sendSMS("+526622339962",temp)?"El mensaje envíado a Gerardo Lara fue enviado con éxito":"El Mensaje enviado a Gerardo Lara no fue entregado");       
        Serial.println(modem.sendSMS("+526621400317",temp)?"El mensaje envíado a Marcelo Cota fue enviado con éxito":"El Mensaje enviado a Marcelo Cota no fue entregado");   
        Serial.println(modem.sendSMS("+526624703498",temp)?"El mensaje envíado a Francisco Pérez fue enviado con éxito":"El Mensaje enviado a Francisco Pérez no fue entregado");
        Serial.println(" ");
        Serial.println(" ");
        
        temp2 = "Reporte de temperatura actual del camion 4 - La Temperatura es: ";
      


    if (isnan(h22) || isnan(t22)) {
    Serial.println("No fue posible leer los datos del sensor DHT22");
    //return;
  }

   
 // Serial.println(modem.callNumber("+526621238110")?"OK":"FAIL");

}
