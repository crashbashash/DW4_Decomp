/* Copies the handle's 20-byte block at +4 to *out once M2VLIB_CheckHn accepts the handle; otherwise
 * reports error 0xFF030204 through M2VERR_SetCode. */
int M2VLIB_CheckHn(void *handle); /* 0 when handle is non-null and in state 2, else -1 */
void M2VERR_SetCode(void *handle, int error);

struct Block00285558 {
    int word[5];
};

struct Handle00285558 {
    int state;                  /* +0 */
    struct Block00285558 block; /* +4 */
};

void M2V_GetErrInf(struct Handle00285558 *handle, struct Block00285558 *out) {
    if (M2VLIB_CheckHn(handle) != 0) {
        M2VERR_SetCode(0, 0xFF030204);
        return;
    }
    *out = handle->block;
}
