#ifndef DW4_ENBAYA_H
#define DW4_ENBAYA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Creates the Enbaya codec's memory management on first use: the given allocator object, or the
 * malloc/free default when it is 0. */
void Enbaya_InitMemoryManagement(void **memory);
void thunk_Enbaya_InitMemoryManagement(void **memory);

#ifdef __cplusplus
}
#endif

#endif
