/* 0x00277490 — FUN_00277490 (148 bytes). Returns word +4 of the lsc queue entry whose stream id matches (16 32-byte entries at +56); a NULL object or unknown id is reported through FUN_002777f8 and returns 0. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct LscEntry_277490 {
    int id;             /* 0x00 */
    int f4;        /* 0x04 */
    int pad_end[6];
} LscEntry_277490;      /* 0x20 bytes */

typedef struct Lsc_277490 {
    char pad0[56];
    LscEntry_277490 entries[16];    /* 0x38 */
} Lsc_277490;

extern char s_E0003_Illigal_parameter_lsc_NULL_004f0b08[];   /* 'E0003: Illigal parameter lsc=NULL\n' */
extern char s_E0012_Can_not_find_stream_ID_d_004f0b78[];       /* 'E0012: Can not find stream ID =%d\n' */
void FUN_002777f8(const char *format, ...);

int FUN_00277490(Lsc_277490 *lsc, int id) {
    int i;

    if (lsc == 0) {
        FUN_002777f8(s_E0003_Illigal_parameter_lsc_NULL_004f0b08);
        return 0;
    }
    for (i = 0; i < 16; i++) {
        if (lsc->entries[i].id == id) {
            break;
        }
    }
    if (i == 16) {
        FUN_002777f8(s_E0012_Can_not_find_stream_ID_d_004f0b78, id);
        return 0;
    }
    return lsc->entries[i].f4;
}
