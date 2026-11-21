char *igTextureAttr_GetFileName(char *arg0) {
    char *p;
    char c;

    if (arg0 == 0) {
        return 0;
    }
    p = arg0 + strlen(arg0);
    for (; arg0 < p; p--) {
        c = p[-1];
        if (c == 0x5C || c == 0x2F) {
            break;
        }
    }
    return p;
}

static inline void retain(Image *o) { igObject::ref(o); }

static inline unsigned magFilter(const TextureAttr *a) { return a->magFilter; }

static inline unsigned minFilter(const TextureAttr *a) { return a->minFilter; }

static inline unsigned wrapS(const TextureAttr *a) { return a->wrapS; }

static inline unsigned wrapT(const TextureAttr *a) { return a->wrapT; }

int Gap__Attrs__igTextureAttr__vfunc_37(TextureAttr *attr, int unused, Allocator *allocator) {
    char text[8204];
    if (allocator == 0) {
        allocator = (Allocator *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleDefault);
    }
    igSmartPointer<Image> image((Image *)igTextureAttr_GetImage((igTextureAttr *)attr, 0), kRetainReference);
    const char *name = "NO_IMAGE";
    if (image.p != 0) {
        if (image.p->name != 0) {
            name = igTextureAttr_GetFileName((char *)image.p->name);
        }
    }
    sprintf(text, "%s %d %d %d %d %d %d %d %d", name, attr->bColor, magFilter(attr), minFilter(attr), wrapS(attr), wrapT(attr), (long long)attr->mipmapMode, (long long)attr->source, (long long)attr->paging);
    int copy = allocator->allocate(strlen(text) + 1);
    strcpy((char *)copy, text);
    return copy;
}

int Gap__Attrs__igTextureAttr__vfunc_38(Arg *arg0, int arg1) {
    int sp206C;
    int sp2068;
    int sp2064;
    int sp2060;
    int sp205C;
    int sp2058;
    int sp2054;
    int sp2050;
    char sp50[8192];
    const char *var_a1;
    const char *var_s1;

    if (sscanf((const char *)arg1, "%s %d %d %d %d %d %d %d %d", sp50, &sp206C, &sp2068, &sp2064, &sp2060, &sp205C, &sp2058, &sp2054, &sp2050) != 9) {
        return 0;
    }
    var_s1 = "NO_IMAGE";
    var_a1 = "NO_IMAGE";
    if (igTextureAttr_GetImage((igTextureAttr *)arg0, 0) != 0) {
        if (((T_140740 *)igTextureAttr_GetImage((igTextureAttr *)arg0, 0))->f88 != 0) {
            var_s1 = (igTextureAttr_GetFileName((char *)((T_140740 *)igTextureAttr_GetImage((igTextureAttr *)arg0, 0))->f88));
        }
        var_a1 = var_s1;
    }
    if (strcmp(sp50, var_a1) == 0) {
        if (sp206C == arg0->f16) {
            if ((sp2068 == arg0->f20) && (sp2064 == arg0->f24) && (sp2060 == arg0->f28) && (sp205C == arg0->f32) && (sp2058 == arg0->f40) && (sp2054 == arg0->f44) && (sp2050 == arg0->f52)) {
                return 1;
            }
        }
    }
    return 0;
}

void igTextureAttr_SynchronizeDefault(void) {

}

void igTextureAttr_UserPostLoad(S0 *arg0) {
    if (arg0->f3C == 0) {
        arg0->f3C = 1;
    }
    igAttr_UserPostLoad(arg0);
}

void igTextureAttr_apply(igTextureAttr *self, igObject *context) {
    if (self->_texId < 0) {
        igImage *image;
        switch (self->_source) {
        case 0:
        case 1:
        default: {
            int level;
            image = (igImage *)self->_image;
            if (image == 0) {
                return;
            }
            self->_texId = Gap__Gfx__igPsx2VisualContext__createTexture((igPsx2VisualContext *)context, image->_px, image->_py, image->_pfmt, 0, self->_mipmapMode, self->_imageCount);
            for (level = 0; level < self->_imageCount; level++) {
                igImage *levelImage;
                if (level == 0) {
                    levelImage = (igImage *)self->_image;
                } else {
                    levelImage = ((igImage **)((igObjectList *)self->_imageMipMaps)->_data)[level - 1];
                }
                igPsx2VisualContext_SetTextureSourceLevel(context, self->_texId, levelImage, level);
            }
            break;
        }
        case 2:
            image = (igImage *)self->_image;
            if (image == 0) {
                return;
            }
            self->_texId = Gap__Gfx__igPsx2VisualContext__createTexture((igPsx2VisualContext *)context, image->_px, image->_py, image->_pfmt, 2, 0, 1);
            break;
        case 3:
        case 4:
            image = (igImage *)self->_image;
            if (image == 0) {
                return;
            }
            self->_texId = Gap__Gfx__igPsx2VisualContext__createTexture((igPsx2VisualContext *)context, image->_px, image->_py, image->_pfmt, 3, 0, 1);
            break;
        }
        igObject::ref(context);
        igRelease((igObject *)self->_vc);
        self->_vc = (int)context;
    }
    if (self->_source == 2) {
        igPsx2VisualContext_SetTextureSourceFromBuffer((igPsx2VisualContext *)context, self->_texId, self->_videoBuffer);
    }
    igPsx2VisualContext_SetTextureAddressingMode((igPsx2VisualContext *)context, self->_texId, (IG_GFX_TEXTURE_WRAP)self->_wrapS, (IG_GFX_TEXTURE_WRAP)self->_wrapT);
    igPsx2VisualContext_SetTextureMinificationFilter((igPsx2VisualContext *)context, self->_texId, (IG_GFX_TEXTURE_FILTER)self->_minFilter);
    igPsx2VisualContext_SetTextureMagnificationFilter((igPsx2VisualContext *)context, self->_texId, (IG_GFX_TEXTURE_FILTER)self->_magFilter);
}

void igTextureAttr_SetImage(igTextureAttr *self, igImage *image, int level) {
    T_140ad0 *arg0 = (T_140ad0 *)self;
    L_140ad0 *s1;
    int s0;
    int n;
    int *a0;
    int v1;
    int *a0b;
    if (level == 0) {
        igObject::ref(image);
        a0 = arg0->f48;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)a0);
            }
        }
        arg0->f48 = (int *)image;
        return;
    }
    if (arg0->f64->n == 0) {
        ((Gap::Core::igObjectList *)arg0->f64)->setCount(arg0->f60 - 1);
    }
    s1 = arg0->f64;
    igObject::ref(image);
    s0 = level * 4;
    a0b = *(int **)((char *)s1->d + s0 - 4);
    if (a0b != 0) {
        a0b[1] = a0b[1] - 1;
        if ((a0b[1] & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)a0b);
        }
    }
    n = s1->n;
    v1 = level - 1;
    if (n != 0 && v1 >= 0 && v1 < n) {
        *(int **)(s0 + (int)s1->d - 4) = (int *)image;
    }
}

igImage *igTextureAttr_GetImage(igTextureAttr *self, int level) {
    if (level == 0) {
        return (igImage *)self->_image;
    }
    return ((igImage **)((igImageMipMapList *)self->_imageMipMaps)->_data)[level - 1];
}

void igTextureAttr_ReleaseDefaults(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    igObject_ReleaseDefaults((igObject *)arg0);
}

void igTextureAttr_Reset(S_140c70 *arg0) {
    int temp_a1;
    R_140c70 *t;

    temp_a1 = arg0->f36;
    if (temp_a1 != -1) {
        if (arg0->f12 != 0) {
            arg0->f12->vX(temp_a1);
        }
    }
    arg0->f36 = -1;
    t = arg0->f12;
    if (t != 0) {
        t->refs = t->refs - 1;
        if ((t->refs & 0x7fffff) == 0) {
            igObject_Destroy((igObject *)t);
        }
    }
    arg0->f12 = 0;
}

