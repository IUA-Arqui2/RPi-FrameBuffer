 #!/bin/sh

#    USO:
#       bash img2h.sh {archivo Imagen} {prefijo variable} > {archivo de salida}
#           prefijo: es el nombre que se le dará al arreglo y a la estructura con los datos
#
#    Ejemplo:
#       bash img2h.sh assets/img.png smile  > assets/img.h
#    Se creará la estructura smile_img y el arreglo smile_arr
#


echo '#include "images.h"'
echo "const uint32_t ${2}_arr[] = {"
convert $1 -color-matrix '0 0 1 0, 0 1 0 0, 1 0 0 0, 0 0 0 1' RGBA:- | hexdump -v -e '1/4 "0x%08x,\n"'
echo '};'

echo "const image_t  ${2}_img = {"
identify -format "%w, %h,${2}_arr" $1 
echo '};'
