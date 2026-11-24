namespace Gap {
namespace Sg {

bool igShaderProcessor::configure(igSimpleShaderDispatchView *shader, igCapabilityManager *capabilityManager)
{
    return shader->_shaderData->getPassCount() > 0;
}

void igShaderProcessor::update(igSimpleShaderDispatchView *shader, igCommonTraversal *ct)
{

}

/* Pushes each pass's attributes as overrides, traverses the pass's children (or the shader's own when the pass
 * has no child list) if the pass is enabled in the pass mask, and pops the attributes in reverse order. */
IG_TRAVERSAL_RETURN igShaderProcessor::shade(igSimpleShaderDispatchView *shader, igCommonTraversal *ct)
{
    /* matching construct: the declaration order (pass and the index the push and pop loops share before stop,
     * pushCount ahead of passCount and passMask) sets retail's saved registers and spill slots. */
    igAttrStackManager *attrStacks = ct->_attrStack;
    int pass;
    int i;
    bool stop = false;
    igShaderData *shaderData = shader->_shaderData;
    int pushCount;
    /* matching construct: read as the field, not getPassCount(), whose return value would replace the local
     * and take a late id (spill slot). */
    int passCount = shaderData->_attrPushLists->_count;
    igBitMask *passMask = (igBitMask *)shader->_passMask;

    for (pass = 0; pass < passCount && !stop; pass++) {
        igAttrList *pushList = shaderData->getPushList(pass);
        pushCount = pushList->getCount();
        for (i = 0; i < pushCount; i++) {
            igAttr *attr = pushList->get(i);
            attrStacks->fastPushOverride(attr);
        }
        if (((unsigned int *)passMask->_data)[(unsigned int)pass >> 5] & (1 << (pass & 31))) {
            int j; /* matching construct: the child index is declared ahead of the child list */
            igNodeList *childList = shaderData->_childLists->get(pass);
            if (childList == 0) {
                if (igTraversal_TraverseChildren((::igTraversal *)ct, (::igNode *)shader) == IG_TRAVERSAL_STOP)
                    stop = true;
            } else {
                for (j = 0; j < childList->getCount(); j++) {
                    if (((igTraversal *)ct)->dispatch(childList->get(j)) == IG_TRAVERSAL_STOP) {
                        stop = true;
                        break;
                    }
                }
            }
        }
        igAttrList *popList = shaderData->getPopList(pass);
        for (i = popList->getCount() - 1; i >= 0; i--) {
            igAttr *attr = popList->get(i);
            attrStacks->fastPopOverride(attr);
        }
    }
    return stop ? IG_TRAVERSAL_STOP : IG_TRAVERSAL_CONTINUE;
}
}
}

void FUN_001d9090(SkeletonBitOwnerView *o, int index, int value) {
    SkeletonBitListView *l = o->_bits;
    int i = l->_bitCount;
    if (i <= index) {
        unsigned int words;
        int n = index + 1;
        l->_bitCount = n;
        words = (unsigned int)(n + 31) >> 5;
        if ((int)words >= 0) {
            if ((int)words <= l->_capacity) { l->_count = words; }
            else { ((Gap::Core::igDataList *)l)->resizeAndSetCount(words, 4); }
        }
        {
            int j;
            for (j = i; j <= index; j++) {
                setBit(o->_bits, j);
            }
        }
    }
    l = o->_bits;
    if (value != 0) {
        setBit(l, index);
    } else {
        clearBit(l, index);
    }
}

