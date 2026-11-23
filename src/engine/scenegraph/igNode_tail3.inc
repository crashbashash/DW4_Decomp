namespace Gap {
namespace Sg {

void igNode::userConstruct(int flag)
{
    igNamedObject::userConstruct(flag);
    if (flag == 0) {
        setFlags(getInherantFlags(), true);
    }
}

unsigned int igNode::getInherantFlags()
{
    return 0;
}

/* matching construct: igNodeRef's retain and release written over the held slot — retail reads the pointer back
 * from the slot for the null test, the increment and again after the decrement, which igSmartPointer's inlined
 * ref/release (a register copy of the pointer) does not. */
static inline void retainHeld(int *slot)
{
    ::igNode *node = (::igNode *)*slot;
    if (node != 0) {
        node->_refCount = node->_refCount + 1;
    }
}

static inline void releaseHeld(int *slot)
{
    if (*slot != 0) {
        ((::igNode *)*slot)->_refCount = ((::igNode *)*slot)->_refCount - 1;
        if ((((::igNode *)*slot)->_refCount & 0x7fffff) == 0) {
            igObject_Destroy((::igObject *)*slot);
        }
    }
}

void igNode::insertGroupAbove(igGroup *groupToInsert)
{
    ::igNode *held = (::igNode *)this;
    retainHeld((int *)&held);
    for (int i = getParentCount() - 1; i >= 0; i--) {
        igGroup *parent = (igGroup *)getParent(i);
        parent->insertChild(parent->getChild(this), groupToInsert);
        parent->removeChild(this);
    }
    groupToInsert->appendChild(this);
    releaseHeld((int *)&held);
}

void igNode::resetFields(int flag)
{
    igNamedObject::resetFields(flag);
    _handle = getMeta()->_id;
}

void igNode::userPostLoad()
{
    igNamedObject::userPostLoad();
    _handle = getMeta()->_id;
}
}
}

igSmartPointer<igObject> *igSmartPointer_igInfoList_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igSceneInfo_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igDirectory_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

