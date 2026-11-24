namespace Gap {
namespace Sg {

void igIntersectTraversal::registerClass(igMetaObject *meta) {
    _registerClass(travProcs, meta);
}

void igIntersectTraversal::userConstruct(int flag)
{
    igTraversal::userConstruct(flag);
    if (flag == 0) {
        cacheTravProcs();
    }
}
}
}

