typedef struct {
    char f0;
    signed char req;
} SrdState;

extern SrdState DAT_004a9288;
extern int DAT_004a92c4;
extern int DAT_004a92c8;
extern int DAT_004a92cc;
int FUN_0027eca8(int *lock);
void FUN_0027e220(void);
void FUN_0027e298(void);
void FUN_00271d50(SrdState *srd);
void FUN_00271f38(SrdState *srd);

void FUN_00272118(void)
{
    SrdState *srd = &DAT_004a9288;

    if (FUN_0027eca8(&DAT_004a92c4) == 0) {
        return;
    }
    if (srd->req == 1) {
        if (DAT_004a92c8 == 1) {
            FUN_0027e220();
        }
        FUN_00271d50(srd);
        if (DAT_004a92c8 == 1) {
            FUN_0027e298();
        }
    }
    if (srd->req == 2) {
        if (DAT_004a92cc == 1) {
            FUN_0027e220();
        }
        FUN_00271f38(srd);
        if (DAT_004a92cc == 1) {
            FUN_0027e298();
        }
    }
    DAT_004a92c4 = 0;
}
