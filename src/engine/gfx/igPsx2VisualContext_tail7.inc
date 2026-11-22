void igPsx2VisualContext_SetVertexArray2(int *arg0, int *arg1, int arg2) {
    int *old;
    int *slot;
    int idx;

    if (arg1 != 0) {
        arg1[1] = arg1[1] + 1;
    }
    idx = arg2 * 4;
    idx = idx + (int)arg0;
    slot = (int *)(idx + 240);
    old = (int *)*slot;
    if (old != 0) {
        old[1] = old[1] - 1;
        if ((old[1] & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)old);
        }
    }
    *slot = (int)arg1;
    if (arg1 != 0) {
        ((Obj_17dea0 *)arg0)->vX(0);
    }
}

/* Bind the position, normal, color and texture-coordinate streams of `vertexData` for drawing and
 * return their base addresses through the four out pointers (zero for an absent optional stream).
 * Float streams (igVec3fList / igVec2fList) bind as they are; char/short streams set a fixed-point
 * component layout from the entry's shift, which the return value reports. Without an index
 * array the streams are advanced to `firstVertex`. */
static inline bool isListOf(VC_17e590 *list, igMetaObject *meta) { return (int)meta == list->vX(); }

bool FUN_0017df40(B_17eb90 *context, int vertexData, int firstVertex, int *positions, int *normals, int *colors, int *texCoords) {
    igPsx2VisualContext *vc = (igPsx2VisualContext *)context;
    bool integerFormat = false;
    Node *entry;
    VC_17e590 *source;
    VC_17e590 *list;
    VC_17e590 *floatList;
    VC_17e590 *other;

    entry = (Node *)FUN_0015f4a0((S_15f430 *)vertexData, 1, 0);
    source = (VC_17e590 *)dw4_cast_or_null((char *)entry->obj, &g_igVec3fList_metaObject);
    if (source != 0) {
        *positions = source->f16;
        p2SetComponentLayout(0, 0, 0, 0);
    } else {
        source = entry->obj;
        if (isListOf(source, Gap::Core::igCharList::getClassMeta())) {
            p2SetComponentLayout(0, 1, 7 - entry->f32, entry->f32);
            integerFormat = true;
            *positions = source->f16;
        } else if (isListOf(source, Gap::Core::igUnsignedCharList::getClassMeta())) {
            p2SetComponentLayout(0, 0, 8 - entry->f32, entry->f32);
            integerFormat = true;
            *positions = source->f16;
        } else if (isListOf(source, Gap::Core::igShortList::getClassMeta())) {
            p2SetComponentLayout(0, 1, 15 - entry->f32, entry->f32);
            integerFormat = true;
            *positions = source->f16;
        } else if (isListOf(source, Gap::Core::igUnsignedShortList::getClassMeta())) {
            p2SetComponentLayout(0, 0, 16 - entry->f32, entry->f32);
            integerFormat = true;
            *positions = source->f16;
        }
    }
    entry = (Node *)FUN_0015f4a0((S_15f430 *)vertexData, 3, 0);
    if (entry != 0) {
        list = entry->obj;
        if (list != 0 && ((Gap::Core::igObject *)list)->isOfType(g_igVec3fList_metaObject) != 0) {
            floatList = list;
        } else {
            floatList = 0;
        }
        if (floatList != 0) {
            *normals = floatList->f16;
            p2SetComponentLayout(1, 0, 0, 0);
        } else {
            other = entry->obj;
            if (isListOf(other, Gap::Core::igCharList::getClassMeta())) {
                p2SetComponentLayout(1, 1, 7 - entry->f32, entry->f32);
                integerFormat = true;
                *normals = other->f16;
            } else if (isListOf(other, Gap::Core::igUnsignedCharList::getClassMeta())) {
                p2SetComponentLayout(1, 0, 8 - entry->f32, entry->f32);
                integerFormat = true;
                *normals = other->f16;
            } else if (isListOf(other, Gap::Core::igShortList::getClassMeta())) {
                p2SetComponentLayout(1, 1, 15 - entry->f32, entry->f32);
                integerFormat = true;
                *normals = other->f16;
            } else if (isListOf(other, Gap::Core::igUnsignedShortList::getClassMeta())) {
                p2SetComponentLayout(1, 0, 16 - entry->f32, entry->f32);
                integerFormat = true;
                *normals = other->f16;
            }
        }
    } else {
        *normals = 0;
    }
    entry = (Node *)FUN_0015f4a0((S_15f430 *)vertexData, 2, 0);
    if (entry != 0) {
        if (isListOf(entry->obj, Gap::Core::igUnsignedIntList::getClassMeta())) {
            *colors = entry->obj->f16;
        } else if (isListOf(entry->obj, g_igVec4ucList_metaObject)) {
            *colors = entry->obj->f16;
        }
    } else {
        *colors = 0;
    }
    entry = (Node *)FUN_0015f4a0((S_15f430 *)vertexData, 4, vc->_texCoordIndex[0]);
    if (entry != 0) {
        list = entry->obj;
        if (list != 0 && ((Gap::Core::igObject *)list)->isOfType(g_igVec2fList_metaObject) != 0) {
            floatList = list;
        } else {
            floatList = 0;
        }
        if (floatList != 0) {
            *texCoords = floatList->f16;
            p2SetComponentLayout(2, 0, 0, 0);
        } else {
            source = entry->obj;
            if (isListOf(source, Gap::Core::igCharList::getClassMeta())) {
                p2SetComponentLayout(2, 1, 7 - entry->f32, entry->f32);
                integerFormat = true;
                *texCoords = source->f16;
            } else if (isListOf(source, Gap::Core::igUnsignedCharList::getClassMeta())) {
                p2SetComponentLayout(2, 0, 8 - entry->f32, entry->f32);
                integerFormat = true;
                *texCoords = source->f16;
            } else if (isListOf(source, Gap::Core::igShortList::getClassMeta())) {
                p2SetComponentLayout(2, 1, 15 - entry->f32, entry->f32);
                integerFormat = true;
                *texCoords = source->f16;
            } else if (isListOf(source, Gap::Core::igUnsignedShortList::getClassMeta())) {
                p2SetComponentLayout(2, 0, 16 - entry->f32, entry->f32);
                integerFormat = true;
                *texCoords = source->f16;
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


bool FUN_0017e590(Self_17e590 *arg0, int arg1, int arg2, int *arg3, int *arg4) {
    Node *n2; VC_17e590 *s; VC_17e590 *r; VC_17e590 *o2;
    bool var_s2 = false;
    Node *n = (Node *)FUN_0015f4a0((S_15f430 *)arg1, 9, 0);
    if (n != 0) {
        if ((int)Gap::Core::igFloatList::getClassMeta() == n->obj->vX()) {
            *arg3 = n->obj->f16;
            p2SetComponentLayout(4, 0, 0, 0);
        } else if (n->obj->vX() == (int)g_igVec2fList_metaObject) {
            *arg3 = n->obj->f16;
            p2SetComponentLayout(4, 0, 0, 0);
        } else {
            VC_17e590 *o = n->obj;
            if ((int)Gap::Core::igCharList::getClassMeta() == o->vX()) {
                int a = n->f32;
                p2SetComponentLayout(4, 1, 7 - a, a);
                var_s2 = true;
                *arg3 = o->f16;
            } else if ((int)Gap::Core::igUnsignedCharList::getClassMeta() == o->vX()) {
                int a = n->f32;
                p2SetComponentLayout(4, 0, 8 - a, a);
                *arg3 = o->f16;
            } else if ((int)Gap::Core::igShortList::getClassMeta() == o->vX()) {
                int a = n->f32;
                p2SetComponentLayout(4, 1, 0xF - a, a);
                *arg3 = o->f16;
            } else if ((int)Gap::Core::igUnsignedShortList::getClassMeta() == o->vX()) {
                int a = n->f32;
                p2SetComponentLayout(4, 0, 0x10 - a, a);
                *arg3 = o->f16;
            }
        }
    } else {
        *arg3 = 0;
    }
    n2 = (Node *)FUN_0015f4a0((S_15f430 *)arg1, 4, 1);
    if (n2 != 0) {
        s = n2->obj;
        if (s != 0 && ((Gap::Core::igObject *)s)->isOfType(g_igVec2fList_metaObject) != 0) {
            r = s;
        } else {
            r = 0;
        }
        if (r != 0) {
            *arg4 = r->f16;
        } else {
            o2 = n2->obj;
            if ((int)Gap::Core::igCharList::getClassMeta() == o2->vX()) {
                int a = n2->f32;
                p2SetComponentLayout(2, 1, 7 - a, a);
                *arg4 = o2->f16;
            } else if ((int)Gap::Core::igUnsignedCharList::getClassMeta() == o2->vX()) {
                int a = n2->f32;
                p2SetComponentLayout(2, 0, 8 - a, a);
                *arg4 = o2->f16;
            } else if ((int)Gap::Core::igShortList::getClassMeta() == o2->vX()) {
                int a = n2->f32;
                p2SetComponentLayout(2, 1, 0xF - a, a);
                *arg4 = o2->f16;
            } else if ((int)Gap::Core::igUnsignedShortList::getClassMeta() == o2->vX()) {
                int a = n2->f32;
                p2SetComponentLayout(2, 0, 0x10 - a, a);
                *arg4 = o2->f16;
            }
        }
    } else {
        *arg4 = 0;
    }
    if (arg0->f944 == 0) {
        if (*arg3 != 0) *arg3 = *arg3 + arg2 * 4;
        if (*arg4 != 0) *arg4 = *arg4 + arg2 * 8;
    }
    return var_s2;
}

void FUN_0017e980(igPsx2VisualContext *h, int arg1, int arg2)
{
    int i;
    E_17e980 *e;
    int v;
    Obj_17e980 *o;

    if (h->_bMultiPassNum > 1 && h->_pixelPipelineMode == 3) {
        for (i = 1; i < h->_bMultiPassNum; i++) {
            e = (E_17e980 *)FUN_0015f4a0((S_15f430 *)arg1, 4, h->_texCoordIndex[i]);
            v = 0;
            if (e != 0) {
                o = e->obj;
                if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(g_igVec2fList_metaObject) != 0) {
                    o = (Obj_17e980 *)o;
                } else {
                    o = 0;
                }
                if (o != 0) {
                    v = ((int *)o)[4];
                } else {
                    o = e->obj;
                    if ((int)g_igCharList_metaObject == o->meta()) {
                        p2SetComponentLayout(2, 1, 7 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if ((int)g_igUnsignedCharList_metaObject == o->meta()) {
                        p2SetComponentLayout(2, 0, 8 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if ((int)g_igShortList_metaObject == o->meta()) {
                        p2SetComponentLayout(2, 1, 15 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    } else if ((int)g_igUnsignedShortList_metaObject == o->meta()) {
                        p2SetComponentLayout(2, 0, 16 - e->f32, e->f32);
                        v = ((int *)o)[4];
                    }
                }
                if (h->_pIndexArray == 0) {
                    v += arg2 * 8;
                }
            }
            p2SetTexCoordArray(i, (float *)v);
        }
    }
}

void FUN_0017eb90(B_17eb90 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, bool useTexture) {
    int spBC;
    int spB8;
    int spB4;
    int spB0;
    int spAC;
    int spA8;
    int *var_s3;
    int var_s0;
    int var_s0_2;
    int var_s1;
    int var_s6;
    int temp_s7;
    struct C_17eb90 *c;

    c = arg0->f944;
    var_s1 = arg4;
    if (c != 0) {
        var_s0 = c->f12;
    } else {
        var_s0 = 0;
    }
    temp_s7 = FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4) & 0xFF;
    FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
    if ((temp_s7 != 0) || useTexture) {
        p2EnableCapability(0x1B);
    } else if (p2IsCapabilityEnabled(0x1B) != 0) {
        p2DisableCapability(0x1B);
    }
    switch (arg2) {
    case 0x0:
        p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
        p2DrawPoints(arg3);
        break;
    case 0x1:
        p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
        p2DrawLines(arg3);
        break;
    case 0x2:
        p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
        p2DrawLineStrip(arg3);
        break;
    case 0x3:
        p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
        if (var_s0 == 0) {
            p2DrawTriangles(arg3);
        } else {
            p2DrawIndexedTriangles(arg3, (unsigned short *)(var_s0 + (var_s1 * 2)));
        }
        break;
    case 0x4:
        p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
        if (var_s0 == 0) {
            p2DrawTriangleStrip(arg3);
        } else {
            p2DrawIndexedTriangleStrip(arg3, (unsigned short *)(var_s0 + (var_s1 * 2)));
        }
        break;
    case 0x5:
        p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
        if (var_s0 == 0) {
            p2DrawTriangleFan(arg3);
        } else {
            p2DrawIndexedTriangleFan(arg3, (unsigned short *)(var_s0 + (var_s1 * 2)));
        }
        break;
    case 0x1000:
        if (FUN_0017e590((Self_17e590 *)arg0, arg1, var_s1, &spA8, &spB0) && (temp_s7 == 0)) {
            p2EnableCapability(0x1B);
        }
        p2SetTexCoordArray(1, (float *)spB0);
        p2SetVertexArrays((float *)spBC, (float *)spA8, (unsigned int *)spAC, (float *)spB4);
        if (var_s0 == 0) {
            p2DrawSprites(arg3);
        } else {
            p2DrawIndexedSprites(arg3, (unsigned short *)(var_s0 + (var_s1 * 2)));
        }
        break;
    case 0x2000:
        var_s3 = arg0->f948->f8 + arg5;
        for (var_s0_2 = 0; var_s0_2 < arg3; var_s0_2++) {
            p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
            p2DrawLineStrip(*var_s3);
            var_s1 += *var_s3;
            var_s3 += 1;
            FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
            FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
        }
        break;
    case 0x2002:
        var_s3 = arg0->f948->f8 + arg5;
        for (var_s6 = 0; var_s6 < arg3; var_s6++) {
            p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
            if (var_s0 == 0) {
                p2DrawTriangleFan(*var_s3);
            } else {
                p2DrawIndexedTriangleFan(*var_s3, (unsigned short *)(var_s0 + (var_s1 * 2)));
            }
            var_s1 += *var_s3;
            var_s3 += 1;
            FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
            FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
        }
        break;
    case 0x2001:
        var_s3 = arg0->f948->f8 + arg5;
        if (var_s0 == 0) {
            p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
            p2DrawTriangleStrips(arg3, var_s3);
        } else {
            for (var_s6 = 0; var_s6 < arg3; var_s6++) {
                p2SetVertexArrays((float *)spBC, (float *)spB8, (unsigned int *)spAC, (float *)spB4);
                p2DrawIndexedTriangleStrip(*var_s3, (unsigned short *)(var_s0 + (var_s1 * 2)));
                var_s1 += *var_s3;
                var_s3 += 1;
                FUN_0017df40(arg0, arg1, var_s1, &spBC, &spB8, &spAC, &spB4);
                FUN_0017e980((igPsx2VisualContext *)arg0, arg1, var_s1);
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
                         (igPrimLengthArray *)vc->_pStripLengthArray, (igVisualContext *)vc);
    }
    stream = (Gap::Gfx::igPsx2VertexStream *)array->_vertexStream.p;
    useRenderList = stream->_renderListHandle != 0;
    useTexture = false;
    blendState = FUN_001774c0(vc, (Geometry1774 *)stream, &useTexture);
    count = PrimitiveVertexCount(primitive, count);
    sync = stream->getAccessMode() == Gap::Gfx::igVertexStream::IG_VERTEX_ACCESS_READ_WRITE
        || stream->getAccessMode() == Gap::Gfx::igVertexStream::IG_VERTEX_ACCESS_READ;
    if (blendState == 3 || blendState == 1
        || (useRenderList && (vertexOffset != 0 || primitiveOffset != 0 || count != stream->_vertexCountCompiled))) {
        if (blendState == 1) {
            FUN_001805a0((ResourceBuilder *)vc, (ResourceSource *)stream, count);
            sync = true;
        }
        useRenderList = false;
    }
    if (useRenderList) {
        p2CallDisplayList((p2DisplayList *)stream->_renderListHandle);
    } else {
        FUN_0017eb90((B_17eb90 *)vc, (int)stream->_vertexDataList.p, primitive, count, vertexOffset, primitiveOffset, useTexture);
    }
    if (sync) {
        stream->_syncSequence = p2GetVif1WaitSequence();
    }
}

static inline void release_17f2b0(Rc_17f2b0 *object) {
    igObject::release(object);
}

