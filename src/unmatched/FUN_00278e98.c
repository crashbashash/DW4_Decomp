int FUN_00278698();
extern char DAT_004f13d8[];
extern char DAT_004f1400[];

typedef struct {
    char pad0[16];
    int f16;
    int f20;
    int f24;
} CriStream;


void FUN_00278e98(CriStream *st, int size)
{
    int n;

    if (st == 0) {
        FUN_00278698(DAT_004f13d8);
        return;
    }
    if (size <= 0) {
        FUN_00278698(DAT_004f1400);
        return;
    }
    n = size / 750;
    st->f16 = size;
    if (n > 96) {
        n = 96;
    } else if (n < 1) {
        n = 1;
    }
    st->f24 = n;
}
