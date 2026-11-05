#ifndef DW4_LIBC_STDLIB_H
#define DW4_LIBC_STDLIB_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
#define EXIT_FAILURE 1
#define RAND_MAX 2147483647
void *malloc(size_t);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void free(void *);
void abort(void);
void exit(int);
int abs(int);
int rand(void);
void srand(unsigned int);
double strtod(const char *, char **);
unsigned long strtoul(const char *, char **, int);
#ifdef __cplusplus
}
#endif
#endif
