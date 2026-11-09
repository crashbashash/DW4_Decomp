#include "dw4/reflected.h"

void igMatrix44f_SetIdentity(float *m);
void FUN_00173fd0(void *context, int which, float *m);
void Matrix44_Copy(float *dst, float *src);

void Gap__Attrs__igTexGenMatrixAttr__vfunc_26(igTexGenMatrixAttr *self, void *context)
{
    float m[16];

    igMatrix44f_SetIdentity(m);
    FUN_00173fd0(context, 14, m);
    Matrix44_Copy(self->m, m);
}
