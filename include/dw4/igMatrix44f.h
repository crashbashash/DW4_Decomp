#ifndef DW4_IGMATRIX44F_H
#define DW4_IGMATRIX44F_H

#include "dw4/igMath.h"

extern "C" {
void igMatrix44f_SetIdentity(float *matrix);
void FUN_00130e90(float *matrix, const igVec4f *row0, const igVec4f *row1, const igVec4f *row2,
                  const igVec4f *row3);
}

/* Alchemy's 4x4 float matrix. Its constructors are the library's out-of-line identity and
 * four-row setters. */
struct igMatrix44f {
    float m[16];

    igMatrix44f() { igMatrix44f_SetIdentity(m); }
    igMatrix44f(const igVec4f &row0, const igVec4f &row1, const igVec4f &row2, const igVec4f &row3) {
        FUN_00130e90(m, &row0, &row1, &row2, &row3);
    }
};

#endif
