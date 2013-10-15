#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "wordify.h"

#define UUID {0xC0,0x5E,0x85,0xD5,0x46,0x2E,0x4B,0xAA,0xAA,0xF8,0x40,0x9C,0x33,0xB0,0xDE,0x33}
#define BUFSIZE 16

PBL_APP_INFO(UUID,
		"Pixelated", "John Weachock",
		1, 0,
		DEFAULT_MENU_ICON,
		APP_INFO_WATCH_FACE);

Window window;
TextLayer hour_layer, min_layer, day_layer, month_layer, date_layer;
char hour_txt[BUFSIZE], min_txt[BUFSIZE];
char day_txt[BUFSIZE], month_txt[BUFSIZE], date_txt[BUFSIZE];

void tick() {
	PblTm current_time;

	get_time(&current_time);

	hour_to_str(current_time.tm_hour, hour_txt, BUFSIZE);
	min_to_str(current_time.tm_min, min_txt, BUFSIZE);
	day_to_str(current_time.tm_wday, day_txt, BUFSIZE);
	month_to_str(current_time.tm_mon, month_txt, BUFSIZE);
	date_to_str(current_time.tm_mday, date_txt, BUFSIZE);

	text_layer_set_text(&hour_layer, hour_txt);
	text_layer_set_text(&min_layer, min_txt);
	text_layer_set_text(&day_layer, day_txt);
	text_layer_set_text(&month_layer, month_txt);
	text_layer_set_text(&date_layer, date_txt);
}

void init(AppContextRef ctx) {
	window_init(&window, "Pixelated");
	window_stack_push(&window, true);

	text_layer_init(&hour_layer, GRect(0, 2, 144, 24));
	text_layer_set_text_alignment(&hour_layer, GTextAlignmentCenter);
	text_layer_set_font(&hour_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&min_layer, GRect(0, 26, 144, 24));
	text_layer_set_text_alignment(&min_layer, GTextAlignmentCenter);
	text_layer_set_font(&min_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&day_layer, GRect(0, 90, 144, 24));
	text_layer_set_text_alignment(&day_layer, GTextAlignmentCenter);
	text_layer_set_font(&day_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&month_layer, GRect(0, 116, 144, 24));
	text_layer_set_text_alignment(&month_layer, GTextAlignmentCenter);
	text_layer_set_font(&month_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	text_layer_init(&date_layer, GRect(0, 142, 144, 24));
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
