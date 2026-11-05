/* 0x00174db0 — FUN_00174db0, m2c draft (hybrid+w mode), does not match yet.
 * Iterate here; a match is copied to src/FUN_00174db0.c only after verify.py agrees. */
int FUN_001e81c0();
extern int DAT_0048a540[4];
void FUN_00174db0(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 1276) == 1) {
        FUN_001e81c0(DAT_0048a540[*(int *)((char *)(arg0) + 1280)], 0);
        return;
    }
    FUN_001e81c0(DAT_0048a540[*(int *)((char *)(arg0) + 1280)], 1);
}
