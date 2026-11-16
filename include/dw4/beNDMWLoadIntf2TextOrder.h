#ifndef DW4_BENDMWLOADINTF2TEXTORDER_H
#define DW4_BENDMWLOADINTF2TEXTORDER_H

struct beNDMWLoadIntf2TextOrder;
struct beUnicodeObj;

extern "C" {
void TextOrder_ClearFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex);
void TextOrder_ConfigureFont(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, const char *text, int align, int color);
void TextOrder_ConfigureUnicode(beNDMWLoadIntf2TextOrder *order, const char *line, int player, int fontIndex, beUnicodeObj *unicodeText, int align, int color);
void TextOrder_PublishLineListOnly(beNDMWLoadIntf2TextOrder *order, int messageId);
beNDMWLoadIntf2TextOrder *beNDMWLoadIntf2TextOrder_Create(int allocator);
void beNDMWLoadIntf2TextOrder_PublishIdLines(beNDMWLoadIntf2TextOrder *order, int messageId, int withFollowUp);
}

#endif
