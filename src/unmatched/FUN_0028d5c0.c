/* Copies the handle's 32-byte block at +40 to *out once mps_CheckHn accepts the handle (returning
 * its 0 status); otherwise returns mps_ReportError's report of 0xFF020202. */
int mps_CheckHn(void *handle);
int mps_ReportError(void *handle, int error);

struct Block0028d5c0 {
    int word[8];
};

struct Handle0028d5c0 {
    char pad0[40];
    struct Block0028d5c0 block; /* +40 */
};

int FUN_0028d5c0(struct Handle0028d5c0 *handle, struct Block0028d5c0 *out) {
    int status = mps_CheckHn(handle);

    if (status != 0) {
        return mps_ReportError(0, 0xFF020202);
    }
    *out = handle->block;
    return status;
}
