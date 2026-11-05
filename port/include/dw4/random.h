/* One engine-owned retail MT19937 stream, shared by Lua and native consumers. */
#ifndef DW4_RANDOM_H
#define DW4_RANDOM_H
#include <stdint.h>
typedef struct { uint32_t index, words[624]; } dw4_random;
/* Boot-only initialization: original 69069 seeding, constant 5150. */
void dw4_random_init(dw4_random *);
uint32_t dw4_random_next(dw4_random *);
/* SYSgetRandom uses unsigned EE division and returns a signed 32-bit integer.
 * Zero divisor preserves the dividend in HI; every call consumes one draw. */
int32_t dw4_random_mod(dw4_random *, int32_t modulus);
#endif
