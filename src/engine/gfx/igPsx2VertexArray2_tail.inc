namespace Gap {
namespace Gfx {

bool igPsx2VertexArray2::configure(IG_GFX_DRAW primitive, igIndexArray *indexArray, igPrimLengthArray *primLengthArray, igVisualContext *vc)
{
    if (_vertexStream == 0) {
        igSmartPointer<igVertexStream> stream(igVertexStream::_instantiateFromPool(getMemoryPool()));
        _vertexStream = stream;
    }
    igVertexStream *vs = _vertexStream.p;
    if (vs->isConfigured()) {
        return true;
    }
    igSmartPointer<igVertexDataList> list((igVertexDataList *)igVertexDataList_Create((int)getMemoryPool()));
    buildVertexDataList(list);
    if (primLengthArray != 0 && primLengthArray->_numStrips > 1 && !(primitive & IG_GFX_DRAW_DRAWMULTIPLE)) {
        switch (primitive) {
        case IG_GFX_DRAW_TRIANGLE_STRIP:
            primitive = (IG_GFX_DRAW)(IG_GFX_DRAW_DRAWMULTIPLE | IG_GFX_DRAW_MULTIPLE_TRIANGLE_STRIPS);
            break;
        case IG_GFX_DRAW_LINE_STRIP:
            primitive = (IG_GFX_DRAW)(IG_GFX_DRAW_DRAWMULTIPLE | IG_GFX_DRAW_MULTIPLE_LINE_STRIPS);
            break;
        case IG_GFX_DRAW_TRIANGLE_FAN:
            primitive = (IG_GFX_DRAW)(IG_GFX_DRAW_DRAWMULTIPLE | IG_GFX_DRAW_MULTIPLE_TRIANGLE_FANS);
            break;
        }
    }
    vs->setPrimitive(primitive);
    ((igVisualContextDispatchView *)vc)->setVertexArray((::igVertexArray2 *)this, 0);
    return vs->configure(list, indexArray, primLengthArray, vc);
}

void igPsx2VertexArray2::releaseDefaults()
{
    reset();
}

void igPsx2VertexArray2::reset()
{
    if (_vertexStream != 0) {
        _vertexStream->reset();
    }
}
}
}

