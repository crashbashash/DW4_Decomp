/* Ask the main beMessenger object (the GAMERAM property root) for a record: send the command named
 * by entry `playerNo` of the command table to group "GAMERAM", then fetch the object that answers.
 * The table at 0x004c8720 holds the strings GETCOMMON, GETPLAYER1, GETPLAYER2, GETPLAYER3,
 * GETPLAYER4, so 0 selects the shared record and 1..4 select a player. (The fetched object is not
 * returned; callers read it back through the messenger.) */
extern "C" {
extern char GAMERAM[];
int beMessenger_SendNamed(int, char *, int, int, char *);
int beMessenger_GetObject(int, int);
extern char *g_getRecordCommands[5];
extern int g_beMessenger[4];
void bePlayer_GetStruct(int playerNo);
}

void bePlayer_GetStruct(int playerNo) {
    beMessenger_SendNamed(g_beMessenger[0], GAMERAM, 0, 0, g_getRecordCommands[playerNo]);
    beMessenger_GetObject(g_beMessenger[0], 0);
}
