/* Stores a 64-byte-aligned value in word 1 of one entry of the context's shared 36-byte table (the
 * table the other audio slots index by the same entry number). A value that is not a multiple of
 * 64 is ignored; the mask on the store is then a no-op but is kept. The word is later sent shifted
 * left by 8 in an IOP RPC command, so it is an address-like quantity, not a count. */

/* One 36-byte table entry; only word 1 is touched here. */
typedef struct AudioTableEntry {
    int word0;
    int word1;
    char unknown8[28];
} AudioTableEntry;

/* The table owner: the table's base address sits at +16. It is kept as a byte pointer because the
 * instruction order (load base, then scale the index) only comes out of byte-offset arithmetic,
 * not entries[index]. */
typedef struct AudioTableOwner {
    char unknown0[16];
    char *entries;
} AudioTableOwner;

extern AudioTableOwner *g_audioTableOwner[4];

void Gap__Core__igPsx2AudioContext__vfunc_53(int unusedReceiver, int entryIndex, int value) {
    if (!(value & 0x3F)) {
        ((AudioTableEntry *)(g_audioTableOwner[0]->entries + entryIndex * 0x24))->word1 = value & ~0x3F;
    }
}
