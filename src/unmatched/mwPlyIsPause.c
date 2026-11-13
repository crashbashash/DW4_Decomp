/* Returns whether SFD_GetPaStat (FUN_002aa2f0 on the handle's target) reports 1; values other than
 * 0 and 1 are reported as invalid. */
int FUN_002aa2f0(int target);
void FUN_0029a320(const char *format, ...);

extern char DAT_004f36c8[]; /* "E10821A : Invalid value of SFD_GetPaStat : %d" */

struct Handle00295468 {
    char pad0[64];
    int target; /* +64 */
};

int mwPlyIsPause(struct Handle00295468 *handle) {
    int status = FUN_002aa2f0(handle->target);
    int result;

    if (status == 0) {
        result = 0;
    } else if (status == 1) {
        result = 1;
    } else {
        FUN_0029a320(DAT_004f36c8, status);
        result = 0;
    }
    return result;
}
