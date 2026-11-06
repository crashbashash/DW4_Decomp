/* Round-robin slot allocator: wraps the cursor at +36 by the slot count at +24, returns that
 * 64-byte slot of the array at +20 and advances the cursor. */
typedef struct Slot10dbd0 { char bytes[64]; } Slot10dbd0;

typedef struct Pool10dbd0 {
    char pad0[20];
    Slot10dbd0 *slots;      /* +20 */
    int count;              /* +24 */
    char pad28[8];
    int cursor;             /* +36 */
} Pool10dbd0;

Slot10dbd0 *FUN_0010dbd0(Pool10dbd0 *pool) {
    Slot10dbd0 *slot;

    pool->cursor %= pool->count;
    slot = &pool->slots[pool->cursor];
    pool->cursor++;
    return slot;
}
