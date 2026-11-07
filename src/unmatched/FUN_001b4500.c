struct S { char p0[12]; int k; char p1[100]; float firstX,firstY,firstZ,secondX,secondY,secondZ; };
struct O { char p0[56]; float x,y,z; int w; char p1[64]; struct S *s; };
void FUN_001b4500(struct O *o, struct S *s, int b) {
    s = o->s;
    if (s != 0) {
        if (s->k == 1) { o->x = s->firstX; o->y = s->firstY; o->z = s->firstZ; o->w = 0x3F800000; return; }
        o->x = s->secondX; o->y = s->secondY; o->z = s->secondZ; o->w = 0;
    }
}
