-- apartado g --
select distinct ventas.codpj from ventas, proveedor, proyecto where ventas.codpj = proyecto.codpj and ventas.codpro = proveedor.codpro  and proveedor.ciudad != proyecto.ciudad;

-- apartado h --
select pieza.ciudad from pieza union select proyecto.ciudad from proyecto;

-- apartado i --
select ciudad from proveedor minus select ciudad from pieza;

-- apartado j --
select ciudad from (select * from proveedor natural join (select * from pieza));
-- tambien se puede hacer así--
select proveedor.ciudad from (proveedor join pieza on proveedor.ciudad = pieza.ciudad);

-- apartado k --
select distinct codpj from ventas where codpro='S1';

-- apartado l --
select cantidad from ventas where cantidad <= all (select cantidad from ventas);
-- tambien --
select cantidad from ventas minus select ventas.cantidad from ventas, ventas v where ventas.cantidad > v.cantidad;

-- apartado m --
select codpj from ventas minus select distinct ventas.codpj from ventas, pieza, proveedor where ventas.codpie = pieza.codpie and proveedor.codpro = ventas.codpro and pieza.color = 'Rojo' and proveedor.ciudad = 'Londres';

-- apartado n --
select distinct codpj from ventas where codpro='S1' minus select distinct codpj from ventas where codpro!='S1';