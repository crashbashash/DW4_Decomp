/* Advances the field counter (+968, parity into +964) for field pictures or resets both for frame
 * pictures (structure 3), then loads two per-mode table words indexed by +276. */

struct Decoder00285f98 {
    char pad0[276];
    int tableIndex; /* +276 */
    int structure; /* +280 */
    char pad284[516];
    int f800; /* +800 */
    char pad804[12];
    int f816; /* +816 */
    char pad820[144];
    int parity; /* +964 */
    int fieldCount; /* +968 */
};

extern int DAT_004f28b0[]; /* indexed by tableIndex, stored at +800 */
extern int DAT_004f28c0[]; /* indexed by tableIndex, stored at +816 */

void FUN_00285f98(struct Decoder00285f98 *d) {
    if (d->structure == 3) {
        d->fieldCount = 0;
        d->parity = 0;
    } else {
        int count = d->fieldCount;

        d->fieldCount = count + 1;
        d->parity = count % 2;
    }
    d->f800 = DAT_004f28b0[d->tableIndex];
    d->f816 = DAT_004f28c0[d->tableIndex];
}
