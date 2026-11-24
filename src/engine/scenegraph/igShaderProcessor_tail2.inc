namespace Gap {
namespace Sg {

bool igShaderProcessor::configure(igSimpleShaderDispatchView *shader, igCapabilityManager *capabilityManager)
{
    return shader->_shaderData->getPassCount() > 0;
}

void igShaderProcessor::update(igSimpleShaderDispatchView *shader, igCommonTraversal *ct)
{

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

