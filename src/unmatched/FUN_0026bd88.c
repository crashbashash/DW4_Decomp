/* Reports an ADXT handle's playback position as a (samples, rate) pair: in states 3/4 from the
 * renderer (+12) via FUN_00265ce8; in state 5 from the source (+4): ADXSJD_GetTotalNumSmpl samples scaled by
 * 16 / ADXSJD_GetOutBps, rate ADXSJD_GetSfreq; otherwise (0, 1). The handle's offset (+136) is added to
 * the sample count. */
typedef struct Adxt_26bd88 {
    signed char pad0;
    signed char state;  /* 0x01 */
    char pad2[2];
    void *source;       /* 0x04 */
    int pad8;
    int renderer;       /* 0x0c */
    char pad16[120];
    int offset;         /* 0x88 */
} Adxt_26bd88;

void FUN_00265ce8(int renderer, int *samples, int *rate);
int ADXSJD_GetTotalNumSmpl(void *source);
int ADXSJD_GetSfreq(void *source);
int ADXSJD_GetOutBps(void *source);

void FUN_0026bd88(Adxt_26bd88 *adxt, int *samples, int *rate) {
    if (adxt->state == 3 || adxt->state == 4) {
        FUN_00265ce8(adxt->renderer, samples, rate);
    } else if (adxt->state == 5) {
        *samples = ADXSJD_GetTotalNumSmpl(adxt->source);
        *rate = ADXSJD_GetSfreq(adxt->source);
        *samples *= 16 / ADXSJD_GetOutBps(adxt->source);
    } else {
        *samples = 0;
        *rate = 1;
    }
    *samples += adxt->offset;
}

