/* Creates two temporary objects (FUN_0027bd48, FUN_0027b408) in local storage, caches their
 * slot-16 values in DAT_0057fab0/DAT_0057fab4 and releases them. */
struct Object;
struct ObjectOps {
    char pad[12];
    void (*release)(struct Object *);     /* slot 12 */
    int (*fn16)(struct Object *);         /* slot 16 */
};
struct Object {
    struct ObjectOps *ops;
};
struct Object *FUN_0027b408();
struct Object *FUN_0027bd48();
extern int DAT_0057fab0;
extern int DAT_0057fab4;

void FUN_0029ebb0(void) {
    char storage[16];
    struct Object *object;

    object = FUN_0027bd48(storage, 8, 0);
    DAT_0057fab0 = object->ops->fn16(object);
    object->ops->release(object);
    object = FUN_0027b408(storage, 8);
    DAT_0057fab4 = object->ops->fn16(object);
    object->ops->release(object);
}
