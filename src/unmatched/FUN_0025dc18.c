/* Parses three 16-bit values out of a string with FUN_0025d0b8 and stores them in f160/f162/f164
 * of the decoder block. */
/* CRI ADX decoder block as this function touches it; field meanings are not yet known */
typedef struct DecoderBlock {
    short f0;
    short state;
    char f4[8];
    unsigned char f12;
    unsigned char f13;
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
    char f72[8];
    int f80;
    int f84;
    int f88;
    int f92;
    int f96;
    int f100;
    char f104[32];
    int f136;
    int f140;
    char f144[8];
    short f152;
    unsigned short f154;
    short f156;
    short f158;
    unsigned short f160;
    unsigned short f162;
    unsigned short f164;
} DecoderBlock;

unsigned int strlen(const char *string);
void FUN_0025d0b8(const char *text, unsigned int length, unsigned short *first, unsigned short *second,
                  unsigned short *third);

void FUN_0025dc18(DecoderBlock *block, const char *text) {
    unsigned short first;
    unsigned short second;
    unsigned short third;

    FUN_0025d0b8(text, strlen(text), &first, &second, &third);
    block->f160 = first;
    block->f162 = second;
    block->f164 = third;
}
