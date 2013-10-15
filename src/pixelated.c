#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#define UUID {0xC0,0x5E,0x85,0xD5,0x46,0x2E,0x4B,0xAA,0xAA,0xF8,0x40,0x9C,0x33,0xB0,0xDE,0x33}

char* hours[] = {"twelve", "one", "two", "three", "four", "five", "six",
	"seven", "eight", "nine", "ten", "eleven"};
char* ones[] = {"oh", "one", "two", "three", "four", "five", "six", "seven",
	"eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
	"sixteen", "seventeen", "eighteen", "nineteen"};
char* tens[] = {"o'clock", "ten", "twenty", "thirty", "forty", "fifty"};
char* ord_ones[] = {"zeroth", "first", "second", "third", "fourth", "fifth",
	"sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth",
	"thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth",
	"eighteenth", "nineteenth"};
char* ord_tens[] = {"zeroth", "tenth", "twentieth", "thirtieth"};

char* days[] = {"sunday", "monday", "tuesday", "wednesday", "thursday",
	"friday", "saturday"};
char* months[] = {"january", "february", "march", "april", "may", "june", "july",
	"august", "september", "october", "november", "december"};

PBL_APP_INFO(UUID,
		"Pixelated", "John Weachock",
		1, 0,
		DEFAULT_MENU_ICON,
		APP_INFO_WATCH_FACE);

Window window;
TextLayer hour_layer, min_layer, day_layer, month_layer, date_layer;
char hour_txt[16], min_txt[16], day_txt[16], month_txt[16], date_txt[16];

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

void date_to_str(int x, char* buffer, int size) {
	if(x % 10 == 0) {
		snprintf(buffer, size, "%s", ord_tens[x / 10]);
	} else if(x < 20) {
		snprintf(buffer, size, "%s", ord_ones[x]);
	} else {
		snprintf(buffer, size, "%s %s", ord_tens[x / 10], ord_ones[x % 10]);
	}
}

void tick() {
	PblTm current_time;

	get_time(&current_time);

	snprintf(hour_txt, 16, "%s", hours[current_time.tm_hour % 12]);
	min_to_str(current_time.tm_min, min_txt, 16);
	snprintf(day_txt, 16, "%s", days[current_time.tm_wday]);
	snprintf(month_txt, 16, "%s", months[current_time.tm_mon]);
	date_to_str(current_time.tm_mday, date_txt, 16);

	text_layer_set_text(&hour_layer, hour_txt);
	text_layer_set_text(&min_layer, min_txt);
	text_layer_set_text(&day_layer, day_txt);
	text_layer_set_text(&month_layer, month_txt);
	text_layer_set_text(&date_layer, date_txt);
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

	text_layer_init(&day_layer, GRect(0, 64, 144, 30));
	text_layer_set_text_alignment(&day_layer, GTextAlignmentCenter);
	text_layer_set_font(&day_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&month_layer, GRect(0, 96, 144, 30));
	text_layer_set_text_alignment(&month_layer, GTextAlignmentCenter);
	text_layer_set_font(&month_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&date_layer, GRect(0, 128, 144, 30));
	text_layer_set_text_alignment(&date_layer, GTextAlignmentCenter);
	text_layer_set_font(&date_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	layer_add_child(&window.layer, &hour_layer.layer);
	layer_add_child(&window.layer, &min_layer.layer);
	layer_add_child(&window.layer, &day_layer.layer);
	layer_add_child(&window.layer, &month_layer.layer);
	layer_add_child(&window.layer, &date_layer.layer);

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
