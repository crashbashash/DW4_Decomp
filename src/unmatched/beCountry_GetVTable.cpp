/* stack-object GetVTable accessor.py. C++ translation unit: the unit compiled with exceptions on
 * and retail keeps this function's exception index record, which only the C++ front end emits. */
struct Obj { int *vt; char pad[4]; };
extern "C" {
int igObject_InitHeader(void *);
extern int DAT_00534d10[4];
extern void * DAT_00586dc8[4];
int beCountry_GetVTable(void);
}
int beCountry_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534d10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
