#ifndef DW4_IGCORE_H
#define DW4_IGCORE_H

/* The core library's shared types (alchemy-kit_202309 include/igCore/igCore.h). */
#ifdef __cplusplus
namespace Gap {
/* An enumeration's value (alchemy-kit_202309 include/igGap.h). */
typedef int igEnum;
/* A list's element comparison: each argument points at an element (or the searched item), and the result is 0
 * for equal ones, negative when the first sorts before the second. This engine's form takes no user data. */
typedef int (igCompareFunction)(const void *argument1, const void *argument2);
namespace Core {
/* A dependency pair, igDependencyList's element (alchemy-kit_202309 igCore/igDependencyOrderedList.h). */
class igDependency {
public:
    const void *_before;
    const void *_after;
    inline igDependency() : _before(0), _after(0) {}
};
}
}
#endif

#endif
