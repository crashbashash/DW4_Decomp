/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
extern "C" {
int igObject_InitHeader(int *);
extern int DAT_00539c10[4];
extern void * DAT_00586dc8[4];
int beWeaponAttachDataList_GetVTable(void);
}
int beWeaponAttachDataList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00539c10[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}
