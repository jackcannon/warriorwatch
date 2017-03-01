#include <pebble.h>
#include "shared.h"
#include "welcome.h"
#include "location.h"

Window *welcome_window;
Layer *welcome_window_layer;

TextLayer *welcome_layer;
TextLayer *title_layer;

static GBitmap *icon_bitmap;
static BitmapLayer *icon_bitmap_layer;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	location_open();
	welcome_deinit();
}
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {}
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {}
static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
	window_set_background_color(window, GColorOxfordBlue);
	welcome_window_layer = window_get_root_layer(welcome_window);
	
	welcome_layer = text_layer_create(GRect(0, 10, 144, 28));
	title_layer = text_layer_create(GRect(0, 30, 144, 28));
	prepare_layer(welcome_layer, welcome_window_layer, GColorWhite, "Welcome to", FONT_KEY_GOTHIC_24);
	prepare_layer(title_layer, welcome_window_layer, GColorWhite, "Warrior Watch", FONT_KEY_GOTHIC_28_BOLD);
	
	
	icon_bitmap_layer = bitmap_layer_create(GRect(0, 60, 144, 32));
	bitmap_layer_set_bitmap(icon_bitmap_layer, icon_bitmap);
	bitmap_layer_set_compositing_mode(icon_bitmap_layer, GCompOpSet);
	layer_add_child(welcome_window_layer, bitmap_layer_get_layer(icon_bitmap_layer));
}



void welcome_init(void) {
	welcome_window = window_create();
	
	icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICON_BATTLE);

	window_set_click_config_provider(welcome_window, click_config_provider);
	window_set_window_handlers(welcome_window, (WindowHandlers) {
		.load = window_load,
	});
}
void welcome_deinit(void) {
	window_destroy(welcome_window);
}
void welcome_open() {
	if (!welcome_window) {
		welcome_init();
	} 
	window_stack_push(welcome_window, true);
}