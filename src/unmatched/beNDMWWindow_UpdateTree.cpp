/* 0x003f6490 - beNDMWWindow_UpdateTree. Window tree update: virtual hook slot 21, children below the minimum state are reset to state 2, then children without the flag are released and removed (recursion before the check); alternate compiler -O3,p. */
#include "dw4/reflected.h"
extern "C" {
void List_RemoveWordAt(void *, int);
void igObject_Destroy(void *);
}
/* matching construct: dummy-virtual view so ->f21() dispatches through vtable slot 21 of the window */
struct WinView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void f21(); };
extern "C" void beNDMWWindow_UpdateTree(beNDMWWindow *w);
extern "C" void beNDMWWindow_UpdateTree(beNDMWWindow *w) {
    int n;
    int i;
    int c;
    int j;
    beNDMWWindow *ch;
    igObjectList *k;
    if (w->_isRun != 0) {
        ((WinView *)w)->f21();
    }
    if (w->_isRun == 0 || w->_st0 >= 2) {
        c = ((igObjectList *)w->_subWindow)->_count;
        j = 0;
        if (0 < c) {
            int off = 0;
            do {
                ch = *(beNDMWWindow **)(((igObjectList *)w->_subWindow)->_data + off);
                if (ch->_st0 < 2) {
                    ch->_st0 = 2;
                    ch->_st3 = 0;
                    ch->_st2 = 0;
                    ch->_st1 = 0;
                }
                j++;
                off += 4;
            } while (j < c);
        }
    }
    n = ((igObjectList *)w->_subWindow)->_count;
    i = 0;
    if (n > 0) {
        do {
            int off = i * 4;
            beNDMWWindow_UpdateTree(*(beNDMWWindow **)(((igObjectList *)w->_subWindow)->_data + off));
            k = (igObjectList *)w->_subWindow;
            ch = *(beNDMWWindow **)(k->_data + off);
            if (ch->_isRun == 0) {
                if (ch != 0) {
                    ch->_refCount = (int)ch->_refCount - 1;
                    if (((unsigned long long)((long long)(int)ch->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(ch);
                    }
                }
                List_RemoveWordAt(k, i);
                i--;
                n--;
                *(int *)(k->_data + k->_count * 4) = 0;
            }
            i++;
        } while (i < n);
    }
}
