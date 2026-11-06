/* Edge-detect state update; forwarded this to the helper, stack float pair, countdown arm order. */
struct V2 { float x; float y; };
struct O { char pad[12]; float f12; float f16; char pad2[8]; int f28; int f32; int f36; int f40; int f44; char pad3[48]; int f96; int f100; };
extern "C" {
int FUN_0039b110(struct O *, int *, struct V2 *);
void FUN_0039af90(struct O *arg0, struct V2 *arg1);
}
void FUN_0039af90(struct O *arg0, struct V2 *arg1) {
    struct V2 v;
    arg0->f12 = arg1->x;
    arg0->f16 = arg1->y;
    arg0->f40 = arg0->f36;
    v.x = arg0->f12;
    v.y = arg0->f16;
    FUN_0039b110(arg0, &arg0->f36, &v);
    arg0->f28 = arg0->f36 & (arg0->f40 ^ arg0->f36);
    if ((arg0->f40 ^ arg0->f36) != 0) {
        arg0->f32 = arg0->f28;
        arg0->f44 = arg0->f96;
    } else {
        if (--arg0->f44 != 0) {
            arg0->f32 = 0;
        } else {
            arg0->f32 = arg0->f36;
            arg0->f44 = arg0->f100;
        }
    }
}
