# MrBayes-3.2.7a-Angel
MrBayes 3.2.7a modificado por Ángel Calzas, permite realizar trabajar
con temperaturas menores a 1 con el parámetro "RedTemp" y permite 
realizar cambios en el Parallel Tempering sólo entre cadenas con 
temperaturas adyacentes. Además, exporta los índices de las cadenas 
en un fichero de nombre "tempIndex.dat", para poder realizar un 
análisis de la convergencia con los tiempos de autocorrección.
Se añade, por consiguiente, además del MrBayes modificado un programa
en C que permite este análisis, denominado "analisisR.c", en cual se 
debe modificar la línea 14 y añadir la ruta del fichero "tempIndex.dat".

Build instructions, very very short version (would install MrBayes as
"/usr/local/bin/mb" on a Unix system):
    git clone --depth=1 https://github.com/acalzasd/MrBayes-3.2.7a-Angel.git
    cd MrBayes
    ./configure
    make && sudo make install
Refer to the document called "INSTALL" for further information. Original 
file "INSTALL" from MrBayes 3.2.7a.
