/* Sets the word at +392 to 1 in every 1024-byte handle of the global pool. */

struct Handle00290e40 {
    char pad0[392];
    int f392;              /* +392 */
    char pad396[1024 - 396];
};

struct Pool00290e40 {
    char pad0[84];
    int count;                      /* +84 */
    struct Handle00290e40 *handles; /* +88 */
};

extern struct Pool00290e40 DAT_00573f18;

void FUN_00290e40(void) {
    struct Handle00290e40 *handle = DAT_00573f18.handles;
    int count = DAT_00573f18.count;
    int i;

    for (i = 0; i < count; i++, handle++) {
        handle->f392 = 1;
    }
}
