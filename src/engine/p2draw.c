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
    P2_PRIM_SPRITE
};

/* Bits of p2VertexFormat: which arrays the vertex program unpacks. */
enum p2VertexFormatBit {
    P2_FORMAT_NORMALS = 0x1,
    P2_FORMAT_COLOURS = 0x2,
    P2_FORMAT_TEXCOORDS = 0x4,
    P2_FORMAT_ARRAY_BITS = 0x7,
    P2_FORMAT_RECORDING = 0x20,
    P2_FORMAT_SPRITE_SIZE_MODE0 = 0x40,
    P2_FORMAT_SPRITE_SIZE_MODE1 = 0x80,
    P2_FORMAT_SPRITE_BYTES = 0x100
};

/* Bits of a program's p2ProgramFlags entry, as shifts. */
enum p2ProgramFlagBit {
    P2_PROGRAM_ARRAY_FORMAT = 22, /* the format follows the bound arrays outside recording too */
    P2_PROGRAM_FIXED_POINT = 27   /* the components are fixed point: upload their scales */
};

enum {
    P2_VIF_UNPACK_RELATIVE_UNSIGNED = 0xC000,
    P2_PIPELINE_VERTEX_ARRAYS = 0,
    P2_RENDER_STATE_ALL = 0x1FF
};

/* Where the double-buffered vertex batches sit in VU1 memory, and how many vertices one holds. */
typedef struct p2VuBufferLayout {
    char pad0[10];
    short byteUnpackAddress;
    char pad12[10];
    short batchVertexLimit;
} p2VuBufferLayout;

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
    unsigned int word;
} p2VifCode;

/* A DMA tag with its quadword count in the low half, written to the packet as four words. */
typedef union p2DmaTag {
    unsigned short qwc;
    unsigned int word[4];
} p2DmaTag;

typedef void (*p2VertexSubmit)(unsigned int count, int first);

int FUN_001eb810(void);
int FUN_001fffb0(void);
int FUN_00200980(void);
int FUN_00201a90(void);
int FUN_001ff3b0(int);
int FUN_001ff720(int);
void FUN_0020e3c0(float);
float FUN_0020e3d0(void);

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
        FUN_00201a90();
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
            FUN_001ff720(P2_RENDER_STATE_ALL);
        }
    }
    if (fixedPoint) {
        FUN_001eb810();
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

/* Loads the VIF row registers when the value or the scale differs from what they hold. */
void p2WriteVifRow(p2VifCursor *cursor, unsigned int value, float scale) {
    unsigned int *p;

    if (value != 0 || scale != FUN_0020e3d0()) {
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
        FUN_0020e3c0(scale);
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
