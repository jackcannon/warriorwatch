#include <pebble.h>
#include "shared.h"
#include "character.h"
#include "location.h"

Window *character_window;
Layer *character_window_layer;

static GBitmap *char_warrior_bitmap;
static GBitmap *char_mage_bitmap;
static GBitmap *char_ninja_bitmap;
static BitmapLayer *char_warrior_bitmap_layer;
static BitmapLayer *char_mage_bitmap_layer;
static BitmapLayer *char_ninja_bitmap_layer;

// static GColor back_color = GColorPastelYellow;
// static GColor text_color = GColorBulgarianRose;


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
	window_set_background_color(window, GColorPastelYellow);
	character_window_layer = window_get_root_layer(character_window);
	
	char_warrior_bitmap_layer = bitmap_layer_create(GRect(2, 13, 32, 32));
	char_mage_bitmap_layer = bitmap_layer_create(GRect(2, 69, 32, 32));
	char_ninja_bitmap_layer = bitmap_layer_create(GRect(2, 125, 32, 32));
	bitmap_layer_set_bitmap(char_warrior_bitmap_layer, char_warrior_bitmap);
	bitmap_layer_set_bitmap(char_mage_bitmap_layer, char_mage_bitmap);
	bitmap_layer_set_bitmap(char_ninja_bitmap_layer, char_ninja_bitmap);
	bitmap_layer_set_compositing_mode(char_warrior_bitmap_layer, GCompOpSet);
	bitmap_layer_set_compositing_mode(char_mage_bitmap_layer, GCompOpSet);
	bitmap_layer_set_compositing_mode(char_ninja_bitmap_layer, GCompOpSet);
	layer_add_child(character_window_layer, bitmap_layer_get_layer(char_warrior_bitmap_layer));
	layer_add_child(character_window_layer, bitmap_layer_get_layer(char_mage_bitmap_layer));
	layer_add_child(character_window_layer, bitmap_layer_get_layer(char_ninja_bitmap_layer));
}



void character_init(void) {
	character_window = window_create();
	
	char_warrior_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHAR_WARRIOR);
	char_mage_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHAR_MAGE);
	char_ninja_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHAR_NINJA);

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