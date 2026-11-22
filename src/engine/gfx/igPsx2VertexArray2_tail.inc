namespace Gap {
namespace Gfx {

bool igPsx2VertexArray2::configure(IG_GFX_DRAW primitive, igIndexArray *indexArray, igPrimLengthArray *primLengthArray, igVisualContext *vc)
{
    if (_vertexStream == 0) {
        igSmartPointer<igVertexStream> stream((igVertexStream *)igVertexStream_Create((int)getMemoryPool()));
        _vertexStream = stream;
    }
    igVertexStream *vs = _vertexStream.p;
    if (vs->_isConfigured != 0) {
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
    vs->_primitive = primitive;
    ((igVisualContextDispatchView *)vc)->setVertexArray((::igVertexArray2 *)this, 0);
    return ((igVertexStreamDispatchView *)vs)->configure(list, (::igIndexArray *)indexArray, primLengthArray, vc);
}

void igPsx2VertexArray2::releaseDefaults()
{
    reset();
}

void igPsx2VertexArray2::reset()
{
    if (_vertexStream != 0) {
        ((igVertexStreamDispatchView *)_vertexStream.p)->reset();
    }
}
}
}

