#include <WiFi.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>



const char* ssid = "NIWC-Guest";

const char* password = "Leyte Gulf";

ros::NodeHandle nh;

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
  nh.getHardware()->setConnection(server_ip, server_port);  // Set your ROS master IP and port
  nh.initNode();
  nh.subscribe(sub);

}

 

void loop() {
  nh.spinOnce();
  delay(10);
}