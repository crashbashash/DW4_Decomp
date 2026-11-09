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
