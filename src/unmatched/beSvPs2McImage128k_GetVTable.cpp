/* stack-object GetVTable accessor; verified by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; char pad[8]; };
extern "C" {
int igObject_InitHeader(void *);
extern int DAT_00538b60[4];
extern void * DAT_00586dc8[4];
int beSvPs2McImage128k_GetVTable(void);
}
int beSvPs2McImage128k_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538b60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
