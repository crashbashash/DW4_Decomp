/* 0x00406fe0
 * Lazily creates the global string pool (finding 3149/3156: the cache at
 * 0x00586f20): allocates 16 bytes and runs StringPool_Construct on them only
 * while the cache is null.  An allocation failure stores and returns null, so
 * a later call retries (finding 1035).  FUN_002eb010 is the engine's default
 * allocator (size in a0). */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
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
} /* extern "C" */
