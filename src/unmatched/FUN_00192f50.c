void FUN_00192f50(float *out, float *v, float *m) {
    float x = v[0];
    float y = v[1];
    float z = v[2];
    out[0] = x * m[0] + y * m[4] + z * m[8];
    out[1] = x * m[1] + y * m[5] + z * m[9];
    out[2] = x * m[2] + y * m[6] + z * m[10];
}
