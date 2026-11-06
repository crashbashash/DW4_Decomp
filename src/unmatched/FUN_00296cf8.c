/* Returns the sum of the second and fourth words of the 32-byte status FUN_002ac3a8 reports for
 * the handle's +64 stream. */
typedef struct {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
} Stat296cf8;

typedef struct {
    char pad0[64];
    int stream;   /* 64 */
} Ply296cf8;

extern void FUN_002ac3a8(int stream, Stat296cf8 *stat);

int FUN_00296cf8(Ply296cf8 *ply) {
    Stat296cf8 stat;

    FUN_002ac3a8(ply->stream, &stat);
    return stat.f4 + stat.f12;
}
