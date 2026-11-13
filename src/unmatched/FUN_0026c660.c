/* Stores an ADXT handle's output volume (+64) and applies it, offset by ADXSJD_GetDefOutVol of the
 * handle's stream (+4), to its renderer (+12) with ADXRNA_SetOutVol; a NULL handle is reported through
 * ADXERR_CallErrFunc1. */
typedef struct Adxt_26c660 {
    int pad0;
    int stream;         /* 0x04 */
    int pad8;
    int renderer;       /* 0x0c */
    char pad16[48];
    short volume;       /* 0x40 */
} Adxt_26c660;

extern char E02080823_ADXT_SetOutVol_parameter_error[]; /* 'E02080823 ADXT_SetOutVol: parameter error' */
void ADXERR_CallErrFunc1(const char *message);
int ADXSJD_GetDefOutVol(int stream);
void ADXRNA_SetOutVol(int renderer, int volume);

void FUN_0026c660(Adxt_26c660 *adxt, int volume) {
    int renderer;

    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080823_ADXT_SetOutVol_parameter_error);
        return;
    }
    adxt->volume = volume;
    renderer = adxt->renderer;
    ADXRNA_SetOutVol(renderer, adxt->volume + ADXSJD_GetDefOutVol(adxt->stream));
}

