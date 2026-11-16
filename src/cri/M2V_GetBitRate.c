/* Reads the word at +724 of a decoder's +352 sub-block into *out after validating the handle
 * (M2VLIB_CheckHn); an invalid handle is reported as error 0xFF03020D through M2VERR_SetCode. */
struct Block285 {
    char pad0[724];
    int value;          /* +724 */
};

struct Decoder285 {
    char pad0[352];
    struct Block285 block;   /* +352 */
};

extern int M2VLIB_CheckHn(struct Decoder285 *decoder);
extern void M2VERR_SetCode(int a0, int code);

void M2V_GetBitRate(struct Decoder285 *decoder, int *out) {
    struct Block285 *block = &decoder->block;

    if (M2VLIB_CheckHn(decoder) != 0) {
        M2VERR_SetCode(0, 0xFF03020D);
        return;
    }
    *out = block->value;
}
