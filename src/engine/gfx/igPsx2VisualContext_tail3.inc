void igPsx2VisualContext_SetColor(VisualContextView *arg0, void *color) {
    unsigned int value = igVec4f_PackColor((float *)color, 1);
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((value >> 1) & 0x7F000000) + (value & 0x01000000);
    lo = value & 0xFFFFFF;
    c = (arg0->f3bc == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    arg0->f3bc = lo | hi;
    p2SetColour(arg0->f3bc);
}

void igPsx2VisualContext_SetColorPacked(igPsx2VisualContext *self, unsigned int arg1) {
    VisualContextView *arg0 = (VisualContextView *)self;
    unsigned int hi;
    unsigned int lo;
    int c;
    hi = ((arg1 >> 1) & 0x7F000000) + (arg1 & 0x01000000);
    lo = arg1 & 0xFFFFFF;
    c = (arg0->f3bc == lo);
    if ((c | hi) != 0) {
        DAT_005608a0[0] += 1;
    }
    arg0->f3bc = lo | hi;
    p2SetColour(arg0->f3bc);
}

void igPsx2VisualContext_GetColor(S_16d010 *arg0, float *arg1) {
    unsigned int t;
    float f;
    t = (arg0->f956 >> 24) & 0xFF;
    f = (float)t;

    arg1[0] = 0.0078125f * f;
    t = (arg0->f956 >> 16) & 0xFF;
    f = (float)t;

    arg1[1] = 0.00392156886f * f;
    t = (arg0->f956 >> 8) & 0xFF;
    f = (float)t;

    arg1[2] = 0.00392156886f * f;
    t = arg0->f956 & 0xFF;
    f = (float)t;

    arg1[3] = 0.00392156886f * f;
}

unsigned int igPsx2VisualContext_GetColorPacked(igPsx2VisualContext *self) {
    unsigned int t = self->_currentColor;
    unsigned int a = (t & 0x80000000) >> 7;
    return (t & 0xFFFFFF) | (a + (((t & 0xFF000000) - a) * 2));
}

void igPsx2VisualContext_SetVertexMask(igPsx2VisualContext *self, int *arg1) {
    *(int *)((char *)self + 952) = (int) *arg1;
}

void igPsx2VisualContext_GetVertexMask(int *arg0, void *arg1)
{
  int new_var;
  new_var = *((int *) (((char *) arg1) + 952));
  *arg0 = 0;
  *arg0 = new_var;
}

void igPsx2VisualContext_SetVertexArray(igPsx2VisualContext *self, igVertexArray *vertexArray) {
    igVertexArray *old;
    if ((igVertexArray *)self->_pVertexArray == vertexArray) {
        DAT_005608c0[0] += 1;
    }
    if (vertexArray) {
        vertexArray->_refCount++;
    }
    old = (igVertexArray *)self->_pVertexArray;
    if (old != 0) {
        --old->_refCount;
        if ((old->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_pVertexArray = (int)vertexArray;
    if (vertexArray != 0) {
        ((VC_16d190 *)self)->vX(0, 0);
    }
}

/* IgPsx2VisualContext vtable slot 61, a plain getter that returns the reflected field
 * _pVertexArray (the vertex-array object reference, +940). */

int igPsx2VisualContext_GetVertexArray(igPsx2VisualContext *self) {
    return self->_pVertexArray;
}

void igPsx2VisualContext_SetPrimLengthArray(igPsx2VisualContext *self, igPrimLengthArray *stripLengths) {
    igPrimLengthArray *old;
    if ((igPrimLengthArray *)self->_pStripLengthArray == stripLengths) {
        DAT_005608c4[0] += 1;
    }
    if (stripLengths) {
        stripLengths->_refCount++;
    }
    old = (igPrimLengthArray *)self->_pStripLengthArray;
    if (old != 0) {
        --old->_refCount;
        if ((old->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_pStripLengthArray = (int)stripLengths;
}

int igPsx2VisualContext_GetPrimLengthArray(igPsx2VisualContext *self) {
    return self->_pStripLengthArray;
}

void igPsx2VisualContext_SetIndexArray(igPsx2VisualContext *self, igIndexArray *indexArray) {
    igIndexArray *old;
    if ((igIndexArray *)self->_pIndexArray == indexArray) {
        DAT_005608c8[0] += 1;
    }
    if (indexArray) {
        indexArray->_refCount++;
    }
    old = (igIndexArray *)self->_pIndexArray;
    if (old != 0) {
        --old->_refCount;
        if ((old->_refCount & 0x7fffff) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_pIndexArray = (int)indexArray;
}

int igPsx2VisualContext_GetIndexArray(igPsx2VisualContext *self) {
    return self->_pIndexArray;
}

/* The second texture-coordinate stream, which sprites read; an indexed draw addresses it from the start. */
static inline int SpriteTexCoordArray(igPsx2VisualContext *vc, int *components, int first) {
    int start = vc->_pIndexArray != 0 ? 0 : first;
    return components[12] != 0 ? components[12] + start * 8 : 0;
}

void igPsx2VisualContext_Draw(igPsx2VisualContext *vc, int primitive, unsigned int count, int first) {
    int positions;
    int normals;
    int blendState;

    if (vc->_pVertexArray != 0) {
        positions = 0;
        normals = 0;
        blendState = FUN_00177010(vc, &positions, &normals, -1, -1);
        FUN_0016cc60((char *)vc);
        switch (primitive) {
        case 0:
            FUN_0016d910(vc, count, first, (float *)positions, (float *)normals, (int (*)(...))p2DrawPoints, 0);
            break;
        case 1:
            FUN_0016d910(vc, count * 2, first, (float *)positions, (float *)normals, (int (*)(...))p2DrawLines, 0);
            break;
        case 2:
            FUN_0016d910(vc, count + 1, first, (float *)positions, (float *)normals, (int (*)(...))p2DrawLineStrip, 0);
            break;
        case 3:
            FUN_0016d910(vc, count * 3, first, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangles, (int (*)(...))p2DrawIndexedTriangles);
            break;
        case 4:
            FUN_0016d910(vc, count + 2, first, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangleStrip, (int (*)(...))p2DrawIndexedTriangleStrip);
            break;
        case 5:
            FUN_0016d910(vc, count + 2, first, (float *)positions, (float *)normals, (int (*)(...))p2DrawTriangleFan, (int (*)(...))p2DrawIndexedTriangleFan);
            break;
        default: {
            int *components = ((VertexArray177 *)vc->_pVertexArray)->f8;
            int sizes = components[15] != 0 ? components[15] : 0;
            int bytes = components[19] != 0 ? components[19] : 0;
            p2SetTexCoordArray(1, (const float *)SpriteTexCoordArray(vc, components, first));
            p2SetSpriteByteArray((const unsigned char *)bytes);
            FUN_0016d910(vc, count, first, (float *)positions, (float *)sizes, (int (*)(...))p2DrawSprites, (int (*)(...))p2DrawIndexedSprites);
            break;
        }
        }
        if (blendState == 1) {
            void *array = (void *)vc->_pVertexArray;
            FUN_0016e140(array, (int)p2GetVif1WaitSequence());
        }
        FUN_0016cd10(vc);
        {
            Q_16d660 *q = (Q_16d660 *)vc->_pVertexArray;
            if (q->f20 & 4) {
                q->f64 = p2GetVif1WaitSequence();
            }
        }
    } else {
        FUN_0017f080(vc, primitive, count, first, 0);
    }
}

void igPsx2VisualContext_DrawMultiple(igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4) {
    int sp8C;
    int sp88;
    int *p;
    int s6, i, *s1, *s0;
    int *rec;
    int *tbl;
    struct Q_16d660 *q;
    int t;
    if (self->_pVertexArray != 0) {
        sp8C = 0;
        sp88 = 0;
        s6 = FUN_00177010(self, &sp8C, &sp88, -1, -1);
        FUN_0016cc60((char *)self);
        p = (int *)(((int *)self->_pStripLengthArray)[2] + arg4 * 4);
        switch (arg1) {
        case 0:
            for (i = 0; i < arg2; i++) {
                FUN_0016d910(self, *p, arg3, (float *)sp8C, (float *)sp88, (int (*)(...))p2DrawLineStrip, 0);
                arg3 += *p;
                p++;
            }
            break;
        case 2:
            for (i = 0; i < arg2; i++) {
                FUN_0016d910(self, *p, arg3, (float *)sp8C, (float *)sp88, (int (*)(...))p2DrawTriangleFan, (int (*)(...))p2DrawIndexedTriangleFan);
                arg3 += *p;
                p++;
            }
            break;
        case 1:
            i = 0;
            if (self->_pIndexArray != 0) {
                for (; i < arg2; i++) {
                    FUN_0016d910(self, *p, arg3, (float *)sp8C, (float *)sp88, (int (*)(...))p2DrawTriangleStrip, (int (*)(...))p2DrawIndexedTriangleStrip);
                    arg3 += *p;
                    p++;
                }
            } else {
                tbl = ((struct Q_16d660 *)self->_pVertexArray)->f8;
                t = self->_texCoordIndex[0] + 11; rec = (int *)tbl[t];
                s1 = 0;
                if (rec != 0) {
                    s1 = (int *)((char *)rec + arg3 * 8);
                }
                s0 = 0;
                if (tbl[2] != 0) {
                    s0 = (int *)(tbl[2] + arg3 * 4);
                }
                FUN_0016db20(self, arg3);
                t = arg3 * 12;
                p2SetVertexArrays((float *)(sp8C + t), (float *)(sp88 + t), (unsigned int *)s0, (float *)s1);
                p2DrawTriangleStrips(arg2, p);
            }
            break;
        }
        FUN_0016cd10(self);
        if (s6 == 1) {
            q = (struct Q_16d660 *)self->_pVertexArray;
            FUN_0016e140(q, (int)p2GetVif1WaitSequence());
        }
        q = (struct Q_16d660 *)self->_pVertexArray;
        if (q->f20 & 4) {
            q->f64 = p2GetVif1WaitSequence();
        }
    } else {
        FUN_0017f080(self, arg1 + 0x2000, arg2, arg3, arg4);
    }
}

/* The vertex array's colour and texture-coordinate streams for a draw starting at `first`; an indexed
 * draw addresses them from the start. */
static inline int ColourArray(igPsx2VisualContext *vc, int first) {
    int start = first;
    int colours;
    if (vc->_pIndexArray != 0) start = 0;
    colours = ((VertexArray177 *)vc->_pVertexArray)->f8[2];
    return colours != 0 ? colours + start * 4 : 0;
}

static inline int TexCoordArray(igPsx2VisualContext *vc, int unit, int first) {
    int start = vc->_pIndexArray != 0 ? 0 : first;
    int component = vc->_texCoordIndex[unit] + 11;
    int texCoords = ((VertexArray177 *)vc->_pVertexArray)->f8[component];
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
    } else if (*((VertexFormat177 *)vc->_pVertexArray)->format() & 2) {
        normalArray = normals + first * 3;
    } else if ((unsigned char)(((unsigned int)*((VertexFormat177 *)vc->_pVertexArray)->format() & 0x300000) >> 20) == 1) {
        normalArray = normals + first;
    } else if ((unsigned char)(((unsigned int)*((VertexFormat177 *)vc->_pVertexArray)->format() & 0x300000) >> 20) == 2) {
        normalArray = normals + first * 2;
    } else {
        normalArray = 0;
    }
    p2SetVertexArrays(positions + first * 3, normalArray, colours, coords);
    draw(count);
}

int igPsx2VisualContext_BeginDraw(A_16dbe0 *arg0) {
    N *var_s0;

    if (arg0->f60 != 0) {
        arg0->f68 = __floatdisf(arg0->f56->vX());
    }
    var_s0 = arg0->f1552;
    if (var_s0 != 0) {
        while (var_s0 != 0) {
            if (var_s0->f16 != 0) {
                if (var_s0->f8 == 0) {
                    p2GetStatistics(&var_s0->f24[0]);
                    var_s0->f936 = arg0->f56->vX();
                }
                var_s0->f8 = var_s0->f8 - 1;
            }
            var_s0 = var_s0->f952;
        }
    }
    return 1;
}

void igPsx2VisualContext_EndDraw(A_16dca0 *arg0) {
    float f20 = 0.0f;
    StatisticsCapture *n;
    if (arg0->b60 != 0) {
        f20 = dptofp(arg0->f56->v100());
        arg0->f56->v116();
    }
    p2EndFrame();
    p2SwapBuffers();
    if (arg0->b60 != 0) {
        arg0->v112(f20, f20 - arg0->f68);
        arg0->v116(f20);
        arg0->f64 = 0;
    }
    n = arg0->f1552;
    if (n != 0) {
      while (n != 0) {
        if (n->active != 0 && n->startCapture == -n->frameCount) {
            p2GetStatistics(&n->end);
            n->f936 = arg0->f56->v104();
            FUN_00178970((igPsx2VisualContext *)arg0, n);
            n->active = 0;
        }
        n = n->next;
      }
    }
}

void igPsx2VisualContext_FlushDraw(void) {
    p2WaitFinishSequence(p2NewFinishSequence(1));
    p2SetSingleFrameLatency();
}

void FUN_0016e140(void *arg0, int arg1) {
    long long v;
    int temp_a2;
    void *temp_a1;
    int temp_v1;
    v = arg1;
    temp_a2 = *(int *)((char *)(arg0) + 60);
    temp_a1 = (void *)(*(int *)((char *)(arg0) + 56));
    temp_v1 = *(int *)((char *)(temp_a1) + 8);
    if ((temp_v1 != 0) && (temp_a2 >= 0) && (temp_a2 < temp_v1)) {
        *(long long *)(*(int *)((char *)(temp_a1) + 16) + (temp_a2 * 8)) = (long long)v;
    }
}

