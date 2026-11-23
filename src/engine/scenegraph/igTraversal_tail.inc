namespace Gap {
namespace Sg {

void igTraversal::registerClass(igMetaObject *meta)
{
    _registerClass(travProcs, meta);
}

void igTraversal::_registerClass(igTraversalFunctionList *tpl, igMetaObject *meta)
{
    if (igMetaObject_IsOfType(meta, Gap::Sg::igNode::getClassTypeSafe()) != 0) {
        if (igMetaObject_IsOfType(meta, Gap::Sg::igGroup::getClassTypeSafe()) != 0) {
            _setFunction(tpl, meta, (igTraversalFunction *)igTraversal_TraverseChildren);
            return;
        }
        _setFunction(tpl, meta, (igTraversalFunction *)igTraversal_TraverseLeaf);
    }
}

void igTraversal::userConstruct(int flag)
{
    igObject::userConstruct(flag);
    if (flag == 0) {
        cacheTravProcs();
    }
}
}
}

unsigned char g_useScratchPadForTraversal;

namespace Gap {
namespace Sg {

void igTraversal::userRegister()
{
    travProcs = igTraversalFunctionList::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
    ((Gap::Core::igRegistry *)(*(int *)((char *)g_objectSystem + 56)))->getValue(7, "useScratchPadForTraversal", g_useScratchPadForTraversal, g_useScratchPadForTraversal, 1);
}

void igTraversal::userUnregister()
{
    igObject::release(travProcs);
}

int igTraversal::dispatch(igObject *node)
{
    if (_nodeSelectProcEnabled) {
        int selected = _nodeSelectProc((::igTraversal *)this, (::igNode *)node);
        if (selected != 0) {
            if (selected == 2) {
                igMetaObject *nodeMeta = Gap::Sg::igNode::getClassMeta(); /* matching construct: MWCC — igNode's meta is read before getMeta() */
                if (node->getMeta() != nodeMeta) {
                    int result;
                    if (igTraversal_TraverseChildren((::igTraversal *)this, (::igNode *)node) == 2) {
                        result = 2;
                    } else {
                        result = 0;
                    }
                    return result;
                }
            } else {
                return 0;
            }
        }
    }
    return _travProcs->get(((::igNode *)node)->_handle)((::igTraversal *)this, (::igObject *)node);
}

void igTraversal::begin(igNode *root)
{
}

void igTraversal::end(igNode *root)
{
}

/* Traverses {node} between the pre- and post-traversal hooks. With useScratchPadForTraversal set, the
 * outermost traversal runs on a stack at the top of the scratchpad and restores the caller's stack after. */
void igTraversal::apply(igNode *root)
{
    if (g_useScratchPadForTraversal) {
        DAT_00562a50 = (V_1e04c0 *)root;
        if (DAT_00562a40 == 0) {
            long long *savedStack = &DAT_00562a48;
            unsigned int scratchPadTop = 0x70003fe0;
            __asm__("sd $sp, 0(%0)\n\tmove $sp, %1" : : "r"(savedStack), "r"(scratchPadTop));
        }
        DAT_00562a40 = DAT_00562a40 + 1;
        begin(root);
        dispatch((igObject *)DAT_00562a50);
        end((igNode *)DAT_00562a50);
        DAT_00562a40 = DAT_00562a40 - 1;
        if (DAT_00562a40 == 0) {
            __asm__("ld $sp, 0(%0)" : : "r"(&DAT_00562a48));
        }
    } else {
        begin(root);
        dispatch((igObject *)root);
        end(root);
    }
}

void igTraversal::_setFunction(igTraversalFunctionList *tpl, igMetaObject *meta, igTraversalFunction *func)
{
    if (igMetaObject_IsOfType(meta, Gap::Sg::igNode::getClassMeta()) != 0) {
        int handle = getNodeHandle(meta);
        if (handle < 0) {
            handle = tpl->getCount();
            setNodeHandle(meta, handle);
        }
        if (handle >= tpl->getCount()) {
            tpl->setCount(handle + 1);
        }
        tpl->set(handle, func);
    }
}
}
}

int igTraversal_TraverseLeaf(void) {
    return 0;
}

int igTraversal_TraverseChildren(igTraversal *traversal, igNode *node) {
    S_1e07a0 *arg1 = (S_1e07a0 *)node;
    L_1e07a0 *temp_v0 = arg1->f28;
    int *var_s0;
    int *temp_s2;
    int r;
    if (temp_v0 != 0) {
        var_s0 = temp_v0->arr;
        temp_s2 = var_s0 + temp_v0->n;
        for (; var_s0 < temp_s2; var_s0++) {
            r = ((Gap::Sg::igTraversal *)traversal)->dispatch((Gap::Core::igObject *)(*var_s0));
            if (r == 1) return 0;
            if (r == 2) return 2;
        }
    }
    return 0;
}

void thunk_FUN_001c1c50(void **self, int flag) {
    FUN_001c1c50((void * *)self, flag);
}

