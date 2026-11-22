/* matching construct: _pBufList is a 4-byte reference field; the cast gives the typed T260 view (no layout effect) */
void FUN_00169260(igPsx2VisualContext *arg0, int arg1) {
    int s0, s2, v, old;
    int *hd;
    T260 *t;
    s0 = ((T260 *)arg0->_pBufList)->f0 - 1;
    for (; s0 > -1; s0--) {
        if (((T260 *)arg0->_pBufList)->Chk(s0)) {
            ((T260 *)arg0->_pBufList)->Add(s0);
        }
    }
    if (arg1 == 0) {
        t = ((T260 *)arg0->_pBufList);
        if (t != 0) {
            if (g_stringPool == 0) {
                v = (int)StringPool_Allocate(16);
                if (v != 0) {
                    v = (int)StringPool_Construct((StringPool *)v);
                }
                g_stringPool = (StringPool *)v;
            }
            s2 = (int)StringPool_Intern(g_stringPool, 0);
            old = t->f8;
            if (old != 0) {
                hd = (int *)(old - 8);
                v = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                }
            }
            t->f8 = s2;
            Memory_FreeBuffer((void *)t->f16);
            Memory_FreeBuffer((void *)((int)t->f12));
            if (&t->f8 != 0) {
                old = t->f8;
                if (old != 0) {
                    hd = (int *)(old - 8);
                    v = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = v;
                    if (v == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                    }
                }
            }
            Memory_FreeBufferAliasB(t);
        }
        arg0->_pBufList = 0;
    }
    arg0->_currentBuf = -1;
}

int igPsx2VisualContext_CreateRenderDestination(igPsx2VisualContext *self, RenderDestinationDesc *desc) {
    Pool46 *p;
    Ent46 *e;
    int s0;
    int i;
    p = (Pool46 *)self->_pBufList;
    if (p->f4 <= 0) {
        p->f16 = (Ent46 *)Memory_ReallocateAlignedAlias(p->f16, (p->f0 + 4) * 48, 16);
        memset(p->f16 + p->f0, 0, 192);
        if (p->f2 < 4) {
            Buf46 *b = (Buf46 *)Memory_FindBufferOwner(p);
            p->f12 = b->vB(p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    s0 = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    e = ((Pool46 *)self->_pBufList)->f16 + s0;
    e->f28 = desc->type;
    e->f0 = desc->sizeX;
    e->f4 = desc->sizeY;
    e->f8 = desc->colorBitCount;
    e->f16 = desc->alphaBitCount;
    e->f12 = desc->depthBitCount;
    e->f20 = desc->stencilBitCount;
    e->f24 = desc->f28;
    e->f40 = 0;
    e->f44 = 0;
    e->f36 = -1;
    self->_currentBuf = s0;
    return s0;
}

void igPsx2VisualContext_DeleteRenderDestination(igPsx2VisualContext *arg0, int arg1) {
    int temp_a1;
    Ar *temp_s0;
    Ar *temp_a2;
    DW4VC_232 *temp_v0;

    temp_a2 = (Ar *)arg0->_pBufList;
    temp_a1 = *(int *)((char *)temp_a2->f16 + arg1 * 0x30 + 36);
    if (-1 < temp_a1) {
        ((DW4VC_524 *)arg0)->vX(temp_a1, temp_a2);
    }
    temp_s0 = (Ar *)arg0->_pBufList;
    if ((arg1 < temp_s0->n) && (arg1 >= 0)) {
        if (temp_s0->cnt >= temp_s0->cap) {
            temp_v0 = (DW4VC_232 *)Memory_FindBufferOwner(temp_s0);
            temp_s0->cap = temp_s0->cap + 8;
            temp_s0->f12 = temp_v0->vX(temp_s0->f12, temp_s0->cap * 2);
        }
        ((short *)temp_s0->f12)[temp_s0->cnt] = arg1;
        temp_s0->cnt = temp_s0->cnt + 1;
    }
}

void igPsx2VisualContext_SetRenderDestination(igPsx2VisualContext *self, int arg1, int unused) {
    I *base;
    I *s0;
    I *cur;
    int t;
    base = ((L48 *)self->_pBufList)->f16;
    s0 = base + arg1;
    cur = base + self->_currentBuf;
    t = s0->f28;
    if (t != 2 && cur->f28 == 2) {
        p2RestoreRenderTarget();
        p2SetViewport(self->_iViewportX, self->_iViewportY, self->_iViewportW, self->_iViewportH, 1.0f - self->_viewportNear, 1.0f - self->_viewportFar);
    } else if (t == 2) {
        p2SetRenderTarget((P2Texture *)s0->f40, (P2Texture *)s0->f44);
        p2SetViewport(0, 0, s0->w, s0->h, 1.0f - self->_viewportNear, 1.0f - self->_viewportFar);
    }
    self->_currentBuf = arg1;
    FUN_0016a520((O520 *)self);
    if (s0->f12 <= 0) {
        ((V_1690d0 *)self)->vX(0);
        return;
    }
    ((V_1690d0 *)self)->vX(1);
}

void igPsx2VisualContext_SetRenderDestinationWithTexture(igPsx2VisualContext *context, int bufferIndex, int *textureIndex,
                                                        int unused) {
    int index;
    int format;
    bool create;
    Tex49 *tex;
    int colorFormat;
    Buf49 *buf;
    buf = &((VC49 *)context)->bufList->records[bufferIndex];
    tex = 0;
    index = *textureIndex;
    create = false;
    if (index == -1) {
        create = true;
    } else {
        tex = &((VC49 *)context)->texList->records[index];
        if (*tex->handle == 0) {
            create = true;
        }
    }
    if (create) {
        switch (buf->format) {
        case 16:
        case 15:
            colorFormat = 3;
            format = 8;
            break;
        case 24:
            if (buf->f16 == 0) {
                colorFormat = 1;
                format = 5;
            } else {
                colorFormat = 0;
                format = 7;
            }
            break;
        case 7:
        case 8:
        default:
            colorFormat = 0;
            format = 7;
            break;
        }
        if (index == -1) {
            *textureIndex = igPsx2VisualContext_CreateTexture((TexContext *)((VC49 *)context), buf->width, buf->height, format, 3, 0, 1);
            buf->texIndex = *textureIndex;
            tex = &((VC49 *)context)->texList->records[*textureIndex];
        }
        if (buf->colorTex != 0) {
            ((VC49 *)context)->releaseTexture(buf->texIndex);
        }
        if (buf->depthFormat > 0) {
            int depthFormat;
            switch (buf->depthFormat) {
            case 16:
            default:
                depthFormat = 12;
                break;
            case 24:
                depthFormat = 10;
                break;
            case 32:
                depthFormat = 9;
                break;
            }
            buf->depthTex = (int)p2LoadTexture(0, buf->width, buf->height, depthFormat, 0);
        }
        buf->colorTex = (int)p2LoadTexture(0, buf->width, buf->height, colorFormat, 0);
        if (buf->colorTex != 0) {
            *tex->handle = buf->colorTex;
            tex->depthHandle = buf->depthTex;
            tex->state = 2;
        } else {
            ((VC49 *)context)->freeTexture(*textureIndex);
            *textureIndex = -1;
            return;
        }
    }
    p2SetRenderTarget((P2Texture *)buf->colorTex, (P2Texture *)buf->depthTex);
    ((VC49 *)context)->currentBuf = bufferIndex;
    p2SetViewport(0, 0, buf->width, buf->height, 1.0f - ((VC49 *)context)->near, 1.0f - ((VC49 *)context)->far);
    FUN_0016a520((O520 *)((VC49 *)context));
    if (buf->depthFormat <= 0) {
        ((VC49 *)context)->setDepth(0);
        return;
    }
    ((VC49 *)context)->setDepth(1);
}

/* Read the first two fields of VRAM buffer record `bufferIndex` (0x30-byte records at _pBufList +
 * 0x10) into *word0 and *word1; vfunc_52 is the matching setter. */
void igPsx2VisualContext_GetRenderDestinationSize(igPsx2VisualContext *self, int bufferIndex, int *word0, int *word1) {
    int recordOffset;

    recordOffset = bufferIndex * 0x30;
    *word0 = *(int *)(*(int *)((char *)(self->_pBufList) + 16) + recordOffset);
    *word1 = *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + recordOffset)) + 4);
}

/* Store two words into the first two fields of VRAM buffer record `bufferIndex`. _pBufList
 * (+0x364) holds the 0x30-byte VRAM buffer records at +0x10; vfunc_53 is the matching getter. */
int igPsx2VisualContext_SetRenderDestinationSize(igPsx2VisualContext *self, int bufferIndex, int word0, int word1) {
    int recordOffset;

    recordOffset = bufferIndex * 0x30;
    *(int *)(*(int *)((char *)(self->_pBufList) + 16) + recordOffset) = word0;
    *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + recordOffset)) + 4) = word1;
    return 1;
}

int igPsx2VisualContext_GetCurrentRenderDestination(igPsx2VisualContext *self) {
    int *p = (int *)self;
    return *(int *)((char *)p + 872);
}

/* Getter for the record field at +0x1c of buffer `bufferIndex`. `_pBufList` (+0x364) is an
 * igDataList whose data pointer (+0x10) addresses 0x30-byte VRAM buffer records. */

int igPsx2VisualContext_GetRenderDestinationType(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 28);
}

void FUN_00169be0(void *d0, int arg1) {
    if (arg1 == 1) {
        p2SetClearWidth(0x40);
        return;
    }
    p2SetClearWidth(0);
}

void igPsx2VisualContext_ClearRenderDestination(igPsx2VisualContext *self, int arg1) {
    int var_a0;

    var_a0 = 0;
    if (arg1 & 1) {
        var_a0 |= 1;
    }
    if (arg1 & 2) {
        var_a0 |= 2;
    }
    p2Clear(var_a0, *(int *)((char *)(self) + 896), *(int *)((char *)(self) + 900));
}

int igPsx2VisualContext_CopyRenderDestinationToTexture(igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8) {
    int temp_a1;
    int temp_a2;
    int temp_v1;
    char *temp_a3;
    char *temp_s0;
    char *temp_s7;

    temp_a2 = (arg1 * 3) << 4;
    temp_a3 = (char *)self->_pBufList;
    temp_a1 = *(int *)(temp_a3 + 16);
    temp_s7 = (char *)(temp_a1 + temp_a2);
    temp_s0 = (char *)(*(int *)((char *)self->_pTexList + 16) + (arg2 * 0x88));
    if (**(int **)(temp_s0 + 72) == 0) {
        **(int **)(temp_s0 + 72) = (int)p2LoadTexture(0, *(int *)(temp_s0 + 32), *(int *)(temp_s0 + 36), FUN_0017a2b0(*(int *)(temp_s0 + 0)), 0);
    }
    if ((arg7 == -1) || (arg8 == -1)) {
        if (self->_textureStateFilter != 0) {
            temp_v1 = (self->_textureMagFilter << 0x10) | self->_textureMinFilter;
            if (self->_currentTextureFilter[0] != temp_v1) {
                self->_currentTextureFilter[0] = temp_v1;
                p2SetTextureFilter(DAT_0048acd0[self->_textureMagFilter], DAT_0048acd0[self->_textureMinFilter]);
            }
        }
        FUN_00209cf0(*(int *)(temp_s7 + 40), **(int **)(temp_s0 + 72), arg3, arg4, arg5, arg6, 0);
    } else if (*(int *)(temp_s7 + 28) == 2) {
        p2CopyTexture((void *)*(int *)(temp_s7 + 40), arg3, arg4, (void *)**(int **)(temp_s0 + 72), arg7, arg8, arg5, arg6);
    } else {
        p2CopyFramebufferToTexture((P2Texture *)**(int **)(temp_s0 + 72), arg3, arg4, arg7, arg8, arg5, arg6, 0);
    }
    *(int *)(temp_s0 + 132) = 3;
    return 1;
}

void igPsx2VisualContext_CopyRenderDestinationToMemory(igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    FUN_00169e40((VisualContextTextures *)self, arg1, (TextureImage *)arg2, (void *)arg3, arg4, arg5, arg6, 0);
}

/* matching construct: a small sweep of spellings */
int FUN_00169e40(VisualContextTextures *self, int index, TextureImage *image, void *source, int sourceFormat, int width, int height, int flags) {
    void *pixels;
    TextureEntry *entry;
    entry = &self->textures->entries[index];
    pixels = image->pixels;
    bool allocated = false;
    int format;
    if (pixels == 0 || image->imageSize < 0 || ((int)pixels & 15) != 0) {
        pixels = ((BufferAllocator *)igVisualContext_GetImageMemoryPool((int *)self))->allocate(width * height * 4, 16);
        allocated = true;
    }
    if (entry->kind == 2) {
        FUN_00203c50(source, sourceFormat, width, height, entry->layout, pixels, flags);
        format = self->palettes->entries[entry->palette].format;
    } else {
        FUN_00203580(source, sourceFormat, width, height, 1, pixels, flags);
        if (entry->depth == 32) {
            format = 7;
        } else if (entry->depth == 24) {
            if (entry->indexed) {
                format = 7;
            } else {
                format = 5;
            }
        } else if (entry->depth == 15 || entry->depth == 16) {
            format = 8;
        } else {
            format = 7;
        }
    }
    if (allocated) {
        image->setPixels(pixels, format, 100, width, height);
        Memory_FreeBuffer(pixels);
    } else {
        ((Gap::Gfx::igImage *)image)->load(pixels, (IG_GFX_TEXTURE_FORMAT)format, width, height);
    }
    return 1;
}

void igPsx2VisualContext_SetViewport(igPsx2VisualContext *self, int arg1, int arg2, int arg3, int arg4, float fparg0, float fparg1) {
    self->_iViewportX = arg1;
    self->_iViewportY = arg2;
    self->_iViewportW = arg3;
    self->_iViewportH = arg4;
    self->_viewportNear = fparg0;
    self->_viewportFar = fparg1;
    if (self->_scissorType == 0) {
        FUN_0016a520((O520 *)self);
    }
    p2SetViewport(arg1, arg2, arg3, arg4, 1.0f - self->_viewportNear, 1.0f - self->_viewportFar);
}

void igPsx2VisualContext_GetViewport(igPsx2VisualContext *self, int *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = self->_iViewportX;
    *arg2 = self->_iViewportY;
    *arg3 = self->_iViewportW;
    *arg4 = self->_iViewportH;
}

void igPsx2VisualContext_GetViewportWithDepth(igPsx2VisualContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4, float *arg5, float *arg6) {
    *arg1 = arg0->_iViewportX;
    *arg2 = arg0->_iViewportY;
    *arg3 = arg0->_iViewportW;
    *arg4 = arg0->_iViewportH;
    *arg5 = arg0->_viewportNear;
    *arg6 = arg0->_viewportFar;
}

void igPsx2VisualContext_SetClearColor(igPsx2VisualContext *self, float *color) {
    self->_clearColor.set(color);
    int green = (unsigned int)(255.0f * self->_clearColor.vec[1]) << 8;
    self->_uiClearColor = ((unsigned int)(255.0f * ((128.0f * self->_clearColor.vec[3]) / 255.0f)) << 24)
        + (((unsigned int)(255.0f * self->_clearColor.vec[2]) << 16) + ((unsigned int)(255.0f * self->_clearColor.vec[0]) + green));
}

void igPsx2VisualContext_SetClearColorPacked(igPsx2VisualContext *self, unsigned int x) {
    int *a = (int *)self;
    a[224] = (x & 0xffffff) | (((x >> 1) & 0x7f000000) + (x & 0x01000000));
}

int igPsx2VisualContext_GetClearColorPacked(igPsx2VisualContext *self) {
    int temp_a1;
    unsigned int temp_a0;

    temp_a1 = self->_uiClearColor;
    temp_a0 = (unsigned int)(temp_a1 & 0x80000000) >> 7;
    return (temp_a1 & 0xFFFFFF) | (temp_a0 + (((temp_a1 & 0xFF000000) - temp_a0) * 2));
}

void igPsx2VisualContext_GetClearColor(igPsx2VisualContext *self, igVec4f *color) {
    Color4f_Unpack(color, 1, self->_uiClearColor);
}

void igPsx2VisualContext_SetClearDepth(igPsx2VisualContext *self, float fparg0) {
    S181 *arg0 = (S181 *)self;
    arg0->f892 = fparg0;
    if (arg0->f1280 & 4) {
        arg0->f900 = (unsigned)(2.1474836e9f * arg0->f892);
        return;
    }
    arg0->f900 = (unsigned)(2.1474836e9f * (1.0f - arg0->f892));
}

float igPsx2VisualContext_GetClearDepth(igPsx2VisualContext *self) {
    return self->_clearDepth;
}

void igPsx2VisualContext_SetClearStencil(igPsx2VisualContext *self, int a1) {
    *(int *)((char *)self + 904) = a1;
}

int igPsx2VisualContext_GetClearStencil(igPsx2VisualContext *self) {
    return self->_clearStencil;
}

/* Getter for the record field at +0x8 of buffer `bufferIndex`: the buffer format
 * (8/7/0x18/0xf/0x10). `_pBufList` (+0x364) is an igDataList whose data pointer
 * (+0x10) addresses 0x30-byte VRAM buffer records. */
int igPsx2VisualContext_GetColorBitsPerPixel(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 8);
}

/* Getter for the record field at +0x10 of buffer `bufferIndex`. `_pBufList` (+0x364) is an
 * igDataList whose data pointer (+0x10) addresses 0x30-byte VRAM buffer records. */
int igPsx2VisualContext_GetAlphaBitsPerPixel(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 16);
}

/* Getter for the record field at +0xc of buffer `bufferIndex`: the secondary format (0x20/0x18 in
 *. `_pBufList` (+0x364) is an igDataList whose data pointer (+0x10) addresses
 * 0x30-byte VRAM buffer records. */
int igPsx2VisualContext_GetDepthBitsPerPixel(igPsx2VisualContext *self, int bufferIndex) {
    igDataList *bufList = (igDataList *)self->_pBufList;
    return *(int *)(bufList->_data + bufferIndex * BUFFER_RECORD_SIZE + 12);
}

/* igPsx2VisualContext vtable slot 57: reads the word at +20 of one VRAM buffer record. _pBufList
 * is the context's table of 0x30-byte buffer records whose element array is at +16 (texture
 * capture). */

int igPsx2VisualContext_GetStencilBitsPerPixel(igPsx2VisualContext *self, int buffer_index) {
    return *(int *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + (buffer_index * VRAM_BUFFER_RECORD_SIZE))) + 20);
}

/* igPsx2VisualContext vtable slot 58: reads the float at +24 of one VRAM buffer record (companion
 * of slot 57, which reads the word at +20). _pBufList is the context's table of 0x30-byte buffer
 * records whose element array is at +16 (texture capture). */
float igPsx2VisualContext_GetPixelAspectRatio(igPsx2VisualContext *self, int buffer_index) {
    return *(float *)((char *)((*(int *)((char *)(self->_pBufList) + 16) + (buffer_index * VRAM_BUFFER_RECORD_SIZE))) + 24);
}

void FUN_0016a520(O520 *o) {
    R520 *r = (R520 *)((char *)o->l364->rects + o->idx * 0x30);
    if (r != 0) {
        if (o->f68 == 0) {
            int a = o->e398; int hi_y = r->y; int c = o->e3a0;
            c = H_1690d0::clampLen(c, hi_y - a);
            { int lo_x = o->e394; int hi_x = r->x; int w = o->e39c;
              w = H_1690d0::clampLen(w, hi_x - lo_x);
              a = H_1690d0::clampLow(a, hi_y);
              lo_x = H_1690d0::clampLow(lo_x, hi_x);
              p2SetScissor(lo_x, a, w, c); }
        } else {
            int a = o->e4d8; int hi_y = r->y; int c = o->e4e0;
            c = H_1690d0::clampLen(c, hi_y - a);
            { int lo_x = o->e4d4; int hi_x = r->x; int w = o->e4dc;
              w = H_1690d0::clampLen(w, hi_x - lo_x);
              a = H_1690d0::clampLow(a, hi_y);
              lo_x = H_1690d0::clampLow(lo_x, hi_x);
              p2SetScissor(lo_x, a, w, c); }
        }
    }
}

void igPsx2VisualContext_SetScissor(igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4) {
    int temp_a1;

    arg0->_scissorX = arg1;
    arg0->_scissorY = arg2;
    arg0->_scissorW = arg3;
    arg0->_scissorH = arg4;
    temp_a1 = arg0->_scissorType;
    if (temp_a1 == 1) {
        FUN_0016a520((O520 *)arg0);
    }
}

void igPsx2VisualContext_GetScissor(igPsx2VisualContext *self, int *arg1, int *arg2, int *arg3, int *arg4) {
    *arg1 = self->_scissorX;
    *arg2 = self->_scissorY;
    *arg3 = self->_scissorW;
    *arg4 = self->_scissorH;
}

void igPsx2VisualContext_SetScissorType(int a0, int a1) {
    *(int *)((char *)a0 + 104) = (int)a1;
    FUN_0016a520((O520 *)a0);
}

void FUN_0016a800(S0_1690d0 *arg0) {
    S_temp_a0 *temp_a0;
    temp_a0 = (S_temp_a0 *)(arg0->f4);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
    arg0->f4 = 0;
    arg0->f8 = 0;
    arg0->f14 = 0;
}

void FUN_0016a860(Arg *arg0) {
    int sp5C;
    int i;
    P_1690d0 *p;
    int n;
    int v;
    int *old;
    int *s3;
    Buf860 *b;
    sp5C = 64;
    igGetRegistryValue_Int((igRegistry *)(*(int *)((char *)g_objectSystem + 56)), 4, "IG_GFX_VC_CLUT_ARRAY_SIZE", &sp5C, 64, 0);
    p = (P_1690d0 *)Memory_AllocateBufferDirect(20, (igMemoryPoolView *)igVisualContext_GetListMemoryPool((int *)arg0));
    if (p != 0) {
        n = sp5C;
        p->f8 = 0;
        if (g_stringPool == 0) {
            v = (int)StringPool_Allocate(16);
            if (v != 0) {
                v = (int)StringPool_Construct((StringPool *)v);
            }
            g_stringPool = (StringPool *)v;
        }
        s3 = (int *)StringPool_Intern(g_stringPool, "IG_GFX_VC_CLUT_ARRAY_SIZE");
        old = p->f8;
        if (old != 0) {
            int *a1 = old - 2;
            int v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
            }
        }
        p->f8 = s3;
        if (n == 0) {
            n = 1;
        }
        b = (Buf860 *)Memory_FindBufferOwner(p);
        p->f16 = b->vA(n, 24, 16);
        p->f12 = b->vB(n, 2);
        i = 0;
        p->f2 = n;
        p->f0 = n;
        p->f4 = n;
        while (i < n) {
            p->f12[i] = i;
            i = i + 1;
        }
    }
    arg0->f328 = p;
    arg0->f344 = -1;
}

void FUN_0016a9f0(igPsx2VisualContext *arg0, int arg1) {
    int s0, s2, v, old;
    int *hd;
    T9f0 *t;
    s0 = ((T9f0 *)arg0->_pClutList)->f0 - 1;
    for (; s0 > -1; s0--) {
        if (((T9f0 *)arg0->_pClutList)->Chk(s0)) {
            FUN_0016ab80((Oab80 *)arg0, s0);
        }
    }
    if (arg1 == 0) {
        t = (T9f0 *)arg0->_pClutList;
        if (t != 0) {
            if (g_stringPool == 0) {
                v = (int)StringPool_Allocate(16);
                if (v != 0) {
                    v = (int)StringPool_Construct((StringPool *)v);
                }
                g_stringPool = (StringPool *)v;
            }
            s2 = (int)StringPool_Intern(g_stringPool, 0);
            old = t->f8;
            if (old != 0) {
                hd = (int *)(old - 8);
                v = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                }
            }
            t->f8 = s2;
            Memory_FreeBuffer((void *)t->f16);
            Memory_FreeBuffer((void *)((int)t->f12));
            if (&t->f8 != 0) {
                old = t->f8;
                if (old != 0) {
                    hd = (int *)(old - 8);
                    v = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = v;
                    if (v == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                    }
                }
            }
            Memory_FreeBufferAliasB(t);
        }
        arg0->_pClutList = 0;
    }
}

void FUN_0016ab80(Oab80 *arg0, int arg1) {
    Tab80 *t;
    E_1690d0 *e;
    RC_1690d0 *r;
    t = arg0->f328;
    if (t->Chk(arg1)) {
        e = (E_1690d0 *)((char *)t->f16 + arg1 * 24);
        if (e->f8 != 0) {
            FUN_0016b1d0((OB1d0 *)arg0, arg1);
        }
        r = e->f4;
        if (r != 0) {
            --r->refs;
            if (!(r->refs & 0x7fffff)) igObject_Destroy((igObject *)r);
        }
        e->f4 = 0;
        if (e->f16 != 0) {
            Memory_FreeBuffer((void *)e->f16);
        }
        t = arg0->f328;
        if (arg1 < t->f0 && arg1 >= 0) {
            if (t->f4 >= t->f2) {
                VO *ow = (VO *)Memory_FindBufferOwner(t);
                t->f2 = t->f2 + 8;
                t->f12 = (unsigned short *)ow->v58(t->f12, t->f2 * 2);
            }
            t->f12[t->f4] = arg1;
            t->f4 = t->f4 + 1;
        }
    }
}

int FUN_0016ad20(ObjAd20 *arg0, int arg1, int arg2) {
    PoolAd20 *p;
    EntAd20 *e;
    int s0;
    int i;
    if (arg1 > 256) {
        return -1;
    }
    p = arg0->f328;
    if (p->f4 <= 0) {
        p->f16 = (EntAd20 *)Memory_ReallocateAlignedAlias(p->f16, (p->f0 + 4) * 24, 16);
        memset(p->f16 + p->f0, 0, 96);
        if (p->f2 < 4) {
            Buf46 *b = (Buf46 *)Memory_FindBufferOwner(p);
            p->f12 = b->vB(p->f12, 8);
            p->f2 = 4;
        }
        i = 0;
        do {
            p->f12[i] = p->f0 + i;
            i++;
        } while (i < 4);
        p->f4 = 4;
        p->f0 = p->f0 + 4;
    }
    s0 = p->f12[p->f4 - 1];
    p->f4 = p->f4 - 1;
    e = arg0->f328->f16 + s0;
    FUN_0016a800((S0_1690d0 *)e);
    e->f20 = 0;
    e->f12 = arg2;
    e->f0 = arg1;
    e->f16 = 0;
    return s0;
}

void FUN_0016aea0(int arg0, int arg1, int *arg2, int *arg3) {
    int *var_a2;
    int *var_a3;
    int temp_v1;
    int var_a1;
    int var_a1_2;

    var_a2 = arg2;
    var_a3 = arg3;
    switch (arg1) {
    case 0:
        var_a1 = 0;
        do {
            var_a1 += 1;
            *var_a2 = *var_a3;
            var_a3 += 1;
            var_a2 += 1;
        } while (var_a1 < 0x10);
        return;
    case 1:
        var_a1_2 = 0;
        do {
            temp_v1 = (var_a1_2 & 0xE7) | (((var_a1_2 >> 1) & 8) | ((var_a1_2 & 8) * 2));
            var_a1_2 += 1;
            *var_a2 = *(var_a3 + temp_v1);
            var_a2 += 1;
        } while (var_a1_2 < 0x100);
        return;
    }
}

void FUN_0016af30(A_1690d0 *arg0, int arg1, RAf30 *arg2) {
    EntAf30 *e;
    int n;
    RAf30 *t;
    void **o;
    e = &arg0->f148->f10[arg1];
    if (arg2 != 0) {
        arg2->f4 = arg2->f4 + 1;
    }
    t = e->f4;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)t);
        }
    }
    e->f4 = arg2;
    e->f14 = 0;
    n = 256;
    if (arg0->f5bc != 0 && e->f0 < 17) {
        e->fc = 0;
        n = 16;
    }
    if (e->f10 != 0 && e->f8 != 0) {
        p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)p2GetImageTexture((p2Image *)e->f8)));
    } else if (e->f10 == 0) {
        o = (void **)igVisualContext_GetImageMemoryPool((int *)arg0);
        e->f10 = ((VC_220 *)o)->vX(n * 4, 128);
    }
    if (e->f10 != 0) {
        arg2->f1c = 1;
        FUN_0016aea0((int)arg0, e->fc, (int *)e->f10, (int *)arg2->f14);
    }
}

bool FUN_0016b090(Ob *arg0, int arg1) {
    int sp5C;
    bool v;
    int h;
    int r;
    RB090 *s;
    Q_1690d0 *q;
    s = arg0->f328->f16 + arg1;
    v = true;
    if (s->f8 == 0 || s->f4->f28 != 0) {
        if (s->f8 != 0) {
            h = (int)p2GetImageTexture((p2Image *)s->f8);
            p2InvalidateTexture((P2Texture *)h);
            p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)h));
            q = s->f4;
            q->f28 = 1;
            FUN_0016aea0((int)arg0, s->f12, (int *)s->f16, (int *)q->f20);
        } else {
            s->f8 = (int)p2CreateImage(DAT_0048a4e0[s->f12], 0, DAT_0048a4ec[0], (void *)s->f16);
        }
        s->f4->f28 = 0;
    }
    if (s->f20 != 5) {
        sp5C = (int)p2GetImageTexture((p2Image *)s->f8);
        v = FUN_0020bb20((P2Texture **)&sp5C, 0, 0) != 0;
    }
    s->f20 = 4;
    return v;
}

void FUN_0016b1d0(OB1d0 *arg0, int arg1) {
    TB1d0 *t;
    int h;
    E8 *e;
    t = arg0->f328;
    if (t->Chk(arg1)) {
        e = t->f16 + arg1;
        if (e->w8 != 0) {
            h = (int)p2GetImageTexture((p2Image *)e->w8);
            p2WaitDmaSequence(2, p2GetTextureUploadSequence((P2Texture *)h));
            p2FreeTexture((P2Texture *)h);
            p2FreeImage((p2Image *)e->w8);
        }
        e->w8 = 0;
        arg0->f344 = -1;
    }
}

/* The override is a jump to igVisualContext's constructFields: the callee takes the caller's
 * registers untouched. */

void igPsx2VisualContext_constructFields(igVisualContextFieldsView *self, int flags) {
    igVisualContext_constructFields(self, flags);
}

void igPsx2VisualContext_userDestruct(S10 *arg0) {
    int temp_a0;

    temp_a0 = arg0->f50;
    if (temp_a0 != 0) {
        Memory_FreeBuffer((void *)temp_a0);
        arg0->f50 = 0;
    }
    FUN_00169260((igPsx2VisualContext *)arg0, 0);
    FUN_0017a540((igPsx2VisualContext *)arg0, 0);
    FUN_0016a9f0((igPsx2VisualContext *)arg0, 0);
    FUN_00170510((Obj_170510 *)arg0, 0);
    FUN_0016c650((igPsx2VisualContext *)arg0, 0);
    FUN_001788e0((StatContext88 *)arg0, 0);
    if (arg0->f142 != 0) {
        p2CloseDisplay();
    }
    FUN_00165bb0((char *)arg0);
}

/* The buffer-format record _pBufList holds per buffer (BUFFER_RECORD_SIZE bytes). */
struct BufferRecord {
    int width;
    int height;
    int colorBits;
    int depthBits;
    int stencilBits;
    int f20;
    int f24;
    int kind;
    char pad32[16];
};
struct BufferRecordList {
    unsigned short count;
    unsigned short f2;
    unsigned short reserved;
    unsigned short f6;
    char pad8[8];
    BufferRecord *data;
};
/* _videoMode: display timing the context opens with. */
struct OpenVideoMode {
    unsigned char f0;
    unsigned char custom;
    short pad2;
    int frameCount;
    int frameMode;
    float refreshRate;
    int f16;
    int standard;
};
/* igPsx2VisualContext as its open slot sees it. */
class OpenContext {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void openBase(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual int getColorBits(int buffer); virtual int getStencilBits(int buffer); virtual int getDepthBits(int buffer);
    char pad4[318];
    unsigned char _iContextOpen;       /* +322 */
    char pad323[545];
    BufferRecordList *_pBufList;       /* +868 */
    int _currentBuf;                   /* +872 */
    char pad876[32];
    int _iDisplayWidth;                /* +908 */
    int _iDisplayHeight;               /* +912 */
    char pad916[432];
    OpenVideoMode _videoMode;          /* +1348 */
    char pad1372[100];
    int _maxStageNum;                  /* +1472 */
    BufferRecord *bufferRecord(int i) { return &_pBufList->data[i]; }
};
struct ContextText : public igObject {
    const char *_text;
    int _length;
    const char *text() const {
        const char *t = _text;
        if (t == 0) t = (const char *)g_stringObjEmptyText;
        return t;
    }
};
#include "dw4/p2/p2core.h"
#include "dw4/p2/p2swap.h"
extern "C" int p2OpenDisplay(int mode, int colorBits, int depthBits, const char *config, const char *symbols, int width, int height);
class OpenResult {
public:
    int v;
    OpenResult(int x) : v(x) {}
    OpenResult(const OpenResult &o) : v(o.v) {}
};
extern "C" OpenResult igPsx2VisualContext_Open(OpenContext *self);

OpenResult igPsx2VisualContext_Open(OpenContext *self) {
    BufferRecord *record;
    igRegistry *registry;
    int colorBits;
    int stencilBits;
    int depthBits;
    bool useWatchdog;
    int width;
    int height;

    self->openBase();
    igSmartPointer<ContextText> ucodeConfig((ContextText *)igStringObj_Create(igVisualContext_GetInternalMemoryPool((int *)self)));
    igSmartPointer<ContextText> ucodeSym((ContextText *)igStringObj_Create(igVisualContext_GetInternalMemoryPool((int *)self)));
    int size;
    int syncMode;
    record = self->bufferRecord(self->_currentBuf);
    if (record->kind != 0 && record->kind != 1 && record->kind != 2) {
        BufferRecordList *list = self->_pBufList;
        record = 0;
        for (int i = 0; i < list->count - list->reserved; i++) {
            record = self->bufferRecord(i);
            if (record->kind == 0 || record->kind == 1 || record->kind == 2) {
                self->_currentBuf = i;
                break;
            }
        }
    }
    if (record == 0) {
        return OpenResult(g_resultFailure.v);
    }
    if (self->_videoMode.custom == 1) {
        if (self->_videoMode.frameMode == 0) {
            p2SetFrameMode(0);
        } else if (self->_videoMode.frameMode == 1) {
            p2SetFrameMode(1);
        }
        p2SetDisplayFrameCount(self->_videoMode.frameCount);
    } else {
        p2SetFrameMode(0);
        p2SetDisplayFrameCount(2);
    }
    if (self->_videoMode.refreshRate < 40.0f) {
        p2SetSwapInterval(1);
    }
    colorBits = self->getColorBits(self->_currentBuf);
    stencilBits = self->getStencilBits(self->_currentBuf);
    depthBits = self->getDepthBits(self->_currentBuf);
    if (colorBits >= 32 || colorBits <= 0) {
        colorBits = 32;
    } else if (colorBits >= 24) {
        colorBits = 24;
    } else {
        colorBits = 16;
    }
    if (stencilBits >= 8) {
        stencilBits = 8;
    } else if (stencilBits >= 6) {
        stencilBits = 6;
    } else if (stencilBits >= 4) {
        stencilBits = 4;
    } else {
        stencilBits = 0;
    }
    if (depthBits >= 32) {
        depthBits = 32;
    } else if (depthBits >= 24) {
        depthBits = 24;
    } else {
        depthBits = 16;
    }
    record->colorBits = colorBits;
    record->stencilBits = stencilBits;
    record->depthBits = depthBits;
    record->f20 = 0;
    registry = (igRegistry *)((G_1778e0 *)g_objectSystem)->f56;
    igGetRegistryValue_StringObj(registry, 4, "ucodeConfig", (igStringObj **)&ucodeConfig, "", 0);
    igGetRegistryValue_StringObj(registry, 4, "ucodeSym", (igStringObj **)&ucodeSym, "", 0);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_CLUT_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(3, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMAPREDICATE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(7, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMACOMPLETION_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(8, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_FINISH_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(9, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_TEXTURE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(10, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF0_SIZE_PSX2", &size, -1, 0);
    if (size >= 0) p2SetPoolSize(4, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF1_SIZE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(5, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_GIF_SIZE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(6, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF0_PSX2", &size, -1, 0);
    if (size >= 0) p2SetPoolSize(0, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_VIF1_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(1, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_DMABUFFER_GIF_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(2, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_STATE_CACHE_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(11, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_MULTIPASS_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(12, size);
    igGetRegistryValue_Int(registry, 4, "IG_GFX_INTERNAL_STRUCT_RENDERLIST_PSX2", &size, -1, 0);
    if (size > 0) p2SetPoolSize(13, size);
    ((Gap::Core::igRegistry *)registry)->getValue(4, "IG_GFX_CAPABILITY_MAX_TEXTURE_STAGES", *(int *)(&self->_maxStageNum), 1, 0);
    self->_maxStageNum = self->_maxStageNum < 16 ? self->_maxStageNum : 16;
    self->_maxStageNum = self->_maxStageNum > 1 ? self->_maxStageNum : 1;
    syncMode = 0;
    ((Gap::Core::igRegistry *)registry)->getValue(4, "IG_GFX_TEXTURE_SYNC_MODE_PSX2", syncMode, 1, 0);
    p2SetTextureWaitMode(syncMode);
    useWatchdog = true;
    ((Gap::Core::igRegistry *)registry)->getValue(4, "useWatchdog", *(unsigned char *)&useWatchdog, 1, 0);
    p2EnableWatchdog(useWatchdog);
    FUN_00179e00((StatContext *)self);
    {
        int bits = colorBits + stencilBits;
        bits = bits < 32 ? bits : 32;
        int standard = self->_videoMode.standard;
        if (standard != 2 && standard != 3) {
            if (standard == 0) {
                int mode;
                switch (record->width) {
                case 256: mode = 0; break;
                case 320: mode = 1; break;
                case 384: mode = 2; break;
                case 512: mode = 3; break;
                default:
                    mode = 4;
                    record->width = 640;
                    record->height = 448;
                    break;
                }
                const char *config = ucodeConfig->text();
                const char *symbols = ucodeSym->text();
                p2OpenDisplay(mode, bits, depthBits, config, symbols, record->width, record->height);
            } else if (self->_videoMode.standard == 1) {
                int mode;
                switch (record->width) {
                case 256: mode = 5; break;
                case 320: mode = 6; break;
                case 384: mode = 7; break;
                case 512: mode = 8; break;
                default:
                    mode = 9;
                    record->width = 640;
                    record->height = 576;
                    break;
                }
                const char *config = ucodeConfig->text();
                const char *symbols = ucodeSym->text();
                p2OpenDisplay(mode, bits, depthBits, config, symbols, record->width, record->height);
            }
        }
    }
    p2GetDisplaySize(&width, &height, 0, 0);
    self->_iDisplayWidth = width;
    self->_iDisplayHeight = height;
    {
        bool slowSpotLight;
        if (igGetRegistryValue_Bool(registry, 4, "useSlowSpotLight", (unsigned char *)&slowSpotLight, 0, 0) != 0 && slowSpotLight) {
            p2DisableCapability(24);
        } else {
            p2EnableCapability(24);
        }
    }
    {
        bool eyeLocalLight;
        igGetRegistryValue_Bool(registry, 4, "useEyeLocalLight", (unsigned char *)&eyeLocalLight, 0, 0);
        if (eyeLocalLight) p2EnableCapability(20); else p2DisableCapability(20);
    }
    {
        bool cpuLightLoading;
        igGetRegistryValue_Bool(registry, 4, "useCpuLightLoading", (unsigned char *)&cpuLightLoading, 0, 0);
        if (cpuLightLoading) p2EnableCapability(21); else p2DisableCapability(21);
    }
    {
        bool lock;
        igGetRegistryValue_Bool(registry, 4, "lockDMAVif1", (unsigned char *)&lock, 0, 0);
        if (lock) p2FixDmaPacketPool(1);
        igGetRegistryValue_Bool(registry, 4, "lockDMAGif", (unsigned char *)&lock, 0, 0);
        if (lock) p2FixDmaPacketPool(2);
    }
    {
        bool showGuardBand;
        igGetRegistryValue_Bool(registry, 4, "showGuardBand", (unsigned char *)&showGuardBand, 0, 0);
        if (showGuardBand) p2SetClearPasses(1);
    }
    FUN_00174090(self);
    self->_iContextOpen = 1;
    FUN_0017a7e0((S0_17a070 *)self);
    return OpenResult(g_resultSuccess.v);
}

void igPsx2VisualContext_Reset(Obj35 *arg0) {
    igVisualContext_Reset(arg0);
    arg0->rel(arg0->m940);
    arg0->rel(arg0->m944);
    arg0->rel(arg0->m948);
}

int igPsx2VisualContext_GetCapability(igPsx2VisualContext *context, unsigned int query) {
    switch (query) {
    case 0:
        return 640;
    case 1:
        return 448;
    case 2:
        return 24;
    case 3:
        return 8;
    case 4:
        return 32;
    case 5:
        return 0;
    case 6:
        return 0;
    case 8:
        return 1;
    case 22:
        return context->_maxStageNum;
    case 7:
        return 1024;
    case 9:
        return 8;
    case 10:
        return 1;
    case 11:
        return 0;
    case 12:
        return 1;
    case 13:
        return 4;
    case 14:
        return 0;
    case 15:
        return 0;
    case 16:
        return 0;
    case 17:
        return 0;
    case 23:
        return 1;
    case 21:
        return 0;
    case 28:
    default:
        return 0;
    }
}

/* matching construct: dummy-virtual view so ->v772() dispatches through vtable slot 193 of the context */
void FUN_0016c650(igPsx2VisualContext *arg0, int arg1) {
    int s0, s2, v, old;
    int *hd;
    T650 *t;
    s0 = ((T650 *)arg0->_pDLists)->f0 - 1;
    for (; s0 > -1; s0--) {
        ((VO650 *)arg0)->v772(s0);
    }
    if (arg1 == 0) {
        t = (T650 *)arg0->_pDLists;
        if (t != 0) {
            if (g_stringPool == 0) {
                v = (int)StringPool_Allocate(16);
                if (v != 0) {
                    v = (int)StringPool_Construct((StringPool *)v);
                }
                g_stringPool = (StringPool *)v;
            }
            s2 = (int)StringPool_Intern(g_stringPool, 0);
            old = t->f8;
            if (old != 0) {
                hd = (int *)(old - 8);
                v = *(int *)(old - 4) - 1;
                *(int *)(old - 4) = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                }
            }
            t->f8 = s2;
            Memory_FreeBuffer((void *)t->f16);
            Memory_FreeBuffer((void *)t->f12);
            if (&t->f8 != 0) {
                old = t->f8;
                if (old != 0) {
                    hd = (int *)(old - 8);
                    v = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = v;
                    if (v == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
                    }
                }
            }
            Memory_FreeBufferAliasB(t);
        }
        arg0->_pDLists = 0;
    }
}

int igPsx2VisualContext_CreateRenderList(igPsx2VisualContext *self) {
    O192 *arg0 = (O192 *)self;
    int a1;
    T192 *s1 = arg0->f960;
    int s0;
    if (s1->f4 <= 0) {
        s1->f16 = (Ent192 **)Memory_ReallocateAlignedAlias(s1->f16, (s1->f0 + 4) * 4, 16);
        memset(s1->f0 + s1->f16, 0, 16);
        if (s1->f2 < 4) {
            VM *o = (VM *)Memory_FindBufferOwner(s1);
            s1->f12 = (unsigned short *)o->v232(s1->f12, 8);
            s1->f2 = 4;
        }
        a1 = 0;
        do {
            int t = s1->f0; t = t + a1; s1->f12[a1] = t;
            a1++;
        } while (a1 < 4);
        s1->f4 = 4;
        s1->f0 = s1->f0 + 4;
    }
    s0 = s1->f12[s1->f4 - 1];
    s1->f4 = s1->f4 - 1;
    {
        Nd192 *n = new (igVisualContext_GetDriverDataMemoryPool((int *)arg0)) Nd192;
        int v = (int)(igIntList_Create(igVisualContext_GetDriverDataMemoryPool((int *)arg0)));
        arg0->f960->f16[s0] = (Ent192 *)n;
        n->a = v;
    }
    arg0->f968 = 0;
    return s0;
}

void igPsx2VisualContext_DeleteRenderList(igPsx2VisualContext *self, int arg1) {
    T193 *a3;
    int s0;
    Rc193 *s2;
    int s1;
    bool ok;
    int a2, a1;
    a3 = ((T193 *)self->_pDLists);
    if (arg1 < a3->f0) {
        ok = false;
        if (arg1 >= 0) {
            a1 = a3->f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (arg1 == a3->f12[a2]) {
                    ok = false;
                    goto done;
                }
            }
            ok = true;
        }
    } else {
        ok = false;
    }
done:
    if (ok & 0xFF) {
        s0 = arg1 * 4;
        s2 = a3->f16[arg1]->list;
        for (s1 = 0; s1 < s2->count; s1++) {
            p2ReleaseDisplayList((p2DisplayList *)s2->data[s1]);
        }
        --s2->refs;
        if ((s2->refs & 0x7fffff) == 0) {
            igObject_Destroy((igObject *)s2);
        }
        Memory_FreeBufferAliasB(((T193 *)self->_pDLists)->f16[arg1]);
        ((T193 *)self->_pDLists)->Add(arg1);
    }
}

void igPsx2VisualContext_BeginRenderListDraw(igPsx2VisualContext *self, int arg1) {
    *(int *)((char *)(self) + 964) = arg1;
    if (*(int *)((char *)(self) + 72) < 0x10) {
        p2SetBlendMatrices(0, 0x10);
    }
}

int igPsx2VisualContext_EndRenderListDraw(igPsx2VisualContext *self) {
    int temp_a1;
    temp_a1 = *(int *)((char *)(self) + 72);
    if (temp_a1 > 0) {
        p2SetBlendMatrices(*(int *)((char *)(self) + 84), temp_a1);
    }
    *(int *)((char *)(self) + 964) = -1;
    return *(unsigned char *)((char *)(self) + 968) == 0;
}

bool igPsx2VisualContext_ExecuteRenderList(igPsx2VisualContext *arg0, int arg1) {
    struct L196 *temp_s4;
    int temp_v0;
    int var_s2;
    int var_s1;
    int temp_v0_2;

    temp_s4 = *((struct T196 *)arg0->_pDLists)->tab[arg1];
    if (temp_s4->n > 0) {
        temp_v0 = FUN_00177010(arg0, 0, 0, temp_s4->a[0], arg1);
        if ((temp_v0 == 1) || (temp_v0 == 3)) {
            return false;
        }
        var_s2 = 0;
        if (temp_v0 == 2) {
            var_s2 = p2GetDisplayListBlendWeightCount((p2DisplayList *)temp_s4->a[0]);
        }
        for (var_s1 = 0; var_s1 < temp_s4->n; var_s1 += 1) {
            temp_v0_2 = p2GetDisplayListBlendWeightCount((p2DisplayList *)temp_s4->a[var_s1]);
            if ((temp_v0 == 2) && (var_s2 != temp_v0_2)) {
                p2SetBlendWeightCount(temp_v0_2, temp_v0_2);
            }
            p2CallDisplayList((p2DisplayList *)temp_s4->a[var_s1]);
        }
    }
    return true;
}

void FUN_0016cc50(int a0, int a1)
{
    *(int *)((char *)a0 + 1400) = a1;
}

static inline int count_of(const IntList *list) { return list->_count; }

void FUN_0016cc60(char *arg0) {
    int idx;
    IntList *list;
    int top;
    int value;
    idx = *(int *)(arg0 + 964);
    if (idx >= 0) {
        list = **(IntList ***)(*(int *)(*(int *)(arg0 + 960) + 16) + idx * 4);
        value = (int)(p2BeginDisplayList(*(int *)((char *)DAT_0048a4f0 + *(int *)(arg0 + 1400) * 4)));
        top = count_of(list);
        if (top < list->_capacity) {
            list->_count = list->_count + 1;
        } else {
            ((Gap::Core::igDataList *)list)->resizeAndSetCount(top + 1, 4);
        }
        list->_data[top] = value;
    }
}

void FUN_0016cd10(void *arg0) {
    if (*(int *)((char *)arg0 + 964) >= 0) {
        p2EndDisplayList();
    }
}

void igPsx2VisualContext_DetectDriverDatabaseProperties(int dummy0, int arg1) {
    igDriverDatabase_SetCurrentProperty((void *)arg1, 1, "psx2");
    igDriverDatabase_SetCurrentProperty((void *)arg1, 2, "1.0");
    igDriverDatabase_SetCurrentProperty((void *)arg1, 3, "sony");
    igDriverDatabase_SetCurrentProperty((void *)arg1, 4, "psx2");
    igDriverDatabase_SetCurrentProperty((void *)arg1, 5, "1.0");
}

void igPsx2VisualContext_CallDmaChain(igPsx2VisualContext *self, void *packet, int size, int flush) {
    p2CallGifChain((unsigned int)packet, size, flush);
}

int igPsx2VisualContext_IsDisplayingFirstBuffer(igPsx2VisualContext *self) {
    return swapbuffersDrawPredicate(1);
}
