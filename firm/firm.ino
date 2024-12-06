#include <ArduinoBLE.h>
#define BLE_UUID      "19B10000-E8F2-537E-4F6C-D104768A1214"
#define BLE_UUID_CHAR "19B10001-E8F2-537E-4F6C-D104768A1214"

BLEService myService(BLE_UUID); // UUID
BLEStringCharacteristic myCharacteristic(BLE_UUID_CHAR, BLERead | BLEWrite, 20);

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()) {
    Serial.println("BLEの初期化に失敗しました!");
    while (1);
  }

  BLE.setLocalName("Nano33IoT");
  BLE.setAdvertisedService(myService);

  myService.addCharacteristic(myCharacteristic);
  BLE.addService(myService);

  BLE.advertise();

  Serial.println("BLEペリフェラルとしてアドバタイズ開始!");
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("デバイスが接続されました!");

    while (central.connected()) {
      if (myCharacteristic.written()) {
        String received = myCharacteristic.value();
        Serial.println("受信データ: " + received);
      }
    }

    Serial.println("デバイスが切断されました");
  }
}
