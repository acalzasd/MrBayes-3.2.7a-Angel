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

MrBayes 3.2.7a modified by Angel Calzas allows working with temperatures 
lower than 1 with the parameter "RedTemp", and it allows changes only 
between chains with adjacent temperatures in the Parallel Tempering. 
In addition, it exports the indices of the chains in a file named 
"tempIndex.dat", in order to be able to carry out a convergence analysis 
with the autocorrelation times. Therefore, in addition to the modified 
MrBayes, a C program is added which allows this analysis, called "analisisR.c", 
in which line 14 must be modified to add the path to the file "tempIndex.dat".

Build instructions, very very short version (would install MrBayes as
"/usr/local/bin/mb" on a Unix system):
    git clone --depth=1 https://github.com/acalzasd/MrBayes-3.2.7a-Angel.git
    cd MrBayes
    ./configure
    make && sudo make install
Refer to the document called "INSTALL" for further information. Original 
file "INSTALL" from MrBayes 3.2.7a.
