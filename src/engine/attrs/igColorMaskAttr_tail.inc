/* Setter for the colour write mask: one flag per channel. */

namespace Gap {
namespace Attrs {

void igColorMaskAttr::setMask(bool r, bool g, bool b, bool a)
{
    _red = r;
    _green = g;
    _blue = b;
    _alpha = a;
}

void igColorMaskAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetColorMask((igPsx2VisualContext *)vc, _red, _green, _blue, _alpha);
}

void igColorMaskAttr::synchronizeDefault(igVisualContext *vc)
{
    bool r;
    bool g;
    bool b;
    bool a;

    vc->getColorMask(r, g, b, a);
    _red = r;
    _green = g;
    _blue = b;
    _alpha = a;
}
}
}

