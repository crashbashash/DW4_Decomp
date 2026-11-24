namespace Gap {
namespace Sg {

void igSkeleton::update(igCommonTraversal *traversal, igActor *actor, const igMatrix44f *animResultArray, igMatrix44f *boneMatrixResultArray, igMatrix44f *blendMatrixResultArray, igAnimationModifierList *modifierList)
{
    igMatrix44f *invJoint;
    int boneCount;
    int modifierCount;
    int i;
    int j;
    float translation[3];
    float combined[16];

    boneCount = ((igAnimationHierarchy *)this)->getBoneCount();
    invJoint = _invJointArray;
    if (modifierList == 0 || (modifierCount = modifierList->getCount()) == 0) {
        for (i = 1; i < boneCount; i++) {
            igSkeletonBoneInfo *info = _boneInfoList->get(i);
            igMatrix44f *global;
            int parent = info->_parentIdx;
            if (parent == 0) {
                global = &boneMatrixResultArray[i];
                igMatrix44f_Copy(global->m, animResultArray[i].m);
            } else {
                global = &boneMatrixResultArray[i];
                FUN_00190470(global, (void *)&animResultArray[i], &boneMatrixResultArray[parent]);
            }
            if (info->_bmIdx != -1) {
                FUN_00190470(&blendMatrixResultArray[info->_bmIdx], invJoint, global);
                invJoint++;
            }
        }
        return;
    }
    for (i = 1; i < boneCount; i++) {
        int offset;
        igSkeletonBoneInfo *info;
        igMatrix44f *global;
        info = _boneInfoList->get(i);
        offset = i << 6;
        igMatrix44f_Copy(combined, (const float *)((char *)animResultArray + offset));
        for (j = 0; j < modifierCount; j++) {
            igAnimationModifier *modifier = modifierList->getArray()[j];
            if (i == modifier->_boneIndex) {
                igTransform *transform = modifier->getTransform();
                igMatrix44f *source;
                ((igTransformUpdateView *)transform)->update(((igCommonTraversalDispatchView *)traversal)->getTime());
                source = modifier->getTransform()->getMatrix();
                if (modifier->_type == igAnimationModifier::kOverride) {
                    igMatrix44f_Copy(combined, source->m);
                }
                if (modifier->_type == igAnimationModifier::kOverrideOrientation) {
                    igMatrix44f_GetTranslation(combined, translation);
                    igMatrix44f_Copy(combined, source->m);
                    igMatrix44f_SetTranslation(combined, translation);
                } else if (modifier->_type == igAnimationModifier::kPre) {
                    igMatrix44f_PreMultiply(combined, source->m);
                } else if (modifier->_type == igAnimationModifier::kPost) {
                    igMatrix44f_Multiply(combined, combined, source->m);
                }
            }
        }
        if (info->_parentIdx != 0) {
            global = (igMatrix44f *)((char *)boneMatrixResultArray + offset);
            igMatrix44f_Multiply(global->m, combined, boneMatrixResultArray[info->_parentIdx].m);
        } else {
            global = (igMatrix44f *)((char *)boneMatrixResultArray + offset);
            igMatrix44f_Copy(global->m, combined);
        }
        if (info->_bmIdx != -1) {
            igMatrix44f_Multiply(blendMatrixResultArray[info->_bmIdx].m, invJoint->m, global->m);
            invJoint++;
        }
    }
}

int igSkeleton::getBoneCount() const
{
    return _boneInfoList->getCount();
}

int igSkeleton::findBoneIndex(const char *boneName) const
{
    int i;

    for (i = 0; i < _boneInfoList->getCount(); i++) {
        if (strcasecmp(_boneInfoList->get(i)->getName(), boneName) == 0) {
            return i;
        }
    }
    return -1;
}

int igSkeleton::getChild(int parentIndex, int &startIndex) const
{
    while (startIndex < getBoneCount()) {
        igSkeletonBoneInfo *info = _boneInfoList->get(startIndex);
        startIndex++;
        if (info->_parentIdx == parentIndex) {
            return startIndex - 1;
        }
    }
    return -1;
}

int igSkeleton::getSpecifiedChild(int boneIndex, int number) const
{
    int startIndex = 0;
    int count = 0;
    int child;

    do {
        child = getChild(boneIndex, startIndex);
        if (child != -1 && count == number) {
            return child;
        }
        count++;
    } while (child != -1);
    return -1;
}

int igSkeleton::getChildCount(int boneIndex) const
{
    int startIndex = 0;
    int count = 0;
    int child;

    do {
        child = getChild(boneIndex, startIndex);
        if (child != -1) {
            count++;
        }
    } while (child != -1);
    return count;
}

int igSkin::traverse(igTraversal *traversal)
{
    int result = 0;

    if (_skinnedGraph != 0) {
        result = ((Gap::Sg::igTraversal *)traversal)->dispatch((Gap::Core::igObject *)_skinnedGraph);
    }
    return result;
}
}
}

igSmartPointer<igObject> *igSmartPointer_igModelViewMatrixBoneSelect_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

igSmartPointer<igObject> *igSmartPointer_igAttrSet_Destruct(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

void **FUN_001d9870(void **arg0, short arg1) {
    int *r;
    if (arg0 != 0) {
        r = (int *)*arg0;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (arg1 > 0) {
            operator delete(arg0);
        }
    }
    return arg0;
}

