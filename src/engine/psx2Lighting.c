int memcpy();
extern char DAT_00554bc0;
extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern int DAT_0056aed0[4];
extern int DAT_0056aee0[4];
extern int DAT_0056aef0[4];
extern int DAT_0056aef8[4];
extern long long DAT_0056af08[4];
extern long long DAT_0056af10[4];
extern long long DAT_0056af18[4];
extern long long DAT_0056af20[4];
extern long long DAT_0056af28[4];
extern int DAT_0056af40[4];
extern int DAT_0056af60[4];
extern long long DAT_0056b478[4];

void FUN_001f8830(int arg0) {
    int *p;
    void **slot;

    slot = (void **)(&DAT_0056af40[arg0]);
    p = (int *)((char *)(*slot) + 128);
    if (*p == 0) {
        *p = 1;
        DAT_0056aef0[0] += 1;
        if (*(int *)((char *)((*slot)) + 124) == 1) {
            DAT_0056aef8[0] += 1;
        }
    }
    DAT_00491270[0] = 1;
    DAT_0056af28[0] += 1;
    DAT_00491478[0] |= 0x84;
}

void FUN_001f88d0(int arg0) {
    void **temp_a1;
    void *temp_v1;

    temp_a1 = (void **)(&DAT_0056af40[arg0]);
    temp_v1 = (void *)(*temp_a1);
    if (*(int *)((char *)(temp_v1) + 128) != 0) {
        *(int *)((char *)(temp_v1) + 128) = 0;
        DAT_0056aef0[0] -= 1;
        if (*(int *)((char *)((*temp_a1)) + 124) == 1) {
            DAT_0056aef8[0] -= 1;
        }
    }
    *temp_a1 = 0;
    DAT_00491270[0] = 1;
    DAT_0056af28[0] += 1;
    DAT_00491478[0] |= 0x84;
}

void FUN_001f8970(void) {
    if (DAT_00554bc0 != 1) {
        DAT_00554bc0 = 1;
        DAT_00491270[0] = 1;
        DAT_0056af08[0] += 1;
        DAT_00491478[0] |= 0x97;
    }
}

void FUN_001f89c0(void) {
    if (DAT_00554bc0 != 0) {
        DAT_00554bc0 = 0;
        DAT_0056af08[0] += 1;
        DAT_0056b478[0] &= (int)0xFFFF1E7F;
        DAT_00491270[0] = 1;
        DAT_00491478[0] |= 0x97;
    }
}

void FUN_001f8a30(int arg0, int *arg1) {
    if (arg1[27] & 8) {
        DAT_00491270[0] = 1;
        arg1[27] = arg1[27] & ~8;
    }
    DAT_0056af20[0] += 1;
    DAT_0056af40[arg0] = (int)arg1;
    DAT_00491478[0] |= 4;
}

void FUN_001f8aa0(int arg0) {
    memcpy(&DAT_0056aee0[0], arg0, 0x10);
    DAT_00491478[0] |= 4;
}

struct S1f8ae0 { char pad[68]; int flags; };
void FUN_001f8ae0(int arg0, struct S1f8ae0 *arg1) {
    DAT_0056af10[0] += 1;
    if (arg1->flags & 2) {
        DAT_00491270[0] = 1;
        arg1->flags = arg1->flags & ~2;
    }
    DAT_0056af60[arg0] = (int)arg1;
    DAT_00491478[0] |= 4;
}

void FUN_001fb0a0(int arg0) {
    DAT_0056aed0[0] = arg0;
    DAT_00491270[0] = 1;
    DAT_0056af18[0] += 1;
    DAT_00491478[0] |= 5;
}
