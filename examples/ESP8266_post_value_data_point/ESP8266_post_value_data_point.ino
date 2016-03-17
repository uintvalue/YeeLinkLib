#include <ESP8266WiFiMulti.h>

#include <yl_data_point.h>
#include <yl_device.h>
#include <yl_wifi_client.h>
#include <yl_messenger.h>
#include <yl_sensor.h>
#include <yl_value_data_point.h>
#include <yl_sensor.h>

ESP8266WiFiMulti wifiMulti;

//this example reads data from a lm35dz sensor, convert value to degree Celsius
//and then post it to yeelink.net

//replace 2633 3539 with ur device id and sensor id
yl_device ardu(2633);
yl_sensor therm(3539, &ardu);
//replace first param value with ur u-apikey
yl_wifi_client client;
yl_messenger messenger(&client, "your-apikey", "api.yeelink.net");


void setup()
{
    Serial.begin(115200);	//for output information
	delay(10);
	randomSeed(analogRead(0));

	wifiMulti.addAP("SSID", "password");
    wifiMulti.addAP("SSID1", "password1");

	Serial.println("Connecting Wifi...");
	if(wifiMulti.run() == WL_CONNECTED) {
		Serial.println("");
		Serial.println("WiFi connected");
		Serial.println("IP address: ");
		Serial.println(WiFi.localIP());
	}
}

void loop()
{
	if(wifiMulti.run() != WL_CONNECTED) {
		Serial.println("WiFi not connected!");
		delay(1000);
	}
	else
	{
		int randNumber = random(0, 500);
		Serial.println(randNumber);
		yl_value_data_point dp(randNumber);
		therm.single_post(messenger, dp);
		delay(1000 * 15);
	}

}
