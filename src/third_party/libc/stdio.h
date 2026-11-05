#ifndef DW4_LIBC_STDIO_H
#define DW4_LIBC_STDIO_H
#include <stddef.h>
#include <stdarg.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct _FILE FILE;
struct _reent {
    int _errno;
    FILE *_stdin, *_stdout, *_stderr;
};
extern struct _reent *_impure_ptr;
#define stdin (_impure_ptr->_stdin)
#define stdout (_impure_ptr->_stdout)
#define stderr (_impure_ptr->_stderr)
#define BUFSIZ 1024
int fprintf(FILE *, const char *, ...);
int sprintf(char *, const char *, ...);
int vsprintf(char *, const char *, va_list);
int fputs(const char *, FILE *);
int fflush(FILE *);
FILE *fopen(const char *, const char *);
FILE *freopen(const char *, const char *, FILE *);
int fclose(FILE *);
int fgetc(FILE *);
int ungetc(int, FILE *);
int feof(FILE *);
size_t fread(void *, size_t, size_t, FILE *);
size_t fwrite(const void *, size_t, size_t, FILE *);
#ifdef __cplusplus
}
#endif
#endif
