#ifndef DW4_IGMATRIX44F_H
#define DW4_IGMATRIX44F_H

#include "dw4/igMath.h"

extern "C" {
void igMatrix44f_SetIdentity(float *matrix);
void igMatrix44f_FromRows(float *matrix, const igVec4f *row0, const igVec4f *row1, const igVec4f *row2,
                  const igVec4f *row3);
/* The matrices are 16 floats, row-major, translation in elements 12-14. */
void igMatrix44f_GetTranslation(const float *matrix, float *vector);
void igMatrix44f_MakeEulerRotation(void *matrix, float x, float y, float z);
void igMatrix44f_SetEulerRotation(float *m, float x, float y, float z);
void igMatrix44f_SetQuaternion(float *m, float *q);
void igMatrix44f_GetQuaternion(float *q, float *m);
}

/* Alchemy's 4x4 float matrix. Its constructors are the library's out-of-line identity and
 * four-row setters. */
struct igMatrix44f {
    float m[16];

    igMatrix44f() { igMatrix44f_SetIdentity(m); }
    igMatrix44f(const igVec4f &row0, const igVec4f &row1, const igVec4f &row2, const igVec4f &row3) {
        igMatrix44f_FromRows(m, &row0, &row1, &row2, &row3);
    }
};

#endif
