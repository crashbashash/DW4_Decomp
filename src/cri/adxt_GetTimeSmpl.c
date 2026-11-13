/* Reports an ADXT handle's playback time as a (samples, rate) pair: in states 3/4 the decoded
 * total (ADXSJD_GetDecNumSmpl) minus what the renderer (+12) still holds (ADXRNA_GetNumData less +168, plus
 * FUN_0026c9d8), plus +164; in state 5 ADXSJD_GetTotalNumSmpl samples scaled by 16 / ADXSJD_GetOutBps, plus
 * +164; otherwise (0, 1). The handle's offset (+136) is added to the sample count. */
typedef struct Adxt_26be50 {
    signed char pad0;
    signed char state;  /* 0x01 */
    char pad2[2];
    void *source;       /* 0x04 */
    int pad8;
    int renderer;       /* 0x0c */
    char pad16[120];
    int offset;         /* 0x88 */
    char pad140[24];
    int f164;        /* 0xa4 */
    int f168;        /* 0xa8 */
} Adxt_26be50;

int ADXSJD_GetSfreq(void *source);
int ADXSJD_GetDecNumSmpl(void *source);
int ADXRNA_GetNumData(int renderer);
int FUN_0026c9d8(Adxt_26be50 *adxt, int arg);
int ADXSJD_GetTotalNumSmpl(void *source);
int ADXSJD_GetOutBps(void *source);

void adxt_GetTimeSmpl(Adxt_26be50 *adxt, int *samples, int *rate) {
    int total;
    int pending;

    if (adxt->state == 3 || adxt->state == 4) {
        *rate = ADXSJD_GetSfreq(adxt->source);
        total = ADXSJD_GetDecNumSmpl(adxt->source);
        pending = ADXRNA_GetNumData(adxt->renderer);
        *samples = total - (pending - adxt->f168 + FUN_0026c9d8(adxt, 0)) + adxt->f164;
    } else if (adxt->state == 5) {
        *samples = ADXSJD_GetTotalNumSmpl(adxt->source);
        *rate = ADXSJD_GetSfreq(adxt->source);
        *samples *= 16 / ADXSJD_GetOutBps(adxt->source);
        *samples += adxt->f164;
    } else {
        *samples = 0;
        *rate = 1;
    }
    *samples += adxt->offset;
}

