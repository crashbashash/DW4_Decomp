#ifndef DW4_RECOVERED_MATERIAL_RUNTIME_H
#define DW4_RECOVERED_MATERIAL_RUNTIME_H
#include <stdint.h>
/* Behavioral reference; guest addresses and controlled platform/service leaves. */
typedef struct {
    void *user;
    uint32_t (*read)(void *, uint32_t, unsigned);
    void (*write)(void *, uint32_t, unsigned, uint32_t);
    uint32_t (*call)(void *, uint32_t, const uint32_t[8]);
} Dw4MaterialRuntimeApi;
/* scratch is a caller-owned 320-byte guest range, separate from runtime objects. */
void dw4_material_update(const Dw4MaterialRuntimeApi *, uint32_t self,
                         uint32_t ram, uint32_t scratch);
int dw4_material_message(const Dw4MaterialRuntimeApi *, uint32_t self,
                         uint32_t ram, uint32_t message);
void dw4_material_initialize(const Dw4MaterialRuntimeApi *, uint32_t self);
void dw4_material_register(const Dw4MaterialRuntimeApi *, uint32_t self, uint32_t selector);
/* 0x18b630: inclusive three-axis box membership; returns only 0 or 2. */
int dw4_material_box_contains(const Dw4MaterialRuntimeApi *, uint32_t box, uint32_t point);
void dw4_material_accumulate(const Dw4MaterialRuntimeApi *, uint32_t self,
                             uint32_t masks, uint32_t search, int32_t player,
                             uint32_t point, uint32_t materials);
#endif
