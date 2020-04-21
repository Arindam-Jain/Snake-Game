// SNAKE GAME on 8x8 LED matrix
// using Arduino and 2 74HC595 shift register.

// Pin connected to Pin 12 of 74HC595 (Latch)
int latchPin = 10;

// Pin connected to Pin 11 of 74HC595 (Clock)
int clockPin = 12;

// Pin connected to Pin 14 of 74HC595 (Data)
int dataPin = 11;

// Screen
byte led[8];

// button pin
int btn_up = 0;
int btn_down = 1;
int btn_left = 2;
int btn_right = 3;

// game variables
typedef struct Link {
  int x;
  int y;
  struct Link * next;
} Link;

Link * pHead = NULL;
Link * pTail = NULL;

int curDirection = 4;
int newDirection = 4;
int appleX = 5;
int appleY = 5;

//Declaration of Arduino pins used as HCF4511 inputs
const int A=9;
const int B=8;
const int C=7;
const int D=6;

unsigned long oldTimer, curTimer;

boolean dead = 0;

void setup() {
  // Seed Random Generator with noise from analog pin 0  
  randomSeed(analogRead(0));

  // set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  // set button pins to input
  pinMode(btn_up, INPUT_PULLUP);
  pinMode(btn_down, INPUT_PULLUP);
  pinMode(btn_left, INPUT_PULLUP);
  pinMode(btn_right, INPUT_PULLUP);

  pinMode(A, OUTPUT); //LSB
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  
  Serial.begin(9600);
  // clear screen
  clrscr();
}

int count_seven = 0; //the variable used to show the number

void loop() {

  snakeInit();
  screenUpdate_red();
  screenUpdate_green();
  oldTimer = millis();
  curTimer = millis();

  while(!dead) {
    curTimer = millis();
    
    setDirection();
    
    if(curTimer-oldTimer >= 320) {
      curDirection = newDirection;
      moveSnake(curDirection);
      screenUpdate_red();
      screenUpdate_green();
      oldTimer = millis();
    }
    
    // update screen
    screenDisplay();
  }
  
  int count = 0;
  while(count<8) {
    curTimer = millis();
    if(curTimer-oldTimer >= 100) {
      led[count]=B11111111;
      oldTimer = millis();
      count++;
    }
    screenDisplay();
  }
  
  clrscr();
  
  while(1) {
    curTimer = millis();
    if(curTimer-oldTimer >= 700) {
      for(int i=0; i<8; i++) {
        led[i]=~led[i];
      }
      oldTimer = millis();
    }
    screenDisplay();
  }
  
  
}


void to_BCD()
{
    if (count_seven == 0) //write 0000
  {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 1) //write 0001
  {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 2) //write 0010
  {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 3) //write 0011
  {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 4) //write 0100
  {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 5) //write 0101
  {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 6) //write 0110
  {
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 7) //write 0111
  {
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
    }
    
    if (count_seven == 8) //write 1000
  {
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
    }
    
    if (count_seven == 9) //write 1001
  {
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
    } 
}

void addHead(int x, int y)
{
  Link *temp;
  temp = (Link*) malloc (sizeof(Link));
    
  // create new head
  temp->x = x;
  temp->y = y;
  temp->next = NULL;
    
  if(pHead!=NULL)
    pHead->next = temp;
    
  // point to new head
  pHead = temp;
}


void snakeInit() {
  int x = 3;
  int y = 3;
  for (int i=0; i<2; i++, x++) {
    addHead(x,y);
    if (i == 0)
      pTail = pHead;
  }
}

void setDirection() {
  if(digitalRead(btn_up) == LOW) {
    if(curDirection!=2)
      newDirection = 1;
  }
  if(digitalRead(btn_down) == LOW) {
    if(curDirection!=1)
      newDirection = 2;
  }
  if(digitalRead(btn_left) == LOW) {
    if(curDirection!=4)
      newDirection = 3;
  }
  if(digitalRead(btn_right) == LOW) {
    if(curDirection!=3)
      newDirection = 4;
  }
}

void moveSnake(int direction)
{
  int newX = pHead->x;
  int newY = pHead->y;
  if(direction==1)
    newY--;
  if(direction==2)
    newY++;
  if(direction==3)
    newX--;
  if(direction==4)
    newX++;

  if(newX > 8)
    newX=1;
  if(newX < 1)
    newX=8;
  if(newY > 8)
    newY=1;
  if(newY < 1)
    newY=8;

  dead |= check(newX, newY);

  if(!dead) {
    if(newX==appleX && newY==appleY) {
      addHead(newX, newY);
      newApple();
    }
    else {
      Link *temp = pTail;
            
      // point to new tail
      pTail = pTail->next;
            
      // new head
      pHead->next = temp;
      pHead = temp;
            
      pHead->x = newX;
      pHead->y = newY;      
      pHead->next = NULL;
    } 
  }
}

void newApple() {
  count_seven++; 
    delay(200); //the delay prevent from button bouncing
    if (count_seven == 10) //we want to count_seven from 0 to 9!
      count_seven = 0;
    to_BCD(); //convert to binary
  boolean check = 0;
  Link * ptr = pTail;
  do {
    check = 0;
    appleX = random(7) + 1;
    appleY = random(7) + 1;
    Serial.println(appleX);
    while(ptr!=NULL) {
      if(appleX==(ptr->x) && appleY==(ptr->y)) {
        check = 1;
        break;
      }
      ptr = ptr->next;
    }
  } while (check == 1);
}
    
boolean check(int x, int y) {
  Link *ptr;
  ptr = pTail;
  while(ptr!=NULL)
  {
    if(x==ptr->x && y==ptr->y)
      return 1;
    ptr=ptr->next;
  }
  
  return 0;
}
  
//
// display driver
//
void screenUpdate_green() {
  Link * ptr;
  ptr = pTail;
  
  clrscr();
  while(ptr!=NULL) {
    led[ptr->y-1] = led[ptr->y-1] | (1<<(8-ptr->x));
    ptr = ptr->next;
  }
  
  //led[appleY-1] = led[appleY-1] | (1<<(8-appleX)); // arindam
}  
void screenUpdate_red() {
  Link * ptr;
  ptr = pTail;
  
  clrscr();
 led[appleY-1] = led[appleY-1] | (1<<(8-appleX)); // arindam
}  
  
void screenDisplay() {
  byte row = B10000000;

  for (byte k = 0; k < 8; k++) {
    // Open up the latch ready to receive data
    digitalWrite(latchPin, LOW);
    
    shiftData(~row); // if use PNP transitors
    // shiftData(row);
     screenUpdate_red();
     shiftData(led[k]);// red
      screenUpdate_green();
     shiftData(led[k]);// green // arindam
    // Close the latch, sending the data in the registers out to the matrix
    digitalWrite(latchPin, HIGH);
    row = row >> 1;
  }
}

void clrscr()
{
  for(int i=0; i<8; i++) {
    led[i] = B00000000;
  }
}

void shiftData(byte data) {
  // Shift out 8 bits LSB first,
  // on rising edge of clock
  boolean pinState;

  //clear shift register read for sending data
  digitalWrite(dataPin, LOW);

  // for each bit in dataOut send out a bit
  for (int i=0; i<8; i++) 
  {
    //set clockPin to LOW prior to sending bit
    digitalWrite(clockPin, LOW);

    // if the value of data and (logical AND) a bitmask
    // are true, set pinState to 1 (HIGH)
    if (data & (1<<i)) 
    {
      pinState = HIGH;
    }
    else 
    {
      pinState = LOW;
    }

    //sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(dataPin, pinState);

    //send bit out on rising edge of clock
    digitalWrite(clockPin, HIGH);
    digitalWrite(dataPin, LOW);
  }

  //stop shifting
  digitalWrite(clockPin, LOW);
}
