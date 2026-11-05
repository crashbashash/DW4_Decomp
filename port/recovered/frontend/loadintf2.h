/* recovered/frontend/loadintf2.h — behavioral interface for the Game Start
 * slot/character/name/difficulty/card interface, Gap::Bec::beNDMWLoadIntf2.
 *
 * Host records, not packed PS2 objects.  Field offsets and widths come from
 * data/reflection.json and the retail lw/sb/lbu instructions at
 *
 *   0x003e4750  vfunc_31  the per-frame master update   (18,624 bytes)
 *   0x003e9430  vfunc_34  the family message handler     (8,252 bytes)
 *
 * The recovery runs over one flat, word-addressed "world" (peek/poke/call) so
 * it mirrors the retail instruction stream; the verifier runs the same world
 * under a restricted R5900 interpreter and compares the two.
 *
 * Naming note: the second argument ("frame") is the per-frame context the
 * manager framework passes to a base-info manager method.  Only +0x08 (the
 * player/interface index) and +0x28 (the *named work registry*) are read.  The
 * C++ owner of "frame" is not pinned; it is left structural.
 *
 * The named working set and message protocol are documented in
 * docs/engine/load-intf2.md; the offset comments below name each reflected
 * field from data/reflection.json.
 */
#ifndef DW4_RECOVERED_LOADINTF2_H
#define DW4_RECOVERED_LOADINTF2_H
#include <stdint.h>

typedef struct {
    void *user;
    int32_t (*peek)(void *user, int32_t addr, int width);          /* sign-extended */
    void    (*poke)(void *user, int32_t addr, int width, int32_t v);
    /* a[0..7] are the EE argument registers a0..a3 then t0..t3; missing ones zero. */
    int32_t (*call)(void *user, int32_t addr, const int32_t a[8]);
} Dw4LoadIntf2Api;

/* Named working set (FUN_003022c0 lookup keys; string tokens in the ELF). */
#define LI2_COMMONINTF   0x5172a0   /* "COMMONINTF" */
#define LI2_CTRL         0x5172b0   /* "CTRL"        */
#define LI2_MAKECHR      0x5172b8   /* "MAKECHR"     */
#define LI2_COMMDLCTRL   0x5172c0   /* "COMMDLCTRL"  */
#define LI2_MESWIN       0x5172d0   /* "MESWIN"      */
#define LI2_SELSLOT      0x5172d8   /* "SELSLOT"     */
#define LI2_NAMESEL      0x5172e0   /* "NAMESEL"     */
#define LI2_TEXTORDER    0x5172e8   /* "TEXTORDER"   */
#define LI2_DEGISTATECTRL 0x5172f8  /* "DEGISTATECTRL" */
#define LI2_DATASELINTF  0x517308   /* "DATASELINTF" */
#define LI2_DIFFSELECT   0x517318   /* "DIFFSELECT"  */

/* Front-end UI object and animation tokens the update drives. */
#define LI2_T_GAMERAM       0x517338
#define LI2_T_GETPLAYER     0x517340
#define LI2_T_MODELCTRL     0x5171f8
#define LI2_T_ISRUN         0x517228
#define LI2_T_GENERATE      0x517208
#define LI2_T_HOSTLOAD      0x517450
#define LI2_T_GAMEDATAINIT  0x517408
#define LI2_T_GAMESTART     0x517418
#define LI2_T_JCHRSELMESS   0x517360
#define LI2_T_JLINEWIN01    0x517370
#define LI2_T_JCHRSELBASE   0x517328
#define LI2_T_SQOPEN        0x516cd0
#define LI2_T_SQCLOSE       0x516d30
#define LI2_T_SQCANCEL      0x516d50

/* Message protocol tokens the handler builds and tears down. */
#define LI2_ALL          0x5175d8   /* LOADINTF2_ALL */
#define LI2_IF           0x5175e8   /* LOADINTF2     */
#define LI2_LOADCTRL2    0x5175f8   /* LOADCTRL2     */
#define LI2_GETCOMMON    0x517608   /* GETCOMMON     */
#define LI2_GAMEREMOVE   0x517618   /* GAMEREMOVE    */
#define LI2_MSG_517338   0x517338
#define LI2_MSG_517340   0x517340
/* gp-relative lazy-init flag read by the getter guards. */
#define LI2_GP_FLAG      0x554c14

/* Reference scratch slots standing in for the retail stack temporaries the
 * update copies vec3s through; the verifier normalises stack/temp pointers. */
#define LI2_TMP(c)       (0x01060000 + (c) * 0x40)


void    dw4_loadintf2_update(int32_t self, int32_t frame, const Dw4LoadIntf2Api *api);
int32_t dw4_loadintf2_message(int32_t self, int32_t frame, int32_t info, const Dw4LoadIntf2Api *api);

#endif /* DW4_RECOVERED_LOADINTF2_H */
