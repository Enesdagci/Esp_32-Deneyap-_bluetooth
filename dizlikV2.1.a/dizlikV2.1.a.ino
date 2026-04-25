#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <time.h>
#include <sys/time.h>
#include "FS.h"
#include "SPIFFS.h"

// Sensor Canlı takip silinmiş hali güncel

// Toplam sensör sayısının tanımlanması
#define sensor_sayisi 5 

// BLE servis ve karakteristik tanımları
#define SERVICE_UUID        "12345678-1234-1234-1234-1234567890ab"
#define CHARACTERISTIC_UUID "abcd1234-5678-90ab-cdef-1234567890ab"

// Zaman tanımlaması
#define UUID_SET_TIME "13333333-3333-3333-3333-333333333333" 

// Log tanımlanması
#define UUID_GET_LOGS "13333333-4444-4444-4444-444444444444" 
#define UUID_SEND_LOGS "13333333-5555-5555-5555-555555555555"
#define UUID_CLEAR_LOGS "13333333-6666-6666-6666-666666666666"

// Pil Seviyesinin tanımlanması
#define UUID_BATTERY_LEVEL "13333333-7777-7777-7777-777777777777"

BLECharacteristic *tempCharacteristic;
BLECharacteristic *pDataDumpCharacteristic;
BLECharacteristic *pBatteryCharacteristic;

// Sensör pinlerinin tanımlanması
const int sensorPinleri[sensor_sayisi] = {A0, A1, A2, A3, A4}; 

const int batteryPin = 35; // Batarya pininin tanımlanması

float sicaklikToplami[sensor_sayisi]; // Her sensörün 1dk'lık toplamını tutar
int sicaklikSayaci[sensor_sayisi];    // Her sensörün 1dk'lık sayacını tutar

long sonKayitZamani = 0;      // En son ne zaman kayıt yaptık (Unix Timestamp)

// Bağlantı durumunu yönetme
class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      Serial.println("Cihaz bağlandı.");
    }

    void onDisconnect(BLEServer* pServer) {
      Serial.println("Cihaz bağlantıyı kesti. Yayın tekrar başlatılıyor...");
      pServer->startAdvertising(); 
    }
};

// Zamanın oluşturulması
class TimeSetCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        String value = pCharacteristic->getValue();
        if (value.length() > 0) {
            long timestamp = atol(value.c_str());
            struct timeval tv;
            tv.tv_sec = timestamp;
            tv.tv_usec = 0;
            settimeofday(&tv, NULL);
            Serial.print("Saat telefondan ayarlandı! Unix Timestamp: ");
            Serial.println(timestamp);
        }
    }
};

// Logların kontrolü
class LogsRequestCallback: public BLECharacteristicCallbacks {
  private:
    BLECharacteristic* pNotifyChar;

  public:
    LogsRequestCallback(BLECharacteristic* pCharacteristic) {
      pNotifyChar = pCharacteristic;
    }

    void onWrite(BLECharacteristic *pWriteChar) {
      String cmd = pWriteChar->getValue();
      if (cmd == "GET") {
        Serial.println("Telefon logları istedi. Gönderim başlıyor...");
        
        File dosya = SPIFFS.open("/datalog.txt", FILE_READ);
        if(!dosya) {
          Serial.println("Log dosyası açılamadı!");
          pNotifyChar->setValue("ERROR: NO_FILE");
          pNotifyChar->notify();
          return;
        }

        while (dosya.available()) {
          String line = dosya.readStringUntil('\n');
          line.replace("\r", ""); 
    
          if (line.length() > 0) {
            pNotifyChar->setValue(line.c_str());
            pNotifyChar->notify();
            delay(20);
          }
        }
        dosya.close();

        Serial.println("Log gönderimi bitti.");
        delay(20);

        float EOT_SIGNAL = -999.0;
        tempCharacteristic->setValue(EOT_SIGNAL);
        tempCharacteristic->notify();
      }
    }
};

// Logların temizlenmesi
class LogsClearCallback: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        String cmd = pCharacteristic->getValue();
        if (cmd == "CLEAR") {
            Serial.println("Telefondan 'Logları Sil' onayı (ACK) alındı.");
            if (SPIFFS.remove("/datalog.txt")) {
                Serial.println("datalog.txt başarıyla silindi.");
            } else {
                Serial.println("Dosya silme hatası.");
            }
        }
    }
};

// Log kayıt etme
void kayitEkle(String veriSatiri) {
  File dosya = SPIFFS.open("/datalog.txt", FILE_APPEND);
  if(!dosya) {
    Serial.println("Dosya yazmak için açılamadı");
    return;
  }
  
  if(dosya.println(veriSatiri)) {
    Serial.print("Dosyaya eklendi: ");
    Serial.println(veriSatiri);
  } else {
    Serial.println("Dosyaya yazma hatası");
  }
  dosya.close();
}

uint8_t getBatteryPercentage() {
  int adcValue = analogRead(batteryPin);
  float adcVoltage = (adcValue / 4095.0) * 3.3;
  float batteryVoltage = adcVoltage * 2.0;
  float percentage = 100.0 * (batteryVoltage - 3.2) / (4.2 - 3.2);

  if (percentage > 100.0) percentage = 100.0;
  if (percentage < 0.0) percentage = 0.0;

  return (uint8_t)percentage;
}

void setup() {
  Serial.begin(115200);
  setenv("TZ", "GMT-3", 1); 
  tzset();
  
  if(!SPIFFS.begin(true)){
    Serial.println("SPIFFS bağlanamadı!");
    return;
  }
  Serial.println("SPIFFS başarıyla bağlandı.");

  // BLE başlatma
  BLEDevice::init("DizlikSensör10");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // 1. Sıcaklık Karakteristiği (Notify)
  tempCharacteristic = pService->createCharacteristic(
                         CHARACTERISTIC_UUID,
                         BLECharacteristic::PROPERTY_NOTIFY
                       );
                       
  // 2. Zaman Ayarı Karakteristiği (Write)
  BLECharacteristic *pTimeCharacteristic = pService->createCharacteristic(
                                             UUID_SET_TIME,
                                             BLECharacteristic::PROPERTY_WRITE
                                           );
  pTimeCharacteristic->setCallbacks(new TimeSetCallback());

  // 3. Veri Gönderme Karakteristiği (Notify)
  BLECharacteristic* pDataDumpCharacteristic = pService->createCharacteristic(
                                               UUID_SEND_LOGS,
                                               BLECharacteristic::PROPERTY_NOTIFY
                                             );

  // 4. Veri İsteme Karakteristiği (Write)
  BLECharacteristic *pGetLogsCharacteristic = pService->createCharacteristic(
                                                UUID_GET_LOGS,
                                                BLECharacteristic::PROPERTY_WRITE
                                              );                                            
  pGetLogsCharacteristic->setCallbacks(new LogsRequestCallback(pDataDumpCharacteristic));

  // 5. Logları Silme Karakteristiği (Write)
  BLECharacteristic *pClearLogsCharacteristic = pService->createCharacteristic(
                                                  UUID_CLEAR_LOGS,
                                                  BLECharacteristic::PROPERTY_WRITE
                                                );
  pClearLogsCharacteristic->setCallbacks(new LogsClearCallback());

  // 6. Batarya Karakteristiği
  pBatteryCharacteristic = pService->createCharacteristic(
                                 UUID_BATTERY_LEVEL,
                                 BLECharacteristic::PROPERTY_READ |
                                 BLECharacteristic::PROPERTY_NOTIFY
                               );
 
  pService->start();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->start();

  Serial.println("BLE cihaz yayında...");
}

void loop() {
  time_t simdikiZaman = time(NULL);

  // ============================================================
  // ✅ YENİ: 1 DAKİKADA BİR 5 SENSÖRÜN VERİSİNİ TOPLA VE KAYDET
  // (Canlı takip kaldırıldı - Sadece 60 saniyede bir işlem)
  // ============================================================
  
  static long sonOkumaZamani = 0; 
  
  if (simdikiZaman - sonOkumaZamani >= 60) { // 1 dakika geçti mi?
    sonOkumaZamani = simdikiZaman;
    
    Serial.println("--- 1 Dakikalık Kayıt Döngüsü ---");

    // 5 sensörün hepsinden veri oku
    for (int i = 0; i < sensor_sayisi; i++) {
      int adcValue = analogRead(sensorPinleri[i]);
      float voltage = (adcValue / 4095.0) * 3.3;
      float resistance = (3.3 * 4700 / voltage) - 4700;
      float tempK = 1.0 / (1.0 / (25 + 273.15) + (1.0 / 3950.0) * log(resistance / 4700.0));
      float anlikSicaklik = tempK - 273.15;

      sicaklikToplami[i] += anlikSicaklik;
      sicaklikSayaci[i]++;
      
      Serial.print("Sensör "); Serial.print(i); Serial.print(": "); Serial.println(anlikSicaklik);
    }

    // Ortalama hesapla ve kaydet
    if (sicaklikSayaci[0] > 0) {
      // Zaman formatı
      char zamanFormati[6]; 
      struct tm * zamanBilgisi;
      zamanBilgisi = localtime(&simdikiZaman);
      strftime(zamanFormati, sizeof(zamanFormati), "%H:%M", zamanBilgisi);

      String kayitSatiri = String(zamanFormati);

      // Ortalama hesapla
      for (int i = 0; i < sensor_sayisi; i++) {
        float ortalamaSicaklik = sicaklikToplami[i] / sicaklikSayaci[i];
        kayitSatiri += "," + String(ortalamaSicaklik);
        
        // Sayaçları sıfırla
        sicaklikToplami[i] = 0.0;
        sicaklikSayaci[i] = 0;
      }
      
      // Dosyaya kaydet
      kayitEkle(kayitSatiri);

      // ✅ Pil seviyesini sadece kayıt sırasında gönder
      uint8_t pilYuzdesi = getBatteryPercentage();
      pBatteryCharacteristic->setValue(&pilYuzdesi, 1);
      pBatteryCharacteristic->notify();
      Serial.print("Pil Yüzdesi: %"); Serial.println(pilYuzdesi);
    }
  }
}
