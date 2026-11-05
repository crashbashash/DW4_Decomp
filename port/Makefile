# The port's asset layer.  See README.md.
CC      ?= cc
CFLAGS  ?= -O2 -std=c99 -Wall -Wextra -Iinclude
# The decomp's authoritative class layouts (include/dw4/reflected.h at the repository root).
CFLAGS  += -I../include
BUILD   := build

# The verifies below default `--roms` to `../../local/extracted`; forward DW4_ROMS when the caller has one,
# so `DW4_ROMS=<dir> make check` works on a tree that keeps the archives elsewhere.
ROMS    := $(if $(DW4_ROMS),--roms $(DW4_ROMS),)

# The optional backends each compile to clean no-ops when absent, so the default build needs
# nothing extra and the headless check just skips the window/present tests.  A backend is enabled
# only when BOTH its libraries and its headers are actually usable: the headers are probed with the
# compiler, not just pkg-config, because a runtime-only install (the shared library present but the
# -dev package absent) reports its `--libs` fine while the header is missing -- which would turn the
# backend on and then fail the build on `#include <...>`.
#
# The probe asks for the header by the exact name the source `#include`s it (SDL as `SDL.h` with
# pkg-config's `-I.../SDL2`, not `SDL2/SDL.h`), so it resolves the same way the real compile does.
probe_hdr = $(shell $(CC) $(2) -E -xc /dev/null -include $(1) >/dev/null 2>&1 && echo 1)

# SDL2: the window/present backend (src/window.c).
SDL2_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null)
SDL2_LIBS   := $(shell pkg-config --libs sdl2 2>/dev/null)
SDL2_ON     := $(if $(SDL2_LIBS),$(call probe_hdr,SDL.h,$(SDL2_CFLAGS)),)
ifeq ($(SDL2_ON),1)
CFLAGS += -DDW4_ENABLE_SDL2 $(SDL2_CFLAGS)
endif

# GPU backend: normal entry points require hardware; explicit reference tools
# may use whatever EGL provides, including a software implementation.
GL_CFLAGS := $(shell pkg-config --cflags egl glesv2 2>/dev/null)
GL_LIBS   := $(shell pkg-config --libs egl glesv2 2>/dev/null)
GL_ON     := $(if $(GL_LIBS),$(and $(call probe_hdr,EGL/egl.h,$(GL_CFLAGS)),$(call probe_hdr,GLES3/gl3.h,$(GL_CFLAGS))),)
ifeq ($(GL_ON),1)
CFLAGS += -DDW4_ENABLE_GL $(GL_CFLAGS)
endif

# Vulkan present backend (src/vk_present.c): needs Vulkan (the swapchain) *and* SDL2 (the window and
# the VkSurfaceKHR), so it is enabled only when both are usable.
VK_CFLAGS := $(shell pkg-config --cflags vulkan 2>/dev/null)
VK_LIBS   := $(shell pkg-config --libs vulkan 2>/dev/null)
VK_ON     := $(if $(and $(VK_LIBS),$(SDL2_ON)),$(call probe_hdr,vulkan/vulkan.h,$(VK_CFLAGS)),)
ifeq ($(VK_ON),1)
CFLAGS += -DDW4_ENABLE_VULKAN $(VK_CFLAGS)
endif

# Rebuild every object when the enabled set changes, so installing or removing a -dev package takes
# effect on the next `make` instead of silently reusing objects built with a different -D set.
BACKENDS := $(BUILD)/backends
$(shell mkdir -p $(BUILD); printf 'SDL2=%s GL=%s VK=%s\n' '$(SDL2_ON)' '$(GL_ON)' '$(VK_ON)' > $(BACKENDS).new; \
        if ! cmp -s $(BACKENDS).new $(BACKENDS); then mv $(BACKENDS).new $(BACKENDS); else rm -f $(BACKENDS).new; fi)

LDLIBS  ?= -lm -lpthread $(SDL2_LIBS) $(GL_LIBS) $(VK_LIBS)
ifeq ($(OS),Windows_NT)
LDLIBS += -lshell32 -lole32 -luuid
endif
CFLAGS += -DDW4_ENABLE_THREADS -pthread -Irecovered/frontend
LUA_SRC := $(wildcard third_party/lua401/src/*.c) $(wildcard third_party/lua401/src/lib/*.c)
LUA_OBJ := $(LUA_SRC:third_party/lua401/%.c=$(BUILD)/lua401/%.o)
# the arena, its class registry and the generated schema: what the typed property folders stand on
ARENA_SRC := src/arena.c src/object.c src/reflection_data.c
SRC := src/fieldhud.c src/database.c src/playerrecords.c src/playerinit.c src/playerhealth.c src/hudmeter.c src/hudnumber.c src/playerstats.c src/playertransactions.c src/inventorydetail.c src/statusctrl.c src/statussubmenu.c src/statusequip.c src/statusequiprecords.c src/statusscene.c src/statusview.c src/statuscontent.c src/statusskill.c src/statuspage.c src/statusdevice.c src/statusdeviceview.c src/statusui.c src/statusgear.c src/statusdetail.c src/statusdetailctrl.c src/statusflag.c src/statusbit.c src/statusbitctrl.c src/statusdisk.c src/statusdiskctrl.c src/statusfolder.c src/statusequipmentmenu.c src/statusmenu.c src/xdatashop.c src/shoproot.c src/saveimage.c src/bankshop.c src/cnosshop.c src/diskshop.c src/cardshop.c src/shopstock.c src/equipshop.c src/laboshop.c src/statusstats.c src/menuwindow.c src/subwindow.c src/fontlayout.c src/textcodec.c src/dialogue.c src/selectctrl.c src/controllers.c src/modelview.c src/modelfade.c src/modelsubcom.c src/modelctrl.c src/stageobjects.c src/filelist.c src/modelai.c src/random.c src/cameratime.c src/boxcamera.c src/titleservices.c src/scriptservices.c src/simulation.c src/script.c src/scriptengine.c src/loadjob.c src/npcmotion.c src/lobbycollision.c src/audio.c src/frontaudio.c src/lobbyui.c src/lobby.c src/clockhost.c src/action2host.c src/logoseq.c src/commdlhost.c src/titlehost.c src/actoranim.c src/options.c src/frontopt.c src/fetext.c src/fronttext.c src/frontchr.c src/afs.c src/host.c src/igb.c src/igfile.c src/mesh.c src/models.c src/render.c src/scene.c src/manifest.c src/mount.c src/arena.c src/arenadb.c src/arenapack.c src/object.c src/png.c src/reflection_data.c src/sfp.c src/skin.c src/pose.c src/texpack.c src/texture.c src/livetex.c src/wav.c src/gl_layer.c src/window.c src/gl_render.c src/engine.c src/frontend.c src/fefont.c src/input.c src/stageinput.c src/padrepeat.c src/movie.c src/vk_present.c src/uireplay.c src/frontlayer.c src/frontui.c
SRC += src/fightrecord.c src/sequencefraction.c src/wndepth.c src/wnprojection.c
SRC += src/gpupolicy.c src/stagetravel.c src/playerpoint.c src/materialcontact.c src/hubruntime.c src/modelcontact.c src/hitbox.c src/foldercalls.c src/memcard.c src/savectrl.c src/saveintf.c src/savescene.c
SRC += src/evodemo.c src/loot.c src/fieldgen.c src/fightcalc.c src/fightstatus_p2e.c src/fightstatus_e2p.c src/fightmagic.c src/magicapply.c src/statusapply.c src/buffapply.c src/combat.c
SRC += src/pads.c src/technique.c src/stagesound.c src/voicepool.c src/ramp.c src/streamplayer.c
OBJ := $(SRC:src/%.c=$(BUILD)/%.o) $(LUA_OBJ) $(BUILD)/enbaya.o $(BUILD)/enbaya_help.o $(BUILD)/title-menu.o $(BUILD)/commdl.o $(BUILD)/completion.o $(BUILD)/modelwait.o $(BUILD)/action2time.o $(BUILD)/eefloat.o $(BUILD)/systemclock.o $(BUILD)/loadingnode.o
DEP := $(OBJ:.o=.d) $(BUILD)/dw4asset.d $(BUILD)/main.d

all: $(BUILD)/dw4asset $(BUILD)/dw4

$(BUILD)/test_gpu_policy: tools/test_gpu_policy.c src/gpupolicy.c include/dw4/gpupolicy.h | $(BUILD)
	$(CC) $(CFLAGS) tools/test_gpu_policy.c src/gpupolicy.c -o $@ $(LDLIBS)
$(BUILD)/test_gpu_policy_backend: tools/test_gpu_policy_backend.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
# Longest recipes first: make -j starts the prerequisites of `check` in the order they are first named, so the slow ones are named here (measured wall times, a loaded
# 14-job run: hub NPC stages 3-10 min, the route runs ~4-6 min each, hubstages/hubgates/hub_boot/hubtalk/hubcommander/fieldroute 3-6 min) and the quick ones fill the gaps.
check: check-hubnpcs-stagML02 check-hubnpcs-stagML11 check-hubnpcs-stagML12 check-hubnpcs-stagML13
check: check-dungeonroute2-c4 check-dungeonroute2-c3 check-dungeonroute2-c2 check-dungeonroute2-c1 check-dungeonroute-c1 check-dungeonroute-c4 check-dungeonroute-c3 check-dungeonroute-c2
check: check-hubstages check-hubgates check-hub-boot check-hubtalk check-hubcommander check-fieldroute check-hublabo check-hubruntime check-hubcnos
check-gpu-policy: $(BUILD)/test_gpu_policy $(BUILD)/test_gpu_policy_backend
	./$(BUILD)/test_gpu_policy
	./$(BUILD)/test_gpu_policy_backend
check: check-gpu-policy
check: check-hubedges
.PHONY: check-gpu-policy
GPU_PRESENT_WRAP := -Wl,--wrap=vkGetPhysicalDeviceProperties,--wrap=vkCreateDevice
$(BUILD)/test_gpu_present: tools/test_gpu_present.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) $(if $(filter -DDW4_ENABLE_VULKAN,$(CFLAGS)),$(GPU_PRESENT_WRAP))
check-gpu-entries: $(BUILD)/dw4 $(BUILD)/test_gpu_present
	python3 tools/verify_gpu_entries.py $(ROMS) --tool $(BUILD)/dw4 --present-tool $(BUILD)/test_gpu_present
.PHONY: check-gpu-entries

$(BUILD)/test_options: tools/test_options.c src/options.c include/dw4/options.h | $(BUILD)
	$(CC) $(CFLAGS) tools/test_options.c src/options.c -o $@ $(LDLIBS)

check-options: $(BUILD)/test_options
	python3 tools/verify_options.py

check: check-options
.PHONY: check-options

# The decomp's authoritative structs (../include/dw4/reflected.h) must compile with the port's own flags and agree
# with the arena model (technical specification: source-level retarget, four-byte references).
$(BUILD)/test_decomp_headers: tools/test_decomp_headers.c include/dw4/scene.h ../include/dw4/reflected.h | $(BUILD)
	$(CC) $(CFLAGS) tools/test_decomp_headers.c -o $@

check-decomp-headers: $(BUILD)/test_decomp_headers
	$(BUILD)/test_decomp_headers

check: check-decomp-headers
.PHONY: check-decomp-headers

# dw4_object_init_header is retargeted onto the authoritative igObject: it must agree with the previous hand-written
# version on every header pattern and with the retail function's result (vtable 0x52f0f0, header word 1).
$(BUILD)/test_igobject_header: tools/test_igobject_header.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-igobject-header: $(BUILD)/test_igobject_header
	./$(BUILD)/test_igobject_header

check: check-igobject-header
.PHONY: check-igobject-header

$(BUILD)/test_fightrecords: tools/test_fightrecords.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-fightrecords: $(BUILD)/test_fightrecords
	./$(BUILD)/test_fightrecords
check-fightrecords-retail: $(BUILD)/test_fightrecords
	python3 tools/verify_fightrecords_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check: check-fightrecords
check-retail: check-fightrecords-retail
.PHONY: check-fightrecords check-fightrecords-retail

$(BUILD)/test_menu_arena: tools/test_menu_arena.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-menu-arena: $(BUILD)/test_menu_arena
	./$(BUILD)/test_menu_arena
check: check-menu-arena
.PHONY: check-menu-arena

# The game arena contract (docs/arena-object-model.md, P0): handle validity, regions, exhaustion, the class registry and
# igObject reference counting.
$(BUILD)/test_arena: tools/test_arena.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-arena: $(BUILD)/test_arena
	./$(BUILD)/test_arena

check: check-arena
.PHONY: check-arena

# P1: the real DATABASE tables as typed arena instances answer exactly like the retail-checked host database (needs the extracted
# assets).
$(BUILD)/test_arenadb: tools/test_arenadb.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-arenadb: $(BUILD)/test_arenadb
	./$(BUILD)/test_arenadb $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)

check: check-arenadb
.PHONY: check-arenadb

check-options-menu: all
	python3 tools/verify_options_menu.py $(ROMS)

check: check-options-menu
.PHONY: check-options-menu

$(BUILD)/%.o: src/%.c $(BACKENDS) | $(BUILD)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/enbaya.o: third_party/enbrip/enbaya.c third_party/enbrip/enbaya.h third_party/enbrip/help.h
	$(CC) $(CFLAGS) -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter -Wno-sign-compare -Wno-parentheses -Wno-alloc-size-larger-than -c $< -o $@

$(BUILD)/enbaya_help.o: third_party/enbrip/help.c third_party/enbrip/help.h
	$(CC) $(CFLAGS) -Wno-unused-variable -c $< -o $@

$(BUILD)/dw4asset: $(OBJ) $(BUILD)/dw4asset.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

# the native host executable (P6.1): the same objects, with the engine host's main instead of the CLI's
$(BUILD)/dw4: $(OBJ) $(BUILD)/main.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/test_scene_transform: tools/test_scene_transform.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_frontchr: tools/test_frontchr.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_lobby_gpu: tools/test_lobby_gpu.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_lobby_render: tools/test_lobby_render.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_input: tools/test_input.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_audio: tools/test_audio.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_audio_mix: tools/test_audio_mix.c src/audio.c include/dw4/audio.h $(BACKENDS)
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

$(BUILD)/test_stagesound: tools/test_stagesound.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-audio: all $(BUILD)/test_audio $(BUILD)/test_audio_mix $(BUILD)/test_stagesound $(BUILD)/survey_stagesound
	./$(BUILD)/test_stagesound $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	python3 tools/verify_stagesound_lua.py $(if $(DW4_ROMS),--roms $(DW4_ROMS),)
	python3 tools/verify_voicepool.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_ramp.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_streamplayer.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_frontaudio_rules.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	./$(BUILD)/test_audio_mix
	python3 tools/verify_audio.py $(ROMS)

.PHONY: check-audio

check: check-audio

$(BUILD)/lobby_ui_frame: tools/lobby_ui_frame.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/lobby_frame: tools/lobby_frame.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_lobbyui: tools/test_lobbyui.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_lobby: tools/test_lobby.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_actoranim: tools/test_actoranim.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_window: tools/test_window.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_gl_layer: tools/test_gl_layer.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
$(BUILD)/test_gl_mesh: tools/test_gl_mesh.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-gl-mesh: $(BUILD)/test_gl_mesh
	./$(BUILD)/test_gl_mesh
check: check-gl-mesh
.PHONY: check-gl-mesh
$(BUILD)/test_fefont_gpu: tools/test_fefont_gpu.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-fefont-gpu: $(BUILD)/test_fefont_gpu
	./$(BUILD)/test_fefont_gpu $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-fefont-gpu
.PHONY: check-fefont-gpu
check-title-mesh-gpu: $(BUILD)/dw4
	python3 tools/verify_title_mesh_gpu.py $(ROMS) --tool $(BUILD)/dw4
.PHONY: check-title-mesh-gpu
$(BUILD)/test_gl_post: tools/test_gl_post.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-gl-post: $(BUILD)/test_gl_post
	./$(BUILD)/test_gl_post
check: check-gl-post
.PHONY: check-gl-post

$(BUILD)/test_title_gpu: tools/test_title_gpu.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_menu_gpu: tools/test_menu_gpu.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_mainmenu: tools/test_mainmenu.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
$(BUILD)/test_mainmenu_cursor: tools/test_mainmenu_cursor.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
$(BUILD)/test_fronttext: tools/test_fronttext.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-fronttext: $(BUILD)/test_fronttext
	./$(BUILD)/test_fronttext $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-fronttext
.PHONY: check-fronttext
check-mainmenu: $(BUILD)/test_mainmenu
	./$(BUILD)/test_mainmenu $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-mainmenu-cursor: $(BUILD)/test_mainmenu_cursor
	./$(BUILD)/test_mainmenu_cursor $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-mainmenu
check: check-mainmenu-cursor
.PHONY: check-mainmenu check-mainmenu-cursor
check-mainmenu-navigation-retail: $(BUILD)/test_mainmenu_cursor
	python3 tools/verify_mainmenu_navigation.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) --roms $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) --tool ./$(BUILD)/test_mainmenu_cursor
check-retail: check-mainmenu-navigation-retail
.PHONY: check-mainmenu-navigation-retail

check: $(BUILD)/test_lobby_gpu $(BUILD)/test_lobbyui $(BUILD)/test_menu_gpu $(BUILD)/test_title_gpu $(BUILD)/test_gl_layer $(BUILD)/test_window $(BUILD)/test_input $(BUILD)/test_lobby_render $(BUILD)/test_lobby $(BUILD)/test_titlehost $(BUILD)/test_actoranim $(BUILD)/test_frontchr $(BUILD)/dw4asset $(BUILD)/dw4 $(BUILD)/test_scene_transform
	./$(BUILD)/test_menu_gpu $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_title_gpu $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_gl_layer
	./$(BUILD)/test_window
	./$(BUILD)/test_input
	./$(BUILD)/test_lobby_gpu $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_lobby_render
	python3 tools/check_title_reference.py
	./$(BUILD)/test_titlehost
	./$(BUILD)/test_actoranim $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_frontchr $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_lobbyui $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_lobby $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	./$(BUILD)/test_scene_transform
	./tools/crosscheck.sh
	python3 tools/verify_platform.py
	python3 tools/extract_iso.py --self-test
	python3 tools/gen_reflection.py --check
	python3 tools/verify_object.py --entry 622 $(ROMS)
	python3 tools/verify_object.py --entry 621 $(ROMS)
	python3 tools/verify_host.py $(ROMS)
	python3 tools/verify_frontend.py $(ROMS)
	python3 tools/verify_present.py
	python3 tools/frame_metric.py --self-test
	DW4_LIVEDUMP=$${DW4_LIVEDUMP} python3 tools/verify_pose.py
	DW4_LIVEDUMP=$${DW4_LIVEDUMP} python3 tools/verify_fog.py

clean:
	rm -rf $(BUILD)

.PHONY: all check clean

# Header changes must rebuild dependents: a struct-layout change without this leaves a
# stale object linked against the new one (which is exactly how a stack smash appears).
-include $(DEP)

$(BUILD)/title-menu.o: recovered/frontend/title-menu.c recovered/frontend/title-menu.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/test_titlehost: tools/test_titlehost.c $(BUILD)/random.o $(BUILD)/clockhost.o $(BUILD)/action2host.o $(BUILD)/logoseq.o $(BUILD)/commdlhost.o $(BUILD)/titlehost.o $(BUILD)/title-menu.o $(BUILD)/commdl.o $(BUILD)/completion.o $(BUILD)/modelwait.o $(BUILD)/action2time.o $(BUILD)/eefloat.o $(BUILD)/systemclock.o $(BUILD)/arena.o $(BUILD)/object.o $(BUILD)/reflection_data.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD)/commdl.o: recovered/frontend/commdl.c recovered/frontend/commdl.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/completion.o: recovered/frontend/completion.c recovered/frontend/completion.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Optional oracle: requires sibling decomp/workspace tools, retail ELF and AREA.AFS.
check-retail:
	python3 ../scripts/verify_npcmotion.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 ../scripts/verify_systemclock.py --source recovered/frontend/systemclock.c --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) --mutations
	python3 tools/gen_lobby_arrival.py --check $(if $(DW4_ROMS),--afs $(DW4_ROMS)/NDMW.AFS,)
	python3 tools/gen_logo_program.py --check
	python3 ../scripts/verify_modelwait.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 ../scripts/verify_commdl.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_title_integration.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
.PHONY: check-retail

$(BUILD)/modelwait.o: recovered/frontend/modelwait.c recovered/frontend/modelwait.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/action2time.o: recovered/frontend/action2time.c recovered/frontend/action2time.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/eefloat.o: recovered/frontend/eefloat.c recovered/frontend/eefloat.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/systemclock.o: recovered/frontend/systemclock.c recovered/frontend/systemclock.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/test_bootcards: tools/test_bootcards.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-bootcards: all $(BUILD)/test_bootcards
	./$(BUILD)/test_bootcards $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)

.PHONY: check-bootcards
check: check-bootcards

$(BUILD)/test_lobbycollision: tools/test_lobbycollision.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-lobbycollision: $(BUILD)/test_lobbycollision
	python3 tools/gen_lobby_arrival.py --check $(if $(DW4_ROMS),--afs $(DW4_ROMS)/NDMW.AFS,)
	./$(BUILD)/test_lobbycollision
check: check-lobbycollision
.PHONY: check-lobbycollision

$(BUILD)/test_dminfotext: tools/test_dminfotext.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)
check-dminfotext: $(BUILD)/test_dminfotext
	./$(BUILD)/test_dminfotext $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-dminfotext
.PHONY: check-dminfotext
$(BUILD)/test_practicetext: tools/test_practicetext.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)
check-practicetext: $(BUILD)/test_practicetext
	./$(BUILD)/test_practicetext
check: check-practicetext
.PHONY: check-practicetext
$(BUILD)/test_practicelight: tools/test_practicelight.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)
check-practicelight: $(BUILD)/test_practicelight
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./$(BUILD)/test_practicelight $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-practicelight
.PHONY: check-practicelight
$(BUILD)/test_loadingcards: tools/test_loadingcards.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-loadingcards: $(BUILD)/test_loadingcards
	./$(BUILD)/test_loadingcards $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-loadingcards
.PHONY: check-loadingcards
$(BUILD)/test_hitkinds: tools/test_hitkinds.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-hitkinds: $(BUILD)/test_hitkinds
	./$(BUILD)/test_hitkinds
check: check-hitkinds
.PHONY: check-hitkinds
$(BUILD)/test_arenawalls: tools/test_arenawalls.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)
check-arenawalls: $(BUILD)/test_arenawalls
	./$(BUILD)/test_arenawalls $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-arenawalls
.PHONY: check-arenawalls
$(BUILD)/test_loadingstale: tools/test_loadingstale.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-loadingstale: $(BUILD)/test_loadingstale
	./$(BUILD)/test_loadingstale $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-loadingstale
.PHONY: check-loadingstale
$(BUILD)/test_loading: tools/test_loading.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
$(BUILD)/test_loading_live: tools/test_loading_live.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) -Wl,--wrap=dw4_window_pump,--wrap=dw4_window_pump_mates,--wrap=dw4_simulation_due,--wrap=dw4_frontui_loading_sample,--wrap=dw4_window_present,--wrap=dw4_frontend_boot

check-loading: all $(BUILD)/test_loading $(BUILD)/test_loading_live
	python3 ../scripts/verify_loadingnode.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	./$(BUILD)/test_loading $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a ./$(BUILD)/test_loading_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	python3 tools/verify_loading.py $(ROMS)
check: check-loading
.PHONY: check-loading

$(BUILD)/loadingnode.o: recovered/frontend/loadingnode.c recovered/frontend/loadingnode.h $(BACKENDS)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Vendored Lua 4.0.1; no dependency on the host's modern Lua installation.
CFLAGS += -Ithird_party/lua401/include
$(BUILD)/lua401/%.o: third_party/lua401/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Wno-unused-parameter -MMD -MP -c $< -o $@
-include $(LUA_OBJ:.o=.d) $(BUILD)/script.d
$(BUILD)/test_script: tools/test_script.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-script: $(BUILD)/test_script
	python3 tools/gen_script_api.py --check
	./$(BUILD)/test_script $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-script
.PHONY: check-script

$(BUILD)/test_scriptservices: tools/test_scriptservices.c src/scriptservices.c include/dw4/scriptservices.h
	$(CC) $(CFLAGS) tools/test_scriptservices.c src/scriptservices.c -o $@ -lm

check-scriptservices: $(BUILD)/test_scriptservices
	./$(BUILD)/test_scriptservices
check: check-scriptservices
.PHONY: check-scriptservices

check-script-retail: $(BUILD)/test_script $(BUILD)/test_filelist $(BUILD)/test_stageobjects $(BUILD)/test_actorctrl $(BUILD)/test_controllers
	python3 tools/verify_actorctrl_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) --roms $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	python3 tools/verify_controller_slots_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) --roms $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) --tool $(BUILD)/test_controllers
	python3 tools/verify_stageobjects_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) --roms $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) --tool $(BUILD)/test_stageobjects
	python3 tools/verify_filelist_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) --roms $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) --tool $(BUILD)/test_filelist
	python3 tools/verify_scriptownership_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_modelai_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_random_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_cameratime_retail.py --elf $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)/SLUS_208.36
	python3 tools/verify_script_retail.py $(ROMS) --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_scriptservices_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-script-retail
.PHONY: check-script-retail

$(BUILD)/test_filelist: tools/test_filelist.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-filelist: $(BUILD)/test_filelist
	./$(BUILD)/test_filelist $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)

check: check-filelist
.PHONY: check-filelist

$(BUILD)/test_stageobjects: tools/test_stageobjects.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-stageobjects: $(BUILD)/test_stageobjects
	./$(BUILD)/test_stageobjects $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)

check: check-stageobjects
.PHONY: check-stageobjects

$(BUILD)/test_controllers: tools/test_controllers.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-controllers: $(BUILD)/test_controllers
	./$(BUILD)/test_controllers $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-controllers
.PHONY: check-controllers

$(BUILD)/test_actorctrl: tools/test_actorctrl.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-actorctrl: $(BUILD)/test_actorctrl
	./$(BUILD)/test_actorctrl $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-actorctrl
.PHONY: check-actorctrl

$(BUILD)/test_dialogue: tools/test_dialogue.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-dialogue: $(BUILD)/test_dialogue
	./$(BUILD)/test_dialogue $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-dialogue
check-retail: check-dialogue-retail
check-dialogue-retail:
	python3 tools/verify_subwindow_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_font_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_selectctrl_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
.PHONY: check-dialogue check-dialogue-retail

$(BUILD)/test_statusctrl: tools/test_statusctrl.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-statusctrl: $(BUILD)/test_statusctrl $(BUILD)/test_playerrecords_vm
	./$(BUILD)/test_statusctrl
	./$(BUILD)/test_playerrecords_vm
check: check-statusctrl
check-statusctrl-retail:
	python3 tools/verify_playerrecords_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_statusctrl_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-statusctrl-retail
.PHONY: check-statusctrl check-statusctrl-retail
$(BUILD)/test_playerrecords_vm: tools/test_playerrecords_vm.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

$(BUILD)/test_statusviews: tools/test_statusviews.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-statusviews: $(BUILD)/test_statusviews $(BUILD)/test_textcalls
	./$(BUILD)/test_textcalls
	./$(BUILD)/test_statusviews $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-statusviews
check-statusviews-retail:
	python3 tools/verify_statusviews_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-statusviews-retail
.PHONY: check-statusviews check-statusviews-retail

$(BUILD)/test_textcalls: tools/test_textcalls.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-statusstats-retail:
	python3 tools/verify_statusstats_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-statusstats-retail
.PHONY: check-statusstats-retail

$(BUILD)/test_statusstats: tools/test_statusstats.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-statusstats: $(BUILD)/test_statusstats
	./$(BUILD)/test_statusstats
check: check-statusstats
.PHONY: check-statusstats

$(BUILD)/test_database: tools/test_database.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-database: $(BUILD)/test_database
	./$(BUILD)/test_database $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-database
check-database-retail:
	python3 tools/verify_database_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-database-retail
.PHONY: check-database check-database-retail

$(BUILD)/test_playerinit: tools/test_playerinit.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-playerinit: $(BUILD)/test_playerinit
	./$(BUILD)/test_playerinit $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-playerinit
.PHONY: check-playerinit

check-playerinit-retail: $(BUILD)/test_playerinit
	python3 tools/verify_playerinit_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) $(ROMS)
check-retail: check-playerinit-retail
.PHONY: check-playerinit-retail

$(BUILD)/test_playertransactions: tools/test_playertransactions.c $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(OBJ) $(LDLIBS)
check-playertransactions: $(BUILD)/test_playertransactions
	./$(BUILD)/test_playertransactions
check: check-playertransactions
check-playertransactions-retail:
	python3 tools/verify_playertransactions_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-playertransactions-retail
.PHONY: check-playertransactions check-playertransactions-retail

check-inventorydetail-retail:
	python3 tools/verify_inventorydetail_retail.py
check-retail: check-inventorydetail-retail
.PHONY: check-inventorydetail-retail

$(BUILD)/test_inventorydetail: tools/test_inventorydetail.c src/inventorydetail.c src/playerrecords.c $(ARENA_SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-inventorydetail: $(BUILD)/test_inventorydetail
	./$(BUILD)/test_inventorydetail
check: check-inventorydetail
.PHONY: check-inventorydetail

check-playerstats: $(BUILD)/test_playerinit
	./$(BUILD)/test_playerinit $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) --stats > /dev/null
check-playerstats-retail: $(BUILD)/test_playerinit
	python3 tools/verify_playerstats_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36) $(ROMS)
check: check-playerstats
check-retail: check-playerstats-retail
.PHONY: check-playerstats check-playerstats-retail

$(BUILD)/test_statussubmenu: tools/test_statussubmenu.c src/statussubmenu.c src/statusscene.c src/menuwindow.c src/playerrecords.c $(ARENA_SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-statussubmenu: $(BUILD)/test_statussubmenu
	./$(BUILD)/test_statussubmenu
check-statussubmenu-retail:
	python3 tools/verify_statussubmenu_retail.py
	python3 tools/verify_statuspage_retail.py
	python3 tools/verify_statusscene_retail.py
check: check-statussubmenu
check-retail: check-statussubmenu-retail
.PHONY: check-statussubmenu check-statussubmenu-retail

$(BUILD)/test_statusequip: tools/test_statusequip.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-statusequip: $(BUILD)/test_statusequip
	./$(BUILD)/test_statusequip $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-statusequip-retail:
	python3 tools/verify_statusequip_retail.py
check: check-statusequip
check-retail: check-statusequip-retail
.PHONY: check-statusequip check-statusequip-retail

check-statuscontent-retail:
	python3 tools/verify_statuscontent_retail.py
check-retail: check-statuscontent-retail
.PHONY: check-statuscontent-retail

check-statusdevice-retail:
	python3 tools/verify_statusdevice_retail.py
check-retail: check-statusdevice-retail
.PHONY: check-statusdevice-retail

check-statusbit-retail:
	python3 tools/verify_statusbit_retail.py
check-retail: check-statusbit-retail
.PHONY: check-statusbit-retail

check-modelfreeze-retail: $(BUILD)/test_controllers
	python3 tools/verify_modelfreeze_retail.py
check-retail: check-modelfreeze-retail
.PHONY: check-modelfreeze-retail

check-modelfade-retail:
	python3 tools/verify_modelfade_retail.py
check-retail: check-modelfade-retail
.PHONY: check-modelfade-retail

check-soundfreeze-retail:
	python3 tools/verify_soundfreeze_retail.py
check-retail: check-soundfreeze-retail
.PHONY: check-soundfreeze-retail

check-playerhealth-retail:
	python3 tools/verify_playerhealth_retail.py
check-retail: check-playerhealth-retail
.PHONY: check-playerhealth-retail

check-hudmeter-retail:
	python3 tools/verify_hudmeter_retail.py
check-retail: check-hudmeter-retail
.PHONY: check-hudmeter-retail

check-hudnumber-retail:
	python3 tools/verify_hudnumber_retail.py
check-retail: check-hudnumber-retail
.PHONY: check-hudnumber-retail

check-status-boot: $(BUILD)/dw4
	python3 tools/verify_status_boot.py $(ROMS) --tool $(BUILD)/dw4
	python3 tools/verify_status_boot.py $(ROMS) --tool $(BUILD)/dw4 --dialogue-button circle
.PHONY: check-status-boot

check-padrepeat-retail:
	python3 tools/verify_padrepeat_retail.py
check-retail: check-padrepeat-retail
.PHONY: check-padrepeat-retail

STATUS_LIVE_WRAP := -Wl,--wrap=dw4_window_pump,--wrap=dw4_window_pump_mates,--wrap=dw4_simulation_due,--wrap=dw4_statusscene_freeze,--wrap=dw4_statusscene_restore,--wrap=dw4_frontend_boot,--wrap=dw4_lobby_weapon,--wrap=dw4_lobby_tick,--wrap=dw4_stageinput_service,--wrap=dw4_statusmenu_window_open
STATUS_LIVE_WRAP += -Wl,--wrap=dw4_statusdetail_window_open,--wrap=dw4_statusdisk_window_open,--wrap=dw4_statusflag_window_open,--wrap=dw4_statusbit_window_open
STATUS_LIVE_WRAP += -Wl,--wrap=dw4_frontaudio_action
STATUS_LIVE_WRAP += -Wl,--wrap=dw4_lobby_draw_layers,--wrap=dw4_gl_layer_ui_or_cpu,--wrap=dw4_window_present,--wrap=dw4_audio_open,--wrap=dw4_audio_close
STATUS_LIVE_WRAP += -Wl,--wrap=dw4_controllers_sample
STATUS_LIVE_WRAP += -Wl,--wrap=dw4_playerhealth_restore
STATUS_LIVE_WRAP += -Wl,--wrap=dw4_gl_layer_ui,--wrap=dw4_modelview_draw
$(BUILD)/test_status_live: tools/test_status_live.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) $(if $(filter -DDW4_ENABLE_SDL2,$(CFLAGS)),$(STATUS_LIVE_WRAP))
check-status-live: $(BUILD)/test_status_live
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-status-gpu: $(BUILD)/test_statusviews $(BUILD)/test_status_live
	python3 tools/verify_status_gpu.py $(ROMS) --tool $(BUILD)/test_statusviews
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a DW4_STATUS_LIVE_GPU=640x448 ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a DW4_STATUS_LIVE_GPU=640x448 DW4_STATUS_LIVE_GPU_FAIL=1 ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
.PHONY: check-status-gpu
.PHONY: check-status-live
CALLED_ARRIVAL_WRAP := -Wl,--wrap=dw4_lobby_tick,--wrap=dw4_controllers_sample,--wrap=dw4_lobby_dialogue,--wrap=dw4_dialogue_input
$(BUILD)/test_called_arrival: tools/test_called_arrival.c tools/savetest.h tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS) $(if $(filter -DDW4_ENABLE_SDL2,$(CFLAGS)),$(CALLED_ARRIVAL_WRAP))
check-called-arrival: $(BUILD)/test_called_arrival
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./$(BUILD)/test_called_arrival $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-called-arrival
.PHONY: check-called-arrival

check-lobby-parity: $(BUILD)/test_status_live
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a DW4_LOBBY_PARITY=1 ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-lobby-parity
.PHONY: check-lobby-parity

check-paddirection-retail:
	python3 tools/verify_paddirection_retail.py
check-retail: check-paddirection-retail
.PHONY: check-paddirection-retail

check-generator-freeze-retail:
	python3 tools/verify_generator_freeze_retail.py
check-retail: check-generator-freeze-retail
.PHONY: check-generator-freeze-retail

check-stageinput-retail:
	python3 tools/verify_stageinput_retail.py
check-retail: check-stageinput-retail
.PHONY: check-stageinput-retail

check-statusdisk-retail:
	python3 tools/verify_statusdiskctrl_retail.py
check-retail: check-statusdisk-retail
.PHONY: check-statusdisk-retail

check-statusdetail-retail:
	python3 tools/verify_statusdetailctrl_retail.py
check-retail: check-statusdetail-retail
.PHONY: check-statusdetail-retail

check-statusbit-outer-retail:
	python3 tools/verify_statusbitctrl_retail.py
check-retail: check-statusbit-outer-retail
.PHONY: check-statusbit-outer-retail

check-positioned-model-retail:
	python3 tools/verify_positioned_model_retail.py
check-retail: check-positioned-model-retail
.PHONY: check-positioned-model-retail

check-actionvisibility-retail:
	python3 tools/verify_actionvisibility_retail.py
check-retail: check-actionvisibility-retail
.PHONY: check-actionvisibility-retail

$(BUILD)/textcodec.o: src/textcodec_table.inc
check-textcodec-retail:
	python3 tools/gen_textcodec_table.py --check --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
	python3 tools/verify_textcodec_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-textcodec-retail
.PHONY: check-textcodec-retail

check-sequencefraction-retail:
	python3 tools/verify_sequencefraction_retail.py
check-retail: check-sequencefraction-retail
.PHONY: check-sequencefraction-retail

check-wnprojection-retail:
	python3 tools/verify_wnprojection_retail.py
check-retail: check-wnprojection-retail
.PHONY: check-wnprojection-retail

$(BUILD)/test_lobbywalk: tools/test_lobbywalk.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-lobbywalk: $(BUILD)/test_lobbywalk
	./$(BUILD)/test_lobbywalk $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-lobbywalk
.PHONY: check-lobbywalk

check-mdllive-retail:
	python3 tools/verify_mdllive_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check-retail: check-mdllive-retail
.PHONY: check-mdllive-retail

$(BUILD)/test_loading_startup: tools/test_loading_live.c $(OBJ)
	$(CC) $(CFLAGS) -DDW4_TEST_START_FAILURE $^ -o $@ $(LDLIBS) -Wl,--wrap=dw4_window_pump,--wrap=dw4_window_pump_mates,--wrap=dw4_simulation_due,--wrap=dw4_frontui_loading_sample,--wrap=dw4_window_present,--wrap=dw4_frontend_boot,--wrap=dw4_filelist_first,--wrap=dw4_lobby_tick
check-loading-startup: $(BUILD)/test_loading_startup
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a ./$(BUILD)/test_loading_startup $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-loading-startup
.PHONY: check-loading-startup

$(BUILD)/test_boxcamera: tools/test_boxcamera.c $(OBJ)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@
check-boxcamera: $(BUILD)/test_boxcamera
	./$(BUILD)/test_boxcamera
check-boxcamera-retail:
	python3 tools/verify_boxcamera_retail.py --elf $(if $(DW4_ELF),$(DW4_ELF),../../local/extracted/SLUS_208.36)
check: check-boxcamera
check-retail: check-boxcamera-retail
.PHONY: check-boxcamera check-boxcamera-retail

check-background-focus: $(BUILD)/test_status_live
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a DW4_STATUS_LIVE_FOCUS_ONLY=1 ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-background-focus-gpu: $(BUILD)/test_status_live
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a DW4_STATUS_LIVE_FOCUS_ONLY=1 DW4_STATUS_LIVE_GPU=640x448 ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
.PHONY: check-background-focus check-background-focus-gpu

check-lobby-floor-retail:
	python3 tools/verify_lobby_floor_retail.py
check-retail: check-lobby-floor-retail
.PHONY: check-lobby-floor-retail

$(BUILD)/test_lobby_portaledge: tools/test_lobby_portaledge.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-lobby-portaledge: $(BUILD)/test_lobby_portaledge
	./$(BUILD)/test_lobby_portaledge $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-lobby-portaledge
.PHONY: check-lobby-portaledge

check-lobby-portaledge-live: $(BUILD)/test_status_live
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy SDL_GAMECONTROLLER_IGNORE_DEVICES=0x2dc8/0x310a DW4_LOBBY_PORTAL_EDGE=1 ./$(BUILD)/test_status_live $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-lobby-portaledge-live
.PHONY: check-lobby-portaledge-live

$(BUILD)/test_hubtravel: tools/test_hubtravel.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-hubtravel: $(BUILD)/test_hubtravel
	./$(BUILD)/test_hubtravel $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubtravel
.PHONY: check-hubtravel

$(BUILD)/test_playerpoint: tools/test_playerpoint.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-playerpoint-retail: $(BUILD)/test_playerpoint
	python3 tools/verify_playerpoint_retail.py $(ROMS)
check-retail: check-playerpoint-retail
.PHONY: check-playerpoint-retail

check-materialcontact-retail:
	python3 tools/verify_materialcontact_retail.py $(ROMS) $(if $(DW4_ELF),--elf $(DW4_ELF),)
check-retail: check-materialcontact-retail
.PHONY: check-materialcontact-retail

$(BUILD)/test_hubscene: tools/test_hubscene.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-hubscene: $(BUILD)/test_hubscene
	./$(BUILD)/test_hubscene $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubscene
.PHONY: check-hubscene

$(BUILD)/test_session_snapshot: tools/test_session_snapshot.c src/playerrecords.c $(ARENA_SRC) include/dw4/playerrecords.h
	$(CC) $(CFLAGS) tools/test_session_snapshot.c src/playerrecords.c $(ARENA_SRC) -o $@ $(LDLIBS)
check-session-snapshot: $(BUILD)/test_session_snapshot
	./$(BUILD)/test_session_snapshot
check: check-session-snapshot
.PHONY: check-session-snapshot

$(BUILD)/test_hubruntime: tools/test_hubruntime.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-hubruntime: $(BUILD)/test_hubruntime
	./$(BUILD)/test_hubruntime $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubruntime
.PHONY: check-hubruntime

$(BUILD)/test_hubbank: tools/test_hubbank.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubbank: $(BUILD)/test_hubbank
	./$(BUILD)/test_hubbank $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubbank
.PHONY: check-hubbank

$(BUILD)/test_hublabo: tools/test_hublabo.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hublabo: $(BUILD)/test_hublabo
	./$(BUILD)/test_hublabo $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hublabo
.PHONY: check-hublabo

$(BUILD)/test_hubdisk: tools/test_hubdisk.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubdisk: $(BUILD)/test_hubdisk
	@mkdir -p $(BUILD)/hub-captures
	./$(BUILD)/test_hubdisk $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(BUILD)/hub-captures
check: check-hubdisk
.PHONY: check-hubdisk

$(BUILD)/test_hubshops: tools/test_hubshops.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubshops: $(BUILD)/test_hubshops
	@mkdir -p $(BUILD)/hub-captures
	./$(BUILD)/test_hubshops $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(BUILD)/hub-captures
check: check-hubshops
.PHONY: check-hubshops

$(BUILD)/test_hubcnos: tools/test_hubcnos.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubcnos: $(BUILD)/test_hubcnos
	@mkdir -p $(BUILD)/hub-captures
	./$(BUILD)/test_hubcnos $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(BUILD)/hub-captures
check: check-hubcnos
.PHONY: check-hubcnos

$(BUILD)/test_savectrl: tools/test_savectrl.c $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

$(BUILD)/test_saveintf: tools/test_saveintf.c src/saveintf.c src/saveintf_tables.inc include/dw4/saveintf.h
	$(CC) $(CFLAGS) tools/test_saveintf.c src/saveintf.c -o $@

check-saveintf: $(BUILD)/test_saveintf
	./$(BUILD)/test_saveintf
check: check-saveintf
.PHONY: check-saveintf

$(BUILD)/test_savescene: tools/test_savescene.c tools/savetest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-savescene: $(BUILD)/test_savescene
	./$(BUILD)/test_savescene $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-savescene
.PHONY: check-savescene

$(BUILD)/test_titlecall: tools/test_titlecall.c tools/savetest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-titlecall: $(BUILD)/test_titlecall
	./$(BUILD)/test_titlecall $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-titlecall
.PHONY: check-titlecall

$(BUILD)/test_lobbyrows: tools/test_lobbyrows.c $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-lobbyrows: $(BUILD)/test_lobbyrows
	./$(BUILD)/test_lobbyrows $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-lobbyrows
.PHONY: check-lobbyrows

$(BUILD)/test_hubload: tools/test_hubload.c tools/savetest.h tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubload: $(BUILD)/test_hubload
	./$(BUILD)/test_hubload $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubload
.PHONY: check-hubload

$(BUILD)/test_hubsave: tools/test_hubsave.c tools/savetest.h tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubsave: $(BUILD)/test_hubsave
	./$(BUILD)/test_hubsave $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubsave
.PHONY: check-hubsave

check-savectrl: $(BUILD)/test_savectrl
	./$(BUILD)/test_savectrl
check: check-savectrl
.PHONY: check-savectrl check-dialogue-e2e

# Slow (about ten minutes): real headless engine, ten NPC conversations (Terminal, first Terminal, Central, Shop, Commander Room), rendered frames classified. Not part of `check`.
check-dialogue-e2e: $(BUILD)/dw4
	python3 tools/test_dialogue_e2e.py --roms $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) --tool $(BUILD)/dw4

$(BUILD)/test_saveimage: tools/test_saveimage.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-saveimage: $(BUILD)/test_saveimage
	./$(BUILD)/test_saveimage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-saveimage
.PHONY: check-saveimage

# Headless per-stage CPU cost of the hub (tick + the CPU side of the world draw); not part of `check` because it is timing based.
$(BUILD)/profile_hubstages: tools/profile_hubstages.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

profile-hubstages: $(BUILD)/profile_hubstages
	./$(BUILD)/profile_hubstages $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(PROFILE_BUDGET_MS)
.PHONY: profile-hubstages

$(BUILD)/test_hubstages: tools/test_hubstages.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

$(BUILD)/test_hubedges: tools/test_hubedges.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubedges: $(BUILD)/test_hubedges
	./$(BUILD)/test_hubedges $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
.PHONY: check-hubedges

check-hubstages: $(BUILD)/test_hubstages
	./$(BUILD)/test_hubstages $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubstages
.PHONY: check-hubstages

$(BUILD)/test_hubowner: tools/test_hubowner.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubowner: $(BUILD)/test_hubowner
	./$(BUILD)/test_hubowner $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubowner
.PHONY: check-hubowner

$(BUILD)/test_hubnpcs: tools/test_hubnpcs.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

# One target per hub stage (DW4_NPC_STAGE): the four stages are independent and the whole run was the longest single recipe of the check.
HUBNPC_STAGES=stagML11 stagML12 stagML13 stagML02
define hubnpcs_stage
check-hubnpcs-$(1): $(BUILD)/test_hubnpcs
	DW4_NPC_STAGE=$(1) ./$(BUILD)/test_hubnpcs $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
endef
$(foreach st,$(HUBNPC_STAGES),$(eval $(call hubnpcs_stage,$(st))))
check-hubnpcs: $(addprefix check-hubnpcs-,$(HUBNPC_STAGES))
check: check-hubnpcs
.PHONY: check-hubnpcs $(addprefix check-hubnpcs-,$(HUBNPC_STAGES))

$(BUILD)/test_hubprmame: tools/test_hubprmame.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubprmame: $(BUILD)/test_hubprmame
	./$(BUILD)/test_hubprmame $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubprmame
.PHONY: check-hubprmame

$(BUILD)/test_hubtalk: tools/test_hubtalk.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)

check-hubtalk: $(BUILD)/test_hubtalk
	@mkdir -p $(BUILD)/hub-captures
	./$(BUILD)/test_hubtalk $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(BUILD)/hub-captures
check: check-hubtalk
.PHONY: check-hubtalk

$(BUILD)/test_hubcommander: tools/test_hubcommander.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubcommander: $(BUILD)/test_hubcommander
	@mkdir -p $(BUILD)/hub-captures
	./$(BUILD)/test_hubcommander $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(BUILD)/hub-captures
check: check-hubcommander
.PHONY: check-hubcommander

$(BUILD)/test_hubgates: tools/test_hubgates.c tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubgates: $(BUILD)/test_hubgates
	./$(BUILD)/test_hubgates $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hubgates
.PHONY: check-hubgates

HUB_BOOT_WRAP := -Wl,--wrap=dw4_playerrecords_create,--wrap=dw4_loadjob_poll,--wrap=dw4_window_pump,--wrap=dw4_window_pump_mates,--wrap=dw4_simulation_due,--wrap=dw4_simulation_step,--wrap=dw4_lobby_tick,--wrap=dw4_frontui_loading_sample,--wrap=dw4_window_present,--wrap=dw4_hubruntime_prepare,--wrap=dw4_statusscene_freeze,--wrap=dw4_statusscene_restore,--wrap=dw4_frontend_boot
$(BUILD)/test_hub_boot: tools/test_hub_boot.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS) $(if $(filter -DDW4_ENABLE_SDL2,$(CFLAGS)),$(HUB_BOOT_WRAP))
check-hub-boot: $(BUILD)/test_hub_boot
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy ./$(BUILD)/test_hub_boot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
.PHONY: check-hub-boot

check: check-hub-boot
check-hub-boot-failure: $(BUILD)/test_hub_boot
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy DW4_HUB_FAIL=1 DW4_HUB_LEGS=1 ./$(BUILD)/test_hub_boot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy DW4_HUB_FAIL=1 DW4_HUB_FAIL_LEG=1 DW4_HUB_LEGS=2 ./$(BUILD)/test_hub_boot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-hub-boot-shutdown: $(BUILD)/test_hub_boot
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy DW4_HUB_CLOSE_LOAD=1 ./$(BUILD)/test_hub_boot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-hub-boot-gpu: $(BUILD)/test_hub_boot
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy DW4_HUB_GPU=1 DW4_HUB_LEGS=2 ./$(BUILD)/test_hub_boot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-hub-boot-gate: $(BUILD)/test_hub_boot
	SDL_VIDEODRIVER=dummy SDL_AUDIODRIVER=dummy DW4_HUB_GATE=1 ./$(BUILD)/test_hub_boot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-hub-boot-gate
.PHONY: check-hub-boot-failure check-hub-boot-shutdown check-hub-boot-gpu check-hub-boot-gate

$(BUILD)/test_modelcontact: tools/test_modelcontact.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-modelcontact: $(BUILD)/test_modelcontact
	./$(BUILD)/test_modelcontact $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check-modelcontact-retail:
	python3 tools/verify_modelcontact_retail.py
	python3 tools/verify_hitbox_retail.py
check: check-modelcontact
check-retail: check-modelcontact-retail
.PHONY: check-modelcontact check-modelcontact-retail

$(BUILD)/test_hubcard: tools/test_hubcard.c tools/savetest.h tools/hubtest.h $(OBJ)
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDLIBS)

check-hubcard: $(BUILD)/test_hubcard
	@mkdir -p $(BUILD)/hub-captures
	./$(BUILD)/test_hubcard $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) $(BUILD)/hub-captures
check: check-hubcard
.PHONY: check-hubcard

$(BUILD)/dump_igb: tools/dump_igb.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
$(BUILD)/census_model: tools/census_model.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
# Every action with two or more MOTIONSETs (or a MOTIONSET behind a WAITCHECK) in the asset tree's model packs: `build/census_motionset ../../local/extracted [all]`.
$(BUILD)/census_motionset: tools/census_motionset.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
# Loot delivery (docs/dungeon-floors.md "Loot delivery"): the recovered roll and delivery rules with fixed random streams, plus the item databases' real rows.
$(BUILD)/test_loot: tools/test_loot.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-loot: $(BUILD)/test_loot
	./$(BUILD)/test_loot $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-loot
.PHONY: check-loot

$(BUILD)/test_fieldstage: tools/test_fieldstage.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
# One target per mode: the modes are independent processes, so make -j runs them side by side and the longest one sets the wall time (they used to be one serial recipe).
FS_ROMS=$(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
FS_BIN=./$(BUILD)/test_fieldstage
FIELDSTAGE_PLAIN=hitschedule startmenu propwalls enemyfall revisit exit damage damagelive hurt guard dungeon dungeoncoop loot lootmodels genediff coopmenus retail fightstatus fightstatus_e2p e2pboss statusapply statusflow statusflow_e2p droptables fightmagic magicapply buffapply supportheal supportbuff supportcure supportraise deathflow deathcoop supportcast coop jumpstop attack technique first lesson4
define fieldstage_plain
check-fieldstage-$(1): $(BUILD)/test_fieldstage
	$(FS_BIN) $(FS_ROMS) $(1)
endef
$(foreach m,$(FIELDSTAGE_PLAIN),$(eval $(call fieldstage_plain,$(m))))
check-fieldstage-dungeon-b1: $(BUILD)/test_fieldstage
	FLOOR=dng102b1 DOORS=doorwall01,doorwall02,doorwall03,doorwall04,doorwall05 $(FS_BIN) $(FS_ROMS) dungeon
check-fieldstage-dungeon-b2: $(BUILD)/test_fieldstage
	FLOOR=dng102b2 DOORS=doorwall01,doorwall02,doorwall03,doorwall04,doorwall05,doorwall06,doorwall07 $(FS_BIN) $(FS_ROMS) dungeon
check-fieldstage-dungeon-b3: $(BUILD)/test_fieldstage
	FLOOR=dng102b3 $(FS_BIN) $(FS_ROMS) dungeon
check-fieldstage-probe-stag0102: $(BUILD)/test_fieldstage
	STAGE=stag0102 $(FS_BIN) $(FS_ROMS) probe
check-fieldstage-room-stagGF03: $(BUILD)/test_fieldstage
	STAGE=stagGF03 $(FS_BIN) $(FS_ROMS) room
FIELDSTAGE_ENV=dungeon-b1 dungeon-b2 dungeon-b3 probe-stag0102 room-stagGF03
check-fieldstage: $(addprefix check-fieldstage-,$(FIELDSTAGE_PLAIN) $(FIELDSTAGE_ENV))
.PHONY: check-fieldstage $(addprefix check-fieldstage-,$(FIELDSTAGE_PLAIN) $(FIELDSTAGE_ENV))
check: check-fieldstage
# The whole mission route from a fresh save: Terminal gate -> practice stage stag0001 (lessons 1-4, arena) -> stag0101 -> stagGF01 -> stagGF02 -> stagGF03 (boss, Leomon, flag 20) -> stagML02 (about fifteen minutes).
check-fieldroute: $(BUILD)/test_fieldstage
	FRESH=1 ./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) route
# The attack path for every one of the 16 forms (DIGIMONNO 0..15, p_<species> model, recalculated record): Cross -> HITBOX -> hit_e_goburi.lua -> FIGHTCALC -> HP, then the kill.
# One target per form (FORM=0..15), each the same attack-and-kill run as before.
FIELDFORMS=0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
define fieldform
check-fieldforms-$(1): $(BUILD)/test_fieldstage
	FORM=$(1) ./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) attack >/dev/null
endef
$(foreach f,$(FIELDFORMS),$(eval $(call fieldform,$(f))))
check-fieldforms: $(addprefix check-fieldforms-,$(FIELDFORMS))
	@echo "field forms: all 16 forms attack and kill the Goblin Pass goblin"
check: check-fieldforms
.PHONY: check-fieldforms $(addprefix check-fieldforms-,$(FIELDFORMS))
check: check-fieldroute
.PHONY: check-fieldroute
# The Humid Cave end to end for one player: stag0101 -> dng101b1 -> dng101b2 -> Blossomon -> the Terminal (about four minutes; docs/dungeon-floors.md).
# One target per party size so make -j runs the four in parallel.
check-dungeonroute-c1: $(BUILD)/test_fieldstage
	$(FS_BIN) $(FS_ROMS) dungeonroute
check-dungeonroute-c2: $(BUILD)/test_fieldstage
	COOP=2 $(FS_BIN) $(FS_ROMS) dungeonroute
check-dungeonroute-c3: $(BUILD)/test_fieldstage
	COOP=3 $(FS_BIN) $(FS_ROMS) dungeonroute
check-dungeonroute-c4: $(BUILD)/test_fieldstage
	COOP=4 $(FS_BIN) $(FS_ROMS) dungeonroute
check-dungeonroute: check-dungeonroute-c1 check-dungeonroute-c2 check-dungeonroute-c3 check-dungeonroute-c4
check: check-dungeonroute
.PHONY: check-dungeonroute check-dungeonroute-c1 check-dungeonroute-c2 check-dungeonroute-c3 check-dungeonroute-c4
# The second dungeon end to end: stag0101 -> stag0102 -> dng102b1 -> dng102b2 -> dng102b3 -> Mammothmon -> the Terminal for 1-4 players (level-60 fixture; the exits are placement, START=dng102b1 skips the field leg)
# One target per party size so make -j runs the four in parallel.
check-dungeonroute2-c1: $(BUILD)/test_fieldstage
	$(FS_BIN) $(FS_ROMS) dungeonroute2
check-dungeonroute2-c2: $(BUILD)/test_fieldstage
	COOP=2 $(FS_BIN) $(FS_ROMS) dungeonroute2
check-dungeonroute2-c3: $(BUILD)/test_fieldstage
	COOP=3 $(FS_BIN) $(FS_ROMS) dungeonroute2
check-dungeonroute2-c4: $(BUILD)/test_fieldstage
	COOP=4 $(FS_BIN) $(FS_ROMS) dungeonroute2
check-dungeonroute2: check-dungeonroute2-c1 check-dungeonroute2-c2 check-dungeonroute2-c3 check-dungeonroute2-c4
check: check-dungeonroute2
.PHONY: check-dungeonroute2 check-dungeonroute2-c1 check-dungeonroute2-c2 check-dungeonroute2-c3 check-dungeonroute2-c4
# Real door collision in the Humid Cave, stick input only (no placement inside the floors; docs/dungeon-floors.md). The quick recipe walks
# stag0101 -> dng101b1 to the first door and pushes into it (under a minute, part of check); the full one walks both floors, the
# doors, the button and the boss door to the Terminal (about three minutes, not part of check).
check-dungeondoors: $(BUILD)/test_fieldstage
	FIRSTDOOR=1 ./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) dungeondoors
check: check-dungeondoors
.PHONY: check-dungeondoors
check-dungeondoors-full: $(BUILD)/test_fieldstage
	./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) dungeondoors
.PHONY: check-dungeondoors-full
# The second dungeon (dng102b1..b3) on the same stick-only footing. The quick recipe opens dng102b1 directly, walks to the
# first door and pushes into it (part of check); the full one walks the three floors, their doors, buttons and Mammothmon's arena to the Terminal (about nine minutes, not part of check).
check-dungeondoors2: $(BUILD)/test_fieldstage
	FIRSTDOOR=1 FLOOR=dng102b1 ./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) dungeondoors2
check-dungeondoors2-full: $(BUILD)/test_fieldstage
	./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) dungeondoors2
# Mammothmon killed with the pad alone (BOSSSMART=1: the technique pilot of smart_fight in the test): dng102b3 started in the arena, no placement of the player
# or script of the boss; the fight, the doors that open on the kill and the exit follow as in the full walk. BOSSBUDGET is the pilot's tick budget.
check-dungeondoors2-boss: $(BUILD)/test_fieldstage
	ARENADIRECT=1 FLOOR=dng102b3 BOSSSMART=1 BOSSBUDGET=6000 BOSSREQUIRE=1 ./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) dungeondoors2
.PHONY: check-dungeondoors2 check-dungeondoors2-full check-dungeondoors2-boss
check: check-dungeondoors2
# dng102b3 GENE-09 (add, 10 total / 6 concurrent) against the retail reads of findings #2978, #3072, #3073: the wave of six at once, the victim's end after HP 0, the refill, no refill while the player is outside the matg09 box (about 35 s).
check-gene09refill: $(BUILD)/test_fieldstage
	./$(BUILD)/test_fieldstage $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted) gene09refill
.PHONY: check-gene09refill
check: check-gene09refill

check-modelsubcom-retail:
	python3 tools/verify_modelsubcom_retail.py
check-retail: check-modelsubcom-retail
.PHONY: check-modelsubcom-retail

$(BUILD)/test_modelsubcom: tools/test_modelsubcom.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-modelsubcom: $(BUILD)/test_modelsubcom
	./$(BUILD)/test_modelsubcom $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-modelsubcom
.PHONY: check-modelsubcom

# Each MOTIONSET starts when the Action2 component walk reaches it and `WAITCHECK Motion` waits for that motion (docs/dungeon-floors.md "Mammothmon's charge"):
# fixed host programs plus the retail Mammothmon pack's SQ_ATCK3 (actn03 + actn04).
$(BUILD)/test_motionset: tools/test_motionset.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
check-motionset: $(BUILD)/test_motionset
	./$(BUILD)/test_motionset $(if $(DW4_ROMS),$(DW4_ROMS),../../local/extracted)
check: check-motionset
.PHONY: check-motionset

check-modeldependencies-retail:
	python3 tools/verify_modeldependencies_retail.py
check-retail: check-modeldependencies-retail
.PHONY: check-modeldependencies-retail

check-bind-retail:
	python3 tools/verify_bind_retail.py
check-retail: check-bind-retail
.PHONY: check-bind-retail

$(BUILD)/survey_stagesound: tools/survey_stagesound.c $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDLIBS)
