#include "dw4/reflected.h"
extern "C" {
int beLua__RunNamedChunk(int, int *, int);
int TextOrder_PublishLine(beNDMWLoadIntf2TextOrder *, int, int, int);
extern int DAT_004cda40[4];
extern int DAT_004cda44[4];
extern int DAT_004cda48[4];
extern int DAT_004ceb30[4];
extern int DAT_00517a18[4];
extern int DAT_00517a28[4];
extern int DAT_0058a1e0[4];
extern int DAT_0058a220[4];
void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *arg0, int arg1, int arg2) {
    int s0;
    int s2;
    int i;
    int off;
    int v;
    int *e;
    int *p;
    s2 = -1;
    i = 0;
    e = DAT_004cda40;
    for (;;) {
        v = *e;
        if (v == -1) break;
        if ((v & 0xFFFFF) == arg1) { s2 = i; break; }
        e += 3;
        i++;
    }
    if (s2 != -1) {
        off = s2 * 12;
        p = (int *)*(int *)((char *)DAT_004cda48 + off);
        for (;;) {
            if (p[0] == 0) break;
            TextOrder_PublishLine(arg0, p[0], (&DAT_004ceb30[p[1] * 20])[p[2]], p[1]);
            p += 3;
        }
        s0 = arg1 & 0xF000;
        DAT_0058a220[0] = *(int *)((char *)DAT_004cda44 + off);
        DAT_0058a1e0[0] = 0;
        switch (s0) {
        case 0:
            beLua__RunNamedChunk(arg0->_lua, DAT_00517a18, 0);
            break;
        case 0x1000:
        case 0x2000:
        case 0x3000:
            beLua__RunNamedChunk(arg0->_lua, DAT_00517a28, 0);
            break;
        }
        if (arg2 == 1 && (*(int *)((char *)DAT_004cda40 + off) & 0x100000)) {
            DAT_0058a220[0] = *(int *)((char *)DAT_004cda44 + (s2 + 1) * 12);
            DAT_0058a1e0[0] = 0;
            switch (s0) {
            case 0:
                beLua__RunNamedChunk(arg0->_lua, DAT_00517a18, 0);
                break;
            case 0x1000:
            case 0x2000:
            case 0x3000:
                beLua__RunNamedChunk(arg0->_lua, DAT_00517a28, 0);
                break;
            }
        }
    }
}
}
