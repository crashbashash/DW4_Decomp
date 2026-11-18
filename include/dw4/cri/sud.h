/* CRI SUD: the Sofdec picture user data (the text block SFX reads its frame type and tags from). */
#ifndef DW4_CRI_SUD_H
#define DW4_CRI_SUD_H

void SUD_Init(void);
void SUD_Finish(void);
unsigned int SUD_AnalyVersion(char *header, int size);
int SUD_AnalyTypeDivField(char *header, int size);
int SUD_AnalyTypeCcs(char *header, int size);
int SUD_AnalyTypeIntl(char *header, int size);
int SUD_AnalyExtScan(char *header, int size);
int SUD_AnalyExtFlag(char *header, int size);
int SUD_AnalyExtVal0(char *header, int size);
int SUD_AnalyExtVal1(char *header, int size);
int SUD_AnalyExtVal2(char *header, int size);
int SUD_AnalyExtVal3(char *header, int size);
void SUD_SearchSudDat(char *text, int length, char **found, int *value);

#endif
