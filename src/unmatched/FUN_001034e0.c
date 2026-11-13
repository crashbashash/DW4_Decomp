typedef struct {
    int w[7];
} Block;
typedef struct {
    int x0;
    void *dest;
    int pad[8];
    void (*fa[4])(Block *b);
    void (*fb[4])(Block *b);
    Block ea[4];
    Block eb[4];
    char *src;
    int count;
    int direct;
    int skipped;
    int pending;
    int skip;
} FrameBuf;
typedef struct {
    char *base;
    int pad[3];
    int stride;
} Frame;
typedef struct {
    char p0[308];
    int fault;
    char p1[324 - 312];
    int mb_width;
    char p2[396 - 328];
    int picture_structure;
    char p3[472 - 400];
    Frame *cur_frame;
    char p4[488 - 476];
    Frame *top_frame;
    char p5[504 - 492];
    Frame *bot_frame;
    char p6[1448 - 508];
    FrameBuf buf[2];
    int cur;
} Dec;
extern char DAT_004d1ee0[];
void FUN_00103730(Dec *d, int bx, int by, int macroblock_type, int motion_type, int PMV[2][2][2],
                  int mv_field_sel[2][2], int dmvector[2]);
void FUN_00108340(Dec *d);
void _sceMpegErrorf(Dec *d, const char *msg, ...);
int FUN_001034e0(Dec *d, int MBA, int MBAinc, int macroblock_type, int motion_type, int PMV[2][2][2],
                 int mv_field_sel[2][2], int dmvector[2]) {
    int intra = macroblock_type & 1;
    int bx = MBA % d->mb_width;
    int by = MBA / d->mb_width;
    int x = bx * 16;
    int y = by * 16;
    Frame *f;

    if (intra) {
        while ((*(volatile unsigned int *)0x1000D400 >> 8) & 1);
        d->buf[d->cur].pending = 0;
    } else {
        if ((unsigned int)(motion_type - 1) >= 3) {
            _sceMpegErrorf(d, DAT_004d1ee0, motion_type);
            d->fault = 1;
            return 0;
        }
        FUN_00103730(d, x, y, macroblock_type, motion_type, PMV, mv_field_sel, dmvector);
        while ((*(volatile unsigned int *)0x1000D400 >> 8) & 1);
        FUN_00108340(d);
        d->buf[d->cur].pending = 1;
    }
    if (MBAinc == 1 && (macroblock_type & 2)) {
        d->buf[d->cur].skipped = MBAinc;
    } else {
        d->buf[d->cur].skipped = 0;
    }
    d->buf[d->cur].direct = intra;
    if (d->picture_structure == 3) {
        d->buf[d->cur].src = d->cur_frame->base + (bx * d->cur_frame->stride + by) * 384;
    } else {
        f = d->picture_structure == 2 ? d->bot_frame : d->top_frame;
        d->buf[d->cur].src = f->base + (bx * f->stride + by) * 384;
    }
    return 1;
}
