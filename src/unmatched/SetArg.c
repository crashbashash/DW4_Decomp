typedef struct {
    int number;
    void *address;
} SyscallEntry;
extern char *DAT_004822a0;
extern SyscallEntry DAT_00482d58;
void RFU116_SetSyscall__001143e0(int number, void *address);
int FUN_001143a0(void *dst, const void *src, int size);
unsigned int strlen(const char *s);
char *SetArg(const char *filename, int argc, char **argv) {
    char **slot = (char **)DAT_004822a0;
    char *data = (char *)(slot + 16);
    char *strings = data;
    int length;
    int i;
    RFU116_SetSyscall__001143e0(DAT_00482d58.number, DAT_00482d58.address);
    if (argc > 15) argc = 15;
    FUN_001143a0(slot, &data, 4);
    slot++;
    length = strlen(filename) + 1;
    FUN_001143a0(data, filename, length);
    data += length;
    for (i = 0; i < argc; i++) {
        FUN_001143a0(slot, &data, 4);
        slot++;
        length = strlen(argv[i]) + 1;
        FUN_001143a0(data, argv[i], length);
        data += length;
    }
    return strings;
}
