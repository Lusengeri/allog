#include <stdio.h>

typedef enum {NOTSET, DEBUG, INFO, WARNING, ERROR, CRITICAL} log_lev;

#define DEFAULT_LOG_LEVEL WARNING

struct handler{
	int (*log_to) (struct handler*, char*, ...);	
	FILE *file;
	char *domain_name;
	char *uri;
	char *method;
};

struct log_obj {
	log_lev level;
	struct handler *handlr;
	// List of *handlers;
};

struct formatter{
	;
};

//void init_logs(log_lev);
void set_log_level(struct log_obj*, log_lev);
void set_handler(struct log_obj*, struct handler*);
void make_file_handler(struct handler*, char *file_name);
void new_syslog_handler(void);
void log_message(struct log_obj *log, log_lev level, char *log_string, ...);
