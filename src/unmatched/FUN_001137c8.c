typedef struct {
    int number;
    void *handler;
} SyscallEntry;

void RFU116_SetSyscall(int number, void *handler);
void FUN_00113760(void *dst, void *src, int size);
void FlushCache(int mode);
void *RFU091(int number);
extern SyscallEntry D_004822a8[];
extern char D_00481f28[];
extern void *D_004822a0;

void FUN_001137c8(void)
{
    unsigned int i;
    RFU116_SetSyscall(D_004822a8[0].number, D_004822a8[0].handler);
    FUN_00113760((void *)0x80075000, D_00481f28, 0x330);
    FlushCache(0);
    FlushCache(2);
    RFU116_SetSyscall(D_004822a8[1].number, D_004822a8[1].handler);
    RFU116_SetSyscall(D_004822a8[2].number, D_004822a8[2].handler);
    for (i = 3; i < 8; i++) {
        RFU116_SetSyscall(D_004822a8[i].number, RFU091(D_004822a8[i].number));
    }
    D_004822a0 = RFU091(3);
}
