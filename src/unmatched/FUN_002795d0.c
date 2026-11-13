/* Tears down every entry of the 24-byte table at 0x004b1e20 (count 0x004b1dc0): destroys its
 * stream (+4, FUN_0027d880), its object (+8, through its method at slot +12) and its +12 resource
 * (FUN_0027e078), then clears the entry; finally releases the shared resource 0x004b1dcc through
 * FUN_001122d8 when the owned flag 0x004b1dd4 is set. */
struct Object279;
struct Object279Methods {
    void *slots[3];
    void (*destroy)(struct Object279 *object);   /* +12 */
};
struct Object279 {
    struct Object279Methods *methods;
};

struct Entry279 {
    int f0;
    int stream;                 /* +4 */
    struct Object279 *object;   /* +8 */
    int resource;               /* +12 */
    int f16;
    int f20;
};

extern void FUN_0027d880(int stream);
extern void FUN_0027e078(int resource);
extern void *memset(void *dest, int value, unsigned int size);
extern void FUN_001122d8(int resource);
extern int ps2rna_nvoice;
extern int ps2rna_iop_heap;
extern signed char ps2rna_iop_alloced;
extern struct Entry279 ps2rna_psj[];

void FUN_002795d0(void) {
    struct Entry279 *entry;
    int i;

    for (i = 0; i < ps2rna_nvoice; i++) {
        entry = &ps2rna_psj[i];
        if (entry->stream != 0) {
            FUN_0027d880(entry->stream);
        }
        if (entry->object != 0) {
            entry->object->methods->destroy(entry->object);
        }
        if (entry->resource != 0) {
            FUN_0027e078(entry->resource);
        }
        memset(entry, 0, sizeof(*entry));
    }
    if (ps2rna_iop_alloced == 1) {
        FUN_001122d8(ps2rna_iop_heap);
        ps2rna_iop_heap = 0;
        ps2rna_iop_alloced = 0;
    }
}
