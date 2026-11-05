typedef struct S { char pad0[272]; char f272[127]; char f399; } S;
int strncpy();
extern void * DAT_004c1ec0[4];
void FUN_002d3240(S *arg0, char *arg1) {
    if (arg1 != 0) {
        strncpy(arg0->f272, arg1, 0x7F);
        arg0->f399 = 0;
    } else {
        arg0->f272[0] = 0;
    }
    if ((arg1 != 0) && (*arg1 != 0)) {
        DAT_004c1ec0[0] = (void *)arg0->f272;
    }
}
