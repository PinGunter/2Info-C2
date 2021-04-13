#!/bin/csh -vx
echo "" >> salida_basico.dat
@ i = 10000
while ( $i < 10000000 )
./algoritmo_basico $i >> salida_basico.dat
@ i += 1000
end
