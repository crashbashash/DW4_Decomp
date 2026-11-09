typedef struct Sj Sj;
typedef struct {
    void *vtbl;
    int used;
    char *uuid;
    char pad12[16];
    int arg0;
    int arg1;
    int arg2;
    char pad40[16];
    void (*func)(Sj *);
    Sj *self;
} SjMemObj;

extern void *DAT_004b5630[];
extern SjMemObj DAT_004b5668[256];
extern char DAT_004f1d78[];
void FUN_0027bc38(Sj *);
void FUN_0027bf60(SjMemObj *);

SjMemObj *FUN_0027bda0(int arg0, int arg1, int arg2)
{
    SjMemObj *sj;
    int i;

    for (i = 0; i < 256; i++) {
        if (DAT_004b5668[i].used == 0) {
            break;
        }
    }
    sj = 0;
    if (i != 256) {
        sj = &DAT_004b5668[i];
        sj->used = 1;
        sj->vtbl = DAT_004b5630;
        sj->arg0 = arg0;
        sj->arg1 = arg1;
        sj->arg2 = arg2;
        sj->uuid = DAT_004f1d78;
        sj->func = FUN_0027bc38;
        sj->self = (Sj *)sj;
        FUN_0027bf60(sj);
    }
    return sj;
}
