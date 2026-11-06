/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
union U { int vt; char b[32]; };
extern "C" {
int igObject_InitHeader(char *);
extern int DAT_00538600[4];
extern void * DAT_00586dc8[4];
int bePadDataList_GetVTable(void);
}
int bePadDataList_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00538600[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
