dist_pkgdata_DATA = \
	flexskel.cc \
	flexskel.h

# libmain.c -> libfl.a, not installed.
# main.c -> libmain.a, for per-object flags.
noinst_LIBRARIES = \
	libfl.a \
	libmain.a

libfl_a_SOURCES = \
	libmain.c

libmain_a_SOURCES = \
	main.c
libmain_a_CPPFLAGS = $(AM_CPPFLAGS) \
	-DDEFAULT_SKELETON_FILE='"$(pkgdatadir)/flexskel.cc"' \
	-DDEFAULT_SKELETONHEADER_FILE='"$(pkgdatadir)/flexskel.h"'

# Generate parse.[ch] using bison++.
# Not using AC_PROG_YACC because it doesn't search for bison++.
BUILT_SOURCES = parse.h
YACC = bison++ -y
AM_YFLAGS = -d

# Generate scan.c using flex++ (yes, it generates its own source code).
# Be sure to distribute a copy of scan.c so others can booststrap.
LEX = flex++
LEX_OUTPUT_ROOT = lex.yy
AM_LFLAGS = -is8

# FIXME:  The following two paragraphs were in the previous make system.
# If they still apply today, then we should provide an option to do this.
#
# By default, flex will be configured to generate 8-bit scanners only
# if the -8 flag is given.  If you want it to always generate 8-bit
# scanners, add "-DDEFAULT_CSIZE=256" to CFLAGS.  Note that doing
# so will double the size of all uncompressed scanners.
#
# If on your system you have trouble building flex due to 8-bit
# character problems, remove the -8 from FLEX_FLAGS and the
# "#define FLEX_8_BIT_CHARS" from the beginning of flexdef.h.

bin_PROGRAMS = flex++
flex___SOURCES = \
	ccl.c \
	dfa.c \
	ecs.c \
	gen.c \
	misc.c \
	nfa.c \
	sym.c \
	tblcmp.c \
	yylex.c \
	flexdef.h \
	scan.l \
	parse.y
flex___LDADD = \
	libmain.a

# FIXME:  Here are the tests from the previous make system.
# doc/Notes.txt indicates that these are obsolete.
#
#COMPRESSION =
#FLEX_FLAGS = -ist8
#test : flex++
#	echo "diff should only be on #line directive"
#	-./flex++ $(FLEX_FLAGS) -S./flexskel.cc -H./flexskel.h $(COMPRESSION) scan.l | diff scan.c -
#bigtest :
#	echo "diff should only be on #line directive"
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-C" test
#	echo "diff should only be on #line directive"
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-Ce" test
#	echo "diff should only be on #line directive"
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-Cm" test
#	echo this should fail because there is trailing context in the grammar
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-Cfe" test
#	echo this should fail because there is trailing context in the grammar
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-CFe" test
#	echo this should fail because there is trailing context in the grammar
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-Cf" test
#	echo this should fail because there is trailing context in the grammar
#	-rm -f scan.c ; $(MAKE) COMPRESSION="-CF" test
#	echo "diff should only be on #line directive"
#	-rm -f scan.c ; $(MAKE)
