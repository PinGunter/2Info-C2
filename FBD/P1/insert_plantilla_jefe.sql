INSERT INTO plantilla(dni,nombre,estadocivil,fechaalta)
    VALUES ('12345678', 'Pepe', 'soltero', SYSDATE);
INSERT INTO plantilla(dni,nombre,estadocivil,fechaalta)
    VALUES ('87654321', 'Juan', 'casado', SYSDATE);
    
INSERT INTO serjefe VALUES('87654321','12345678');
INSERT INTO plantilla (dni,estadocivil) VALUES ('11223344', 'soltero');

UPDATE plantilla set estadocivil='divorciado' where nombre='Juan';
UPDATE plantilla SET fechaalta = fechaalta + 1 where nombre='Juan';

INSERT INTO plantilla values ('11223355', 'Miguel', 'casado', TO_DATE('22/10/2005','dd/mm/yyyy'));