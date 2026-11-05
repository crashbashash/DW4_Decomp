#include <string.h>
#include <stdio.h>
#include "dw4/buffapply.h"
#include "dw4/statusapply.h"
/* Retail 0x445d10 (message handler), cases 7 / 8 / 9 of its jump table at 0x51d510:
 *   SETSPEEDUP  : _isFirstList[5]=1, _timerList[5]=int0, _upDataList[0..3]=int1..int4
 *   SETPOWERUP  : _isFirstList[6]=1, _timerList[6]=int0, _upDataList[4..6]=int1..int3
 *   SETREFRACT  : _isFirstList[4]=1, _timerList[4]=int0, _upDataList[7..10]=int1..int4
 * every store is skipped when the list holds too few entries. */
static const struct {int slot,first_up,count;} layout[7]={
    [DW4_MAGIC_SPEEDUP]={DW4_BUFF_SPEED,DW4_UP_SUBAYASA,4},
    [DW4_MAGIC_POWERUP]={DW4_BUFF_POWER,DW4_UP_TSUYOSA,3},
    [DW4_MAGIC_REFRACT]={DW4_BUFF_RESIST,DW4_UP_RES_FIRE,4},
};
void dw4_buffs_init(dw4_buffs *b,int is_player)
{
    memset(b,0,sizeof *b);
    b->is_player=is_player!=0;b->up_count=is_player?DW4_UP_COUNT:7;
}
int64_t dw4_buff_duration_ns(int32_t time){return (int64_t)1000000000*time/60;}
int dw4_buff_apply(dw4_buffs *b,const dw4_magic *m)
{
    if(!b || !m || (m->kind!=DW4_MAGIC_SPEEDUP && m->kind!=DW4_MAGIC_POWERUP && m->kind!=DW4_MAGIC_REFRACT))return -1;
    int slot=layout[m->kind].slot,first=layout[m->kind].first_up;
    b->first[slot]=1;
    b->time[slot]=m->v[0];
    for(int i=0;i<layout[m->kind].count;i++)if(first+i<b->up_count)b->up[first+i]=m->v[1+i];
    return b->is_player;
}
/* One buff block of retail vfunc_46 (0x4448ac speed, 0x444af0 power, 0x444c70 resist). */
static int step(dw4_buffs *b,int slot,int first_up,int count,int on_ctrl,int64_t now)
{
    if(!on_ctrl || !b->time[slot])return 0;
    if(b->first[slot]){
        b->armed[slot]=1;b->start_ns[slot]=now;b->duration_ns[slot]=dw4_buff_duration_ns(b->time[slot]);
        b->first[slot]=0;
    }
    /* FUN_003a7e90: a missing timer reads complete; otherwise duration < elapsed (strict), elapsed in 2^18 ns steps. */
    if(!dw4_status_timer_complete(b->armed[slot],b->start_ns[slot],b->duration_ns[slot],now))return 0;
    b->armed[slot]=0;b->time[slot]=0;
    for(int i=0;i<count;i++)if(first_up+i<b->up_count)b->up[first_up+i]=0;
    return b->is_player;
}
int dw4_buff_update(dw4_buffs *b,int on_ctrl,int64_t now_ns)
{
    int r=0;
    r|=step(b,DW4_BUFF_SPEED,DW4_UP_SUBAYASA,4,on_ctrl,now_ns);
    r|=step(b,DW4_BUFF_POWER,DW4_UP_TSUYOSA,3,on_ctrl,now_ns);
    r|=step(b,DW4_BUFF_RESIST,DW4_UP_RES_FIRE,4,on_ctrl,now_ns);
    return r;
}
int dw4_buff_message(const dw4_magic *m,char name[DW4_BUFF_NAME_CAP],char args[DW4_BUFF_ARGS_CAP])
{
    static const char *const names[7]={[DW4_MAGIC_SPEEDUP]="SETSPEEDUP",[DW4_MAGIC_POWERUP]="SETPOWERUP",[DW4_MAGIC_REFRACT]="SETREFRACT"};
    if(!m || !name || !args || (m->kind!=DW4_MAGIC_SPEEDUP && m->kind!=DW4_MAGIC_POWERUP && m->kind!=DW4_MAGIC_REFRACT) || m->nv<1 || m->nv>5)return -1;
    snprintf(name,DW4_BUFF_NAME_CAP,"%s",names[m->kind]);
    size_t used=0;args[0]=0;
    for(int i=0;i<m->nv;i++){
        int w=snprintf(args+used,DW4_BUFF_ARGS_CAP-used,"%sI<%d>",i?"/":"",(int)m->v[i]);
        if(w<0 || (size_t)w>=DW4_BUFF_ARGS_CAP-used)return -1;
        used+=(size_t)w;
    }
    return 0;
}
int dw4_buffs_load_player(dw4_buffs *b,const dw4_property_folder *f)
{
    size_t n=0;const int32_t *u=dw4_property_array(f,"UPDATA",&n);
    if(!b || !u || n!=DW4_UP_COUNT)return -1;
    memcpy(b->up,u,sizeof b->up);b->up_count=DW4_UP_COUNT;b->is_player=1;return 0;
}
int dw4_buffs_store_player(const dw4_buffs *b,dw4_property_folder *f){return b && b->up_count==DW4_UP_COUNT?dw4_property_set_array(f,"UPDATA",b->up,DW4_UP_COUNT):-1;}
