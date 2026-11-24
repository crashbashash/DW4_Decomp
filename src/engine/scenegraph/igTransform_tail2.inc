namespace Gap {
namespace Sg {

void igTransform::transform(const igMatrix44f &matrix)
{
    if (_transformInput == 0) {
        igMatrix44f_Multiply(_m.m, _m.m, matrix.m);
        return;
    }
    ((VC_1dd010 *)(_transformInput.p))->vX((int)&matrix);
}
}
}

