/* Points a decoder object's three buffers into the shared block (DAT_00573f68 + 4384/4352/4448)
 * and its two clamp-table pointers (+64, +272) at the saturation table centre DAT_004bccd4 (built
 * by FUN_00290db8). */
extern char *DAT_00573f68;           /* shared 7136-byte block (FUN_00290ec8) */
extern unsigned char *DAT_004bccd4;  /* saturation table centre (FUN_00290db8) */

typedef struct {
    char pad0[44];
    char *buf44;
    char *buf48;
    char *buf52;
    char pad56[8];
    unsigned char *clamp64;
    char pad68[204];
    unsigned char *clamp272;
} Dec290e88;

void FUN_00290e88(Dec290e88 *dec) {
    dec->buf44 = DAT_00573f68 + 4384;
    dec->buf48 = DAT_00573f68 + 4352;
    dec->buf52 = DAT_00573f68 + 4448;
    dec->clamp64 = DAT_004bccd4;
    dec->clamp272 = DAT_004bccd4;
}
