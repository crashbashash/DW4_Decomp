namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setColor(const igVec4f &rgba) {
    unsigned int value = igVec4f_PackColor(rgba.vec, 1);
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((value >> 1) & 0x7F000000) + (value & 0x01000000);
    lo = value & 0xFFFFFF;
    c = (_currentColor == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    _currentColor = lo | hi;
    p2SetColour(_currentColor);
}

void igPsx2VisualContext::setColor(unsigned int abgr) {
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((abgr >> 1) & 0x7F000000) + (abgr & 0x01000000);
    lo = abgr & 0xFFFFFF;
    c = (_currentColor == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    _currentColor = lo | hi;
    p2SetColour(_currentColor);
}

void igPsx2VisualContext::getColor(igVec4f &rgba) const {
    unsigned int t;
    float f;
    t = (_currentColor >> 24) & 0xFF;
    f = (float)t;

    rgba[0] = 0.0078125f * f;
    t = (_currentColor >> 16) & 0xFF;
    f = (float)t;

    rgba[1] = 0.00392156886f * f;
    t = (_currentColor >> 8) & 0xFF;
    f = (float)t;

    rgba[2] = 0.00392156886f * f;
    t = _currentColor & 0xFF;
    f = (float)t;

    rgba[3] = 0.00392156886f * f;
}

unsigned int igPsx2VisualContext::getColor() const {
    unsigned int t = _currentColor;
    unsigned int a = (t & 0x80000000) >> 7;
    return (t & 0xFFFFFF) | (a + (((t & 0xFF000000) - a) * 2));
}

void igPsx2VisualContext::setVertexMask(igVertexComponentFilter attr) {
    _vMask = attr;
}

igVertexComponentFilter igPsx2VisualContext::getVertexMask() const {
    return igVertexComponentFilter(_vMask);
}

void igPsx2VisualContext::setVertexArray(igVertexArray *vertexArray) {
    if (_pVertexArray == vertexArray) {
        DAT_005608c0[0] += 1;
    }
    _pVertexArray = vertexArray;
    if (vertexArray != 0) {
        setVertexArray((igVertexArray2 *)0, 0);
    }
}

/* IgPsx2VisualContext vtable slot 61, a plain getter that returns the reflected field
 * _pVertexArray (the vertex-array object reference, +940). */

igVertexArray *igPsx2VisualContext::getVertexArray() const {
    return _pVertexArray;
}

void igPsx2VisualContext::setPrimLengthArray(igPrimLengthArray *lengthArray) {
    if (_pStripLengthArray == lengthArray) {
        DAT_005608c4[0] += 1;
    }
    _pStripLengthArray = lengthArray;
}

igPrimLengthArray *igPsx2VisualContext::getPrimLengthArray() const {
    return _pStripLengthArray;
}

void igPsx2VisualContext::setIndexArray(igIndexArray *indexArray) {
    if (_pIndexArray == indexArray) {
        DAT_005608c8[0] += 1;
    }
    _pIndexArray = indexArray;
}

igIndexArray *igPsx2VisualContext::getIndexArray() const {
    return _pIndexArray;
}
}
}

/* The second texture-coordinate stream, which sprites read; an indexed draw addresses it from the start. */
static inline int SpriteTexCoordArray(igPsx2VisualContext *vc, void **streams, int first) {
    int start = vc->_pIndexArray != 0 ? 0 : first;
    return streams[12] != 0 ? (int)streams[12] + start * 8 : 0;
}

namespace Gap {
namespace Gfx {

void igPsx2VisualContext::draw(IG_GFX_DRAW primType, int numPrimitives, int offset) {
    int positions;
    int normals;
    int blendState;

    if (_pVertexArray != 0) {
        positions = 0;
        normals = 0;
        blendState = FUN_00177010((::igPsx2VisualContext *)this, &positions, &normals, -1, -1);
        FUN_0016cc60(this);
        switch (primType) {
        case 0:
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives, offset, (float *)positions, (float *)normals, (int (*)(...))p2DrawPoints, 0);
            break;
        case 1:
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives * 2, offset, (float *)positions, (float *)normals, (int (*)(...))p2DrawLines, 0);
            break;
        case 2:
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives + 1, offset, (float *)positions, (float *)normals, (int (*)(...))p2DrawLineStrip, 0);
            break;
        case 3:
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives * 3, offset, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangles, (int (*)(...))p2DrawIndexedTriangles);
            break;
        case 4:
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives + 2, offset, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangleStrip, (int (*)(...))p2DrawIndexedTriangleStrip);
            break;
        case 5:
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives + 2, offset, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangleFan, (int (*)(...))p2DrawIndexedTriangleFan);
            break;
        default: {
            void **streams = ((Gap::Gfx::igPsx2VertexArray1_1 *)_pVertexArray.p)->_vdata;
            int sizes = streams[15] != 0 ? (int)streams[15] : 0;
            int bytes = streams[19] != 0 ? (int)streams[19] : 0;
            p2SetTexCoordArray(1, (const float *)SpriteTexCoordArray((::igPsx2VisualContext *)this, streams, offset));
            p2SetSpriteByteArray((const unsigned char *)bytes);
            FUN_0016d910((::igPsx2VisualContext *)this, numPrimitives, offset, (float *)positions, (float *)sizes, (int (*)(...))p2DrawSprites, (int (*)(...))p2DrawIndexedSprites);
            break;
        }
        }
        if (blendState == 1) {
            Gap::Gfx::igPsx2VertexArray1_1 *array = (Gap::Gfx::igPsx2VertexArray1_1 *)_pVertexArray.p;
            FUN_0016e140(array, (int)p2GetVif1WaitSequence());
        }
        FUN_0016cd10(this);
        {
            Gap::Gfx::igPsx2VertexArray1_1 *array = (Gap::Gfx::igPsx2VertexArray1_1 *)_pVertexArray.p;
            if (array->_usageFlags & 4) {
                array->_lSequence = p2GetVif1WaitSequence();
            }
        }
    } else {
        FUN_0017f080((::igPsx2VisualContext *)this, primType, numPrimitives, offset, 0);
    }
}

void igPsx2VisualContext::drawMultiple(IG_GFX_DRAW_MULTIPLE stripType, int numStrips, int vertexOffset, int primitiveOffset) {
    int positions;
    int normals;
    int *lengths;
    int blendState, i, *texCoords, *colors;
    int *texCoordStream;
    void **streams;
    Gap::Gfx::igPsx2VertexArray1_1 *array;
    int t;
    if (_pVertexArray != 0) {
        positions = 0;
        normals = 0;
        blendState = FUN_00177010((::igPsx2VisualContext *)this, &positions, &normals, -1, -1);
        FUN_0016cc60(this);
        lengths = (int *)(((igPrimLengthArray *)_pStripLengthArray.p)->_lengthData + primitiveOffset * 4);
        switch (stripType) {
        case 0:
            for (i = 0; i < numStrips; i++) {
                FUN_0016d910((::igPsx2VisualContext *)this, *lengths, vertexOffset, (float *)positions, (float *)normals, (int (*)(...))p2DrawLineStrip, 0);
                vertexOffset += *lengths;
                lengths++;
            }
            break;
        case 2:
            for (i = 0; i < numStrips; i++) {
                FUN_0016d910((::igPsx2VisualContext *)this, *lengths, vertexOffset, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangleFan, (int (*)(...))p2DrawIndexedTriangleFan);
                vertexOffset += *lengths;
                lengths++;
            }
            break;
        case 1:
            i = 0;
            if (_pIndexArray != 0) {
                for (; i < numStrips; i++) {
                    FUN_0016d910((::igPsx2VisualContext *)this, *lengths, vertexOffset, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangleStrip, (int (*)(...))p2DrawIndexedTriangleStrip);
                    vertexOffset += *lengths;
                    lengths++;
                }
            } else {
                streams = ((Gap::Gfx::igPsx2VertexArray1_1 *)_pVertexArray.p)->_vdata;
                t = _texCoordIndex[0] + 11; texCoordStream = (int *)streams[t];
                texCoords = 0;
                if (texCoordStream != 0) {
                    texCoords = (int *)((char *)texCoordStream + vertexOffset * 8);
                }
                colors = 0;
                if (streams[2] != 0) {
                    colors = (int *)((int)streams[2] + vertexOffset * 4);
                }
                FUN_0016db20((::igPsx2VisualContext *)this, vertexOffset);
                t = vertexOffset * 12;
                p2SetVertexArrays((float *)(positions + t), (float *)(normals + t), (unsigned int *)colors, (float *)texCoords);
                p2DrawTriangleStrips(numStrips, lengths);
            }
            break;
        }
        FUN_0016cd10(this);
        if (blendState == 1) {
            array = (Gap::Gfx::igPsx2VertexArray1_1 *)_pVertexArray.p;
            FUN_0016e140(array, (int)p2GetVif1WaitSequence());
        }
        array = (Gap::Gfx::igPsx2VertexArray1_1 *)_pVertexArray.p;
        if (array->_usageFlags & 4) {
            array->_lSequence = p2GetVif1WaitSequence();
        }
    } else {
        FUN_0017f080((::igPsx2VisualContext *)this, stripType + 0x2000, numStrips, vertexOffset, primitiveOffset);
    }
}
}
}

/* The vertex array's colour and texture-coordinate streams for a draw starting at `first`; an indexed
 * draw addresses them from the start. */
static inline int ColourArray(igPsx2VisualContext *vc, int first) {
    int start = first;
    int colours;
    if (vc->_pIndexArray != 0) start = 0;
    colours = (int)((Gap::Gfx::igPsx2VertexArray1_1 *)vc->_pVertexArray)->_vdata[2];
    return colours != 0 ? colours + start * 4 : 0;
}

static inline int TexCoordArray(igPsx2VisualContext *vc, int unit, int first) {
    int start = vc->_pIndexArray != 0 ? 0 : first;
    int component = vc->_texCoordIndex[unit] + 11;
    int texCoords = (int)((Gap::Gfx::igPsx2VertexArray1_1 *)vc->_pVertexArray)->_vdata[component];
    return texCoords != 0 ? texCoords + start * 8 : 0;
}

void FUN_0016d910(igPsx2VisualContext *vc, unsigned int count, int first, const float *positions, const float *normals,
                  int (*draw)(...), int (*drawIndexed)(...)) {
    unsigned int *colours = (unsigned int *)ColourArray(vc, first);
    float *coords = (float *)TexCoordArray(vc, 0, first);
    const float *normalArray;

    FUN_0016db20(vc, first);
    if (vc->_pIndexArray != 0) {
        unsigned short *indices = (unsigned short *)((igPsx2IndexArray *)vc->_pIndexArray)->_indexData;
        p2SetVertexArrays(positions, normals, colours, coords);
        drawIndexed(count, indices + first);
        return;
    }
    if (normals == 0) {
        normalArray = 0;
    } else if (((Gap::Gfx::igPsx2VertexArray1_1 *)vc->_pVertexArray)->getVertexFormat().hasNormals()) {
        normalArray = normals + first * 3;
    } else if (((Gap::Gfx::igPsx2VertexArray1_1 *)vc->_pVertexArray)->getVertexFormat().getPointSpriteCoordCount() == 1) {
        normalArray = normals + first;
    } else if (((Gap::Gfx::igPsx2VertexArray1_1 *)vc->_pVertexArray)->getVertexFormat().getPointSpriteCoordCount() == 2) {
        normalArray = normals + first * 2;
    } else {
        normalArray = 0;
    }
    p2SetVertexArrays(positions + first * 3, normalArray, colours, coords);
    draw(count);
}

namespace Gap {
namespace Gfx {

bool igPsx2VisualContext::beginDraw() {
    StatisticsCapture *capture;

    if (_showFrameRate != 0) {
        _frameStartTime = __floatdisf(_timer->getTimeAsLong());
    }
    capture = (StatisticsCapture *)_statisticCaptures;
    if (capture != 0) {
        while (capture != 0) {
            if (capture->active != 0) {
                if (capture->startCapture == 0) {
                    p2GetStatistics(&capture->start);
                    capture->f936 = _timer->getTimeAsLong();
                }
                capture->startCapture = capture->startCapture - 1;
            }
            capture = capture->next;
        }
    }
    return 1;
}

void igPsx2VisualContext::endDraw() {
    float frameTime = 0.0f;
    StatisticsCapture *n;
    if (_showFrameRate != 0) {
        frameTime = dptofp(_timer->getTimeAsDouble());
        _timer->reset();
    }
    p2EndFrame();
    p2SwapBuffers();
    if (_showFrameRate != 0) {
        ((Gap::Gfx::igVisualContext *)this)->updateFrameRateDisplay(frameTime, frameTime - _frameStartTime);
        ((Gap::Gfx::igVisualContext *)this)->updatePrimitiveCountDisplay(frameTime);
        _primitiveCount = 0;
    }
    n = (StatisticsCapture *)_statisticCaptures;
    if (n != 0) {
      while (n != 0) {
        if (n->active != 0 && n->startCapture == -n->frameCount) {
            p2GetStatistics(&n->end);
            n->f936 = _timer->getTimeAsLong();
            printStatisticCapture(n);
            n->active = 0;
        }
        n = n->next;
      }
    }
}

void igPsx2VisualContext::flushDraw() {
    p2WaitFinishSequence(p2NewFinishSequence(1));
    p2SetSingleFrameLatency();
}
}
}

/* Records the VIF1 wait sequence of a draw in the vertex array's wait-sequence list, at the slot of the array just used. */
void FUN_0016e140(Gap::Gfx::igPsx2VertexArray1_1 *array, int sequence) {
    long long wait = sequence;
    int index = array->_lastArrayUsed;
    ::igPsx2LongList *list = array->_pWaitSeqList.p;
    if ((list->_count != 0) && (index >= 0) && (index < list->_count)) {
        ((long long *)list->_data)[index] = (long long)wait;
    }
}
