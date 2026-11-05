extern float DAT_004e1170[4];
extern float D_004e1170[4];
extern float D_004e1180[4];
extern float DAT_004e1174[4];
extern float DAT_004e1178[4];
extern float DAT_004e117c[4];
extern float DAT_004e1180[4];
extern float DAT_004e1184[4];
extern float DAT_004e1188[4];
extern float DAT_004e118c[4];
int FUN_001931b0(float *arg0, unsigned int arg1) {
    float r, g, b, a;
    int res;
    float mx = DAT_004e1180[0];
    r = arg0[0]; g = arg0[1]; b = arg0[2]; a = arg0[3];
    res = 0;
    if (r > D_004e1180[0]) r = mx;
if (g > DAT_004e1184[0]) g = DAT_004e1184[0];
if (b > DAT_004e1188[0]) b = DAT_004e1188[0];
if (a > DAT_004e118c[0]) a = DAT_004e118c[0];
{ float mn = DAT_004e1170[0]; if (r < D_004e1170[0]) r = mn; }
if (g < DAT_004e1174[0]) g = DAT_004e1174[0];
if (b < DAT_004e1178[0]) b = DAT_004e1178[0];
if (a < DAT_004e117c[0]) a = DAT_004e117c[0];
    switch (arg1) {
    case 4: res |= (int)(0.5f + 255.0f * r); res |= (int)(0.5f + 255.0f * g) << 8; res |= (int)(0.5f + 255.0f * b) << 16; break;
    case 3: res |= (int)(0.5f + 255.0f * b); res |= (int)(0.5f + 255.0f * g) << 8; res |= (int)(0.5f + 255.0f * r) << 16; break;
    case 2: res |= (int)(0.5f + 255.0f * a); res |= (int)(0.5f + 255.0f * r) << 8; res |= (int)(0.5f + 255.0f * g) << 16; res |= (int)(0.5f + 255.0f * b) << 24; break;
    case 0: res |= (int)(0.5f + 255.0f * a); res |= (int)(0.5f + 255.0f * b) << 8; res |= (int)(0.5f + 255.0f * g) << 16; res |= (int)(0.5f + 255.0f * r) << 24; break;
    case 1: res |= (int)(0.5f + 255.0f * a) << 24; res |= (int)(0.5f + 255.0f * b) << 16; res |= (int)(0.5f + 255.0f * g) << 8; res |= (int)(0.5f + 255.0f * r); break;
    case 6: res |= (int)(0.5f + 255.0f * a) << 24; res |= (int)(0.5f + 255.0f * r) << 16; res |= (int)(0.5f + 255.0f * g) << 8; res |= (int)(0.5f + 255.0f * b); break;
    }
    return res;
}
