#ifndef DW4_IGMERSENNETWISTERRANDOMNUMBER_H
#define DW4_IGMERSENNETWISTERRANDOMNUMBER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Parses three floats from `text`, by `format` when given; nonzero on success. */
int Vec3f_FromString(const char *text, float *vector, const char *format);

#ifdef __cplusplus
}
#endif

#endif
