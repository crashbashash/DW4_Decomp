/* 0x002859b8 — FUN_002859b8 (120 bytes). Clears the 1304-byte block at +352 of the decoder object and sets its non-zero defaults (1 at +76/+212, 0xFF at +116/+120/+124). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void *memset(void *, int, unsigned int);

/* Members of the block that this initialiser touches; roles not yet recovered. */
struct Block002859b8 {
    char pad0[76];
    int f76; /* +76 */
    char pad80[32];
    int f112; /* +112 */
    int f116; /* +116 */
    int f120; /* +120 */
    int f124; /* +124 */
    char pad128[80];
    int f208; /* +208 */
    int f212; /* +212 */
    char pad216[752];
    int f968; /* +968 */
    char pad972[164];
    int f1136; /* +1136 */
    int f1140; /* +1140 */
    int f1144; /* +1144 */
    int f1148; /* +1148 */
    int f1152; /* +1152 */
    int f1156; /* +1156 */
    char pad1160[4];
    int f1164; /* +1164 */
    char pad1168[124];
    int f1292; /* +1292 */
    char pad1296[8];
};

struct Decoder002859b8 {
    char pad0[352];
    struct Block002859b8 block; /* +352 */
};

void FUN_002859b8(struct Decoder002859b8 *decoder) {
    struct Block002859b8 *block = &decoder->block;

    memset(block, 0, sizeof(*block));
    block->f76 = 1;
    block->f112 = 0;
    block->f116 = 0xFF;
    block->f120 = 0xFF;
    block->f124 = 0xFF;
    block->f212 = 1;
    block->f1136 = 0;
    block->f1140 = 0;
    block->f1144 = 0;
    block->f1148 = 0;
    block->f1152 = 0;
    block->f1156 = 0;
    block->f1164 = 0;
    block->f968 = 0;
    block->f208 = 0;
    block->f1292 = 0;
}
