typedef struct {
    int number;
    void *handler;
} SyscallEntry;

void RFU116_SetSyscall__001141b8(int number, void *handler);
unsigned int FUN_00114070(unsigned int start, unsigned int end, void *pattern);
int *FUN_00114030(int *p, int *end, int value);
int FUN_00113ff8(int *dst, int *src, unsigned int size);
extern SyscallEntry D_00482580[];
extern unsigned int D_00482578;

void FUN_001140b8(void)
{
    unsigned int first;
    unsigned int second;
    unsigned int first_base;
    unsigned int second_base;
    RFU116_SetSyscall__001141b8(D_00482580[0].number, D_00482580[0].handler);
    RFU116_SetSyscall__001141b8(D_00482580[1].number, D_00482580[1].handler);
    first = FUN_00114070(0x80000000, 0x80080000, FUN_00114030);
    second = FUN_00114070(0x80000000, 0x80080000, FUN_00113ff8);
    first_base = first - 0x20C;
    second_base = second - 0x168;
    while (first_base != second_base) {
        if (first_base < second_base) {
            first = FUN_00114070(first + 4, 0x80080000, FUN_00114030);
            first_base = first - 0x20C;
        } else {
            second = FUN_00114070(second + 4, 0x80080000, FUN_00113ff8);
            second_base = second - 0x168;
        }
    }
    D_00482578 = first_base;
}
