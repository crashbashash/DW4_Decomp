namespace Gap {
namespace Gfx {

bool igPsx2Image::toggleComponentOrder()
{
    bool r = true;
    if (_order == IG_GFX_IMAGE_ORDER_DEFAULT) {
        _order = IG_GFX_IMAGE_ORDER_PSX2;
    } else if (_order == IG_GFX_IMAGE_ORDER_PSX2) {
        _order = IG_GFX_IMAGE_ORDER_DEFAULT;
    } else {
        r = false;
    }
    return r;
}
}
}

