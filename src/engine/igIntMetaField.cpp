#include "dw4/reflected.h"

class DW4VC_140_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int); };

extern "C" {
int sscanf(...);
int sprintf(...);
int FUN_002eb010(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
igMetaField *igMetaField_Init(igMetaField *);
void *igMetaField_Construct(igMetaField *);
int igMetaField_CopyConstruct(...);
int igMetaField_Destruct(...);
void *igIntMetaField_Init(igMetaField *);
extern int DAT_004f9588[4];
extern int DAT_004f95c0[4];
extern int DAT_00586f20[4];
extern int g_igIntMetaField_vtable[4];

int Gap__Core__igIntMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &DAT_004f9588[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igIntMetaField__vfunc_57(int *arg0, int arg1, int *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;

    sprintf(&sp20[0], &DAT_004f95c0[0], *arg2);
    if (&sp20[0] == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern(DAT_00586f20[0], &sp20[0]);
    }
    *arg0 = var_v1;
}

int FUN_002ea3d0(void) {
    return 4;
}

void *igIntMetaField_Construct(igMetaField *self) {
    igMetaField_Construct(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    if (self) {
        igIntMetaField_Init(self);
    }
    return self;
}

void *igIntMetaField_Init(igMetaField *self) {
    igMetaField_Init(self);
    self->_vtable = (int)g_igIntMetaField_vtable;
    return self;
}

int **FUN_002ea460(int **arg0) {
    igMetaField_CopyConstruct();
    *arg0 = &g_igIntMetaField_vtable[0];
    return arg0;
}

void Gap__Core__igIntMetaField__vfunc_02(void) {
    igMetaField_Destruct();
}

void FUN_002ea4b0(void **arg0, int arg1) {
    int sp1C;

    sp1C = arg1;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1C));
}

int Gap__Core__igIntMetaField__vfunc_27(void) {
    return 4;
}
}
