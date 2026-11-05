extern float * DAT_0058a218[4];
void MDLsetWorldPosTarget_78(float fparg0, float fparg1, float fparg2) {
    float *p = DAT_0058a218[0];
    if (p != 0) {
        p[0] = fparg0;
        p[1] = fparg1;
        p[2] = fparg2;
    }
}
