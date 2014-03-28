# Always include top-level source directory
AM_CXXFLAGS = -I$(top_srcdir) -I$(top_builddir) @AM_CXXFLAGS@

# Set default compiler flags
AM_CXXFLAGS += --std=c++0x -Wc++0x-compat
AM_CXXFLAGS += \
	-Wall \
	-Wextra \
	-Wabi \
	-Wold-style-cast

if CC_FLAG_USE_NULL_SENTINEL
AM_CXXFLAGS += \
	-Wstrict-null-sentinel
endif

# Dependencies XXX keep these in sync with meta.pc.in
# AM_LDFLAGS += 
