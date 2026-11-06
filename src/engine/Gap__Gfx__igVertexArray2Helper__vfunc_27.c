/* Predicate on the bound vertex array: true when its igVertexStream exists and that stream's
 * _accessMode is 2. The enum behind _accessMode is not named in the reflection data, so the value
 * stays a literal. */
#include "dw4/reflected.h"
int Gap__Gfx__igVertexArray2Helper__vfunc_27(igVertexArray2Helper *self) {
    int result;
    igVertexArray2 *vertexArray;
    igVertexStream *stream;

    vertexArray = (igVertexArray2 *)(self->_vertexArray);
    result = 0;
    if (vertexArray != 0) {
        stream = (igVertexStream *)(vertexArray->_vertexStream);
        if ((stream != 0) && (stream->_accessMode == 2)) {
            result = 1;
        }
    }
    return result;
}
