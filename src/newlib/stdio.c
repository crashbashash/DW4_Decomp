#include "dw4/newlib_stdio.h"

long _read_r(struct _reent *ptr, int fd, void *buf, int count);
long _write_r(struct _reent *ptr, int fd, const void *buf, int count);
long _lseek_r(struct _reent *ptr, int fd, long offset, int whence);
int _close_r(struct _reent *ptr, int fd);

int __sread(void *cookie, char *buf, int n)
{
    FILE *fp = cookie;
    int ret;

    ret = _read_r(fp->_data, fp->_file, buf, n);
    if (ret >= 0) {
        fp->_offset += ret;
    } else {
        fp->_flags &= ~__SOFF;
    }
    return ret;
}

int __swrite(void *cookie, const char *buf, int n)
{
    FILE *fp = cookie;

    if (fp->_flags & __SAPP) {
        _lseek_r(fp->_data, fp->_file, 0, 2);
    }
    fp->_flags &= ~__SOFF;
    return _write_r(fp->_data, fp->_file, buf, n);
}

long __sseek(void *cookie, long offset, int whence)
{
    FILE *fp = cookie;
    long ret;

    ret = _lseek_r(fp->_data, fp->_file, offset, whence);
    if (ret == -1) {
        fp->_flags &= ~__SOFF;
    } else {
        fp->_flags |= __SOFF;
        fp->_offset = ret;
    }
    return ret;
}

int __sclose(void *cookie)
{
    FILE *fp = cookie;

    return _close_r(fp->_data, fp->_file);
}
