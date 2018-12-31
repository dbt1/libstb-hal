# explicit defines for separate revision handling
define(ver_major, 0)
define(ver_minor, 2)
define(ver_micro, 1)

# sync with current git
define(ver_git, m4_esyscmd([
	GITBRANCH=$(git rev-parse --abbrev-ref HEAD);
	GITDESCRIBE=$(git describe --always --tags --dirty);
	printf "$GITDESCRIBE $GITBRANCH"
]))

AC_PACKAGE_NAME, PACKAGE_NAME_LIBSTB_HAL
AC_INIT([Tuxbox-libstb-hal], [ver_major.ver_minor.ver_micro])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([include/libstb-hal-config.h])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AC_CONFIG_MACRO_DIR([m4])
AC_GNU_SOURCE

AC_DEFINE(PACKAGE_VERSION_MAJOR, ver_major, [Major version number])
AC_DEFINE(PACKAGE_VERSION_MINOR, ver_minor, [Minor version number])
AC_DEFINE(PACKAGE_VERSION_MICRO, ver_micro, [Micro version number])
AC_DEFINE(PACKAGE_VERSION_GIT, "ver_git", [internal vcs version info])

TUXBOX_APPS
TUXBOX_APPS_DIRECTORY
TUXBOX_BOXTYPE

AC_PROG_CC
AC_PROG_CXX
PKG_PROG_PKG_CONFIG
## both disabled => libtool still defaults to static
##                  at least the libtool I tested with ;-)
## --enable-shared => build only shared
## --enable-shared --enable-static => build both
AC_DISABLE_SHARED
AC_DISABLE_STATIC
AC_SYS_LARGEFILE
AC_PROG_LIBTOOL

AC_ARG_ENABLE(clutter,
	AS_HELP_STRING(--enable-clutter, use clutter instead of OpenGL),
	,[enable_clutter=no])

AM_CONDITIONAL(USE_CLUTTER,test "$enable_clutter" = "yes")
AM_CONDITIONAL(USE_OPENGL,test "$enable_clutter" = "no")
if test "$enable_clutter" = "yes"; then
	AC_DEFINE(USE_CLUTTER,1,[use clutter instead of opengl])
else
	AC_DEFINE(USE_OPENGL,1,[use opengl instead of clutter])
fi

if test x"$BOXTYPE" = x"tripledragon"; then
	PKG_CHECK_MODULES([DIRECTFB], [directfb])
fi

if test x$BOXTYPE = xgeneric; then
	if test x"$enable_clutter" = xyes; then
		PKG_CHECK_MODULES([CLUTTER], [clutter-1.0])
	fi
	if test x$BOXMODEL != xraspi; then
		PKG_CHECK_MODULES([AVFORMAT], [libavformat >= 53.21.1])
		PKG_CHECK_MODULES([AVCODEC], [libavcodec >= 54.28.0])
		# don't know which version is exactly needed here...
		PKG_CHECK_MODULES([SWSCALE], [libswscale])
	else
		# openmaxil are the broadcom userspace libs
		# my yocto (openembedded) layer has an openmaxil package built from userland git.
		# Use that if available. If not, just fall back to /opt/vc/...
		# can be overridden with OMX_CFLAGS= OMX_LIBS= variables...
		#
		PKG_CHECK_MODULES([OMX], [openmaxil], echo "OpenMAX/IL userspace package found. Good.",
			[ echo "OpenMAX/IL package not found, assuming /opt/vc/..."
			  OMX_CFLAGS="-I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads/ -I/opt/vc/include/interface/vmcs_host/linux"
			  OMX_LIBS="-L/opt/vc/lib/ -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -pthread"
			])
		# raspbian has no current versions and only libav instead of ffmpeg... :-(
		PKG_CHECK_MODULES([AVFORMAT], [libavformat])
		PKG_CHECK_MODULES([AVCODEC], [libavcodec])
	fi
	PKG_CHECK_MODULES([SWRESAMPLE], [libswresample])
	# don't know which version is exactly needed here...
	PKG_CHECK_MODULES([AVUTIL], [libavutil])
fi
if test x$BOXTYPE = xspark; then
	# versions are probably not correct :-(
	PKG_CHECK_MODULES([AVFORMAT], [libavformat >= 53.21.1])
	PKG_CHECK_MODULES([AVCODEC], [libavcodec >= 54.28.0])
	PKG_CHECK_MODULES([SWRESAMPLE], [libswresample])
	PKG_CHECK_MODULES([AVUTIL], [libavutil])
fi

AC_OUTPUT([
Makefile
common/Makefile
libeplayer3/Makefile
azbox/Makefile
generic-pc/Makefile
libtriple/Makefile
libspark/Makefile
raspi/Makefile
tools/Makefile
])

