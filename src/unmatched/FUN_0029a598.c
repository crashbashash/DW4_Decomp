/* 0x0029a598 — FUN_0029a598 (244 bytes). In state 3, once the sub-object at +660 is in state 2 or its slot-36 query returns 0, runs the follow-up calls gated by the flag bytes at +116/+118. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
int FUN_00295398();
int FUN_00295908();
int FUN_00299ae8();
int FUN_00299bc0();
int FUN_0029a320();
int FUN_0029ece8();
int FUN_002ad910();
extern int DAT_004f4a10[4];

struct Obj29a598;
struct VtblA { char pad[36]; int (*fn36)(); };
struct Inner { struct VtblA *vt; };
struct Sub294 { int f0, f4, f8; struct Inner *f12; };
struct Obj29a598 {
    char pad0[64];
    int f64;
    char pad68[116 - 68];
    signed char f116;
    char pad117;
    signed char f118;
    char pad119[660 - 119];
    struct Sub294 f660;
};

void FUN_0029a598(struct Obj29a598 *obj) {
    struct Sub294 *sub = &obj->f660;
    int state = FUN_002ad910(obj->f64);
    int subState = FUN_00299ae8(sub);

    /* matching construct: manual — nested ifs instead of early returns keep the final call a sibling (tail) call */
    if (state == 3) {
        if (subState == 2 || sub->f12->vt->fn36(sub->f12, 1) == 0) {
            FUN_00295398(obj);
            if (obj->f118 == 0) {
                FUN_00295908(obj, 0);
            }
            if (obj->f116 == 1 && FUN_0029ece8(obj->f64) != 0) {
                FUN_0029a320(&DAT_004f4a10[0]);
            }
            if (obj->f118 == 0) {
                FUN_00299bc0(sub, 0);
            }
        }
    }
}
