#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(lib/libsdi.c)
AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

LIBSDI_AGE=0
LIBSDI_REVISION=1
LIBSDI_CURRENT=0
AC_SUBST(LIBSDI_AGE)
AC_SUBST(LIBSDI_REVISION)
AC_SUBST(LIBSDI_CURRENT)
VERSION=$LIBSDI_AGE.$LIBSDI_REVISION.$LIBSDI_CURRENT

AM_INIT_AUTOMAKE(libsdi, $VERSION)


# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_AWK
AC_PROG_LIBTOOL

AC_CONFIG_FILES([Makefile
                 cmd/Makefile
                 lib/Makefile
                 test/Makefile])
AC_OUTPUT
