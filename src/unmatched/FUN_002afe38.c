/* Applies the first pending change in a request (flags at +4, +8, +12, +32): logs it through
 * FUN_002b01a8, hands it to its handler and, for the stream changes, re-issues the FUN_002ada78
 * requests 6/5 and clears the matching ids at +2988/+2984; returns -1 when nothing was pending. */
void FUN_002b01a8(void *handle, int a, int code);
void FUN_002aff58(void *handle, void *request);
void FUN_002b0048(void *handle, void *request);
void FUN_002b00e8(void *handle, void *request);
void FUN_002b0188(void *handle, void *request);
void FUN_002ada78(void *handle, int code, int arg);

struct Request {
    int f0;
    int change4;  /* +4 */
    int change8;  /* +8 */
    int change12; /* +12 */
    char pad16[32 - 16];
    int change32; /* +32 */
};

struct Handle {
    char pad0[2984];
    int id2984; /* +2984 */
    int id2988; /* +2988 */
};

int FUN_002afe38(struct Handle *handle, struct Request *request) {
    if (request->change4 != 0) {
        FUN_002b01a8(handle, 0, 0);
        FUN_002aff58(handle, request);
    } else if (request->change8 != 0) {
        FUN_002b01a8(handle, 0, 1);
        FUN_002b0048(handle, request);
        FUN_002ada78(handle, 6, 0);
        handle->id2988 = 0;
    } else if (request->change12 != 0) {
        FUN_002b01a8(handle, 0, 2);
        FUN_002b00e8(handle, request);
        FUN_002ada78(handle, 5, 0);
        handle->id2984 = 0;
    } else if (request->change32 != 0) {
        FUN_002b01a8(handle, 0, 7);
        FUN_002b0188(handle, request);
        FUN_002ada78(handle, 6, 0);
        FUN_002ada78(handle, 5, 0);
        handle->id2988 = 0;
        handle->id2984 = 0;
    } else {
        return -1;
    }
    return 0;
}
