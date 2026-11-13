/* Stores an ADXT handle's output balance (+70) clamped to -15..15 and applies it to its renderer
 * (+12) with FUN_00265df8, or -128 while the override DAT_0049c8e8 is set; a NULL handle is
 * reported through ADXERR_CallErrFunc1. */
typedef struct Adxt_26c5a8 {
    char pad0[12];
    int renderer;       /* 0x0c */
    char pad16[54];
    short balance;      /* 0x46 */
} Adxt_26c5a8;

extern char E02080870_ADXT_SetOutBalance_parameter_error[]; /* 'E02080870 ADXT_SetOutBalance: parameter error' */
extern int DAT_0049c8e8;
void ADXERR_CallErrFunc1(const char *message);
void FUN_00265df8(int renderer, int balance);

void FUN_0026c5a8(Adxt_26c5a8 *adxt, int balance) {
    if (adxt == 0) {
        ADXERR_CallErrFunc1(E02080870_ADXT_SetOutBalance_parameter_error);
        return;
    }
    if (balance < -15) {
        adxt->balance = -15;
    } else if (balance >= 16) {
        adxt->balance = 15;
    } else {
        adxt->balance = balance;
    }
    if (DAT_0049c8e8 == 0) {
        FUN_00265df8(adxt->renderer, adxt->balance);
    } else {
        FUN_00265df8(adxt->renderer, -128);
    }
}

