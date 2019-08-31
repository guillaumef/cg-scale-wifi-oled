all: photo screenshot

photo:
	@for file in photo-*.jpg; do \
		convert $$file -resize 20\% ../$$file;	\
		mogrify -font Liberation-Sans -fill white -undercolor '#00000080' -pointsize 26 -gravity NorthEast -annotate +10+10 'development unit' ../$$file; \
	 done

screenshot:
	@for file in screenshot-*.jpg; do \
		convert $$file -resize 50\% ../$$file; \
	 done
