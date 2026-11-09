typedef struct Psx2ParticleFormat {
    char pad0[8];
    unsigned char positionCount;
    char pad9;
    unsigned char countA;
    unsigned char countB;
    char pad12;
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
} Psx2ParticleFormat;

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
