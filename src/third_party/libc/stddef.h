#ifndef DW4_LIBC_STDDEF_H
#define DW4_LIBC_STDDEF_H
/* Only what the stock libraries include: the game links Sony's newlib-based libc. */
#ifdef __cplusplus
extern "C" {
#endif
typedef unsigned int size_t;
typedef int ptrdiff_t;
#define NULL 0
#define offsetof(type, member) ((size_t)&((type *)0)->member)
#ifdef __cplusplus
}
#endif
#endif
