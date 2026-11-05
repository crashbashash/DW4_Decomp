int FUN_0020e3c0(float);
float FUN_0020e3d0(void);
extern int DAT_00490e88[4];
void FUN_001f4300(int **arg0, int arg1, float fparg0) {
    int *p;

    if ((arg1 != 0) || (fparg0 != FUN_0020e3d0())) {
        p = *arg0;
        *arg0 = p + 1;
        *p = DAT_00490e88[0];
        p = *arg0;
        *arg0 = p + 1;
        *p = arg1;
        p = *arg0;
        *arg0 = p + 1;
        *p = arg1;
        p = *arg0;
        *arg0 = p + 1;
        *p = arg1;
        if (fparg0 == 1.0f) {
            p = *arg0;
            *arg0 = p + 1;
            *(float *)p = 1.0f;
        } else {
            p = *arg0;
            *arg0 = p + 1;
            *p = arg1;
        }
        FUN_0020e3c0(fparg0);
    }
}
