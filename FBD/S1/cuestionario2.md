**Definir cardinalidad máxima y mínima y dar dos ejemplos: uno referente a una relación uno a muchos y otro referente a una relación muchos a muchos**

Cardinalidad máxima y mínima hace referencia a la cota superior e inferior del número de entidades que pueden participar en una relación uno a muchos(1:n). o muchos a muchos (n:m).

Es decir, indican cuál es el valor máximo y/o mínimo de n y de m.

Ejemplo con uno a muchos:
Profesor enseña a alumnos (1:n). Un profesor enseña a varios alumnos. Para que sea posible dar clase es necesario que hay mínimo 5 alumnos y máximo 50. La cardinalidad mínima de alumnos es 5 y la máxima 50.

Ejemplo con muchos a muchos:
Alumnos se matriculan de asignaturas. En cada grupo hay un mínimo de 5 alumnos y un máximo de 100. Y cada alumno se puede matricular de entre 1 y 15 asignaturas. Entonces, en este caso la cardinalidad mínima de alumnos es 5 y la máxima es 100. En el caso de asignaturas es 1 y 15, respectivamente.

**Definir entidad débil, dar dos ejemplos diferentes de los estudiados en clase**

Una entidad débil es una entidad que no tiene sentido por sí sola, necesita de otra entidad para identificarse (denominada entidad fuerte). Es imposible identificar a la débil sin la fuerte.

Ejemplo 1:

La entidad llave (débil) no tiene sentido sin la existencia de una puerta (fuerte).

La entidad volante (débil) no tiene sentido sin la existencia de un coche (fuerte).

**Distinguir mediante un ejemplo de cada uno el concepto de de entidad débil de el de relación uno a muchos**

Una entidad débil podría ser "llave" que no tiene sentido sin puerta o sin casa.

Una relación uno a muchos puede ser un propietario que tiene varias llaves (1 propietario: n llaves).

**Defina el concepto de subtipo, ponga dos ejemplos que no se hayan explicado en clase**

Si el conjunto de entidades A está incluido en el conjunto de entidades de B, entonces diremos que A es un sub-tipo de B.

Por ejemplo un móvil es un sub-tipo de dispositivo electrónico.

Otro ejemplo: un escritorio es un sub-tipo de mueble.

**Defina el concepto de herencia. ¿Como se relaciona con el de tipo y subtipo?**

**Explicar la diferencia entre la relción TIENE-UN y la relación ES-UN poner un ejemplo de cada una de ellas.**

**Decidir de forma razonada si se debe incluir una entidad nueva junto con una relación, o un atributo en el caso de los cuartos de baño que tiene un apartamento. Si se ha decidido que hay que añadir una entidad junto con una nueva relación especificar las características de esta última**

**Decidir de forma razonada si se debe incluir una entidad nueva junto con una relación, o un atributo en el caso del responsable de una investigación criminal. Si se ha decidido que hay que añadir una entidad junto con una nueva relación especificar las características de esta última**

**Decidir de forma razonada si se debe incluir una entidad nueva junto con una relación, o un atributo en el caso de la fecha y hora de un crimen. Si se ha decidido que hay que añadir una entidad junto con una nueva relación especificar las características de esta última**

**Decidir de forma razonada si se debe incluir una entidad nueva junto con una relación, o un atributo en el caso del horario de una asignatura. Si se ha decidido que hay que añadir una entidad junto con una nueva relación especificar las características de esta última**
