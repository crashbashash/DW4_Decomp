namespace Gap {
namespace Sg {

void igLod::reset()
{
    _lastRange = 0;
    _lastIndex = -1;
    _lastLower = 0;
    _lastUpper = 0;
}

void igLod::userPostLoad()
{
    igGroup::userPostLoad();
    reset();
}

void igLod::transform(const igMatrix44f &matrix)
{
    igGroup::transform(matrix);
    Vec3f_TransformProjective(_center.vec, _center.vec, matrix.m);
}
}
}

