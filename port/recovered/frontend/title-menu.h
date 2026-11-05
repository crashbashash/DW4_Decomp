/* Names/offsets: data/reflection.json; widths: retail lw/sw instructions.
 * Only fields used by the behavioral entry are exposed; these are host records,
 * not packed PS2 objects. */
#ifndef DW4_RECOVERED_TITLE_MENU_H
#define DW4_RECOVERED_TITLE_MENU_H
#include <stdint.h>
typedef struct {
    int32_t _gameMenuCnt, _gameMenuNext, _st0, _st1, _st2, _st3;
} Dw4TitleCtrl;
typedef struct {
    int32_t _selLang, _ctrlPos, _isOK, _comConf, _lightConf, _oldCountry;
    int32_t _dispComConf, _dispLightConf, _dispCountryConf;
} Dw4TitleOption;
typedef struct { uint32_t direction_a, direction_b, pressed, button_secondary; } Dw4TitleInput;
enum Dw4TitleToken {
    T_GAMERAM = 0x00518310,
    T_GETCOMMON = 0x00518318,
    T_CAMERAMODE = 0x00518328,
    T_LIGHTMODE = 0x00518338,
    T_j_startlogo = 0x00518370,
    T_SQ_OPEN = 0x00518380,
    T_j_startmenu01 = 0x00518388,
    T_MODELCTRL = 0x00518398,
    T_SQ_LINESL00 = 0x005183a8,
    T_ISSEQNAME = 0x005183b8,
    T_i_fadewn01 = 0x005183c8,
    T_GENERATE = 0x005183d8,
    T_SQ_BLOUT30 = 0x005183e8,
    T_ISRUN = 0x005183f8,
    T_STAGECTL = 0x00518400,
    T_stagIS09 = 0x00518410,
    T_NEXTSTAGE = 0x00518420,
    T_SQ_LINEON00 = 0x00518430,
    T_j_startmenu02 = 0x00518440,
    T_SQ_LINEUP00 = 0x00518450,
    T_SQ_LINEDW01 = 0x00518460,
    T_SQ_LINEON01 = 0x00518470,
    T_SQ_CANCEL = 0x00518480,
    T_SQ_CLOSE = 0x00518490,
    T_j_optionwin02 = 0x005184a8,
    T_SQ_BOPEN = 0x005184b8,
    T_SQ_AOPEN = 0x005184c8,
    T_j_optioncursor11 = 0x005184e0,
    T_j_optioncursor12 = 0x00518500,
    T_SQ_MOVE = 0x00518518,
    T_SQ_LINERT00 = 0x00518520,
    T_SQ_LINERT01 = 0x00518530,
    T_SQ_LINERT02 = 0x00518540,
    T_SQ_LINELF00 = 0x00518550,
    T_SQ_LINELF01 = 0x00518560,
    T_SQ_LINELF02 = 0x00518570,
    T_SQ_LINESL01 = 0x00518580,
    T_SQ_LINESL02 = 0x00518590,
    T_SQ_LINESL03 = 0x005185a0,
    T_SQ_LINEON02 = 0x005185b0,
    T_SQ_LINEON03 = 0x005185c0,
    T_SOUND = 0x005185d0,
    T_BGMSTOP = 0x005185d8,
    T_ENVSTOP = 0x005185e0,
    T_SESTOP = 0x005185e8,
    T_stagIS08 = 0x005185f0,
    T_SQ_WTOUT60 = 0x00518600,
    T_j_startback = 0x00518610,
    T_LOADCTRL2 = 0x00518620,
    T_GENERATE_TITLE = 0x00518630,
};
/* All callbacks run synchronously and in retail call order. Completion queries
 * are separate: opening/play waits and close/remove waits are not interchangeable.
 * Slot is the retail address index (0 or -1), wait is its tracked-operation flag.
 */
typedef struct {
    void *user;
    void (*model_tick)(void *);
    int (*opening_done)(void *);
    int (*closing_done)(void *);
    int (*model_exists)(void *, int slot, int target);
    void (*model_start)(void *, int slot, int target, int sequence, int wait);
    void (*model_play)(void *, int slot, int target, int sequence, int wait);
    void (*model_close)(void *, int slot, int target, int sequence, int wait);
    void (*text_show)(void *, int id, int flags);
    void (*text_hide)(void *, int id);
    void (*message_begin)(void *, int target, int node, int slot);
    void (*message_target)(void *, int target);
    void (*message_common)(void *, int target, int command);
    void (*push_string)(void *, int token);
    void (*push_int)(void *, int value);
    void (*message_end)(void *, int command);
    void (*message_send)(void *, int target, int node, int slot, int command);
    int (*read_bool)(void *, int index);
    int (*read_object)(void *, int index);
    void (*set_record)(void *, int object, int field, int value);
    void (*options_valid)(void *);
} Dw4TitleApi;
void dw4_title_tick(Dw4TitleCtrl *, Dw4TitleOption *, const Dw4TitleInput *, int, const Dw4TitleApi *);
#endif
