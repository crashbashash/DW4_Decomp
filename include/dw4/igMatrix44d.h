#ifndef DW4_IGMATRIX44D_H
#define DW4_IGMATRIX44D_H

#include "dw4/igMath.h"

extern "C" {
void FUN_00190250(long long *matrix);
void *memcpy(void *dest, const void *src, unsigned int size);
}

/* Alchemy's 4x4 double matrix: identity by default, or copied from four rows. */
struct igMatrix44d {
    igVec4d rows[4];

    igMatrix44d() { FUN_00190250((long long *)rows); }
    igMatrix44d(const igVec4d &row0, const igVec4d &row1, const igVec4d &row2, const igVec4d &row3) {
        memcpy(&rows[0], &row0, sizeof(igVec4d));
        memcpy(&rows[1], &row1, sizeof(igVec4d));
        memcpy(&rows[2], &row2, sizeof(igVec4d));
        memcpy(&rows[3], &row3, sizeof(igVec4d));
    }
};

#endif
