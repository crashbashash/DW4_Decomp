/* 0x0029a718 — FUN_0029a718 (188 bytes). If the stream at +68 is not in state 2, notifies the handler at +464, re-issues the request from +440..+460 and returns 1, or flags error 4 / reports -102 and returns -1 when FUN_0029b328 fails. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00291d30();
int FUN_00294ef8();
int FUN_0029a320();
int FUN_0029b2b0();
int FUN_0029b328();
int FUN_0029b390();
extern int DAT_004f4a40[4];

struct Handler { struct HandlerVtbl *vt; };
struct HandlerVtbl { char pad[20]; int (*fn20)(); };
struct Obj29a718 {
    char pad0[8];
    int f8;
    char pad12[68 - 12];
    int f68;
    char pad72[440 - 72];
    int f440;
    char pad444[448 - 444];
    int f448;
    int f452, f456, f460;
    struct Handler *f464;
};

int FUN_0029a718(struct Obj29a718 *obj) {
    struct Handler *handler;

    if (FUN_0029b390(obj->f68) == 2) {
        return -1;
    }
    handler = obj->f464;
    if (handler != 0) {
        handler->vt->fn20(handler);
    }
    FUN_0029b2b0(obj->f68, obj->f440, obj->f452, obj->f456, obj->f460);
    if (FUN_0029b328(obj->f68) == -1) {
        obj->f8 = 4;
        FUN_00294ef8(-102);
        FUN_0029a320(&DAT_004f4a40[0], obj->f440);
        obj->f448 = 0;
        return -1;
    }
    FUN_00291d30(obj);
    return 1;
}
