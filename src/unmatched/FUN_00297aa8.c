/* Validates the picture's pictureStructure (+140): 1, 2, 3 pass through; anything else is reported
 * ("E301272 : picture_structure is invalid.") and gives 3. */
void FUN_0029a320(const char *format, ...);

extern char DAT_004f4050[]; /* "E301272 : picture_structure is invalid." */

struct Picture00297aa8 {
    char pad0[140];
    unsigned int pictureStructure; /* +140 */
};

int FUN_00297aa8(struct Picture00297aa8 *picture) {
    int result = 3;

    switch (picture->pictureStructure) {
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
        FUN_0029a320(DAT_004f4050);
        break;
    }
    return result;
}
