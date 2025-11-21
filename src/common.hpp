#pragma once

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef unsigned char uchar;

#ifndef NDEBUG
#define DEBUG_PRINT(...) fprintf( stderr, __VA_ARGS__ )
#else
#define DEBUG_PRINT(...) do{ } while ( 0 )
#endif

// print error message and quit (not dependent on NDEBUG)
#define ERROR(...) { fprintf(stderr, __VA_ARGS__); exit(1); }

