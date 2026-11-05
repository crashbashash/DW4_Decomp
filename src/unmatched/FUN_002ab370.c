/* 0x002ab370 — FUN_002ab370 (128 bytes). True when the current stream's level (interface slot +36) is at least 80% of its capacity. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct SfdStreamObj SfdStreamObj;
typedef struct SfdStreamVtbl {
    char pad0[36];
    int (*f36)(SfdStreamObj *obj, int mode);  /* +36 */
} SfdStreamVtbl;
struct SfdStreamObj {
    SfdStreamVtbl *vtbl;
};

typedef struct SfdStreamSlot {
    int f0;
    SfdStreamObj *obj;      /* +4 */
    int f8;
    int capacity;           /* +12 */
    char pad16[100];
} SfdStreamSlot;

typedef struct SfdHandle {
    char pad0[4888];
    SfdStreamSlot slots[1]; /* +4888, 116 bytes each */
    char pad5004[3192];
    int current;            /* +8196 */
} SfdHandle;

int FUN_002ab370(SfdHandle *handle) {
    SfdStreamSlot *slot = &handle->slots[handle->current];
    SfdStreamObj *obj = slot->obj;

    if (obj->vtbl->f36(obj, 1) < slot->capacity * 80 / 100) {
        return 0;
    }
    return 1;
}
