/* Scene-owned TEXTCTL, SELECTCTRL and subwindow completion routing. */
#ifndef DW4_DIALOGUE_H
#define DW4_DIALOGUE_H
#include "dw4/stageobjects.h"
#include "dw4/gl_layer.h"
#include "dw4/selectctrl.h"
#include "dw4/fontlayout.h"
#include "dw4/subwindow.h"
typedef struct dw4_dialogue dw4_dialogue;
typedef struct {
    const char *group,*name,*kind;
    float x,y,width,height,color[3]; /* authored font units, +Y up */
    int visible,align;
    const uint32_t *codes;
    size_t count;
} dw4_dialogue_text;
dw4_dialogue *dw4_dialogue_open(dw4_scriptservices *,uint64_t scope,const dw4_stageobjects *);
void dw4_dialogue_close(dw4_dialogue *);
/* Drop the font atlases from a GPU layer's texture cache before dw4_dialogue_close frees them. */
void dw4_dialogue_forget_gpu(const dw4_dialogue *,dw4_gl_layer *);
/* Each player owns a separate original RAM slot. No tick during world holds. */
void dw4_dialogue_input(dw4_dialogue *,unsigned player,uint32_t analog,
    uint32_t held,uint32_t pressed);
int dw4_dialogue_tick(dw4_dialogue *);
const char *dw4_dialogue_error(const dw4_dialogue *);
int dw4_dialogue_claimed(const dw4_dialogue *);
/* A message or choice page of an NPC talk is showing (visible TALKFONT* text). */
int dw4_dialogue_talk_open(const dw4_dialogue *);
size_t dw4_dialogue_text_count(const dw4_dialogue *);
const dw4_dialogue_text *dw4_dialogue_text_at(const dw4_dialogue *,size_t);
/* Native beUnicodeObj overloads. The buffer contains original 16-bit font codes,
 * including icons, not UTF-8 or host pointers in guest fields. TEXTSET copies the
 * object into owned geometry; REPLACEUNKNOWN mutates the supplied object in place
 * against the first collected font, matching 382c68. */
int dw4_dialogue_set_unicode(dw4_dialogue *,const char *group,const char *name,
    const uint16_t *codes,size_t count);
int dw4_dialogue_replace_unknown(dw4_dialogue *,uint16_t *codes,size_t count,uint16_t replacement);
/* Renderer-neutral text triangles; borrowed until next call or scene teardown.
 * Samples authored ancestor transforms, switches and native layer masks; no tick.
 * Returns -1 on allocation/transform failure. */
int dw4_dialogue_draw(dw4_dialogue *,unsigned width,unsigned height,
    const dw4_ui_draw **draws,size_t *count);
/* Limit dw4_dialogue_draw to the text drawn before (part 1) or after (part 2) the models of `layer` and above; NULL/0 draws all text. */
void dw4_dialogue_text_split(dw4_dialogue *,const char *layer,int part);
/* Field stages (no lobby UI): TALKFONT text follows the models of the layers from the split on, as the FONT layer follows WN04. */
void dw4_dialogue_talk_late(dw4_dialogue *,int on);
/* An active status/menu owner must supply REMOVE and ISRUN. The borrowed owner
 * outlives this scene; ISRUN stays true until its real close completes. */
int dw4_dialogue_subwindow(dw4_dialogue *,dw4_script_binding,void *);
/* Scene-owned status slots and concrete menu factory interface. */
dw4_subwindows *dw4_dialogue_subwindows(dw4_dialogue *);
#endif
