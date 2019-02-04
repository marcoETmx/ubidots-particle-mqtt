/*
Copyright (c) 2016 Ubidots.
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Made by: Jose García -- Developer at Ubidots Inc

*/

#ifndef UbidotsMQTT_H
#define UbidotsMQTT_H

#include "MQTT.h"
#include "application.h"

#ifndef FIRST_PART_TOPIC
#define FIRST_PART_TOPIC "/v1.6/devices/"
#endif

#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

#ifndef SERVER
#define SERVER "things.ubidots.com"
#endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

#ifndef MAX_VALUES
#define MAX_VALUES 5
#endif

typedef struct ValueMQTT {
  char* _context;
  unsigned long _timestamp;
  float _value;
  char* _variableLabel;
} ValueMQTT;

class UbidotsMQTT {
 private:
  void (*callback)(char*, uint8_t*, unsigned int);
  MQTT* _client;
  ValueMQTT* val;
  String _clientName;
  bool _debug = false;
  uint8_t _currentValue;
  char* _server;
  char* _token;
  char* build_json(char* variableLabel, float value, char* context,
                   char* timestamp);

 public:
  UbidotsMQTT(char* token, void (*callback)(char*, uint8_t*, unsigned int));
  void add(char* variableLabel, float value);
  void add(char* variableLabel, float value, char* context);
  void add(char* variableLabel, float value, char* context,
           unsigned long timestamp);
  bool connect();
  void initialize();
  bool isConnected();
  bool loop();
  bool reconnect();
  bool ubidotsPublish(char* device);
  bool ubidotsSubscribe(char* deviceLabel, char* variableLabel);
  void ubidotsSetBroker(char* broker);
  void ubidotsSetDebug(bool debug);
};

#endif