/* beNDMWSaveIntf: the shared character-data-select interface (stagIS12's SaveIntfInfo; the same pack serves the
 * Save Keeper and the title's Game Start slot screen). Recovered from update 4081a0 (vfunc_31), the GENERATE handler
 * 40c220 (vfunc_34) and the 85 helpers 3d9de0..3f1460. Every messenger/Lua/pad/card interaction of the retail
 * bodies is a host callback, so the order of the retail sends is the order the tests assert.
 * Evidence, state map and boundaries: port/docs/save-keeper.md. */
#ifndef DW4_SAVEINTF_H
#define DW4_SAVEINTF_H
#include <stddef.h>
#include <stdint.h>
#define DW4_SI_PLAYERS 4
#define DW4_SI_SLOTS 4          /* save areas A..D = character slots of one file */
#define DW4_SI_CARD_SLOTS 5     /* memory-card rows of the slot chooser (2 in mode 0, 5 otherwise) */

/* One saved character as the interface shows it: the leading summary of the retail save record (3ee4d0). */
typedef struct {
    uint8_t used;               /* +0x28 (record ISUSE) */
    int32_t unique;             /* +0x2C (UNIQUE) */
    char model[33];             /* +0x30 digimon model name, e.g. p_dorumon */
    uint16_t name[9];           /* player name, zero padded */
    int32_t level,hp,mhp,mp,mmp;/* +0x38..+0x48 */
} dw4_si_summary;

/* A memory-card slot's scan result (card object +0x2C list entries). */
typedef struct {int ok;int32_t a,b;int flag;} dw4_si_card_slot;

typedef struct {
    void *user;
    /* MODELCTRL sends. generate = SelectReceivers(MODELCTRL, ram)+Vec3+GENERATE (3e3e00), sequence = SendNamed. */
    int (*model_generate)(void *,const char *model,int ram,const float position[3]);
    int (*model_sequence)(void *,const char *model,int ram,const char *sequence);
    int (*model_is_sequence)(void *,const char *model,int ram,const char *sequence); /* ISSEQNAME (3e4210) */
    int (*model_is_running)(void *,const char *model,int ram);                       /* ISRUN (3e4480) */
    /* TEXTCTL (3eba10/3ebce0/3ec120) and the Lua text scripts (txt_mem.lua / txt_Tar.lua) run with call numbers. */
    int (*text_clear)(void *,const char *group,const char *font);
    int (*text_set)(void *,const char *group,const char *font,int align,int cancel_colour,const char *ascii,const uint16_t *wide);
    int (*text_script)(void *,const char *chunk,int call);
    /* Pad words of bePadManager_GetPadForPlayer: horizontal edges|repeats (+0x1C|+0x20) and digital (+0x48,+0x4C). */
    int (*pad)(void *,int player,uint32_t *horizontal,uint32_t *digital_edges,uint32_t *digital_repeats);
    /* GAMERAM GETPLAYER ISUSE / CURRENT2BASE / GAMESTART, and the player's current record summary (3ee6d0). */
    int (*player_in_use)(void *,int player);
    int (*player_current_to_base)(void *,int player);
    int (*player_summary)(void *,int player,dw4_si_summary *);
    int (*player_start_game)(void *,int player,const char *model); /* GAMERAM GAMESTART (title flow, player 0 only) */
    int (*player_remove)(void *,int player);                       /* GAMERAM GAMEREMOVE (command 6) */
    /* LoadIntf2: a pad is connected for the player (bePadManager_GetPadForPlayer(...)->+8), and GAMERAM GAMEDATAINIT. */
    int (*pad_connected)(void *,int player);
    int (*player_data_init)(void *,int player);
    /* DATABASE shinka NAME for a model row of the digimon table. */
    int (*species_name)(void *,int row,char *out,size_t cap);
    /* SAVEUTILITY requests (3f1490): kinds 0 FILEMAKE 1 FILEFIND 2 FORMAT 3 USE_CHECK 4 READ_MEDIA 5 WRITE_MEDIA
     * 6 GETFREESIZE 7 REPORT_GAMEDATA. A request returns 0 when accepted; poll done, then read the result code
     * (2 = OK). card_state fills the card's present/unformatted flags and the per-slot scan results. */
    int (*card_request)(void *,int kind,int slot,int player,int area);
    int (*card_done)(void *,int *result);
    int (*card_state)(void *,int *present,int *unformatted,dw4_si_card_slot slots[DW4_SI_CARD_SLOTS],int *slot_count);
    /* READ_MEDIA's payload: the saved summaries of the four areas of a card slot. WRITE_MEDIA is carried by
     * card_request (the player's record goes into the given area). */
    int (*card_read)(void *,int slot,dw4_si_summary areas[DW4_SI_SLOTS]);
    /* LoadIntf2 (title Call Digimon): the chosen card area becomes the player's character (GAMEDATAINIT's successor 3ef5d0, then
     * BASE2CURRENT and RECALCPLAYER), and hostLoad.lua's LISsetDifficultMax for the loaded character (0 none, 1 Normal/Hard, 2 three rows). */
    int (*player_restore)(void *,int player,int card_slot,int area);
    int (*difficulty_cap)(void *,int player);
    /* LoadIntf2 Create (state 8's new-character commit): GAMERAM GAMEDATAINIT, then GAMESTART with the starter's player model
     * (p_agumon/p_vmon/p_girumon/p_dorumon) and the NameSel name (eight UCS-2 codes, zero padded), then GETPLAYER UNIQUE = the
     * low word of the world clock (sys+0x50, passed in as unique). */
    int (*player_create)(void *,int player,const char *model,const uint16_t name[8],int32_t unique);
    /* A raw MODELCTRL send without the window tracker (38e5f0): GENERATE with no operand, MOVETRANS "V<..>/V<..>", and the
     * starter preview's SQ_ENTR/SQ_EXIT. data may be NULL. */
    int (*model_send)(void *,const char *model,int ram,const char *key,const char *data);
    /* The world clock (sys+0x50 _worldTime, nanoseconds). */
    int64_t (*world_ns)(void *);
    /* 3a7a20/3a7e90: a named timer that holds a notice for at least the given nanoseconds. */
    int (*timer_start)(void *,const char *name,int64_t nanoseconds);
    int (*timer_done)(void *,const char *name);
    /* Named errors for retail paths the host cannot serve. */
    const char *error;
} dw4_saveintf_host;

typedef struct dw4_saveintf dw4_saveintf;
/* mode: COMMONINTF +0x38, the call-number set (0 = 0x1xxx, 1 = 0x2xxx, 2 = 0x3xxx); the Save Keeper runs mode 2. */
dw4_saveintf *dw4_saveintf_open(const dw4_saveintf_host *,int mode,const int joined[DW4_SI_PLAYERS]);
/* beNDMWLoadIntf2 (stagIS13's LoadIntf2Info): the same toolkit with the load/join screen's own update (3e4750) and
 * receiver (3e9430). COMMONINTF +0x38 is 0 in both of its modes. The states a player without data reaches (Create/Call, starter,
 * name entry, card load, difficulty) run for the title (dw4_loadintf_open_title); a joining player 1..3 has no pad in this port. */
dw4_saveintf *dw4_loadintf_open(const dw4_saveintf_host *,const int joined[DW4_SI_PLAYERS]);
/* The title's Game Start slot screen runs LoadIntf2 for player 0 only, from control state 0: the base panels open, the Create/Call
 * window (control state 3) opens; Create runs the starter choice (4, MakeChr), the name entry (5, NameSel) and the new-character
 * commit and log-in prompt (8); Call runs the memory-card chooser (6), data select (7) and the difficulty/log-in prompt (8).
 * dw4_saveintf_title_state: 0 running, 1 finished (START pressed). For a called character card_slot/area/difficulty name the card
 * data; for a created one card_slot and area are -1 and the scene's GETPLAYER 0 record holds the new character. */
dw4_saveintf *dw4_loadintf_open_title(const dw4_saveintf_host *);
/* The Create/Call window is open and waiting for the pad (control state 3, sub 2). */
int dw4_saveintf_title_ready(const dw4_saveintf *);
int dw4_saveintf_title_state(const dw4_saveintf *,int *card_slot,int *area,int *difficulty);
/* Create diagnostics: MakeChr _chaSelDegi (0 agumon, 1 vmon, 2 girumon, 3 dorumon), and the NameSel state: the name's UCS-2 codes
 * (zero padded, nine), _nameCurPos, _tatePoint (key row), _yokoPoint + _yokoCurPos (the highlighted key) and _st0. */
typedef struct {int species;uint16_t name[9];int pos,row,first,column,st0,question;} dw4_saveintf_create_trace;
void dw4_saveintf_create_diagnostics(const dw4_saveintf *,int player,dw4_saveintf_create_trace *);
void dw4_saveintf_close(dw4_saveintf *);
/* SAVEINTF_ALL GENERATE (vfunc_34 for every player): builds the per-player controllers once. */
int dw4_saveintf_generate(dw4_saveintf *);
/* One update of every player's vfunc_31 (item order 0..3). Returns 0, or -1 with dw4_saveintf_error set. */
int dw4_saveintf_update(dw4_saveintf *);
const char *dw4_saveintf_error(const dw4_saveintf *);

/* COMMONINTF as the SaveCtrl host sees it (dw4/savectrl.h callbacks). */
int  dw4_saveintf_scene_state(const dw4_saveintf *);   /* +0x30: 0 loading, 2 busy, 3 finished */
void dw4_saveintf_scan(dw4_saveintf *);                /* 3ecc60 */
int  dw4_saveintf_select_data(dw4_saveintf *);          /* SETSELECT_DATA (vfunc_34 command 6): GAMEREMOVE every player without chosen data */
void dw4_saveintf_close_players(dw4_saveintf *);       /* per item: +0xE=0, state 2, counters 0 */
int  dw4_saveintf_player_closed(const dw4_saveintf *,int player);  /* item +0xE */
int  dw4_saveintf_player_done(const dw4_saveintf *,int player);    /* item +0xD */
/* Diagnostics for tests. */
typedef struct {int state,sub,subsub,subsubsub;int control,control_sub,control_subsub;} dw4_saveintf_trace;
void dw4_saveintf_diagnostics(const dw4_saveintf *,int player,dw4_saveintf_trace *);
#endif
