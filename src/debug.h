#ifndef _DEBUG_H_
#define _DEBUG_H_ 


#include <stdio.h>


void
WARNING(
    FILE * stream
    , const char * format
    , ...);

 
void
ERROR(
    FILE * stream
    , const char * format
    , ...);


void
FATAL(
    FILE * stream
    , const char * format
    , ...);


#endif
