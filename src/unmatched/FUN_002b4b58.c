/* 0x002b4b58 — FUN_002b4b58 (44 bytes). True unless both floats at +60/+64 (set by FUN_002b4aa8) are zero. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */

struct Obj003C {
    char pad[60];
    float f60;
    float f64;
};

int FUN_002b4b58(struct Obj003C *obj) {
    /* Both floats are read into locals first, which gives retail's register assignment. */
    float a = obj->f60;
    float b = obj->f64;
    int nonzero = 1;

    if (a == 0.0f && b == 0.0f) {
        nonzero = 0;
    }
    return nonzero;
}
