#ifndef DW4_IGMATRIX44F_H
#define DW4_IGMATRIX44F_H

#include "dw4/igMath.h"
#include "dw4/igVec3f.h"

class igResult;

extern "C" {
void igMatrix44f_SetIdentity(float *matrix);
void igMatrix44f_FromRows(float *matrix, const igVec4f *row0, const igVec4f *row1, const igVec4f *row2,
                  const igVec4f *row3);
/* The matrices are 16 floats, row-major, translation in elements 12-14. */
void igMatrix44f_GetTranslation(const float *matrix, float *vector);
/* Sets elements 12-14 to `vector`, leaving the rest. */
void igMatrix44f_SetTranslation(float *matrix, const float *vector);
/* The identity with `translation` in elements 12-14. */
void igMatrix44f_FromTranslation(float *matrix, const igVec3f &translation);
void igMatrix44f_MakeEulerRotation(void *matrix, float x, float y, float z);
void igMatrix44f_SetEulerRotation(float *m, float x, float y, float z);
/* Reads the matrix's rotation back as Euler angles, one per output. */
void igMatrix44f_GetEulerAngles(const float *matrix, float *x, float *y, float *z);
void igMatrix44f_SetQuaternion(float *m, float *q);
void igMatrix44f_GetQuaternion(float *q, float *m);
void igMatrix44f_MakePerspective(float *matrix, float fovX, float fovY, float aspect, float nearPlane, float farPlane);
void igMatrix44f_MakeLookAt(float *matrix, const float *eye, const float *center, const float *up);
void igMatrix44f_Copy(float *destination, const float *source);
void igMatrix44f_Multiply(float *product, const float *a, const float *b);
void igMatrix44f_PreMultiply(float *matrix, const float *a);
void igMatrix44f_PreRotateAxisAngle(float *matrix, const float *axis, float angle);
/* Moves the translation by `translation` expressed in the matrix's own axes. */
void igMatrix44f_TranslateLocal(float *matrix, const igVec3f &translation);
/* Fails when the matrix is singular. */
igResult igMatrix44f_Invert(float *inverse, const float *matrix);
/* The inverse of a rotation-and-translation matrix: the transposed rotation and the translation
 * taken back through it. */
igResult igMatrix44f_InvertOrthonormal(float *inverse, const float *matrix);
void Quaternion_Lerp(float *out, float t, const float *from, const float *to);
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
