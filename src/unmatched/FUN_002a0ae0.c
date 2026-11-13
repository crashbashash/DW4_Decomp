void FUN_0029d4b8();
void FUN_002a0e10();
void FUN_002a0e48();
void FUN_002a0e68();
int FUN_002abd18();
void FUN_002ae020();
int FUN_002afca0();
extern void *sfply_handles[8];

struct Block2a0ae0 {
    char f0[12];
    char f12[4];
    char f16[4];
};
extern struct Block2a0ae0 DAT_004bea88;

/* Shuts the eight handles in sfply_handles and the sub-systems down; returns the first error seen
 * from FUN_002afca0, else the last FUN_002abd18 status. */
int FUN_002a0ae0(void) {
    int i;
    void **handle = sfply_handles;
    int status = 0;
    int error;

    for (i = 7; i >= 0; i--) {
        if (*handle != 0) {
            status = FUN_002abd18(*handle);
        }
        handle++;
    }
    FUN_002ae020(DAT_004bea88.f0);
    FUN_0029d4b8(DAT_004bea88.f12);
    error = FUN_002afca0(DAT_004bea88.f16);
    FUN_002a0e68();
    FUN_002a0e48();
    FUN_002a0e10();
    if (error != 0) {
        return error;
    }
    return status;
}
