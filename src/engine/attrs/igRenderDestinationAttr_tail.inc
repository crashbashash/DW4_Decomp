/* igTextureAttr as a render-target texture: slot 28 releases its texture handle (`_texId`). */
class RenderTargetTextureView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25();
    virtual void release();
    unsigned int _refCount;
    char _pad8[28];
    int _texId;      /* +36 */
    int _mipmapMode; /* +40 */
    int _source;     /* +44 */
};

/* igRenderDestinationAttr (reflected layout) with its vptr: slot 24 is apply(). */
class RenderDestinationAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void apply(igObject *context);
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    int _iCreateMode;
    int _iTexCreateMode;
    int _iRDHandle;
    unsigned char _bEnabled;
    int _iPrevRDHandle;
    RenderTargetTextureView *_pTex;
    int _iType;
    int _iSizeX;
    int _iSizeY;
    int _iColorBitCount;
    int _iAlphaBitCount;
    int _iDepthBitCount;
    int _iStencilBitCount;
    igSmartPointer<igObject> _vc;
};

/* apply: create the render destination on first use (copying the current one's format unless
 * `_iCreateMode` is 1, or adopting it when 2), then hold the context. */
extern "C" void Gap__Attrs__igRenderDestinationAttr__apply(RenderDestinationAttrView *self, igObject *context) {
    RenderDestinationDesc desc;
    int sizeX;
    int sizeY;

    if (!self->_bEnabled) {
        return;
    }
    self->_iPrevRDHandle = igPsx2VisualContext_GetCurrentRenderDestination((igPsx2VisualContext *)context);
    if (self->_iRDHandle < 0) {
        if (self->_iCreateMode != 1) {
            igPsx2VisualContext_GetRenderDestinationSize((igPsx2VisualContext *)context, self->_iPrevRDHandle, &sizeX, &sizeY);
            self->_iSizeX = sizeX;
            self->_iSizeY = sizeY;
            self->_iColorBitCount = igPsx2VisualContext_GetColorBitsPerPixel((igPsx2VisualContext *)context, self->_iPrevRDHandle);
            self->_iAlphaBitCount = igPsx2VisualContext_GetAlphaBitsPerPixel((igPsx2VisualContext *)context, self->_iPrevRDHandle);
            self->_iDepthBitCount = igPsx2VisualContext_GetDepthBitsPerPixel((igPsx2VisualContext *)context, self->_iPrevRDHandle);
            self->_iStencilBitCount = igPsx2VisualContext_GetStencilBitsPerPixel((igPsx2VisualContext *)context, self->_iPrevRDHandle);
        }
        if (self->_iCreateMode == 2) {
            self->_iRDHandle = self->_iPrevRDHandle;
        } else {
            desc.sizeX = self->_iSizeX;
            desc.sizeY = self->_iSizeY;
            desc.colorBitCount = self->_iColorBitCount;
            desc.alphaBitCount = self->_iAlphaBitCount;
            desc.depthBitCount = self->_iDepthBitCount;
            desc.stencilBitCount = self->_iStencilBitCount;
            desc.type = self->_iType;
            self->_iRDHandle = igPsx2VisualContext_CreateRenderDestination((igPsx2VisualContext *)context, &desc);
        }
    }
    self->_vc = context;
}

void igRenderDestinationAttr_SynchronizeDefault(OO *arg0, void **arg1) {
    int sp4C;
    int sp48;
    int temp_s0;
    int *pp;
    int t;

    temp_s0 = ((DW4VC_200_0 *)(arg1))->vX();
    arg0->f20 = ((DW4VC_200_0 *)(arg1))->vX();
    arg0->f48 = ((DW4VC_216_1 *)(arg1))->vX(temp_s0);
    arg0->f52 = ((DW4VC_220_1 *)(arg1))->vX(temp_s0);
    arg0->f56 = ((DW4VC_224_1 *)(arg1))->vX(temp_s0);
    arg0->f60 = ((DW4VC_228_1 *)(arg1))->vX(temp_s0);
    pp = (int *)((int)&sp4C + 0);
    ((DW4VC_212_3 *)(arg1))->vX(temp_s0, &sp48, pp);
    t = *pp;
    arg0->f40 = sp48;
    arg0->f44 = t;
}

void igRenderDestinationAttr_ReleaseDefaults(void **arg0) {
    ((DW4VC_112_0 *)(arg0))->vX();
    igObject_ReleaseDefaults((igObject *)arg0);
}

void igRenderDestinationAttr_Reset(X_13fea0 *arg0) {
    int temp_a1;
    R_13fea0 *temp_a0;
    R_13fea0 *temp_a0_2;

    if (arg0->w12 != 2) {
        temp_a0 = arg0->obj;
        if (temp_a0 != 0) {
            temp_a1 = arg0->w20;
            if (temp_a1 >= 0) {
                ((DW4VC_188 *)temp_a0)->vX(temp_a1);
            }
        }
        temp_a0_2 = arg0->obj;
        if (temp_a0_2 != 0) {
            temp_a0_2->refs = temp_a0_2->refs - 1;
            if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)temp_a0_2);
            }
        }
        arg0->obj = 0;
        arg0->w20 = -1;
    }
}


/* igVisualContext's default for the slot igRenderDestinationAttr's release calls with its handle. */
extern "C" void Gap__Gfx__igVisualContext__destroyRenderDestination(igObject *context, int renderDestination) {
}
