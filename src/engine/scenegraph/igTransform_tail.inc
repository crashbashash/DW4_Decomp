namespace Gap {
namespace Sg {

void igTransform::userConstruct(int flag)
{
    igGroup::userConstruct(flag);
    if (flag == 0) {
        setFlags(HAS_TRANSFORM, true);
    }
}

bool igTransform::isTransformable() const
{
    if (getParentCount() > 1) {
        return false;
    }
    if (_transformInput == 0) {
        return true;
    }
    return _transformInput->isTransformable();
}
}
}

