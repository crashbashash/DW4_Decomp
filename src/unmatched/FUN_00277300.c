/* 0x00277300 — FUN_00277300 (60 bytes). Sets the byte flag at +4 of an lsc object to 1 when flag is 1 and to 0 otherwise; a NULL object is reported through FUN_002777f8 (error E0003). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Lsc_277300 {
    int pad0;
    char flag;  /* 0x04 */
} Lsc_277300;

extern char s_E0003_Illigal_parameter_lsc_NULL_004f0b08[]; /* 'E0003: Illigal parameter lsc=NULL\n' */
int FUN_002777f8(const char *format, ...);

void FUN_00277300(Lsc_277300 *lsc, int flag) {
    if (lsc == 0) {
        FUN_002777f8(s_E0003_Illigal_parameter_lsc_NULL_004f0b08);
        return;
    }
    if (flag == 1) {
        lsc->flag = flag;
    } else {
        lsc->flag = 0;
    }
}
