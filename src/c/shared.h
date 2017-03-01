#pragma once
#include <pebble.h>
	
/* Persistent memory keys */
#define PERSIST_LOCATION 10
	
/* Location keys */
#define LOC_WOODS 0
#define LOC_TOWN 1
#define LOC_BEACH 2
#define LOC_CASTLE 3
	
/* Enemy/Monster keys */
#define ENEMY_RAT         0
#define ENEMY_GIANTRAT    1
#define ENEMY_IMP         2
#define ENEMY_GIANTSPIDER 3

/* Structs */
typedef struct {
	char      name[25];
	int       key;
	int       hp_min;
	int       hp_max;
	int       lvl_min;
	int       lvl_max;
	uint32_t  icn_image;
} EnemyType;
typedef struct {
	EnemyType enemytype;
	int       hp;
	int       hp_full;
	int       lvl;
} Enemy;
typedef struct {
	char      name[10];
	char      desc[25];
	char      intro[25];
	GColor    bck_color;
	GColor    spt_color;
	GColor    bck_battle_color;
	GColor    spt_battle_color;
	bool      txt_color_is_white;
	uint32_t  bck_image;
	uint32_t  bck_battle_image;
} Location;

/* Functions */
void shared_init();
void itoa1();
void itoa2();
void prepare_layer(TextLayer *layer, Layer *page, GColor color, const char *text, const char *font_key);
Enemy generateEnemy(int enemyTypeId);

/* Variables */
EnemyType enemyTypes[4];
Location locations[4];
int page;
int location;