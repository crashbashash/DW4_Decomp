typedef struct Sj Sj;
typedef struct {
    void *vtbl;
    int used;
    char *uuid;
    int f12;
    int f16;
    int arg0;
    int arg1;
    void (*func)(Sj *);
    Sj *self;
} CriSjObj;

extern void *DAT_004b5148[];
extern CriSjObj DAT_004b5180[32];
extern char DAT_004f1a58[];
void FUN_0027b2f8(Sj *);
void FUN_0027b710(CriSjObj *);

CriSjObj *FUN_0027b450(int arg0, int arg1)
{
    CriSjObj *sj;
    int i;

    for (i = 0; i < 32; i++) {
        if (DAT_004b5180[i].used == 0) {
            break;
        }
    }
    if (i == 32) {
        return 0;
    }
    sj = &DAT_004b5180[i];
    sj->used = 1;
    sj->vtbl = DAT_004b5148;
    sj->arg0 = arg0;
    sj->arg1 = arg1;
    sj->uuid = DAT_004f1a58;
    sj->func = FUN_0027b2f8;
    sj->self = (Sj *)sj;
    FUN_0027b710(sj);
    return sj;
}
