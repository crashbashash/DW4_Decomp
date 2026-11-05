/* 0x00277400 — FUN_00277400 (144 bytes). Returns the id (first word) of queue entry no of an lsc object: entries are a 16-slot ring of 32-byte records at +56 starting at slot +32, with +36 entries queued; a NULL object or out-of-range no is reported through FUN_002777f8 and returns -1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct LscEntry_277400 {
    int id;             /* 0x00 */
    int pad4[7];
} LscEntry_277400;      /* 0x20 bytes */

typedef struct Lsc_277400 {
    char pad0[32];
    int head;                       /* 0x20 */
    int count;                      /* 0x24 */
    char pad40[16];
    LscEntry_277400 entries[16];    /* 0x38 */
} Lsc_277400;

extern char s_E0003_Illigal_parameter_lsc_NULL_004f0b08[];   /* 'E0003: Illigal parameter lsc=NULL\n' */
extern char s_E0009_Illigal_parameter_no_d_004f0b58[];       /* 'E0009: Illigal parameter no=%d\n' */
void FUN_002777f8(const char *format, ...);

int FUN_00277400(Lsc_277400 *lsc, int no) {
    int slot;

    if (lsc == 0) {
        FUN_002777f8(s_E0003_Illigal_parameter_lsc_NULL_004f0b08);
        return -1;
    }
    if (no < 0 || no >= lsc->count) {
        FUN_002777f8(s_E0009_Illigal_parameter_no_d_004f0b58, no);
        return -1;
    }
    slot = (lsc->head + no) % 16;
    return lsc->entries[slot].id;
}

