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
double atof(const char *);
int atoi(const char *);
long atol(const char *);
long strtol(const char *, char **, int);
unsigned long strtoul(const char *, char **, int);
char *getenv(const char *);
void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
#ifdef __cplusplus
}
#endif
#endif
