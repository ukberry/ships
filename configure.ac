dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.68)
AC_INIT([ships], 0.2)

AC_CONFIG_AUX_DIR(conf)

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CXX

dnl PKG_CHECK_MODULES([SDL],[sdl])
dnl AC_SUBST(SDL_CFLAGS)
dnl AC_SUBST(SDL_LIBS)

AC_CHECK_HEADER([SDL/SDL.h])

AC_MSG_CHECKING([for native Win32])

case "$host" in
	*-*-mingw*)
		CFLAGS="$CFLAGS -include windows.h -mwindows"
		CXXFLAGS="$CXXFLAGS -include windows.h -mwindows"
		os_win32=yes
		;;
	*) 
		
		os_win32=no
		;;
esac
AC_MSG_RESULT([$os_win32])
AM_CONDITIONAL(WIN_32,[test "xyes" = "x$os_win32"])

dnl Check for OpenGL (Original or Mesa) (or osX-framework)
		AC_CHECK_HEADERS([GL/glew.h GL/gl.h GL/glu.h],[],
		    [AC_CHECK_HEADERS([OpenGL/glew.h OpenGL/gl.h OpenGL/glu.h],[],[echo "OpenGL is mandatory";exit 1;])
		    ])


AC_CHECK_LIB([m],[sin],,)

AC_CHECK_LIB([SDL],[SDL_Init],,)

if test "xno" = "x$os_win32"; then

if test `uname -s` != Darwin; then
dnl Check for GLU (Original or Mesa)
    AC_CHECK_LIB(GLU, gluLookAt, ,[
        AC_CHECK_LIB(MesaGLU,gluLookAt,,
            [echo "incomplete OpenGL (no GLU)";exit 1])]
    )

    AC_CHECK_LIB([GL], [glInitNames],,[
        AC_CHECK_LIB(MesaGL,glInitNames,,
            [echo "OpenGL is mandatory";exit 1]])
    )

    AC_CHECK_LIB([GLEW], [glewInit],,[
        AC_CHECK_LIB(MesaGLEW,glewInit,,
            [echo "GLEW is mandatory";exit 1]])
    )
fi

else
LIBS="-lopengl32 -lglu32 $LIBS"
fi

AC_CONFIG_FILES(Makefile src/Makefile data/Makefile)
AC_OUTPUT

