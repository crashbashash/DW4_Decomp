#include "dw4/reflected.h"
extern "C" {
struct T { int word0; int references; };
void igObject_Destroy(T *);
int StringChunk_ReleaseHeader(...);
extern int DAT_0053d830[4];
extern void * DAT_00586dc8[4];
}
/* matching construct: the object is a beSaveIntfComMdlData; _openSQ/_infoName are 4-byte string handles, viewed as char* for the release helpers; the 12-byte tail pads the stack slot to 32 bytes */
struct Obj : beSaveIntfComMdlData {
    char tail[12];
    inline void rel12() {
        char **self = (char **)&_openSQ;
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
    inline void rel16() {
        char **self = (char **)&_infoName;
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
extern "C" int beSaveIntfComMdlData_GetVTable(void) {
    Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&DAT_0053d830[0];
    obj._openSQ = 0;
    obj._infoName = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_0053d830[0];
    obj.rel16();
    obj.rel12();
    return r;
}
