typedef struct Sj Sj;
typedef struct {
    void *vtbl;
    signed char used;
    char mode;
    char pad6[2];
    char *uuid;
    int data;
    int nnode;
    char pad20[20];
    void (*func)(Sj *);
    Sj *self;
} SjNodePool;

extern void *DAT_004b9668[];
extern SjNodePool DAT_004b96a0[64];
extern char DAT_004f2028[];
void FUN_0027c778(Sj *);
void FUN_0027cbc0(SjNodePool *);

SjNodePool *FUN_0027c8e0(int mode, int data, int size)
{
    SjNodePool *sj;
    int i;

    for (i = 0; i < 64; i++) {
        if (DAT_004b96a0[i].used == 0) {
            break;
        }
    }
    if (i == 64) {
        return 0;
    }
    sj = &DAT_004b96a0[i];
    sj->used = 1;
    sj->vtbl = DAT_004b9668;
    sj->mode = mode;
    sj->uuid = DAT_004f2028;
    sj->data = data;
    sj->nnode = size / 16;
    sj->func = FUN_0027c778;
    sj->self = (Sj *)sj;
    FUN_0027cbc0(sj);
    return sj;
}
