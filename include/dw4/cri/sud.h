/* CRI SUD: the Sofdec picture user data (the text block SFX reads its frame type and tags from). */
#ifndef DW4_CRI_SUD_H
#define DW4_CRI_SUD_H

void SUD_Init(void);
void SUD_Finish(void);
unsigned int SUD_AnalyVersion(char *header, int index);
int SUD_AnalyTypeDivField(char *header, int index);
int SUD_AnalyTypeCcs(char *header, int index);
void SUD_SearchSudDat(char *text, int length, char **found, int *value);

#endif
