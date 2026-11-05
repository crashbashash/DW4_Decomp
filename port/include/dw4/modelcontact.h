#ifndef DW4_MODELCONTACT_H
#define DW4_MODELCONTACT_H
#include "dw4/script.h"
#include "dw4/statusapply.h"
/* Snapshot of the matrix and scalar globals published by retail394400 for a
 * synchronous hit callback. The owner supplies actual hit/shooter identity;
 * geometry selection and collision dispatch are separate owners. */
/* Combat rules the BLT and MDL contact calls reach through (FIGHTCALC owner). Return 0 on success. `user` is the owner.
 * `target` / `attacker` below are the status of the work the retail rule queries for its _downDataList (the receiver for the BLT calls, the
 * attacking enemy for the BLP calls); NULL when that model has none. */
typedef struct {
    void *user;
    int (*is_hit)(void *user,int32_t shooter,int32_t row,int32_t attack,const dw4_status *target,int *hit);
    int (*is_critical)(void *user,int32_t shooter,int32_t row,int32_t attack,int *critical);
    /* out: damage, element (-1 none), high-roll flag */
    int (*damage)(void *user,int32_t shooter,int32_t row,int32_t attack,int critical,const dw4_status *target,int32_t out[3]);
    int (*stun_time)(void *user,int32_t shooter,int32_t row,int32_t max_hp,int32_t damage,int32_t *time);
    int (*skill_up)(void *user,int32_t shooter,int32_t attack,int32_t hit,int32_t critical);
    int (*exp_up)(void *user,int32_t shooter,int32_t row,int32_t *share);
    void (*display_damage)(void *user,int32_t value);
    void (*display_exp)(void *user,int32_t value);
    /* The floating number of FUN_00373ef0 (row 0 damage, 1 exp, 3 player damage) at the hit model's world position: called after the display_* callback. */
    void (*display_popup)(void *user,int32_t row,int32_t value,const float position[3]);
    /* Enemy-to-player rules (BLP calls): target player slot, the attacker's enemy row, the attack number. */
    int (*e2p_is_hit)(void *user,int32_t player,int32_t row,int32_t attack,int *hit);
    int (*e2p_damage)(void *user,int32_t player,int32_t row,int32_t attack,const dw4_status *attacker,int32_t out[3]);
    int (*e2p_rank)(void *user,int32_t player,int32_t attack,int32_t hp_after,int32_t damage,int32_t *rank);
    void (*display_damage_player)(void *user,int32_t player,int32_t value);
    int (*e2p_stun)(void *user,int32_t player,int32_t row,int32_t attack,int32_t damage,int32_t rank,const dw4_status *attacker,int32_t *time);
    int (*e2p_has_effect)(void *user,int32_t attack);
    /* Shared seam for the technique/status/support wiring (appended so independent branches only fill their own slot; all NULL-safe).
     * Status-time rules: `method` is the script call (BLTgetPoisonTime ... BLPgetPowerDownTime), `what` its selector ("TIME", "SUBAYASA", ... or NULL);
     * return 0 and *out on success, 1 when the rule appends nothing, -1 on error. The BLT calls reach p2e_status only for the technique base numbers the
     * retail wrappers accept (see modelcontact.c); `row` is the target's enemy row (P2E) or the attacking enemy's row (E2P). */
    int (*p2e_status)(void *user,int32_t shooter,int32_t row,int32_t attack,const char *method,const char *what,int32_t *out);
    int (*e2p_status)(void *user,int32_t player,int32_t row,int32_t attack,const char *method,const char *what,int32_t *out);
    /* BLPcalcKoukaMagic (FIGHTCALC P2PKOUKAMAGIC): receiver slot, shooter slot, bullet kind; result is the script's return value. */
    int (*p2p_magic)(void *user,int32_t receiver,int32_t shooter,int32_t attack,int32_t *result);
    /* BLPgetAttackZokusei / GETPATKZOKUSEI: the shooter's element for an attack (0..4, -1 none). */
    int (*attack_element)(void *user,int32_t shooter,int32_t attack,int32_t *element);
} dw4_model_fight;
typedef struct {
    float world[16];
    int32_t bullet_kind,bullet_box,shoot_ram_no;
    int damage_turn;
    char result[192];
    /* Combat context (NULL fight: only the geometry/identity calls above exist). */
    const dw4_model_fight *fight;
    int32_t target_row,target_max_hp,target_slot,source_row;
    const dw4_status *receiver_status,*source_status;   /* the receiver's and the shooter's status (NULL: none), for the _downDataList reads */
    int32_t cached[3];        /* last BLTgetDamageValue: damage, element, high roll (retail 0x58a330/338/340) */
    const char *sequence;     /* the receiver's current sequence, for MDLisSeqName */
    const char *bullet_name;  /* MDLgetBulletName */
} dw4_model_contact;
/* Original lobby player's 60000 probe, delivered synchronously after the
 * source's subcommand update. Source matrix/box belong to that update, not to
 * a delayed SD pointer. Geometry cache keys use the session world timestamp. */
typedef struct {
    float source_world[16],box[6];
    int32_t shoot_ram_no;
    int64_t world_ns;
} dw4_model_talk_probe;
/* Returns 1 for another method/missing context, 0 handled, -1 malformed input.
 * String output borrows result until the next call. No simulation is advanced. */
int dw4_model_contact_call(dw4_model_contact *,const char *,const dw4_script_value *,size_t,
    dw4_script_value *,char *,size_t);
#endif
