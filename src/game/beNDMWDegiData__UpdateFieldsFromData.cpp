#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, char *);
int StringChunk_ReleaseHeader(int, int *);
extern int DAT_00586f20[4];
typedef struct S { unsigned char b0; char p0[3]; int f4; char p1[32]; unsigned short s40[9]; char p2[14]; int f72, f76, f80, f84, f88; } S;
void beNDMWDegiData__UpdateFieldsFromData(beNDMWDegiData *a) {
    S *s0;
    int s2, v, old;
    int *hd;
    s0 = (S *)a->_data;
    a->_isUse = s0->b0;
    a->_lv = s0->f72;
    a->_hp = s0->f76;
    a->_maxHp = s0->f80;
    a->_mp = s0->f84;
    a->_maxMp = s0->f88;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], (char *)s0 + 8);
    old = a->_dmkind;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    a->_dmkind = s2;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(16);
        if (v != 0) v = StringPool_Construct(v);
        DAT_00586f20[0] = v;
    }
    s2 = StringPool_Intern(DAT_00586f20[0], (char *)s0 + 40);
    old = a->_dmName;
    if (old != 0) {
        hd = (int *)(old - 8);
        v = *(int *)(old - 4) - 1;
        *(int *)(old - 4) = v;
        if (v == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    a->_dmName = s2;
    {
        int n;
        unsigned short *pa;
        char *p;
        pa = s0->s40;
        n = 0;
        p = (char *)a;
        a->_id = s0->f4;
        do {
            unsigned short v = *pa;
            if (v == 0) break;
            *(unsigned short *)(p + 8) = v;
            n += 1;
            pa += 1;
            p += 2;
        } while (n < 9);
        for (; n < 9; n++) {
            *(unsigned short *)((char *)a + n * 2 + 8) = 0;
        }
    }
}
} /* extern "C" */
