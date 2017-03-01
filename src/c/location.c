#include <pebble.h>
#include "shared.h"
#include "location.h"
#include "character.h"
#include "battle.h"
	
Window *location_window;
Layer *location_window_layer;
Layer *location_sidebar_layer;

static GBitmap *sidebar_icon_1_bitmap;
static GBitmap *sidebar_icon_2_bitmap;
static GBitmap *sidebar_icon_3_bitmap;
static BitmapLayer *sidebar_icon_1_bitmap_layer;
static BitmapLayer *sidebar_icon_2_bitmap_layer;
static BitmapLayer *sidebar_icon_3_bitmap_layer;

Window *loc_menu_window;
Layer *loc_menu_window_layer;

static GBitmap *loc_bg_bitmap;
static BitmapLayer *loc_bg_bitmap_layer;

TextLayer *text_location;
TextLayer *text_location_intro;

static SimpleMenuLayer *loc_menu_layer;
static SimpleMenuSection loc_menu_sect[1];
static SimpleMenuItem loc_menu_items[4];

static void draw_sidebar(Layer *layer, GContext *ctx) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "heap_bytes_used %d", (int) heap_bytes_used());
	APP_LOG(APP_LOG_LEVEL_DEBUG, "heap_bytes_free %d", (int) heap_bytes_free());
	APP_LOG(APP_LOG_LEVEL_DEBUG, "--- %d", 0);
	graphics_context_set_stroke_color(ctx, locations[location].spt_color);
	graphics_draw_line(ctx, GPoint(0, 0), GPoint(0, 168));
	
	graphics_draw_line(ctx, GPoint(0, 56), GPoint(37, 56));
	graphics_draw_line(ctx, GPoint(0, 111), GPoint(37, 111));
}

static void update_display_location() {
	gbitmap_destroy(loc_bg_bitmap);
	loc_bg_bitmap = gbitmap_create_with_resource(locations[location].bck_image);
	window_set_background_color(location_window, locations[location].bck_color);
	
	if (locations[location].txt_color_is_white) {
		text_layer_set_text_color(text_location_intro, GColorWhite);
		text_layer_set_text_color(text_location, GColorWhite);
	} else {
		text_layer_set_text_color(text_location_intro, GColorBlack);
		text_layer_set_text_color(text_location, GColorBlack);
	}
	
	text_layer_set_text(text_location_intro, locations[location].intro);
	text_layer_set_text(text_location, locations[location].name);
}

static void select_location(int index, void *ctx) {
	location = index;
	persist_write_int(PERSIST_LOCATION, location);
	update_display_location();
	window_stack_pop(true);
// 	window_stack_push(location_window, true);
}

static void loc_menu_load() {
	for (int i = 0; i < (int)(sizeof(locations) / sizeof(locations[0])); i++) {
		loc_menu_items[i] = (SimpleMenuItem) {
			.title = locations[i].name,
			.subtitle = locations[i].desc,
			.callback = select_location,
		};
	}
	loc_menu_sect[0] = (SimpleMenuSection) {
		.items = loc_menu_items,
		.num_items = sizeof(loc_menu_items) / sizeof(loc_menu_items[0])
	};
	
	GRect bounds = layer_get_frame(loc_menu_window_layer);

	loc_menu_layer = simple_menu_layer_create(bounds, loc_menu_window, loc_menu_sect, 1, NULL);
	MenuLayer *loc_menu = simple_menu_layer_get_menu_layer(loc_menu_layer);
	menu_layer_set_normal_colors(loc_menu, GColorPastelYellow, GColorBulgarianRose); // GColorPastelYellow
	menu_layer_set_highlight_colors(loc_menu, GColorWindsorTan, GColorPastelYellow);
	simple_menu_layer_set_selected_index(loc_menu_layer, location, false);
	menu_layer_pad_bottom_enable(loc_menu, false);
	layer_add_child(loc_menu_window_layer, simple_menu_layer_get_layer(loc_menu_layer));
}
static void loc_menu_unload() {
	simple_menu_layer_destroy(loc_menu_layer);
}
static void open_loc_menu() {
	window_stack_push(loc_menu_window, true);
}


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	character_open();
}
static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	open_loc_menu();
}
static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	battle_open();
}
static void click_config_provider(void *context) {
	window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
	window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
	window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}



static void window_load(Window *window) {
	window_set_background_color(window, GColorWhite);
	location_window_layer = window_get_root_layer(location_window);
	loc_menu_window_layer = window_get_root_layer(loc_menu_window);

	// set up location page
	loc_bg_bitmap_layer = bitmap_layer_create(GRect(0, 0, 107, 168));
	
	gbitmap_destroy(loc_bg_bitmap);
	loc_bg_bitmap = gbitmap_create_with_resource(locations[location].bck_image);
	
	bitmap_layer_set_bitmap(loc_bg_bitmap_layer, loc_bg_bitmap);
	bitmap_layer_set_compositing_mode(loc_bg_bitmap_layer, GCompOpSet);
	layer_add_child(location_window_layer, bitmap_layer_get_layer(loc_bg_bitmap_layer));

	text_location_intro = text_layer_create(GRect(0, 0, 107, 20));
	text_location = text_layer_create(GRect(0, 14, 107, 30));
	prepare_layer(text_location_intro, location_window_layer, GColorBlack, locations[location].intro, FONT_KEY_GOTHIC_18_BOLD);
	prepare_layer(text_location, location_window_layer, GColorBlack, locations[location].name, FONT_KEY_GOTHIC_28_BOLD);
	update_display_location();
	
	sidebar_icon_1_bitmap_layer = bitmap_layer_create(GRect(110, 13, 32, 32));
	sidebar_icon_2_bitmap_layer = bitmap_layer_create(GRect(110, 69, 32, 32));
	sidebar_icon_3_bitmap_layer = bitmap_layer_create(GRect(110, 125, 32, 32));
	bitmap_layer_set_bitmap(sidebar_icon_1_bitmap_layer, sidebar_icon_1_bitmap);
	bitmap_layer_set_bitmap(sidebar_icon_2_bitmap_layer, sidebar_icon_2_bitmap);
	bitmap_layer_set_bitmap(sidebar_icon_3_bitmap_layer, sidebar_icon_3_bitmap);
	bitmap_layer_set_compositing_mode(sidebar_icon_1_bitmap_layer, GCompOpSet);
	bitmap_layer_set_compositing_mode(sidebar_icon_2_bitmap_layer, GCompOpSet);
	bitmap_layer_set_compositing_mode(sidebar_icon_3_bitmap_layer, GCompOpSet);
	layer_add_child(location_window_layer, bitmap_layer_get_layer(sidebar_icon_1_bitmap_layer));
	layer_add_child(location_window_layer, bitmap_layer_get_layer(sidebar_icon_2_bitmap_layer));
	layer_add_child(location_window_layer, bitmap_layer_get_layer(sidebar_icon_3_bitmap_layer));
	
	location_sidebar_layer = layer_create(GRect(107, 0, 37, 168));
	layer_set_update_proc(location_sidebar_layer, draw_sidebar);
	layer_add_child(location_window_layer, location_sidebar_layer);
}
static void window_unload(Window *window) {
	gbitmap_destroy(loc_bg_bitmap);
	bitmap_layer_destroy(loc_bg_bitmap_layer);
	
	text_layer_destroy(text_location_intro);
	text_layer_destroy(text_location);
	
	bitmap_layer_destroy(sidebar_icon_1_bitmap_layer);
	bitmap_layer_destroy(sidebar_icon_2_bitmap_layer);
	bitmap_layer_destroy(sidebar_icon_3_bitmap_layer);
	
	layer_destroy(location_sidebar_layer);
	
	layer_destroy(location_window_layer);
	layer_destroy(loc_menu_window_layer);
}



void location_init(void) {
	sidebar_icon_1_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICON_MAP);
	sidebar_icon_2_bitmap = gbitmap_create_with_resource(RESOURCE_ID_CHAR_WARRIOR);
	sidebar_icon_3_bitmap = gbitmap_create_with_resource(RESOURCE_ID_ICON_BATTLE);

	if (persist_exists(PERSIST_LOCATION)) {
		location = persist_read_int(PERSIST_LOCATION);
	}
	
	location_window = window_create();
	loc_menu_window = window_create();

	window_set_click_config_provider(location_window, click_config_provider);
	window_set_window_handlers(location_window, (WindowHandlers) {
		.load   = window_load,
		.unload = window_unload,
	});
	window_set_window_handlers(loc_menu_window, (WindowHandlers) {
		.load   = loc_menu_load,
		.unload = loc_menu_unload,
	});
}
void location_deinit(void) {
	gbitmap_destroy(sidebar_icon_1_bitmap);
	gbitmap_destroy(sidebar_icon_2_bitmap);
	gbitmap_destroy(sidebar_icon_3_bitmap);
	persist_write_int(PERSIST_LOCATION, location);
	window_destroy(loc_menu_window);
	window_destroy(location_window);
}
void location_open() {
	if (!location_window) {
		location_init();
	}
	window_stack_push(location_window, true);	
}
