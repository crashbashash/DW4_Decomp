/* 0x001592c0 — igPsx2LongList vfunc 36: release the list's storage.  Frees
 * the storage block at +0x38 through its object allocator, then frees the
 * +0x34 buffer, but only when the list owns it (flag at +0x3C).  Those
 * members lie past the reflected igPsx2LongList (include/dw4/reflected.h ends
 * at +0x14), so they are reached through the local view below; the role names
 * are descriptive only, taken from how each member is used here.
 * FUN_00300f50 is a byte-identical twin of igObject_FreeStorage (0x00300f00). */
typedef struct LongListStorageView {
    char pad52[52];
    int buffer;                 /* +0x34: block returned to Memory_FreeBuffer */
    int storage;                /* +0x38: block released with FUN_00300f50 */
    unsigned char ownsBuffer;   /* +0x3C: nonzero when buffer must be freed */
} LongListStorageView;
int Memory_FreeBuffer();
int FUN_00300f50();

void Gap__Core__igPsx2LongList__vfunc_36(LongListStorageView *self) {
    int storage;
    int buffer;

    storage = self->storage;
    if (storage != 0) {
        FUN_00300f50(self, storage);
    }
    buffer = self->buffer;
    if ((buffer != 0) && (self->ownsBuffer != 0)) {
        Memory_FreeBuffer(buffer);
        self->buffer = 0;
    }
}
