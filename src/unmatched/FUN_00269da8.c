typedef struct {
    signed char used;
    char pad1[73];
    char f74;
    char pad75[21];
} Sjr;

extern int DAT_004a7ef0;
extern int adxstmf_nrml_num;
extern Sjr DAT_004a7f10[];
void ADXSTMF_SetupHandleMember(Sjr *sjr, int a0, int a1, int a2, int a3);

Sjr *FUN_00269da8(int a0, int a1, int a2, int a3)
{
    Sjr *sjr;
    int i;

    sjr = 0;
    for (i = 0; i < adxstmf_nrml_num; i++) {
        sjr = &DAT_004a7f10[DAT_004a7ef0 + i];
        if (sjr->used == 0) {
            break;
        }
    }
    if (i == adxstmf_nrml_num) {
        return 0;
    }
    ADXSTMF_SetupHandleMember(sjr, a0, a1, a2, a3);
    sjr->f74 = 1;
    return sjr;
}
