/* 0x00269660 — FUN_00269660 (100 bytes). Sets the object's owner id (+68) and re-claims both of its table entries (+128, +132): each held entry is released with FUN_00267da0 and replaced by a fresh one from FUN_00267d00 for the new owner. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
typedef struct Obj_269660 {
    char pad0[68];
    int owner;          /* 0x44 */
    char pad72[56];
    void *entry_a;      /* 0x80 */
    void *entry_b;      /* 0x84 */
} Obj_269660;

void FUN_00267da0(void *entry);
void *FUN_00267d00(int owner);

void FUN_00269660(Obj_269660 *obj, int owner) {
    obj->owner = owner;
    if (obj->entry_a != 0) {
        FUN_00267da0(obj->entry_a);
    }
    obj->entry_a = FUN_00267d00(obj->owner);
    if (obj->entry_b != 0) {
        FUN_00267da0(obj->entry_b);
    }
    obj->entry_b = FUN_00267d00(obj->owner);
}
