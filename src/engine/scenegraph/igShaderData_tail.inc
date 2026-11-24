

namespace Gap {
namespace Sg {

/* Resizes the push, pop and child lists to {count}; child slots past the old count are released and cleared. */
void igShaderData::setPassCount(int numPasses)
{
    _attrPushLists->setCount(numPasses);
    _attrPopLists->setCount(numPasses);
    int oldCount = _childLists->getCount();
    _childLists->setCount(numPasses);
    for (int i = oldCount; i < numPasses; i++)
        _childLists->set(i, 0);
}

void igShaderData::appendPass(igAttrList *pushList, igAttrList *popList, igNodeList *childList)
{
    _attrPushLists->append(pushList);
    _attrPopLists->append(popList);
    _childLists->append(childList);
}

void igShaderData::removeAll()
{
    _attrPushLists->removeAll();
    _attrPopLists->removeAll();
    _childLists->removeAll();
    setDataPumps(0);
}

void igShaderData::setPushList(int passIndex, igAttrList *pushList)
{
    _attrPushLists->set(passIndex, pushList);
}

void igShaderData::setPopList(int passIndex, igAttrList *popList)
{
    _attrPopLists->set(passIndex, popList);
}

void igShaderData::setChildList(int passIndex, igNodeList *childList)
{
    _childLists->set(passIndex, childList);
}

void igShaderData::userPostLoad()
{
    igObject::userPostLoad();
    if (_attrPushLists->getCount() != _childLists->getCount()) {
        _childLists->setCount(_attrPushLists->getCount());
        _childLists->clearAll();
    }
}
}
}

