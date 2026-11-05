/* Retail's wall-info selection by check flag (FUN_00388640): which beHitLandModelInfo kinds a player (7), an enemy (11), a hub NPC (3) or a bullet (2051)
 * collides with. The flags are the beHitLandDelivInfoRam values of the packs and of retail savestates (4 player records with flag 7 in every state). */
#include "dw4/lobbycollision.h"
#include <assert.h>
#include <stdio.h>
int main(void)
{
    static const unsigned kinds[]={1,2,4,8,0x401,0x402,0x802,0x1403,0x1405};
    /* bit k of the row = kinds[k] applies */
    static const struct {unsigned flags;unsigned want;const char *who;} rows[]={
        {7,   (1u<<1)|(1u<<2)|(1u<<5)|(1u<<6)|(1u<<7)|(1u<<8),"player: walls 2, 4, dynamic 0x402, air walls 0x802, ride-on 0x1403/0x1405"},
        {11,  (1u<<1)|(1u<<3)|(1u<<5)|(1u<<6)|(1u<<7),         "enemy: walls 2, 8, dynamic 0x402, air walls 0x802, ride-on 0x1403"},
        {3,   (1u<<1)|(1u<<5)|(1u<<6)|(1u<<7),                 "flag 3 (bosses, NPCs): walls 2, 0x402, 0x802, 0x1403"},
        {2051,(1u<<1)|(1u<<5)|(1u<<7),                         "bullet: walls 2, 0x402, 0x1403 (the 0x800 order skips the 0x802 air walls)"},
    };
    for(unsigned r=0;r<sizeof rows/sizeof *rows;r++) {
        unsigned got=0;for(unsigned k=0;k<sizeof kinds/sizeof *kinds;k++)if(dw4_hitland_info_applies(kinds[k],rows[r].flags))got|=1u<<k;
        if(got!=rows[r].want){fprintf(stderr,"flags %u (%s): got %#x, want %#x\n",rows[r].flags,rows[r].who,got,rows[r].want);return 1;}
    }
    assert(!dw4_hitland_info_applies(2,0) && !dw4_hitland_info_applies(1,3));   /* the floor bit is not a wall query; a zero flag selects nothing */
    assert(dw4_hitland_info_applies(0x1403,0x1003) && !dw4_hitland_info_applies(2,0x1003));   /* an order with 0x1000 (ride-on wall) sees only infos with 0x1000 */
    puts("hitland kinds: the wall-info selection table of players, enemies, NPCs and bullets matches FUN_00388640");
    return 0;
}
