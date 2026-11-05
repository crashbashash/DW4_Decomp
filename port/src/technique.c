#include "dw4/technique.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Retail facts (port/docs/combat.md "Technique firing (R1 panel)"): the panel update accepts input only once its frame counter reached 2
 * (Ram+0x24) and the named timer FIRE has elapsed; a fired technique starts FIRE with pcTech.DELAY frames (60 Hz), a refused press with 0x0fe502aa ns
 * (about 16 frames). Cursor: a four-row window without wrap. MP is charged in the panel when Cross is accepted (strictly less MP refuses). */
#define DEBOUNCE_FRAMES 2
#define NG_LOCK_NS 0x0fe502aaULL
#define PAD_R1 0x800u
#define PAD_CROSS 0x4000u
#define FLIGHTS 4
/* ASSUMPTIONS, not recovered: the cast's bullet. Retail spawns an effect model (x_200fire01 ...) through the action-starter rows; that dispatcher and
 * the bullet's MOVE Push speed are not recovered. Verified from the data: x_200fire01 SQ_ATCK02 has one HITBOX kind 40000 with a 4x4x4 box at the
 * bullet origin, and its starter row for the projectile is offset (0,6,0), delay 0, not locked to the player. The port flies one such box forward from
 * that offset at BULLET_SPEED units per frame (a step no longer than the box, so nothing is skipped) for BULLET_LIFE frames, and ends it on its first
 * contact (the 123-byte bht script is just MDLsetSeq(SQ_ERAS), registered for BHit/WHit/FHit). Speed and lifetime are guesses (the inferred retail
 * lifetime is 73-83 frames); every family uses the fire geometry, a support technique delivers its box once, on the caster. */
#define BULLET_SIZE 4.0f
#define BULLET_HEIGHT 6.0f
#define BULLET_SPEED 2.0f
#define BULLET_LIFE 75
typedef struct {int live,age,attack,support;float world[16];} flight;
typedef struct {
    int open,age,cursor,offset,count;
    int32_t row[DW4_TECHNIQUE_LIST],base[DW4_TECHNIQUE_LIST];int color[DW4_TECHNIQUE_LIST];
    int ret_fire;dw4_technique_cast cast;
    int locked;uint64_t lock_until_ns;
    flight bullet[FLIGHTS];unsigned next_bullet;
} slot_state;
struct dw4_technique {dw4_playerrecords *records;const dw4_databases *databases;dw4_dbtable tech;slot_state slot[4];};
dw4_technique *dw4_technique_open(dw4_playerrecords *records,const dw4_databases *databases)
{
    if(!records || !databases)return NULL;
    dw4_dbtable tech=dw4_databases_table(databases,"pcTech");if(!dw4_dbtable_valid(tech))return NULL;
    dw4_technique *t=calloc(1,sizeof *t);if(!t)return NULL;
    t->records=records;t->databases=databases;t->tech=tech;return t;
}
void dw4_technique_close(dw4_technique *t){free(t);}
/* PanelObjectWaza::vfunc_21: the list is a copy of the player's WAZALIST; a row is colour 1 while the current MP is below its pcTech MP. The cursor is
 * reset only when the count changes. */
static void refresh(dw4_technique *t,int slot)
{
    slot_state *p=t->slot+slot;
    dw4_property_folder *f=dw4_playerrecords_get(t->records,"GETPLAYER",slot);
    size_t n=0;const dw4_item_record *w=f?dw4_property_items(f,"WAZALIST",&n):NULL;int32_t mp=0;
    if(f)dw4_property_number(f,"MP",&mp);
    if(n>DW4_TECHNIQUE_LIST)n=DW4_TECHNIQUE_LIST;
    for(size_t i=0;i<n;i++) {
        int32_t cost=0;dw4_dbt_number(t->tech,w[i].record,"MP",&cost);
        p->row[i]=w[i].record;p->base[i]=w[i].revision;p->color[i]=mp<cost;
    }
    if((int)n!=p->count){p->count=(int)n;p->cursor=p->offset=0;}
}
int dw4_technique_panel_get(const dw4_technique *t,int slot,dw4_technique_panel *out)
{
    if(!t || !out || slot<0 || slot>3)return -1;
    const slot_state *p=t->slot+slot;
    *out=(dw4_technique_panel){.open=p->open,.cursor=p->cursor,.offset=p->offset,.count=p->count};
    memcpy(out->row,p->row,sizeof out->row);memcpy(out->base,p->base,sizeof out->base);memcpy(out->color,p->color,sizeof out->color);
    return 0;
}
/* FUN_003d0a90 (GENERATEWAZA): active, state 0, no pending fire, page 0. The FIRE timer is a named timer on the manager and is kept (assumption:
 * the message does not clear it). */
static void open_panel(dw4_technique *t,int slot)
{
    slot_state *p=t->slot+slot;
    p->open=1;p->age=0;p->ret_fire=0;refresh(t,slot);
}
/* FUN_003ce7e0 / FUN_003ce890: up decrements the cursor, or the offset at the top row; down stops at the last entry and scrolls only while more
 * entries remain below the window. */
static void move_up(slot_state *p){if(p->cursor>0)p->cursor--;else if(p->offset>0)p->offset--;}
static void move_down(slot_state *p)
{
    if(p->cursor+p->offset>=p->count-1)return;
    if(p->cursor<DW4_TECHNIQUE_ROWS-1)p->cursor++;else if(p->offset+DW4_TECHNIQUE_ROWS<p->count)p->offset++;
}
/* The families the 80000+base attack numbers belong to: Heal Lt, Heal, Raise, Cure Lt, Cure, Speed, Resist, Power (the stage pack's x_250*hit01 and
 * the reanimation section carry HITBOX kinds 80040/45/50/55/60/65/75/80); every other family, Freeze / Power Dwn / Sleep / Bind included, is 40000+base. */
static int support_base(int32_t base)
{
    static const int32_t bases[]={40,45,50,55,60,65,75,80};
    for(unsigned i=0;i<sizeof bases/sizeof *bases;i++)if(bases[i]==base)return 1;
    return 0;
}
/* PanelObjectWaza::vfunc_22 and its caller in vfunc_31. */
static void fire(dw4_technique *t,int slot,uint64_t now_ns)
{
    slot_state *p=t->slot+slot;int index=p->cursor+p->offset;
    if(!p->count)return;   /* _listKazu == 0: Cross does nothing */
    p->locked=1;p->lock_until_ns=now_ns+NG_LOCK_NS;   /* the refused-press lockout, replaced below by the technique's DELAY on success */
    if(index>=p->count || p->color[index])return;
    dw4_property_folder *f=dw4_playerrecords_get(t->records,"GETPLAYER",slot);
    int32_t cost=0,mp=0,delay=0;const char *label;
    if(!f || dw4_property_number(f,"MP",&mp) || dw4_dbt_number(t->tech,p->row[index],"MP",&cost) || mp<cost)return;
    label=dw4_dbt_string(t->tech,p->row[index],"LABEL");dw4_dbt_number(t->tech,p->row[index],"DELAY",&delay);
    if(!label || !*label || strlen(label)>=sizeof p->cast.label || delay<=0 || dw4_property_set_number(f,"MP",mp-cost))return;
    p->cast=(dw4_technique_cast){.row=p->row[index],.base=p->base[index],.mp=cost,.delay=delay,.support=support_base(p->base[index])};
    p->cast.attack=(p->cast.support?80000:40000)+p->cast.base;
    snprintf(p->cast.label,sizeof p->cast.label,"%s",label);
    p->ret_fire=1;p->lock_until_ns=now_ns+(uint64_t)delay*1000000000ULL/60;
}
int dw4_technique_input(dw4_technique *t,int slot,uint64_t now_ns,const dw4_technique_pad *pad)
{
    if(!t || !pad || slot<0 || slot>3)return 0;
    slot_state *p=t->slot+slot;
    if(!p->open){
        if((pad->pressed&PAD_R1) && pad->can_open){open_panel(t,slot);return 1;}
        return 0;
    }
    refresh(t,slot);
    if(p->age<DEBOUNCE_FRAMES)return 1;
    if(p->locked && now_ns<p->lock_until_ns)return 1;
    p->locked=0;
    /* R1 on page 0 closes (the panel has no Circle or Triangle handling). */
    if(pad->pressed&PAD_R1){p->open=0;p->ret_fire=0;}
    else if(pad->up)move_up(p);
    else if(pad->down)move_down(p);
    else if(pad->pressed&PAD_CROSS)fire(t,slot,now_ns);
    return 1;
}
void dw4_technique_tick(dw4_technique *t,int slot,int on_ctrl)
{
    if(!t || slot<0 || slot>3)return;
    slot_state *p=t->slot+slot;
    if(!p->open)return;
    if(!on_ctrl){p->open=0;p->ret_fire=0;return;}
    if(p->age<DEBOUNCE_FRAMES)p->age++;
    refresh(t,slot);
}
int dw4_technique_poll(dw4_technique *t,int slot,int airborne,dw4_technique_cast *out)
{
    if(!t || !out || slot<0 || slot>3)return 0;
    slot_state *p=t->slot+slot;
    if(!p->open || !p->ret_fire || airborne)return 0;
    p->ret_fire=0;*out=p->cast;return 1;
}
void dw4_technique_launch(dw4_technique *t,int slot,const dw4_technique_cast *cast,const float world[16])
{
    if(!t || !cast || slot<0 || slot>3)return;
    /* Raise: the `reanimation` section of SQ_WAZA carries its own HITBOX (kind 80050, frame 0, 1x1x1 at the origin), which dw4_combat_tick delivers
     * to the player bodies; a stand-in bullet on top would deliver the self hit twice (two skill-growth draws). The other support families have no
     * HITBOX in their section, so their volume is this stand-in (an assumption, docs/combat.md "Support technique wiring"). */
    if(cast->support && cast->base==50)return;
    slot_state *p=t->slot+slot;flight *b=p->bullet+p->next_bullet++%FLIGHTS;
    *b=(flight){.live=1,.attack=cast->attack,.support=cast->support};memcpy(b->world,world,sizeof b->world);
}
int dw4_technique_step(dw4_technique *t,int slot,dw4_technique_deliver deliver,void *user)
{
    if(!t || !deliver || slot<0 || slot>3)return -1;
    int total=0;
    for(unsigned i=0;i<FLIGHTS;i++) {
        flight *b=t->slot[slot].bullet+i;
        if(!b->live)continue;
        const float offset[3]={0,BULLET_HEIGHT,b->support?0:BULLET_SPEED*(float)b->age},size[3]={BULLET_SIZE,BULLET_SIZE,BULLET_SIZE};
        int hits=deliver(user,slot,b->attack,b->world,offset,size);
        if(hits<0)return -1;
        total+=hits;
        if(hits>0 || b->support || ++b->age>=BULLET_LIFE)b->live=0;
    }
    return total;
}
int dw4_technique_flying(const dw4_technique *t,int slot)
{
    int n=0;
    for(unsigned i=0;t && slot>=0 && slot<4 && i<FLIGHTS;i++)n+=t->slot[slot].bullet[i].live;
    return n;
}
