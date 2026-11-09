int memset();
void FUN_0025f300(int, int, short *, short *);

typedef struct {
    int used;
    int id;
    int f8;
    int f12;
    char pad16[24];
    char f40[8];
    short f48;
    short f50;
    char pad52[8];
} RnaVoice;

extern RnaVoice DAT_004a8eb8[16];

RnaVoice *FUN_0026ee98(void)
{
    RnaVoice *v;
    int i;

    for (i = 0; i < 16; i++) {
        if (DAT_004a8eb8[i].used == 0) {
            break;
        }
    }
    if (i == 16) {
        return 0;
    }
    v = &DAT_004a8eb8[i];
    memset(v, 0, sizeof(RnaVoice));
    v->used = 1;
    v->id = i;
    v->f8 = 0;
    v->f12 = 0;
    FUN_0025f300(500, 44100, &v->f48, &v->f50);
    memset(v->f40, 0, 8);
    return v;
}
