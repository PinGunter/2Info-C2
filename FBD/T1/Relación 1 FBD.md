### Relación 1 FBD

###### Salvador Romero Cortés

---

**1. Cuales son las principales diferencias entre un sistema de procesamiento de archivos y un sistema de bases de datos**

Por una parte, un SGBD consiste en una colección de datos interrelacionados y un conjunto de programas para acceder a dichos datos. El objetivo principal es proporcionar una forma de almacenar y recuperar la información de manera que sea tanto práctica como eficaz.

Por otra parte, un sistema de procesamiento de archivos nos permite almacenar información pero con una serie de inconvenientes como redundancia e inconsistencia.

Las diferencias principales son que, un sistema de procesamiento de archivos no nos permite indexar la información, realizar búsquedas complejas, consistencia en la información ni una fácil administración de ella.

* Crear un archivo con una estructura determinada
* Consultar o actualizar un archivo imponiendo diferentes condiciones.
* Modificar dinámicamente la estructura de un archivo.
* Proteger ciertos datos de usuarios no autorizados.
* Permitir el acceso desde distintas aplicaciones, con distintos lenguajes y sistemas operativos.

Todas estas funciones resultan complejas con un sistema de procesamiento de archivos, mientras que se pueden evitar usando un SGBD.

**2. Características más importantes en una base de datos. Propiedades más deseables. Explicar a tu juicio cuál es la propiedad más importante.**

* Independencia de los datos.
* Diseño y utilización orientada al usuario.
* Centralización.
* No redundancia.
* Consistencia.
* Fiabilidad.
* Seguridad.

Las más importantes diría que son la no redundancia. Cada vez almacenamos más información y es necesario asegurarse de que se almacena de manera eficiente sin tener que gastar más de lo necesario en almacenamiento.

**3. Hemos conocido cuales son las ventajas de utilizar un sistema de bases de datos, podrías encontrar algún inconveniente.**

Los SGBD son programas muy complejos que necesitan que los administradores esté bien formados. Además son software con requisitos de memoria y almacenamiento altos.

**4. Explica la diferencia entre independencia física e independencia lógica.**

La independencia física quiere decir que el diseño lógico de la base de datos no se tiene que corresponder con la manera en la que se almacena físicamente. 

La independencia lógica permite tener dos esquemas o vistas, de manera que se puede tener una visión general (de todos los datos) o una visión ajustada a los datos que necesite un usuario.

**5. Definir brevemente:**

* **Base de datos:** instancia de un esquema lógico junto con las instancias de los datos operativos que dicho esquema organiza.
* **DBMS**: Conjunto de elementos software con capacidad para definir, mantener y utilizar una base de datos.
* **DBA:** Encargado de gestionar todos los componentes del SGBD para que la BD represente e integre adecuadamente todos los elementos de información precisados por las aplicaciones y usuarios.
* **Acceso concurrente:** Un acceso a la base de datos por más de un usuario simultáneamente.
* **Visión de usuario:** Los datos a los que tiene acceso un usuario de la base de datos.

**6. Explicar brevemente los conceptos de: Integridad, fiabilidad y seguridad en una base de datos. Ordenarlos por importancia explicando los criterios utilizados. ¿En qué etapa de la vida de una base de datos se deben tener en cuenta unos y otros? ¿Cómo se mantienen en una base de datos?**

**Integridad:** correctitud y completitud de la información.

**Fiabilidad:** indica que la base de datos funciona correctamente. Que los datos mantienen consistencia y son precisos.

**Seguridad:** conjunto de herramientos, controles y medidas diseñadas a establecer y preservar la confidencialidad, integridad y disponibilidad de una base de datos.

Los ordenaría como Integridad > Fiabilidad > Seguridad. Puesto que lo más importante es que la base de datos tenga datos e información correcta, siendo totalmente inservible si no cumple la propiedad de integridad. En segundo puesto, la fiabilidad puesto que es importante que el funcionamiento sea correcto. Finalmente, la seguridad puesto que si ya hemos cumplido que los datos y el funcionamiento sea correcto, ahora toca protegerlos.

La integridad de los datos es especialmente a la hora de crear la base de datos mientras que la fiabilidad y seguridad es algo que se mantiene a lo largo de toda la vida de la base de datos.

**7. Definir y situar históricamente lo siguientes términos**
* **COBOL** Primer lenguaje de orientado a la definición de datos en los 60.
* **Acceso secuencial** Signigica que se debe recuperar todos los registros de un determinado archivo almacenado. 
* **CODASYL** (COnference On DAta SYstems) Empresa que desarrolló COBOL en los 60.
* **DBTG** Subgrupo de CODASYL que introdujo un lenguaje de descripción de datos y otro de definición de datos en el 69.
* **SQL** es un lenguaje de dominio específico utilizado en programación, diseñado para administrar, y recuperar información de SGBD. Apareció en 1974.
* **Ingres** Sistema de bases de datos basado en el modelo relacional por la Universidad de Berkeley. Años 80.
* **Calculo relacional** Lenguaje de consulta que describe la respuesta deseada sobre una base de datos sin especificar como obtenerla.
* **Consultas recursivas** Consulta en la que el servidor consulta al enviador.
* **Modelo semántico** Modelo de datos en el que se describe el significado de sus instancias. Es una abstracción que define como los símbolos almacenados se relacionan con el mundo real. Tomó gran intereś a finales de los setenta.
* **Base de datos orientada a objetos** La información se representa mediante objetos como los presentes en la programación orientada a objetos. Finales de los 60.
* **Base de datos multimedia** Almacenan además de texto, información de Audio y Vídeo, permitiendo su manipulación y recuperació.
* **Base de datos XML** 
* Una base de datos XML constituye un sistema software que da persistencia a datos almacenados en formato XML. Estos datos pueden ser interrogados, exportados y serializados.
* **Base de datos móviles** Es una Base de datos donde los usuarios pueden acceder a la información lejos de donde se encuentra almacenada la base de datos, se hace utilizando una conexión inalámbrica
* **Minería de Datos** es un campo de la estadística y las ciencias de la computación referido al proceso que intenta descubrir patrones en grandes volúmenes de conjuntos de datos. Finales de los 80.