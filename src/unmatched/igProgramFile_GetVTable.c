#include "dw4/reflected.h"
int igObject_InitHeader(igProgramFile *);
int igObject_Destroy();
int StringChunk_ReleaseHeader();
extern int DAT_0052e010[4];
extern void * DAT_00586dc8[4];
int igProgramFile_GetVTable(void) {
    igProgramFile obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &DAT_0052e010[0];
    obj._fileName = 0;
    obj._file = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj._vtable = (int)&DAT_0052e010[0];
    if (&obj._file != 0) {
        o = (char *)obj._file;
        if (o != 0) {
            ((igObject *)o)->_refCount = ((igObject *)o)->_refCount - 1;
            if ((((igObject *)o)->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._fileName != 0) {
        o = (char *)obj._fileName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}
