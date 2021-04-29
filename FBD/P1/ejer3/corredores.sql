-- Corredores --
CREATE TABLE paises(
    cod_pais varchar2(5)
        constraint cod_pais_no_nulo not null,
    nomb_pais varchar2(30),
    PRIMARY KEY (cod_pais)
);

CREATE TABLE equipos(
    cod_eq varchar2(5)
        constraint cod_eq_no_nulo not null,
    nombre_eq varchar2(30),
    director varchar2(30),
    PRIMARY KEY(cod_eq)
);

CREATE TABLE corredores(
    no_corre number
        constraint no_corre_no_nulo not null
        constraint no_corre_mayor_0 check(no_corre>0),
    cod_eq references equipos(cod_eq),
    cod_pais references paises(cod_pais),
    nom_corredor varchar2(30),
    PRIMARY KEY (no_corre)
);

CREATE TABLE etapas(
    no_etapa number
        constraint no_etapa_mayor_0 check(no_etapa>0)
        constraint no_etapa_no_nulo not null,
    fecha date,
    ciusal varchar2(30),
    ciudlle varchar2(30),
    kms number,
    PRIMARY KEY(no_etapa)
);

CREATE TABLE tiempos(
    no_corre references corredores(no_corre),
    no_etapa references etapas(no_etapa),
    tiempo number(8,4),
    PRIMARY KEY(no_corre,no_etapa)
);

CREATE TABLE tests(
    test_id varchar2(10)
        constraint test_id_no_null not null,
    denominacion varchar2(30),
    PRIMARY KEY(test_id)
);

CREATE TABLE t_realizados(
    no_corre,
    no_etapa,
    test_id,
    result varchar2(10),
    PRIMARY KEY (no_corre,no_etapa,test_id),
    FOREIGN KEY (no_corre,no_etapa) references tiempos(no_corre,no_etapa),
    FOREIGN KEY (test_id) references tests(test_id)

);