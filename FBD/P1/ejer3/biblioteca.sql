-- Creacion de tablas --
CREATE TABLE libro(
    cod_libro number 
        constraint cod_libro_no_nulo not null,
    titulo varchar2(30)
        constraint titulo_no_nulo not null,
    PRIMARY KEY(cod_libro)
);

CREATE TABLE ejemplar(
    cod_libro references libro(cod_libro),
    n_ejemplar number
        constraint numero_mayor_que_1 check(n_ejemplar>1)
        constraint n_ejemplar_no_nulo not null,
    PRIMARY KEY(cod_libro,n_ejemplar)
);

CREATE TABLE prestado(
    cod_libro references ejemplar(cod_libro),
    n_ejemplar references ejemplar(n_ejemplar),
    
);