int FUN_002977d8(int a, int b);
int FUN_00293508(void *obj, int size);
int FUN_00298260(void *sub);
void FUN_002936a8(void *obj);
void mwsfd_Error(const char *message);

extern char DAT_004f2fb0[];
extern char DAT_004f2fd8[];

int FUN_00293050(char *obj) {
    char *sub = obj + 12;
    int size = FUN_002977d8(*(int *)(sub + 8), *(int *)(sub + 12));
    int buf = FUN_00293508(obj, size);
    int stream;

    if (buf == 0) {
        mwsfd_Error(DAT_004f2fb0);
        FUN_002936a8(obj);
        return -1;
    }
    *(int *)(obj + 176) = buf;
    *(int *)(obj + 180) = size;
    if (FUN_00298260(sub) == 1) {
        stream = FUN_00293508(obj, 0x20000);
        if (stream == 0) {
            mwsfd_Error(DAT_004f2fd8);
            FUN_002936a8(obj);
            return -1;
        }
        *(int *)(obj + 404) = stream;
        *(int *)(obj + 408) = 0x20000;
    } else {
        *(int *)(obj + 404) = 0;
        *(int *)(obj + 408) = 0;
    }
    return 0;
}
