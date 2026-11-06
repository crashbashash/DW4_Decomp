#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(int);
int FUN_003f5410(beNDMWStatusSelect01 *, int *, int *, int *, int *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, int *);
int beNDMWWindow_PresentModelAtOrigin(beNDMWStatusSelect01 *, int *, int, char *, int *);
int beNDMWWindow_RunMessageScript(beNDMWStatusSelect01 *, int *, int);
extern int DAT_0051a978[4];
extern int DAT_0051a998[4];
extern int DAT_0051a9b8[4];
extern int DAT_0051a9c0[4];
extern int DAT_0051a9c8[4];
extern int DAT_0051a9d0[4];
extern int DAT_0051a9e0[4];
extern int DAT_0051a9f0[4];
extern int DAT_0051aa08[4];
extern int DAT_0051aa18[4];
extern int DAT_0051aa28[4];
extern int DAT_0051aa30[4];
extern int DAT_0051aa38[4];
extern int DAT_0051aa40[4];
extern int DAT_0051aa50[4];
extern int DAT_00586f20[4];
void Gap__Bec__beNDMWStatusSelect01__vfunc_22(beNDMWStatusSelect01 *arg0);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    /* take a freshly interned token, dropping the share of the previous one */
    void Assign(char *fresh) { char *old = p; if (old) { int *h = (int *)old - 2; int r = ((int *)old)[-1] - 1; ((int *)old)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } p = fresh; }
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
void Gap__Bec__beNDMWStatusSelect01__vfunc_22(beNDMWStatusSelect01 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    char *temp_s1;

    {
    /* the model name to present: empty unless the entry code selects one */
    StringRef name(0);
    switch (arg0->_entCode) {
    case 0x1F:
    case 0x5B:
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        name.Assign(StringPool_Intern(DAT_00586f20[0], &DAT_0051a9f0[0]));
        arg0->_selectMax = 3;
        break;
    case 0x3D:
        if (DAT_00586f20[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            DAT_00586f20[0] = var_v0;
        }
        name.Assign(StringPool_Intern(DAT_00586f20[0], &DAT_0051aa08[0]));
        arg0->_selectMax = 4;
        break;
    }
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051a978[0], 0, name.p, &DAT_0051a998[0]);
    }
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051aa28[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051a9b8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051a9c0[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051a9c8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051aa50[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    if (arg0->_entCode > 0) {
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051a9d0[0], arg0->_entCode);
    }
    if (DAT_00586f20[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s1 = StringPool_Intern(DAT_00586f20[0], &DAT_0051a9e0[0]);
    temp_a0 = (int *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_infoName = (int)temp_s1;
    arg0->_offsetPos[0] = -83.0f;
    arg0->_offsetPos[1] = 172.0f;
    arg0->_offsetPos[2] = 0.0f;
    arg0->_isNoCancel = 0;
}
