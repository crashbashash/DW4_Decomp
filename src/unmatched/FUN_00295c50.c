/* Looks up a file's range with ADXF_GetFnameRangeEx (ADXF_GetFnameRangeEx, per its diagnostic) using the
 * handle's +440 value and stores the three results at +452..+460 with +448 = 1; reports failure
 * through mwsfd_Error. */
int ADXF_GetFnameRangeEx(int a, int b, int c, int *out0, int *out1, int *out2);
void mwsfd_Error(const char *format, ...);

extern char DAT_004f3918[]; /* "E211151: ADXF_GetFnameRangeEx() faild." */

struct Range00295c50 {
    int valid;  /* +0 */
    int first;  /* +4 */
    int second; /* +8 */
    int third;  /* +12 */
};

struct Handle00295c50 {
    char pad0[440];
    int f440;                   /* +440 */
    char pad444[448 - 444];
    struct Range00295c50 range; /* +448 */
};

void FUN_00295c50(struct Handle00295c50 *handle, int a, int b) {
    int out[3];

    if (ADXF_GetFnameRangeEx(a, b, handle->f440, &out[0], &out[1], &out[2]) == 0) {
        handle->range.first = out[0];
        handle->range.second = out[1];
        handle->range.third = out[2];
        handle->range.valid = 1;
    } else {
        mwsfd_Error(DAT_004f3918);
    }
}
