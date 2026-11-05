/* memmove_shim.c — memcpy for ee-as that allows overlapping copies (finding #3897).
 *
 * ee-as moves an expanded macro over itself with memcpy, which modern C libraries may get wrong.
 * tools/eegcc_compile.py preloads this for ee-as alone when DW4_EE_AS_SHIM names it. */
#include <stddef.h>
#include <string.h>

void *memcpy(void *destination, const void *source, size_t size)
{
    return memmove(destination, source, size);
}
