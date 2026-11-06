/* Lazily creates the global string pool: allocates 16 bytes and runs StringPool_Construct on them
 * only while the cache is null. An allocation failure stores and returns null, so a later call
 * retries. FUN_002eb010 is the engine's default allocator (size in a0). */
extern "C" {
int FUN_002eb010(int);
int StringPool_Construct(int);
extern int g_stringPool[4];
int StringPool_GetInstance(void) {
    int pool;

    if (g_stringPool[0] == 0) {
        pool = FUN_002eb010(0x10);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return g_stringPool[0];
}
}
