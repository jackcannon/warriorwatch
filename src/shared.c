#include <pebble.h>
#include "shared.h"

void shared_init() {
	locations[0] = (Location) { "Woods", "in the dark, dark woods", "You are in the", GColorMayGreen, GColorDarkGreen, true, RESOURCE_ID_BG_TREES };
	locations[1] = (Location) { "Town", "a pleasant lil' town", "You are in the", GColorCeleste, GColorCyan, false, RESOURCE_ID_BG_TOWN };
	locations[2] = (Location) { "Beach", "chillax by the sea", "You are on the", GColorRajah, GColorWindsorTan, false, RESOURCE_ID_BG_BEACH };
	locations[3] = (Location) { "Castle", "a towering shadow", "You are at the", GColorOxfordBlue, GColorBlack, true, RESOURCE_ID_BG_CASTLE };
}

void prepare_layer(TextLayer *layer, Layer *page, GColor color, const char *text, const char *font_key) {
	text_layer_set_background_color(layer, GColorClear);
	text_layer_set_text_color(layer, color);
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	text_layer_set_text(layer, text);
	text_layer_set_font(layer, fonts_get_system_font(font_key));
	layer_add_child(page, text_layer_get_layer(layer));
}