/* Storage size in bytes of the field's array: `_num` elements of 4 bytes (float), truncated to the
 * 16-bit size the meta field system uses. */

int igFloatArrayMetaField_GetSize(igFloatArrayMetaField *self) {
    return (self->_num * 4) & 0xFFFF;
}

void igFloatArrayMetaField_SwapBytes(igFloatArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(((void **)Gap::Core::igFloatMetaField::getMetaField()));
    ((igMetaFieldView *)(elementField))->SwapBytes((void *)(buffer), (int)(count * self->_num));
}

namespace Gap {
namespace Core {

int igFloatMetaField::setMemoryByString(void *dstMem, const char *strVal, igDirectory *dir)
{
    int consumed;

    consumed = 0;
    sscanf(strVal, "%f%n", (float *)dstMem, &consumed);
    return consumed;
}

igStringRef igFloatMetaField::getStringFromMemory(const void *srcMem, igDirectory *dir)
{
    char buffer[1024];

    sprintf(buffer, "%f", fptodp(*(const float *)srcMem));
    return igStringRef(buffer);
}
}
}

