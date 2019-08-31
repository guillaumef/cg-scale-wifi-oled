all:
	@for file in *.jpg; do \
		convert $$file -resize 20\% ../$$file;	\
		mogrify -font Liberation-Sans -fill white -undercolor '#00000080' -pointsize 26 -gravity NorthEast -annotate +10+10 'development unit' ../$$file; \
	 done
