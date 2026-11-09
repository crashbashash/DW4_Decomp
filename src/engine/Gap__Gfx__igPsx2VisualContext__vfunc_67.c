typedef struct S { char pad[956]; unsigned int f956; } S;
void Gap__Gfx__igPsx2VisualContext__vfunc_67(S *arg0, float *arg1) {
    unsigned int t;
    float f;
    t = (arg0->f956 >> 24) & 0xFF;
    f = (float)t;

    arg1[0] = 0.0078125f * f;
    t = (arg0->f956 >> 16) & 0xFF;
    f = (float)t;

    arg1[1] = 0.00392156886f * f;
    t = (arg0->f956 >> 8) & 0xFF;
    f = (float)t;

    arg1[2] = 0.00392156886f * f;
    t = arg0->f956 & 0xFF;
    f = (float)t;

    arg1[3] = 0.00392156886f * f;
}
