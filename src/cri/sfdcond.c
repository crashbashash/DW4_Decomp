typedef struct SfdInfo64 {
    char c[64];
} SfdInfo64;

typedef struct SfdStatus160 {
    long words[20];
} SfdStatus160;

typedef struct SfdStat64 {
    long sum;
    long min;
    long max;
    int count;
    int pad28;
} SfdStat64;

typedef struct SfdReport {
    SfdStat64 stat[6];
} SfdReport;

typedef struct SfdHn {
    char pad0[72];
    int state;
    char pad76[120 - 76];
    int f120;
    char pad124[264 - 124];
    int f264;
    char f268[2316 - 268];
    SfdInfo64 info;
    char pad2380[2384 - 2380];
    SfdStatus160 status;
    char pad2544[2564 - 2544];
    int cond[100];
    int cond2[100];
    char pad3364[13880 - 3364];
    SfdReport report;
} SfdHn;

typedef struct SfdEntryRef {
    char pad[7984];
    int *value;
} SfdEntryRef;

extern int DAT_004be8d8[];
typedef struct SfdLib {
    int counter;
    int f4;
    int rate;
    char pad12[84 - 12];
    SfdHn *slots[8];
} SfdLib;

extern SfdLib DAT_004bea88;

int FUN_002a0bb8();
int FUN_002a0dd8(SfdHn *hn);
int FUN_002ab6b8();
int FUN_002b03e8(SfdHn *hn, int check);

void FUN_002ada08(int index, int value);
void FUN_002ada78(SfdHn *hn, int index, int value);
void FUN_002adac8(SfdHn *hn, int index, int value);
int FUN_002adb18(SfdHn *hn, int index, int value);
int FUN_002adc40(SfdHn *hn, int index);
void FUN_002adf48(char *ctx, int index, int *out);

void FUN_002ad8f8(void)
{
    FUN_002ab6b8();
}

int FUN_002ad910(SfdHn *hn)
{
    if (FUN_002a0dd8(hn) != 0) {
        FUN_002a0bb8(0, 0xFF000111);
    }
    return hn->state;
}

int FUN_002ad950(SfdHn *hn, int index, int value)
{
    if (hn == 0) {
        FUN_002ada08(index, value);
        DAT_004be8d8[index] = value;
    } else {
        if (FUN_002a0dd8(hn) != 0) {
            return FUN_002a0bb8(0, 0xFF000112);
        }
        FUN_002ada78(hn, index, value);
        FUN_002adac8(hn, index, value);
    }
    return 0;
}

void FUN_002ada08(int index, int value)
{
    SfdHn **slots = DAT_004bea88.slots;
    int i;
    for (i = 0; i < 8; i++) {
        if (slots[i] != 0) {
            FUN_002ada78(slots[i], index, value);
        }
    }
}

void FUN_002ada78(SfdHn *hn, int index, int value)
{
    if (FUN_002adb18(hn, index, value) != 0) {
        hn->cond[index] = value;
    }
}

void FUN_002adac8(SfdHn *hn, int index, int value)
{
    if (FUN_002adb18(hn, index, value) != 0) {
        hn->cond2[index] = value;
    }
}

int FUN_002adb18(SfdHn *hn, int index, int value)
{
    if (index == 6 && value == 1 && FUN_002b03e8(hn, 3) == 0) {
        return 0;
    }
    if (index == 5 && value == 1 && FUN_002b03e8(hn, 2) == 0) {
        return 0;
    }
    return 1;
}

int FUN_002adba0(SfdHn *hn, int index, int *out)
{
    if (hn == 0) {
        *out = DAT_004be8d8[index];
    } else {
        /* matching construct: manual — both paths fall through to one `return 0` */
        if (FUN_002a0dd8(hn) != 0) {
            return FUN_002a0bb8(0, 0xFF000113);
        }
        *out = FUN_002adc40(hn, index);
    }
    return 0;
}

int FUN_002adc40(SfdHn *hn, int index)
{
    return hn->cond[index];
}

int FUN_002adc50(SfdHn *hn, SfdInfo64 *out)
{
    int r = FUN_002a0dd8(hn);
    if (r != 0) {
        return FUN_002a0bb8(0, 0xFF000114);
    }
    *out = hn->info;
    return r;
}

int FUN_002add28(SfdHn *hn, SfdStatus160 *out)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000119);
    }
    *out = hn->status;
    return 0;
}

int FUN_002adec8(SfdHn *hn, int index, int *out)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF000117, out);
    }
    FUN_002adf48((char *)hn, index, out);
    return 0;
}

void FUN_002adf48(char *ctx, int index, int *out)
{
    int *value = ((SfdEntryRef *)(ctx + index * 0x44))->value;
    if (value == 0) {
        *out = 0;
        return;
    }
    *out = *value;
}

int FUN_002adf78(SfdHn *hn, char **data, int *size)
{
    if (FUN_002a0dd8(hn) != 0) {
        return FUN_002a0bb8(0, 0xFF00011C);
    }
    if (hn->f120 != 0) {
        *data = hn->f268;
        *size = hn->f264;
    } else {
        *data = 0;
        *size = 0;
    }
    return 0;
}
