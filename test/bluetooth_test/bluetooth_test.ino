#define BUFFER_SIZE 256
char buffer_in[256];
size_t bytes_received;

void setup() {
  Serial.begin(9600);
}

void loop() {
}

void serialEvent() {
  bytes_received = Serial.readBytes(buffer_in, BUFFER_SIZE);
  buffer_in[bytes_received] = 0;
  Serial.println(bytes_received);
  Serial.println(buffer_in);
}
