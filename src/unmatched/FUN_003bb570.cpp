extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058b010[4];
int FUN_003bb570(void);
}
int FUN_003bb570(void) {
    if (DAT_0058b010[0] == 0) {
        DAT_0058b010[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058b010[0];
}
