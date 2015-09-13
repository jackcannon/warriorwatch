#pragma once
#include <pebble.h>
	
void shared_init();
void prepare_layer(TextLayer *layer, Layer *page, GColor color, const char *text, const char *font_key);

typedef struct {
	char     name[10];
	char     desc[25];
	char     intro[25];
	GColor   bck_color;
	GColor   spt_color;
	bool     txt_color_is_white;
	uint32_t bck_image;
} Location;

Location locations[4];