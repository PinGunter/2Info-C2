-- apartado ñ ---
select distinct codpie from (select * from ventas natural join 
(select codpj from proyecto where ciudad='Paris'));

-- apartado o --
select codpro from (
select v1.codpro, v1.codpie from ventas v1 where
not exists (
    select codpj from proyecto minus
    select codpj from ventas v2 where v1.codpro=v2.codpro and v1.codpie=v2.codpie)
);
-- apartado p --
select distinct v1.codpj from ventas v1 where codpro='S1' and
not exists(
    select codpie from pieza
    minus
    select codpie from ventas v2 where v2.codpj=v1.codpj
);

-- apartado q --
select codpro from (
select v1.codpro, v1.codpie from ventas v1 where
not exists (
    select codpj from proyecto minus
    select codpj from ventas v2 where v1.codpro=v2.codpro)
);