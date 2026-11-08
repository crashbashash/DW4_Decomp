/* Gets object 8 from FUN_00102df0, stores `owner` at its +128 and passes `data` with size/16 to
 * sceDmaRecvN; returns 0. */

struct Object002960e8 {
    char pad0[128];
    int owner; /* +128 */
};

struct Object002960e8 *FUN_00102df0(int id);
void sceDmaRecvN(struct Object002960e8 *object, void *data, int count);

int FUN_002960e8(int owner, int size, void *data) {
    struct Object002960e8 *object = FUN_00102df0(8);

    object->owner = owner;
    sceDmaRecvN(object, data, size / 16);
    return 0;
}
