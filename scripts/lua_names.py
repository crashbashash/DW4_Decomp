#!/usr/bin/env python3
"""lua_names.py — name the decompiler's locals from how the bytecode uses them.

The game's chunks are stripped of local names (`nlocvars == 0`), so
scripts/lua_decompile.py renders slots as `local_N` / `arg_N`. Its first pass
records, per binding (a slot's for-loop variable, parameter, or a local with a
given initial value), every use: the value it was declared with, the values
assigned to it, the `be:` arguments it is passed as, the comparisons it is tested
in. `infer` turns that evidence into a name only where one rule below applies;
everything else keeps its synthetic name. Rules, first match wins:

  local function  the closure's body: `TEXTCTL`/`TEXTSET` -> showText, `PLAYER`
                  `GENERATE` -> generatePlayer, otherwise its one native command
                  (`be:MDLaddHp` -> addHp, `be:CFLsetName` -> setFileNames)
  value           every value it holds comes from one kind of native getter:
                  `be:MDLgetRamNo()` -> ramNo, `be:BLTisCritical()` -> isCritical,
                  `be:SYSctlPlayer("HP", "GETMHP", ...)` -> maxHp; getters that
                  differ but share a last word name it by that word
                  (`BLTgetPoisonTime` / `BLTgetStunTime` -> time)
  counter         starts at a number and is only ever `x = x + ...`: count when
                  every step is 1, offset when every step is one other number,
                  total otherwise
  argument        passed straight to a native call whose parameter has a name in
                  the engine source (src/game/be.cpp): `be:FLGset(x, 1)` ->
                  flagNo, `be:SYSisJoinPlayer(x)` -> playerIndex; or as the text
                  of a `TEXTSET` command -> text
  global          its only use is being stored into one `g_` global:
                  `g_GateStage = x` -> gateStage
  skip            holds only nil/0/1 and is only tested as `x ~= 1`
  list            a table constructor that is only indexed
  loop            a numeric-for variable with none of the above: i, j, k by
                  nesting depth
A few romanised words in getter names are translated (Ninzu -> Count, Kyori ->
Distance, Kouka -> Effect, Zokusei -> Attribute, Shinka -> Evolution).

Names never shadow a global, a native name or a Lua keyword (any string
constant of the function or of a function nested in it). Two bindings in
different slots that want the same name get `2`, `3`, ... suffixes in slot
order, except numeric-for variables at the same nesting depth (their loops
cannot overlap). Bindings of one slot never coexist, so they may share a name.
A slot the decompiler's stack model loses track of keeps its synthetic name
throughout.
"""
import json
import os
import re
from collections import Counter, defaultdict

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BE_SOURCE = os.path.join(ROOT, "src", "game", "be.cpp")
SCRIPT_API = os.path.join(ROOT, "data", "script_api.json")

LUA_KEYWORDS = {
    "and", "break", "do", "else", "elseif", "end", "for", "function", "if",
    "in", "local", "nil", "not", "or", "repeat", "return", "then", "until",
    "while", "arg", "self",
}
ROMAJI = {"Ninzu": "Count", "Kyori": "Distance", "Kouka": "Effect",
          "Zokusei": "Attribute", "Shinka": "Evolution", "MHp": "MaxHp"}
CTL_TOKENS = {"MHP": "maxHp", "MMP": "maxMp"}
# engine parameter names that say nothing about the value
VAGUE_PARAMS = re.compile(r"(?:args?|param|value|extra|scriptArg|first|second)\d*$")
PLAYER_PARAMS = {"player", "playerIndex"}
LOOP_NAMES = ["i", "j", "k"]
SEND_COMMANDS = {"be:sd", "be:DMsetSD", "be:DMchkSD", "be:DMswtSD"}

_params = None


def native_params():
    """{(Lua method, argument count): [parameter name or None]} from the
    declarations in be.cpp of the methods data/script_api.json lists as bound.
    Overloads of one arity (`sd_29` / `sd_32`) keep a position's name only when
    they agree."""
    global _params
    if _params is None:
        decls = defaultdict(list)
        with open(BE_SOURCE, encoding="utf-8") as fh:
            text = fh.read()
        with open(SCRIPT_API, encoding="utf-8") as fh:
            bound = {row["name"] for row in json.load(fh)}
        section = text.split("/* This file. */", 1)[1].split("/* Other files. */", 1)[0]
        for m in re.finditer(r"^[\w \*]*?\b([A-Za-z]\w*?)(?:_\d+)?\(([^)]*)\);$", section, re.M):
            if m.group(1) not in bound:
                continue
            names = [re.findall(r"\w+", p)[-1] for p in m.group(2).split(",")
                     if p.strip() not in ("", "void")]
            decls[(m.group(1), len(names))].append(names)
        _params = {}
        for key, overloads in decls.items():
            _params[key] = [names[0] if len(set(names)) == 1 else None
                            for names in zip(*overloads)]
    return _params


def lower_camel(word):
    for jp, en in ROMAJI.items():
        word = word.replace(jp, en)
    m = re.match(r"[A-Z]+(?=[A-Z][a-z]|$)|[A-Z]", word)
    if not m:
        return word
    return word[:m.end()].lower() + word[m.end():]


def getter_noun(sig):
    """The value name of a native getter call signature, or None."""
    if sig[0] != "call" or not sig[1] or not sig[1].startswith("be:"):
        return None
    method = sig[1][3:]
    if method == "FLGisOn":
        return "flagOn"
    m = re.match(r"([A-Z]+)(get|is|calc)([A-Z]\w*)?$", method)
    if m:
        prefix, verb, noun = m.groups()
        if not noun:
            return prefix.lower()
        return "is" + lower_camel(noun)[:1].upper() + lower_camel(noun)[1:] if verb == "is" \
            else lower_camel(noun)
    m = re.match(r"[A-Z]+ctl\w+$", method)
    args = sig[2]
    if m and len(args) > 1 and args[1][0] == "str" and args[1][1].startswith("GET"):
        token = args[1][1][3:]
        return CTL_TOKENS.get(token, token.lower()) if token.isalpha() else None
    return None


def last_word(name):
    words = re.findall(r"[A-Z]?[a-z]+|[A-Z]+(?![a-z])", name)
    return words[-1].lower() if words else None


def is_self(sig, key):
    return sig == ("local",) + key[:2]


def value_name(key, ev):
    sources = [u[1] for u in ev if u[0] == "set"]
    if key[0] == "init":
        sources.append(key[2])
    if not sources:
        return None
    resets = {("num", 0), ("num", None)}
    # counter: x = x + step, from a numeric start
    steps = [s for s in sources if s[0] == "binop" and s[1] == "+" and is_self(s[2], key)]
    rest = [s for s in sources if s not in steps]
    if steps and rest and all(s[0] == "num" for s in rest):
        increments = {s[3] for s in steps}
        if increments == {("num", 1)}:
            return "count"
        if len(increments) == 1 and next(iter(increments))[0] == "num":
            return "offset"
        return "total"
    getters = [s for s in sources if s not in resets]
    if not getters:
        return None
    nouns = [getter_noun(s) for s in getters]
    if None in nouns:
        return None
    if len(set(nouns)) == 1:
        return nouns[0]
    words = {last_word(n) for n in nouns}
    if len(words) == 1:
        word = words.pop()
        if word and len(word) >= 3:
            return word
    return None


def argument_name(ev):
    params = native_params()
    found = Counter()
    for u in ev:
        if u[0] != "arg" or not u[1] or not u[1].startswith("be:"):
            continue
        callee, index, consts = u[1], u[2], u[3]
        if callee in SEND_COMMANDS and len(consts) > 3 and consts[3] == "TEXTSET" and index == 4:
            found["text"] += 1
            continue
        names = params.get((callee[3:], len(consts)), [])
        if index < len(names) and names[index] and not VAGUE_PARAMS.match(names[index]):
            name = names[index]
            if callee in SEND_COMMANDS and index == 2 and consts and consts[0] in ("PLAYER", "PLAYER2"):
                name = "playerIndex"  # the instance number of a PLAYER command is the player
            found["playerIndex" if name in PLAYER_PARAMS else name] += 1
    if not found:
        return None
    if "playerIndex" in found:
        return "playerIndex"
    best = max(found.values())
    return min(n for n, c in found.items() if c == best)


def global_name(ev):
    stores = {u[1] for u in ev if u[0] == "stored"}
    other = [u for u in ev if u[0] not in ("ref", "stored", "set")]
    if len(stores) == 1 and not other:
        target = stores.pop()
        if target[0] == "global" and re.match(r"g_[A-Za-z]\w*$", target[1]):
            return lower_camel(target[1][2:])
    return None


def skip_name(key, ev):
    values = [u[1] for u in ev if u[0] == "set"]
    if key[0] == "init":
        values.append(key[2])
    allowed = {("num", None), ("num", 0), ("num", 1)}
    if ("num", 1) not in values or any(v not in allowed for v in values):
        return None
    uses = [u for u in ev if u[0] not in ("ref", "set")]
    if uses and all(u[0] == "cmp" and u[1] == "~=" and u[2] == ("num", 1) for u in uses):
        return "skip"
    return None


def function_name(proto):
    methods = []
    code, kstr = proto["code"], proto["kstr"]
    for ins in code:
        if ins & 0x3F == 16:  # OP_PUSHSELF
            methods.append(kstr[ins >> 6])
    strings = set(kstr)
    if "TEXTCTL" in strings and "TEXTSET" in strings:
        return "showText"
    if "PLAYER" in strings and "GENERATE" in strings:
        return "generatePlayer"
    commands = {m for m in methods if not re.match(r"[A-Z]+(get|is)", m)
                and m not in ("sd", "DMsetSD", "DMchkSD", "DMswtSD")}
    if commands == {"CFLsetName"}:
        return "setFileNames"  # every argument is an `.igb` file name
    if len(commands) == 1:
        m = re.match(r"[A-Z]+([a-z]\w*)$", commands.pop())
        if m:
            return m.group(1)
    return None


def chunk_strings(proto, out=None):
    out = set() if out is None else out
    out.update(s for s in proto["kstr"] if s)
    for p in proto["kproto"]:
        chunk_strings(p, out)
    return out


def base_name(d, key, ev):
    kind = key[0]
    if kind in ("unbound", "ctl", "vararg"):
        return None
    if kind == "init" and key[2][0] == "func" and key[2][1] is not None:
        return function_name(d.kproto[key[2][1]])
    if kind in ("init",):
        name = value_name(key, ev)
        if name:
            return name
    elif kind == "for":
        pass
    else:
        name = value_name(key, ev) if any(u[0] == "set" for u in ev) else None
        if name:
            return name
    name = argument_name(ev) or global_name(ev) or skip_name(key, ev)
    if name:
        return name
    if kind == "init" and key[2] == ("table",):
        if all(u[0] in ("ref", "indexed", "field", "tableset") for u in ev):
            return "list"
    if kind == "for":
        depth = key[2]
        return LOOP_NAMES[depth] if depth < len(LOOP_NAMES) else f"i{depth + 1}"
    return None


def infer(d):
    """{binding key: name} for Decompiler `d` after its analysis pass."""
    lost = {key[1] for key in d.evidence if key[0] in ("unbound", "ctl")}
    reserved = LUA_KEYWORDS | chunk_strings({"kstr": d.kstr, "kproto": d.kproto})
    wanted = {}
    for key, ev in d.evidence.items():
        if key[1] in lost:
            continue
        name = base_name(d, key, ev)
        if name and re.match(r"[A-Za-z_]\w*$", name):
            wanted[key] = name
    names, owners = {}, defaultdict(set)
    for key in sorted(wanted, key=lambda k: (k[1], repr(k))):
        owner = ("for", key[2]) if key[0] == "for" else ("slot", key[1])
        base = name = wanted[key]
        n = 1
        while name in reserved or (owners[name] and owner not in owners[name]):
            n += 1
            name = f"{base}{n}"
        owners[name].add(owner)
        names[key] = name
    return names
