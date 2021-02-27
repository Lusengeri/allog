#ifndef ALLOG
#define ALLOG

#include <stdio.h>
#include <stdbool.h>

typedef enum {NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL} log_lev;

struct log_handler{
	void (*log_to) (struct log_handler*, log_lev, char*, va_list);	
};

struct file_handler{
	struct log_handler base;
	FILE *file;
};

typedef struct log_obj {
	log_lev level;
	struct log_handler *handler;
	void (*add_handler)(struct log_obj*, struct log_handler*);
	void (*set_level) (struct log_obj*, log_lev);
	log_lev (*get_effective_level)(struct log_obj*);
	bool (*is_enabled_for_level)(struct log_obj*, log_lev);
} log_obj;

log_obj *new_log_obj(log_lev);	
void set_level(struct log_obj*, log_lev);
void add_handler(struct log_obj*, struct log_handler*);
struct file_handler* new_file_handler(char *file_name);
struct file_handler* new_stream_handler(FILE*);
struct file_handler* new_syslog_handler();
void log_message(struct log_obj *log, log_lev level, char *log_string, ...);
#endif
