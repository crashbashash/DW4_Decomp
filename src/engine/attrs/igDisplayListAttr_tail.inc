namespace Gap {
namespace Attrs {

void igDisplayListAttr::apply(igVisualContext *rc)
{
    igAttr **attr = (igAttr **)_contents->_data;
    igAttr **end = attr + _contents->_count;

    while (attr < end) {
        (*attr)->apply(rc);
        attr++;
    }
}

void igDisplayListAttr::setup(igVisualContext *vc)
{
    igNonRefCountedAttrList *contents = _contents;
    igAttr **attr = (igAttr **)contents->_data;
    igAttr **end = attr + contents->_count;

    while (attr < end) {
        (*attr)->setup(vc);
        attr++;
    }
}

void igVisualAttribute::setup(igVisualContext *vc)
{
    apply(vc);
}
}
}

