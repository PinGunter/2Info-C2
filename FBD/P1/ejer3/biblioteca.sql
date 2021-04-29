-- Creacion de tablas --
CREATE TABLE libro(
    n_libro number 
        constraint cod_libro_no_nulo not null,
    titulo varchar2(30)
        constraint titulo_no_nulo not null,
    PRIMARY KEY(n_libro)
);

CREATE TABLE ejemplar(
    n_libro references libro(n_libro),
    n_ejemplar number
        constraint numero_mayor_que_1 check(n_ejemplar>1)
        constraint n_ejemplar_no_nulo not null,
    PRIMARY KEY(n_libro,n_ejemplar)
);

CREATE TABLE autor(
    dni_a varchar2(9)
        constraint dnia_no_nulo not null,
    nombre_a varchar2(30)
        constraint nombre_a_no_nulo not null,
    PRIMARY KEY(dni_a)
);

CREATE TABLE tema(
    n_tema number
        constraint n_tema_no_nulo not null
        constraint n_tema_mayor_que_0 check (n_tema>0),
    descr varchar2(50)
        constraint descripcion_no_nula not null,
    
    PRIMARY KEY(n_tema)
);

CREATE TABLE usuario(
    dni varchar2(9)
        constraint dni_no_nulo not null,
    nombre_u varchar2(30),
    PRIMARY KEY(dni)
);

CREATE TABLE trata(
    n_libro references libro(n_libro),
    n_tema references tema(n_tema),
    PRIMARY KEY (n_tema)
);


CREATE TABLE escribe(
    n_libro references libro(n_libro),
    dni_a references autor(dni_a),
    PRIMARY KEY(n_libro,dni_a)
);

CREATE TABLE prestado(
    n_libro ,
    n_ejemplar ,
    dia_inicio date
        constraint dia_inicio_not_null not null,
    n_dias number,
    dni references usuario(dni),
    UNIQUE(dia_inicio,dni),
    PRIMARY KEY (n_libro,n_ejemplar,dia_inicio),
    FOREIGN KEY (n_libro,n_ejemplar) references ejemplar(n_libro,n_ejemplar)
    
);