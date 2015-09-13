#include <pebble.h>
#include "shared.h"
#include "location.h"

static void init() {
	shared_init();
  location_init();
	location_open();
}

static void deinit() {
  location_deinit();
}

int main() {
  init();
  app_event_loop();
  deinit();
}