# Behavioral reconstructions

These sources expose recovered behavior for analysis and port work. They are
**not byte-matched translation units** and are excluded from `src/`, the relink,
and matching-progress counts. Each module states its boundary and verification.

- [Game helpers](game/README.md): complete immediate combat helper behavior,
  compared against original instructions with controlled engine services.

- [Engine helpers](engine/README.md): Lua material contact/runtime and complete
  messenger result channels, validated against original instructions with their
  remaining service boundaries recorded.

- [Title menu](frontend/README.md): executable title/menu/options state machine,
  compared with the original MIPS instructions using a stubbed engine boundary.
- [Load controller](frontend/README.md#load-controller): the Game Start load
  controller's per-frame update and RUN/GAMESTART message handler, compared the
  same way.
- [Load interface](frontend/README.md#load-interface): the Game Start
  slot/character/name/difficulty/card interface's master update and family
  message handler, compared the same way.
