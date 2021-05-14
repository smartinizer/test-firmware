#include <Smartinizer.h>
#include <usecase.hh>

Smartinizer* sm;

void setup() {
  pinMode(usecase::ledPin, OUTPUT);
  sm = new Smartinizer();
  sm->register_usecase(usecase::callback);
  sm->setup();
}


void loop() {
  sm->loop();
}
