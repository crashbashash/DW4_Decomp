/* 0x002b47d8 — FUN_002b47d8 (244 bytes). Clears the first 0x400 bytes of buf, fills buf+0x400 with FUN_002b4630, then hands both halves to the object's callback at +68 (with its floats at +60/+64) or, without one, to FUN_002b48d0 (mode 16 at +4) or FUN_002b4960. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_002b4630();
int FUN_002b48d0();
int FUN_002b4960();
void *memset(void *, int, unsigned int);

typedef void (*BufferCallback)(char *, char *, float, float);

struct Obj0044 {
    int f0;
    int f4;                               /* mode; 16 selects FUN_002b48d0 */
    char pad8[60 - 8];
    float f60;                            /* also set by FUN_002b4aa8 */
    float f64;
    BufferCallback callback;              /* +68: optional override */
};

void FUN_002b47d8(struct Obj0044 *obj, int arg1, int arg2, char *buf) {
    char *second = buf + 0x400;
    BufferCallback callback;

    memset(buf, 0, 0x400);
    FUN_002b4630(obj, arg1, arg2, second);
    callback = obj->callback;
    if (callback == 0) {
        if (obj->f4 == 16) {
            FUN_002b48d0(obj, second, buf);
            return;
        }
        FUN_002b4960(obj, second, buf);
        return;
    }
    callback(second, buf, obj->f60, obj->f64);
}
