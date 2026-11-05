extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058a030[4];
int FUN_0036dfe0(void);
}

int FUN_0036dfe0(void) {
    if (DAT_0058a030[0] == 0) {
        DAT_0058a030[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058a030[0];
}
