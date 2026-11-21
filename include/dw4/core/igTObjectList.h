/* reflected.h comes first, outside the guard: it reads this header itself, just before the first converted class
 * deriving from the kit's template, so the template follows its parent igObjectList there whichever header a
 * unit names first. */
#include "dw4/support/reflected.h"
#ifndef DW4_IGTOBJECTLIST_H
#define DW4_IGTOBJECTLIST_H

namespace Gap {
namespace Core {

/* The kit's typed object list (alchemy-kit_202309 igCore/igTObjectList.h): igObjectList's services taking and
 * returning T, and the element type T's meta (the kit's getElementType, DW4's slot getElementMeta). It adds no
 * fields; its vtable is the compiler's, and a derived class's inlined constructor stamps only its own, so only an
 * out-of-line constructor copy references it (igDirectory's, which stamps igTObjectList<igDirEntry>'s, retail's
 * 0x532590). */
template <class T> class igTObjectList : public igObjectList {
public:
    inline T *const *getArray() const { return (T *const *)igObjectList::getArray(); }
    inline T *get(int index) const { return (T *)igObjectList::get(index); }
    inline void set(int index, T *object) { igObjectList::set(index, (igObject *)object); }
    inline void setAll(T *object) { igObjectList::setAll(object); }
    inline void append(T *object) { igObjectList::append(object); }
    inline void concatenate(const igTObjectList<T> *list) { igObjectList::concatenate((const igObjectList *)list); }
    inline igResult removeByValue(const T *obj, int startAt) { return igObjectList::removeByValue(obj, startAt); }
    inline int removeAllByValue(const T *obj, int startIndex) { return igObjectList::removeAllByValue(obj, startIndex); }
    inline int find(const T *obj, int startIndex) const { return igObjectList::find(obj, startIndex); }
    inline int appendUnique(T *obj) { return igObjectList::appendUnique(obj); }
    inline T *search(igStringMetaField *field, const char *name) const { return (T *)igObjectList::search(field, name); }
    inline T *search(igObjectRefMetaField *field, const igObject *obj) const {
        return (T *)igObjectList::search(field, obj);
    }
    inline virtual igMetaObject *getElementMeta() const { return T::getClassMeta(); }
};
}
}

#endif
