// Convert to port manipulation later 

// Define SPI pins to bit-bash over
#define MOSI 1      // Data (Master In Slave Out)
#define CLK 2       // Clock
#define LE 3        // Latch Enable
#define msgLen 32   // Define the word size for the messages to be sent

void setup() {
  // setup code here, to run once:

  // Initialise SPI pins as outputs 
  pinMode(MOSI, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(LE, OUTPUT);

  // Set all SPI pins to 0
  digitalWrite(MOSI, LOW);
  digitalWrite(CLK, LOW);
  digitalWrite(LE, LOW);

  delay(5);
}

void loop() {
  // put your main code here, to run repeatedly:
//  // Test code
//  digitalWrite(1, HIGH);
//  delay(1);
//  digitalWrite(1, LOW);
//  delay(1);
unsigned long msg = 0x0000FFFF;
digitalWrite(MOSI, HIGH);
delay(1);
digitalWrite(MOSI,LOW);
word_send(msg); // 8 digits of hex make up 32 bits of binary

}

void word_send(unsigned long msg) 
{
  int select = 1; //2^msgLen
  for(int i = 0; i < msgLen; i++) 
  {
    if (msg & 0x80000000 != 0) bit_send(1);
    else bit_send(0);
    msg = msg >> 1;
  }
}

void bit_send(byte b)
{
  if (b == 1) 
  {
    digitalWrite(MOSI, HIGH);
    delay(0.1);
    digitalWrite(CLK, HIGH);
    delay(0.1);
    digitalWrite(CLK, LOW);
    delay(0.1);
    digitalWrite(MOSI, LOW);
    delay(0.1);
  }
  else 
  {
    digitalWrite(MOSI, LOW);
    delay(0.1);
    digitalWrite(CLK, HIGH);
    delay(0.1);
    digitalWrite(CLK, LOW);
    delay(0.1);
    digitalWrite(MOSI, LOW);
    delay(0.1);
  }
}
