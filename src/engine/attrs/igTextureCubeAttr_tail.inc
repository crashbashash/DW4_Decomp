namespace Gap {
namespace Attrs {

void igTextureCubeAttr::apply(igVisualContext *vc)
{
    if (_texId < 0) {
        switch (_applyType) {
        case NOT_SET:
            if (vc->getCapability(IG_GFX_CAPABILITY_CUBE_MAP_SUPPORT) != 0 && _cubeImage[0] != 0) {
                _applyType = CUBE_MAP;
            } else {
                _applyType = SPHERE_MAP;
            }
            apply(vc);
            break;
        case CUBE_MAP:
            if (_texId < 0) {
                _applyType = SPHERE_MAP;
                apply(vc);
            }
            break;
        case SPHERE_MAP:
            igTextureAttr::apply(vc);
            break;
        }
        if (_texId >= 0) {
            goto applied;
        }
    } else {
    applied:
        igTextureAttr::apply(vc);
    }
}

void igTextureCubeAttr::releaseDefaults()
{
    igTextureAttr::releaseDefaults();
}

void igTextureCubeAttr::releaseImage(ApplyType type)
{
    int i;

    if (type == CUBE_MAP) {
        for (i = 0; i < 6; i++) {
            if (_cubeImage[i] != 0) {
                _cubeImage[i] = 0;
            }
        }
    } else if (type == SPHERE_MAP) {
        setImage(0, 0);
    }
}
}
}

