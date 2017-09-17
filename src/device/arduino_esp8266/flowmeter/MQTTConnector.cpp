#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "MQTTConnector.h"
#include "Global.h"
#include "Credentials.h"
#include "FlowSensor.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

boolean mqttInitCompleted = false;
String clientId = "IoTPractice-" + String(ESP.getChipId());

/* Incoming data callback. */
void dataCallback(char* topic, byte* payload, unsigned int length)
{
  char payloadStr[length + 1];
  memset(payloadStr, 0, length + 1);
  strncpy(payloadStr, (char*)payload, length);
  Printf("Data    : dataCallback. Topic : [%s]\n", topic);
  Printf("Data    : dataCallback. Payload : %s\n", payloadStr);

  if(strncmp(topic, MQTT_TOPIC_FLOW, strlen(topic)) == 0)
  {
    /* Experimental command distinguishment. */
    String tempStr = payloadStr;
    if (tempStr == "start")
    {
      FLOWInfinitive();
    }
    else if (tempStr == "stop")
    {
      FLOWStop();
    }
    else
    {
      int mliter = tempStr.toInt();
      FLOWStart(mliter);
    }
  }
}

/* MQTT connector function. */
void performConnect()
{
  uint16_t connectionDelay = 5000;
  while (!mqttClient.connected())
  {
    Printf("Trace   : Attempting MQTT connection...\n");
    if (mqttClient.connect(clientId.c_str(), MQTT_USERNAME, MQTT_KEY))
    {
      Printf("Trace   : Connected to Broker.\n");

      MQTTSubscribe(MQTT_TOPIC_FLOW);
    }
    else
    {
      Printf("Error!  : MQTT Connect failed, rc = %d\n", mqttClient.state());
      Printf("Trace   : Trying again in %d msec.\n", connectionDelay);
      delay(connectionDelay);
    }
  }
}

/* MQTT Publisher function. */
boolean MQTTPublish(const char* topic, const char* payload)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.publish(topic, payload);
  }
  return retval;
}

/* MQTT Subscriber function. */
boolean MQTTSubscribe(const char* topicToSubscribe)
{
  boolean retval = false;
  if (mqttClient.connected())
  {
    retval = mqttClient.subscribe(topicToSubscribe);
  }
  return retval;
}

/* Gather MQTT status. */
boolean MQTTConnected()
{
  return mqttClient.connected();
}

/* Init MQTT process */
void MQTTBegin()
{
  mqttClient.setServer(MQTT_BROKER, MQTT_BROKER_PORT);
  mqttClient.setCallback(dataCallback);
  mqttInitCompleted = true;
}

/* Sustain broker connection. */
void MQTTLoop()
{
  if(mqttInitCompleted)
  {
    if (!MQTTConnected())
    {
      performConnect();
    }
    mqttClient.loop();
  }
}
