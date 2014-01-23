T = sevcon$(EXT)
TARGETS += $T

SUBDIRS += velib
$T_DEPS += $(call subtree_tgts,$(d)/velib)

SUBDIRS += src
$(T)_DEPS += $(call subtree_tgts,$(d)/src)

CC_CONFIG_CFLAGS += -DDBUS $(shell pkg-config --cflags dbus-1)
$T_LIBS += -lpthread -ldl $(shell pkg-config --libs dbus-1) -levent

INCLUDES += inc
INCLUDES += velib/inc
