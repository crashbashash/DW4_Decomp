/* libmpeg mpc: macroblock decoding (slices, macroblock modes, motion vectors) and the IPU bit reader. */
#include "dw4/sony/libmpeg.h"
#include "dw4/libkernl.h"

#define IPU_CMD (*(volatile unsigned int *)0x10002000)
#define IPU_CMD64 (*(volatile long long *)0x10002000)
#define IPU_CTRL (*(volatile unsigned int *)0x10002010)
#define IPU_BP (*(volatile unsigned int *)0x10002020)
#define IPU_TOP64 (*(long long *)0x10002030)
#define D3_CHCR (*(volatile unsigned int *)0x1000b000)
#define D3_QWC (*(volatile unsigned int *)0x1000b020)
#define D4_CHCR (*(volatile unsigned int *)0x1000b400)
#define D4_QWC (*(volatile unsigned int *)0x1000b420)
#define D9_CHCR (*(volatile unsigned int *)0x1000d400)
#define D_ENABLER (*(volatile unsigned int *)0x1000f520)
#define D_ENABLEW (*(volatile unsigned int *)0x1000f590)

#define IPU_CTRL_BUSY 0x80000000
#define IPU_CTRL_ECD 0x4000
#define IPU_CTRL_RST 0x40000000
#define IPU_CTRL_MP1_SHIFT 23
#define IPU_CTRL_PCT_SHIFT 24
#define D_ENABLE_CPND 0x10000
#define D_CHCR_STR 0x100

#define IPU_BCLR 0x00000000
#define IPU_BDEC 0x20000000
#define IPU_VDEC 0x30000000
#define IPU_FDEC 0x40000000

/* VDEC tables */
#define VDEC_MBAI 0
#define VDEC_MB_TYPE 1
#define VDEC_MOTION_CODE 2
#define VDEC_DMVECTOR 3

#define MB_INTRA 1
#define MB_PATTERN 2
#define MB_MOTION_BACKWARD 4
#define MB_MOTION_FORWARD 8
#define MB_QUANT 0x10

#define I_TYPE 1
#define P_TYPE 2
#define B_TYPE 3

#define MC_FIELD 1
#define MC_FRAME 2
#define MC_16X8 2
#define MC_DMV 3

#define MBAI_STUFFING 34
#define MBAI_ESCAPE 35
#define MPEG1_STUFFING_CODE 15

#define POLLS_PER_NODATA 5000

void _dmaRefImage(_sceMpegDecoder *dec);
void _sprClear(unsigned int addr, int size);
void _getAllRefs(_sceMpegDecoder *dec, int x, int y, int macroblock_type, int motion_type, int PMV[2][2][2],
                 int mv_field_sel[2][2], int dmvector[2]);
void _getRef0(_sceMpegDecoder *dec, _sceMpegPicture *ref, int refParity, int dstParity, int dstRow, int rows, int x,
              int y, int mvx, int mvy, int fieldMode, int average);
void _doMC(_sceMpegDecoder *dec, int buffer);
int _waitBdec(_sceMpegDecoder *dec);
void _nextStartCode(_sceMpegDecoder *dec);
int _sliceHeader(_sceMpegDecoder *dec);

void _sceMpegWaitIpuIdle(_sceMpegDecoder *dec);
void _ipuCommand(_sceMpegDecoder *dec, unsigned int cmd);
int _ipuVdec(_sceMpegDecoder *dec, int table);
unsigned int _ipuShowBits(_sceMpegDecoder *dec, int n);
void _ipuFlushBits(_sceMpegDecoder *dec, int n);
unsigned int _ipuGetBits(_sceMpegDecoder *dec, int n);
void _motionVector(_sceMpegDecoder *dec, int *PMV, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale,
                   int full_pel_vector);

void _dualPrimeVector(_sceMpegDecoder *dec, int DMV[][2], int *dmvector, int mvx, int mvy);

/* Whether an IPU command leaves IPU_TOP stale, by command number: the cached bits must be refetched. */
static void _rix_000(_sceMpegMcFetch *fetch);
static void _ri0_000(_sceMpegMcFetch *fetch);
static void _rix_001(_sceMpegMcFetch *fetch);
static void _ri0_001(_sceMpegMcFetch *fetch);
static void _rix_010(_sceMpegMcFetch *fetch);
static void _ri0_010(_sceMpegMcFetch *fetch);
static void _rix_011(_sceMpegMcFetch *fetch);
static void _ri0_011(_sceMpegMcFetch *fetch);
static void _rix_100(_sceMpegMcFetch *fetch);
static void _ri0_100(_sceMpegMcFetch *fetch);
static void _rix_101(_sceMpegMcFetch *fetch);
static void _ri0_101(_sceMpegMcFetch *fetch);
static void _rix_110(_sceMpegMcFetch *fetch);
static void _ri0_110(_sceMpegMcFetch *fetch);
static void _rix_111(_sceMpegMcFetch *fetch);
static void _ri0_111(_sceMpegMcFetch *fetch);
static void _copyAddRefImage(unsigned char *dst, short *src, short *pred);
static void _copyRefImage(unsigned char *dst, short *src);

static _sceMpegMcKernel _rix[8] = {_rix_000, _rix_001, _rix_010, _rix_011, _rix_100, _rix_101, _rix_110, _rix_111};
static _sceMpegMcKernel _ri0[8] = {_ri0_000, _ri0_001, _ri0_010, _ri0_011, _ri0_100, _ri0_101, _ri0_110, _ri0_111};

static int _invalidatesBits[10] = {1, 1, 0, 0, 0, 1, 1, 1, 1, 1};

/* Stops the IPU's DMA channels and resets it when the stream is aborted. */
#define ABORT_IPU()                                         \
    {                                                       \
        int intr = DIntr();                                 \
        D_ENABLEW = D_ENABLER | D_ENABLE_CPND;              \
        D4_CHCR = 0;                                        \
        D3_CHCR = 0;                                        \
        D_ENABLEW = D_ENABLER & ~D_ENABLE_CPND;             \
        if (intr) {                                         \
            EIntr();                                        \
        }                                                   \
        D3_QWC = 0;                                         \
        D4_QWC = 0;                                         \
        IPU_CTRL = IPU_CTRL_RST;                            \
    }

/* Waits for the IPU to finish a command, feeding the stream every so often. */
#define IPU_WAIT(dec)                                                                    \
    {                                                                                    \
        int polls = 0;                                                                   \
        while ((IPU_CTRL & (IPU_CTRL_BUSY | IPU_CTRL_ECD)) == IPU_CTRL_BUSY && !(dec)->abort) { \
            if (polls++ > POLLS_PER_NODATA) {                                            \
                _sceMpegDispatchMpegCbNodata((dec)->mp);                                 \
                polls = 0;                                                               \
            }                                                                            \
        }                                                                                \
    }


/* Places the decoded macroblock: starts motion compensation for a predicted one and points its buffer at
   its spot in the picture being decoded. */
int _motionCompensation(_sceMpegDecoder *dec, int MBA, int MBAinc, int macroblock_type, int motion_type,
                        int PMV[2][2][2], int mv_field_sel[2][2], int dmvector[2])
{
    int intra = macroblock_type & MB_INTRA;
    int bx = MBA % dec->mb_width;
    int by = MBA / dec->mb_width;
    int x = bx * 16;
    int y = by * 16;
    _sceMpegPicture *picture;

    if (intra) {
        while ((D9_CHCR >> 8) & 1)
            ;
        dec->spr[dec->mb_buffer].predicted = 0;
    } else {
        if ((unsigned int)(motion_type - 1) >= 3) {
            _sceMpegError1(dec, "Invalid modion type -- ignored(%d)", motion_type);
            dec->error = 1;
            return 0;
        }
        _getAllRefs(dec, x, y, macroblock_type, motion_type, PMV, mv_field_sel, dmvector);
        while ((D9_CHCR >> 8) & 1)
            ;
        _dmaRefImage(dec);
        dec->spr[dec->mb_buffer].predicted = 1;
    }
    if (MBAinc == 1 && (macroblock_type & MB_PATTERN)) {
        dec->spr[dec->mb_buffer].skipped = MBAinc;
    } else {
        dec->spr[dec->mb_buffer].skipped = 0;
    }
    dec->spr[dec->mb_buffer].intra = intra;
    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        dec->spr[dec->mb_buffer].dest =
            dec->slots[0].decode->base + (bx * dec->slots[0].decode->mb_height + by) * 384;
    } else {
        picture = dec->picture_structure == MPEG_BOTTOM_FIELD ? dec->slots[2].decode : dec->slots[1].decode;
        dec->spr[dec->mb_buffer].dest = picture->base + (bx * picture->mb_height + by) * 384;
    }
    return 1;
}

/* Fetches the reference blocks a predicted macroblock is built from: forward, then backward averaged with it. */
void _getAllRefs(_sceMpegDecoder *dec, int x, int y, int macroblock_type, int motion_type, int PMV[2][2][2],
                      int mv_field_sel[2][2], int dmvector[2])
{
    int bottom;
    int dstParity = 1;
    int average = 0;
    int DMV[2][2];
    _sceMpegPicture *refs[2][2];

    dec->spr[dec->mb_buffer].pred_count = 0;
    if ((macroblock_type & MB_MOTION_FORWARD) || dec->picture_coding_type == P_TYPE) {
        if (dec->picture_structure == MPEG_FRAME_PICTURE) {
            if (motion_type == MC_FRAME || !(macroblock_type & MB_MOTION_FORWARD)) {
                _getRef0(dec, dec->slots[0].ref_image, 0, 0, 0, 16, x, y, PMV[0][0][0], PMV[0][0][1], 0, 0);
            } else if (motion_type == MC_FIELD) {
                _getRef0(dec, dec->slots[0].ref_image, mv_field_sel[0][0], 0, 0, 8, x, y, PMV[0][0][0],
             PMV[0][0][1] >> 1, MC_FIELD, 0);
                _getRef0(dec, dec->slots[0].ref_image, mv_field_sel[1][0], 1, 0, 8, x, y, PMV[1][0][0],
             PMV[1][0][1] >> 1, MC_FIELD, 0);
            } else if (motion_type == MC_DMV) {
                _dualPrimeVector(dec, DMV, dmvector, PMV[0][0][0], PMV[0][0][1] >> 1);
                _getRef0(dec, dec->slots[0].ref_image, 0, 0, 0, 8, x, y, PMV[0][0][0], PMV[0][0][1] >> 1, 1, 0);
                _getRef0(dec, dec->slots[0].ref_image, 1, 0, 0, 8, x, y, DMV[0][0], DMV[0][1], 1, 1);
                _getRef0(dec, dec->slots[0].ref_image, 1, 1, 0, 8, x, y, PMV[0][0][0], PMV[0][0][1] >> 1, 1, 0);
                _getRef0(dec, dec->slots[0].ref_image, 0, 1, 0, 8, x, y, DMV[1][0], DMV[1][1], 1, 1);
            } else {
                _sceMpegError1(dec, "(a) invalid motion_type(%d)-0", motion_type);
            }
        } else {
            refs[0][0] = dec->slots[1].ref_image;
            refs[0][1] = dec->slots[2].ref_image;
            refs[1][0] = dec->slots[1].prev_image;
            refs[1][1] = dec->slots[2].prev_image;
            bottom = dec->picture_structure == MPEG_BOTTOM_FIELD;
            if (dec->picture_coding_type == P_TYPE && dec->second_field && bottom != mv_field_sel[0][0]) {
                dstParity = 1;
            } else {
                dstParity = 0;
            }
            if (motion_type == MC_FIELD || !(macroblock_type & MB_MOTION_FORWARD)) {
                _getRef0(dec, refs[dstParity][mv_field_sel[0][0]], 0, 0, 0, 16, x, y, PMV[0][0][0], PMV[0][0][1], 0,
             0);
            } else if (motion_type == MC_16X8) {
                _getRef0(dec, refs[dstParity][mv_field_sel[0][0]], 0, 0, 0, 8, x, y, PMV[0][0][0], PMV[0][0][1], 0,
             0);
                if (dec->picture_coding_type == P_TYPE && dec->second_field && bottom != mv_field_sel[1][0]) {
                    dstParity = 1;
                } else {
                    dstParity = 0;
                }
                _getRef0(dec, refs[dstParity][mv_field_sel[1][0]], 0, 0, 8, 8, x, y, PMV[1][0][0], PMV[1][0][1], 0,
             0);
            } else if (motion_type == MC_DMV) {
                if (dec->second_field) {
                    dstParity = 1;
                } else {
                    dstParity = 0;
                }
                _dualPrimeVector(dec, DMV, dmvector, PMV[0][0][0], PMV[0][0][1]);
                _getRef0(dec, refs[0][bottom], 0, 0, 0, 16, x, y, PMV[0][0][0], PMV[0][0][1], 0, 0);
                _getRef0(dec, refs[dstParity][!bottom], 0, 0, 0, 16, x, y, DMV[0][0], DMV[0][1], 0, 1);
            } else {
                _sceMpegError1(dec, "(b) invalid motion_type(%d)-1", motion_type);
            }
        }
        average = 1;
    }
    if (macroblock_type & MB_MOTION_BACKWARD) {
        if (dec->picture_structure == MPEG_FRAME_PICTURE) {
            dstParity = 1;
            if (motion_type == MC_FRAME) {
                _getRef0(dec, dec->slots[0].prev_image, 0, 0, 0, 16, x, y, PMV[0][1][0], PMV[0][1][1], 0, average);
            } else {
                _getRef0(dec, dec->slots[0].prev_image, mv_field_sel[0][1], 0, 0, 8, x, y, PMV[0][1][0],
             PMV[0][1][1] >> 1, dstParity, average);
                _getRef0(dec, dec->slots[0].prev_image, mv_field_sel[1][1], 1, 0, 8, x, y, PMV[1][1][0],
             PMV[1][1][1] >> 1, dstParity, average);
            }
        } else if (motion_type == MC_FIELD) {
            _getRef0(dec, mv_field_sel[0][1] ? dec->slots[2].prev_image : dec->slots[1].prev_image, 0, 0, 0, 16, x, y,
                     PMV[0][1][0], PMV[0][1][1], 0, average);
        } else if (motion_type == MC_16X8) {
            _getRef0(dec, mv_field_sel[0][1] ? dec->slots[2].prev_image : dec->slots[1].prev_image, 0, 0, 0, 8, x, y,
                     PMV[0][1][0], PMV[0][1][1], 0, average);
            _getRef0(dec, mv_field_sel[1][1] ? dec->slots[2].prev_image : dec->slots[1].prev_image, 0, 0, 8, 8, x, y,
                     PMV[1][1][0], PMV[1][1][1], 0, average);
        } else {
            _sceMpegError1(dec, "(c) invalid motion_type(%d)-2", motion_type);
        }
    }
}

/* Sets up the luma and chroma fetches of one prediction from `ref` and picks their kernels: the block the vector
   lands in, the rows taken from it and from the row below, and where in the work area they go. */
void _getRef0(_sceMpegDecoder *dec, _sceMpegPicture *ref, int refParity, int dstParity, int dstRow, int rows,
              int x, int y, int mvx, int mvy, int fieldMode, int average)
{
    unsigned int work;
    int n;
    _sceMpegMcFetch *luma;
    _sceMpegMcFetch *chroma;
    int lx;
    int ly;
    int lbx;
    int lby;
    int ry;
    int hx;
    int hy;
    int mode;
    int block;
    unsigned char *buffer;
    unsigned char *cbuffer;
    int cmvx;
    int cmvy;
    int cbx;
    int cby;
    int crow;
    int crows;

    work = dec->mc_work;
    n = dec->spr[dec->mb_buffer].pred_count;
    luma = &dec->spr[dec->mb_buffer].luma[n];
    chroma = &dec->spr[dec->mb_buffer].chroma[n];
    lx = (mvx >> 1) + x;
    if (fieldMode) {
        ly = ((mvy >> 1) << 1) + (dstRow + refParity) + y;
    } else {
        ly = (mvy >> 1) + (dstRow + refParity) + y;
    }
    hy = mvy & 1;
    hx = mvx & 1;
    lbx = lx >> 4;
    lby = ly >> 4;
    block = lbx * ref->mb_height + lby;
    luma->column = lx - (lbx << 4);
    luma->dst = (short *)(work + ((dstParity + dstRow) << 5));
    ry = ly - (lby << 4);
    if (hy) {
        if (ry + (rows << fieldMode) >= 16) {
            luma->rows = (16 >> fieldMode) - (ry >> fieldMode) - 1;
            luma->rows_below = rows - luma->rows;
        } else {
            luma->rows = rows;
            luma->rows_below = 0;
        }
    } else {
        if (ry + (rows << fieldMode) >= 17) {
            luma->rows = (16 >> fieldMode) - (ry >> fieldMode);
            luma->rows_below = rows - luma->rows;
        } else {
            luma->rows = rows;
            luma->rows_below = 0;
        }
    }
    buffer = (unsigned char *)dec->spr[dec->mb_buffer].src + n * 1536;
    luma->left = buffer + ry * 16;
    luma->right = buffer + (ry * 16 + 768);
    luma->pitch = 16 << fieldMode;
    mode = (average << 2) | (hx << 1) | hy;
    /* The chroma fetch reuses the luma coordinates, half-sample flags and (for the row) ly. */
    /* matching construct: gen.py statement-order search — order of the chroma setup statements */
    cmvy = mvy / 2;
    crows = rows >> 1;
    cmvx = mvx / 2;
    lx = (cmvx >> 1) + (x >> 1);
    crow = dstRow >> 1;
    if (fieldMode) {
        ly = ((cmvy >> 1) << 1) + (crow + refParity) + (y >> 1);
    } else {
        ly = (cmvy >> 1) + (crow + refParity) + (y >> 1);
    }
    cby = ly >> 3;
    ly -= cby << 3;
    cbx = lx >> 3;
    hx = cmvx & 1;
    hy = cmvy & 1;
    chroma->column = lx - (cbx << 3);
    chroma->dst = (short *)(work + 512 + ((dstParity + crow) << 4));
    if (hy) {
        if (ly + (crows << fieldMode) >= 8) {
            chroma->rows = (8 >> fieldMode) - (ly >> fieldMode) - 1;
            chroma->rows_below = crows - chroma->rows;
        } else {
            chroma->rows = crows;
            chroma->rows_below = 0;
        }
    } else {
        if (ly + (crows << fieldMode) >= 9) {
            chroma->rows = (8 >> fieldMode) - (ly >> fieldMode);
            chroma->rows_below = crows - chroma->rows;
        } else {
            chroma->rows = crows;
            chroma->rows_below = 0;
        }
    }
    cbuffer = buffer + ((cbx - lbx) * 2 + (cby - lby)) * 384;
    chroma->left = cbuffer + (ly * 8 + 256);
    chroma->right = cbuffer + (ly * 8 + 1024);
    chroma->pitch = 8 << fieldMode;
    dec->spr[dec->mb_buffer].block[n] = (unsigned char *)ref->base + block * 384;
    dec->spr[dec->mb_buffer].block_right[n] = (unsigned char *)ref->base + (block + ref->mb_height) * 384;
    dec->spr[dec->mb_buffer].luma_kernel[n] = _rix[mode];
    dec->spr[dec->mb_buffer].chroma_kernel[n] = _ri0[(average << 2) | (hx << 1) | hy];
    dec->spr[dec->mb_buffer].pred_count++;
}

/* Runs the prediction kernels of a decoded macroblock and adds the coefficients into its picture. */
void _doMC(_sceMpegDecoder *dec, int buffer)
{
    int n;

    if (dec->spr[buffer].predicted) {
        for (n = 0; n < dec->spr[buffer].pred_count; n++) {
            dec->spr[buffer].luma_kernel[n](&dec->spr[buffer].luma[n]);
            dec->spr[buffer].chroma_kernel[n](&dec->spr[buffer].chroma[n]);
        }
    }
    if (dec->spr[buffer].intra && dec->spr[buffer].empty) {
        _sceMpegError(dec, "intra && skip MB");
    }
    if (dec->spr[buffer].intra) {
        _copyRefImage((unsigned char *)dec->spr[buffer].dest, (short *)dec->spr[buffer].dst);
    } else if (dec->spr[buffer].empty) {
        _copyRefImage((unsigned char *)dec->spr[buffer].dest, (short *)dec->mc_work);
    } else {
        _copyAddRefImage((unsigned char *)dec->spr[buffer].dest, (short *)dec->mc_work,
                         (short *)dec->spr[buffer].dst);
    }
}

static void _rix_000(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "sll $11,$12,0x1\n"
        "li $15,-1\n"
        "mtsab $13,0\n"
        "1:\n"
        "lq $8,0($5)\n"
        "addi $7,$7,-1\n"
        "lq $9,0($6)\n"
        "addu $5,$5,$12\n"
        "qfsrv $10,$9,$8\n"
        "pextlb $8,$0,$10\n"
        "pextub $9,$0,$10\n"
        "sq $8,0($14)\n"
        "addu $6,$6,$12\n"
        "sq $9,16($14)\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$11\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $10,$15,$7\n"
        "bne $10,$0,1b\n"
        "daddu $15,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_000(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "sll $11,$12,0x1\n"
        "mtsab $13,0\n"
        "addiu $24,$0,-1\n"
        "1:\n"
        "lw $7,8($4)\n"
        "li $15,-1\n"
        "2:\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "qfsrv $9,$8,$8\n"
        "pextlb $8,$0,$9\n"
        "sq $8,0($14)\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$12\n"
        "addu $14,$14,$11\n"
        "bgtz $7,2b\n"
        "addu $6,$6,$12\n"
        "addiu $5,$5,320\n"
        "addiu $6,$6,320\n"
        "lw $7,12($4)\n"
        "and $10,$15,$7\n"
        "bne $10,$0,2b\n"
        "daddu $15,$0,$0\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "bne $24,$0,1b\n"
        "daddu $24,$0,$0\n"
        ".set reorder\n"
    );
}

static void _rix_001(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $24,16($4)\n"
        "lq $8,0($5)\n"
        "sll $12,$24,0x1\n"
        "lq $9,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $10,$9,$8\n"
        "pextlb $8,$0,$10\n"
        "addiu $11,$0,-1\n"
        "beq $7,$0,2f\n"
        "pextub $9,$0,$10\n"
        "1:\n"
        "addu $5,$5,$24\n"
        "addu $6,$6,$24\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "qfsrv $2,$15,$10\n"
        "pextlb $10,$0,$2\n"
        "addi $7,$7,-1\n"
        "pextub $15,$0,$2\n"
        "paddh $2,$8,$10\n"
        "paddh $3,$9,$15\n"
        "por $8,$10,$0\n"
        "por $9,$15,$0\n"
        "paddh $2,$2,$25\n"
        "paddh $3,$3,$25\n"
        "psrlh $2,$2,0x1\n"
        "psrlh $3,$3,0x1\n"
        "sq $2,0($14)\n"
        "sq $3,16($14)\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$12\n"
        "2:\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_001(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "addiu $11,$0,1\n"
        "sll $24,$12,0x1\n"
        "mtsab $13,0\n"
        "1:\n"
        "lw $7,8($4)\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "qfsrv $8,$8,$8\n"
        "ori $11,$11,0x8000\n"
        "beq $7,$0,3f\n"
        "pextlb $15,$0,$8\n"
        "2:\n"
        "addu $5,$5,$12\n"
        "addu $6,$6,$12\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $10,$0,$8\n"
        "addi $7,$7,-1\n"
        "paddh $9,$10,$15\n"
        "por $15,$10,$0\n"
        "paddh $10,$9,$25\n"
        "psrlh $10,$10,0x1\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$24\n"
        "3:\n"
        "psrah $10,$11,0xf\n"
        "addiu $5,$5,320\n"
        "lw $7,12($4)\n"
        "addiu $6,$6,320\n"
        "and $10,$10,$7\n"
        "bne $10,$0,2b\n"
        "andi $11,$11,0x7fff\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "andi $10,$11,0x1\n"
        "bne $10,$0,1b\n"
        "andi $11,$11,0xfffe\n"
        ".set reorder\n"
    );
}

static void _rix_010(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "addiu $24,$0,1\n"
        "lw $9,16($4)\n"
        "sll $8,$9,0x1\n"
        "addiu $11,$0,-1\n"
        "1:\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $2,$15,$10\n"
        "qfsrv $3,$10,$15\n"
        "pextlb $10,$0,$2\n"
        "addi $7,$7,-1\n"
        "pextub $15,$0,$2\n"
        "mtsab $24,0\n"
        "qfsrv $3,$3,$2\n"
        "pextlb $2,$0,$3\n"
        "pextub $3,$0,$3\n"
        "paddh $10,$10,$2\n"
        "paddh $15,$15,$3\n"
        "paddh $2,$10,$25\n"
        "paddh $3,$15,$25\n"
        "psrlh $2,$2,0x1\n"
        "psrlh $3,$3,0x1\n"
        "sq $2,0($14)\n"
        "sq $3,16($14)\n"
        "addu $5,$5,$9\n"
        "addu $6,$6,$9\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$8\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $12,$11,$7\n"
        "bne $12,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_010(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "addiu $24,$0,1\n"
        "addiu $12,$0,-1\n"
        "lw $3,16($4)\n"
        "sll $2,$3,0x1\n"
        "1:\n"
        "lw $7,8($4)\n"
        "addiu $11,$0,-1\n"
        "2:\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "mtsab $13,0\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$3\n"
        "addu $6,$6,$3\n"
        "mtsab $24,0\n"
        "qfsrv $10,$0,$8\n"
        "pextlb $8,$0,$10\n"
        "paddh $10,$9,$8\n"
        "paddh $10,$10,$25\n"
        "psrlh $10,$10,0x1\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$2\n"
        "addiu $5,$5,320\n"
        "addiu $6,$6,320\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,2b\n"
        "daddu $11,$0,$0\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "bne $12,$0,1b\n"
        "daddu $12,$0,$0\n"
        ".set reorder\n"
    );
}

static void _rix_011(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "psllh $25,$25,0x1\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "addiu $24,$0,1\n"
        "lq $8,0($5)\n"
        "lq $9,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $10,$9,$8\n"
        "qfsrv $15,$8,$9\n"
        "pextlb $8,$0,$10\n"
        "pextub $9,$0,$10\n"
        "addiu $11,$0,-1\n"
        "mtsab $24,0\n"
        "qfsrv $15,$15,$10\n"
        "pextlb $10,$0,$15\n"
        "pextub $15,$0,$15\n"
        "paddh $8,$8,$10\n"
        "beq $7,$0,2f\n"
        "paddh $9,$9,$15\n"
        "1:\n"
        "addu $5,$5,$12\n"
        "addu $6,$6,$12\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $2,$15,$10\n"
        "qfsrv $3,$10,$15\n"
        "pextlb $10,$0,$2\n"
        "addi $7,$7,-1\n"
        "pextub $15,$0,$2\n"
        "mtsab $24,0\n"
        "qfsrv $3,$3,$2\n"
        "pextlb $2,$0,$3\n"
        "pextub $3,$0,$3\n"
        "paddh $10,$10,$2\n"
        "paddh $15,$15,$3\n"
        "paddh $2,$8,$10\n"
        "paddh $3,$9,$15\n"
        "por $8,$10,$0\n"
        "por $9,$15,$0\n"
        "paddh $2,$2,$25\n"
        "paddh $3,$3,$25\n"
        "psrlh $2,$2,0x2\n"
        "psrlh $3,$3,0x2\n"
        "sq $2,0($14)\n"
        "sll $10,$12,0x1\n"
        "sq $3,16($14)\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$10\n"
        "2:\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_011(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "psllh $25,$25,0x1\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "addiu $24,$0,1\n"
        "addiu $11,$0,1\n"
        "1:\n"
        "lw $7,8($4)\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "mtsab $13,0\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addu $5,$5,$12\n"
        "ori $11,$11,0x8000\n"
        "mtsab $24,0\n"
        "qfsrv $10,$0,$8\n"
        "pextlb $8,$0,$10\n"
        "beq $7,$0,3f\n"
        "paddh $15,$9,$8\n"
        "2:\n"
        "addu $6,$6,$12\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "mtsab $13,0\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$12\n"
        "mtsab $24,0\n"
        "qfsrv $10,$0,$8\n"
        "pextlb $8,$0,$10\n"
        "paddh $10,$9,$8\n"
        "paddh $9,$10,$15\n"
        "por $15,$10,$0\n"
        "paddh $10,$9,$25\n"
        "sll $8,$12,0x1\n"
        "psrlh $10,$10,0x2\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$8\n"
        "3:\n"
        "psrah $10,$11,0xf\n"
        "addiu $5,$5,320\n"
        "lw $7,12($4)\n"
        "addiu $6,$6,320\n"
        "and $10,$10,$7\n"
        "bne $10,$0,2b\n"
        "andi $11,$11,0x7fff\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "andi $10,$11,0x1\n"
        "bne $10,$0,1b\n"
        "andi $11,$11,0xfffe\n"
        ".set reorder\n"
    );
}

static void _rix_100(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $9,16($4)\n"
        "sll $8,$9,0x1\n"
        "addiu $11,$0,-1\n"
        "mtsab $13,0\n"
        "1:\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "qfsrv $2,$15,$10\n"
        "pextlb $10,$0,$2\n"
        "pextub $15,$0,$2\n"
        "lq $2,0($14)\n"
        "lq $3,16($14)\n"
        "paddh $2,$2,$10\n"
        "paddh $3,$3,$15\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "paddh $10,$2,$25\n"
        "psrlh $2,$10,0x1\n"
        "paddh $10,$3,$25\n"
        "psrlh $3,$10,0x1\n"
        "sq $2,0($14)\n"
        "sq $3,16($14)\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$9\n"
        "addu $14,$14,$8\n"
        "bgtz $7,1b\n"
        "addu $6,$6,$9\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $12,$11,$7\n"
        "bne $12,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_100(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "addiu $12,$0,-1\n"
        "lw $3,16($4)\n"
        "sll $2,$3,0x1\n"
        "mtsab $13,0\n"
        "1:\n"
        "lw $7,8($4)\n"
        "addiu $11,$0,-1\n"
        "2:\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$3\n"
        "addu $6,$6,$3\n"
        "lq $8,0($14)\n"
        "paddh $10,$9,$8\n"
        "pcgth $9,$10,$0\n"
        "psrlh $9,$9,0xf\n"
        "paddh $10,$10,$9\n"
        "psrlh $10,$10,0x1\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$2\n"
        "addiu $5,$5,320\n"
        "addiu $6,$6,320\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,2b\n"
        "daddu $11,$0,$0\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "bne $12,$0,1b\n"
        "daddu $12,$0,$0\n"
        ".set reorder\n"
    );
}

static void _rix_101(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "lq $8,0($5)\n"
        "lq $9,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $10,$9,$8\n"
        "sll $24,$12,0x1\n"
        "pextlb $8,$0,$10\n"
        "addiu $11,$0,-1\n"
        "beq $7,$0,2f\n"
        "pextub $9,$0,$10\n"
        "1:\n"
        "addu $5,$5,$12\n"
        "addu $6,$6,$12\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "qfsrv $2,$15,$10\n"
        "pextlb $10,$0,$2\n"
        "addi $7,$7,-1\n"
        "pextub $15,$0,$2\n"
        "paddh $2,$8,$10\n"
        "paddh $3,$9,$15\n"
        "por $8,$10,$0\n"
        "por $9,$15,$0\n"
        "paddh $2,$2,$25\n"
        "paddh $3,$3,$25\n"
        "psrlh $2,$2,0x1\n"
        "psrlh $3,$3,0x1\n"
        "lq $10,0($14)\n"
        "lq $15,16($14)\n"
        "paddh $2,$2,$10\n"
        "paddh $3,$3,$15\n"
        "paddh $10,$2,$25\n"
        "psrlh $2,$10,0x1\n"
        "pcgth $10,$3,$0\n"
        "psrlh $10,$10,0xf\n"
        "paddh $10,$3,$10\n"
        "psrlh $3,$10,0x1\n"
        "sq $2,0($14)\n"
        "sq $3,16($14)\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$24\n"
        "2:\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_101(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "addiu $11,$0,1\n"
        "sll $24,$12,0x1\n"
        "mtsab $13,0\n"
        "1:\n"
        "lw $7,8($4)\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "qfsrv $8,$8,$8\n"
        "ori $11,$11,0x8000\n"
        "beq $7,$0,3f\n"
        "pextlb $15,$0,$8\n"
        "2:\n"
        "addu $5,$5,$12\n"
        "addu $6,$6,$12\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $10,$0,$8\n"
        "addi $7,$7,-1\n"
        "paddh $9,$10,$15\n"
        "por $15,$10,$0\n"
        "paddh $10,$9,$25\n"
        "psrlh $10,$10,0x1\n"
        "lq $8,0($14)\n"
        "paddh $10,$10,$8\n"
        "pcgth $9,$10,$0\n"
        "psrlh $9,$9,0xf\n"
        "paddh $10,$10,$9\n"
        "psrlh $10,$10,0x1\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$24\n"
        "3:\n"
        "psrah $10,$11,0xf\n"
        "addiu $5,$5,320\n"
        "lw $7,12($4)\n"
        "addiu $6,$6,320\n"
        "and $10,$10,$7\n"
        "bne $10,$0,2b\n"
        "andi $11,$11,0x7fff\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "andi $10,$11,0x1\n"
        "bne $10,$0,1b\n"
        "andi $11,$11,0xfffe\n"
        ".set reorder\n"
    );
}

static void _rix_110(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "addiu $24,$0,1\n"
        "lw $9,16($4)\n"
        "sll $8,$9,0x1\n"
        "addiu $11,$0,-1\n"
        "1:\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $2,$15,$10\n"
        "qfsrv $3,$10,$15\n"
        "pextlb $10,$0,$2\n"
        "addi $7,$7,-1\n"
        "pextub $15,$0,$2\n"
        "mtsab $24,0\n"
        "qfsrv $3,$3,$2\n"
        "pextlb $2,$0,$3\n"
        "pextub $3,$0,$3\n"
        "paddh $10,$10,$2\n"
        "paddh $15,$15,$3\n"
        "paddh $2,$10,$25\n"
        "paddh $3,$15,$25\n"
        "psrlh $2,$2,0x1\n"
        "psrlh $3,$3,0x1\n"
        "lq $10,0($14)\n"
        "lq $15,16($14)\n"
        "paddh $2,$2,$10\n"
        "paddh $3,$3,$15\n"
        "paddh $10,$2,$25\n"
        "psrlh $2,$10,0x1\n"
        "pcgth $10,$3,$0\n"
        "psrlh $10,$10,0xf\n"
        "paddh $10,$3,$10\n"
        "psrlh $3,$10,0x1\n"
        "sq $2,0($14)\n"
        "sq $3,16($14)\n"
        "addu $5,$5,$9\n"
        "addu $6,$6,$9\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$8\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $12,$11,$7\n"
        "bne $12,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_110(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "addiu $24,$0,1\n"
        "addiu $12,$0,-1\n"
        "lw $3,16($4)\n"
        "sll $2,$3,0x1\n"
        "1:\n"
        "lw $7,8($4)\n"
        "addiu $11,$0,-1\n"
        "2:\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "mtsab $13,0\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$3\n"
        "addu $6,$6,$3\n"
        "mtsab $24,0\n"
        "qfsrv $10,$0,$8\n"
        "pextlb $8,$0,$10\n"
        "paddh $10,$9,$8\n"
        "paddh $10,$10,$25\n"
        "psrlh $10,$10,0x1\n"
        "lq $8,0($14)\n"
        "paddh $10,$10,$8\n"
        "pcgth $9,$10,$0\n"
        "psrlh $9,$9,0xf\n"
        "paddh $10,$10,$9\n"
        "psrlh $10,$10,0x1\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$2\n"
        "addiu $5,$5,320\n"
        "addiu $6,$6,320\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,2b\n"
        "daddu $11,$0,$0\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "bne $12,$0,1b\n"
        "daddu $12,$0,$0\n"
        ".set reorder\n"
    );
}

static void _rix_111(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "psllh $25,$25,0x1\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $7,8($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $24,16($4)\n"
        "addiu $12,$0,1\n"
        "lq $8,0($5)\n"
        "lq $9,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $10,$9,$8\n"
        "qfsrv $15,$8,$9\n"
        "pextlb $8,$0,$10\n"
        "pextub $9,$0,$10\n"
        "addiu $11,$0,-1\n"
        "mtsab $12,0\n"
        "qfsrv $15,$15,$10\n"
        "pextlb $10,$0,$15\n"
        "pextub $15,$0,$15\n"
        "paddh $8,$8,$10\n"
        "beq $7,$0,2f\n"
        "paddh $9,$9,$15\n"
        "1:\n"
        "addu $5,$5,$24\n"
        "addu $6,$6,$24\n"
        "lq $10,0($5)\n"
        "lq $15,0($6)\n"
        "mtsab $13,0\n"
        "qfsrv $2,$15,$10\n"
        "qfsrv $3,$10,$15\n"
        "pextlb $10,$0,$2\n"
        "addi $7,$7,-1\n"
        "pextub $15,$0,$2\n"
        "mtsab $12,0\n"
        "qfsrv $3,$3,$2\n"
        "pextlb $2,$0,$3\n"
        "pextub $3,$0,$3\n"
        "paddh $10,$10,$2\n"
        "paddh $15,$15,$3\n"
        "paddh $2,$8,$10\n"
        "paddh $3,$9,$15\n"
        "por $8,$10,$0\n"
        "por $9,$15,$0\n"
        "paddh $2,$2,$25\n"
        "paddh $3,$3,$25\n"
        "psrlh $2,$2,0x2\n"
        "psrlh $3,$3,0x2\n"
        "lq $10,0($14)\n"
        "lq $15,16($14)\n"
        "paddh $2,$2,$10\n"
        "paddh $3,$3,$15\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "paddh $10,$2,$25\n"
        "psrlh $2,$10,0x1\n"
        "paddh $10,$3,$25\n"
        "psrlh $3,$10,0x1\n"
        "sq $2,0($14)\n"
        "sll $10,$24,0x1\n"
        "sq $3,16($14)\n"
        "bgtz $7,1b\n"
        "addu $14,$14,$10\n"
        "2:\n"
        "addiu $5,$5,128\n"
        "addiu $6,$6,128\n"
        "lw $7,12($4)\n"
        "and $10,$11,$7\n"
        "bne $10,$0,1b\n"
        "daddu $11,$0,$0\n"
        ".set reorder\n"
    );
}

static void _ri0_111(_sceMpegMcFetch *fetch)
{
    __asm__(
        ".set noreorder\n"
        "pnor $25,$0,$0\n"
        "psrlh $25,$25,0xf\n"
        "psllh $25,$25,0x1\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "lw $13,4($4)\n"
        "lw $12,16($4)\n"
        "addiu $24,$0,1\n"
        "addiu $11,$0,1\n"
        "1:\n"
        "lw $7,8($4)\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "mtsab $13,0\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addu $5,$5,$12\n"
        "ori $11,$11,0x8000\n"
        "mtsab $24,0\n"
        "qfsrv $10,$0,$8\n"
        "pextlb $8,$0,$10\n"
        "beq $7,$0,3f\n"
        "paddh $15,$9,$8\n"
        "2:\n"
        "addu $6,$6,$12\n"
        "ld $8,0($5)\n"
        "ld $9,0($6)\n"
        "pcpyld $8,$9,$8\n"
        "mtsab $13,0\n"
        "qfsrv $8,$8,$8\n"
        "pextlb $9,$0,$8\n"
        "addi $7,$7,-1\n"
        "addu $5,$5,$12\n"
        "mtsab $24,0\n"
        "qfsrv $10,$0,$8\n"
        "pextlb $8,$0,$10\n"
        "paddh $10,$9,$8\n"
        "paddh $9,$10,$15\n"
        "por $15,$10,$0\n"
        "paddh $10,$9,$25\n"
        "psrlh $10,$10,0x2\n"
        "lq $8,0($14)\n"
        "paddh $10,$10,$8\n"
        "pcgth $9,$10,$0\n"
        "psrlh $9,$9,0xf\n"
        "paddh $10,$10,$9\n"
        "sll $8,$12,0x1\n"
        "psrlh $10,$10,0x1\n"
        "sq $10,0($14)\n"
        "bgtz $7,2b\n"
        "addu $14,$14,$8\n"
        "3:\n"
        "psrah $10,$11,0xf\n"
        "addiu $5,$5,320\n"
        "lw $7,12($4)\n"
        "addiu $6,$6,320\n"
        "and $10,$10,$7\n"
        "bne $10,$0,2b\n"
        "andi $11,$11,0x7fff\n"
        "lw $5,20($4)\n"
        "lw $6,24($4)\n"
        "lw $14,0($4)\n"
        "addiu $5,$5,64\n"
        "addiu $6,$6,64\n"
        "addiu $14,$14,128\n"
        "andi $10,$11,0x1\n"
        "bne $10,$0,1b\n"
        "andi $11,$11,0xfffe\n"
        ".set reorder\n"
    );
}

static void _copyAddRefImage(unsigned char *dst, short *src, short *pred)
{
    __asm__(
        ".set noreorder\n"
        "addiu $12,$0,24\n"
        "lui $10,%hi(_maxval)\n"
        "addiu $10,$10,%lo(_maxval)\n"
        "lq $11,0($10)\n"
        "1:\n"
        "lq $8,0($5)\n"
        "addi $12,$12,-1\n"
        "lq $13,0($6)\n"
        "addiu $4,$4,16\n"
        "lq $9,16($5)\n"
        "paddh $8,$8,$13\n"
        "lq $2,16($6)\n"
        "pminh $8,$8,$11\n"
        "paddh $9,$9,$2\n"
        "pmaxh $8,$8,$0\n"
        "pminh $9,$9,$11\n"
        "addiu $5,$5,32\n"
        "pmaxh $9,$9,$0\n"
        "addiu $6,$6,32\n"
        "ppacb $10,$9,$8\n"
        "bne $12,$0,1b\n"
        "sq $10,-16($4)\n"
        ".set reorder\n"
    );
}

static void _copyRefImage(unsigned char *dst, short *src)
{
    __asm__(
        ".set noreorder\n"
        "addiu $12,$0,24\n"
        "lui $10,%hi(_maxval)\n"
        "addiu $10,$10,%lo(_maxval)\n"
        "lq $11,0($10)\n"
        "1:\n"
        "lq $8,0($5)\n"
        "addi $12,$12,-1\n"
        "pminh $8,$8,$11\n"
        "lq $9,16($5)\n"
        "pmaxh $8,$8,$0\n"
        "pminh $9,$9,$11\n"
        "addiu $5,$5,32\n"
        "pmaxh $9,$9,$0\n"
        "addiu $4,$4,16\n"
        "ppacb $10,$9,$8\n"
        "bne $12,$0,1b\n"
        "sq $10,-16($4)\n"
        "nop\n"
        "nop\n"
        "_maxval:\n"
        ".word 0x00ff00ff\n"
        ".word 0x00ff00ff\n"
        ".word 0x00ff00ff\n"
        ".word 0x00ff00ff\n"
        ".set reorder\n"
    );
}

void _ipuSetMpeg1(int mpeg1)
{
    IPU_CTRL = (IPU_CTRL & ~(1 << IPU_CTRL_MP1_SHIFT)) | (mpeg1 << IPU_CTRL_MP1_SHIFT);
}

/* Waits for the IPU to finish BDEC on the macroblock, feeding it when its input runs dry, and resets it when
   it reports an error. Returns 0 when the stream is aborted or the macroblock is in error. */
int _waitBdec(_sceMpegDecoder *dec)
{
    int ok = 1;
    sceMpegCbData cbdata;
    sceMpegCbData cbdma;
    long long top;
    unsigned int bp;

    _sceMpegWaitIpuIdle(dec);
    while (D3_QWC != 0 && !(IPU_CTRL & IPU_CTRL_ECD)) {
        if (D4_QWC == 0 && !(D4_CHCR & D_CHCR_STR)) {
            cbdata.type = sceMpegCbNodata;
            _sceMpegDispatchMpegCallback(dec->mp, &cbdata);
        }
        if (dec->abort) {
            ABORT_IPU();
            return 0;
        }
    }
    bp = IPU_BP;
    top = IPU_TOP64;
    dec->bits = top;
    dec->bit_count = top < 0 ? ((bp & 0x1f) ? 32 - (bp & 0x1f) : 0) : 32;
    if (IPU_CTRL & IPU_CTRL_ECD) {
        _sceMpegError(dec, "Error code detected(BDEC)");
        cbdma.type = sceMpegCbStopDMA;
        _sceMpegDispatchMpegCallback(dec->mp, &cbdma);
        IPU_CTRL = IPU_CTRL_RST;
        cbdma.type = sceMpegCbRestartDMA;
        _sceMpegDispatchMpegCallback(dec->mp, &cbdma);
        {
            int intr = DIntr();
            D_ENABLEW = D_ENABLER | D_ENABLE_CPND;
            D3_CHCR = 0;
            D_ENABLEW = D_ENABLER & ~D_ENABLE_CPND;
            if (intr) {
                EIntr();
            }
        }
        ok = 0;
        D3_QWC = 0;
    }
    return ok;
}

static int _getDmvector(_sceMpegDecoder *dec)
{
    int dmvector = _ipuVdec(dec, VDEC_DMVECTOR);

    return dmvector;
}

/* Dual-prime: the vectors to the opposite-parity fields from the transmitted one and the differential. */
void _dualPrimeVector(_sceMpegDecoder *dec, int DMV[][2], int *dmvector, int mvx, int mvy)
{
    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        if (dec->top_field_first) {
            DMV[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[1][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        } else {
            DMV[0][0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[0][1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[1][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        }
    } else {
        DMV[0][0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
        DMV[0][1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1];
        if (dec->picture_structure == MPEG_TOP_FIELD)
            DMV[0][1]--;
        else
            DMV[0][1]++;
    }
}

int _getMacroblockAddressIncrement(_sceMpegDecoder *dec)
{
    int increment = 0;
    unsigned int code;
    int more;
    unsigned int bits;

    do {
        code = _ipuVdec(dec, VDEC_MBAI);
        switch (code) {
        case MBAI_STUFFING:
            more = 1;
            break;
        case MBAI_ESCAPE:
            more = 1;
            increment += 33;
            break;
        case 0:
            bits = _ipuShowBits(dec, 11);
            if (dec->mpeg2 && bits == MPEG1_STUFFING_CODE) {
                _ipuFlushBits(dec, 11);
                more = 1;
                break;
            }
            _sceMpegError1(dec, "Invalid macroblock_address_increment code(0x%08x)", code);
            dec->error = 1;
            return 1;
        default:
            increment += code;
            more = 0;
            break;
        }
    } while (more);
    return increment;
}

int _slice0(_sceMpegDecoder *dec, int MBAmax);

/* Decodes the picture's slices. 1: decoded; 0 with the reason in the log otherwise; 4: aborted. */
int _pictureData(_sceMpegDecoder *dec)
{
    int MBAmax;
    int ret;

    dec->mb_buffer = 0;
    MBAmax = dec->mb_width * dec->mb_height;
    dec->mb_count = 0;
    if (dec->picture_structure != MPEG_FRAME_PICTURE) {
        MBAmax >>= 1;
    }
    do {
        ret = _slice0(dec, MBAmax);
    } while (ret == 1 || ret == 3);
    _sceMpegWaitIpuIdle(dec);
    if (!_waitBdec(dec)) {
        if (dec->abort) {
            return 4;
        }
        ret = 2;
    }
    while ((D9_CHCR >> 8) & 1)
        ;
    if (ret == 0) {
        _doMC(dec, dec->mb_buffer == 0);
    }
    if (ret == 1 || ret == 2) {
        _sceMpegError(dec, "= Skip to the next picture =");
    }
    return ret == 0;
}

/* The slice header up to the first macroblock: its address and a cleared set of motion predictors. */
int _sliceA0(_sceMpegDecoder *dec, int MBAmax, int *MBA, int *MBAinc, int PMV[2][2][2])
{
    int slice_vertical_position_extension;
    unsigned int code;
    int increment;

    dec->error = 0;
    _nextStartCode(dec);
    code = _ipuShowBits(dec, 32);
    if (code - 0x101 >= 0xaf) {
        _sceMpegError1(dec, "slice_start_code(0x%08x) out of range", code);
        return 2;
    }
    _ipuFlushBits(dec, 32);
    slice_vertical_position_extension = _sliceHeader(dec);
    increment = _getMacroblockAddressIncrement(dec);
    *MBAinc = increment;
    if (dec->error) {
        _sceMpegError(dec, "_sliceA0(): error happens");
        return 1;
    }
    *MBA = (((slice_vertical_position_extension << 7) + (code & 0xff) - 1) * dec->mb_width + increment) - 1;
    *MBAinc = 1;
    dec->dc_reset = 1;
    PMV[1][0][1] = 0;
    PMV[1][0][0] = 0;
    PMV[0][0][1] = 0;
    PMV[0][0][0] = 0;
    PMV[1][1][1] = 0;
    PMV[1][1][0] = 0;
    PMV[0][1][1] = 0;
    PMV[0][1][0] = 0;
    return 0;
}

int _skipMB0(_sceMpegDecoder *dec, int PMV[2][2][2], int *motion_type, int mv_field_sel[2][2], int *macroblock_type);
int _decMB0(_sceMpegDecoder *dec, int *macroblock_type, int *motion_type, int *dct_type, int PMV[2][2][2],
            int mv_field_sel[2][2], int dmvector[2]);

/* One slice. 0: picture complete; 1: resynchronise at the next slice; 2: give up on the picture;
   3: the slice ended early; 4: aborted. */
int _slice0(_sceMpegDecoder *dec, int MBAmax)
{
    int PMV[2][2][2];
    int motion_vertical_field_select[2][2];
    int dmvector[4];
    int MBA, MBAinc, macroblock_type, motion_type, dct_type;
    int ret;

    MBA = 0;
    MBAinc = 0;

    if ((ret = _sliceA0(dec, MBAmax, &MBA, &MBAinc, PMV)) != 0)
        return ret;
    dec->error = 0;

    for (;;) {
        if (MBA >= MBAmax)
            return 0;

        dec->spr[dec->mb_buffer].empty = 0;
        if (!_waitBdec(dec))
            return dec->abort == 0 ? 2 : 4;

        if (MBAinc == 0) {
            if (!_ipuShowBits(dec, 23) || dec->error) {
                dec->error = 0;
                return 3;
            } else {
                MBAinc = _getMacroblockAddressIncrement(dec);
                if (dec->error)
                    goto resync;
            }
        }

        if (MBA >= MBAmax) {
            _sceMpegError(dec, "Too many macroblocks in picture");
            return 2;
        }

        if (MBAinc == 1) {
            if (!_decMB0(dec, &macroblock_type, &motion_type, &dct_type, PMV, motion_vertical_field_select,
                         dmvector)) {
resync:
                dec->error = 0;
                return 1;
            }
        } else {
            if (!_skipMB0(dec, PMV, &motion_type, motion_vertical_field_select, &macroblock_type))
                goto fail;
        }

        if (!_motionCompensation(dec, MBA, MBAinc, macroblock_type, motion_type, PMV, motion_vertical_field_select,
                                 dmvector)) {
fail:
            dec->error = 0;
            return 2;
        }

        if (MBA)
            _doMC(dec, dec->mb_buffer ^ 1);
        MBA++;
        dec->mb_buffer ^= 1;
        MBAinc--;
    }
}

/* A skipped macroblock: no coefficients, and the prediction carries over (reset in P pictures). */
int _skipMB0(_sceMpegDecoder *dec, int PMV[2][2][2], int *motion_type, int mv_field_sel[2][2], int *macroblock_type)
{
    int ok = 1;

    dec->spr[dec->mb_buffer].empty = 1;
    dec->dc_reset = 1;
    if (dec->picture_coding_type == P_TYPE) {
        PMV[1][0][1] = 0;
        PMV[1][0][0] = 0;
        PMV[0][0][1] = 0;
        PMV[0][0][0] = 0;
    }
    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        *motion_type = MC_FRAME;
    } else {
        *motion_type = MC_FIELD;
        mv_field_sel[0][0] = mv_field_sel[0][1] = dec->picture_structure == MPEG_BOTTOM_FIELD;
    }
    if (dec->picture_coding_type == I_TYPE) {
        _sceMpegError(dec, "skiped macroblock in I picure is not allowed");
        ok = 0;
    }
    *macroblock_type &= ~MB_INTRA;
    return ok;
}

void _motionVectors(_sceMpegDecoder *dec, int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s,
                    int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale);

/* The macroblock modes and motion vectors, then the IPU's BDEC of its coefficients. */
int _decMB0(_sceMpegDecoder *dec, int *pmacroblock_type, int *pmotion_type, int *pdct_type, int PMV[2][2][2],
            int motion_vertical_field_select[2][2], int *dmvector)
{
    int macroblock_type;
    int motion_vector_count, mv_format, dmv, mvscale, dct_type;

    IPU_CTRL = (IPU_CTRL & ~(7 << IPU_CTRL_PCT_SHIFT)) | (dec->picture_coding_type << IPU_CTRL_PCT_SHIFT);
    macroblock_type = *pmacroblock_type = _ipuVdec(dec, VDEC_MB_TYPE);
    if (macroblock_type == 0) {
        _sceMpegError(dec, "Invalid macroblock_type code: 0");
        dec->error = 1;
        return 0;
    }

    if (macroblock_type & (MB_MOTION_FORWARD | MB_MOTION_BACKWARD)) {
        if (dec->picture_structure == MPEG_FRAME_PICTURE && dec->frame_pred_frame_dct)
            *pmotion_type = MC_FRAME;
        else
            *pmotion_type = _ipuGetBits(dec, 2);
    } else if ((macroblock_type & MB_INTRA) && dec->concealment_motion_vectors) {
        *pmotion_type = (dec->picture_structure == MPEG_FRAME_PICTURE) ? MC_FRAME : MC_FIELD;
    }

    if (dec->picture_structure == MPEG_FRAME_PICTURE) {
        motion_vector_count = (*pmotion_type == MC_FIELD) ? 2 : 1;
        mv_format = (*pmotion_type == MC_FRAME);
    } else {
        mv_format = 0;
        motion_vector_count = (*pmotion_type == MC_16X8) ? 2 : 1;
    }
    dmv = (*pmotion_type == MC_DMV);
    mvscale = (mv_format == 0 && dec->picture_structure == MPEG_FRAME_PICTURE);
    dct_type = (dec->picture_structure == MPEG_FRAME_PICTURE) && (!dec->frame_pred_frame_dct)
                       && (*pmacroblock_type & (MB_INTRA | MB_PATTERN))
                   ? _ipuGetBits(dec, 1)
                   : 0;
    *pdct_type = dct_type;

    if (*pmacroblock_type & MB_QUANT)
        dec->quantiser_scale_code = _ipuGetBits(dec, 5);

    if ((*pmacroblock_type & MB_MOTION_FORWARD) || ((*pmacroblock_type & MB_INTRA) && dec->concealment_motion_vectors)) {
        if (dec->mpeg2)
            _motionVectors(dec, PMV, dmvector, motion_vertical_field_select, 0, motion_vector_count, mv_format,
                           dec->f_code[0][0] - 1, dec->f_code[0][1] - 1, dmv, mvscale);
        else
            _motionVector(dec, PMV[0][0], dmvector, dec->forward_f_code - 1, dec->forward_f_code - 1, 0, 0,
                          dec->full_pel_forward_vector);
    }
    if (dec->error)
        return 0;

    if (*pmacroblock_type & MB_MOTION_BACKWARD) {
        if (dec->mpeg2)
            _motionVectors(dec, PMV, dmvector, motion_vertical_field_select, 1, motion_vector_count, mv_format,
                           dec->f_code[1][0] - 1, dec->f_code[1][1] - 1, 0, mvscale);
        else
            _motionVector(dec, PMV[0][1], dmvector, dec->backward_f_code - 1, dec->backward_f_code - 1, 0, 0,
                          dec->full_pel_backward_vector);
    }
    if (dec->error)
        return 0;

    if ((*pmacroblock_type & MB_INTRA) && dec->concealment_motion_vectors)
        _ipuFlushBits(dec, 1); /* marker bit */

    if (*pmacroblock_type & (MB_INTRA | MB_PATTERN)) {
        _sprClear(dec->spr[dec->mb_buffer].dst, 0x300);
        _sceMpegWaitIpuIdle(dec);
        _ipuCommand(dec, IPU_BDEC | ((*pmacroblock_type & MB_INTRA) << 27) | (dec->dc_reset << 26)
                             | (*pdct_type << 25) | (dec->quantiser_scale_code << 16));
    } else {
        dec->spr[dec->mb_buffer].empty = 1;
    }
    dec->dc_reset = 0;
    if (dec->error)
        return 0;

    if (!(*pmacroblock_type & MB_INTRA))
        dec->dc_reset = 1;

    if ((*pmacroblock_type & MB_INTRA) && !dec->concealment_motion_vectors) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        PMV[0][1][0] = PMV[0][1][1] = PMV[1][1][0] = PMV[1][1][1] = 0;
    }

    if (dec->picture_coding_type == P_TYPE && !(*pmacroblock_type & (MB_MOTION_FORWARD | MB_INTRA))) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        if (dec->picture_structure == MPEG_FRAME_PICTURE)
            *pmotion_type = MC_FRAME;
        else {
            *pmotion_type = MC_FIELD;
            motion_vertical_field_select[0][0] = (dec->picture_structure == MPEG_BOTTOM_FIELD);
        }
    }
    return 1;
}

/* Adds a decoded motion_code/residual to a predictor, wrapping into its f_code range. */
static void _decodeMotionVector(int *pred, int r_size, int motion_code, int motion_residual, int full_pel_vector)
{
    int lim, vec;

    lim = 16 << r_size;
    vec = full_pel_vector ? (*pred >> 1) : (*pred);

    if (motion_code > 0) {
        vec += ((motion_code - 1) << r_size) + motion_residual + 1;
        if (vec >= lim)
            vec -= lim + lim;
    } else if (motion_code < 0) {
        vec -= ((-motion_code - 1) << r_size) + motion_residual + 1;
        if (vec < -lim)
            vec += lim + lim;
    }
    *pred = full_pel_vector ? (vec << 1) : vec;
}

void _motionVectors(_sceMpegDecoder *dec, int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s,
                    int motion_vector_count, int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale)
{
    if (motion_vector_count == 1) {
        if (mv_format == 0 && !dmv) {
            mv_field_sel[1][s] = mv_field_sel[0][s] = _ipuGetBits(dec, 1);
        }
        _motionVector(dec, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s][0] = PMV[0][s][0];
        PMV[1][s][1] = PMV[0][s][1];
    } else {
        mv_field_sel[0][s] = _ipuGetBits(dec, 1);
        _motionVector(dec, PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        mv_field_sel[1][s] = _ipuGetBits(dec, 1);
        _motionVector(dec, PMV[1][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}

void _motionVector(_sceMpegDecoder *dec, int *PMV, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale,
                   int full_pel_vector)
{
    int motion_code, motion_residual;

    motion_code = _ipuVdec(dec, VDEC_MOTION_CODE);
    motion_residual = (h_r_size != 0 && motion_code != 0) ? _ipuGetBits(dec, h_r_size) : 0;
    _decodeMotionVector(&PMV[0], h_r_size, motion_code, motion_residual, full_pel_vector);

    if (dmv)
        dmvector[0] = _getDmvector(dec);

    motion_code = _ipuVdec(dec, VDEC_MOTION_CODE);
    motion_residual = (v_r_size != 0 && motion_code != 0) ? _ipuGetBits(dec, v_r_size) : 0;

    if (mvscale)
        PMV[1] >>= 1;

    _decodeMotionVector(&PMV[1], v_r_size, motion_code, motion_residual, full_pel_vector);

    if (mvscale)
        PMV[1] <<= 1;

    if (dmv)
        dmvector[1] = _getDmvector(dec);
}

void _ipuCommand(_sceMpegDecoder *dec, unsigned int cmd)
{
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
}

/* Waits out the IPU's current command; an abort stops it instead. */
void _sceMpegWaitIpuIdle(_sceMpegDecoder *dec)
{
    int polls = 0;

    while ((IPU_CTRL & (IPU_CTRL_BUSY | IPU_CTRL_ECD)) == IPU_CTRL_BUSY) {
        if (dec->abort) {
            ABORT_IPU();
            break;
        }
        if (polls++ > POLLS_PER_NODATA) {
            _sceMpegDispatchMpegCbNodata(dec->mp);
            polls = 0;
        }
    }
}

/* Waits for IPU_CMD's result to be valid and returns it (bit 63 is the busy flag). */
static long long _ipuWaitResult(_sceMpegDecoder *dec)
{
    long long result;
    int polls = 0;

    while ((result = IPU_CMD64) < 0 && !(IPU_CTRL & IPU_CTRL_ECD)) {
        if (dec->abort) {
            ABORT_IPU();
            break;
        }
        if (polls++ > POLLS_PER_NODATA) {
            _sceMpegDispatchMpegCbNodata(dec->mp);
            polls = 0;
        }
    }
    return result;
}

/* Decodes one variable-length code with the IPU's VDEC table `table`; the bits after it are cached. */
int _ipuVdec(_sceMpegDecoder *dec, int table)
{
    long long result;
    long long top;
    unsigned int bp;
    int cmd;
    int polls = 0;

    IPU_WAIT(dec);
    cmd = (table << 26) | IPU_VDEC;
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
    while ((result = IPU_CMD64) < 0) {
        if (dec->abort) {
            ABORT_IPU();
            return 0;
        }
        if (polls++ > POLLS_PER_NODATA) {
            polls = 0;
            _sceMpegDispatchMpegCbNodata(dec->mp);
        }
    }
    bp = IPU_BP;
    top = IPU_TOP64;
    dec->bits = top;
    if (top < 0) {
        dec->bit_count = -(bp & 0x1f) & 0x1f;
    } else {
        dec->bit_count = 32;
    }
    dec->error = (int)result == 0;
    return (short)result;
}

unsigned int _ipuShowBits(_sceMpegDecoder *dec, int n)
{
    if (dec->ipu_cmd_pending || dec->bit_count < n) {
        IPU_WAIT(dec);
        IPU_CMD = IPU_FDEC;
        dec->ipu_cmd_pending = _invalidatesBits[IPU_FDEC >> 28];
        dec->bits = _ipuWaitResult(dec);
        dec->bit_count = 32;
    }
    return dec->bits >> (32 - n);
}

void _ipuFlushBits(_sceMpegDecoder *dec, int n)
{
    unsigned int cmd;

    IPU_WAIT(dec);
    cmd = n | IPU_FDEC;
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
    dec->bits = _ipuWaitResult(dec);
    dec->bit_count = 32;
}

unsigned int _ipuGetBits(_sceMpegDecoder *dec, int n)
{
    unsigned int cmd;
    unsigned int val;

    IPU_WAIT(dec);
    if (dec->ipu_cmd_pending || dec->bit_count < n) {
        IPU_CMD = IPU_FDEC;
        dec->ipu_cmd_pending = _invalidatesBits[IPU_FDEC >> 28];
        dec->bits = _ipuWaitResult(dec);
    }
    val = dec->bits >> (32 - n);
    dec->bit_count = 32;
    cmd = n | IPU_FDEC;
    IPU_CMD = cmd;
    dec->ipu_cmd_pending = _invalidatesBits[cmd >> 28];
    dec->bits = _ipuWaitResult(dec);
    return val;
}
