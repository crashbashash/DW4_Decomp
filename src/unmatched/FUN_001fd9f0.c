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
