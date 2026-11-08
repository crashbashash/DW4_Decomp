int FUN_002d27a0();
int FUN_002d2800();
int FUN_002d2e60();
int StringChunk_ReleaseHeader();
int thunk_free();
extern void *DAT_00586dc8[4];
extern long long DAT_00586dd8[4];

struct Core {
    char pad[21];
    unsigned char f21;
    char pad2[920 - 22];
    void *f920;
    void *f924;
};

void FUN_002d1770(void) {
    struct Core *core;
    void *p;
    int *h;
    int rc;

    if (((struct Core *)DAT_00586dc8[0])->f21 == 0) {
        FUN_002d27a0(DAT_00586dc8[0]);
    }
    if (--DAT_00586dd8[0] == 0) {
        FUN_002d2800(DAT_00586dc8[0]);
        FUN_002d2e60(DAT_00586dc8[0]);
        core = (struct Core *)DAT_00586dc8[0];
        if (core != 0) {
            if (&core->f924) {
                p = core->f924;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
            if (&core->f920) {
                p = core->f920;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader(*h, h);
                    }
                }
            }
            thunk_free(core);
        }
        DAT_00586dc8[0] = 0;
    }
}
