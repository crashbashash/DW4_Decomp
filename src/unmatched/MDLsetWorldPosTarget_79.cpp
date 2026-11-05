struct V3 { float x, y, z; };
extern "C" {
int FUN_001e6d30(...);
extern int DAT_0050db00[4];
extern V3 * DAT_0058a218[4];
void MDLsetWorldPosTarget_79(int arg0);
}
void MDLsetWorldPosTarget_79(int arg0) {
    V3 sp10;
    float a, b, c;
    V3 *t;

    if (DAT_0058a218[0] != 0) {
        FUN_001e6d30(arg0, &sp10, &DAT_0050db00[0]);
        a = sp10.x; c = sp10.z; b = sp10.y;
        t = DAT_0058a218[0];
        t->x = a;
        t->y = b;
        t->z = c;
        asm { nop }
    }
}
