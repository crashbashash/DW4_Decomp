/* Validates the picture's chromaFormat (+144): 1, 2, 3 pass through; anything else is reported
 * ("E301273 : chroma_format is invalid.") and gives 1. */
void FUN_0029a320(const char *format, ...);

extern char DAT_004f4078[]; /* "E301273 : chroma_format is invalid." */

struct Picture00297b18 {
    char pad0[144];
    unsigned int chromaFormat; /* +144 */
};

int FUN_00297b18(struct Picture00297b18 *picture) {
    int result = 1;

    switch (picture->chromaFormat) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        FUN_0029a320(DAT_004f4078);
        break;
    }
    return result;
}
