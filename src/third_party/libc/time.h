#ifndef DW4_LIBC_TIME_H
#define DW4_LIBC_TIME_H
#ifdef __cplusplus
extern "C" {
#endif
typedef int time_t;
struct tm {
    int tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;
};
struct tm *gmtime(const time_t *);
#ifdef __cplusplus
}
#endif
#endif
