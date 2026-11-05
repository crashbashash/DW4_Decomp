/* 0x002b4aa8 — FUN_002b4aa8 (100 bytes). Stores two floats at +60/+64 of the object, first reporting through FUN_002b3b38 (with DAT_004f58f0) unless FUN_002b4b10(obj) is 1. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b3b38();
int FUN_002b4b10();

extern int DAT_004f58f0[];

struct Obj003C {
    char pad[60];
    float f60;
    float f64;
};

void FUN_002b4aa8(struct Obj003C *obj, float a, float b) {
    if (FUN_002b4b10(obj) != 1) {
        FUN_002b3b38(0, 0, DAT_004f58f0);
    }
    obj->f60 = a;
    obj->f64 = b;
}
