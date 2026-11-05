/* 0x0028b040 — FUN_0028b040 (84 bytes). Stores a value into slot `index` of the parameter array (+24) of
   every valid decoder (state 2) in the decoder table described at 0x00573eb8 (count +64, array +68,
   1664-byte entries). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Decoder28b {
    int state;          /* +0: 2 = valid */
    char pad4[20];
    int params[410];    /* +24 */
};

struct DecoderTable28b {
    char pad0[64];
    int count;                    /* +64 */
    struct Decoder28b *decoders;  /* +68 */
};

extern struct DecoderTable28b DAT_00573eb8;

void FUN_0028b040(int index, int value) {
    struct Decoder28b *decoder;
    int remaining;

    remaining = DAT_00573eb8.count;
    decoder = DAT_00573eb8.decoders;
    if (remaining > 0) {
        do {
            if (decoder->state == 2) {
                decoder->params[index] = value;
            }
            decoder++;
        } while (--remaining != 0);
    }
}
