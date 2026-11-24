namespace Gap {
namespace Sg {

unsigned int igTransform::getInherantFlags()
{
    return HAS_TRANSFORM;
}

void igTransform::reset()
{
    if (_transformInput != 0) {
        ((DW4VC_132_0 *)(_transformInput.p))->vX();
        igMatrix44f_SetIdentity(_m.m);
    }
}
}
}

