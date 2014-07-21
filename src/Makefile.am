bin_PROGRAMS=ships
ships_SOURCES=	gamecontroller.h \
				ships.h \
				shipsviews.h \
				shipscontroller.cpp \
				shipview.cpp \
				views.cpp \
				gamecontroller.cpp \
				ship.cpp \
				camera.cpp \
				shaders.h \
				shaders.cpp \
				object.h \
				object.cpp

ships_CXXFLAGS =-DDATADIR=\"$(datadir)\" \
				-DTOPDIR=\"$(srcdir)\" \
				-I$(srcdir)/data
			
			
# While debugging, turn optimisation off	
CXXFLAGS = -g -O0

if WIN_32
ships_SOURCES += Ships_win32.cpp
else
ships_SOURCES += Ships.cpp
endif
				
#ships_INCLUDES= $(SDL_CFLAGS)
ships_LDADD= $(LIBS)
