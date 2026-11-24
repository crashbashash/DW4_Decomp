namespace Gap {
namespace Sg {

unsigned int igLightSet::getInherantFlags()
{
    return HAS_LIGHT;
}

void igLightSet::userConstruct(int flag)
{
    igNode::userConstruct(flag);
    if (flag == 0)
        setFlags(HAS_LIGHT, true);
}

void igLightSet::reset()
{
    unsigned int count = _lights->getCount();
    for (unsigned int i = 0; i < count; i++)
        _lights->get(i)->reset();
}

void igLightSet::transform(const igMatrix44f &matrix)
{
    igVec4f position;
    igVec4f direction;
    unsigned int count = _lights->getCount();
    for (unsigned int i = 0; i < count; i++) {
        igLightAttr *light = _lights->get(i);
        Vec3f_TransformProjective((float *)&position, (const float *)((char *)light + igLightAttr::k_position->_offset), (const float *)&matrix);
        light->setPosition(*(igVec3f *)&position);
        Vec3f_TransformDirection((float *)&direction, (const float *)((char *)light + igLightAttr::k_direction->_offset), (const float *)&matrix);
        light->setDirection(*(igVec3f *)&direction);
    }
}

void igLightStateSet::userConstruct(int flag) {
    igNode_userConstruct((void * *)(void * *)this, flag);
}
}
}

