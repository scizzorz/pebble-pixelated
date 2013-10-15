#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#define UUID {0xC0,0x5E,0x85,0xD5,0x46,0x2E,0x4B,0xAA,0xAA,0xF8,0x40,0x9C,0x33,0xB0,0xDE,0x33}

char* ones[] = {"oh", "one", "two", "three", "four", "five", "six", "seven", "eight",
	"nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
	"sixteen", "seventeen", "eighteen", "nineteen"};
char* tens[] = {"twenty", "thirty", "forty", "fifty"};

PBL_APP_INFO(UUID,
	"Pixelated", "John Weachock",
	1, 0, /* App version */
	DEFAULT_MENU_ICON,
	APP_INFO_WATCH_FACE);

Window window;
TextLayer time_layer;

void init(AppContextRef ctx) {
	window_init(&window, "Pixelated");
	window_stack_push(&window, true /* Animated */);

	text_layer_init(&time_layer, GRect(0, 65, 144, 30));
	text_layer_set_text_alignment(&time_layer, GTextAlignmentCenter);
	text_layer_set_text(&time_layer, ones[10]);
	text_layer_set_font(&time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));

	layer_add_child(&window.layer, &time_layer.layer);
}

void pbl_main(void *params) {
	PebbleAppHandlers handlers = {
		.init_handler = &init
	};
	app_event_loop(params, &handlers);
}
