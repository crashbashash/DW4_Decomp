namespace Gap {
namespace Sg {

void igGraphPath::getTransformMatrixInclusive(igMatrix44f *mat, long long time) const
{
    getTransformMatrix(getDepth(), mat, time);
}

/* matching construct: the two counting loops keep retail's entry test, which sits after the function's exit
 * (a guard block each: `0 < count`, then the loop's own test); no for/while spelling tried produces it */
void igGroup::userPostLoad()
{
    int n;
    int i;
    igNode *child;
    int have;
    int j;
    igNodeList *children;
    int want;
    int parentCount;
    igNonRefCountedNodeList *parents;
    int k;

    igNode::userPostLoad();
    n = getChildCount();
    for (i = 0; i < n; i++) {
        child = _childList->get(i);
        if (child != 0) {
            have = 0;
            children = _childList;
            j = 0;
            goto guardHave;
        countHave:
            if (children->get(j) == child) {
                have++;
            }
            j++;
        testHave:
            if (j < n) {
                goto countHave;
            }
        haveCounted:
            parents = child->_parentList;
            want = 0;
            parentCount = parents->getCount();
            k = 0;
            goto guardWant;
        countWant:
            if (parents->get(k) == this) {
                want++;
            }
            k++;
        testWant:
            if (k < parentCount) {
                goto countWant;
            }
        wantCounted:
            for (j = want; j < have; j++) {
                child->addParent(this);
            }
            for (; have < want; have++) {
                child->removeParent(this);
            }
        }
    }
    return;
guardWant:
    if (0 < parentCount) {
        goto testWant;
    }
    goto wantCounted;
guardHave:
    if (0 < n) {
        goto testHave;
    }
    goto haveCounted;
}

int igGroup::appendChild(igNode *child)
{
    int index = getChildCount();
    if (insertChild(index, child)) {
        return index + 1;
    }
    return -1;
}

bool igGroup::insertChild(int i, igNode *child)
{
    if (child == 0) {
        return false;
    }
    if (child->addParent(this)) {
        /* matching construct: the element is held in a record whose address escapes to the insert, so the
         * reference count is taken through a reload of it */
        struct {
            igNode *p;
        } item;
        item.p = child;
        ::igDataList *list = (::igDataList *)_childList.p;
        igObject::ref(item.p);
        List_InsertWords(list, i, 1, &item);
        propagateFlagsUp(child->getFlags());
        return true;
    }
    return false;
}

void igGroup::userDestruct()
{
    unsigned int count = getChildCount();
    for (unsigned int i = 0; i < count; i++) {
        _childList->get(i)->removeParent(this);
    }
    igNode::userDestruct();
}

igSmartPointer<igNode> igGroup::removeChild(int i)
{
    igNodeList *children = getChildList();
    int count = children != 0 ? children->getCount() : 0;
    if (i < count) {
        igSmartPointer<igNode> node(getChild(i), kRetainReference);
        node->removeParent(this);
        igNodeList *list = _childList;
        igObject::release(list->get(i));
        List_RemoveWordAt((::igDataList *)list, i);
        ((igNode **)list->_data)[list->_count] = 0;
        removeFlagsUp(node->getFlags());
        return node;
    }
    return igSmartPointer<igNode>(0, kRetainReference);
}

int igGroup::removeChild(igNode *child)
{
    unsigned int count = getChildCount();
    unsigned int i;
    bool found = false;
    for (i = 0; i < count; i++) {
        if (_childList->get(i) == child) {
            found = true;
            break;
        }
    }
    if (found) {
        removeChild((int)i);
        return i;
    }
    return -1;
}

void igGroup::removeFlagsUp(unsigned int flags)
{
    /* matching construct: declaration order (the register assignment follows it) and the parameter reused as
     * the parent counter */
    int childFlags;
    int i;
    igNodeList *children;
    unsigned int notInherent;
    unsigned int mask;
    unsigned int clear;

    notInherent = ~getInherantFlags();
    mask = flagMask;
    flags = notInherent & (flags & mask);
    if (flags != 0) {
        children = _childList;
        childFlags = 0;
        i = 0;
        while (i < (children != 0 ? children->getCount() : 0)) {
            childFlags |= children->get(i)->getFlags();
            i++;
        }
        clear = notInherent & (mask & (flags & ~childFlags));
        if (clear != 0) {
            setFlags(clear, false);
            flags = 0;
            while ((int)flags < getParentCount()) {
                ((igGroup *)getParent(flags))->removeFlagsUp(clear);
                flags++;
            }
        }
    }
}
}
}
