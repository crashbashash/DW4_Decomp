/* Multipass texturing. With the multipass capability on, each texture stage beyond the first is
 * drawn as a pass of its own in GS context 2, so the GS register sets of the stages and the stage
 * capabilities are read per pass. p2SetPassCount sets how many passes there are. */
#include "dw4/p2core.h"

/* The capability bits of a stage's p2ProgramFlags entry used here. */
enum {
    P2_CAP_TEXTURE = 1,
    P2_CAP_TEXTURE_COMBINE = 10,
    P2_CAP_MULTIPASS = 23
};

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
