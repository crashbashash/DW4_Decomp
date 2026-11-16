#ifndef DW4_LIBC_STRING_H
#define DW4_LIBC_STRING_H
#include <stddef.h>
#ifdef __cplusplus
extern "C" {
#endif
void *memcpy(void *, const void *, size_t);
void *memset(void *, int, size_t);
int memcmp(const void *, const void *, size_t);
void *memchr(const void *, int, size_t);
size_t strlen(const char *);
char *strcpy(char *, const char *);
char *strncpy(char *, const char *, size_t);
int strcmp(const char *, const char *);
int strcoll(const char *, const char *);
char *strchr(const char *, int);
char *strpbrk(const char *, const char *);
size_t strcspn(const char *, const char *);
void *memmove(void *, const void *, size_t);
char *strcat(char *, const char *);
char *strncat(char *, const char *, size_t);
char *strrchr(const char *, int);
int strncmp(const char *, const char *, size_t);
char *strstr(const char *, const char *);
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);
char *strlwr(char *);
#ifdef __cplusplus
}
#endif
#endif
