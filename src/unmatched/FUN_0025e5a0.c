/* Reports the frames produced since the last report (f148 minus f244, wrapped into 0..0x7FFFFFFF)
 * and the byte size from f144 to the callback in f252, then records f148 as reported. */
/* CRI ADX decoder block as this function touches it; field meanings are not yet known */
typedef struct DecoderBlock {
    short f0;
    short state;
    char f4[8];
    signed char f12;
    signed char f13;
    signed char f14;
    signed char f15;
    int f16;
    int f20;
    int f24;
    short f28;
    short f30;
    int f32;
    short f36;
    short f38;
    int f40;
    int f44;
    int f48;
    int f52;
    char f56[4];
    int f60;
    int f64;
    int f68;
    int f72;
    int f76;
    int f80;
    int f84;
    int f88;
    int f92;
    int f96;
    int f100;
    char f104[12];
    int f116;
    char f120[16];
    int f136;
    int f140;
    int f144;
    int f148;
    short f152;
    unsigned short f154;
    short f156;
    short f158;
    unsigned short f160;
    unsigned short f162;
    unsigned short f164;
    char f166[78];
    int f244;
    int f248;
    void (*f252)(void *context, int count, int bytes);
    void *f256;
} DecoderBlock;

void FUN_0025e5a0(DecoderBlock *block) {
    int frames;
    int count = block->f148 - block->f244;

    frames = block->f144; /* matching construct: permuter — f144 read into a local before the wrap test */
    if (count < 0) {
        count += 0x7fffffff;
    }
    block->f252(block->f256, count, frames * block->f14 * 2);
    block->f244 = block->f148;
}
