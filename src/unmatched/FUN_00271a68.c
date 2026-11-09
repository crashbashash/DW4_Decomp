typedef struct {
    char f0;
    signed char req;
    signed char stat;
} SrdState;

extern SrdState DAT_004a9288;
extern int DAT_004a92c4;
extern int DAT_004a92e4;
void FUN_0027e1c0(void);
void FUN_0027e1d8(void);
void FUN_00271940(void);
void FUN_00271970(SrdState *h);
void FUN_00271998(SrdState *h);

void FUN_00271a68(SrdState *h)
{
    short i;
    int stat;
    SrdState *srd;

    for (i = 0; i < 1000; i++) {
        FUN_0027e1c0();
        if (DAT_004a92c4 == 1) {
            FUN_0027e1d8();
            FUN_00271940();
            continue;
        }
        DAT_004a92c4 = 1;
        FUN_0027e1d8();
        break;
    }
    stat = h->stat;
    if (stat == 2) {
        srd = &DAT_004a9288;
        if (srd->req == 1) {
            FUN_00271970(h);
        }
        if (srd->req == stat) {
            FUN_00271998(h);
        }
        if (h->stat != 9) {
            h->stat = 3;
            DAT_004a92e4++;
        }
    }
    DAT_004a92c4 = 0;
}
