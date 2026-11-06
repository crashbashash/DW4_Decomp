/* Reads the word at +724 of a decoder's +352 sub-block into *out after validating the handle
 * (FUN_0028b098); an invalid handle is reported as error 0xFF03020D through FUN_002855d8. */
struct Block285 {
    char pad0[724];
    int value;          /* +724 */
};

struct Decoder285 {
    char pad0[352];
    struct Block285 block;   /* +352 */
};

extern int FUN_0028b098(struct Decoder285 *decoder);
extern void FUN_002855d8(int a0, int code);

void FUN_00285820(struct Decoder285 *decoder, int *out) {
    struct Block285 *block = &decoder->block;

    if (FUN_0028b098(decoder) != 0) {
        FUN_002855d8(0, 0xFF03020D);
        return;
    }
    *out = block->value;
}
