-- a --
select distinct codpro from ventas where codpj='J1';

-- b --
select distinct nompie,pieza.codpie from ventas,pieza where cantidad>100;

-- c --
select distinct nompro, nompie, nompj from proveedor,pieza,proyecto where proveedor.ciudad=pieza.ciudad and proveedor.ciudad=proyecto.ciudad;

-- d --
select distinct nompie from ventas, proveedor,pieza where ventas.codpro=proveedor.codpro and proveedor.ciudad='Londres' and ventas.codpie=pieza.codpie; --De Londres no hay ninguno que lo cumpla

-- e --
select distinct proveedor.ciudad, proyecto.ciudad from proveedor,proyecto,ventas where ventas.codpro=proveedor.codpro and ventas.codpj=proyecto.codpj;

-- f --
select distinct pieza.codpie from pieza,proveedor,proyecto,ventas where ventas.codpie=pieza.codpie and ventas.codpj=proyecto.codpj and ventas.codpro=proveedor.codpro and proveedor.ciudad=proyecto.ciudad;
