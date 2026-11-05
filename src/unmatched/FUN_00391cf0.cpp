#include "dw4/reflected.h"
struct VO;
extern "C" {
int FUN_002eb010(...);
int FUN_00392d20(int, int, int, float, float, float);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(...);
void *StringPool_Intern(int, void *);
int igStrCmp(void *, void *);
extern int DAT_0050ef88[4];
extern int DAT_0050efe8[4];
extern int DAT_0050eff0[4];
extern int DAT_00586f20[4];
void FUN_00391cf0(VO *self, int arg1, int arg2, beModelCtrlInfoWork *s);
}
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void v35(int, char *); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void v40(int); };
struct PoolRel { static inline void rel(char *p) {
    if (p != 0) {
        int *h = (int *)(p - 8);
        int r = *(int *)(p - 4) - 1;
        *(int *)(p - 4) = r;
        if (r == 0) StringChunk_ReleaseHeader(*h, h);
    }
} };
void FUN_00391cf0(VO *self, int arg1, int arg2, beModelCtrlInfoWork *s)
{
    if (s->_isOnCtrl != 0) self->v40(arg2);
    if (igStrCmp((void *)s->_keyEventName, &DAT_0050efe8[0]) == 0) {
        switch (s->_ctrlSt0) {
        case 1: {
            int mode = s->_ctrlSt1;
            int a0 = ((int *)((beModelCtrlMoveObjectList *)s->_moveObjectList)->_data)[2];
            switch (mode) {
            case 0:
                if (s->_keyInput != 0) {
                    FUN_00392d20(a0, 0, 1, ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[2], ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[3], 0.0f);
                    s->_ctrlSt1 = 1;
                } else {
                    FUN_00392d20(a0, 2, 1, ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[0], ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[1], 0.0f);
                    s->_ctrlSt1 = 2;
                }
                break;
            case 1:
                if (s->_keyInput == 0) {
                    FUN_00392d20(a0, 2, 1, ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[0], ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[1], 0.0f);
                    s->_ctrlSt1 = 2;
                }
                break;
            case 2:
                if (s->_keyInput == 1) {
                    FUN_00392d20(a0, 0, 1, ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[2], ((float *)((igFloatList *)s->_pdMoveDataList)->_data)[3], 0.0f);
                    s->_ctrlSt1 = 1;
                }
                break;
            }
            break;
        }
        case 2:
            if (s->_keyInput == 1) {
                char *n;
                if (DAT_00586f20[0] == 0) {
                    int p = FUN_002eb010(16);
                    if (p != 0) p = StringPool_Construct(p);
                    DAT_00586f20[0] = p;
                }
                n = (char *)StringPool_Intern(DAT_00586f20[0], &DAT_0050ef88[0]);
                PoolRel::rel((char *)s->_keyEventName);
                s->_keyEventName = (int)n;
            }
            break;
        case 3:
            if (s->_keyInput == 0) {
                char *n;
                if (DAT_00586f20[0] == 0) {
                    int p = FUN_002eb010(16);
                    if (p != 0) p = StringPool_Construct(p);
                    DAT_00586f20[0] = p;
                }
                n = (char *)StringPool_Intern(DAT_00586f20[0], &DAT_0050eff0[0]);
                PoolRel::rel((char *)s->_keyEventName);
                s->_keyEventName = (int)n;
            }
            break;
        }
    }
    if (igStrCmp((void *)s->_keyEventName, &DAT_0050efe8[0]) != 0 && igStrCmp((void *)s->_keyEventName, (void *)s->_seqCodeName) != 0) {
        self->v35(arg2, (char *)s->_keyEventName);
    }
}
