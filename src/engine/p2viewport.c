#include "dw4/p2core.h"
#include "dw4/p2dma.h"
#include "dw4/dmaChannel.h"
#include "dw4/p2viewport.h"

/* The viewport: the rectangle and depth range the VU1 programs map clip space to. p2SetViewport
 * keeps it and derives the VU1 scale and offset constants that p2UploadViewport sends. */

typedef struct p2ViewportRect {
    float x;
    float y;
    float width;
    float height;
    float nearZ;
    float farZ;
} p2ViewportRect;

typedef union p2DmaTag {
    unsigned short qwc;
    unsigned int word[4];
} p2DmaTag;

typedef union p2VifCode {
    unsigned short immediate;
    unsigned int word;
} p2VifCode;

/* A texture record of the p2 texture file: the size and GS format of a VRAM buffer. */
typedef struct P2Texture {
    char f0[60];
    unsigned short width;
    unsigned short height;
    char f64[2];
    unsigned short format;
} P2Texture;

int FUN_00208200(int texture);

extern int p2ClearPasses;
extern int DAT_00568e30;

extern p2ViewportRect p2Viewport;
extern float p2ViewportScale;
extern int p2DepthBias;
extern float p2ViewportVuScale[4];
extern float p2ViewportVuOffset[4];
extern float DAT_0056c310[2];
extern unsigned int DAT_0056c318;
extern p2DmaTag p2ViewportUploadTag;
extern p2VifCode p2ViewportFlush;
extern p2VifCode p2ViewportUnpack;

void p2SetViewportScale(float scale) {
    p2ViewportScale = scale;
}

/* Re-derives the viewport with the new bias. Drawing fields of an interlaced display keeps the
 * viewport at half height, so it is restored to the frame's size first. */
void p2SetDepthBias(int bias) {
    p2DepthBias = bias;
    if (p2Display.frameMode == 0 && p2Display.interlaced > 0 && p2Display.renderTarget == -1) {
        p2Viewport.y = p2Viewport.y * 2.0f;
        p2Viewport.height = p2Viewport.height * 2.0f;
    }
    p2SetViewport((int)p2Viewport.x, (int)p2Viewport.y, (int)p2Viewport.width, (int)p2Viewport.height,
                  p2Viewport.nearZ, p2Viewport.farZ);
}

void p2UploadViewport(void) {
    unsigned int *p;

    p = (unsigned int *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
    p2ViewportUnpack.immediate = 44;
    p[0] = p2ViewportUploadTag.word[0];
    p[1] = p2ViewportUploadTag.word[1];
    p[2] = p2ViewportUploadTag.word[2];
    p[3] = p2ViewportUploadTag.word[3];
    p[4] = p2ViewportFlush.word;
    p[5] = p2ViewportUnpack.word;
    ((float *)p)[6] = p2ViewportVuScale[0];
    ((float *)p)[7] = p2ViewportVuScale[1];
    ((float *)p)[8] = p2ViewportVuScale[2];
    ((float *)p)[9] = p2ViewportScale;
    ((float *)p)[10] = p2ViewportVuOffset[0] + DAT_0056c310[0];
    if (p2Display.frameMode == 0 && p2Display.frameCount == 2) {
        ((float *)p)[11] = DAT_0056c310[1] + (p2ViewportVuOffset[1] + (p2Display.drawBuffer != 0 ? 0.5f : 0.0f));
    } else {
        ((float *)p)[11] = p2ViewportVuOffset[1] + DAT_0056c310[1];
    }
    ((float *)p)[12] = p2ViewportVuOffset[2];
    p[13] = DAT_0056c318;
    p[14] = DAT_0056c318;
    p[15] = DAT_0056c318;
    p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)(p + 16);
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
}

void p2SetViewport(int x, int y, int width, int height, float nearZ, float farZ) {
    int antialias;
    int depthBits;
    int depthMax;
    float depthRange;
    int bufferHeight;
    float halfWidth;

    antialias = (p2GetDisplayFlags() & P2_DISPLAY_ANTIALIAS) != 0;
    if (p2ClearPasses != 0) {
        x = 286;
        y = 198;
        width = 53;
        height = 37;
    }
    if (p2Display.frameMode == 0 && p2Display.interlaced > 0 && p2Display.renderTarget == -1) {
        y = y / 2;
        height = height / 2;
    }
    depthBits = p2Display.f24 == 32 ? 24 : p2Display.f24;
    depthMax = (1LL << depthBits) - 1;
    depthMax &= ~0xF;
    depthRange = depthMax;
    if (p2Display.renderTarget < 0) {
        bufferHeight = antialias != 0 ? p2Display.antialiasHeight : p2Display.height;
    } else {
        if (DAT_00568e30 > -1) {
            switch (((P2Texture *)DAT_00568e30)->format) {
            case 11:
            case 12:
                depthRange = 0xFFFF;
                break;
            case 9:
            case 10:
            default:
                depthRange = 0xFFFFFF;
                break;
            }
        }
        bufferHeight = FUN_00208200(p2Display.renderTarget);
    }
    p2Viewport.nearZ = nearZ;
    p2Viewport.farZ = farZ;
    ((int *)p2ViewportVuScale)[3] = 0;
    p2Viewport.x = x;
    p2Viewport.y = y;
    p2Viewport.width = width;
    p2Viewport.height = height;
    halfWidth = (float)width / 2.0f;
    p2ViewportVuScale[0] = halfWidth * p2ViewportScale;
    p2ViewportVuScale[1] = ((float)-height / 2.0f) * p2ViewportScale;
    p2ViewportVuScale[2] = depthRange * ((farZ - nearZ) / 2.0f);
    depthMax += p2DepthBias * 2;
    p2ViewportVuOffset[0] = (float)(p2CurrentGsRegisters->xyoffset[0].field.ofx / 16) + ((float)x + halfWidth);
    p2ViewportVuOffset[1] = (float)(p2CurrentGsRegisters->xyoffset[0].field.ofy / 16) +
                      ((float)bufferHeight - ((float)y + (float)height / 2.0f));
    p2ViewportVuOffset[2] = (float)depthMax * ((farZ + nearZ) / 2.0f);
    ((int *)p2ViewportVuOffset)[3] = 0;
    p2UploadViewport();
}
