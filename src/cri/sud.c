typedef struct SudChars2 {
    char c[2];
} SudChars2;

typedef struct SudChars3 {
    char c[3];
} SudChars3;

typedef struct SudFlagChars {
    char *s[2];
} SudFlagChars;

typedef struct SudClock {
    long long base;
    unsigned short last;
} SudClock;

typedef struct SudStats {
    long long sum;
    long long min;
    long long max;
    int count;
} SudStats;

char *strncpy(char *dst, const char *src, unsigned int count);
int sprintf(char *dst, const char *format, ...);
char *strcat(char *dst, const char *src);
int strncmp(const char *a, const char *b, unsigned int count);
int memcmp(const void *a, const void *b, unsigned int count);
int atoi(const char *text);
unsigned long strtoul(const char *text, char **end, int radix);
int FUN_0026f4b0(const char *name, int *value);

extern char DAT_004f59c0[];
extern char DAT_004f59f8[];
extern char DAT_004f5a08[];
extern char DAT_004f5a10[];
extern char DAT_004f5a18[];
extern char DAT_004f5a20[];
extern char DAT_004f5a28[];
extern SudFlagChars DAT_004f5a30;
extern char DAT_004f5a40[];
extern SudFlagChars DAT_004f5a48;
extern char DAT_004f5a50[];
extern char DAT_004f5a58[];
extern SudFlagChars DAT_004f5a60;
extern char DAT_004f5a68[];
extern volatile unsigned int *DAT_004f5a70[];
extern volatile unsigned int *DAT_004f5a80[];
extern char DAT_004f5a90[];
extern char DAT_004f5a98[];

extern int DAT_004bf280;
extern long long DAT_004bf288;
extern volatile int DAT_004bf290;
extern int DAT_004bf294;
extern int DAT_004bf298;

/* matching construct: manual — a volatile store target gives retail's la + sw 0(reg) and keeps the counter load ahead of it */
extern char *volatile DAT_005856a8;
extern volatile SudClock DAT_005856b0;
extern volatile SudClock DAT_005856c0;
extern volatile SudClock *volatile DAT_005856d0;
extern volatile int DAT_005856d4;

char *FUN_002b5138(void);
void FUN_002b5ce0(long long rate);

void FUN_002b50e8(void) {
    if (DAT_004bf280 <= 0) {
        DAT_005856a8 = FUN_002b5138();
        DAT_004bf280++;
    }
}

char *FUN_002b5138(void) {
    return DAT_004f59c0;
}

void FUN_002b5148(void) {
    if (DAT_004bf280 > 0) {
        DAT_004bf280--;
    }
}

void FUN_002b51f8(char *dst, int *flags);

void FUN_002b5168(char *out, int unused, int *flags) {
    char number[16];
    char *field;
    strncpy(out, DAT_004f59f8, 8);
    sprintf(number, DAT_004f5a08, 19);
    field = out + 16;
    strcat(out, number);
    strncpy(field, DAT_004f5a10, 2);
    FUN_002b51f8(field, flags);
    strcat(field, DAT_004f5a18);
}

void FUN_002b51f8(char *dst, int *flags) {
    SudFlagChars a = DAT_004f5a30;
    SudFlagChars b = DAT_004f5a48;
    SudFlagChars c = DAT_004f5a60;
    strncpy(dst + 2, a.s[flags[0]], 1);
    strncpy(dst + 3, b.s[flags[1]], 1);
    strncpy(dst + 4, c.s[flags[2]], 1);
}

unsigned int FUN_002b52d8(char *header, int index) {
    SudChars2 digits;
    if (header == 0 || index < 0) {
        return 0;
    }
    digits = *(SudChars2 *)(header + 16);
    return atoi(digits.c);
}

int FUN_002b5320(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    return strncmp(header + 18, DAT_004f5a28, 1) == 0;
}

int FUN_002b5360(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    return strncmp(header + 19, DAT_004f5a40, 1) == 0;
}

int FUN_002b53a0(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) == 0) {
        return 0;
    }
    return strncmp(header + 20, DAT_004f5a58, 1) == 0;
}

int FUN_002b5400(char *header, int index) {
    char *field;
    int kind;
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) < 2) {
        return 0;
    }
    field = header + 21;
    if (strncmp(field, DAT_004f5a50, 1) == 0) {
        kind = 1;
    } else {
        kind = strncmp(field, DAT_004f5a58, 1) != 0 ? 0 : 2;
    }
    return kind;
}

int FUN_002b5490(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) < 2) {
        return 0;
    }
    return strncmp(header + 22, DAT_004f5a20, 1) != 0;
}

int FUN_002b56f8(char *base, int index, int offset);

int FUN_002b54f8(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x17);
    }
    return 0;
}

int FUN_002b5578(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x1A);
    }
    return 0;
}

int FUN_002b55f8(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x1D);
    }
    return 0;
}

int FUN_002b5678(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (FUN_002b52d8(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x20);
    }
    return 0;
}

unsigned long FUN_002b5758(char *text, char **end, int radix);

int FUN_002b56f8(char *base, int index, int offset) {
    SudChars3 digits;
    char *end;
    if (base == 0 || index < 0) {
        return 0;
    }
    digits = *(SudChars3 *)(base + offset);
    return FUN_002b5758(digits.c, &end, 16);
}

unsigned long FUN_002b5758(char *text, char **end, int radix) {
    return strtoul(text, end, radix);
}

int FUN_002b5838(char *header);

void FUN_002b5770(char *text, int length, char **found, int *value) {
    int i;
    *value = 0;
    *found = 0;
    if (text == 0 || length <= 0) {
        return;
    }
    for (i = 0; i < length; i++, text++) {
        if (memcmp(text, DAT_004f5a68, 1) == 0 && memcmp(text, DAT_004f59f8, 8) == 0) {
            *found = text;
            *value = FUN_002b5838(text);
        }
    }
}

int FUN_002b5838(char *header) {
    return header ? 0x23 : 0;
}

void FUN_002b5848(int channel) {
    int value;
    if (FUN_0026f4b0(DAT_004f5a90, &value) == 0) {
        channel = value;
    }
    DAT_004bf290++;
    if (DAT_004bf290 >= 2 && DAT_004bf294 == channel) {
        return;
    }
    DAT_004bf294 = channel;
    if (channel == -1) {
        FUN_002b5ce0(1);
        return;
    }
    FUN_002b5ce0(FUN_0026f4b0(DAT_004f5a98, &value) == 0 ? (unsigned int)value : 0x8CA00);
    DAT_004bf298 = *DAT_004f5a70[channel];
    if ((DAT_004bf298 & 0xC7) != 0x82) {
        *DAT_004f5a80[channel] = 0;
        *DAT_004f5a70[channel] = 0x82;
    }
    DAT_005856b0.last = *DAT_004f5a80[channel];
    DAT_005856b0.base = 0;
    DAT_005856c0 = DAT_005856b0;
    DAT_005856d0 = &DAT_005856b0;
    DAT_005856d4 = 0;
}

void FUN_002b59a0(void) {
    DAT_004bf290--;
    if (DAT_004bf290 == 0 && DAT_004bf294 != -1 && (DAT_004bf298 & 0xC7) != 0x82) {
        *DAT_004f5a70[DAT_004bf294] = DAT_004bf298 ^ 0xC00;
    }
    if (DAT_004bf290 < 0) {
        DAT_004bf290 = 0;
    }
}

long long FUN_002b5a10(void) {
    unsigned int count;
    long long now;
    if (DAT_004bf290 <= 0 || DAT_004bf294 == -1) {
        return 0;
    }
    DAT_005856d4++;
    if (DAT_005856d4 == 1) {
        DAT_005856c0 = DAT_005856b0;
        DAT_005856d0 = &DAT_005856c0;
        count = *DAT_004f5a80[DAT_004bf294] & 0xFFFF;
        if (count < DAT_005856b0.last) {
            DAT_005856b0.base += 0x10000;
        }
        DAT_005856b0.last = count;
        now = count + DAT_005856b0.base;
        DAT_005856d0 = &DAT_005856b0;
    } else {
        count = *DAT_004f5a80[DAT_004bf294] & 0xFFFF;
        now = count + DAT_005856d0->base;
        if (count < DAT_005856d0->last) {
            now += 0x10000;
        }
    }
    DAT_005856d4--;
    return now;
}

int FUN_002b5b38(void) {
    FUN_002b5a10();
    return DAT_004bf288 == 1;
}

void FUN_002b5b68(long long rate) {
    FUN_002b5ce0(rate);
}

long long FUN_002b5b80(void) {
    return DAT_004bf288;
}

long long FUN_002b5b90(long long ticks) {
    return ticks * 1000000 / DAT_004bf288;
}

long long FUN_002b5bd0(long long ticks) {
    return ticks * 1000 / DAT_004bf288;
}

long long FUN_002b5c08(long long ticks) {
    return ticks / DAT_004bf288;
}

float FUN_002b5c30(long long ticks) {
    return (float)(int)ticks * 1000000.0f / (float)(int)DAT_004bf288;
}

float FUN_002b5c70(long long ticks) {
    return (float)(int)ticks * 1000.0f / (float)(int)DAT_004bf288;
}

float FUN_002b5cb0(long long ticks) {
    return (float)(int)ticks / (float)(int)DAT_004bf288;
}

void FUN_002b5ce0(long long rate) {
    DAT_004bf288 = rate;
}

void FUN_002b5cf0(SudStats *stats) {
    stats->sum = 0;
    stats->min = 0x7FFFFFFFFFFFFFFFLL;
    stats->max = 0;
    stats->count = 0;
}

void FUN_002b5d10(SudStats *stats, long long value) {
    stats->sum += value;
    stats->min = value < stats->min ? value : stats->min;
    stats->max = stats->max < value ? value : stats->max;
    stats->count++;
}
