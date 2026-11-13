/* p2draw.c - the p2 renderer's vertex-array draws.
 *
 * The visual context binds its vertex arrays here, then asks for a primitive. A draw brings the
 * GS primitive and the vertex format up to date, then hands the vertices to the submit function
 * in batches no longer than one packet holds; strips and fans repeat their shared vertices at
 * each batch boundary. While a display list is recorded the format follows the bound arrays and
 * every draw goes through the recording submit. */

enum p2Primitive {
    P2_PRIM_POINT,
    P2_PRIM_LINE,
    P2_PRIM_LINE_STRIP,
    P2_PRIM_TRIANGLE,
    P2_PRIM_TRIANGLE_STRIP,
    P2_PRIM_TRIANGLE_FAN,
    P2_PRIM_SPRITE,
    P2_PRIM_TRIANGLE_STRIPS /* a list of triangle strips */
};

#include "dw4/p2dma.h"
#include "dw4/p2core.h"

/* Bits of a program's p2ProgramFlags entry, as shifts. */
enum p2ProgramFlagBit {
    P2_PROGRAM_ARRAY_FORMAT = 22, /* the format follows the bound arrays outside recording too */
    P2_PROGRAM_FIXED_POINT = 27   /* the components are fixed point: upload their scales */
};

enum {
    P2_VIF_UNPACK_UNSIGNED = 0x4000,
    P2_VIF_UNPACK_RELATIVE = 0x8000,
    P2_VIF_UNPACK_RELATIVE_UNSIGNED = 0xC000,
    P2_VIF_MODE_NORMAL = 0,
    P2_VIF_MODE_OFFSET = 1, /* the row registers are added to what is unpacked */
    P2_VIF_UNPACK_V1_32 = 0x60, /* add 4 per further component */
    P2_VIF_UNPACK_16BIT = 1,
    P2_VIF_UNPACK_8BIT = 2,
    P2_PIPELINE_VERTEX_ARRAYS = 0,
    P2_RENDER_STATE_ALL = 0x1FF
};

/* A write position in a VIF packet, also read as an address to test its alignment. */
typedef union p2VifCursor {
    unsigned char *byte;
    unsigned short *half;
    unsigned int *word;
    unsigned int address;
} p2VifCursor;

/* A VIF code, written to the packet as one word. */
typedef union p2VifCode {
    struct {
        unsigned short immediate;
        unsigned char num;
        unsigned char command;
    } field;
    struct {
        unsigned int immediate : 16;
        unsigned int num : 8;
        unsigned int command : 7;
        unsigned int interrupt : 1;
    } bits;
    unsigned int word;
} p2VifCode;

/* A DMA tag with its quadword count in the low half, written to the packet as four words. */
typedef union p2DmaTag {
    unsigned short qwc;
    unsigned int word[4];
} p2DmaTag;

/* What announces one strip of a batch of triangle strips to the vertex program: an UNPACK of
 * one vector to the strip's slot, and the first three words of its GIF tag, vertex count first. */
typedef struct p2StripHeader {
    p2VifCode unpack;
    unsigned int gifTag[3];
} p2StripHeader;

enum {
    P2_STRIPS_PER_BATCH = 16,
    P2_STRIP_PACKET_MARGIN = 0x110 /* room a batch of strip headers needs in the packet */
};

typedef void (*p2VertexSubmit)(unsigned int count, int first);

int p2UploadComponentScales(void);
int FUN_001fffb0(void);
int FUN_00200980(void);
int p2LayoutVuBuffers(void);
int FUN_001ff3b0(int);
int p2SendRenderState(int);
void p2SetVifRowScale(float);
float p2GetVifRowScale(void);
int p2GetComponentFixedScale(int component, int *scale);
int p2GetComponentSize(int component);
int p2GetVifMask(void);
void p2SetVifMask(int mask);
void p2SubmitDmaPacket(int channel);
void p2GrowDisplayList(void);

void p2SubmitVertices(unsigned int count, int first, unsigned short *indices);
/* Declared without a prototype: the recording submit passes it no index list. */
void p2SubmitIndexedVertices();
void p2SubmitRecordedVertices(unsigned int count, int first);

extern int p2RenderStateDirty;
extern p2VuBufferLayout p2VuBuffers;
extern int p2CurrentPrimitive;
extern unsigned int p2ProgramFlags[];
extern int p2CurrentProgram;
extern int p2DisplayListMode;
extern int p2SpriteSizeMode;
extern int p2StatMask;
extern unsigned int p2VifRowCommand;
extern unsigned int p2AlignNop;
extern p2VifCode p2UnpackByteTriplesCode;
extern p2DmaTag p2UnpackByteTriplesTag;
extern const unsigned int p2UnpackByteTriplesNop;
extern p2VifCode p2UnpackBytePairsCode;
extern p2DmaTag p2UnpackBytePairsTag;
extern const unsigned int p2UnpackBytePairsNop;
extern p2VifCode p2UnpackBytesCode;
extern p2DmaTag p2UnpackBytesTag;
extern const unsigned int p2UnpackBytesNop;
extern p2DmaTag p2UnpackElementsTag;
extern char p2StripHeaderReset;
extern int p2BatchStripCount;
extern p2DmaTag p2StripTag;
extern p2VifCode p2StripUnpackCode;
extern unsigned int p2StripGifTag[4];
extern p2StripHeader p2NextStripHeader;
extern p2DmaPacket *p2DmaCurrentPacket[P2_DMA_CHANNEL_COUNT];
extern p2VifCode p2VifModeCode;
extern p2DmaTag p2ComponentUnpackTag;

extern int p2VertexFormat;
extern int p2DrawPipeline;
extern p2VertexSubmit p2VertexSubmitter;
extern int p2ConstantColour;
extern unsigned long long p2IndexedVertexCount;
extern unsigned long long p2VertexCount;
extern unsigned long long p2PrimitiveCount;
extern unsigned long long p2StatVertexCount1;
extern unsigned long long p2StatVertexCount4;
extern unsigned long long p2StatVertexCount2;
extern unsigned long long p2StatVertexCount8;
extern unsigned long long p2StatVertexCount16;
extern unsigned long long p2ColourModeChanges;
extern unsigned long long p2PrimitiveChanges;
extern const float *p2PositionArray;
extern const float *p2NormalArray;
extern const float *p2TexCoordArrays[16];
extern const unsigned int *p2ColourArray;
extern const unsigned char *p2SpriteBytes;

/* The three unpack writers append a DMA tag and a VIF UNPACK of count byte vectors read from
 * element first of data, padded to a quadword; the tag is written last, once the length is known. */
void p2UnpackByteTriples(unsigned int count, const char *data, int first, p2VifCursor *cursor) {
    const char *src = data + first * 3;
    unsigned int i;
    unsigned int *tag = cursor->word;
    unsigned int *p;

    cursor->word = tag + 4;
    p2UnpackByteTriplesCode.field.num = count;
    p2UnpackByteTriplesCode.field.immediate = p2VuBuffers.byteUnpackAddress | P2_VIF_UNPACK_RELATIVE_UNSIGNED;
    p = cursor->word;
    cursor->word = p + 1;
    *p = p2UnpackByteTriplesCode.word;
    for (i = 0; i < count; i++) {
        *cursor->byte++ = *src++;
        *cursor->byte++ = *src++;
        *cursor->byte++ = *src++;
    }
    while (cursor->address & 3) {
        *cursor->byte++ = 0;
    }
    while (cursor->address & 0xF) {
        p = cursor->word;
        cursor->word = p + 1;
        *p = p2UnpackByteTriplesNop;
    }
    p2UnpackByteTriplesTag.qwc = (int)(cursor->address - (unsigned int)tag) / 16 - 1;
    tag[0] = p2UnpackByteTriplesTag.word[0];
    tag[1] = p2UnpackByteTriplesTag.word[1];
    tag[2] = p2UnpackByteTriplesTag.word[2];
    tag[3] = p2UnpackByteTriplesTag.word[3];
}

void p2UnpackBytePairs(unsigned int count, const short *data, int first, p2VifCursor *cursor) {
    const short *src = data + first;
    unsigned int i;
    unsigned int *tag = cursor->word;
    unsigned int *p;

    cursor->word = tag + 4;
    p2UnpackBytePairsCode.field.num = count;
    p2UnpackBytePairsCode.field.immediate = p2VuBuffers.byteUnpackAddress | P2_VIF_UNPACK_RELATIVE_UNSIGNED;
    p = cursor->word;
    cursor->word = p + 1;
    *p = p2UnpackBytePairsCode.word;
    for (i = 0; i < count; i++) {
        *cursor->half++ = *src++;
    }
    while (cursor->address & 3) {
        *cursor->byte++ = 0;
    }
    while (cursor->address & 0xF) {
        p = cursor->word;
        cursor->word = p + 1;
        *p = p2UnpackBytePairsNop;
    }
    p2UnpackBytePairsTag.qwc = (int)(cursor->address - (unsigned int)tag) / 16 - 1;
    tag[0] = p2UnpackBytePairsTag.word[0];
    tag[1] = p2UnpackBytePairsTag.word[1];
    tag[2] = p2UnpackBytePairsTag.word[2];
    tag[3] = p2UnpackBytePairsTag.word[3];
}

void p2UnpackBytes(unsigned int count, const char *data, int first, p2VifCursor *cursor) {
    const char *src = data + first;
    unsigned int i;
    unsigned int *tag = cursor->word;
    unsigned int *p;

    cursor->word = tag + 4;
    p2UnpackBytesCode.field.num = count;
    p2UnpackBytesCode.field.immediate = p2VuBuffers.byteUnpackAddress | P2_VIF_UNPACK_RELATIVE_UNSIGNED;
    p = cursor->word;
    cursor->word = p + 1;
    *p = p2UnpackBytesCode.word;
    for (i = 0; i < count; i++) {
        *cursor->byte++ = *src++;
    }
    while (cursor->address & 3) {
        *cursor->byte++ = 0;
    }
    while (cursor->address & 0xF) {
        p = cursor->word;
        cursor->word = p + 1;
        *p = p2UnpackBytesNop;
    }
    p2UnpackBytesTag.qwc = (int)(cursor->address - (unsigned int)tag) / 16 - 1;
    tag[0] = p2UnpackBytesTag.word[0];
    tag[1] = p2UnpackBytesTag.word[1];
    tag[2] = p2UnpackBytesTag.word[2];
    tag[3] = p2UnpackBytesTag.word[3];
}

void p2SetTexCoordArray(int unit, const float *texCoords) {
    p2TexCoordArrays[unit] = texCoords;
}

void p2SetSpriteByteArray(const unsigned char *bytes) {
    p2SpriteBytes = bytes;
}

void p2SetVertexArrays(const float *positions, const float *normals, const unsigned int *colours,
                       const float *texCoords) {
    p2PositionArray = positions;
    p2NormalArray = normals;
    p2TexCoordArrays[0] = texCoords;
    p2ColourArray = colours;
}

/* Selects the primitive, the colour mode, the vertex format and the submit function. */
static inline void p2BeginDraw(int primitive, int sprites) {
    unsigned int programFlags = p2ProgramFlags[p2CurrentProgram];
    int fixedPoint = (programFlags >> P2_PROGRAM_FIXED_POINT) & 1;
    const unsigned int *colours;
    int constantColour;
    int bit;

    if (p2CurrentPrimitive != primitive) {
        p2CurrentPrimitive = primitive;
        p2RenderStateDirty |= 9;
        p2PrimitiveChanges += 1;
    }
    colours = p2ColourArray;
    constantColour = colours == 0;
    if ((p2ConstantColour ^ constantColour) != 0) {
        p2ConstantColour = constantColour;
        p2RenderStateDirty |= 0x11;
        p2ColourModeChanges += 1;
    }
    if (p2VertexFormat & P2_FORMAT_RECORDING) {
        p2VertexFormat &= ~P2_FORMAT_ARRAY_BITS;
        if (colours != 0) {
            bit = P2_FORMAT_COLOURS;
        } else {
            bit = 0;
        }
        p2VertexFormat |= bit;
        if (p2TexCoordArrays[0] != 0) {
            bit = P2_FORMAT_TEXCOORDS;
        } else {
            bit = 0;
        }
        p2VertexFormat |= bit;
        if (sprites) {
            if (p2SpriteBytes != 0) {
                bit = P2_FORMAT_SPRITE_BYTES;
            } else {
                bit = 0;
            }
            p2VertexFormat |= bit;
            if (p2NormalArray != 0) {
                switch (p2SpriteSizeMode) {
                case 0:
                    p2VertexFormat |= P2_FORMAT_SPRITE_SIZE_MODE0;
                    break;
                case 1:
                    p2VertexFormat |= P2_FORMAT_SPRITE_SIZE_MODE1;
                    break;
                }
            }
        } else if (p2NormalArray != 0) {
            p2VertexFormat |= P2_FORMAT_NORMALS;
        }
        FUN_001fffb0();
        FUN_00200980();
        p2LayoutVuBuffers();
        p2VertexSubmitter = p2SubmitRecordedVertices;
    } else {
        if ((programFlags >> P2_PROGRAM_ARRAY_FORMAT) & 1) {
            p2VertexFormat &= ~P2_FORMAT_ARRAY_BITS;
            if (colours != 0) {
                bit = P2_FORMAT_COLOURS;
            } else {
                bit = 0;
            }
            p2VertexFormat |= bit;
            if (p2NormalArray != 0) {
                bit = P2_FORMAT_NORMALS;
            } else {
                bit = 0;
            }
            p2VertexFormat |= bit;
            if (p2TexCoordArrays[0] != 0) {
                bit = P2_FORMAT_TEXCOORDS;
            } else {
                bit = 0;
            }
            p2VertexFormat |= bit;
        }
        p2DrawPipeline = P2_PIPELINE_VERTEX_ARRAYS;
        p2VertexSubmitter = (p2VertexSubmit)p2SubmitVertices;
        if (p2RenderStateDirty != 0) {
            FUN_001ff3b0(P2_RENDER_STATE_ALL);
            p2SendRenderState(P2_RENDER_STATE_ALL);
        }
    }
    if (fixedPoint) {
        p2UploadComponentScales();
    }
}

/* Hands the current VIF1 packet over when less than room is left in it; while a display list is
 * recorded the list grows a block instead. */
static inline void p2EndVif1Write(unsigned int room) {
    if (p2DmaCurrentPacket[P2_DMA_VIF1]->cursor + room >= p2DmaCurrentPacket[P2_DMA_VIF1]->limit) {
        if (p2DisplayListMode != 0) {
            p2GrowDisplayList();
        } else {
            p2SubmitDmaPacket(P2_DMA_VIF1);
        }
    }
}

/* Adds a batch to the vertex counters p2StatMask selects. */
static inline void p2CountStatVertices(unsigned long long count) {
    int stats = p2StatMask;

    if (stats & 1) {
        p2StatVertexCount1 += count;
    }
    if (stats & 2) {
        p2StatVertexCount2 += count;
    }
    if (stats & 4) {
        p2StatVertexCount4 += count;
    }
    if (stats & 8) {
        p2StatVertexCount8 += count;
    }
    if (stats & 0x10) {
        p2StatVertexCount16 += count;
    }
}

void p2DrawPoints(unsigned int count) {
    int first;
    unsigned int limit;
    unsigned int batch;

    p2BeginDraw(P2_PRIM_POINT, 0);
    p2VertexCount += count;
    p2CountStatVertices(count);
    first = 0;
    limit = p2VuBuffers.batchVertexLimit;
    while (count != 0) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2VertexSubmitter(batch, first);
        first += batch;
        count -= batch;
    }
}

void p2DrawLines(unsigned int count) {
    int first;
    unsigned int batch;
    unsigned int limit;

    p2BeginDraw(P2_PRIM_LINE, 0);
    p2VertexCount += count;
    p2CountStatVertices(count);
    first = 0;
    limit = p2VuBuffers.batchVertexLimit & ~1;
    while (count != 0) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2VertexSubmitter(batch, first);
        first += batch;
        count -= batch;
    }
}

void p2DrawLineStrip(unsigned int count) {
    int first;
    unsigned int batch;
    unsigned int limit;

    p2BeginDraw(P2_PRIM_LINE_STRIP, 0);
    first = 0;
    limit = p2VuBuffers.batchVertexLimit & ~1;
    while (count >= 2) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2VertexSubmitter(batch, first);
        first += batch - 1;
        p2VertexCount += batch;
        p2CountStatVertices(batch);
        count -= batch - 1;
    }
}

void p2DrawTriangles(unsigned int count) {
    unsigned int batch;
    unsigned int limit;
    int first;

    p2BeginDraw(P2_PRIM_TRIANGLE, 0);
    p2VertexCount += count;
    p2PrimitiveCount += count / 3;
    p2CountStatVertices(count);
    first = 0;
    limit = (p2VuBuffers.batchVertexLimit / 3U) * 3;
    while (count != 0) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2VertexSubmitter(batch, first);
        first += batch;
        count -= batch;
    }
}

void p2DrawTriangleStrip(unsigned int count) {
    int first;
    unsigned int limit;
    unsigned int batch;

    p2BeginDraw(P2_PRIM_TRIANGLE_STRIP, 0);
    limit = p2VuBuffers.batchVertexLimit;
    first = 0;
    while (count >= 3) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2VertexSubmitter(batch, first);
        first += batch - 2;
        p2VertexCount += batch;
        p2PrimitiveCount += batch - 2;
        p2CountStatVertices(batch);
        count -= batch - 2;
    }
}

void p2DrawTriangleFan(unsigned int count) {
    unsigned int batch;

    p2BeginDraw(P2_PRIM_TRIANGLE_FAN, 0);
    batch = p2VuBuffers.batchVertexLimit;
    batch = batch < count ? batch : count;
    p2VertexSubmitter(batch, 0);
    p2VertexCount += batch;
    p2PrimitiveCount += batch - 2;
    p2CountStatVertices(batch);
}

/* Draws a list of triangle strips, as many as fit one batch at a time. The strips of a batch are
 * announced to the vertex program by a header each: an UNPACK to the next header slot and the start of
 * the strip's GIF tag. A strip that does not fit is split at an even length with its last two vertices
 * drawn again in the next batch; a split shorter than a triangle waits for the next batch. */
void p2DrawTriangleStrips(int count, const int *lengths) {
    int first = 0;
    int done = 0;
    int total; /* matching construct: declaration-order sweep — this order gives retail's registers */
    int limit;
    int length;
    int i;
    int strips;
    p2DmaTag *tag;
    p2StripHeader *header;
    p2StripHeader *strip;
    int batch[P2_STRIPS_PER_BATCH];

    if (p2StripHeaderReset) {
        p2StripHeaderReset = 0;
        p2NextStripHeader.unpack.word = p2StripUnpackCode.word;
        p2NextStripHeader.gifTag[0] = p2StripGifTag[0];
        p2NextStripHeader.gifTag[1] = p2StripGifTag[1];
        p2NextStripHeader.gifTag[2] = p2StripGifTag[2];
    }
    p2BeginDraw(P2_PRIM_TRIANGLE_STRIPS, 0);
    limit = p2VuBuffers.batchVertexLimit;
    p2EndVif1Write(P2_STRIP_PACKET_MARGIN);
    total = 0;
    strips = 0;
    while (count != 0) {
        length = *lengths - done;
        if (total + length <= limit) {
            total += length;
            batch[strips++] = length;
            lengths++;
            count--;
            done = 0;
        } else {
            batch[strips] = limit - total;
            total = limit;
            if (batch[strips] & 1) {
                batch[strips] -= 1;
                total = limit - 1;
                if (batch[strips] > 2) {
                    done += batch[strips++] - 2;
                } else {
                    done = 0;
                    total = limit - 3;
                }
            } else {
                done += batch[strips++] - 2;
            }
        }
        if (total >= limit - 3 || strips >= P2_STRIPS_PER_BATCH || count == 0) {
            header = (p2StripHeader *)p2DmaCurrentPacket[P2_DMA_VIF1]->cursor;
            p2StripTag.qwc = strips;
            p2BatchStripCount = strips;
            tag = (p2DmaTag *)header++;
            tag->word[0] = p2StripTag.word[0];
            tag->word[1] = p2StripTag.word[1];
            tag->word[2] = p2StripTag.word[2];
            tag->word[3] = p2StripTag.word[3];
            p2NextStripHeader.unpack.word = p2StripUnpackCode.word;
            for (i = 0; i < strips; i++) {
                p2NextStripHeader.gifTag[0] = batch[i];
                strip = header++;
                strip->unpack.word = p2NextStripHeader.unpack.word;
                strip->gifTag[0] = p2NextStripHeader.gifTag[0];
                strip->gifTag[1] = p2NextStripHeader.gifTag[1];
                strip->gifTag[2] = p2NextStripHeader.gifTag[2];
                p2NextStripHeader.unpack.field.immediate++;
                p2PrimitiveCount += batch[i] - 2;
            }
            p2DmaCurrentPacket[P2_DMA_VIF1]->cursor = (unsigned int)header;
            p2VertexSubmitter(total, first);
            p2VertexCount += total;
            p2CountStatVertices(total);
            first += total;
            p2EndVif1Write(P2_STRIP_PACKET_MARGIN);
            total = 0;
            strips = 0;
            if (done != 0) {
                first -= 2;
            }
        }
    }
    p2BatchStripCount = 1;
}

void p2DrawIndexedTriangleStrip(unsigned int count, unsigned short *indices) {
    int limit;
    unsigned int batch;

    p2BeginDraw(P2_PRIM_TRIANGLE_STRIP, 0);
    limit = p2VuBuffers.batchVertexLimit;
    while (count >= 3) {
        batch = (unsigned int)limit < count ? limit : count;
        p2SubmitIndexedVertices(batch, 0, indices);
        p2VertexCount += batch;
        p2IndexedVertexCount += batch;
        p2PrimitiveCount += batch - 2;
        p2CountStatVertices(batch);
        indices += batch - 2;
        count -= batch - 2;
    }
}

void p2DrawIndexedTriangles(unsigned int count, unsigned short *indices) {
    unsigned int batch;
    unsigned int limit;

    p2BeginDraw(P2_PRIM_TRIANGLE, 0);
    p2VertexCount += count;
    p2IndexedVertexCount += count;
    p2PrimitiveCount += count / 3;
    p2CountStatVertices(count);
    limit = ((unsigned int)p2VuBuffers.batchVertexLimit / 3U) * 3;
    while (count >= 3) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2SubmitIndexedVertices(batch, 0, indices);
        count -= batch;
        indices += batch;
    }
}

void p2DrawIndexedTriangleFan(unsigned int count, unsigned short *indices) {
    unsigned int batch;

    p2BeginDraw(P2_PRIM_TRIANGLE_FAN, 0);
    batch = p2VuBuffers.batchVertexLimit;
    batch = batch < count ? batch : count;
    p2SubmitIndexedVertices(batch, 0, indices);
    p2VertexCount += batch;
    p2IndexedVertexCount += batch;
    p2PrimitiveCount += batch - 2;
    p2CountStatVertices(batch);
}

void p2DrawSprites(unsigned int count) {
    int first;
    unsigned int limit;
    unsigned int batch;

    p2BeginDraw(P2_PRIM_SPRITE, 1);
    p2VertexCount += count;
    p2CountStatVertices(count);
    limit = p2VuBuffers.batchVertexLimit;
    first = 0;
    while (count != 0) {
        batch = count;
        if (limit < count) {
            batch = limit;
        }
        p2VertexSubmitter(batch, first);
        first += batch;
        count -= batch;
    }
}

void p2DrawIndexedSprites(unsigned int count, unsigned short *indices) {
    int limit;
    unsigned int batch;

    p2BeginDraw(P2_PRIM_SPRITE, 1);
    p2VertexCount += count;
    p2IndexedVertexCount += count;
    p2CountStatVertices(count);
    limit = p2VuBuffers.batchVertexLimit;
    while (count != 0) {
        batch = (unsigned int)limit < count ? limit : count;
        p2SubmitIndexedVertices(batch, 0, indices);
        count -= batch;
    }
}

void p2SubmitRecordedVertices(unsigned int count, int first) {
    if (p2DisplayListMode == 1) {
        p2SubmitIndexedVertices(count, first);
    } else {
        p2SubmitVertices(count, first, 0);
    }
}

/* Pads the packet to a quadword boundary with VIF no-ops. */
void p2AlignVifPacket(p2VifCursor *cursor) {
    unsigned int *p;

    while (cursor->address & 0xF) {
        p = cursor->word;
        cursor->word = p + 1;
        *p = p2AlignNop;
    }
}

/* Appends a VIF UNPACK of count elements of size bytes each, read in order from data or, with an
 * index list, from the indexed elements, padded to a word. With withTag it opens a DMA tag first
 * and closes it once the packet is aligned, dropping the tag again when it holds nothing. */
void p2UnpackElements(unsigned int count, const short *indices, const char *data, int address,
                      p2VifCursor *cursor, unsigned int size, p2VifCode code, char offsetMode, int withTag) {
    p2DmaTag *tag = (p2DmaTag *)cursor->word;
    unsigned int i; /* matching construct: declaration-order sweep — i before src gives retail's registers */
    const char *src = data;
    unsigned int j;
    unsigned int *p;

    if (withTag) {
        cursor->word = tag->word + 4;
        tag->word[0] = p2UnpackElementsTag.word[0];
        tag->word[1] = p2UnpackElementsTag.word[1];
        tag->word[2] = p2UnpackElementsTag.word[2];
        tag->word[3] = p2UnpackElementsTag.word[3];
    }
    code.field.num = count;
    code.field.immediate = address | P2_VIF_UNPACK_RELATIVE | (offsetMode ? P2_VIF_UNPACK_UNSIGNED : 0);
    p = cursor->word;
    cursor->word = p + 1;
    *p = code.word;
    for (i = 0; i < count; i++) {
        if (indices != 0) {
            src = data + size * indices[i];
        }
        for (j = 0; j < size; j++) {
            *cursor->byte++ = *src++;
        }
    }
    while (cursor->address & 3) {
        *cursor->byte++ = 0;
    }
    if (withTag) {
        p2AlignVifPacket(cursor);
        tag->qwc = (int)(cursor->address - (unsigned int)tag) / 16 - 1;
        if (tag->qwc == 0) {
            cursor->word -= 4;
        }
    }
}

/* Loads the VIF row registers when the value or the scale differs from what they hold. */
void p2WriteVifRow(p2VifCursor *cursor, unsigned int value, float scale) {
    unsigned int *p;

    if (value != 0 || scale != p2GetVifRowScale()) {
        p = cursor->word;
        cursor->word = p + 1;
        *p = p2VifRowCommand;
        p = cursor->word;
        cursor->word = p + 1;
        *p = value;
        p = cursor->word;
        cursor->word = p + 1;
        *p = value;
        p = cursor->word;
        cursor->word = p + 1;
        *p = value;
        if (scale == 1.0f) {
            p = cursor->word;
            cursor->word = p + 1;
            *(float *)p = 1.0f;
        } else {
            p = cursor->word;
            cursor->word = p + 1;
            *p = value;
        }
        p2SetVifRowScale(scale);
    }
}

/* Writes a VIF STMOD when the mode differs from the one VIF1 is in. */
static inline void p2SetVifMode(p2VifCursor *cursor, int mode) {
    unsigned int *p;

    if (p2GetVifMask() ^ mode) {
        p2SetVifMask(mode);
        p2VifModeCode.field.immediate = mode;
        p = cursor->word;
        cursor->word = p + 1;
        *p = p2VifModeCode.word;
    }
}

/* Picks the unpack command of a vertex component and the VIF mode for it. Fixed-point data of a
 * component with a fixed scale is unpacked from bytes, or from halfwords when the component has
 * fewer of them than the count, with the scale loaded into the row registers and added in offset
 * mode; other data is unpacked as it is. */
static inline void p2SelectComponentUnpack(int fixedPoint, int component, const char **elements,
                                           const char *data, p2VifCode *code, int command,
                                           char *offsetMode, p2VifCursor *cursor, int first, int count) {
    int scale;

    if (fixedPoint && p2GetComponentFixedScale(component, &scale)) {
        if (count == p2GetComponentSize(component)) {
            code->bits.command = command + P2_VIF_UNPACK_8BIT;
            *elements = data + first * count;
        } else {
            code->bits.command = command + P2_VIF_UNPACK_16BIT;
            *elements = data + first * count * 2;
        }
        /* matching construct: manual variant — the row value is read through its address */
        p2WriteVifRow(cursor, *(unsigned int *)&scale, count == 4 ? 0.0f : 1.0f);
        p2SetVifMode(cursor, P2_VIF_MODE_OFFSET);
        *offsetMode = 1;
    } else {
        *offsetMode = 0;
        code->bits.command = command;
        p2SetVifMode(cursor, P2_VIF_MODE_NORMAL);
    }
}

/* Sets up the unpack of a vertex component, by default as count words; with withTag inside a DMA
 * tag of its own, dropped again when it holds nothing. */
void p2BeginComponentUnpack(int fixedPoint, int component, const char **elements, const char *data,
                            p2VifCode *code, int command, char *offsetMode, p2VifCursor *cursor,
                            int first, int count, int withTag) {
    p2DmaTag *tag;

    if (command == 0) {
        command = P2_VIF_UNPACK_V1_32 + (count - 1) * 4;
    }
    if (withTag) {
        tag = (p2DmaTag *)cursor->word;
        cursor->word = tag->word + 4;
        tag->word[0] = p2ComponentUnpackTag.word[0];
        tag->word[1] = p2ComponentUnpackTag.word[1];
        tag->word[2] = p2ComponentUnpackTag.word[2];
        tag->word[3] = p2ComponentUnpackTag.word[3];
        p2SelectComponentUnpack(fixedPoint, component, elements, data, code, command, offsetMode, cursor,
                                first, count);
        if (cursor->word == tag->word + 4) {
            cursor->word -= 4;
        } else {
            p2AlignVifPacket(cursor);
            tag->qwc = (int)(cursor->address - (unsigned int)tag) / 16 - 1;
            if (tag->qwc == 0) {
                cursor->word -= 4;
            }
        }
    } else {
        p2SelectComponentUnpack(fixedPoint, component, elements, data, code, command, offsetMode, cursor,
                                first, count);
    }
}

int *p2CopyWord(int *dst, const int *src) {
    *dst = *src;
    return dst;
}

int *p2CopyQuadword(int *dst, const int *src) {
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    return dst;
}
