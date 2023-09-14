#include "debug.h"

#include <stdarg.h>

#define ANSI_RED    "\x1B[31m"
#define ANSI_GREEN  "\x1B[32m"
#define ANSI_YELLOW "\x1B[33m"
#define ANSI_RESET  "\x1B[0m"


inline void
WARNING(FILE * stream, const char * format, ...)                          
{                         
    va_list args;
    va_start(args, format);
                              
    fprintf(stream, ANSI_YELLOW"warning: "ANSI_RESET);    
    vfprintf(stream, format, args);

    va_end(args);                
}


inline void
ERROR(FILE * stream, const char * format, ...)                          
{                         
    va_list args;
    va_start(args, format);
                              
    fprintf(stream, ANSI_RED"error: "ANSI_RESET);    
    vfprintf(stream, format, args);

    va_end(args);                
}


inline void
FATAL(FILE * stream, const char * format, ...)                          
{                         
    va_list args;
    va_start(args, format);
                              
    fprintf(stream, ANSI_RED"fatal error: "ANSI_RESET);    
    vfprintf(stream, format, args);

    va_end(args);                
}

