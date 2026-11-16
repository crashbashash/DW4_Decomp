/* Stores a pair of words in the handle at +4 once M2VLIB_CheckHn accepts the handle; otherwise
 * reports error 0xFF030203 through M2VERR_SetCode. */
int M2VLIB_CheckHn(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void M2VERR_SetCode(void *handle, int error);

struct Pair002854e8 {
    int first;  /* +0 */
    int second; /* +4 */
};

struct Handle002854e8 {
    int state;                 /* +0 */
    struct Pair002854e8 pair;  /* +4 */
};

void M2V_SetErrFunc(struct Handle002854e8 *handle, int first, int second) {
    struct Pair002854e8 *pair;

    if (M2VLIB_CheckHn(handle) != 0) {
        M2VERR_SetCode(0, 0xFF030203);
        return;
    }
    pair = &handle->pair;
    pair->first = first;
    pair->second = second;
}
