-- 3.19
select distinct codpie from ventas where codpro in (select codpro from proveedor where ciudad='Madrid');
-- 3.20
