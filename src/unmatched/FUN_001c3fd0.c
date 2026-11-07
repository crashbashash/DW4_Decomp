int FUN_001c3fd0(float *v) {
    float a[3];
    int r = -1;
    int i;
    a[0] = *(volatile float *)&v[0];
    a[1] = *(volatile float *)&v[1];
    a[2] = *(volatile float *)&v[2];
    for (i = 0; i < 3; i++) {
        if (a[i] < 0.0f) {
            a[i] = a[i] * -1.0f;
        }
    }
    if (a[0] > a[1] && a[0] > a[2]) {
        if (v[0] < 0.0f) {
            r = 0;
        } else if (v[0] > 0.0f) {
            r = 1;
        }
    } else if (a[1] > a[0] && a[1] > a[2]) {
        if (v[1] < 0.0f) {
            r = 2;
        } else if (v[1] > 0.0f) {
            r = 3;
        }
    } else if (a[2] > a[0] && a[2] > a[1]) {
        if (v[2] < 0.0f) {
            r = 4;
        } else if (v[2] > 0.0f) {
            r = 5;
        }
    }
    return r;
}
