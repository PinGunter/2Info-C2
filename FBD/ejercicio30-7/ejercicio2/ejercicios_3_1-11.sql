-- ejercicio 3.1 --
select ciudad from proyecto;
-- ejercicio 3.2 -- 
select distinct codpro, codpie, codpj from ventas;
-- ejercicio 3.3 -- 
select distinct * from pieza where (color='Gris' or color='Rojo') and ciudad='Madrid';
-- ejercicio 3.4 -- 
select * from ventas where cantidad>=200 and cantidad<=300;
-- ejercicio 3.5 -- 
select * from pieza where nompie like '%_ornillo%';
-- ejercicio 3.6 -- 
select table_name from ALL_TABLES where TABLE_NAME like '%ventas';
-- ejercicio 3.7 -- 
(select distinct ciudad from proveedor where status>2) INTERSECT (select distinct ciudad from pieza where codpie != 'P1');
-- ejercicio 3.8 -- 
(select distinct codpj from ventas where codpro='S1') MINUS (select distinct codpj from ventas where codpro!='S1');
-- ejercicio 3.9 -- 
(select ciudad from proveedor) UNION (select ciudad from pieza) UNION (select ciudad from proyecto);
-- ejercicio 3.10 -- 
(select ciudad from proveedor) UNION ALL (select ciudad from pieza) UNION ALL (select ciudad from proyecto);
-- ejercicio 3.11 -- 
select count (*) from ventas,proveedor;