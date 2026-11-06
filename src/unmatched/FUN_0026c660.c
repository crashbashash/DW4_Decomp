/* Stores an ADXT handle's output volume (+64) and applies it, offset by FUN_00267378 of the
 * handle's stream (+4), to its renderer (+12) with FUN_00265dc8; a NULL handle is reported through
 * FUN_002607e8. */
typedef struct Adxt_26c660 {
    int pad0;
    int stream;         /* 0x04 */
    int pad8;
    int renderer;       /* 0x0c */
    char pad16[48];
    short volume;       /* 0x40 */
} Adxt_26c660;

extern char E02080823_ADXT_SetOutVol_parameter_error[]; /* 'E02080823 ADXT_SetOutVol: parameter error' */
void FUN_002607e8(const char *message);
int FUN_00267378(int stream);
void FUN_00265dc8(int renderer, int volume);

void FUN_0026c660(Adxt_26c660 *adxt, int volume) {
    int renderer;

    if (adxt == 0) {
        FUN_002607e8(E02080823_ADXT_SetOutVol_parameter_error);
        return;
    }
    adxt->volume = volume;
    renderer = adxt->renderer;
    FUN_00265dc8(renderer, adxt->volume + FUN_00267378(adxt->stream));
}

