void FUN_00191860(float *m, float l, float r, float b, float t, float n, float f) {
 float x, y, z;
x = 1.0f / (r - l);
m[0] = 2.0f * x;
m[4] = 0;
m[8] = 0;
m[12] = x * -(r + l);
y = 1.0f / (t - b);
m[1] = 0;
m[5] = 2.0f * y;
m[9] = 0;
m[13] = y * -(t + b);
z = 1.0f / (f - n);
m[2] = 0;
m[6] = 0;
m[10] = -2.0f * z;
m[14] = z * -(f + n);
m[3] = 0;
m[7] = 0;
m[11] = 0;
m[15] = 1.0f;
}
