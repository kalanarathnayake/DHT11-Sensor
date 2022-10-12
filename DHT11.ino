//Firebase library includes
#include <FirebaseESP8266.h>
// DHT11 sensor library includes
#include <DHT.h>
#include <DHT_U.h>

//Firebase connection data
#define FIREBASE_HOST "nodemcu-8bd8c-default-rtdb.firebaseio.com" // firebase link
#define FIREBASE_AUTH "gHkRCKjR1zSWhwl40OAqgK6AxXJuHXkj1XXwcPCb" // firebase suth

//wifi connection information 
#define WIFI_SSID "Dialog 4G CB3"
#define WIFI_PASSWORD "BMy7M977"

//DHT11 sensor initializing ports
#define DHTTYPE DHT11     
#define dht_dpin 12   // DHT data pin input (d6)
DHT dht(dht_dpin, DHTTYPE); 

// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

void setup() {

  //starting the serial monitor
  // change the serial monitor bit range to 9600 if not the serial monitor won't work
  Serial.begin(9600);

  // connecting NodeMCU to the Wifi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  //Start sensors
  dht.begin();

  // Firebase connection 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

}

void loop () {
  float Humidity, Temperature;

  // readings
  Humidity = dht.readHumidity();
  Temperature = dht.readTemperature();

  //display sensor captured data in serial monitor
  Serial.print("Humidity:    ");  Serial.print(Humidity); Serial.println("% ");
  Serial.print("Temperature: ");  Serial.print(Temperature);  Serial.println("C ");

  //Send sensor data to firebase live database
  Firebase.setFloat(firebaseData,"/DHT11/Humidity", Humidity);
  Firebase.setFloat(firebaseData,"/DHT11/Temperature", Temperature);

}


