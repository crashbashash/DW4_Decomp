/* Resets a 48-byte record: clears it through FUN_0028b530, then sets the id fields at +36/+40/+44
 * to -1 and the flag at +28 to 1. */
void FUN_0028b530(void *dst, int value, int size);

struct Record48 {
    int f0, f4, f8, f12, f16, f20, f24;
    int enabled; /* +28 */
    int f32;
    int id36;    /* +36 */
    int id40;    /* +40 */
    int id44;    /* +44 */
};

void FUN_002abae0(struct Record48 *rec) {
    FUN_0028b530(rec, 0, 16);
    rec->f0 = 0;
    rec->f4 = 0;
    rec->f8 = 0;
    rec->f12 = 0;
    rec->f16 = 0;
    rec->f20 = 0;
    rec->f24 = 0;
    rec->f32 = 0;
    rec->enabled = 1;
    rec->id36 = -1;
    rec->id40 = -1;
    rec->id44 = -1;
}
