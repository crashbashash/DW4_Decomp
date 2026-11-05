/* 0x00371c10
 * Ask the main beMessenger object (the GAMERAM property root, finding #415) for
 * a record: send the command named by entry `playerNo` of the command table
 * to group "GAMERAM", then fetch the object that answers.  The table at
 * 0x004c8720 holds the strings GETCOMMON, GETPLAYER1, GETPLAYER2, GETPLAYER3,
 * GETPLAYER4, so 0 selects the shared record and 1..4 select a player.
 * (The fetched object is not returned; callers read it back through the messenger.) */
extern "C" {
extern char s_GAMERAM_0050d940[];
int beMessenger_SendNamed(int, char *, int, int, char *);
int beMessenger_GetObject(int, int);
extern char *g_getRecordCommands_004c8720[5];
extern int g_beMessenger_0058a1c0[4];
void bePlayer_GetStruct(int playerNo);
}

void bePlayer_GetStruct(int playerNo) {
    beMessenger_SendNamed(g_beMessenger_0058a1c0[0], s_GAMERAM_0050d940, 0, 0, g_getRecordCommands_004c8720[playerNo]);
    beMessenger_GetObject(g_beMessenger_0058a1c0[0], 0);
}
