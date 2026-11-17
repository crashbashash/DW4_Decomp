/* What the VIF1 row and mask registers hold, so a draw writes STROW or STMASK only when its values
 * differ. p2InitVifRegisters loads both at start-up. */
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2dma.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/p2/p2vif.h"

#define VIF1_ERR ((unsigned int *)0x10003c20)

/* VIF1_ERR: mask the DMAtag mismatch error */
enum {
    P2_VIF_ERR_MASK_DMATAG = 0x2
};

/* A VIF code, written to the packet as one word. */
typedef union p2VifCode {
    struct {
        unsigned short immediate;
        unsigned char num;
        unsigned char command;
    } field;
    unsigned int word;
} p2VifCode;

/* A DMA tag with its quadword count in the low half, written to the packet as four words. */
typedef union p2DmaTag {
    unsigned short qwc;
    unsigned int word[4];
} p2DmaTag;

/* One quadword of a VIF packet. */
typedef union p2VifQuad {
    unsigned int word[4];
    float real[4];
} p2VifQuad;

extern float p2VifRowScale;
extern int p2VifMask;
extern p2VifCode p2VifNop;

extern p2DmaTag p2VifInitTag;
extern p2DmaTag p2VifInitRefTag;
extern p2VifCode p2VifInitMark;
extern p2VifCode p2VifInitMpg;
extern p2VifCode p2VifInitStcycl;
extern p2VifCode p2VifInitMskpath3;
extern p2VifCode p2VifInitBase;
extern p2VifCode p2VifInitOffset;
extern p2VifCode p2VifInitUnpack;
extern p2VifCode p2VifInitUnpackVector3;
extern p2VifCode p2VifInitStrow;
extern p2VifCode p2VifInitStmask;
extern p2VifCode p2VifInitUnpackMasked;

/* Puts VIF1 into a known state: the cycle, base and offset registers, the VU1 constants the
 * programs expect, then the row and mask registers. */
void p2InitVifRegisters(void) {
    p2VifQuad *p;
    p2VifQuad *tag;
    p2VifCode unpack;
    p2VifCode unpackVector3;
    p2VifCode mask;

    p = (p2VifQuad *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2VifInitStcycl.field.immediate = 0xFFFF;
    p2VifInitTag.qwc = 1;
    p->word[0] = p2VifInitTag.word[0];
    p->word[1] = p2VifInitTag.word[1];
    p->word[2] = p2VifInitTag.word[2];
    p->word[3] = p2VifInitTag.word[3];
    p++;
    p2VifInitMark.field.immediate = 8;
    p->word[0] = p2VifInitBase.word;
    p->word[1] = p2VifInitOffset.word;
    p->word[2] = p2VifInitMskpath3.word;
    p->word[3] = p2VifInitStcycl.word;
    p++;
    p2SetVifMask(0);

    p2VifInitMpg.field.num = 0;
    p2VifInitRefTag.qwc = 1;
    unpack = p2VifInitUnpack;
    p2VifInitTag.qwc = 2;
    p->word[0] = p2VifInitTag.word[0];
    p->word[1] = p2VifInitTag.word[1];
    p->word[2] = p2VifInitTag.word[2];
    p->word[3] = p2VifInitTag.word[3];
    p++;
    p->word[0] = p2VifNop.word;
    p->word[1] = p2VifNop.word;
    p->word[2] = p2VifNop.word;
    p->word[3] = unpack.word;
    p++;
    p->word[0] = 0x8000;
    p->word[1] = 0;
    p->word[2] = 0;
    p->word[3] = 0;
    p++;

    tag = p++;
    unpackVector3 = p2VifInitUnpackVector3;
    p2VifInitTag.qwc = 1;
    tag->word[0] = p2VifInitTag.word[0];
    tag->word[1] = p2VifInitTag.word[1];
    tag->word[2] = p2VifInitTag.word[2];
    tag->word[3] = p2VifInitTag.word[3];
    p->word[0] = unpackVector3.word;
    p->real[1] = 0.2f;
    p->word[2] = 0;
    p->word[3] = 1;
    p++;

    /* the row register supplies w; the rows are 1 */
    tag = p++;
    p2VifInitTag.qwc = 2;
    *(unsigned int *)&mask = 0x40404040; /* matching construct: hand search — the mask kept in its stack slot */
    tag->word[0] = p2VifInitTag.word[0];
    tag->word[1] = p2VifInitTag.word[1];
    tag->word[2] = p2VifInitTag.word[2];
    tag->word[3] = p2VifInitTag.word[3];
    p->word[0] = p2VifInitStmask.word;
    p->word[1] = mask.word;
    p->word[2] = p2VifNop.word;
    p->word[3] = p2VifInitStrow.word;
    p++;
    p->real[0] = 1.0f;
    p->real[1] = 1.0f;
    p->real[2] = 1.0f;
    p->real[3] = 1.0f;
    p++;
    p2SetVifRowScale(1.0f);

    /* only x is written */
    p->word[0] = p2VifInitTag.word[0];
    p->word[1] = p2VifInitTag.word[1];
    p->word[2] = p2VifInitTag.word[2];
    p->word[3] = p2VifInitTag.word[3];
    p++;
    p->word[0] = p2VifNop.word;
    p->word[1] = p2VifInitStmask.word;
    p->word[2] = 0xFCFCFCFC;
    p->word[3] = p2VifInitUnpackMasked.word;
    p++;
    p->word[0] = 0x8000;
    p->word[1] = 0;
    p->word[2] = 0;
    p->word[3] = 0;
    p++;
    *VIF1_ERR = P2_VIF_ERR_MASK_DMATAG;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)p;
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
}

void p2SetVifRowScale(float scale) {
    p2VifRowScale = scale;
}

float p2GetVifRowScale(void) {
    return p2VifRowScale;
}

void p2SetVifMask(int mask) {
    p2VifMask = mask;
}

int p2GetVifMask(void) {
    return p2VifMask;
}
