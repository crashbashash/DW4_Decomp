extern "C" {
int Matrix44_GetTranslation(int, float *);
extern int DAT_0058a1e8[4];
float MDLgetKyoriSquare(float x, float y, float z);
}

float MDLgetKyoriSquare(float x, float y, float z) {
    float v[3];
    float dx, dy, dz;
    Matrix44_GetTranslation(DAT_0058a1e8[0], v);
    dy = v[1] - y;
    dx = v[0] - x;
    dz = v[2] - z;
    return dx * dx + dy * dy + dz * dz;
}
