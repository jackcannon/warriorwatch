#include <pebble.h>
#include "shared.h"
#include "battle.h"
#include "location.h"

Window *battle_window;
Layer *battle_window_layer;
Layer *battle_sidebar_layer;
Layer *names_layer;

TextLayer *vs_layer;

static GBitmap *bg_bitmap;
static BitmapLayer *bg_bitmap_layer;

typedef struct {
	GRect              location;
	GBitmap            *bitmap;
	BitmapLayer        *bitmap_layer;
	TextLayer          *name_layer;
} Slot;

Slot slots[5];
GRect slot_locations[5];
GRect ally_slot_locations[3];


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	location_open();
}
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	layer_add_child(battle_window_layer, names_layer);
}
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	layer_remove_from_parent(names_layer);
}
static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void draw_sidebar(Layer *layer, GContext *ctx) {
	graphics_context_set_stroke_color(ctx, locations[location].spt_battle_color);
	graphics_draw_line(ctx, GPoint(0, 0), GPoint(0, 168));
	
	graphics_draw_line(ctx, GPoint(0, 56), GPoint(37, 56));
	graphics_draw_line(ctx, GPoint(0, 111), GPoint(37, 111));
}

static void populate_slot(int slot_num, Enemy enemy) {
	struct GBitmap *bitmap = gbitmap_create_with_resource(enemy.enemytype.icn_image);
	
	GRect loc = slot_locations[slot_num];
	
	struct BitmapLayer *bitmap_layer = bitmap_layer_create(loc);
	bitmap_layer_set_bitmap(bitmap_layer, bitmap);
	bitmap_layer_set_compositing_mode(bitmap_layer, GCompOpSet);
	bitmap_layer_set_alignment(bitmap_layer, GAlignBottom);
	layer_add_child(battle_window_layer, bitmap_layer_get_layer(bitmap_layer));
	
// 	static char lvl_str[] = "Lvl.  ";
// 	static char hp_str[] = "  /  ";
// 	itoa1(enemy.lvl, &lvl_str[5]);
// 	itoa1(enemy.hp, &hp_str[0]);
// 	itoa1(enemy.hp_full, &hp_str[3]);
	
// 	TextLayer *name_layer;
// 	if (slot_num < 3) {
// 		name_layer = text_layer_create(GRect(loc.origin.x, loc.origin.y + 32, 32, 14));
// 	} else {
// 		name_layer = text_layer_create(GRect(loc.origin.x, loc.origin.y - 20, 32, 14));
// 	}
	
	TextLayer *name_layer = text_layer_create(GRect(2, 42 + (slot_num * 9), 103, 14));
	
	slots[slot_num] = (Slot) {
		.location = loc,
		.bitmap = bitmap,
		.bitmap_layer = bitmap_layer,
		.name_layer = name_layer,
	};
	
	prepare_layer(name_layer, names_layer, GColorBlack, enemyTypes[enemy.enemytype.key].name, FONT_KEY_GOTHIC_09);
	if (locations[location].txt_color_is_white) {
		text_layer_set_text_color(name_layer, GColorWhite);
	} else {
		text_layer_set_text_color(name_layer, GColorBlack);
	}
	text_layer_set_text_alignment(name_layer, GTextAlignmentLeft);
}

static void window_load(Window *window) {
	window_set_background_color(window, locations[location].bck_battle_color);
	battle_window_layer = window_get_root_layer(battle_window);

	
	bg_bitmap_layer = bitmap_layer_create(GRect(0, 0, 107, 168));

	bg_bitmap = gbitmap_create_with_resource(locations[location].bck_battle_image);
	
	bitmap_layer_set_bitmap(bg_bitmap_layer, bg_bitmap);
	bitmap_layer_set_compositing_mode(bg_bitmap_layer, GCompOpSet);
	layer_add_child(battle_window_layer, bitmap_layer_get_layer(bg_bitmap_layer));
	
	
	names_layer = layer_create(GRect(0, 0, 107, 168));
	
	vs_layer = text_layer_create(GRect(0, 75, 107, 14));
	prepare_layer(vs_layer, names_layer, GColorBlack, "VS", FONT_KEY_GOTHIC_14_BOLD);
	if (locations[location].txt_color_is_white) {
		text_layer_set_text_color(vs_layer, GColorWhite);
	} else {
		text_layer_set_text_color(vs_layer, GColorBlack);
	}
	
	Enemy foes[] = {
		generateEnemy(ENEMY_RAT),
		generateEnemy(ENEMY_IMP),
		generateEnemy(ENEMY_GIANTSPIDER),
		generateEnemy(ENEMY_GIANTRAT),
		generateEnemy(ENEMY_GIANTRAT),
	};
	
	for (int i = 0; i < 5; i++) {
		populate_slot(i, foes[i]);
	}
	
	battle_sidebar_layer = layer_create(GRect(107, 0, 37, 168));
	layer_set_update_proc(battle_sidebar_layer, draw_sidebar);
	layer_add_child(battle_window_layer, battle_sidebar_layer);
}



void battle_init(void) {
	battle_window = window_create();
	
	slot_locations[0] = GRect( 3,  2, 32, 32);
	slot_locations[1] = GRect(38,  2, 32, 32);
	slot_locations[2] = GRect(73,  2, 32, 32);
	slot_locations[3] = GRect(20, 18, 32, 32);
	slot_locations[4] = GRect(55, 18, 32, 32);
	
	ally_slot_locations[0] = GRect( 3, 130, 32, 32);
	ally_slot_locations[1] = GRect(38, 130, 32, 32);
	ally_slot_locations[2] = GRect(73, 130, 32, 32);

	window_set_click_config_provider(battle_window, click_config_provider);
	window_set_window_handlers(battle_window, (WindowHandlers) {
		.load = window_load,
	});
}
void battle_deinit(void) {
	gbitmap_destroy(bg_bitmap);
	window_destroy(battle_window);
}
void battle_open() {
	if (!battle_window) {
		battle_init();
	} 
	window_stack_push(battle_window, true);	
}