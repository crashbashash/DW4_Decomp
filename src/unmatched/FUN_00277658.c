/* 0x00277658 — FUN_00277658 (100 bytes). Sets the value at +20 of an lsc object after checking it lies in 0..limit (+24); a NULL object or out-of-range value is reported through FUN_002777f8. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Lsc_277658 {
    char pad0[20];
    int value;  /* 0x14 */
    int limit;  /* 0x18 */
} Lsc_277658;

extern char s_E0003_Illigal_parameter_lsc_NULL_004f0b08[];        /* 'E0003: Illigal parameter lsc=NULL\n' */
extern char s_E0010_Illigal_parameter_min_val_d_004f0ba0[];       /* 'E0010: Illigal parameter min_val=%d\n' */
void FUN_002777f8(const char *format, ...);

void FUN_00277658(Lsc_277658 *lsc, int value) {
    if (lsc == 0) {
        FUN_002777f8(s_E0003_Illigal_parameter_lsc_NULL_004f0b08);
        return;
    }
    if (value < 0 || lsc->limit < value) {
        FUN_002777f8(s_E0010_Illigal_parameter_min_val_d_004f0ba0, value);
        return;
    }
    lsc->value = value;
}
