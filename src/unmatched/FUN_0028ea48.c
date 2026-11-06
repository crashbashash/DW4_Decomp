/* Stores a pair of words in the handle at +592 once FUN_002913f8 accepts the handle; otherwise
 * reports error 0xFF030203 through FUN_0028eb38. */
int FUN_002913f8(void *handle); /* handle check; non-zero rejects */
void FUN_0028eb38(void *handle, int error);

struct Pair0028ea48 {
    int first;  /* +0 */
    int second; /* +4 */
};

struct Handle0028ea48 {
    char pad0[592];
    struct Pair0028ea48 pair;  /* +592 */
};

void FUN_0028ea48(struct Handle0028ea48 *handle, int first, int second) {
    struct Pair0028ea48 *pair;

    if (FUN_002913f8(handle) != 0) {
        FUN_0028eb38(0, 0xFF030203);
        return;
    }
    pair = &handle->pair;
    pair->first = first;
    pair->second = second;
}
