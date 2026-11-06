/* Reports an ADXT handle's playback time as a (samples, rate) pair: in states 3/4 the decoded
 * total (FUN_002670c0) minus what the renderer (+12) still holds (FUN_00265d00 less +168, plus
 * FUN_0026c9d8), plus +164; in state 5 FUN_00267288 samples scaled by 16 / FUN_00267240, plus
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

int FUN_00267210(void *source);
int FUN_002670c0(void *source);
int FUN_00265d00(int renderer);
int FUN_0026c9d8(Adxt_26be50 *adxt, int arg);
int FUN_00267288(void *source);
int FUN_00267240(void *source);

void FUN_0026be50(Adxt_26be50 *adxt, int *samples, int *rate) {
    int total;
    int pending;

    if (adxt->state == 3 || adxt->state == 4) {
        *rate = FUN_00267210(adxt->source);
        total = FUN_002670c0(adxt->source);
        pending = FUN_00265d00(adxt->renderer);
        *samples = total - (pending - adxt->f168 + FUN_0026c9d8(adxt, 0)) + adxt->f164;
    } else if (adxt->state == 5) {
        *samples = FUN_00267288(adxt->source);
        *rate = FUN_00267210(adxt->source);
        *samples *= 16 / FUN_00267240(adxt->source);
        *samples += adxt->f164;
    } else {
        *samples = 0;
        *rate = 1;
    }
    *samples += adxt->offset;
}

