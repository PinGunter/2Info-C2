-- apartado a --
    -- seleccion --
    select distinct nombre from alumnos where provincia='Almeria' or provincia='Granada';
    -- union --
    select nombre from alumnos where provincia='Almeria' union select nombre from alumnos where provincia='Granada';
-- apartado b --
    -- seleccion --
    select distinct alumnos.* from alumnos, matricula, asigna where matricula.dni = alumnos.dni and matricula.codasi#=asigna.asi# and (asigna.curso=1 or asigna.curso=2);
    select distinct alumnos.* from alumnos, matricula, asigna where matricula.dni = alumnos.dni and matricula.codasi#=asigna.asi# and asigna.curso=1 union select distinct alumnos.* from alumnos, matricula, asigna where matricula.dni = alumnos.dni and matricula.codasi#=asigna.asi# and asigna.curso=2;

-- apartado c --
select distinct asigna.* from matricula, asigna, alumnos where matricula.dni = alumnos.dni and matricula.codasi#=asigna.asi# and (asigna.credt + asigna.credpr > 6) and matricula.curso_academico='2014-2015';
-- apartado d --
select * from asigna minus select distinct asigna.* from asigna,matricula where asigna.asi# = matricula.codasi#;
-- apartado e --
select dni,nombre,ape1,ape2 from alumnos where nota >= all (select nota from alumnos);
-- o tambien --
select dni, nombre, ape1, ape2 from alumnos minus select alumnos.dni,alumnos.nombre,alumnos.ape1,alumnos.ape2 from alumnos, alumnos alu where alumnos.nota < alu.nota;

-- apartado f --
select matricula.dni from matricula minus select matricula.dni from matricula mat, matricula where matricula.dni = mat.dni and matricula.codasi# != mat.codasi#;