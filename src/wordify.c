#include "pebble_os.h"
#include "pebble_app.h"
#include "wordify.h"

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

void min_to_str(int x, char* buffer, int size) {
	if(x % 10 == 0) {
		snprintf(buffer, size, "%s", tens[x / 10]);
	} else if(x < 10) {
		snprintf(buffer, size, "%s %s", ones[0], ones[x % 10]);
	} else if(x < 20) {
		snprintf(buffer, size, "%s", ones[x]);
	} else {
		snprintf(buffer, size, "%s-%s", tens[x / 10], ones[x % 10]);
	}
}

void date_to_str(int x, char* buffer, int size) {
	if(x % 10 == 0) {
		snprintf(buffer, size, "%s", ord_tens[x / 10]);
	} else if(x < 20) {
		snprintf(buffer, size, "%s", ord_ones[x]);
	} else {
		snprintf(buffer, size, "%s-%s", ord_tens[x / 10], ord_ones[x % 10]);
	}
}

void hour_to_str(int x, char* buffer, int size) {
	snprintf(buffer, size, "%s", ones[x==12 ? 12 : (x % 12)]);
}

void day_to_str(int x, char* buffer, int size) {
	snprintf(buffer, size, "%s", days[x]);
}

void month_to_str(int x, char* buffer, int size) {
	snprintf(buffer, size, "%s", months[x]);
}
