extern "C" {
#include "dw4/reflected.h"

typedef struct ViewModelEvent {
    int type;
    int arg;
    int data;
} ViewModelEvent;

extern int DAT_0058cd40;
extern int DAT_0058cd08[4];

void FUN_004578c0(igViewModel *model, ViewModelEvent *event);
int FUN_00457e90(int, int);
int FUN_003082b0(...);
void igMatrix44f_SetIdentity(float *);
int FUN_00191f30(int *, float *, float *);
extern unsigned char GPR_00554e7c;
extern unsigned char GPR_00554e80;
}

class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int, int, float, float); };
struct O { char p[8]; V *o; };
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };

extern "C" {

static void FUN_00464af0(float *arg0, float *arg1, float fparg0) {
    float temp_f1;
    float temp_f1_2;

    temp_f1 = *arg0;
    if (!(temp_f1 <= fparg0)) {
        *arg0 = temp_f1 - fparg0;
    } else if (temp_f1 < -fparg0) {
        *arg0 = temp_f1 + fparg0;
    } else {
        *arg0 = 0.0f;
    }
    temp_f1_2 = *arg1;
    if (!(temp_f1_2 <= fparg0)) {
        *arg1 = temp_f1_2 - fparg0;
        return;
    }
    if (temp_f1_2 < -fparg0) {
        *arg1 = temp_f1_2 + fparg0;
        return;
    }
    *arg1 = 0.0f;
}

int Gap__Viewer__igViewManager__vfunc_26(O *self, int x, int y, float f0, float f1) {
    float sp1C;
    float sp18;
    sp18 = f0;
    sp1C = f1;
    FUN_00464af0(&sp18, &sp1C, 0.3f);
    self->o->vX(x, y, sp18, sp1C);
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_27(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_116_0 *)(temp_a0))->vX();
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_32(igViewManager *self, int width, int height)
{
    ViewModelEvent event;

    ((igViewModel *)self->_viewModel)->_ratio = (float)width / (float)height;
    event.type = 2;
    event.arg = 0;
    event.data = DAT_0058cd40;
    FUN_004578c0((igViewModel *)self->_viewModel, &event);
    return 0;
}

void FUN_00464c60(igViewManager *self) {
    float inverse[16];
    int status;
    float *m;
    int r;

    m = ((igViewModel *)self->_viewModel)->_viewMatrix;
    if (GPR_00554e7c == 0) {
        r = FUN_003082b0("current view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e7c = 1;
    }
    igMatrix44f_SetIdentity(inverse);
    FUN_00191f30(&status, inverse, ((igViewModel *)self->_viewModel)->_viewMatrix);
    m = inverse;
    if (GPR_00554e80 == 0) {
        r = FUN_003082b0("current inverse view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e80 = 1;
    }
}

void Gap__Viewer__igViewManager__vfunc_13(int *a) { FUN_00457e90(a[2], a[3]); }

int Gap__Viewer__igViewManager__vfunc_22(void) {
    return DAT_0058cd08[0];
}

}
