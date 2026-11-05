float FUN_00123138(float);
float FUN_00123628(float);
float FUN_00123640(float, float);
int igMatrix44f_SetIdentity(float *);
int FUN_001916f0(float *, int);

void FUN_00192990(int arg0, float *arg1, float *arg2, float *arg3) {
    float m[16];
    float t;
    float x;
    float r;

    igMatrix44f_SetIdentity(m);
    FUN_001916f0(m, arg0);
    x = -m[2];
    t = (x > -1.0f) ? x : -1.0f;
    if (t < 1.0f) {
        x = (x > -1.0f) ? x : -1.0f;
    } else {
        x = 1.0f;
    }
    r = FUN_00123628(x);
    *arg2 = r;
    if (FUN_00123138(r) != 0.0f) {
        *arg1 = FUN_00123640(m[6], m[10]);
        *arg3 = FUN_00123640(m[1], m[0]);
        return;
    }
    *arg2 = FUN_00123640(m[4], m[5]);
    *arg3 = 0.0f;
}
