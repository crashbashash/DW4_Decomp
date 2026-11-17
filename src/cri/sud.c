#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dw4/cri/uty.h"
#include "dw4/cri/sud.h"
#include "dw4/cri/cricfg.h"

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


extern int sud_init_cnt;
extern long long utytmr_unit;
extern volatile int utytmr_init_cnt;
extern int utytmr_ch;
extern int utytmr_save_mode;

/* matching construct: manual — a volatile store target gives retail's la + sw 0(reg) and keeps the counter load ahead of it */
extern char *volatile sud_version_ptr;
extern volatile SudClock DAT_005856b0;
extern volatile SudClock DAT_005856c0;
extern volatile SudClock *volatile DAT_005856d0;
extern volatile int DAT_005856d4;

char *sud_GetVersionStr(void);
void FUN_002b5ce0(long long rate);

void SUD_Init(void) {
    if (sud_init_cnt <= 0) {
        sud_version_ptr = sud_GetVersionStr();
        sud_init_cnt++;
    }
}

char *sud_GetVersionStr(void) {
    return "\nCRI SUD/PS2EE Ver.0.05 Build:Oct  6 2004 11:36:33\n";
}

void SUD_Finish(void) {
    if (sud_init_cnt > 0) {
        sud_init_cnt--;
    }
}

void SUD_SetFmtTypeToBuf(char *dst, int *flags);

void SUD_MakePicUsrDat(char *out, int unused, int *flags) {
    char number[16];
    char *field;
    strncpy(out, "<SUDPS_>", 8);
    sprintf(number, "<%06X>", 19);
    field = out + 16;
    strcat(out, number);
    strncpy(field, "02", 2);
    SUD_SetFmtTypeToBuf(field, flags);
    strcat(field, "\n");
}

void SUD_SetFmtTypeToBuf(char *dst, int *flags) {
    SudFlagChars a = {{"A", "D"}};
    SudFlagChars b = {{"N", "C"}};
    SudFlagChars c = {{"P", "I"}};
    strncpy(dst + 2, a.s[flags[0]], 1);
    strncpy(dst + 3, b.s[flags[1]], 1);
    strncpy(dst + 4, c.s[flags[2]], 1);
}

unsigned int SUD_AnalyVersion(char *header, int index) {
    SudChars2 digits;
    if (header == 0 || index < 0) {
        return 0;
    }
    digits = *(SudChars2 *)(header + 16);
    return atoi(digits.c);
}

int SUD_AnalyTypeDivField(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    return strncmp(header + 18, "D", 1) == 0;
}

int SUD_AnalyTypeCcs(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    return strncmp(header + 19, "C", 1) == 0;
}

int FUN_002b53a0(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) == 0) {
        return 0;
    }
    return strncmp(header + 20, "I", 1) == 0;
}

int FUN_002b5400(char *header, int index) {
    char *field;
    int kind;
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) < 2) {
        return 0;
    }
    field = header + 21;
    if (strncmp(field, "P", 1) == 0) {
        kind = 1;
    } else {
        kind = strncmp(field, "I", 1) != 0 ? 0 : 2;
    }
    return kind;
}

int FUN_002b5490(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) < 2) {
        return 0;
    }
    return strncmp(header + 22, "A", 1) != 0;
}

int FUN_002b56f8(char *base, int index, int offset);

int FUN_002b54f8(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x17);
    }
    return 0;
}

int FUN_002b5578(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x1A);
    }
    return 0;
}

int FUN_002b55f8(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) >= 2) {
        return FUN_002b56f8(header, index, 0x1D);
    }
    return 0;
}

int FUN_002b5678(char *header, int index) {
    if (header == 0 || index < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, index) >= 2) {
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

void SUD_SearchSudDat(char *text, int length, char **found, int *value) {
    int i;
    *value = 0;
    *found = 0;
    if (text == 0 || length <= 0) {
        return;
    }
    for (i = 0; i < length; i++, text++) {
        if (memcmp(text, "<", 1) == 0 && memcmp(text, "<SUDPS_>", 8) == 0) {
            *found = text;
            *value = FUN_002b5838(text);
        }
    }
}

int FUN_002b5838(char *header) {
    return header ? 0x23 : 0;
}

/* The hardware timers' mode and count registers, indexed by timer channel. */
static volatile unsigned int *const sud_tmr_mode[] = {
    (unsigned int *)0x10000010, (unsigned int *)0x10000810,
    (unsigned int *)0x10001010, (unsigned int *)0x10001810,
};
static volatile unsigned int *const sud_tmr_count[] = {
    (unsigned int *)0x10000000, (unsigned int *)0x10000800,
    (unsigned int *)0x10001000, (unsigned int *)0x10001800,
};

void UTY_InitTmr(int channel) {
    int value;
    if (CRICFG_Read("TMR_CH", &value) == 0) {
        channel = value;
    }
    utytmr_init_cnt++;
    if (utytmr_init_cnt >= 2 && utytmr_ch == channel) {
        return;
    }
    utytmr_ch = channel;
    if (channel == -1) {
        FUN_002b5ce0(1);
        return;
    }
    FUN_002b5ce0(CRICFG_Read("TMR_CLK", &value) == 0 ? (unsigned int)value : 0x8CA00);
    utytmr_save_mode = *sud_tmr_mode[channel];
    if ((utytmr_save_mode & 0xC7) != 0x82) {
        *sud_tmr_count[channel] = 0;
        *sud_tmr_mode[channel] = 0x82;
    }
    DAT_005856b0.last = *sud_tmr_count[channel];
    DAT_005856b0.base = 0;
    DAT_005856c0 = DAT_005856b0;
    DAT_005856d0 = &DAT_005856b0;
    DAT_005856d4 = 0;
}

void UTY_FinishTmr(void) {
    utytmr_init_cnt--;
    if (utytmr_init_cnt == 0 && utytmr_ch != -1 && (utytmr_save_mode & 0xC7) != 0x82) {
        *sud_tmr_mode[utytmr_ch] = utytmr_save_mode ^ 0xC00;
    }
    if (utytmr_init_cnt < 0) {
        utytmr_init_cnt = 0;
    }
}

long long UTY_GetTmr(void) {
    unsigned int count;
    long long now;
    if (utytmr_init_cnt <= 0 || utytmr_ch == -1) {
        return 0;
    }
    DAT_005856d4++;
    if (DAT_005856d4 == 1) {
        DAT_005856c0 = DAT_005856b0;
        DAT_005856d0 = &DAT_005856c0;
        count = *sud_tmr_count[utytmr_ch] & 0xFFFF;
        if (count < DAT_005856b0.last) {
            DAT_005856b0.base += 0x10000;
        }
        DAT_005856b0.last = count;
        now = count + DAT_005856b0.base;
        DAT_005856d0 = &DAT_005856b0;
    } else {
        count = *sud_tmr_count[utytmr_ch] & 0xFFFF;
        now = count + DAT_005856d0->base;
        if (count < DAT_005856d0->last) {
            now += 0x10000;
        }
    }
    DAT_005856d4--;
    return now;
}

int UTY_IsTmrVoid(void) {
    UTY_GetTmr();
    return utytmr_unit == 1;
}

void UTY_SetTmrUnit(long long rate) {
    FUN_002b5ce0(rate);
}

long long UTY_GetTmrUnit(void) {
    return utytmr_unit;
}

long long UTY_TmrToUsec(long long ticks) {
    return ticks * 1000000 / utytmr_unit;
}

long long UTY_TmrToMsec(long long ticks) {
    return ticks * 1000 / utytmr_unit;
}

long long UTY_TmrToSec(long long ticks) {
    return ticks / utytmr_unit;
}

float FUN_002b5c30(long long ticks) {
    return (float)(int)ticks * 1000000.0f / (float)(int)utytmr_unit;
}

float FUN_002b5c70(long long ticks) {
    return (float)(int)ticks * 1000.0f / (float)(int)utytmr_unit;
}

float FUN_002b5cb0(long long ticks) {
    return (float)(int)ticks / (float)(int)utytmr_unit;
}

void FUN_002b5ce0(long long rate) {
    utytmr_unit = rate;
}

void UTY_InitTsum(SudStats *stats) {
    stats->sum = 0;
    stats->min = 0x7FFFFFFFFFFFFFFFLL;
    stats->max = 0;
    stats->count = 0;
}

void UTY_AddTsum(SudStats *stats, long long value) {
    stats->sum += value;
    stats->min = value < stats->min ? value : stats->min;
    stats->max = stats->max < value ? value : stats->max;
    stats->count++;
}
