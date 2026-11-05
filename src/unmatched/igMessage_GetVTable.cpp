extern "C" {
int igObject_InitHeader(void *);
extern int DAT_0052d000[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int b; };
int igMessage_GetVTable(void) {
    struct Obj o; igObject_InitHeader(&o);
    o.vt = &DAT_0052d000[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
}
