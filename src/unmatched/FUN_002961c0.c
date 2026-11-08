/* Gets object 9 from FUN_00102df0, stores `owner` at its +128 and passes `data` with size/16 to
 * sceDmaSendN; returns 0. */

struct Object002961c0 {
    char pad0[128];
    int owner; /* +128 */
};

struct Object002961c0 *FUN_00102df0(int id);
void sceDmaSendN(struct Object002961c0 *object, void *data, int count);

int FUN_002961c0(void *data, int size, int owner) {
    struct Object002961c0 *object = FUN_00102df0(9);

    object->owner = owner;
    sceDmaSendN(object, data, size / 16);
    return 0;
}
