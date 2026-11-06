/* Returns word +24 of the lsc queue entry whose stream id matches (16 32-byte entries at +56); a
 * NULL object or unknown id is reported through FUN_002777f8 and returns -1. */
typedef struct LscEntry_277528 {
    int id;             /* 0x00 */
    int pad4[5];
    int f24;        /* 0x18 */
    int pad_end[1];
} LscEntry_277528;

typedef struct Lsc_277528 {
    char pad0[56];
    LscEntry_277528 entries[16];    /* 0x38 */
} Lsc_277528;

extern char E0003_Illigal_parameter_lsc_NULL[];   /* 'E0003: Illigal parameter lsc=NULL\n' */
extern char E0012_Can_not_find_stream_ID_d[];       /* 'E0012: Can not find stream ID =%d\n' */
void FUN_002777f8(const char *format, ...);

int FUN_00277528(Lsc_277528 *lsc, int id) {
    int i;

    if (lsc == 0) {
        FUN_002777f8(E0003_Illigal_parameter_lsc_NULL);
        return -1;
    }
    for (i = 0; i < 16; i++) {
        if (lsc->entries[i].id == id) {
            break;
        }
    }
    if (i == 16) {
        FUN_002777f8(E0012_Can_not_find_stream_ID_d, id);
        return -1;
    }
    return lsc->entries[i].f24;
}
