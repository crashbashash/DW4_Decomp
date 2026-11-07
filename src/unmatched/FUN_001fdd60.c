typedef struct S { char pad0[9]; unsigned char f9; char pad10[6]; int f16; char pad20[24]; short f44; short pad46; short f48; short pad50; short f52; } S;
void FUN_001fdd60(S *o, int arg1, float *arg2, float *arg3, float *arg4) {
    char *t5;
    int t, q, r;
    t = o->f16 + 12;
    q = arg1 / o->f48;
    q *= o->f44;
    t += q;
    t += o->f52;
    r = arg1 % o->f48;
    r *= o->f9;
    t += r * 16;
    t5 = (char *)t;
    switch (o->f9) {
    case 3:
        arg4[0] = 0.00392156886f * *(float *)(t5 + 32);
        arg4[1] = 0.00392156886f * *(float *)(t5 + 36);
        arg4[2] = 0.00392156886f * *(float *)(t5 + 40);
        arg4[3] = 0.0078125f * *(float *)(t5 + 44);
    case 2:
        arg3[0] = 0.00392156886f * *(float *)(t5 + 16);
        arg3[1] = 0.00392156886f * *(float *)(t5 + 20);
        arg3[2] = 0.00392156886f * *(float *)(t5 + 24);
        arg3[3] = 0.0078125f * *(float *)(t5 + 28);
    case 1:
        arg2[0] = 0.00392156886f * *(float *)(t5 + 0);
        arg2[1] = 0.00392156886f * *(float *)(t5 + 4);
        arg2[2] = 0.00392156886f * *(float *)(t5 + 8);
        arg2[3] = 0.0078125f * *(float *)(t5 + 12);
    }
}
