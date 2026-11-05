#include "dw4/reflected.h"
extern "C" {
int igStrCmp(int, int *);
extern int DAT_004e0858[4];
int FUN_00383350(beFont *arg0, int arg1);
}

int FUN_00383350(beFont *arg0, int arg1) {
    int s1;
    int *a1;
    if (arg1 == 0) {
        return 0;
    }
    s1 = 0;
    if (0 < ((beFontImageList *)arg0->_fonts)->_count) {
        do {
            a1 = (int *)(((beFontImage **)((beFontImageList *)arg0->_fonts)->_data)[s1])->_name;
            a1 = a1 ? a1 : &DAT_004e0858[0];
            if (igStrCmp(arg1, a1) == 0) {
                return s1;
            }
            s1 += 1;
        } while (s1 < ((beFontImageList *)arg0->_fonts)->_count);
    }
    return 0;
}
