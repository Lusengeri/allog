#include <stdio.h>

typedef enum {NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL} log_lev;

#define DEFAULT_LOG_LEVEL WARNING


struct logger {
	log_lev level;
	FILE *handler;
};

struct formatter{
	;
};

void init_logs(log_lev);
void log_add_handler(FILE *handler);
void log_remove_handler(FILE *handler);
void log_message(struct logger *log, log_lev level, char *log_string, ...);
