bin_PROGRAMS=ships
ships_SOURCES=	gamecontroller.h \
				ships.h \
				object.h \
				shipviews.h \
				shipscontroller.cpp \
				views.cpp \
				gamecontroller.cpp \
				ship.cpp \
				camera.cpp \
				object.cpp
				

if WIN_32
ships_SOURCES += Ships_win32.cpp
else
ships_SOURCES += Ships.cpp
endif
				
ships_INCLUDES= $(SDL_CFLAGS)
ships_LDADD= $(LIBS)
