#include <ArduinoBLE.h>

BLEService numberService("180C");  // Create a BLE service

// Create a characteristic to handle the number (4 bytes for an int32)
BLEIntCharacteristic numberCharacteristic("2A56", BLEWrite | BLEWriteWithoutResponse);

void setup() 
{
  Serial.begin(9600);
  while (!Serial);


  // Begin initialization
  if (!BLE.begin()) 
  {
    Serial.println("Starting BLE failed!");
    while (1);
  }


  // Set the local name peripheral advertises
  BLE.setLocalName("LED-Toggler");
  BLE.setAdvertisedService(numberService);

  // Add the characteristic to the service
  numberService.addCharacteristic(numberCharacteristic);

  // Add the service
  BLE.addService(numberService);

  // Start advertising
  BLE.advertise();

  Serial.println("BLE number receiver ready");
  
  pinMode(LEDR, OUTPUT);              //0 = OFF    1 == ON
  digitalWrite(LEDR, HIGH);

  pinMode(LEDG, OUTPUT);              //2 = OFF    3 == ON
  digitalWrite(LEDG, HIGH);

  pinMode(LEDB, OUTPUT);              //4 = OFF    5 == ON
  digitalWrite(LEDB, HIGH);
}




void loop() 
{
  // Listen for BLE peripherals to connect
  BLEDevice central = BLE.central();

  // If a central is connected to the peripheral
  if (central) 
  {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    // While the central is connected
    while (central.connected()) 
    {
      if (numberCharacteristic.written()) 
      {
        int receivedNumber = numberCharacteristic.value();
        Serial.print("Received number: ");
        Serial.println(receivedNumber);



      if(receivedNumber == 0)
        digitalWrite(LEDR, HIGH);
      else if(receivedNumber == 1)
        digitalWrite(LEDR, LOW);
      else if(receivedNumber == 2)
        digitalWrite(LEDG, HIGH);
      else if(receivedNumber == 3)
        digitalWrite(LEDG, LOW);
      else if(receivedNumber == 4)
        digitalWrite(LEDB, HIGH);
      else if(receivedNumber == 5)
        digitalWrite(LEDB, LOW);
      
      


      }
    }

    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
