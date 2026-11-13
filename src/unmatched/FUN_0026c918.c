/* Stores the reload sector count (+62) of an ADXT handle and, when it has a stream (+8), passes
 * both sector counts (+62 and +60, scaled to bytes) to FUN_0026a9d8; a NULL handle is reported
 * through ADXERR_CallErrFunc1. */
typedef struct Adxt_26c918 {
    char pad0[8];
    void *stream;           /* 0x08 */
    char pad12[48];
    short buffer_sectors;   /* 0x3c */
    short reload_sectors;   /* 0x3e */
} Adxt_26c918;

extern char E02080839_ADXT_SetReloadSct_parameter_error[]; /* 'E02080839 ADXT_SetReloadSct: parameter error' */
void ADXERR_CallErrFunc1(const char *message);
void FUN_0026a9d8(void *stream, int reload_bytes, int buffer_bytes);

/* matching construct: int parameter — retail narrows the 16-bit count only where it is scaled, not on entry */
void FUN_0026c918(Adxt_26c918 *adxt, int sectors) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080839_ADXT_SetReloadSct_parameter_error);
        return;
    }
    adxt->reload_sectors = sectors;
    if (adxt->stream != 0) {
        FUN_0026a9d8(adxt->stream, (short)sectors * 2048, adxt->buffer_sectors * 2048);
    }
}
