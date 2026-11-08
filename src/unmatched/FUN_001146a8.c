typedef struct {
    int number;
    void *handler;
} SyscallEntry;

void RFU116_SetSyscall__00114640(int number, void *handler);
void FUN_00114650(void *dst, void *src, int size);
void FlushCache(int mode);
void *RFU091__00114698(int number);
extern SyscallEntry D_004834c8[];
extern char D_00482d60[];
extern char D_004834a0[];

void FUN_001146a8(void)
{
    unsigned int i;
    if (!(*(volatile int *)0x10001810 & 0x100)) {
        RFU116_SetSyscall__00114640(D_004834c8[0].number, D_004834c8[0].handler);
        FUN_00114650((void *)0x80076000, D_00482d60, 0x740);
        FUN_00114650((void *)0x82000, D_004834a0, 0x28);
        FlushCache(0);
        FlushCache(2);
        RFU116_SetSyscall__00114640(D_004834c8[1].number, D_004834c8[1].handler);
        for (i = 2; i < 8; i++) {
            RFU116_SetSyscall__00114640(D_004834c8[i].number, RFU091__00114698(D_004834c8[i].number));
        }
    }
}
