/* For config mode 3, returns the stream's f64/f68 counts (summed over both layers when it has 3)
 * through the out pointers; zero otherwise. */
struct Counts2a6ea0 {
    char pad0[64];
    int f64;
    int f68;
};
struct Stream2a6ea0 {
    char pad0[164];
    unsigned int layers;                  /* +164 */
    char pad168[352 - 168];
    struct Counts2a6ea0 *first;           /* +352 */
    struct Counts2a6ea0 *second;          /* +356 */
};
struct Config2a6ea0 {
    char pad0[56];
    int f56;
};

void FUN_002a6ea0(struct Config2a6ea0 *config, struct Stream2a6ea0 *stream, int *out64, int *out68) {
    if (config->f56 == 3) {
        switch (stream->layers) {
        case 1: /* matching construct: manual — explicit single-layer case shapes the compare tree */
            break;
        case 2:
            *out64 = stream->first->f64;
            *out68 = stream->first->f68;
            return;
        case 3:
            *out64 = stream->first->f64 + stream->second->f64;
            *out68 = stream->first->f68 + stream->second->f68;
            return;
        }
    }
    *out64 = 0;
    *out68 = 0;
}
