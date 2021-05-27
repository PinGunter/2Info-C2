-- ejercicio 1
select avg(nota), stddev(nota) from alumnos group by sexo having sexo='v';

-- ejercicio 2
select max(credt+credpr), min(credt+credpr) from asigna;

-- ejercicio 3
select count(*) from matricula;

-- ejercicio 4
select count(*) from matricula where calificacion!='np';

-- ejercicio 5
select nombre, ape1, ape2 from alumnos a where edad =  (select min(edad) from alumnos);
-- sin operador min lo hubieramos hecho asi:
select nombre, ape1, ape2 from alumnos al minus select al.nombre,al.ape1, al.ape2 from alumnos al, alumnos al2 where al.edad > al2.edad;

-- ejercicio 6
select nombre, ape1, ape2,nota from alumnos where nota <= (select avg(nota) from alumnos);

-- ejercicio 7
select dni from matricula where curso_academico='2016-2017' group by dni having count(*) > 4;

-- ejercicio 8
select codasi# from matricula group by codasi# having count(codasi#) > 25;

-- ejercicio 9
select nombreas, credt, credpr, credpr+credt from asigna where (credpr+credt) = (select max(credt+credpr) from asigna);