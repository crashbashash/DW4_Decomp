#ifndef DW4_PSX2PARTICLEFORMAT_H
#define DW4_PSX2PARTICLEFORMAT_H

/* The PS2 particle format an igPsx2ParticleArray keeps in _ps2ParticleFormat: how many keys of each
 * attribute a particle has and where each attribute sits in a row of `keysPerRow` particles. */
typedef struct Psx2ParticleFormat {
    char pad0[8];
    unsigned char positionCount;
    unsigned char colourCount;
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
    short colourOffset;
    short attributeOffset;
    short texCoordOffset;
} Psx2ParticleFormat;

#ifdef __cplusplus
extern "C" {
#endif

/* Decoders: each reads particle `index`'s keys of one attribute into the caller's arrays. */
void FUN_001fdca0(Psx2ParticleFormat *format, int index, float *first, float *second, float *third);
void FUN_001fdd60(Psx2ParticleFormat *format, int index, float *first, float *second, float *third);
void FUN_001fdeb0(Psx2ParticleFormat *format, int index, float *first, float *second, float *third);
void FUN_001fe100(Psx2ParticleFormat *format, int index, float *first, float *second, float *third);
void FUN_001fe260(Psx2ParticleFormat *format, int index, float *first, float *second);
void FUN_001fe320(Psx2ParticleFormat *format, int index, float *texCoord);

#ifdef __cplusplus
}
#endif

#endif
