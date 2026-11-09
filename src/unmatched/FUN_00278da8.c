int FUN_00278698();
extern char DAT_004f1380[];
extern char DAT_004f13a8[];

typedef struct {
    char pad0[28];
    int f28;
    int f32;
    int f36;
    int f40;
} CriStream;

#define ABS(x) ((x) < 0 ? -(x) : (x))

void FUN_00278da8(CriStream *st, int x, int y)
{
    if (st == 0) {
        FUN_00278698(DAT_004f1380);
        return;
    }
    if (x < -127 || x > 127 || y < -127 || y > 127) {
        FUN_00278698(DAT_004f13a8);
        return;
    }
    st->f28 = ABS(x + 127);
    st->f32 = ABS(x - 127);
    st->f36 = ABS(y + 127);
    st->f40 = ABS(y - 127);
}
