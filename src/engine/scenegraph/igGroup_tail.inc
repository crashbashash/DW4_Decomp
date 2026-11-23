namespace Gap {
namespace Sg {

bool igGroup::isTransformable() const
{
    if (getParentCount() > 1) {
        return false;
    }
    unsigned int count = getChildCount();
    for (unsigned int i = 0; i < count; i++) {
        if (!_childList->get(i)->isTransformable()) {
            return false;
        }
    }
    return true;
}
}
}

