#include <pebble.h>
#include "shared.h"
#include "location.h"
#include "welcome.h"

static void init() {
	light_enable(true);
	shared_init();
  location_init();
	
	if (persist_exists(PERSIST_LOCATION)) {
		location_open();
	} else {
		welcome_init();
		welcome_open();
	}
	
}

static void deinit() {
  location_deinit();
}

int main() {
  init();
  app_event_loop();
  deinit();
}