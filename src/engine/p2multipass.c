/* Multipass texturing. With the multipass capability on, each texture stage beyond the first is
 * drawn as a pass of its own in GS context 2, so the GS register sets of the stages and the stage
 * capabilities are read per pass. p2SetPassCount sets how many passes there are. */
#include "dw4/p2core.h"

/* GS TEX0.TFX, p2TextureFunction */
enum {
    P2_TFX_MODULATE,
    P2_TFX_DECAL,
    P2_TFX_HIGHLIGHT,
    P2_TFX_HIGHLIGHT2
};

/* GS register numbers written into the pass packet (A+D data). */
enum {
    P2_GS_REG_TEX0_1 = 0x06,
    P2_GS_REG_TEX0_2 = 0x07,
    P2_GS_REG_TEX1_1 = 0x14,
    P2_GS_REG_TEX1_2 = 0x15,
    P2_GS_REG_MIPTBP1_1 = 0x34,
    P2_GS_REG_ALPHA_1 = 0x42,
    P2_GS_REG_ALPHA_2 = 0x43,
    P2_GS_REG_TEXFLUSH = 0x3F
};

#define P2_PASS_COUNT_UNSET 0x1234

#define P2_STAGE_FLAG(stage, cap) ((p2ProgramFlags[stage] >> (cap)) & 1)

extern int p2TextureCombineMode[P2_PROGRAM_COUNT];
extern int p2TextureFunction[P2_PROGRAM_COUNT];
extern int p2PassFrameMask;
extern int p2PassZbufMask;
extern unsigned int p2PassDmaTag[4];
extern unsigned int p2PassGifTag[4];
extern unsigned int p2PassUnpack[2];
extern unsigned int p2PassMscnt[2];

/* The low (0) or high (1) word of a 64-bit GS register image. */
#define P2_GS_WORD(reg, half) (((unsigned int *)&(reg))[half])

/* The number of passes beyond the first, which the stages 1.. draw. */
void p2SetPassCount(int passes) {
    int extra;

    extra = passes - 1;
    extra = extra > 0 ? extra : 0;
    p2ExtraPassCount = extra;
    p2DirtyFlags |= 0x191;
}

/* Context 2 takes over the context 1 drawing area, frame, depth and test registers. */
#define P2_COPY_TO_CONTEXT_2(reg)                                          \
    gs = p2CurrentGsRegisters;                                             \
    gs->reg[1].half[0] = gs->reg[0].half[0];                               \
    gs->reg[1].half[1] = gs->reg[0].half[1]

void p2CopyContext1ToContext2(void) {
    p2GsRegisterSet *gs;

    P2_COPY_TO_CONTEXT_2(frame);
    P2_COPY_TO_CONTEXT_2(zbuf);
    P2_COPY_TO_CONTEXT_2(test);
    gs = p2CurrentGsRegisters;
    gs->xyoffset[1].field.ofx = gs->xyoffset[0].field.ofx;
    gs->xyoffset[1].field.f2 = gs->xyoffset[0].field.f2;
    gs->xyoffset[1].field.ofy = gs->xyoffset[0].field.ofy;
    gs->xyoffset[1].field.f6 = gs->xyoffset[0].field.f6;
    P2_COPY_TO_CONTEXT_2(scissor);
    P2_COPY_TO_CONTEXT_2(fba);
    p2DirtyFlags |= P2_DIRTY_GS_REGISTERS;
    p2GsDirtyRegisters |= 0x40000 | ((long long)0xA902 << 32);
}


/* Whether the drawn stages are textured as asked, `textured` with the combiner off when
 * `uncombined`: with `all` set, whether every stage is, else whether any stage is. */
int p2StagesTextured(int all, unsigned int textured, int uncombined) {
    int stage;
    int last;
    int combined;
    int plain;
    unsigned int flags;
    unsigned int texture;

    last = 0;
    if (P2_STAGE_FLAG(p2CurrentProgram, P2_CAP_MULTIPASS)) {
        last = p2ExtraPassCount;
    }
    for (stage = 0; stage <= last; stage++) {
        flags = p2ProgramFlags[stage];
        texture = (flags >> P2_CAP_TEXTURE) & 1;
        if (textured == texture) {
            combined = uncombined != 0 ? ((flags >> P2_CAP_TEXTURE_COMBINE) & 1) : 0;
            if (combined == 0) {
                goto matched;
            }
        }
        if (all != 0) {
            all = 0;
            break;
        }
matched:
        if (textured == texture) {
            plain = uncombined != 0 ? (unsigned char)!((flags >> P2_CAP_TEXTURE_COMBINE) & 1) : 1;
            if (plain != 0 && all == 0) {
                all = 1;
                break;
            }
        }
    }
    return all;
}

/* Whether every drawn stage (`all`) or any of them textures with the vertex colour taking part, that
 * is with a texture function other than decal. */
int p2StagesUseVertexColour(int all) {
    int stage;
    int last;

    last = 0;
    if (P2_STAGE_FLAG(p2CurrentProgram, P2_CAP_MULTIPASS)) {
        last = p2ExtraPassCount;
    }
    for (stage = 0; last >= stage; stage++) {
        int offset = stage * sizeof(int);
        int textured = (*(unsigned int *)((char *)p2ProgramFlags + offset) >> P2_CAP_TEXTURE) & 1;

        if ((textured == 0 || *(int *)((char *)p2TextureFunction + offset) != P2_TFX_DECAL) && all != 0) {
            all = 0;
            break;
        } else if (textured != 0 && *(int *)((char *)p2TextureFunction + offset) != P2_TFX_DECAL && all == 0) {
            all = 1;
            break;
        }
    }
    return all;
}

/* Whether a drawn stage from `first` on textures with the combiner on in combine mode 1 or 3. */
int p2StagesUseOddCombineMode(int first) {
    int stage;
    int last;
    int found;

    found = 0;
    if (P2_STAGE_FLAG(p2CurrentProgram, P2_CAP_MULTIPASS)) {
        last = p2ExtraPassCount;
    } else {
        last = 0;
    }
    for (stage = first; last >= stage; stage++) {
        unsigned int flags = p2ProgramFlags[stage];
        unsigned int textured = (flags >> P2_CAP_TEXTURE) & 1;
        unsigned int combined = (flags >> P2_CAP_TEXTURE_COMBINE) & 1;

        if (textured && combined) {
            if (p2TextureCombineMode[stage] == 1 || p2TextureCombineMode[stage] == 3) {
                found = 1;
                break;
            }
        }
    }
    return found;
}

/* The highest combine mode among the drawn stages that texture with the combiner on, or -1. */
int p2GetPassCombineMode(void) {
    int stage;
    int last;
    int mode;

    mode = -1;
    if (P2_STAGE_FLAG(p2CurrentProgram, P2_CAP_MULTIPASS)) {
        last = p2ExtraPassCount;
    } else {
        last = 0;
    }
    for (stage = 0; last >= stage; stage++) {
        unsigned int flags = p2ProgramFlags[stage];
        unsigned int textured = (flags >> P2_CAP_TEXTURE) & 1;
        unsigned int combined = (flags >> P2_CAP_TEXTURE_COMBINE) & 1;

        if (textured && combined) {
            int *stageMode = &p2TextureCombineMode[stage];
            const int *value = stageMode;

            switch (*value) {
            case 0:
            case 1:
            case 2:
            case 3:
                if (mode != 4) {
                    mode = *stageMode;
                }
                break;
            case 4:
                mode = 4;
                break;
            }
        }
    }
    return mode;
}

/* Appends the GS setup of `pass` to the packet at *packet: its pass number for the VU1 program, then
 * an A+D GIF tag loading the pass's ALPHA, TEX0 and TEX1 (context 2 for passes beyond the first,
 * from the register set of stage pass-1) and flushing the texture cache, then MSCNT. With `tagged`
 * set, the DMA tag that heads the packet comes first. */
void p2WritePassPacket(unsigned int **packet, int pass, int tagged) {
    unsigned int *word;
    int stage;
    p2GsRegisterSet *gs;

    if (tagged != 0) {
        word = *packet;
        *packet = word + 4;
        word[0] = p2PassDmaTag[0];
        word[1] = p2PassDmaTag[1];
        word[2] = p2PassDmaTag[2];
        word[3] = p2PassDmaTag[3];
    }
    word = *packet; *packet = word + 1; *word = p2PassUnpack[0];
    word = *packet; *packet = word + 1; *word = pass;
    if (pass > 0) {
        *(*packet)++ = pass;
    } else {
        *(*packet)++ = P2_PASS_COUNT_UNSET;
    }
    word = *packet; *packet = word + 1; *word = pass;
    if (pass > 1) {
        stage = pass - 1;
    } else {
        stage = 0;
    }
    gs = &p2GsRegisterSets[stage];
    *(*packet)++ = p2PassGifTag[0];
    *(*packet)++ = p2PassGifTag[1];
    *(*packet)++ = p2PassGifTag[2];
    if (pass > 0) {
        *(*packet)++ = P2_GS_WORD(gs->alpha[1], 0);
        *(*packet)++ = P2_GS_WORD(gs->alpha[1], 1);
        *(*packet)++ = P2_GS_REG_ALPHA_2;
        *(*packet)++ = gs->tex0[1].half[0];
        *(*packet)++ = gs->tex0[1].half[1];
        *(*packet)++ = P2_GS_REG_TEX0_2;
        *(*packet)++ = P2_GS_WORD(gs->tex1[1], 0);
        *(*packet)++ = P2_GS_WORD(gs->tex1[1], 1);
        *(*packet)++ = P2_GS_REG_TEX1_2;
    } else {
        *(*packet)++ = P2_GS_WORD(gs->alpha[0], 0);
        *(*packet)++ = P2_GS_WORD(gs->alpha[0], 1);
        *(*packet)++ = P2_GS_REG_ALPHA_1;
        *(*packet)++ = gs->tex0[0].half[0];
        *(*packet)++ = gs->tex0[0].half[1];
        *(*packet)++ = P2_GS_REG_TEX0_1;
        *(*packet)++ = P2_GS_WORD(gs->tex1[0], 0);
        *(*packet)++ = P2_GS_WORD(gs->tex1[0], 1);
        *(*packet)++ = P2_GS_REG_TEX1_1;
    }
    word = *packet; *packet = word + 1; *word = 0;
    word = *packet; *packet = word + 1; *word = 0;
    *(*packet)++ = P2_GS_REG_TEXFLUSH;
    word = *packet; *packet = word + 1; *word = p2PassMscnt[0];
}

/* The FRAME and ZBUF masks `pass` draws with: a later pass over a textured stage keeps the
 * colour and depth as they are, an untextured one keeps only the depth. */
void p2GetPassMasks(int pass, unsigned int *frameMask, unsigned int *zbufMask) {
    if (pass > 0) {
        if (P2_STAGE_FLAG(pass, P2_CAP_TEXTURE)) {
            *frameMask = p2PassFrameMask | 0x01080000;
            *zbufMask = p2PassZbufMask | 0x01080000;
        } else {
            *frameMask = (p2PassFrameMask | 0x01000000) & ~0x80000;
            *zbufMask = (p2PassZbufMask | 0x01000000) & ~0x80000;
        }
    } else {
        *frameMask = p2PassFrameMask;
        *zbufMask = p2PassZbufMask;
    }
}

extern unsigned int DAT_00491360[4];
extern unsigned int DAT_00491370, DAT_00491378, DAT_00491380;
extern unsigned int DAT_00569378, DAT_0056937c;
typedef struct { char pad0[40]; unsigned int *end; unsigned int pad44; unsigned int *cursor; } GsPacketBuffer;
extern GsPacketBuffer *DAT_00568f04;
extern int p2DisplayListMode;
void p2GrowDisplayList(void);
void p2SubmitDmaPacket(int arg);


/* The layout of a particle block: per-row arrays of the components the particle format has. */
typedef struct p2ParticleFormat {
    int count;
    int primitive;
    unsigned char positionCount;
    unsigned char colourCount;
    unsigned char sizeCount0;
    unsigned char sizeCount1;
    unsigned char texCoordCount;
    unsigned char byteCount;
    unsigned char wordCount;
    char pad15;
    char *data;
    int size;
    char pad24[12];
    unsigned char attributeKind;
    unsigned char verticesPerPrimitive;
    unsigned char headerBytes;
    unsigned char tagBytes;
    unsigned char trailerBytes;
    char pad41[3];
    short rowStride;
    short rowCount;
    short keysPerRow;
    short positionOffset;
    short colourOffset;
    short attributeOffset;
    short texCoordOffset;
    short endOffset;
    short vuAddress0;
    short vuAddress2;
    short vuAddress1;
    short vuAddress3;
    int vertexFormat;
} p2ParticleFormat;

extern int p2VertexFormat;
extern int p2CurrentPrimitive;
extern p2VuBufferLayout p2VuBuffers;
int p2LayoutVuBuffers(void);

/* Lays out a particle block for `format`: the vertex format and attribute kind its components
 * need, how many particles a row holds (what one VU batch takes, whole primitives), where each
 * component's array sits in a row, and the block's size, which it returns. */
int p2LayoutParticleFormat(p2ParticleFormat *format) {
    int primitive;
    int vertexFormat;
    int width;

    primitive = p2CurrentPrimitive;
    vertexFormat = p2VertexFormat;
    p2VertexFormat = P2_FORMAT_RECORDING;
    p2VertexFormat |= format->colourCount ? (int)P2_FORMAT_COLOURS : 0;
    p2VertexFormat |= format->texCoordCount ? (int)P2_FORMAT_TEXCOORDS : 0;
    p2CurrentPrimitive = format->primitive;
    format->attributeKind = 0;
    if (format->sizeCount1 || format->sizeCount0) {
        if (format->sizeCount1) {
            p2VertexFormat |= P2_FORMAT_SPRITE_SIZE_MODE1;
            format->attributeKind = 2;
        } else {
            p2VertexFormat |= P2_FORMAT_SPRITE_SIZE_MODE0;
            format->attributeKind = 1;
        }
    }
    if (format->byteCount) {
        p2VertexFormat |= P2_FORMAT_SPRITE_BYTES;
        format->attributeKind = 3;
    }
    if (format->wordCount) {
        p2VertexFormat |= P2_FORMAT_SPRITE_WORDS;
        format->attributeKind = 4;
    }
    p2DisplayListMode = 1;
    p2LayoutVuBuffers();
    p2DisplayListMode = 0;
    format->verticesPerPrimitive = 2;
    if (format->positionCount == 3 || format->colourCount == 3 || format->byteCount == 3 ||
        format->sizeCount0 == 3 || format->sizeCount1 == 3) {
        format->verticesPerPrimitive = 3;
    }
    format->vertexFormat = P2_FORMAT_RECORDING;
    format->keysPerRow = p2VuBuffers.batchVertexLimit / format->verticesPerPrimitive;
    if (format->byteCount) {
        format->keysPerRow = p2VuBuffers.batchVertexLimit;
    }
    switch (format->primitive) {
    case 1:
        if (format->keysPerRow % 2) {
            format->keysPerRow -= (short)(format->keysPerRow % 2);
        }
        break;
    case 3:
        if (format->keysPerRow % 3) {
            format->keysPerRow -= (short)(format->keysPerRow % 3);
        }
        break;
    case 0:
    case 2:
    case 4:
    case 5:
    case 6:
        break;
    }
    format->headerBytes = 12;
    format->tagBytes = 4;
    format->trailerBytes = 20;
    format->rowStride = 0;
    if (format->positionCount) {
        format->rowStride += format->tagBytes;
        format->positionOffset = format->rowStride;
        format->rowStride += (short)(format->keysPerRow * (format->positionCount * 12));
    }
    if (format->colourCount) {
        format->rowStride += format->tagBytes;
        format->colourOffset = format->rowStride;
        format->rowStride += (short)(format->keysPerRow * (format->colourCount * 16));
        format->vertexFormat |= P2_FORMAT_COLOURS;
    }
    if (format->attributeKind) {
        width = format->sizeCount0 > format->sizeCount1 ? format->sizeCount0 : format->sizeCount1;
        width = (unsigned char)width > format->byteCount ? width : format->byteCount;
        width = width > format->wordCount ? width : format->wordCount;
        format->rowStride += format->tagBytes;
        format->attributeOffset = format->rowStride;
        if (p2VertexFormat & P2_FORMAT_SPRITE_SIZE_MODE0) {
            format->vertexFormat |= P2_FORMAT_SPRITE_SIZE_MODE0;
        } else if (p2VertexFormat & P2_FORMAT_SPRITE_SIZE_MODE1) {
            format->vertexFormat |= P2_FORMAT_SPRITE_SIZE_MODE1;
        }
        if (format->byteCount) {
            format->vertexFormat |= P2_FORMAT_SPRITE_BYTES;
        }
        if (format->wordCount) {
            format->vertexFormat |= P2_FORMAT_SPRITE_WORDS;
        }
        format->rowStride += (short)(format->keysPerRow * (format->attributeKind * (width * 4)));
    }
    if (format->texCoordCount) {
        format->rowStride += format->tagBytes;
        format->texCoordOffset = format->rowStride;
        format->rowStride += (short)(format->keysPerRow * 8);
        format->vertexFormat |= P2_FORMAT_TEXCOORDS;
    }
    format->endOffset = format->rowStride;
    format->rowStride += format->trailerBytes;
    format->rowCount = (format->count + (format->keysPerRow - 1)) / format->keysPerRow;
    format->vuAddress0 = p2VuBuffers.address0;
    format->vuAddress2 = p2VuBuffers.address2;
    format->vuAddress1 = p2VuBuffers.address1;
    format->vuAddress3 = p2VuBuffers.address3;
    format->size = format->headerBytes + format->rowCount * format->rowStride;
    format->size = (format->size + 15) & ~15;
    p2VertexFormat = vertexFormat;
    p2CurrentPrimitive = primitive;
    p2DirtyFlags |= P2_DIRTY_VU_BUFFERS;
    return format->size;
}

/* A VIF code, written to the packet as one word. */
typedef union p2VifCode {
    struct {
        unsigned short immediate;
        unsigned char num;
        unsigned char command;
    } field;
    unsigned int word;
} p2VifCode;

extern unsigned int DAT_004913a8, DAT_004913ac;
extern p2VifCode DAT_00491388, DAT_00491390, DAT_00491398, DAT_004913a0;
extern unsigned int DAT_004913c0, DAT_004913c4;
extern p2VifCode DAT_004913c8;
extern int DAT_0056b458;
extern unsigned int DAT_0056b068;
unsigned short p2GetVuProgramAddress(int);

