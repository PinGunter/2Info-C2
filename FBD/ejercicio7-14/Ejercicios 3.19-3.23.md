### Ejercicios 3.19-3.23

**Ejercicio 3.19. Mostrar las piezas vendidas por los proveedores de Madrid. (Fragmentando la consulta con ayuda del operador IN.) Compara la solución con la del ejercicio 3.15**

``` sql
select distinct codpie from ventas where codpro in (select codpro from proveedor where ciudad='Madrid');
```

Salida: 

```
COD
---
P3 
P4 
P2 
P1 
```

No hay diferencia con respecto al ejercicio 3.15, que se podría resolver así:

```sql
select distinct codpie from ventas natural join (select codpro from proveedor where ciudad='Madrid');
```

**Ejercicio 3.20 Encuentra los proyectos que están en una ciudad donde se fabrica alguna pieza.**

```sql
select * from proyecto natural join (select ciudad from pieza);
```

Salida:

```
CIUDAD          COD NOMPJ               
--------------- --- --------------------
Paris           J3  Proyecto 3          
Londres         J2  Proyecto 2          
Londres         J1  Proyecto 1          
Roma            J4  Proyecto 4          
```

**Ejercicio 3.21 Encuentra los códigos de aquellos proyectos que no utilizan ninguna pieza roja que esté suministrada por un proveedor de Londres.**

```sql
select codpj from ventas minus select distinct ventas.codpj from ventas, pieza, proveedor where ventas.codpie = pieza.codpie and proveedor.codpro = ventas.codpro and pieza.color = 'Rojo' and proveedor.ciudad = 'Londres';
```

Salida:

```  
COD
---
J1 
J2 
J3 
J4 
```

**Ejercicio 3.22 Muestra el código de las piezas cuyo peso es mayor que el peso de cualquier 'tornillo'**

```sql
select codpie from pieza where peso < any (select peso from pieza where nompie like 'tornillo%');
```

Salida:

```  
no se ha seleccionado ninguna fila
```

**Ejercicio 3.23 Encuentra las piezas con peso máximo. Compara esta solución con la obtenida en el ejercicio 3.14**

```sql
select codpie from pieza where peso >= all (select peso from pieza);
```

Salida:

``` 
COD
---
P5 
```

Obtenemos el mismo resultado, pero con una sintaxis más sencilla.

