#include <pebble.h>
#include "shared.h"

void shared_init() {
	page = 0;
	location = 0;
	/* name, key, hp_min, hp_max, lvl_min, lvl_max, icn_image; */
	enemyTypes[ENEMY_RAT] =         (EnemyType) { "Rat", ENEMY_RAT, 3, 5, 1, 2, RESOURCE_ID_ENEMY_RAT };
	enemyTypes[ENEMY_GIANTRAT] =    (EnemyType) { "Giant Rat", ENEMY_GIANTRAT, 8, 10, 3, 5, RESOURCE_ID_ENEMY_GIANTRAT };
	enemyTypes[ENEMY_IMP] =         (EnemyType) { "Imp", ENEMY_IMP, 5, 8, 2, 4, RESOURCE_ID_ENEMY_IMP };
	enemyTypes[ENEMY_GIANTSPIDER] = (EnemyType) { "Giant Spider", ENEMY_GIANTSPIDER, 5, 8, 2, 4, RESOURCE_ID_ENEMY_GIANTSPIDER };
	
	locations[LOC_WOODS] =  (Location) { "Woods", "in the dark, dark woods", "You are in the", GColorMayGreen, GColorDarkGreen, GColorMayGreen, GColorDarkGreen, true, RESOURCE_ID_BG_WOODS, RESOURCE_ID_BG_BATTLE_WOODS };
	locations[LOC_TOWN] =   (Location) { "Town", "a pleasant lil' town", "You are in the", GColorCeleste, GColorCyan, GColorArmyGreen, GColorLimerick, false, RESOURCE_ID_BG_TOWN, RESOURCE_ID_BG_BATTLE_TOWN };
	locations[LOC_BEACH] =  (Location) { "Beach", "chillax by the sea", "You are on the", GColorRajah, GColorWindsorTan, GColorRajah, GColorWindsorTan, false, RESOURCE_ID_BG_BEACH, RESOURCE_ID_BG_BATTLE_BEACH };
	locations[LOC_CASTLE] = (Location) { "Castle", "a towering shadow", "You are at the", GColorOxfordBlue, GColorBlack, GColorOxfordBlue, GColorBlack, true, RESOURCE_ID_BG_CASTLE, RESOURCE_ID_BG_BATTLE_CASTLE };
}

void itoa1(int num, char* buffer) {
  const char digits[10] = "0123456789";
  buffer[0] = digits[num % 10];
}
void itoa2(int num, char* buffer) {
  const char digits[10] = "0123456789";
  if(num > 99) {
    buffer[0] = '9';
    buffer[1] = '9';
    return;
  } else if(num > 9) {
    buffer[0] = digits[num / 10];
  } else {
    buffer[0] = '0';
  }
  buffer[1] = digits[num % 10];
}

void prepare_layer(TextLayer *layer, Layer *page, GColor color, const char *text, const char *font_key) {
	text_layer_set_background_color(layer, GColorClear);
	text_layer_set_text_color(layer, color);
	text_layer_set_text_alignment(layer, GTextAlignmentCenter);
	text_layer_set_text(layer, text);
	text_layer_set_font(layer, fonts_get_system_font(font_key));
	layer_add_child(page, text_layer_get_layer(layer));
}

Enemy generateEnemy(int enemyTypeId) {
	EnemyType enemytype = enemyTypes[enemyTypeId];
	int hp = (rand() % (enemytype.hp_max - enemytype.hp_min)) + enemytype.hp_min;
	Enemy en = (Enemy) {
		.enemytype = enemytype,
		.hp = hp,
		.hp_full = hp,
		.lvl = (rand() % (enemytype.lvl_max - enemytype.lvl_min)) + enemytype.lvl_min,
	};
	return en;
}