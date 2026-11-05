#ifndef DW4_IGOBJECT_RELEASE_H
#define DW4_IGOBJECT_RELEASE_H
/* The one spelling of the Alchemy reference release that retail expands at every use site
 * (MWCC at this flag set does not inline functions, so each release is open-coded in the
 * caller): decrement the count word at +4 (igObject::_refCount) and destroy the object when
 * its low 23 bits reach zero.  The 23-bit test is written as the retail shift pair
 * (`<< 0x29 >> 0x29` on the 64-bit value), which is what the matched bytes show.
 *
 * `obj` is an lvalue of a pointer type whose target has an `_refCount` member (the reflected
 * igObject, or a local view such as igObjectSlotView in dw4/pool_slot.hpp), and is evaluated
 * more than once -- deliberately: a release of a stack slot whose address escaped to a factory
 * call must re-read the slot after the decrement, exactly as retail does.  Release through a
 * local copy (`igObject *held = p; IG_OBJECT_RELEASE(held);`) where the source holds the
 * pointer in a smart-pointer temporary that is read once.
 *
 * Needs a declaration of igObject_Destroy taking the pointer type in use.  Kept as a macro in a
 * header: tools/units.py cannot split a source file that carries a multi-line macro with an
 * `if (...) {` body. */
#define IG_OBJECT_RELEASE(obj)                                                                    \
    do {                                                                                          \
        if ((obj) != 0) {                                                                         \
            (obj)->_refCount = (int)(obj)->_refCount - 1;                                         \
            if (((unsigned long long)((long long)(int)(obj)->_refCount << 0x29) >> 0x29) == 0) { \
                igObject_Destroy(obj);                                                            \
            }                                                                                     \
        }                                                                                         \
    } while (0)
#endif /* DW4_IGOBJECT_RELEASE_H */
