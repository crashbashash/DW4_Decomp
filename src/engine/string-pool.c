int StringPool_DestroyChunks();
int FUN_002eb050(int *);
void *StringTable_Destroy();

/* Pool destructor. Frees the chunk list and the table that is the pool's first member;
 * `delete_flag` is the compiler-generated destructor flag, and a positive value (tested as a
 * 16-bit quantity) also releases the pool object itself. */
int *StringPool_Destroy(int *self, long long delete_flag) {
    if (self != 0) {
        StringPool_DestroyChunks(self);
        StringTable_Destroy((void *)*self, 1);
        if ((short)delete_flag > 0) {
            FUN_002eb050(self);
        }
    }
    return self;
}
