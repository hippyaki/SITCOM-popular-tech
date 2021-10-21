#include <WiFi.h>
#include <WebServer.h>
//#include <Servo.h>
#include <MobaTools.h>

MoToServo Left;
MoToServo Right;

int LeftA=15;  //D8
int LeftB=13;  //D7
int RightA=12; //D6
int RightB=14; //D5

int enA=2; //D4
int enB=0; //D3

/*Put your SSID & Password*/
const char* ssid = " ";  // Enter SSID here
const char* password = " ";  //Enter Password here

WebServer server(80);             
 
void setup() {

// ----- MOVEMENT ------
  Left.attach(9); //SD2
  Right.attach(10); //SD3

  pinMode(LeftA,OUTPUT);
  pinMode(LeftB,OUTPUT);
  pinMode(RightA,OUTPUT);
  pinMode(RightB,OUTPUT);

  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  
  Right.write(60); //Default Setup
  Left.write(120); //Default Setup

 //------ WiFi Connection ----------
  
  Serial.begin(115200);
  delay(100);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

//---------- Page Endpoints ( Main Control Room ) ----------------

  server.on("/asasasasa", handle_OnConnect);

  server.on("/asasasasa/left", left);

  server.on("/asasasasa/right", right);

  server.on("/asasasasa/forward", forward);

  server.on("/asasasasa/backward", backward);

  server.on("/asasasasa/stop", halt);

  server.on("/asasasasa/open", isOpen);
  server.onNotFound(handle_NotFound);

//---------- SERVER EXECUTION --------------

  server.begin();
  Serial.println("HTTP server started");
  
}
void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML()); 
}

void left() {
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,HIGH);
  digitalWrite(RightA,HIGH);
  digitalWrite(RightB,LOW);
  
  server.send(200, "text/html", SendHTML()); 
}

void right() {
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  
  digitalWrite(LeftA,HIGH);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,HIGH);
  
  server.send(200, "text/html", SendHTML()); 
}

void forward() {
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  
  digitalWrite(LeftA,HIGH);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,HIGH);
  digitalWrite(RightB,LOW);
  
  server.send(200, "text/html", SendHTML()); 
}

void backward() {
  digitalWrite(enA,HIGH);
  digitalWrite(enB,HIGH);
  
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,HIGH);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,HIGH);
  
  server.send(200, "text/html", SendHTML()); 
}

void halt() {
  digitalWrite(enA,LOW);
  digitalWrite(enB,LOW);
  
  digitalWrite(LeftA,LOW);
  digitalWrite(LeftB,LOW);
  digitalWrite(RightA,LOW);
  digitalWrite(RightB,LOW);
  server.send(200, "text/html", SendHTML()); 
}

void isOpen() {
  
  digitalWrite(enA,LOW); //stops the car immediately
  digitalWrite(enB,LOW); //..
       
  server.send(200, "text/html", SendHTML()); 

  for(int i=60;i<=140;i+=20)
     {
      Right.write(i);
      Left.write(180-i);
      delay(100);
     }
      
      delay (3000); // 3 second halt before closing
      
     for(int i=140;i>=60;i-=20)
     {
      Right.write(i);
      Left.write(180-i);
      delay(100);
     }
}


void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=yes\">\n";
  ptr +="<title>IoT Gesture Bot</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>Enter /command on the URL, or contact Admin for WebRemote</h1>\n";
  ptr +="<p>Available Commands - left,  right,  forward,  stop,  backward, open </p>";
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
