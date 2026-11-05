/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[32]; };
extern "C" {
int igObject_InitHeader(char *);
extern int DAT_00537890[4];
extern void * DAT_00586dc8[4];
int beModelCtrlAIDataList_GetVTable(void);
}
int beModelCtrlAIDataList_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00537890[0];
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
