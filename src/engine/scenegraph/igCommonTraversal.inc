namespace Gap {
namespace Sg {

igMetaObject *igCommonTraversal::getClassTypeSafe()
{
    igMetaObject *g = _Meta;
    if (!g || ((g->_validity & 4) != 0) == false)
        arkRegister();
    return _Meta;
}

void *igCommonTraversal::retrieveVTablePointer()
{
    igCommonTraversal temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

