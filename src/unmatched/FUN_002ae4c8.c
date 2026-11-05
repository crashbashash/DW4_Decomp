/* 0x002ae4c8 — FUN_002ae4c8 (52 bytes). True when the object's state word at +72 is 4, its word at +80 is clear and the sub-block at +2384 has a clear word at +28. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Sub0950 {
    char pad[28];
    int f28;
};

struct Obj0950 {
    char pad[72];
    int f72;                              /* 4 is required here */
    int f76;
    int f80;
    char pad84[2384 - 84];
    struct Sub0950 sub;                   /* +2384 (0x950) */
};

int FUN_002ae4c8(struct Obj0950 *obj) {
    /* matching construct: manual — taking the sub-block address up front and testing with early returns gives retail's register use */
    struct Sub0950 *sub = &obj->sub;

    if (obj->f72 != 4) {
        return 0;
    }
    if (obj->f80 != 0) {
        return 0;
    }
    return sub->f28 == 0;
}
