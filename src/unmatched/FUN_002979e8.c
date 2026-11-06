/* Reads two values for the handle's +172 object with FUN_002b3d30 into out +80/+84 and clears
 * +88/+92. */
void FUN_002b3d30(int object, int *first, int *second);

struct Handle002979e8 {
    char pad0[172];
    int object; /* +172 */
};

struct Out002979e8 {
    char pad0[80];
    int first;  /* +80 */
    int second; /* +84 */
    int f88;    /* +88 */
    int f92;    /* +92 */
};

void FUN_002979e8(struct Handle002979e8 *handle, int unused, struct Out002979e8 *out) {
    int values[2];

    FUN_002b3d30(handle->object, &values[0], &values[1]);
    out->first = values[0];
    out->second = values[1];
    out->f88 = 0;
    out->f92 = 0;
}
