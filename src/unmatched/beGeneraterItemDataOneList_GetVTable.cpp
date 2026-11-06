extern "C" {
int igObject_InitHeader(int *);
extern int DAT_00535ca0[4];
extern void * DAT_00586dc8[4];
int beGeneraterItemDataOneList_GetVTable(void);
}
int beGeneraterItemDataOneList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00535ca0[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}
