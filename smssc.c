#include <limits.h>
#include <stdlib.h>
#include "smssc.h"

#if CHAR_BIT != 8
#error "CHAR_BIT != 8."
#endif

static           int c0_t[64];
static unsigned char c0_i[64];
static unsigned char c_pat[64][2][16];
static           int c_t[64];
static unsigned char c_i[64];
static unsigned char r_pat[256*34];

#define SPRITE_HEIGHT 8
#include "smssc8xH.c"
#undef SPRITE_HEIGHT
#define SPRITE_HEIGHT 16
#include "smssc8xH.c"
