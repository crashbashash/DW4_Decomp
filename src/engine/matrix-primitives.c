/* src/engine/matrix-primitives.c — matrix copy/translation primitive matches
 *
 * One translation unit: 3 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */

/* 0x001909b0 */
void Matrix44_FromTranslation(float *matrix, const float *vector) {
    matrix[0]=1.0f; matrix[1]=0; matrix[2]=0; matrix[3]=0;
    matrix[4]=0; matrix[5]=1.0f; matrix[6]=0; matrix[7]=0;
    matrix[8]=0; matrix[9]=0; matrix[10]=1.0f; matrix[11]=0;
    matrix[12]=vector[0]; matrix[13]=vector[1]; matrix[14]=vector[2]; matrix[15]=1.0f;
}

/* 0x00190a10 */
void Matrix44_SetTranslation(float *matrix, const float *vector) {
    matrix[12] = vector[0];
    matrix[13] = vector[1];
    matrix[14] = vector[2];
}

/* 0x00190a30 */
void Matrix44_GetTranslation(const float *matrix, float *vector) {
    vector[0] = matrix[12];
    vector[1] = matrix[13];
    vector[2] = matrix[14];
}
