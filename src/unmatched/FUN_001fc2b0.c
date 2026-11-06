float FUN_001fc030();
void FUN_001fc2b0(int arg0, float *arg1) {
    float v[16];
    int i;
    float inv = 1.0f / FUN_001fc030(arg0, v);
    for (i = 0; i < 16; i++) {
        arg1[i] = inv * v[i];
    }
}
