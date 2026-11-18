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
extern volatile SudClock utytmr_main;
extern volatile SudClock utytmr_sub;
extern volatile SudClock *volatile utytmr_ptr;
extern volatile int utytmr_lock;

char *sud_GetVersionStr(void);
void utytmr_SetUnit(long long rate);

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

unsigned int SUD_AnalyVersion(char *header, int size) {
    SudChars2 digits;
    if (header == 0 || size < 0) {
        return 0;
    }
    digits = *(SudChars2 *)(header + 16);
    return atoi(digits.c);
}

int SUD_AnalyTypeDivField(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    return strncmp(header + 18, "D", 1) == 0;
}

int SUD_AnalyTypeCcs(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    return strncmp(header + 19, "C", 1) == 0;
}

int SUD_AnalyTypeIntl(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) == 0) {
        return 0;
    }
    return strncmp(header + 20, "I", 1) == 0;
}

int SUD_AnalyExtScan(char *header, int size) {
    char *field;
    int kind;
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) < 2) {
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

int SUD_AnalyExtFlag(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) < 2) {
        return 0;
    }
    return strncmp(header + 22, "A", 1) != 0;
}

int sud_AnalyHex3(char *header, int size, int offset);

int SUD_AnalyExtVal0(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) >= 2) {
        return sud_AnalyHex3(header, size, 0x17);
    }
    return 0;
}

int SUD_AnalyExtVal1(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) >= 2) {
        return sud_AnalyHex3(header, size, 0x1A);
    }
    return 0;
}

int SUD_AnalyExtVal2(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) >= 2) {
        return sud_AnalyHex3(header, size, 0x1D);
    }
    return 0;
}

int SUD_AnalyExtVal3(char *header, int size) {
    if (header == 0 || size < 0) {
        return 0;
    }
    if (SUD_AnalyVersion(header, size) >= 2) {
        return sud_AnalyHex3(header, size, 0x20);
    }
    return 0;
}

unsigned long sud_StrToUl(char *text, char **end, int radix);

int sud_AnalyHex3(char *header, int size, int offset) {
    SudChars3 digits;
    char *end;
    if (header == 0 || size < 0) {
        return 0;
    }
    digits = *(SudChars3 *)(header + offset);
    return sud_StrToUl(digits.c, &end, 16);
}

unsigned long sud_StrToUl(char *text, char **end, int radix) {
    return strtoul(text, end, radix);
}

int sud_GetSudDatSize(char *header);

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
            *value = sud_GetSudDatSize(text);
        }
    }
}

int sud_GetSudDatSize(char *header) {
    return header ? 0x23 : 0;
}

/* The hardware timers' mode and count registers, indexed by timer channel. */
static volatile unsigned int *const utytmr_t_mode[] = {
    (unsigned int *)0x10000010, (unsigned int *)0x10000810,
    (unsigned int *)0x10001010, (unsigned int *)0x10001810,
};
static volatile unsigned int *const utytmr_t_count[] = {
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
        utytmr_SetUnit(1);
        return;
    }
    utytmr_SetUnit(CRICFG_Read("TMR_CLK", &value) == 0 ? (unsigned int)value : 0x8CA00);
    utytmr_save_mode = *utytmr_t_mode[channel];
    if ((utytmr_save_mode & 0xC7) != 0x82) {
        *utytmr_t_count[channel] = 0;
        *utytmr_t_mode[channel] = 0x82;
    }
    utytmr_main.last = *utytmr_t_count[channel];
    utytmr_main.base = 0;
    utytmr_sub = utytmr_main;
    utytmr_ptr = &utytmr_main;
    utytmr_lock = 0;
}

void UTY_FinishTmr(void) {
    utytmr_init_cnt--;
    if (utytmr_init_cnt == 0 && utytmr_ch != -1 && (utytmr_save_mode & 0xC7) != 0x82) {
        *utytmr_t_mode[utytmr_ch] = utytmr_save_mode ^ 0xC00;
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
    utytmr_lock++;
    if (utytmr_lock == 1) {
        utytmr_sub = utytmr_main;
        utytmr_ptr = &utytmr_sub;
        count = *utytmr_t_count[utytmr_ch] & 0xFFFF;
        if (count < utytmr_main.last) {
            utytmr_main.base += 0x10000;
        }
        utytmr_main.last = count;
        now = count + utytmr_main.base;
        utytmr_ptr = &utytmr_main;
    } else {
        count = *utytmr_t_count[utytmr_ch] & 0xFFFF;
        now = count + utytmr_ptr->base;
        if (count < utytmr_ptr->last) {
            now += 0x10000;
        }
    }
    utytmr_lock--;
    return now;
}

int UTY_IsTmrVoid(void) {
    UTY_GetTmr();
    return utytmr_unit == 1;
}

void UTY_SetTmrUnit(long long rate) {
    utytmr_SetUnit(rate);
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

float UTY_TmrToUsecF(long long ticks) {
    return (float)(int)ticks * 1000000.0f / (float)(int)utytmr_unit;
}

float UTY_TmrToMsecF(long long ticks) {
    return (float)(int)ticks * 1000.0f / (float)(int)utytmr_unit;
}

float UTY_TmrToSecF(long long ticks) {
    return (float)(int)ticks / (float)(int)utytmr_unit;
}

void utytmr_SetUnit(long long rate) {
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
