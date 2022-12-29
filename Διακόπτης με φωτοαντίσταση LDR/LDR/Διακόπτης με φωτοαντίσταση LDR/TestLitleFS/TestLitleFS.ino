#include "LittleFS.h"
 
void setup() {
  Serial.begin(115200);
  
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  

  Serial.println("");
  String Myname = "Γιάννης";
  Serial.println(Myname);
  writeData("/test_example.txt", "Μυρίσκος");
  
  readData("/test_example.txt", Myname) ;
  Serial.println("---------------------");
  Serial.println(Myname);
 
}
 
void loop() {

}

void readData(String Address, String &Data) {
  File file = LittleFS.open(Address, "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  Data = file.readString();
  file.close();
}

void writeData(String Address, String Data) {
  //Open the file
  File file = LittleFS.open(Address, "w");
  //Write to the file
  file.print(Data);
  delay(1);
  //Close the file
  file.close();
}
