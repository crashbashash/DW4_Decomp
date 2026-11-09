int FUN_0026c568();
void FUN_0026c468();
int FUN_0026c630();
int FUN_0026c5a8();

typedef struct {
    signed char state;
    char pad1[2];
    signed char numChannels;
    char pad4[192];
} CriPlayer;

extern int DAT_0049c8e8;
extern CriPlayer DAT_0049c8f8[16];

void FUN_0026d4d0(int time)
{
    CriPlayer *p;
    int i;
    int ch;

    DAT_0049c8e8 = time;
    p = DAT_0049c8f8;
    for (i = 15; i >= 0; i--, p++) {
        if (p->state == 1) {
            for (ch = 0; ch < p->numChannels; ch++) {
                FUN_0026c468(p, ch, FUN_0026c568(p, ch));
            }
            FUN_0026c5a8(p, FUN_0026c630(p));
        }
    }
}
