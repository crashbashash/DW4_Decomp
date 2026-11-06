#include "dw4/reflected.h"
extern "C" {
typedef struct Pair { void *a; void *b; } Pair;
typedef struct Inner { char p[16]; Pair *pair; } Inner;
typedef struct Link { char p[16]; Inner *inner; } Link;
void FUN_003d9e70(void *, int);
int FUN_003da7c0(void *);
unsigned char FUN_003dcab0(beNDMWLoadIntf2DataSelIntf *c, int sel) {
    Link *n = (Link *)c->_statDisp;
    unsigned char r = 0;
    int v;
    switch (sel) {
    default: v = c->_st0; break;
    case 1: v = c->_st1; break;
    case 2: v = c->_st2; break;
    case 3: v = c->_st3; break;
    }
    switch (v) {
    case 0:
        FUN_003d9e70(n->inner->pair->a, 0);
        FUN_003d9e70(n->inner->pair->b, 0);
        c->_isDownStatWin = 0;
        v++;
        c->_isUpStatWin = 0;
        break;
    case 1:
        if ((FUN_003da7c0(n->inner->pair->a) & 0xFF) == 1 && (FUN_003da7c0(n->inner->pair->b) & 0xFF) == 1) {
            v++;
        }
        break;
    case 2:
        r = 1;
        break;
    }
    switch (sel) {
    default: c->_st0 = v; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; break;
    case 1: c->_st1 = v; c->_st3 = 0; c->_st2 = 0; break;
    case 2: c->_st2 = v; c->_st3 = 0; break;
    case 3: c->_st3 = v; break;
    }
    return r;
}
}
