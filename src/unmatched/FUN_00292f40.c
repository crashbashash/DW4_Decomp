/* Returns -1 when the handle (no flag at +24) has a status block from FUN_00294a30 with either +40
 * or +44 still zero, else 0. */

struct Status00292f40 {
    char pad0[40];
    int f40; /* +40 */
    int f44; /* +44 */
};

struct Handle00292f40 {
    char pad0[24];
    int f24; /* +24: non-zero skips the check */
};

struct Status00292f40 *FUN_00294a30(struct Handle00292f40 *handle);

int FUN_00292f40(struct Handle00292f40 *handle) {
    struct Status00292f40 *status = FUN_00294a30(handle);
    int result = 0;

    if (handle->f24 == 0) {
        result = (status->f40 != 0) ? 0 : -1;
        if (status->f44 == 0) {
            result = -1;
        }
    }
    return result;
}
