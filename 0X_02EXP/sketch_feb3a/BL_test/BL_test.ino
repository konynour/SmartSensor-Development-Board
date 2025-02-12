char t;
 
void setup() {
pinMode(8,OUTPUT);   //left motors  forward
pinMode(12,OUTPUT);   //left motors reverse
pinMode(11,OUTPUT);   //right  motors forward
pinMode(10,OUTPUT);   //right motors reverse
pinMode(9,OUTPUT);   //Led
pinMode(13, OUTPUT);
pinMode(5, INPUT_PULLUP); // Button 1
pinMode(6, INPUT_PULLUP); // Button 2
pinMode(7, INPUT_PULLUP); // Button 3

Serial.begin(9600);


 
}

 
void loop() {
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}


 if(digitalRead(5)){
  Serial.println("Key1 is pressed");
}
 if(digitalRead(6)){
  Serial.println("Key2 is pressed");
}

 if(digitalRead(7)){
  Serial.println("Key3 is pressed");
}
 
 
if(t == 'F'){            //move  forward(all motors rotate in forward direction)
  digitalWrite(8,HIGH);
  digitalWrite(11,HIGH);
}

 
else if(t == 'B'){      //move reverse (all  motors rotate in reverse direction)
  digitalWrite(9,HIGH);
  digitalWrite(13,HIGH);
}
else if(t == 'Z'){      //move reverse (all  motors rotate in reverse direction)
  digitalWrite(12,HIGH);
  digitalWrite(10,HIGH);
}
  
else if(t == 'L'){      //turn right (left side motors rotate in forward direction,  right side motors doesn't rotate)
  digitalWrite(10,HIGH);
  digitalWrite(8,HIGH);
}
 
else  if(t == 'R'){      //turn left (right side motors rotate in forward direction, left  side motors doesn't rotate)
  digitalWrite(9,HIGH);
  digitalWrite(8,HIGH);
}


else if(t ==  'W'){    //turn led on or off)
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
}

 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(13,LOW);
  digitalWrite(9,LOW);
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  digitalWrite(8,LOW);
}
delay(100);
}
