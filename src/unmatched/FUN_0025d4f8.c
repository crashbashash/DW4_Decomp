/* 0x0025d4f8 — FUN_0025d4f8 (68 bytes). Releases a 260-byte record: detaches and frees its handle at +8 through
 * FUN_0026f010, clears the whole record and its state halfword. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_0026f010(void *handle);
void *memset(void *dst, int value, unsigned int size);

typedef struct Rec25d4f8 {
    short state;        /* +0 */
    char pad2[6];
    void *handle;       /* +8: released through FUN_0026f010 */
    char pad12[248];
} Rec25d4f8;            /* 260 bytes */

void FUN_0025d4f8(Rec25d4f8 *rec) {
    if (rec != 0) {
        void *handle = rec->handle;

        rec->handle = 0;
        FUN_0026f010(handle);
        memset(rec, 0, sizeof(*rec));
        rec->state = 0;
    }
}
