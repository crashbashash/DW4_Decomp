#include "dw4/reflected.h"
typedef struct K { char pad[52]; int f52; char pad2[8]; int f64; } K;
/* matching construct: pointer-typed view of beBaseInfoRam._parentInfo (+12) and beSoundInfo._dataType (+32); the matching compiler
 * schedules differently when those two fields are int handles.  The shorts at +36/+38 are read through beSoundInfo. */
typedef struct SoundInfoPointerView { char pad0[12]; struct SoundInfoPointerView *f12; char pad[16]; int *f32; } SoundInfoPointerView;
extern "C" {
int FUN_002eb010(int);
int igStrCmp(int *, int *);
int FUN_0037e020(int, int);
int beMessenger_RegisterReceiver(int, SoundInfoPointerView *, int *, int, int);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, int *);
extern int DAT_00586f20[4];
extern int DAT_0050f9a0[4];
extern int DAT_0050f9a8[4];
void Gap__Bec__beSound__vfunc_29(beSound *arg0, SoundInfoPointerView *arg1);
}
void Gap__Bec__beSound__vfunc_29(beSound *arg0, SoundInfoPointerView *arg1) {
    int *s2;
    int *old;
    int *a1;
    int v1;
    int var_v0;
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_0050f9a0[0], 0, -1);
    arg1 = arg1->f12;
    ((K *)arg0->_cri)->f52 = ((beSoundInfo *)arg1)->_baseVolume;
    FUN_0037e020(arg0->_cri, ((beSoundInfo *)arg1)->_sndfVolume);
    if (arg1->f32 == 0) {
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        s2 = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_0050f9a8[0]);
        old = arg1->f32;
        if (old != 0) {
            a1 = old - 2;
            v1 = old[-1] - 1;
            old[-1] = v1;
            if (v1 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        arg1->f32 = s2;
    }
    if (igStrCmp(arg1->f32, &DAT_0050f9a8[0]) == 0) {
        ((K *)arg0->_cri)->f64 = 0;
    } else {
        ((K *)arg0->_cri)->f64 = 1;
    }
}
