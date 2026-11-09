typedef struct igResult { int v; } igResult;

typedef struct MatrixInverseCache {
    char pad0[108];
    float matrix[16];
    float inverse[16];
    unsigned char inverseDirty;
} MatrixInverseCache;

igResult FUN_00191f30(float *dst, float *src);
void Matrix44_Copy(float *dst, float *src);

void FUN_001671b0(MatrixInverseCache *self, float *out) {
    if (self->inverseDirty) {
        FUN_00191f30(self->inverse, self->matrix);
        self->inverseDirty = 0;
    }
    Matrix44_Copy(out, self->inverse);
}
