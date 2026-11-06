/* beNDMWSaveCtrl: the controller that runs the data-select / save scene (stagIS12's SaveCtrlInfo).
 * Recovered from update 407120..407a60 (vfunc_31) and the SAVECTRL GENERATE handler 407aa0
 * (vfunc_34); every messenger call of the retail body is a host callback so the sequencing is
 * exactly the retail order. */
#ifndef DW4_SAVECTRL_H
#define DW4_SAVECTRL_H
#define DW4_SAVECTRL_PLAYERS 4
typedef struct {
    void *user;
    /* SAVEUTILITY (3f1270/3f12f0/3f1380/3f13d0): GENERATE with the count 4, ISRDY and REMOVE. */
    int  (*card_generate)(void *);   /* nonzero: a SAVEUTILITY receiver answered (GetBoolCount > 0) */
    int  (*card_ready)(void *);      /* ISRDY */
    void (*card_remove)(void *);     /* REMOVE */
    /* MODELCTRL sends to j_chrselback / i_fadewn01 (id 0). */
    void (*model_send)(void *,const char *model,const char *key);
    int  (*model_is_sequence)(void *,const char *model,const char *sequence); /* ISSEQNAME */
    int  (*model_is_running)(void *,const char *model);                        /* ISRUN */
    /* SAVEINTF_ALL and the COMMONINTF block (the four per-player items). */
    void (*intf_generate)(void *);   /* SAVEINTF_ALL GENERATE */
    int  (*intf_state)(void *);      /* COMMONINTF +0x30: 0 loading, 2 busy, 3 finished */
    void (*intf_scan)(void *);       /* 3ecc60: mark the slots' data from the card scan */
    void (*players_close)(void *);   /* per player: +0xE=0, +0x24=2, +0x28=+0x2C=+0x30=0 */
    int  (*player_ready)(void *,int player);  /* item +0xE: the player's interface has closed */
    int  (*player_done)(void *,int player);   /* item +0xD: the player's data was chosen */
    void (*intf_select_data)(void *);         /* SAVEINTF_ALL SETSELECT_DATA */
    /* GAMERAM GETCOMMON: BKCHIPSTAGE[i] = NULL for each player that is not done, NINZU = count. */
    void (*publish_players)(void *,int count,const int done[DW4_SAVECTRL_PLAYERS]);
    /* STAGECTL NEXTSTAGE (after PLAYERPOINT SETGENERATEPOS when generate_pos >= 0). */
    void (*go)(void *,const char *stage,int generate_pos);
    /* SAVECTRL GENERATE: asks the messenger to build the controller state (vfunc_34 -> dw4_savectrl_generate). */
    void (*self_generate)(void *);
} dw4_savectrl_host;
typedef struct {
    int built,load;         /* load: beNDMWLoadCtrl2 (stagIS13), the same controller driving LOADINTF2_ALL */
    int phase,sub,subsub;   /* CTRL +0x1C, +0x20, +0x24 */
    int card_present,card_done; /* the card helper's bytes +0xC and +0xD */
} dw4_savectrl;
/* vfunc_34 case GENERATE: phase 1, all counters zero (a second GENERATE does nothing). */
void dw4_savectrl_generate(dw4_savectrl *);
/* beNDMWLoadCtrl2 vfunc_34 (3f2490) GENERATE and its update vfunc_31 (3f1a80). The update is SaveCtrl's with the
 * interface name LOADINTF2_ALL and a different exit: both its modes request stagML11 (the hub mode at generate
 * position 4). Title mode (the GENERATE that carries integers: fade wait, TITLE2 GAMESTART, hostLoad/gameStart.lua)
 * is not ported: title != 0 returns -1. */
int dw4_loadctrl_generate(dw4_savectrl *,int title);
/* The hub exit of 3f1a80 phase 3 (PLAYERPOINT SETGENERATEPOS 4, then NEXTSTAGE stagML11). */
const char *dw4_loadctrl_exit_stage(int *generate_pos);
/* vfunc_31: one update. Before GENERATE it only sends SAVECTRL GENERATE through the host. */
void dw4_savectrl_update(dw4_savectrl *,const dw4_savectrl_host *);
/* The phase-3 exit (407120 case 3/1): with no finished player the scene leaves for the title (stagis10, generate_pos
 * -1); otherwise PLAYERPOINT SETGENERATEPOS 2 and stagML12. */
const char *dw4_savectrl_exit_stage(int done_players,int *generate_pos);
#endif
