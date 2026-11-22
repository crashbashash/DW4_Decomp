static inline Gap::Core::igMemoryRefMetaField *castMemoryRefMetaField(igMetaField *field) {
    if (field != 0 && ((Gap::Core::igObject *)field)->isOfType(Gap::Core::igMemoryRefMetaField::getClassMeta()) != 0) {
        return (Gap::Core::igMemoryRefMetaField *)field;
    }
    return 0;
}

namespace Gap {
namespace Gfx {

void igPsx2VertexStream::userRegister()
{
    igResource_AddAlignment((igResource *)g_globalContext, "DMABuffer_PS2", 0x10);
    castMemoryRefMetaField(igMetaObject_FindFieldByName(_Meta, "_dmaBuffer"))->setAlignmentType("DMABuffer_PS2");
}

void igPsx2VertexStream::userWriteFilePreProcess()
{
    if (_isConfigured) {
        if (_renderListHandle != 0 && (_accessMode == IG_VERTEX_ACCESS_WRITE_ONCE || _accessMode == IG_VERTEX_ACCESS_WRITE) && _dmaBuffer == 0) {
            _dmaBuffer = (unsigned char *)mallocAligned(p2GetDisplayListSize((p2DisplayList *)_renderListHandle), 0x10);
            p2CopyDisplayListData((p2DisplayList *)_renderListHandle, (char *)_dmaBuffer);
            _dmaBufferStruct = (unsigned char *)p2CopyDisplayList((p2DisplayList *)_renderListHandle);
        }
    }
}

void igPsx2VertexStream::userPostLoad()
{
    igVertexStream::userPostLoad();
    if (_dmaBuffer != 0 && _dmaBufferStruct != 0) {
        _isConfigured = true;
        _renderListHandle = (int)p2RebaseDisplayList((unsigned int)_dmaBuffer, (p2DisplayList *)_dmaBufferStruct);
        _stream = (void *)p2GetDisplayListData((p2DisplayList *)_renderListHandle);
    }
}
}
}

