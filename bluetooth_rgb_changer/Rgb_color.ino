int rgb_red_pin = 26, rgb_green_pin = 27, rgb_blue_pin = 25 ;


void setup() {
  // put your setup code here, to run once:
  pinMode(rgb_red_pin, OUTPUT);
  pinMode(rgb_green_pin, OUTPUT);
  pinMode(rgb_blue_pin, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  // Red led
  set_color(255,0,0);
  delay(500);
  // Green led
  set_color(0,255,0);
  delay(500);
  // Blue led
  set_color(0,0,255);
  delay(500);
  // white led
  set_color(255,255,255);
  delay(500);
  //  Yellow
  set_color(255,255,0);
  delay(500);
  // Cyan led
  set_color(0,255,255);
  delay(500);
  // Magenta led
  set_color(255,0,255);
  delay(500);
}

void set_color(int red, int green, int blue){
  analogWrite(rgb_red_pin, red);
  analogWrite(rgb_green_pin,green);
  analogWrite(rgb_blue_pin,blue);
}
