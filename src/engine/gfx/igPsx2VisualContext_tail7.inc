namespace Gap {
namespace Gfx {

void igPsx2VisualContext::setVertexArray(igVertexArray2 *va, unsigned int stream) {
    _vertexArray2[stream] = va;
    if (va != 0) {
        setVertexArray((igVertexArray *)0);
    }
}
}
}

/* Bind the position, normal, color and texture-coordinate streams of `vertexData` for drawing and
 * return their base addresses through the four out pointers (zero for an absent optional stream).
 * Float streams (igVec3fList / igVec2fList) bind as they are; char/short streams set a fixed-point
 * component layout from the entry's shift, which the return value reports. Without an index
 * array the streams are advanced to `firstVertex`. */

bool FUN_0017df40(igPsx2VisualContext *vc, igVertexDataList *vertexData, int firstVertex, int *positions, int *normals, int *colors, int *texCoords) {
    bool integerFormat = false;
    igVertexData *entry;
    Gap::Core::igObject *source;
    Gap::Core::igObject *list;
    Gap::Core::igObject *floatList;
    Gap::Core::igObject *other;

    entry = FUN_0015f4a0(vertexData, 1, 0);
    source = (Gap::Core::igObject *)dw4_cast_or_null((char *)componentList(entry), &g_igVec3fList_metaObject);
    if (source != 0) {
        *positions = listData(source);
        p2SetComponentLayout(0, 0, 0, 0);
    } else {
        source = componentList(entry);
        if (isListOf(source, Gap::Core::igCharList::getClassMeta())) {
            p2SetComponentLayout(0, 1, 7 - entry->_componentFraction, entry->_componentFraction);
            integerFormat = true;
            *positions = listData(source);
        } else if (isListOf(source, Gap::Core::igUnsignedCharList::getClassMeta())) {
            p2SetComponentLayout(0, 0, 8 - entry->_componentFraction, entry->_componentFraction);
            integerFormat = true;
            *positions = listData(source);
        } else if (isListOf(source, Gap::Core::igShortList::getClassMeta())) {
            p2SetComponentLayout(0, 1, 15 - entry->_componentFraction, entry->_componentFraction);
            integerFormat = true;
            *positions = listData(source);
        } else if (isListOf(source, Gap::Core::igUnsignedShortList::getClassMeta())) {
            p2SetComponentLayout(0, 0, 16 - entry->_componentFraction, entry->_componentFraction);
            integerFormat = true;
            *positions = listData(source);
        }
    }
    entry = FUN_0015f4a0(vertexData, 3, 0);
    if (entry != 0) {
        list = componentList(entry);
        if (list != 0 && list->isOfType(g_igVec3fList_metaObject) != 0) {
            floatList = list;
        } else {
            floatList = 0;
        }
        if (floatList != 0) {
            *normals = listData(floatList);
            p2SetComponentLayout(1, 0, 0, 0);
        } else {
            other = componentList(entry);
            if (isListOf(other, Gap::Core::igCharList::getClassMeta())) {
                p2SetComponentLayout(1, 1, 7 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *normals = listData(other);
            } else if (isListOf(other, Gap::Core::igUnsignedCharList::getClassMeta())) {
                p2SetComponentLayout(1, 0, 8 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *normals = listData(other);
            } else if (isListOf(other, Gap::Core::igShortList::getClassMeta())) {
                p2SetComponentLayout(1, 1, 15 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *normals = listData(other);
            } else if (isListOf(other, Gap::Core::igUnsignedShortList::getClassMeta())) {
                p2SetComponentLayout(1, 0, 16 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *normals = listData(other);
            }
        }
    } else {
        *normals = 0;
    }
    entry = FUN_0015f4a0(vertexData, 2, 0);
    if (entry != 0) {
        if (isListOf(componentList(entry), Gap::Core::igUnsignedIntList::getClassMeta())) {
            *colors = listData(componentList(entry));
        } else if (isListOf(componentList(entry), g_igVec4ucList_metaObject)) {
            *colors = listData(componentList(entry));
        }
    } else {
        *colors = 0;
    }
    entry = FUN_0015f4a0(vertexData, 4, vc->_texCoordIndex[0]);
    if (entry != 0) {
        list = componentList(entry);
        if (list != 0 && list->isOfType(g_igVec2fList_metaObject) != 0) {
            floatList = list;
        } else {
            floatList = 0;
        }
        if (floatList != 0) {
            *texCoords = listData(floatList);
            p2SetComponentLayout(2, 0, 0, 0);
        } else {
            source = componentList(entry);
            if (isListOf(source, Gap::Core::igCharList::getClassMeta())) {
                p2SetComponentLayout(2, 1, 7 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *texCoords = listData(source);
            } else if (isListOf(source, Gap::Core::igUnsignedCharList::getClassMeta())) {
                p2SetComponentLayout(2, 0, 8 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *texCoords = listData(source);
            } else if (isListOf(source, Gap::Core::igShortList::getClassMeta())) {
                p2SetComponentLayout(2, 1, 15 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *texCoords = listData(source);
            } else if (isListOf(source, Gap::Core::igUnsignedShortList::getClassMeta())) {
                p2SetComponentLayout(2, 0, 16 - entry->_componentFraction, entry->_componentFraction);
                integerFormat = true;
                *texCoords = listData(source);
            }
        }
    } else {
        *texCoords = 0;
    }
    if (vc->_pIndexArray == 0) {
        *positions = *positions + firstVertex * 12;
        if (*normals != 0) *normals = *normals + firstVertex * 12;
        if (*colors != 0) *colors = *colors + firstVertex * 4;
        if (*texCoords != 0) *texCoords = *texCoords + firstVertex * 8;
    }
    return integerFormat;
}


bool FUN_0017e590(igPsx2VisualContext *vc, igVertexDataList *vertexData, int firstVertex, int *spriteSizes, int *texCoords) {
    igVertexData *n2; Gap::Core::igObject *s; Gap::Core::igObject *r; Gap::Core::igObject *o2;
    bool integerFormat = false;
    igVertexData *n = FUN_0015f4a0(vertexData, 9, 0);
    if (n != 0) {
        if ((int)Gap::Core::igFloatList::getClassMeta() == (int)componentList(n)->getMeta()) {
            *spriteSizes = listData(componentList(n));
            p2SetComponentLayout(4, 0, 0, 0);
        } else if ((int)componentList(n)->getMeta() == (int)g_igVec2fList_metaObject) {
            *spriteSizes = listData(componentList(n));
            p2SetComponentLayout(4, 0, 0, 0);
        } else {
            Gap::Core::igObject *o = componentList(n);
            if (Gap::Core::igCharList::getClassMeta() == o->getMeta()) {
                int a = n->_componentFraction;
                p2SetComponentLayout(4, 1, 7 - a, a);
                integerFormat = true;
                *spriteSizes = listData(o);
            } else if (Gap::Core::igUnsignedCharList::getClassMeta() == o->getMeta()) {
                int a = n->_componentFraction;
                p2SetComponentLayout(4, 0, 8 - a, a);
                *spriteSizes = listData(o);
            } else if (Gap::Core::igShortList::getClassMeta() == o->getMeta()) {
                int a = n->_componentFraction;
                p2SetComponentLayout(4, 1, 0xF - a, a);
                *spriteSizes = listData(o);
            } else if (Gap::Core::igUnsignedShortList::getClassMeta() == o->getMeta()) {
                int a = n->_componentFraction;
                p2SetComponentLayout(4, 0, 0x10 - a, a);
                *spriteSizes = listData(o);
            }
        }
    } else {
        *spriteSizes = 0;
    }
    n2 = FUN_0015f4a0(vertexData, 4, 1);
    if (n2 != 0) {
        s = componentList(n2);
        if (s != 0 && s->isOfType(g_igVec2fList_metaObject) != 0) {
            r = s;
        } else {
            r = 0;
        }
        if (r != 0) {
            *texCoords = listData(r);
        } else {
            o2 = componentList(n2);
            if (Gap::Core::igCharList::getClassMeta() == o2->getMeta()) {
                int a = n2->_componentFraction;
                p2SetComponentLayout(2, 1, 7 - a, a);
                *texCoords = listData(o2);
            } else if (Gap::Core::igUnsignedCharList::getClassMeta() == o2->getMeta()) {
                int a = n2->_componentFraction;
                p2SetComponentLayout(2, 0, 8 - a, a);
                *texCoords = listData(o2);
            } else if (Gap::Core::igShortList::getClassMeta() == o2->getMeta()) {
                int a = n2->_componentFraction;
                p2SetComponentLayout(2, 1, 0xF - a, a);
                *texCoords = listData(o2);
            } else if (Gap::Core::igUnsignedShortList::getClassMeta() == o2->getMeta()) {
                int a = n2->_componentFraction;
                p2SetComponentLayout(2, 0, 0x10 - a, a);
                *texCoords = listData(o2);
            }
        }
    } else {
        *texCoords = 0;
    }
    if (vc->_pIndexArray == 0) {
        if (*spriteSizes != 0) *spriteSizes = *spriteSizes + firstVertex * 4;
        if (*texCoords != 0) *texCoords = *texCoords + firstVertex * 8;
    }
    return integerFormat;
}

void FUN_0017e980(igPsx2VisualContext *h, igVertexDataList *vertexData, int firstVertex)
{
    int i;
    igVertexData *e;
    int v;
    Gap::Core::igObject *o;

    if (h->_bMultiPassNum > 1 && h->_pixelPipelineMode == 3) {
        for (i = 1; i < h->_bMultiPassNum; i++) {
            e = FUN_0015f4a0(vertexData, 4, h->_texCoordIndex[i]);
            v = 0;
            if (e != 0) {
                o = componentList(e);
                if (o != 0 && o->isOfType(g_igVec2fList_metaObject) != 0) {
                    o = (Gap::Core::igObject *)o;
                } else {
                    o = 0;
                }
                if (o != 0) {
                    v = listData(o);
                } else {
                    o = componentList(e);
                    if (g_igCharList_metaObject == o->getMeta()) {
                        p2SetComponentLayout(2, 1, 7 - e->_componentFraction, e->_componentFraction);
                        v = listData(o);
                    } else if (g_igUnsignedCharList_metaObject == o->getMeta()) {
                        p2SetComponentLayout(2, 0, 8 - e->_componentFraction, e->_componentFraction);
                        v = listData(o);
                    } else if (g_igShortList_metaObject == o->getMeta()) {
                        p2SetComponentLayout(2, 1, 15 - e->_componentFraction, e->_componentFraction);
                        v = listData(o);
                    } else if (g_igUnsignedShortList_metaObject == o->getMeta()) {
                        p2SetComponentLayout(2, 0, 16 - e->_componentFraction, e->_componentFraction);
                        v = listData(o);
                    }
                }
                if (h->_pIndexArray == 0) {
                    v += firstVertex * 8;
                }
            }
            p2SetTexCoordArray(i, (float *)v);
        }
    }
}

/* Draws `count` primitives (or, for the 0x2000 strip kinds, `count` strips) of the vertex data list straight
 * from its components, advancing to each strip's first vertex in turn; the sprite kind (0x1000) draws with the
 * size stream as normals and the second texture-coordinate stream. */
void FUN_0017eb90(igPsx2VisualContext *vc, igVertexDataList *vertexData, int primitive, int count, int firstVertex, int stripOffset, bool useTexture) {
    int positions;
    int normals;
    int texCoords;
    int spriteTexCoords;
    int colors;
    int spriteSizes;
    int *stripLengths;
    int strip;
    int strip2;
    int indices;
    int integerFormat;
    igPsx2IndexArray *indexArray;

    indexArray = (igPsx2IndexArray *)vc->_pIndexArray;
    if (indexArray != 0) {
        indices = indexArray->_indexData;
    } else {
        indices = 0;
    }
    integerFormat = FUN_0017df40(vc, vertexData, firstVertex, &positions, &normals, &colors, &texCoords) & 0xFF;
    FUN_0017e980(vc, vertexData, firstVertex);
    if ((integerFormat != 0) || useTexture) {
        p2EnableCapability(0x1B);
    } else if (p2IsCapabilityEnabled(0x1B) != 0) {
        p2DisableCapability(0x1B);
    }
    switch (primitive) {
    case 0x0:
        p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
        p2DrawPoints(count);
        break;
    case 0x1:
        p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
        p2DrawLines(count);
        break;
    case 0x2:
        p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
        p2DrawLineStrip(count);
        break;
    case 0x3:
        p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
        if (indices == 0) {
            p2DrawTriangles(count);
        } else {
            p2DrawIndexedTriangles(count, (unsigned short *)(indices + (firstVertex * 2)));
        }
        break;
    case 0x4:
        p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
        if (indices == 0) {
            p2DrawTriangleStrip(count);
        } else {
            p2DrawIndexedTriangleStrip(count, (unsigned short *)(indices + (firstVertex * 2)));
        }
        break;
    case 0x5:
        p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
        if (indices == 0) {
            p2DrawTriangleFan(count);
        } else {
            p2DrawIndexedTriangleFan(count, (unsigned short *)(indices + (firstVertex * 2)));
        }
        break;
    case 0x1000:
        if (FUN_0017e590(vc, vertexData, firstVertex, &spriteSizes, &spriteTexCoords) && (integerFormat == 0)) {
            p2EnableCapability(0x1B);
        }
        p2SetTexCoordArray(1, (float *)spriteTexCoords);
        p2SetVertexArrays((float *)positions, (float *)spriteSizes, (unsigned int *)colors, (float *)texCoords);
        if (indices == 0) {
            p2DrawSprites(count);
        } else {
            p2DrawIndexedSprites(count, (unsigned short *)(indices + (firstVertex * 2)));
        }
        break;
    case 0x2000:
        stripLengths = (int *)((igPrimLengthArray *)vc->_pStripLengthArray)->_lengthData + stripOffset;
        for (strip = 0; strip < count; strip++) {
            p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
            p2DrawLineStrip(*stripLengths);
            firstVertex += *stripLengths;
            stripLengths += 1;
            FUN_0017df40(vc, vertexData, firstVertex, &positions, &normals, &colors, &texCoords);
            FUN_0017e980(vc, vertexData, firstVertex);
        }
        break;
    case 0x2002:
        stripLengths = (int *)((igPrimLengthArray *)vc->_pStripLengthArray)->_lengthData + stripOffset;
        for (strip2 = 0; strip2 < count; strip2++) {
            p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
            if (indices == 0) {
                p2DrawTriangleFan(*stripLengths);
            } else {
                p2DrawIndexedTriangleFan(*stripLengths, (unsigned short *)(indices + (firstVertex * 2)));
            }
            firstVertex += *stripLengths;
            stripLengths += 1;
            FUN_0017df40(vc, vertexData, firstVertex, &positions, &normals, &colors, &texCoords);
            FUN_0017e980(vc, vertexData, firstVertex);
        }
        break;
    case 0x2001:
        stripLengths = (int *)((igPrimLengthArray *)vc->_pStripLengthArray)->_lengthData + stripOffset;
        if (indices == 0) {
            p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
            p2DrawTriangleStrips(count, stripLengths);
        } else {
            for (strip2 = 0; strip2 < count; strip2++) {
                p2SetVertexArrays((float *)positions, (float *)normals, (unsigned int *)colors, (float *)texCoords);
                p2DrawIndexedTriangleStrip(*stripLengths, (unsigned short *)(indices + (firstVertex * 2)));
                firstVertex += *stripLengths;
                stripLengths += 1;
                FUN_0017df40(vc, vertexData, firstVertex, &positions, &normals, &colors, &texCoords);
                FUN_0017e980(vc, vertexData, firstVertex);
            }
        }
        break;
    }
}

/* The vertices a draw of `count` primitives reads. */
static inline unsigned int PrimitiveVertexCount(int primitive, unsigned int count) {
    switch (primitive) {
    case 0x1000:
    case 0:
        return count;
    case 1:
        return count * 2;
    case 2:
        return count + 1;
    case 3:
        return count * 3;
    case 4:
    case 5:
        return count + 2;
    case 0x2000:
    case 0x2002:
    case 0x2001:
        return count;
    default:
        return 0;
    }
}

/* Draws the context's first vertex array through its PS2 vertex stream: configures the stream on first use, calls
 * the stream's compiled render list when it can (no software blending, the whole compiled range), and otherwise
 * draws the vertex data directly. A stream the CPU reads or writes back (read-write or read access) or one just
 * blended in software records the VIF1 wait sequence of the draw. */
void FUN_0017f080(igPsx2VisualContext *vc, int primitive, unsigned int count, int vertexOffset, int primitiveOffset) {
    Gap::Gfx::igPsx2VertexArray2 *array = (Gap::Gfx::igPsx2VertexArray2 *)vc->_vertexArray2[0];
    Gap::Gfx::igPsx2VertexStream *stream;
    bool useRenderList;
    bool useTexture;
    int blendState;
    bool sync;

    if (array->_vertexStream == 0 || !array->_vertexStream->isConfigured()) {
        array->configure((IG_GFX_DRAW)primitive, (Gap::Gfx::igIndexArray *)vc->_pIndexArray,
                         (Gap::Gfx::igPrimLengthArray *)vc->_pStripLengthArray, (Gap::Gfx::igVisualContext *)vc);
    }
    stream = (Gap::Gfx::igPsx2VertexStream *)array->_vertexStream.p;
    useRenderList = stream->_renderListHandle != 0;
    useTexture = false;
    blendState = FUN_001774c0(vc, stream, &useTexture);
    count = PrimitiveVertexCount(primitive, count);
    sync = stream->getAccessMode() == Gap::Gfx::igVertexStream::IG_VERTEX_ACCESS_READ_WRITE
        || stream->getAccessMode() == Gap::Gfx::igVertexStream::IG_VERTEX_ACCESS_READ;
    if (blendState == 3 || blendState == 1
        || (useRenderList && (vertexOffset != 0 || primitiveOffset != 0 || count != stream->_vertexCountCompiled))) {
        if (blendState == 1) {
            FUN_001805a0(vc, stream, count);
            sync = true;
        }
        useRenderList = false;
    }
    if (useRenderList) {
        p2CallDisplayList((p2DisplayList *)stream->_renderListHandle);
    } else {
        FUN_0017eb90(vc, (igVertexDataList *)stream->_vertexDataList.p, primitive, count, vertexOffset, primitiveOffset, useTexture);
    }
    if (sync) {
        stream->_syncSequence = p2GetVif1WaitSequence();
    }
}

static inline void release_17f2b0(Rc_17f2b0 *object) {
    igObject::release(object);
}

