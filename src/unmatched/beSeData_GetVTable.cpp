#include "dw4/reflected.h"
extern "C" {
int StringChunk_ReleaseHeader(...);
extern int DAT_00524950[4];
extern int DAT_00538e70[4];
extern void * DAT_00586dc8[4];
}
/* matching construct: the retail unit inlines the release of each string handle (header at -8/-4 of the string) */
struct SeDataLocal : beSeData {
    inline void relSound() {
        char **self = (char **)&_sound;
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
    inline void relName() {
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
};
extern "C" int igObject_InitHeader(SeDataLocal *);
extern "C" int beSeData_GetVTable(void) {
    SeDataLocal obj;
    int r;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._vtable = (int)&DAT_00538e70[0];
    obj._sound = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_00538e70[0];
    obj.relSound();
    obj._vtable = (int)&DAT_00524950[0];
    obj.relName();
    return r;
}
