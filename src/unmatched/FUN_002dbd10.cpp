#include "dw4/igSmartPointer.h"

struct R : public igObject { };
extern "C" {
extern int sscanf(int, int *, void *);
extern R *FUN_002b9500(int);
extern int FUN_002dbfb0(int, int, int, int);
extern int FUN_002dc050(int, int, int, int);
extern int FUN_002dc0a0(int, int, float, float);
extern int FUN_002dc120(int, int, int, int);
extern int igStringObj_Set(R *, int);
extern int FUN_0030b670(R *, unsigned char *);
extern int igObject_GetAllocator();
extern int DAT_004f9730[4];
extern int DAT_004f9738[4];
}

extern "C" unsigned char FUN_002dbd10(int arg0, int arg1, int arg2, int arg3, int arg4) {
    unsigned char r;
    switch (arg1) {
    case 1: {
        int first = 0;
        int second = 0;
        if (sscanf(arg2, &DAT_004f9730[0], &first) != 1) return 0;
        if (sscanf(arg4, &DAT_004f9730[0], &second) != 1) return 0;
        r = FUN_002dc050(arg0, first, arg3, second);
        break;
    }
    case 2: {
        float first = 0;
        float second = 0;
        if (sscanf(arg2, &DAT_004f9738[0], &first) != 1) return 0;
        if (sscanf(arg4, &DAT_004f9738[0], &second) != 1) return 0;
        r = FUN_002dc0a0(arg0, arg3, first, second);
        break;
    }
    case 3: {
        unsigned char first = 0;
        unsigned char second = 0;
        igSmartPointer<R> text(FUN_002b9500(igObject_GetAllocator()));
        igStringObj_Set(text.get(), arg2);
        if (FUN_0030b670(text.get(), &first) == 0) return 0;
        igStringObj_Set(text.get(), arg4);
        if (FUN_0030b670(text.get(), &second) == 0) return 0;
        r = FUN_002dc120(arg0, first, arg3, second);
        break;
    }
    default:
    case 0:
        r = FUN_002dbfb0(arg0, arg2, arg3, arg4);
    }
    return r;
}
