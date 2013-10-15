#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#define UUID {0xC0,0x5E,0x85,0xD5,0x46,0x2E,0x4B,0xAA,0xAA,0xF8,0x40,0x9C,0x33,0xB0,0xDE,0x33}

char* hours[] = {"twelve", "one", "two", "three", "four", "five", "six",
	"seven", "eight", "nine", "ten", "eleven"};
char* ones[] = {"oh", "one", "two", "three", "four", "five", "six", "seven", "eight",
	"nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
	"sixteen", "seventeen", "eighteen", "nineteen"};
char* tens[] = {"o'clock", "ten", "twenty", "thirty", "forty", "fifty"};

PBL_APP_INFO(UUID,
		"Pixelated", "John Weachock",
		1, 0,
		DEFAULT_MENU_ICON,
		APP_INFO_WATCH_FACE);

Window window;
TextLayer hour_layer, min_layer, day_layer, date_layer;
char hour_txt[32], min_txt[32], day_txt[16], date_txt[16];

void min_to_str(int x, char* buffer, int size) {
	if(x % 10 == 0) {
		snprintf(buffer, size, "%s", tens[x / 10]);
	} else if(x < 10) {
		snprintf(buffer, size, "%s %s", ones[0], ones[x % 10]);
	} else if(x < 20) {
		snprintf(buffer, size, "%s", ones[x]);
	} else {
		snprintf(buffer, size, "%s %s", tens[x / 10], ones[x % 10]);
	}
}

void tick() {
	PblTm current_time;

	get_time(&current_time);

	snprintf(hour_txt, 32, "%s",
		hours[current_time.tm_hour % 12]);

	min_to_str(current_time.tm_min, min_txt, 32);

	text_layer_set_text(&hour_layer, hour_txt);
	text_layer_set_text(&min_layer, min_txt);
}

void init(AppContextRef ctx) {
	window_init(&window, "Pixelated");
	window_stack_push(&window, true);

	text_layer_init(&hour_layer, GRect(0, 2, 144, 30));
	text_layer_set_text_alignment(&hour_layer, GTextAlignmentCenter);
	text_layer_set_font(&hour_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&min_layer, GRect(0, 32, 144, 30));
	text_layer_set_text_alignment(&min_layer, GTextAlignmentCenter);
	text_layer_set_font(&min_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	layer_add_child(&window.layer, &hour_layer.layer);
	layer_add_child(&window.layer, &min_layer.layer);

	tick();
}

void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &init,
		.tick_info = {
			.tick_handler = &tick,
			.tick_units = MINUTE_UNIT
		},
	};
	app_event_loop(params, &handlers);
}
