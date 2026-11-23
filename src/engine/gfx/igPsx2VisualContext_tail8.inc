namespace Gap {
namespace Gfx {

IG_GFX_PIXEL_PIPELINE_MODE igPsx2VisualContext::getPixelPipelineMode() const {
    return _pixelPipelineMode;
}
}
}

void FUN_0017fd80(L_17fd80 **arg0, L_17fd80 **arg1, int arg2) {
    unsigned int i = 0;
    unsigned int v;
    L_17fd80 *l;
    while (i < (*arg0)->n) {
        v = (*arg0)->data[i];
        v = L_17fd80::cvt(v, arg2);
        l = *arg1;
        if (l->n != 0 && (int)i >= 0 && (int)i < (int)l->n) {
            l->data[i] = v;
        }
        i++;
    }
}

