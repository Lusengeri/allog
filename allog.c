#include "allog.h" 
#include <time.h>
#include <string.h>
#include <stdarg.h>

char *level_strings[] = {"NOTSET", "DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"};
char *get_current_time_string();

void log_message(struct logger *log, log_lev level, char *log_string, ...)
{	
	va_list arg_ptr;
	va_start(arg_ptr, log_string);

	char full_log_string[2048];
	vsprintf(full_log_string, log_string, arg_ptr);

	if (log == NULL) {
		struct logger def = {DEFAULT_LOG_LEVEL, stderr};	
		log = &def;
	}

	if (level >= log->level) {
		fprintf(log->handler, "[%s]:[%s]:%s\n", get_current_time_string(), level_strings[level], full_log_string);
	}

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
