 #!/bin/sh
echo '#include "images.h"'
echo "const uint32_t ${2}_arr[] = {"
convert $1 -color-matrix '0 0 1 0, 0 1 0 0, 1 0 0 0, 0 0 0 1' RGBA:- | hexdump -v -e '1/4 "0x%08x,\n"'
echo '};'

echo "const image_t  ${2}_img[] = {"
identify -format "%w, %h,${2}_arr" $1 
echo '};'
