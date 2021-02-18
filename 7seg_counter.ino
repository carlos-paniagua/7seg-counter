// LEDをオン・オフする際の出力
#define DIGIT_ON LOW
#define DIGIT_OFF HIGH
#define SEGMENT_ON HIGH
#define SEGMENT_OFF LOW

const int up_button = 19;
const int down_button = 18;
const int reset_button = 17;

int old_val1 = 1;
int old_val2 = 1;
int old_val3 = 1;
int up = 0;
int down = 0;
int reset = 0;
int i = 0;

const int digitPins[] = {8, 6, 5, 2};                                        // ディジット(コモン)に接続するArduinoのピン
const int segmentPins[] = {3,7,10,12,13,4,9};                                // セグメントピンに接続するArduinoのピン
const int numberOfDigitPins = sizeof(digitPins) / sizeof(digitPins[0]);        // ディジットの数
const int numberOfSegmentPins = sizeof(segmentPins) / sizeof(segmentPins[0]);  // セグメントの数

// 数字と表示させるセグメントの関係
const int digits[] = {
    0b00111111,  // 0
    0b00000110,  // 1
    0b01011011,  // 2
    0b01001111,  // 3
    0b01100110,  // 4
    0b01101101,  // 5
    0b01111101,  // 6
    0b00100111,  // 7
    0b01111111,  // 8
    0b01101111,  // 9
};

// 数字を表示する
void displayNumber(int n) {
  // digits[n]の各ビットを調べて対応するセグメントを点灯・消灯する
  for (int i = 0; i < numberOfSegmentPins; i++) {
    digitalWrite(segmentPins[i], digits[n] & (1 << i) ? SEGMENT_ON : SEGMENT_OFF);
  }
}

// セグメントをすべてオフにする
void clearSegments() {
  for (int j = 0; j < numberOfSegmentPins; j++) {
    digitalWrite(segmentPins[j], SEGMENT_OFF);
  }
}

// 4桁の数字を表示する
void displayNumbers(int n) {
  for (int i = 0; i < numberOfDigitPins; i++) {  // 右の桁からディジットを選択する
    digitalWrite(digitPins[i], DIGIT_ON);        // ディジットをオンにする
    displayNumber(n % 10);                       // 10で割った余りを求めて、1の位を求め、表示する
    delay(1);
    clearSegments();                        // セグメントをすべてオフにする
    digitalWrite(digitPins[i], DIGIT_OFF);  // ディジットをオフにする
    n /= 10;                                // 10で割り、次に表示する数字を、1の位に移す
  }
}

// setup()　は，最初に一度だけ実行される
void setup() {
  pinMode(up_button, INPUT_PULLUP );
  pinMode(down_button, INPUT_PULLUP );
  pinMode(reset_button, INPUT_PULLUP );
  
  for (int i = 0; i < numberOfDigitPins; i++) {
    pinMode(digitPins[i], OUTPUT);  // digitPinsを出力モードに設定する
    digitalWrite(digitPins[i], DIGIT_OFF);
  }
  for (int i = 0; i < numberOfSegmentPins; i++) {
    pinMode(segmentPins[i], OUTPUT);  // segmentPinsを出力モードに設定する
  }
  Serial.begin( 9600 );
}

void loop() {
  up = digitalRead(up_button);
  down = digitalRead(down_button);
  reset = digitalRead(reset_button);
  if((up == 0) && (old_val1 == 1)){
    if(i == 99){
      i = 0;
      } else{
        i++;
      }
  }else if((i != 0) && (down == 0) &&(old_val2 == 1)){
    i--;
  }else if((reset == 0) &&(old_val3 == 1)){
    i = 0; 
  }
  displayNumbers(i);
  old_val1 = up;
  old_val2 = down;
  old_val3 = reset;
}
