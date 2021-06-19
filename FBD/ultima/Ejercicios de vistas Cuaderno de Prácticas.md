### Ejercicios de vistas Cuaderno de Prácticas

###### Salvador Romero Cortés

****

**4.1 Crear una vista con los proveedores de Londres. ¿Qué sucede si insertamos en dicha vista la tupla ('S7','Jose Suarez',3,'Granada')?**

La creamos con 

```sql
create view ProveedoresLondres AS select * from proveedor where ciudad='Londres';
```

Insertamos los datos con

```sql
insert into ProveedoresLondres values ('S7', 'Jose Suarez',3, 'Granada');
```

Tenemos el siguiente error:

```
Error que empieza en la línea: 3 del comando :
insert into ProveedoresLondres values ('S7', 'Jose Suarez',3, 'Granada')
Informe de error -
ORA-01722: número no válido
```

Sin embargo, si ahora insertamos los valores en el orden que tenemos en la vista:

```sql
insert into ProveedoresLondres values ('S7', 3, 'Granada', 'Jose Suarez');
```

Salida:

```
1 fila insertadas.
```

Sin embargo, a la hora de obtener los datos vemos que no aparece:

```sql
select * from ProveedoresLondres;
```

Salida:

```
COD     STATUS CIUDAD          NOMPRO                        
--- ---------- --------------- ------------------------------
S2           1 Londres         Manuel Vidal                  
```

**4.2 Crear una vista con los nombres de los proveedores y sus ciudades. Inserta sobre ella una fila y explica cuál es el problema que se plantea. ¿Habría problemas de actualización? **

La creamos con:

```sql
create view ProveedoresCiudades as select nompro, ciudad from proveedor;
```

Insertamos una fila:

```sql
insert into ProveedoresCiudades values ('Londres', 'Juan José Estrella');
```

Pero no podemos, porque no podremos poner a nulo codpro

```
Error que empieza en la línea: 4 del comando :
insert into ProveedoresCiudades values ('Londres', 'Juan José Estrella')
Informe de error -
ORA-01400: no se puede realizar una inserción NULL en ("X6752695"."PROVEEDOR"."CODPRO")
```

**4.3 Crear una vista donde aparezcan el código de proveedor, el nombre de proveedor y el código del proyecto tales que la pieza suministrada sea gris. Sobre esta vista realiza alguna consulta y enumera todos los motivos por los que sería imposible realizar una inserción.**

Creamos la vista:

```sql
create view codigosProveedorProyectoGris as
select distinct proveedor.codpro, nompro, proyecto.codpj from proveedor,pieza,proyecto,ventas where pieza.color='Gris' and ventas.codpro = proveedor.codpro and ventas.codpj=proyecto.codpj and pieza.codpie = ventas.codpie;
```

Hacemos una consulta

```sql
select * from codigosProveedorProyectoGris where codpro='S4';
```

Salida:

```
COD NOMPRO                         COD
--- ------------------------------ ---
S4  Pedro Sanchez                  J3 
```

Sin embargo, no podremos insertar ninguna fila nueva:

```sql
insert into codigosproveedorproyectogris values('J6','S6','Juan Joestrella');
```

Salida:

```
Informe de error -
Error SQL: ORA-01732: operación de manipulación de datos no válida en esta vista
01732. 00000 -  "data manipulation operation not legal on this view"
*Cause:    
*Action:
```

Debido a que se obtiene a partir del producto cartesiano de varias tablas, no sabría donde se correspondería realmente la nueva tupla. Además en caso de que no hubiera problemas con eso, no se podría poner a nulo codpie, por ejemplo, en la tabla pieza.

**4.4 Ver la descripción de la vista del catálogo USER_TABLES.**

Lo hacemos con 

```sql
describe USER_TABLES;
```

Salida:

```
Nombre                    ¿Nulo?   Tipo          
------------------------- -------- ------------- 
TABLE_NAME                NOT NULL VARCHAR2(128) 
TABLESPACE_NAME                    VARCHAR2(30)  
CLUSTER_NAME                       VARCHAR2(128) 
IOT_NAME                           VARCHAR2(128) 
STATUS                             VARCHAR2(8)   
PCT_FREE                           NUMBER        
PCT_USED                           NUMBER        
INI_TRANS                          NUMBER        
MAX_TRANS                          NUMBER        
INITIAL_EXTENT                     NUMBER        
NEXT_EXTENT                        NUMBER        
MIN_EXTENTS                        NUMBER        
MAX_EXTENTS                        NUMBER        
PCT_INCREASE                       NUMBER        
FREELISTS                          NUMBER        
FREELIST_GROUPS                    NUMBER        
LOGGING                            VARCHAR2(3)   
BACKED_UP                          VARCHAR2(1)   
NUM_ROWS                           NUMBER        
BLOCKS                             NUMBER        
EMPTY_BLOCKS                       NUMBER        
AVG_SPACE                          NUMBER        
CHAIN_CNT                          NUMBER        
AVG_ROW_LEN                        NUMBER        
AVG_SPACE_FREELIST_BLOCKS          NUMBER        
NUM_FREELIST_BLOCKS                NUMBER        
DEGREE                             VARCHAR2(10)  
INSTANCES                          VARCHAR2(10)  
CACHE                              VARCHAR2(5)   
TABLE_LOCK                         VARCHAR2(8)   
SAMPLE_SIZE                        NUMBER        
LAST_ANALYZED                      DATE          
PARTITIONED                        VARCHAR2(3)   
IOT_TYPE                           VARCHAR2(12)  
TEMPORARY                          VARCHAR2(1)   
SECONDARY                          VARCHAR2(1)   
NESTED                             VARCHAR2(3)   
BUFFER_POOL                        VARCHAR2(7)   
FLASH_CACHE                        VARCHAR2(7)   
CELL_FLASH_CACHE                   VARCHAR2(7)   
ROW_MOVEMENT                       VARCHAR2(8)   
GLOBAL_STATS                       VARCHAR2(3)   
USER_STATS                         VARCHAR2(3)   
DURATION                           VARCHAR2(15)  
SKIP_CORRUPT                       VARCHAR2(8)   
MONITORING                         VARCHAR2(3)   
CLUSTER_OWNER                      VARCHAR2(128) 
DEPENDENCIES                       VARCHAR2(8)   
COMPRESSION                        VARCHAR2(8)   
COMPRESS_FOR                       VARCHAR2(30)  
DROPPED                            VARCHAR2(3)   
READ_ONLY                          VARCHAR2(3)   
SEGMENT_CREATED                    VARCHAR2(3)   
RESULT_CACHE                       VARCHAR2(7)   
CLUSTERING                         VARCHAR2(3)   
ACTIVITY_TRACKING                  VARCHAR2(23)  
DML_TIMESTAMP                      VARCHAR2(25)  
HAS_IDENTITY                       VARCHAR2(3)   
CONTAINER_DATA                     VARCHAR2(3)   
INMEMORY                           VARCHAR2(8)   
INMEMORY_PRIORITY                  VARCHAR2(8)   
INMEMORY_DISTRIBUTE                VARCHAR2(15)  
INMEMORY_COMPRESSION               VARCHAR2(17)  
INMEMORY_DUPLICATE                 VARCHAR2(13)  
```

