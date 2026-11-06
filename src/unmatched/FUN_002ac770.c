/* Sets up a pool over a caller buffer: aligns the start to 8, clears the rest and records it as
 * 16-byte units. */
typedef struct SfdPool {
    char *base;             /* +0 */
    int units;              /* +4, 16-byte units */
    int f8;
    int f12;
    int f16;
} SfdPool;

extern void *memset(void *dst, int value, unsigned int size);

void FUN_002ac770(SfdPool *pool, char *buffer, int size) {
    char *base = (char *)(((int)buffer + 7) & ~7);
    int usable = size - (base - buffer);

    memset(base, 0, usable);
    pool->base = base;
    pool->units = usable / 16;
    pool->f8 = 0;
    pool->f12 = 0;
    pool->f16 = 0;
}
