/* Reports the object's rate as (rate, scale): index 0 at +2336 gives 29970 with scale 0, otherwise
 * DAT_004f5060[index] with scale 1000. */
extern int DAT_004f5060[];

struct Obj0920 {
    char pad[2336];
    int rateIndex;                        /* +2336 (0x920): index into DAT_004f5060 */
};

void FUN_002af540(struct Obj0920 *obj, int *scale, int *rate) {
    int index = obj->rateIndex;
    int value;

    if (index == 0) {
        *scale = 0;
        *rate = 29970;
        return;
    }
    /* The table is read before *scale is written: the store could alias it. */
    value = DAT_004f5060[index];
    *scale = 1000;
    *rate = value;
}
