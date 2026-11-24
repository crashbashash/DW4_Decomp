unsigned char g_enbayaEnabled;

namespace Gap {
namespace Sg {

void igEnbayaAnimationState::setEnbayaEnabled(int mode) {
    if ((mode & 0xFF) != g_enbayaEnabled) {
        int saved = 0;
        List_1c0f00 *list = ((List_1c0f00 *)g_igAnimationStatePool_instance.p);
        if (list != 0) {
            saved = list->getCount();
            list->clear();
        }
        if (mode != 0) {
            DAT_00562728[0] = ((Meta *)((void *)Gap::Sg::igAnimationState::getClassTypeSafe()))->f60;
            Meta *m2 = (Meta *)Gap::Sg::igAnimationState::getClassTypeSafe();
            m2->f60 = (void *)getClassMeta;
            int a = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
            g_igEnbayaContextPool_instance.release();
            g_igEnbayaContextPool_instance.p = (::igEnbayaContextPool *)Gap::Sg::igEnbayaContextPool::_instantiateFromPool((igMemoryPoolView *)a);
        } else {
            ((Meta *)((void *)Gap::Sg::igAnimationState::getClassTypeSafe()))->f60 = DAT_00562728[0];
            g_igEnbayaContextPool_instance.clear();
        }
        if (g_igAnimationStatePool_instance.p != 0) ((Gap::Core::igObjectList *)((igTDataList< ::igObject *> *)g_igAnimationStatePool_instance.p))->setCount(saved);
        g_enbayaEnabled = mode;
    }
}
}
}

void FUN_001c10f0(void) {
    Gap::Sg::igEnbayaAnimationState::setEnbayaEnabled(1);
}

void FUN_001c1100(void) {
    Gap::Sg::igEnbayaAnimationState::setEnbayaEnabled(0);
}

namespace Gap {
namespace Sg {

void igEnbayaAnimationState::userPostLoad()
{
    if (g_enbayaEnabled != 0) {
        activate();
    }
}
}
}

unsigned char g_fastCacheDecodingEnabled;

namespace Gap {
namespace Sg {

void igEnbayaAnimationState::activate()
{
    int found;
    int i;
    igAnimationTrackList *l;
    int n;
    igAnimationTrack *e;
    igEnbayaTransformSource *c;
    found = 0;
    l = _animation->getTrackList();
    n = l->getCount();
    for (i = 0; i < n; i++) {
        e = l->get(i);
        if (e != 0 && (c = (igEnbayaTransformSource *)e->getSource()) != 0 && ((Gap::Core::igObject *)c)->isOfType(Gap::Sg::igEnbayaTransformSource::getClassMeta()) != 0) {
            found = ((::igEnbayaAnimationSource *)c->getEnbayaAnimationSource())->_enbayaAnimationStream;
            break;
        }
    }
    if (found != 0) {
        _context = (int)((Gap::Sg::igEnbayaContextPool *)g_igEnbayaContextPool_instance.p)->allocate(_animation->getTrackList()->getCount());
        if (g_fastCacheDecodingEnabled == 0) {
            _fastCacheDecodingState = 0;
        }
        FUN_0027ef50((EnbayaDecoderState *)_context, (EnbayaAnimationData *)FUN_002808f0(found), _fastCacheDecodingState);
    }
}

void igEnbayaAnimationState::deactivate()
{
    int temp_a1;

    temp_a1 = _context;
    if (temp_a1 != 0) {
        ((Gap::Sg::igEnbayaContextPool *)g_igEnbayaContextPool_instance.p)->deallocate((void *)temp_a1, _animation->getTrackList()->getCount());
    }
}

void igEnbayaAnimationState::preVisit()
{
    DAT_00562720[0] = _context;
}

void igEnbayaAnimationState::postVisit()
{
    void *temp_a0;

    DAT_00562720[0] = 0;
    temp_a0 = (void *)(_context);
    if ((temp_a0 != 0) && (*(unsigned char *)((char *)(temp_a0) + 171) != 0)) {
        FUN_002800d0((EnbayaDecoderState *)temp_a0);
    }
}
}
}

