#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <time.h>
#include "logger.h"

static FILE* log_fp = NULL;

void init_logger(const char* filename) {
log_fp = fopen(filename, "w");
if (!log_fp) {
perror("Logger failed");
exit(1);
}
}

void log_event(const char* format, ...) {
if (!log_fp) return;
va_list args;
va_start(args, format);
vfprintf(log_fp, format, args);
fprintf(log_fp, "\n");
va_end(args);
fflush(log_fp);
}

void close_logger() {
if (log_fp) fclose(log_fp);
}
