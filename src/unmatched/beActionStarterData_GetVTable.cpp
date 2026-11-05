#include "dw4/reflected.h"
extern "C" {
int StringChunk_ReleaseHeader(...);
extern int DAT_00524950[4];
extern int DAT_005344e0[4];
extern void * DAT_00586dc8[4];
}
struct Obj : beActionStarterData {
    inline void rel8() {
        char **self = (char **)&_name;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
    inline void rel12() {
        char **self = (char **)&_message;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
        }
    }
};
extern "C" int igObject_InitHeader(Obj *);
extern "C" int beActionStarterData_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&DAT_005344e0[0];
    obj._message = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_005344e0[0];
    obj.rel12();
    obj._vtable = (int)&DAT_00524950[0];
    obj.rel8();
    return r;
}
