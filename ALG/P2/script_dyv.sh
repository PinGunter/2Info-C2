#!/bin/csh -vx
echo "" >> salida_dyv.dat
@ i = 10000
while ( $i < 1000000 )
./algoritmo_dyv $i >> salida_dyv.dat
@ i += 1000
end
