# The man and info pages for flex (not flex++)
# were not installed by the previous make system.
dist_man1_MANS = \
	flex++.1
dist_noinst_MANS = \
	flex.1 \
	flexdoc.1

# The .dman file and the rule below is/was used to generate the man page.
# According to the man page, it was with a flex++/bison++ parser.
# The source code for that parser is probably lost.
#%: %.dman
#	dman < $*.dman > $@
#	pman -t $@ > $*.ps

# FIXME:  For some reason automake isn't distributing the noinst files,
# so place them in EXTRA_DIST to force their inclusion.
EXTRA_DIST = \
	flex++.1.dman \
	Notes.txt \
	notesevolution \
	misc/Atari.patches \
	misc/MSDOS.notes \
	misc/Makefile.VMS \
	misc/README \
	misc/Turbo-C.notes \
	misc/flex.skel.old \
	$(dist_noinst_MANS)
