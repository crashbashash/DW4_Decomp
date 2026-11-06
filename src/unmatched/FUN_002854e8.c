/* Stores a pair of words in the handle at +4 once FUN_0028b098 accepts the handle; otherwise
 * reports error 0xFF030203 through FUN_002855d8. */
int FUN_0028b098(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void FUN_002855d8(void *handle, int error);

struct Pair002854e8 {
    int first;  /* +0 */
    int second; /* +4 */
};

struct Handle002854e8 {
    int state;                 /* +0 */
    struct Pair002854e8 pair;  /* +4 */
};

void FUN_002854e8(struct Handle002854e8 *handle, int first, int second) {
    struct Pair002854e8 *pair;

    if (FUN_0028b098(handle) != 0) {
        FUN_002855d8(0, 0xFF030203);
        return;
    }
    pair = &handle->pair;
    pair->first = first;
    pair->second = second;
}
