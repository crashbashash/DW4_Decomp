/* Scales the handle's +16 size (in 16 KiB units, as 2 KiB sectors) by `ratio`, caps it at +476 and
 * passes it with the cap to FUN_00296818. */

struct Handle00297348 {
    char pad0[16];
    int size;              /* +16 */
    char pad20[476 - 20];
    int cap;               /* +476 */
};

void FUN_00296818(struct Handle00297348 *handle, int value, int cap);

void FUN_00297348(struct Handle00297348 *handle, float ratio) {
    int cap = handle->cap;
    int value = (float)((handle->size / 16384) << 11) * ratio;

    if (cap < value) {
        value = cap;
    }
    FUN_00296818(handle, value, cap);
}
