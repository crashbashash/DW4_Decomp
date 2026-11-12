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

/* Unpacks a packed 32-bit colour into a 4-float vector, selected by pixel format: each case
 * converts the four bytes of arg2 with (float)(byte) / 255.0f and stores x,y,z,w. Formats: 0 RGBA,
 * 1 ABGR, 2 BGRA, 3 RGB (w=0), 4 BGR (w=0), 6 ARGB; 5 is not handled (no-op). */
void FUN_00193540(Color4f *out, unsigned int format, unsigned int packed)
{
    switch (format) {
    case 2:
        out->z = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->y = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->x = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->w = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 0:
        out->x = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->y = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->z = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->w = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 3:
        out->w = 0.0f;
        out->x = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->z = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 4:
        out->w = 0.0f;
        out->z = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->x = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 1:
        out->w = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->z = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->x = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    case 6:
        out->w = BYTE_TO_UNIT(packed, 0xFF000000, 24);
        out->x = BYTE_TO_UNIT(packed, 0x00FF0000, 16);
        out->y = BYTE_TO_UNIT(packed, 0x0000FF00, 8);
        out->z = BYTE_TO_UNIT(packed, 0x000000FF, 0);
        break;
    default:
        break;
    }
}

void FUN_00193c50(float *out, float *v, float *m) {
    float a = v[0];
    float b = v[1];
    float c = v[2];
    out[0] = m[12] + (a * m[0] + b * m[4] + c * m[8]);
    out[1] = m[13] + (a * m[1] + b * m[5] + c * m[9]);
    out[2] = m[14] + (a * m[2] + b * m[6] + c * m[10]);
    out[3] = m[15] + (a * m[3] + b * m[7] + c * m[11]);
}

