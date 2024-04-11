#include <LCDWIKI_GUI.h>
#include <LCDWIKI_KBV.h>

LCDWIKI_KBV mylcd(ILI9486, A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

//********* Define Colours Below ***************
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


int button = 53;
int baudCount = 4;
unsigned long baudRates[] = {300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, 115200};
int numBaudRates = sizeof(baudRates) / sizeof(baudRates[0]);
int buttonState = LOW;
int prevButtonState = LOW;

String strReceived;

void setup() {
  pinMode(button, INPUT_PULLUP);
  //Serial.begin(4800);

  mylcd.Init_LCD();                   //Initialize Display Object
  mylcd.Set_Rotation(1);              //Set Screen Orientation
  mylcd.Fill_Screen(CYAN);            //Background Colour
  mylcd.Set_Text_Size(2);             //Text Size
  mylcd.Set_Text_colour(BLACK);       //Text Colour
  mylcd.Set_Text_Mode(1);             //Text howit's Displayed

  mylcd.Print("RME \n Ramon Mengerink Engineering \n www.rm-e.nl +31 642810591", 10, 50);  //Numbers = across, down
  delay(10000);
  mylcd.Fill_Screen(CYAN);

  long int baudRate = 4800;
  Serial1.begin(baudRate);
  mylcd.Print("Baud rate: ", 10, 10);        // Print the label
  char ChrBaudRate[7];
  ultoa(baudRate, ChrBaudRate, 10);
  mylcd.Print(ChrBaudRate, 130 , 10);  
  Serial2.begin(4800);

}

void loop() {
  
  
  buttonState = digitalRead(button);

  // Check if button is pressed and has transitioned from HIGH to LOW
  if (buttonState == LOW && prevButtonState == HIGH) {
    // Update baud rate
    baudCount = (baudCount + 1) % numBaudRates;
    unsigned long baudRate = baudRates[baudCount];

    // Change serial1 baud rate
    Serial1.end();
    Serial1.begin(baudRate);

    // Print baud rate to LCD
    mylcd.Fill_Rect(10, 10, 220, 20, CYAN);    // Clear the previous line
    mylcd.Print("Baud rate: ", 10, 10);        // Print the label
    char ChrBaudRate[7];
    ultoa(baudRate, ChrBaudRate, 10);
    mylcd.Print(ChrBaudRate, 130 , 10);     

    // Delay for display (adjust as needed)
    delay(500);
  }

  // Update previous button state
  prevButtonState = buttonState;
  send();
  readData();

}

void send(){
  Serial2.println("test test");
}

void readData() {
  static int line = 0;
  while (Serial1.available()) {
    strReceived = Serial1.readStringUntil('\n'); //read the incoming data as string
    

    // Convert String to C-style string
    char charArray[strReceived.length() + 1]; // +1 for null terminator
    strReceived.toCharArray(charArray, sizeof(charArray));
    
    line = (line + 1) % 15;
    if (line == 0) {
      //mylcd.Fill_Rect(00, 30, 1000, 1000, CYAN);    // Clear the previous line
    }
    
    // Print the C-style string
    mylcd.Fill_Rect(00, line*15+30, 1000, 15, CYAN);
    mylcd.Print(charArray, 10, line*15+30);
  }
}
