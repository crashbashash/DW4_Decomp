#include "dw4/reflected.h"
typedef struct NameHolder { char pad[8]; int *f8; } NameHolder;
typedef struct RamInfoArg { char pad[8]; int f8; NameHolder *fc; char pad2[4]; unsigned char f14; char pad3[31]; igObject *f34; } RamInfoArg;
extern "C" {
int beMessenger_RegisterReceiver(int, RamInfoArg *, int *, int *, int);
int igObject_Destroy(igObject *);
extern int DAT_004e0858[4];
extern int DAT_0050f638[4];
void Gap__Bec__beParticleCtrl2__vfunc_29(beParticleCtrl2 *arg0, RamInfoArg *arg1);
}
void Gap__Bec__beParticleCtrl2__vfunc_29(beParticleCtrl2 *arg0, RamInfoArg *arg1) {
    int *var_a3;
    int t0;
    igObject *temp_a0;

    t0 = arg1->f8;
    var_a3 = arg1->fc->f8;
    var_a3 = (var_a3 != 0) ? var_a3 : (int *)(&DAT_004e0858[0]);
    beMessenger_RegisterReceiver(arg0->_messenger, arg1, &DAT_0050f638[0], var_a3, t0);
    arg1->f14 = 0;
    temp_a0 = arg1->f34;
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)temp_a0->_refCount - 1;
        if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg1->f34 = 0;
}
