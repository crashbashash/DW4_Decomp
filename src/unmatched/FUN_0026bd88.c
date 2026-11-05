/* 0x0026bd88 — FUN_0026bd88 (200 bytes). Reports an ADXT handle's playback position as a (samples, rate) pair: in states 3/4 from the renderer (+12) via FUN_00265ce8; in state 5 from the source (+4): FUN_00267288 samples scaled by 16 / FUN_00267240, rate FUN_00267210; otherwise (0, 1). The handle's offset (+136) is added to the sample count. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
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
int FUN_00267288(void *source);
int FUN_00267210(void *source);
int FUN_00267240(void *source);

void FUN_0026bd88(Adxt_26bd88 *adxt, int *samples, int *rate) {
    if (adxt->state == 3 || adxt->state == 4) {
        FUN_00265ce8(adxt->renderer, samples, rate);
    } else if (adxt->state == 5) {
        *samples = FUN_00267288(adxt->source);
        *rate = FUN_00267210(adxt->source);
        *samples *= 16 / FUN_00267240(adxt->source);
    } else {
        *samples = 0;
        *rate = 1;
    }
    *samples += adxt->offset;
}

