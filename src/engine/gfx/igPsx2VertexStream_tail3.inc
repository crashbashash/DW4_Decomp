namespace Gap {
namespace Gfx {

void igPsx2VertexStream::getEditableComponent(igComponentEditInfo2 &componentInfo)
{
    if (_accessMode == IG_VERTEX_ACCESS_READ_WRITE) {
        waitForSync();
    }
    if (!(_accessMode == IG_VERTEX_ACCESS_WRITE_ONCE || _accessMode == IG_VERTEX_ACCESS_WRITE)) {
        igSmartPointer<igVertexData> vertexData(FUN_0015f4a0((igVertexDataList *)_vertexDataList.p, componentInfo._componentType, componentInfo._componentIndex), kRetainReference);
        unsigned int componentSize = vertexData->_componentSize;
        unsigned int elementSize = ((igDataList *)vertexData->_data)->getElementSize();
        unsigned int stride = elementSize * componentSize;
        componentInfo._componentData = (char *)((igDataList *)vertexData->_data)->_data + componentInfo._startIndex * stride;
        componentInfo._stride = stride;
        componentInfo._numComponents = ((igDataList *)vertexData->_data)->_count - componentInfo._startIndex;
    }
    componentInfo._colorFormat = IG_MATH_COLORSPACE_FORMAT_RGBA;
}

void igPsx2VertexStream::reset()
{
    if (_isConfigured && getRawVertexStream() != 0) {
        p2ReleaseDisplayList((p2DisplayList *)_renderListHandle);
        _stream = 0;
    } else {
        if (_syncSequence != 0) {
            waitForSync();
        }
        _stream = 0;
    }
    _renderListHandle = 0;
    if (_dmaBuffer != 0) {
        Memory_FreeBuffer(_dmaBuffer);
        _dmaBuffer = 0;
    }
    if (_dmaBufferStruct != 0) {
        Memory_FreeBuffer(_dmaBufferStruct);
        _dmaBufferStruct = 0;
    }
    igVertexStream::reset();
}
}
}

