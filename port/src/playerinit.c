/* Fresh GAMERAM creation, using the shared production stat/technique owner. */
#include "dw4/playerinit.h"
#include "dw4/playerstats.h"
#include <stdio.h>
#include <string.h>
static int number(const dw4_database *d,int row,const char *key,int32_t *v,int required)
{int rc=dw4_database_number(d,row,key,v);return rc<0 || (required && rc);}
static int put(dw4_property_folder *f,const char *key,int32_t v)
{return dw4_property_set_number(f,key,v);}
int dw4_playerrecords_create(dw4_playerrecords *o,const dw4_databases *db,int32_t slot,
    const char *model,const char *name,char *e,size_t cap)
{
    const dw4_database *sh=dw4_databases_get(db,"shinka"),*weapon=dw4_databases_get(db,"weapon");
    static const char *const starters[]={"p_dorumon","p_agumon","p_vmon","p_girumon"};
    int allowed=0,species=-1;size_t len=name?strlen(name):0;
    for(unsigned i=0;model && i<4;i++)if(!strcmp(model,starters[i]))allowed=1;
    if(!o || slot<0 || slot>3 || !allowed || !len || len>8 || !sh || !weapon)goto invalid;
    for(size_t i=0;i<len;i++)if((unsigned char)name[i]<32 || (unsigned char)name[i]>126)goto invalid;
    for(int i=0;i<16;i++){
        const char *s=dw4_database_string(sh,i,"MODEL_NAME");
        if(s && !strcmp(s,model)){species=i;break;}
    }
    if(species<0)goto invalid;
    dw4_playerrecords *staged=dw4_playerrecords_open();if(!staged)goto invalid;
    dw4_property_folder *f=dw4_playerrecords_get(staged,"GETPLAYER",slot);
    /* Scalar int/byte constructors in 4cedf0 start at zero. */
    static const char *const zero[]={"UNIQUE","XDATA","BIT","EXP","HP","MP","MHP","MMP",
        "TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO",
        "KAMINARITEIKO","YAMITEIKO","NEXTEXP","ATTACKDELAY","MEICHURITSU","CHIMEIRITSU",
        "MAHIRITSU","KAIHIRITSU","BOUGYORITSU","MAHITEIKOU","DOKUTEIKOU","BITRITSU",
        "EXPRITSU","LUCKRITSU","ATTACKZOKUSEI","HPDRAIN","MPDRAIN","CHOHATURITSU",
        "WEAPONRECNO","WEAPONSKILLNO","BANKBIT"};
    for(size_t i=0;i<sizeof zero/sizeof *zero;i++)if(put(f,zero[i],0))goto bad;
    int32_t levels[16],skills[144],zeroes[176]={0},use[16]={0};
    for(int i=0;i<16;i++)levels[i]=1;
    for(int i=0;i<144;i++)skills[i]=1;
    use[species]=1;
    if(dw4_property_set_array(f,"BASE_LEVEL",levels,16) ||
       dw4_property_set_array(f,"BASE_EXP",zeroes,16) ||
       dw4_property_set_array(f,"BASE_SKILL",skills,144) ||
       dw4_property_set_array(f,"BASE_UPCNT",zeroes,176) ||
       dw4_property_set_array(f,"BASE_ISUSE",use,16) ||
       dw4_property_set_array(f,"SKILL",skills,9) ||
       dw4_property_set_array(f,"UPCNT",zeroes,11) ||
       dw4_property_set_array(f,"UPDATA",zeroes,11) ||
       dw4_property_set_array(f,"DOWNDATA",zeroes,7) ||
       put(f,"DIGIMONNO",species) || put(f,"LEVEL",1) ||
       dw4_property_set_string(f,"DIGIMONNAME",model))goto bad;
    /* Remaining 4cedf0 records and 3f7310's twelve initialized disk objects.
     * Disk +20 is _kazu (quantity), represented by the shared revision word. */
    uint8_t flags[1024]={0},card[50]={0};flags[960]=1;
    dw4_item_record disks[12];for(int i=0;i<12;i++)disks[i]=(dw4_item_record){.kind=4,.record=i};
    if(dw4_property_set_bytes(f,"BASE_FLAG",flags,1024) ||
       dw4_property_set_bytes(f,"BASE_FLAGFOLDER",card,12) ||
       dw4_property_set_array(f,"BASE_COUNTER",zeroes,16) ||
       dw4_property_set_bytes(f,"CARDLIST",card,50) ||
       dw4_property_set_items(f,"DISKFOLDER",disks,12) ||
       dw4_property_set_items(f,"BANKDEVICE",NULL,0))goto bad;
    /* US converter 382eb0 filters unsupported ASCII through table 4c8880.
     * The current name grid includes six punctuation keys absent from it. */
    static const char *const supported="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !\"()+,-:'.<>?^_|&";
    uint16_t codes[8]={0};size_t used=0;
    for(size_t i=0;i<len;i++)if(strchr(supported,name[i]))codes[used++]=(unsigned char)name[i];
    dw4_unicode_object unicode={codes,8,1};
    if(dw4_property_set_unicode_objects(f,"PLAYERNAME",&unicode,1))goto bad;
    dw4_item_record items[3]={0};const char *sockets[3];
    static const char *const initial[]={"INI_WEAPON1","INI_WEAPON2","INI_WEAPON3"};
    for(int i=0;i<3;i++){
        int32_t rec;
        if(number(sh,species,initial[i],&rec,1) || rec<0 || !(sockets[i]=dw4_database_string(weapon,rec,"MODEL")) || !*sockets[i])goto bad;
        items[i]=(dw4_item_record){.kind=0,.record=rec,.equipped=1};
    }
    if(dw4_property_set_items(f,"DEVICEFOLDER",items,3) ||
       dw4_property_set_items(f,"POWERSOCKET",items,3) ||
       dw4_property_set_strings(f,"POWERSOCKETNAME",sockets,3))goto bad;
    int32_t weaponrefs[]={0,1,2},emptyrefs[]={-1,-1,-1,-1,-1};
    dw4_item_record empty[5];for(unsigned i=0;i<5;i++)empty[i]=(dw4_item_record){.kind=-1};
    const char *emptykeys[]={"POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
    const char *refkeys[]={"POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};
    const size_t sizes[]={5,1,5,1};
    if(dw4_property_set_array(f,"POWERSOCKETREF",weaponrefs,3))goto bad;
    for(unsigned i=0;i<4;i++)if(dw4_property_set_items(f,emptykeys[i],empty,sizes[i]) ||
        dw4_property_set_array(f,refkeys[i],emptyrefs,sizes[i]))goto bad;
    if(dw4_playerstats_recalculate((void *)db,f) || put(f,"ISUSE",1))goto bad;
    if(dw4_playerrecords_publish(o,staged,slot))goto bad;
    dw4_playerrecords_close(staged);return 0;
bad:
    dw4_playerrecords_close(staged);
invalid:
    snprintf(e,cap,"character initialization: invalid starter/name/slot or unavailable database dependency");return -1;
}
