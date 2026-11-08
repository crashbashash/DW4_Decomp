typedef struct {
    int number;
    void *handler;
} SyscallEntry;

int FUN_00114288(void);
void RFU116_SetSyscall__00114220(int number, void *handler);
void FUN_00114230(void *dst, void *src, int size);
void FlushCache(int mode);
void *RFU091__00114278(int number);
extern SyscallEntry D_00482d40[];
extern char D_00482598[];

void FUN_001142f0(void)
{
    unsigned int i;
    if (FUN_00114288() != 0) {
        RFU116_SetSyscall__00114220(D_00482d40[0].number, D_00482d40[0].handler);
        FUN_00114230((void *)0x80074000, D_00482598, 0x7A8);
        FlushCache(0);
        FlushCache(2);
        RFU116_SetSyscall__00114220(D_00482d40[1].number, D_00482d40[1].handler);
        for (i = 2; i < 3; i++) {
            RFU116_SetSyscall__00114220(D_00482d40[i].number, RFU091__00114278(D_00482d40[i].number));
        }
    }
}
