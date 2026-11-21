namespace Gap {
namespace Attrs {

void igAttrPool::addNonSharableType(igMetaObject *meta)
{
    ((igObjectList *)(::igMetaObjectList *)_nonSharableMetaList)->appendUnique((igObject *)meta);
}
}
}

static inline void clearBytes(char *p, unsigned int n) {
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}

namespace Gap {
namespace Attrs {

void igAttrPool::resetFields(int flag)
{
    igMetaObject *metas[4];
    int i;

    igObject::resetFields(flag);
    clearBytes((char *)metas, sizeof(metas));
    metas[0] = igTextureBindAttr_GetMetaObject();
    metas[1] = igTextureAttr_GetMetaObject();
    metas[2] = igLightAttr_GetMetaObject();
    metas[3] = igLightStateAttr_GetMetaObject();
    for (i = 0; i < 4; i++) {
        addNonSharableType(metas[i]);
    }
}
}
}

