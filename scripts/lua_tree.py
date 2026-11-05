#!/usr/bin/env python3
"""lua_tree.py — find a script in `lua/`, the decompiled Lua corpus, by pack entry and chunk.

`lua/<NN-region>/<NN-stage>_e<ENTRY>/<CCC>-<name>.lua` holds chunk CCC of NDMW.AFS entry ENTRY
(chunks are numbered in the order the pack concatenates them); scripts/build_lua_tree.py writes
the tree from the decompiler's output and docs/engine/lua-tree-layout.md indexes it. The entry
and chunk numbers are what the tools, tables and findings cite, so this module is the one place
that turns them into paths.
"""
import os
import re

ROOT = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "lua")
_STAGE = re.compile(r"_e(\d+)$")
_CHUNK = re.compile(r"^(\d+)-.*\.lua$")


def stage_dirs(root=ROOT):
    """{entry: stage folder} for every pack entry in the tree."""
    out = {}
    for region in sorted(os.listdir(root)):
        folder = os.path.join(root, region)
        if not os.path.isdir(folder):
            continue
        for stage in sorted(os.listdir(folder)):
            found = _STAGE.search(stage)
            if found:
                out[int(found.group(1))] = os.path.join(folder, stage)
    return out


def chunks(entry, root=ROOT):
    """[(chunk index, path)] of one pack entry, in chunk order; empty when the entry is absent."""
    folder = stage_dirs(root).get(entry)
    if not folder:
        return []
    out = []
    for name in os.listdir(folder):
        found = _CHUNK.match(name)
        if found:
            out.append((int(found.group(1)), os.path.join(folder, name)))
    return sorted(out)


def chunk_path(entry, chunk, root=ROOT):
    """The file holding chunk `chunk` of entry `entry`; KeyError when there is none."""
    for index, path in chunks(entry, root):
        if index == chunk:
            return path
    raise KeyError("no Lua chunk %d in entry %d under %s" % (chunk, entry, root))
