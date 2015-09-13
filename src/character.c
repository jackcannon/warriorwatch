#include <pebble.h>
#include "shared.h"
#include "character.h"
#include "location.h"

Window *character_window;
Layer *character_window_layer;

TextLayer *text_test;



static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	location_open();
}
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {}
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {}
static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
	window_set_background_color(window, GColorPictonBlue);
	character_window_layer = window_get_root_layer(character_window);
	
	text_test = text_layer_create(GRect(0, 0, 107, 20));
	prepare_layer(text_test, character_window_layer, GColorBlack, "TEST", FONT_KEY_GOTHIC_18_BOLD);
}





void character_init(void) {
	character_window = window_create();

	window_set_click_config_provider(character_window, click_config_provider);
	window_set_window_handlers(character_window, (WindowHandlers) {
		.load = window_load,
	});
}
void character_deinit(void) {
	window_destroy(character_window);
}
void character_open() {
	if (!character_window) {
		character_init();
	} 
	window_stack_push(character_window, true);	
}