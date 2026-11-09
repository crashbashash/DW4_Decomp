int memset();

typedef struct {
    char pad0[72];
    int f72;
    char pad76[726 - 76];
    signed char f726;
    char f727[16];
    char pad743;
    short f744;
    short f746;
    short f748;
} CriChannel;

void FUN_002697d8(CriChannel *ch)
{
    if (ch->f726 == 1) {
        ch->f726 = 0;
        ch->f72 += 36;
    }
    ch->f744 = 0;
    ch->f746 = -128;
    ch->f748 = -128;
    memset(ch->f727, 0, 16);
}
