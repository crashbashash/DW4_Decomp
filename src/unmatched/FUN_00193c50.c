void FUN_00193c50(float *out, float *v, float *m) {
    float a = v[0];
    float b = v[1];
    float c = v[2];
    out[0] = m[12] + (a * m[0] + b * m[4] + c * m[8]);
    out[1] = m[13] + (a * m[1] + b * m[5] + c * m[9]);
    out[2] = m[14] + (a * m[2] + b * m[6] + c * m[10]);
    out[3] = m[15] + (a * m[3] + b * m[7] + c * m[11]);
}
