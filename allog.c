#include "allog.h" 
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <syslog.h>

char *level_strings[] = {"NOTSET", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
char *get_current_time_string();

log_obj *new_log_obj(log_lev lev)
{
	log_obj *new = malloc(sizeof(log_obj));
	new->level = lev;
	new->handler_list = new_list();	
	return new;
}

void set_level(struct log_obj *logger, log_lev lev)
{
	logger->level = lev;	
}

void add_handler(struct log_obj *logger, void *handler)
{
	add_obj(logger->handler_list, (struct log_handler*)handler);
}

void log_message(struct log_obj *logger, log_lev level, char *log_string, ...)
{
	if (level < logger->level)
		return;

	va_list arg_ptr;
	va_start(arg_ptr, log_string);

	obj_list_node *iter;	
	for (iter = (logger->handler_list->head.next_obj); (iter->this_obj) != NULL; iter = iter->next_obj) {
		struct log_handler *handler = (struct log_handler*) (iter->this_obj);
		handler->log_to(handler, level, log_string, arg_ptr);
	}

	va_end(arg_ptr);
	return;
}

void log_message_to_file(struct log_handler *handler, log_lev level, char *log_string, va_list arg_ptr)
{	
	struct file_handler *f_handler = (struct file_handler*) handler;
	char full_log_string[2048];
	vsprintf(full_log_string, log_string, arg_ptr);
	fprintf(f_handler->file, "[%s]:[%s]:%s\n", get_current_time_string(), level_strings[level], full_log_string);
	return;
}


void log_message_to_syslog(struct log_handler *handler, log_lev level, char *log_string, va_list arg_ptr)
{
	int priority;

	switch (level){
		case DEBUG: 
			priority = LOG_DEBUG;
			break;
		case INFO: 
			priority = LOG_INFO;
			break;
		case WARNING:
			priority = LOG_WARNING;
			break;
		case ERROR:
			priority = LOG_ERR;
			break;
		case CRITICAL:
			priority = LOG_CRIT;
			break;
		default:
			priority = LOG_DEBUG;
	}

	vsyslog(priority, log_string, arg_ptr);

}
struct file_handler* new_file_handler(char *file_name)
{
	struct file_handler *new = malloc(sizeof(struct file_handler));

	FILE *log_file = fopen(file_name, "a");
	
	if (log_file == NULL) {
		fprintf(stderr, "fopen(%s) failed: %s\n", file_name, strerror(errno));
		exit(EXIT_FAILURE);
	}

	new->base.log_to = log_message_to_file;
	new->file = log_file;
	return new;
}

struct file_handler* new_stream_handler(FILE *file_stream)
{
	struct file_handler *new = malloc(sizeof(struct file_handler));
	//What error handling's required here?
	new->base.log_to = log_message_to_file;
	new->file = file_stream;
	return new;
}

struct log_handler* new_syslog_handler()
{
	struct log_handler *new = malloc(sizeof(struct log_handler));
	new->log_to = log_message_to_syslog;
}

char *get_current_time_string()
{
	time_t raw_time;
	time(&raw_time);
	struct tm *time_now;
	time_now = localtime(&raw_time);
	return strtok(asctime(time_now), "\n");
}
