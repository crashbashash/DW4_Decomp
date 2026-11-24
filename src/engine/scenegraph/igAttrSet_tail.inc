namespace Gap {
namespace Sg {

void igAttrSet::reset()
{
    unsigned int count = _attributes->getCount();
    for (unsigned int i = 0; i < count; i++) {
        _attributes->get(i)->reset();
    }
}
}
}

