#ifndef DW4_IGSTRINGOBJ_H
#define DW4_IGSTRINGOBJ_H

#ifdef __cplusplus
extern "C" {
#endif

/* Nonzero when `text` ends in a dot and `extension`, compared without case; `extension` may include
 * the dot. */
int igStringObj_HasFileExtensionText(char *text, char *extension);

#ifdef __cplusplus
}
#endif

#endif
