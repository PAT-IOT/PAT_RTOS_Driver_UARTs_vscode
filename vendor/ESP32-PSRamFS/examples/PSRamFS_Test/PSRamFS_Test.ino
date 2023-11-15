int n_elements = 1000;
unsigned char * acc_data_all = (unsigned char *) ps_malloc (n_elements * sizeof (unsigned char));  

void setup(){
        delay(3000);
        Serial.begin(115200);
        if(psramInit()){
        Serial.println("\nPSRAM is correctly initialized");
        }else{
        Serial.println("PSRAM not available");
        }
}

void loop() {
  Serial.println(acc_data_all[1]);
  delay(5000);
}