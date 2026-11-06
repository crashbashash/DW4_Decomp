#include "dw4/reflected.h"
struct R { int a, b, c; };
struct H { char pad[236]; short a, b, c; };
struct Q { char pad[200]; int a, b, c; };
/* Tail of the NameSel object past the reflected fields (+100): selection table state. */
struct NameSelTail {
    char p0[104];
    struct R rows[8];
    int ints[9];
    short shorts[9];
    char c254, c255, c256, c257, c258, c259;
};
void beNDMWLoadIntf2NameSel__Init(beNDMWLoadIntf2NameSel *arg0, unsigned char arg1) {
    struct NameSelTail *T = (struct NameSelTail *)arg0;
    int i;
    int j;
    struct Q *q;
    struct H *h;
    arg0->_langID = 1;
    switch (arg0->_langID) {
    case 0:
        arg0->_nameMojiMax = 6; arg0->_tateMax = 24; arg0->_tateMin = 0;
        break;
    case 1:
        arg0->_nameMojiMax = 8; arg0->_tateMax = 4; arg0->_tateMin = 0;
        break;
    default:
        arg0->_nameMojiMax = 8; arg0->_tateMax = 30; arg0->_tateMin = 24;
        break;
    }
    if (arg1 == 1) {
        T->c254 = 0; T->c255 = 0; T->c256 = 0; T->c257 = 0; T->c258 = 0; T->c259 = 0;
        arg0->_nameCurPos = -1;
        i = 0;
        q = (struct Q *)arg0;
        do {
            q->a = 0; q->b = 0; q->c = 0;
            i += 3;
            q = (struct Q *)((char *)q + 12);
        } while (i < 9);
        j = 0;
        h = (struct H *)arg0;
        do {
            h->a = 0; h->b = 0; h->c = 0;
            j += 3;
            h = (struct H *)((char *)h + 6);
        } while (j < 9);
    }
    switch (arg0->_langID) {
    case 0:
        if (arg0->_nameCurPos == -1) { T->rows[0].a = 4; T->rows[0].b = 0; T->rows[0].c = 0; arg0->_nameCurPos = 0; }
        break;
    case 1:
        if (arg0->_nameCurPos == -1) { T->rows[0].a = 0; T->rows[0].b = 0; T->rows[0].c = 0; arg0->_nameCurPos = 0; }
        break;
    default:
    case 2:
        if (arg0->_nameCurPos == -1) { T->rows[0].a = 28; T->rows[0].b = 0; T->rows[0].c = 0; arg0->_nameCurPos = 0; }
        break;
    }
    arg0->_tatePoint = T->rows[arg0->_nameCurPos].a;
    arg0->_yokoPoint = T->rows[arg0->_nameCurPos].b;
    arg0->_yokoCurPos = T->rows[arg0->_nameCurPos].c;
    T->ints[arg0->_nameCurPos] = 1;
    arg0->_isEnd = 0; arg0->_isMakeName = 0; arg0->_isQuestion = 0; arg0->_isAnswer = 0; arg0->_isNameOK = 0; arg0->_isSideCur = 0;
    arg0->_st0 = 0; arg0->_st3 = 0; arg0->_st2 = 0; arg0->_st1 = 0;
}
