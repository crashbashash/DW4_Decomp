/* reflected.h comes first, outside the guard: it reads this header itself, just before the first converted class
 * deriving from the kit's template, so the template follows its parent igDependencyOrderedList there whichever
 * header a unit names first. */
#include "dw4/support/reflected.h"
#ifndef DW4_IGTDEPENDENCYORDEREDLIST_H
#define DW4_IGTDEPENDENCYORDEREDLIST_H

namespace Gap {
namespace Core {

/* The kit's typed dependency-ordered list (alchemy-kit_202309 igCore/igDependencyOrderedList.h): igDependencyOrderedList's
 * services taking and returning T. It adds no fields and no virtuals. The kit's search overloads are left out: no
 * DW4 code searches an ordered list. */
template <class T> class igTDependencyOrderedList : public igDependencyOrderedList {
public:
    inline T *get(unsigned int index) { return static_cast<T *>(igDependencyOrderedList::get(index)); }
    inline int find(T *object) const { return igDependencyOrderedList::find(static_cast<igObject *>(object)); }
    inline void append(T *object) { igDependencyOrderedList::append(static_cast<igObject *>(object)); }
    inline void appendUnique(T *object) { igDependencyOrderedList::appendUnique(static_cast<igObject *>(object)); }
    inline igResult remove(T *object) { return igDependencyOrderedList::remove(static_cast<igObject *>(object)); }
};
}
}

#endif
