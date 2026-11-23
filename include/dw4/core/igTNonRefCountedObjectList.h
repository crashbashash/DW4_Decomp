/* reflected.h comes first, outside the guard: it reads this header itself, just before the first converted class
 * deriving from the kit's template, so the template follows its parent igNonRefCountedObjectList there whichever
 * header a unit names first. */
#include "dw4/support/reflected.h"
#ifndef DW4_IGTNONREFCOUNTEDOBJECTLIST_H
#define DW4_IGTNONREFCOUNTEDOBJECTLIST_H

namespace Gap {
namespace Core {

/* The kit's typed list of unretained objects (alchemy-kit_202309 igCore/igTNonRefCountedObjectList.h): the
 * element type T's meta (the kit's getElementType, DW4's slot getElementMeta). It adds no fields; its vtable is
 * the compiler's and referenced by nothing, since a derived class's constructor stamps only its own. */
template <class T> class igTNonRefCountedObjectList : public igNonRefCountedObjectList {
public:
    inline T *const *getArray() const { return (T *const *)igNonRefCountedObjectList::getArray(); }
    inline T *get(int index) const { return (T *)igNonRefCountedObjectList::get(index); }
    inline void set(int index, T *object) { igNonRefCountedObjectList::set(index, object); }
    inline void append(T *object) { igNonRefCountedObjectList::append(object); }
    inline int find(const T *obj, int startIndex = 0) const {
        return igNonRefCountedObjectList::find((igObject *const &)obj, startIndex);
    }
    inline virtual igMetaObject *getElementMeta() const { return T::getClassMeta(); }
};
}
}

#endif
