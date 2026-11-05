extern float GPR_00554904;
typedef struct S { char pad[956]; unsigned int f956; } S;
void FUN_0016d010(S *arg0, float *arg1) {
    unsigned int t;
    float f;
    t = (*(volatile unsigned int *)&arg0->f956 >> 24) & 0xFF;
    f = (float)t;

    arg1[0] = 0.0078125f * f;
    t = (*(volatile unsigned int *)&arg0->f956 >> 16) & 0xFF;
    f = (float)t;

    arg1[1] = GPR_00554904 * f;
    t = (*(volatile unsigned int *)&arg0->f956 >> 8) & 0xFF;
    f = (float)t;

    arg1[2] = GPR_00554904 * f;
    t = *(volatile unsigned int *)&arg0->f956 & 0xFF;
    f = (float)t;

    arg1[3] = GPR_00554904 * f;
}
