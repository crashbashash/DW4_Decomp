/* The shared-pool globals are declared as 4-element arrays so they stay out of small data (lui/lw
 * addressing). Each arm of the pool fill stores the slot itself (the store is duplicated). */

#include "dw4/pool_slot.hpp"
/* Only the fields this method touches are named. */
struct igVisualContextCapabilityManager {
    int vtable;
    int _pad04[5];
    igObjectSlotView *pool24;
    igObjectSlotView *pool28;
    igObjectSlotView *pool32;
    igObjectSlotView *pool36;
    igObjectSlotView *pool40;
    igObjectSlotView *pool44;
    igObjectSlotView *pool48;
    igObjectSlotView *pool52;
    igObjectSlotView *capabilities56;
    int _pad60[61];
    igObjectSlotView *helper304;
    igObjectSlotView *helper308;
};

extern "C" {

extern void Gap__Core__igObject__vfunc_01(void *self);
extern int FUN_00165ce0(void *self);
extern int FUN_00165d10(void *self);
extern igObjectSlotView *FUN_002b79d0(int arg);
extern igObjectSlotView *FUN_0014ee00(int arg);
extern igObjectSlotView *FUN_0014e930(int arg);

extern igObjectSlotView *g_pool_00560760[4];
extern igObjectSlotView *g_pool_00560768[4];
extern igObjectSlotView *g_pool_00560770[4];
extern igObjectSlotView *g_pool_00560778[4];
extern igObjectSlotView *g_pool_00560780[4];
extern igObjectSlotView *g_pool_00560788[4];
extern igObjectSlotView *g_pool_00560790[4];
extern igObjectSlotView *g_pool_00560798[4];
extern int DAT_005870b8[4];
extern int DAT_00587068[4];
extern int DAT_00587060[4];
extern int DAT_005870e8[4];
extern int DAT_00587078[4];
extern int DAT_00587058[4];

}

extern "C" void FUN_00164f50(igVisualContextCapabilityManager *self)
{
    igObjectSlotView *caps;
    int arg;

    Gap__Core__igObject__vfunc_01(self);

    fill_pool_slot(self, &self->pool24, g_pool_00560760[0], DAT_005870b8);
    fill_pool_slot(self, &self->pool28, g_pool_00560768[0], DAT_00587068);
    fill_pool_slot_plain(self, &self->pool32, g_pool_00560770[0]);
    fill_pool_slot(self, &self->pool36, g_pool_00560778[0], DAT_00587060);
    fill_pool_slot(self, &self->pool40, g_pool_00560780[0], DAT_005870e8);
    fill_pool_slot(self, &self->pool44, g_pool_00560788[0], DAT_00587078);
    fill_pool_slot_plain(self, &self->pool48, g_pool_00560790[0]);
    fill_pool_slot(self, &self->pool52, g_pool_00560798[0], DAT_00587058);

    caps = FUN_002b79d0(FUN_00165ce0(self));
    retain(caps);
    release(self->capabilities56);
    self->capabilities56 = caps;
    self->capabilities56->vfunc_29();

    arg = FUN_00165d10(self);
    release(self->helper304);
    self->helper304 = FUN_0014ee00(arg);
    arg = FUN_00165d10(self);
    release(self->helper308);
    self->helper308 = FUN_0014e930(arg);
}
