-- a
select descripcion from (select ref from lista_boda minus select ref from reserva_regalo) res, lista_boda    where res.ref = lista_boda.ref; 

-- b
select direccion from invitaciones, confirman where confirman.nombre=invitaciones.nombre and confirman.numero > 2;

-- c
select reserva_regalo.nombre, reserva_regalo.ref from 
(
    select precio,ref from lista_boda 
        minus 
    select lista_boda.precio, lista_boda.ref from lista_boda, lista_boda lb2 
        where lista_boda.precio < lb2.precio

) tabla1, reserva_regalo where tabla1.ref = reserva_regalo.ref;
