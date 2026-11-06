/* Vfunc_46, the "Deep" alike technique for an object-reference field. Compares the object this
 * field points at in two owners, `objectA` and `objectB`, found `self->_offset` bytes into each.
 * Two equal references (including both null) are alike; if only one side is null they are not;
 * otherwise the two target objects are compared member by member by igObject_IsAlikeDeep, which
 * walks the target's meta-object fields with igMetaField_IsAlikeDeep. Evidence: the sibling
 * vfunc_45/46/47 differ only in this callee, and the callees call
 * igMetaField_IsAlikeExactly/Deep/Shallow respectively (src/unmatched/igObject_IsAlikeExactly.cpp,
 * igObject_IsAlikeDeep.cpp, igObject_IsAlikeShallow.cpp; technique slots named in
 * config/SLUS-20836/names/ObjectModel.tsv). */
#include "dw4/reflected.h"
int igObject_IsAlikeDeep(int, int);

int Gap__Core__igObjectRefMetaField__vfunc_46(igObjectRefMetaField *self, int objectA, int objectB) {
    int refA;
    int refB;
    int fieldOffset;

    fieldOffset = self->_offset;
    refA = *(int *)(objectA + fieldOffset);
    refB = *(int *)(objectB + fieldOffset);
    if (refA == refB) {
        return 1;
    }
    if ((refA == 0) || (refB == 0)) {
        return 0;
    }
    return igObject_IsAlikeDeep(refA, refB);
}
