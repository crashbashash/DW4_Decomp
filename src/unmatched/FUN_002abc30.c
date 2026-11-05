/* 0x002abc30 — FUN_002abc30 (100 bytes). Adds `delta` to the counter at +0x950 and, when slot 36 holds a callback, calls it with the object, `arg` and the counter block. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
struct Owner;
typedef void (*CounterCallback)(struct Owner *obj, int arg, int *counter);
CounterCallback FUN_002adc40(struct Owner *obj, int slot);

struct Owner {
    char pad0[0x950];
    int counter; /* +0x950 */
};

void FUN_002abc30(struct Owner *obj, int delta, int arg) {
    int *counter = &obj->counter;
    CounterCallback callback;

    *counter += delta;
    callback = FUN_002adc40(obj, 36);
    if (callback != 0) {
        callback(obj, arg, counter);
    }
}
