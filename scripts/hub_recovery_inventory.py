#!/usr/bin/env python3
"""Inventory hub Lua call sites and their known direct retail dependencies.

This is a recovery queue, not a gameplay-completion or source-equivalence test.
The generated Lua retains string constants but reconstructs control flow only
best-effort. Dynamic calls, native receiver dispatch and original named-chunk
ownership require separate recovery; no call graph is inferred from strings.
"""
import argparse
from collections import defaultdict, deque
import json
from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import lua_tree  # noqa: E402
PACKS = {816: "Commander Room", 820: "Terminal Area",
         824: "Central Areas", 828: "Shop Area"}
# These are the generated decompiler's token spellings, including comments and
# escaped quoted strings. Tokenizing prevents dialogue text from becoming calls.
TOKEN = re.compile(r'--\[\[.*?\]\]|--[^\n]*|"(?:\\.|[^"\\])*"|'
                   r"'(?:\\.|[^'\\])*'|[A-Za-z_][A-Za-z_0-9]*|\d+|\S", re.S)


def calls(text):
    tokens = [(m.group(), text.count("\n", 0, m.start()) + 1)
              for m in TOKEN.finditer(text) if not m.group().startswith("--")]
    for i in range(len(tokens) - 3):
        if [t[0] for t in tokens[i:i+2]] != ["be", ":"] or tokens[i+3][0] != "(":
            continue
        args, current, depth = [], [], 0
        for token, _ in tokens[i+4:]:
            if token == ")" and depth == 0:
                if current:
                    args.append(current)
                break
            if token == "," and depth == 0:
                args.append(current)
                current = []
                continue
            if token in ("(", "[", "{"):
                depth += 1
            elif token in (")", "]", "}"):
                depth -= 1
            current.append(token)
        else:
            raise ValueError(f"unterminated be call at line {tokens[i][1]}")
        # Keep expressions as tokens, without evaluating Lua or treating an
        # identifier as a literal. This also exposes dynamic receiver arguments.
        yield tokens[i+2][0], [" ".join(a) for a in args], tokens[i][1]


def literal(value):
    if re.fullmatch(r'"(?:\\.|[^"\\])*"|' + r"'(?:\\.|[^'\\])*'", value):
        return value[1:-1]
    return None


def inventory():
    dependencies = json.loads((ROOT / "data/lua-dependencies.json").read_text())
    apis = {r["api"]: r for r in dependencies["roots"]}
    functions = {r["address"]: r for r in dependencies["functions"]}
    packs, observed, messages = [], set(), defaultdict(list)
    for entry, area in PACKS.items():
        files = [Path(path) for _index, path in lua_tree.chunks(entry)]
        if not files:
            raise ValueError(f"missing hub script entry {entry}")
        names, modes, used = set(), set(), set()
        call_count = 0
        for path in files:
            for api, args, line in calls(path.read_text()):
                used.add(api)
                observed.add(api)
                call_count += 1
                if api in ("DMsetLua", "DMaddLua") and args and literal(args[0]):
                    names.add(literal(args[0]))
                if api in ("sd", "DMsetSD", "DMchkSD", "DMswtSD"):
                    key = tuple([api] + args)
                    messages[key].append(f"{path.relative_to(ROOT)}:{line}")
                    if len(args) > 4 and literal(args[0]) == "SUBWND" and literal(args[3]) == "GENERATE":
                        # The retail scripts concatenate a dynamic player into
                        # "BANK/I<" .. g_messPlayerNo .. ">". Only the constant
                        # mode prefix is known; do not label the whole argument
                        # as a string literal or invent its player value.
                        prefix = re.match(r'^"([A-Z]+)/', args[4])
                        mode = literal(args[4])
                        if prefix:
                            modes.add(prefix[1])
                        elif mode:
                            modes.add(mode.split("/")[0])
        packs.append({"entry": entry, "area": area, "chunks": len(files),
                      "be_call_sites": call_count, "apis": sorted(used),
                      "queued_named_chunks": sorted(names), "subwindow_modes": sorted(modes)})
    queue = deque([apis[n]["address"] for n in sorted(observed) if n in apis]
                  + dependencies["infrastructure_roots"])
    reached = set()
    while queue:
        address = queue.popleft()
        if address in reached:
            continue
        row = functions[address]
        reached.add(address)
        queue.extend(e["function"] for e in row["direct"] if e["function"] is not None)
    rows = [functions[a] for a in sorted(reached)]
    return {"scope": "Four main hub Lua packs; known direct native dependency lower bound",
            "packs": packs, "unbound_be_names": sorted(observed - apis.keys()),
            "infrastructure_roots": dependencies["infrastructure_roots"],
            "api_roots": [apis[n] for n in sorted(observed) if n in apis],
            "messages": [{"api": k[0], "arguments": list(k[1:]), "sites": v}
                         for k, v in sorted(messages.items())],
            "functions": rows}


def render(data):
    rows = data["functions"]
    missing = [r for r in rows if not r["source"]]
    indirect = sum(len(r["indirect"]) for r in rows)
    lines = ["# Hub script and direct dependency inventory", "",
             "Generated by `python3 scripts/hub_recovery_inventory.py --write`; do not edit by hand.", "",
             "This inventories the four main hub script packs. It is a static lower bound,",
             "not a completion percentage. Source presence requires the separate matching",
             "checks. Lua text reconstruction is best-effort; original bytecode remains",
             "the behavior authority. Reviewed engine roots outside the direct call graph",
             "are not automatically attributed to the hub.", "",
             "| Pack | Area | Chunks | be call sites | Subwindow modes |",
             "| --- | --- | ---: | ---: | --- |"]
    for p in data["packs"]:
        lines.append(f"| {p['entry']} | {p['area']} | {p['chunks']} | {p['be_call_sites']} | "
                     + ", ".join(p["subwindow_modes"]) + " |")
    lines += ["", f"**{len(data['api_roots'])} bound APIs**, plus registration/dispatch, reach",
              f"**{len(rows)} functions / {sum(r['size'] for r in rows):,} bytes** through known direct edges.",
              f"**{len(missing)} functions / {sum(r['size'] for r in missing):,} bytes** lack source definitions.",
              f"The reached bodies contain **{indirect} unresolved register-transfer sites**.", "",
              "SD receiver methods, callbacks, model/AI programs, named-chunk ownership,",
              "progression branches and platform replacements still need explicit review.",
              "A register transfer can also be a switch; its presence is not a missing-function count.",
              "Shared SDK/middleware dependencies are included and must be classified.", "",
              "Exact script call-site references, message arguments, API roots and native edges:",
              "[machine-readable inventory](../../data/hub-recovery.json).", "",
              "[Completion contract and work queue](hub-recovery.md).", "",
              "## Direct dependencies without source", "",
              "| Address | Symbol | Bytes | Indirect sites |",
              "| --- | --- | ---: | ---: |"]
    for r in missing:
        lines.append(f"| `0x{r['address']:08x}` | `{r['name']}` | {r['size']} | {len(r['indirect'])} |")
    return "\n".join(lines) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    data = inventory()
    outputs = {ROOT / "data/hub-recovery.json": json.dumps(data, indent=2) + "\n",
               ROOT / "docs/systems/hub-inventory.md": render(data)}
    for path, content in outputs.items():
        if args.write:
            path.write_text(content)
        if args.check and (not path.exists() or path.read_text() != content):
            raise SystemExit(f"stale generated output: {path.relative_to(ROOT)}")
    print(render(data).split("## Direct dependencies")[0])


if __name__ == "__main__":
    main()
