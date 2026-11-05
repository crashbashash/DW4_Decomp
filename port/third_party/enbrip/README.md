# Enbaya decoder

Source: https://github.com/korenkonder/enbrip
Revision: `461b7818ec4b1b20ed68b4a7935250f3b4b4ce18` (MIT, see LICENSE).

Only the library sources are included. Local portability changes in help.h: use explicit Windows preprocessor checks,
remove stray semicolons from `#undef`, and make the identity constant const. The port uses the
in-memory decoder for the original character-select `waitC` streams.
