CREATE TABLE plantilla(
    dni char(8),
    nombre varchar2(15),
    estadocivil varchar(10)
        CHECK (estadocivil IN ('soltero', 'casado', 'divorciado', 'viudo')),
    fechaalta date,
    PRIMARY KEY (dni)
);