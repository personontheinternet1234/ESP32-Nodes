#include <WiFi.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>

/*
  A ros-to-esp32 project created by
  Isaac Verbrugge isaacverbruge@gmail.com,
  Kayla Uyema kayla.uyema@gmail.com

  Install: WiFi, esp32 arduino espressif
  Install via arduino libraries: esp32 espressif boards
  Install via arduino libraries: rosserial

*/

const char* ssid = "RANGER";

const char* password = "militaryfps";

ros::NodeHandle nh;

IPAddress server(192,168,0,137);



void messageCb(const geometry_msgs::Twist& cmd_msg) {
  float linear_x = cmd_msg.linear.x;
  float angular_z = cmd_msg.angular.z;
  // Process the received velocities (linear_x, angular_z) here
  // For example, send these values to motor controllers
}



ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb);

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);

    Serial.println("Establishing connection to WiFi..");

  }

  Serial.println("Connected to network");
  nh.getHardware()->setConnection(server, 11411);  // Set your ROS master IP and port
  // nh.getHardware()->setConnection();  // Set your ROS master IP and port
  nh.initNode();
  nh.subscribe(sub);

}

 

void loop() {
  nh.spinOnce();
  delay(10);
}