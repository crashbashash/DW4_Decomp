void igNamedObject_SetName(igNamedObject *self, int name) {
    int *header;
    int references;
    int pool;
    char *previous;
    void *interned;
    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = pool;
    }
    interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)name)));
    previous = (char *)self->_name;
    if (previous != 0) {
        header = (int *)(previous - 8);
        references = *(int *)((char *)previous - 4) - 1;
        *(int *)((char *)previous - 4) = references;
        if (references == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    self->_name = (int)interned;
}

