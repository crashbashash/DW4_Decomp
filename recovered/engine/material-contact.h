/* Behavioral recovery of all seven Lua material-contact engine helpers,
 * 0x0038aca0..0x0038af70. This is not matching-build source.
 * Addresses are guest references, never host pointers. */
#ifndef DW4_RECOVERED_MATERIAL_CONTACT_H
#define DW4_RECOVERED_MATERIAL_CONTACT_H
#include <stdint.h>
typedef struct {
    void *user;
    uint32_t (*read)(void *, uint32_t address, unsigned width);
    void (*write)(void *, uint32_t address, unsigned width, uint32_t value);
} Dw4MaterialContactApi;
int dw4_mat_is_player(const Dw4MaterialContactApi *, uint32_t self);
int dw4_mat_is_all_player(const Dw4MaterialContactApi *, uint32_t self);
int dw4_mat_get_player_no(const Dw4MaterialContactApi *, uint32_t self);
int dw4_mat_is_ride_player(const Dw4MaterialContactApi *, uint32_t self, int32_t player);
int dw4_mat_is_ride_off_player(const Dw4MaterialContactApi *, uint32_t self, int32_t player);
void dw4_mat_set_run(const Dw4MaterialContactApi *, uint32_t self, uint32_t value);
int dw4_mat_get_player_status(const Dw4MaterialContactApi *, uint32_t self, int32_t player);
#endif
