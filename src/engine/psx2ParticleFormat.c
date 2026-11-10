typedef struct Psx2ParticleFormat {
    char pad0[8];
    unsigned char positionCount;
    char pad9;
    unsigned char countA;
    unsigned char countB;
    unsigned char texCoordCount;
    unsigned char countC;
    unsigned char countD;
    char pad15;
    char *data;
    char pad20[16];
    unsigned char vertexWords;
    char pad37[7];
    short rowStride;
    short pad46;
    short keysPerRow;
    short positionOffset;
    short pad52;
    short attributeOffset;
    short texCoordOffset;
} Psx2ParticleFormat;

typedef struct ParticlePositionView { char p0[8]; unsigned char n; char p9[7]; char *base; char p14[24]; short s44; short p46; short s48; short s50; } ParticlePositionView;

typedef struct ParticleColourView { char pad0[9]; unsigned char f9; char pad10[6]; int f16; char pad20[24]; short f44; short pad46; short f48; short pad50; short f52; } ParticleColourView;

typedef struct ParticleSizeView { char pad0[10]; unsigned char f10; unsigned char f11; char pad12; unsigned char f13; unsigned char f14; char pad15; char *f16; char pad20[16]; unsigned char f36; char pad37[7]; short f44; short pad46; short f48; short pad50; short pad52; short f54; } ParticleSizeView;

typedef struct PackedTable {
    char _pad0[10];
    unsigned char widthA;
    unsigned char widthB;
    char _pad12;
    unsigned char widthC;
    unsigned char widthD;
    char _pad15;
    char *data;
    char _pad20[16];
    unsigned char stride;
    char _pad37[7];
    short rowBytes;
    short _pad46;
    short rowLength;
    short _pad50;
    short _pad52;
    short offset;
} PackedTable;

void FUN_001fd5a0(ParticlePositionView *o, int idx, float *a2, float *a3, float *a4) {
    char *p = o->base;
    short d = o->s48;
    float *t;
    int q = idx / d;
    int r = idx % d;
    int s = o->s44;
    p += 12;
    p += q * s;
    p += o->s50;
    p += r * o->n * 12;
    t = (float *)p;
    switch (o->n) {
    case 3:
        t[6] = a4[0]; t[7] = a4[1]; t[8] = a4[2];
    case 2:
        t[3] = a3[0]; t[4] = a3[1]; t[5] = a3[2];
    case 1:
        t[0] = a2[0]; t[1] = a2[1]; t[2] = a2[2];
    default:
        break;
    }
}

void FUN_001fd660(ParticleColourView *o, int arg1, float *arg2, float *arg3, float *arg4) {
    char *t5;
    int t, q, r;
    t = o->f16 + 12;
    q = arg1 / o->f48;
    q *= o->f44;
    t += q;
    t += o->f52;
    r = arg1 % o->f48;
    r *= o->f9;
    t += r * 16;
    t5 = (char *)t;
    switch (o->f9) {
    case 3:
        *(float *)(t5 + 32) = 255.0f * arg4[0];
        *(float *)(t5 + 36) = 255.0f * arg4[1];
        *(float *)(t5 + 40) = 255.0f * arg4[2];
        *(float *)(t5 + 44) = 128.0f * arg4[3];
    case 2:
        *(float *)(t5 + 16) = 255.0f * arg3[0];
        *(float *)(t5 + 20) = 255.0f * arg3[1];
        *(float *)(t5 + 24) = 255.0f * arg3[2];
        *(float *)(t5 + 28) = 128.0f * arg3[3];
    case 1:
        *(float *)(t5 + 0) = 255.0f * arg2[0];
        *(float *)(t5 + 4) = 255.0f * arg2[1];
        *(float *)(t5 + 8) = 255.0f * arg2[2];
        *(float *)(t5 + 12) = 128.0f * arg2[3];
    }
}

void FUN_001fd7a0(ParticleSizeView *o, int arg1, float *a2, float *a3, float *a4) {
    int a7;
    float * t;
    int a6;
    int t4;
    int v1;
    int a1;
    int q;
    int r;
    char * p;
    a7 = o->f48;
    p = o->f16;
    a6 = o->f11;
    t4 = o->f10;
    v1 = o->f36;
    q = arg1 / a7;
    p += 0xC;
    r = arg1 % a7;
    t4 = ((a6 < t4) ? t4 : a6) & 0xFF;
    a1 = o->f13;
    t4 = (a1 < t4) ? t4 : a1;
    a1 = o->f14;
    t4 = (a1 < t4) ? t4 : a1;
    p += q * o->f44;
    p += o->f54;
    p += v1 * (r * t4) * 4;
    t = (float *)p;
    if (v1 == 1) {
        switch (t4) {
        case 3: t[2] = 0.5f * a4[0];
        case 2: t[1] = 0.5f * a3[0];
        case 1: t[0] = 0.5f * a2[0];
        }
    } else if (v1 == 2) {
        switch (t4) {
        case 3: t[4] = 0.5f * a4[0]; t[5] = 0.5f * a4[1];
        case 2: t[2] = 0.5f * a3[0]; t[3] = 0.5f * a3[1];
        case 1: t[0] = 0.5f * a2[0]; t[1] = 0.5f * a2[1];
        }
    } else {
        if (v1 >= 3) {
            switch (t4) {
            case 3: *(float *)((char *)t + v1 * 8) = 0.5f * a4[0]; *(float *)((char *)t + v1 * 8 + 4) = 0.5f * a4[1];
            case 2: *(float *)((char *)t + v1 * 4) = 0.5f * a3[0]; *(float *)((char *)t + v1 * 4 + 4) = 0.5f * a3[1];
            case 1: t[0] = 0.5f * a2[0]; t[1] = 0.5f * a2[1];
            }
        }
    }
}

void FUN_001fd9f0(Psx2ParticleFormat *format, int index, const float *first, const float *second, const float *third) {
    int q;
    int r;
    char *p;
    int count;
    int words;

    p = format->data + 12;
    words = format->vertexWords;
    q = index / format->keysPerRow;
    r = index % format->keysPerRow;
    count = format->countA > format->countB ? format->countA : format->countB;
    count = format->countC < count ? count : format->countC;
    count = format->countD < count ? count : format->countD;
    p += q * format->rowStride;
    p += format->attributeOffset;
    p += (unsigned char)words * (r * count) * 4; /* matching construct: declaration and cast sweep — narrowed stride operand */
    switch (count) {
    case 3:
        ((float *)(p + words * 8))[2] = *third * 0.15915494309189535;
    case 2:
        ((float *)(p + words * 4))[2] = *second * 0.15915494309189535;
    case 1:
        ((float *)p)[2] = *first * 0.15915494309189535;
    }
}

/* matching construct: 120 declaration orders by 4 compare spellings */
void FUN_001fdb60(Psx2ParticleFormat *format, int index, float *first, float *second) {
    int q;
    int r;
    char *p;
    int words;
    int count;

    p = format->data + 12;
    words = format->vertexWords;
    q = index / format->keysPerRow;
    r = index % format->keysPerRow;
    count = format->countA > format->countB ? format->countA : format->countB;
    count = format->countC < count ? count : format->countC;
    count = format->countD < count ? count : format->countD;

    p += q * format->rowStride;
    p += format->attributeOffset;
    p += words * (r * count) * 4;
    switch (count) {
    case 3:
        ((float *)(p + words * 8))[3] = 0.0f;
    case 2:
        ((float *)(p + words * 4))[3] = *second;
    case 1:
        ((float *)p)[3] = *first;
    }
}

void FUN_001fdc30(Psx2ParticleFormat *format, int index, float *texCoord) {
    char *p;
    int t, q, r;
    t = (int)format->data + 12;
    q = index / format->keysPerRow;
    q *= format->rowStride;
    t += q;
    t += format->texCoordOffset;
    r = index % format->keysPerRow;
    r *= format->texCoordCount;
    t += r * 8;
    p = (char *)t;
    switch (format->texCoordCount) {
    case 1:
        *(float *)(p + 0) = texCoord[0];
        *(float *)(p + 4) = texCoord[1];
    }
}

/* matching construct: 8 variants, quotient and remainder in locals */
void FUN_001fdca0(Psx2ParticleFormat *format, int index, float *first, float *second, float *third) {
    float *v;
    char *p;
    int q;
    int r;

    p = format->data + 12;
    q = index / format->keysPerRow;
    p += q * format->rowStride;
    p += format->positionOffset;
    r = index % format->keysPerRow;
    p += r * format->positionCount * 12;
    v = (float *)p;
    switch (format->positionCount) {
    case 3:
        third[0] = v[6];
        third[1] = v[7];
        third[2] = v[8];
    case 2:
        second[0] = v[3];
        second[1] = v[4];
        second[2] = v[5];
    case 1:
        first[0] = v[0];
        first[1] = v[1];
        first[2] = v[2];
    }
}

void FUN_001fdd60(ParticleColourView *o, int arg1, float *arg2, float *arg3, float *arg4) {
    char *t5;
    int t, q, r;
    t = o->f16 + 12;
    q = arg1 / o->f48;
    q *= o->f44;
    t += q;
    t += o->f52;
    r = arg1 % o->f48;
    r *= o->f9;
    t += r * 16;
    t5 = (char *)t;
    switch (o->f9) {
    case 3:
        arg4[0] = 0.00392156886f * *(float *)(t5 + 32);
        arg4[1] = 0.00392156886f * *(float *)(t5 + 36);
        arg4[2] = 0.00392156886f * *(float *)(t5 + 40);
        arg4[3] = 0.0078125f * *(float *)(t5 + 44);
    case 2:
        arg3[0] = 0.00392156886f * *(float *)(t5 + 16);
        arg3[1] = 0.00392156886f * *(float *)(t5 + 20);
        arg3[2] = 0.00392156886f * *(float *)(t5 + 24);
        arg3[3] = 0.0078125f * *(float *)(t5 + 28);
    case 1:
        arg2[0] = 0.00392156886f * *(float *)(t5 + 0);
        arg2[1] = 0.00392156886f * *(float *)(t5 + 4);
        arg2[2] = 0.00392156886f * *(float *)(t5 + 8);
        arg2[3] = 0.0078125f * *(float *)(t5 + 12);
    }
}

void FUN_001fdeb0(ParticleSizeView *o, int arg1, float *a2, float *a3, float *a4) {
    int a7;
    float * t;
    int a6;
    int t4;
    int v1;
    int a1;
    int q;
    int r;
    char * p;
    a7 = o->f48;
    p = o->f16;
    a6 = o->f11;
    t4 = o->f10;
    v1 = o->f36;
    q = arg1 / a7;
    p += 0xC;
    r = arg1 % a7;
    t4 = ((a6 < t4) ? t4 : a6) & 0xFF;
    a1 = o->f13;
    t4 = (a1 < t4) ? t4 : a1;
    a1 = o->f14;
    t4 = (a1 < t4) ? t4 : a1;
    p += q * o->f44;
    p += o->f54;
    p += v1 * (r * t4) * 4;
    t = (float *)p;
    if (v1 == 1) {
        switch (t4) {
        case 3: a4[0] = 2.0f * t[2];
        case 2: a3[0] = 2.0f * t[1];
        case 1: a2[0] = 2.0f * t[0];
        }
    } else if (v1 == 2) {
        switch (t4) {
        case 3: a4[0] = 2.0f * t[4]; a4[1] = 2.0f * t[5];
        case 2: a3[0] = 2.0f * t[2]; a3[1] = 2.0f * t[3];
        case 1: a2[0] = 2.0f * t[0]; a2[1] = 2.0f * t[1];
        }
    } else {
        if (v1 >= 3) {
            switch (t4) {
            case 3: a4[0] = 2.0f * *(float *)((char *)t + v1 * 8); a4[1] = 2.0f * *(float *)((char *)t + v1 * 8 + 4);
            case 2: a3[0] = 2.0f * *(float *)((char *)t + v1 * 4); a3[1] = 2.0f * *(float *)((char *)t + v1 * 4 + 4);
            case 1: a2[0] = 2.0f * t[0]; a2[1] = 2.0f * t[1];
            }
        }
    }
}

void FUN_001fe100(Psx2ParticleFormat *format, int index, float *first, float *second, float *third) {
    int q;
    int r;
    char *p;
    int words;
    int count;

    p = format->data + 12;
    words = format->vertexWords;
    q = index / format->keysPerRow;
    r = index % format->keysPerRow;
    count = format->countA > format->countB ? format->countA : format->countB;
    count = format->countC < count ? count : format->countC;
    count = format->countD < count ? count : format->countD;
    p += q * format->rowStride;
    p += format->attributeOffset;
    p += words * (r * count) * 4;
    switch (count) {
    case 3:
        *third = ((float *)(p + words * 8))[2] * 6.283185307179586;
    case 2:
        *second = ((float *)(p + words * 4))[2] * 6.283185307179586;
    case 1:
        *first = ((float *)p)[2] * 6.283185307179586;
    }
}

/* matching construct: declaration-order sweep — values, row, cursor, column, rowLength, b, c, stride, width */
void FUN_001fe260(PackedTable *table, int index, float *first, float *second) {
    float *values;
    int row;
    char *cursor;
    int column;
    int rowLength;
    int b;
    int c;
    int stride;
    int width;

    rowLength = table->rowLength;
    cursor = table->data;
    b = table->widthB;
    width = table->widthA;
    stride = table->stride;
    row = index / rowLength;
    cursor += 0xC;
    column = index % rowLength;
    width = ((b < width) ? width : b) & 0xFF;
    c = table->widthC;
    width = (c < width) ? width : c;
    c = table->widthD;
    width = (c < width) ? width : c;
    cursor += row * table->rowBytes;
    cursor += table->offset;
    cursor += stride * (column * width) * 4;
    values = (float *)cursor;
    switch (width) {
    case 3:
    case 2:
        second[0] = *(float *)((char *)values + stride * 4 + 12);
    case 1:
        first[0] = values[3];
    }
}

void FUN_001fe320(Psx2ParticleFormat *format, int index, float *texCoord) {
    char *p;
    int t, q, r;
    t = (int)format->data + 12;
    q = index / format->keysPerRow;
    q *= format->rowStride;
    t += q;
    t += format->texCoordOffset;
    r = index % format->keysPerRow;
    r *= format->texCoordCount;
    t += r * 8;
    p = (char *)t;
    switch (format->texCoordCount) {
    case 1:
        texCoord[0] = *(float *)(p + 0);
        texCoord[1] = *(float *)(p + 4);
    }
}
