int FUN_00281ac0(unsigned short kind, unsigned short arg, int a, int b, int c, int d);

struct Ctx00282e00 {
    char pad0[2727];
    signed char sending;    /* +2727 */
    char pad2728[4];
    int mode;               /* +2732 */
};

extern struct Ctx00282e00 *DAT_004bb114;
extern int DAT_004bb118[];

int FUN_00282e00(int id, unsigned short angle, unsigned short vol) {
    struct Ctx00282e00 *ctx = DAT_004bb114;
    int result;
    int pan;
    int p;
    int v;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    pan = (angle % 360) >> 1;
    p = pan + 45;
    if (p >= 180) {
        p = pan - 135;
    }
    if (DAT_004bb114->mode == 2) {
        p = DAT_004bb118[p];
    }
    v = vol < 256 ? vol : 255;
    if ((unsigned int)(id - 1) < 24) {
        result = FUN_00281ac0(3, 0xFFFF, 0x1200, id, p, v);
    } else {
        result = -1;
    }
    DAT_004bb114->sending = 0;
    return result;
}
