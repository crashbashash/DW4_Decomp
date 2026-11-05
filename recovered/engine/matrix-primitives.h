#ifndef DW4_RECOVERED_MATRIX_PRIMITIVES_H
#define DW4_RECOVERED_MATRIX_PRIMITIVES_H
#include <stdint.h>
typedef struct {
    void *user;
    uint32_t (*read)(void *,uint32_t);
    void (*write)(void *,uint32_t,uint32_t);
} Dw4MatrixApi;
void dw4_matrix_copy(const Dw4MatrixApi *,uint32_t destination,uint32_t source);
void dw4_matrix_from_translation(const Dw4MatrixApi *,uint32_t matrix,uint32_t vector);
void dw4_matrix_set_translation(const Dw4MatrixApi *,uint32_t matrix,uint32_t vector);
void dw4_matrix_get_translation(const Dw4MatrixApi *,uint32_t matrix,uint32_t vector);
void dw4_matrix_translate_local(const Dw4MatrixApi *,uint32_t matrix,uint32_t vector);
#endif
