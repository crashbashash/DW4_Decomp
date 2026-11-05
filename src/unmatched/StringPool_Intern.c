/* Return the pooled copy of a name, creating it on first use; 0x002eaf60, 172 bytes. */
typedef struct StringPool {
    int table;  /* name -> token table */
    int chunks; /* chunk store the copies are carved from */
} StringPool;

int StringTable_Find(int table, const char *name);
int strlen(const char *s);
int StringChunk_AllocateToken(int chunks, int size, int *out_a, int *out_b);
void *memcpy(void *dst, const void *src, int n);
void StringTable_Register(int table, int a, int b, int copy);

int StringPool_Intern(StringPool *pool, const char *name)
{
    int token, hash;
    int copy, size;

    if (name == 0) {
        return 0;
    }
    token = 0;
    copy = StringTable_Find(pool->table, name);
    if (copy == 0) {
        hash = 0;
        size = strlen(name) + 1;
        copy = StringChunk_AllocateToken(pool->chunks, size, &hash, &token);
        memcpy((void *)copy, name, size);
        StringTable_Register(pool->table, token, hash, copy);
    }
    return copy;
}
