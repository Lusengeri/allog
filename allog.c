#include "allog.h" 
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>

char *level_strings[] = {"NOTSET", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
char *get_current_time_string();

void set_log_level(struct log_obj* logger, log_lev lev)
{
	logger->level = lev;	
}

void set_handler(struct log_obj* logger, struct handler *handlr)
{
	logger->handlr = handlr;
}

void log_message_to_file(FILE *log_file, log_lev level, char *log_string, va_list arg_ptr)
{	
	char full_log_string[2048];
	vsprintf(full_log_string, log_string, arg_ptr);
	fprintf(log_file, "[%s]:[%s]:%s\n", get_current_time_string(), level_strings[level], full_log_string);
	return;
}

void make_file_handler(struct handler *handlr, char *file_name)
{
	FILE *log_file = fopen(file_name, "a");
	
	if (log_file == NULL) {
		fprintf(stderr, "fopen(%s) failed: %s\n", file_name, strerror(errno));
		exit(EXIT_FAILURE);
	}

	handlr->file = log_file;
	//handlr->log_to = log_message_to_file;
}

void log_message(struct log_obj *log, log_lev level, char *log_string, ...)
{	
	va_list arg_ptr;
	va_start(arg_ptr, log_string);

	if (log->handlr->file != NULL)
		log_message_to_file(log->handlr->file, log->level, log_string, arg_ptr);

	va_end(arg_ptr);
	return;
}

char *get_current_time_string()
{
	time_t raw_time;
	time(&raw_time);
	struct tm *time_now;
	time_now = localtime(&raw_time);
	return strtok(asctime(time_now), "\n");
}
