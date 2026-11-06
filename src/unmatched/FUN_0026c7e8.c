/* 0x0026c7e8 — FUN_0026c7e8 (176 bytes). Sets an ADXT handle's reload size from a time: time * rate samples, in 32-sample 18-byte frames per channel, as 2048-byte sectors capped at the buffer size (+60); stores it at +62 and, with a stream (+8), passes both sizes in bytes to FUN_0026a9d8. A NULL handle is reported through FUN_002607e8. Its error string names it ADXT_SetReloadTime (CRI), a name hypothesis. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Adxt_26c7e8 {
    char pad0[8];
    void *stream;           /* 0x08 */
    char pad12[48];
    short buffer_sectors;   /* 0x3c */
    short reload_sectors;   /* 0x3e */
} Adxt_26c7e8;

extern char E02080838_ADXT_SetReloadTime_parameter_error[]; /* 'E02080838 ADXT_SetReloadTime: parameter error' */
void FUN_002607e8(const char *message);
void FUN_0026a9d8(void *stream, int reload_bytes, int buffer_bytes);

void FUN_0026c7e8(Adxt_26c7e8 *adxt, float time, int channels, int rate) {
    int sectors;

    if (adxt == 0) {
        FUN_002607e8(E02080838_ADXT_SetReloadTime_parameter_error);
        return;
    }
    sectors = (int)(time * (float)rate) / 32 * channels * 18 / 2048;
    adxt->reload_sectors = sectors < adxt->buffer_sectors ? sectors : adxt->buffer_sectors;
    if (adxt->stream != 0) {
        FUN_0026a9d8(adxt->stream, adxt->reload_sectors << 11, adxt->buffer_sectors << 11);
    }
}

