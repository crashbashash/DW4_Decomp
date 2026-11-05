#ifndef DW4_PLAYERPOINT_H
#define DW4_PLAYERPOINT_H
#include <stdint.h>
#include <stddef.h>
/* Resolve the authored bePoint01Info -> group -> player transform chain.
 * Uses the raw local matrix copied by retail 39c1c0, not scene traversal order.
 * A too-large group falls back to zero. Host-invalid negative groups, absent
 * player rows and malformed assets fail without changing the output matrix. */
int dw4_playerpoint_matrix(const void *blob,size_t size,int32_t group,unsigned player,float matrix[16]);
#endif
