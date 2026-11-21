namespace Gap {
namespace Attrs {

void igTimeAttr::apply(igVisualContext *rc)
{
    rc->_renderingTime = _time;
}

/* Take the 64-bit time stored at +96 of `source` (an object not typed in reflected.h) as this
 * attribute's `_time`. */

void igTimeAttr::synchronizeDefault(igVisualContext *visualContext)
{
    _time = visualContext->_renderingTime;
}
}
}

