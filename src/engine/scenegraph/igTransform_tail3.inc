namespace Gap {
namespace Sg {

unsigned int igTransform::getInherantFlags()
{
    return HAS_TRANSFORM;
}

void igTransform::reset()
{
    if (_transformInput != 0) {
        _transformInput->reset();
        igMatrix44f_SetIdentity(_m.m);
    }
}
}
}

