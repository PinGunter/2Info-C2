### Ejercicios Cuaderno 3.1 - 3.11

###### Salvador Romero Cortés

---

**Ejercicio 3.1**

```sql
select ciudad from proyecto;
```

Salida:

```
CIUDAD         
---------------
Londres
Londres
Paris
Roma
```

Por tanto, no está conforme a lo que se obtiene en el AR, puesto que la proyección no incluye tuplas duplicadas o redundantes.

**Ejercicio 3.2**

```sql
select distinct codpro, codpie, codpj from ventas;
```

Salida:

 ```
 COD COD COD
 --- --- ---
 S4  P1  J3 
 S4  P2  J3 
 S4  P3  J1 
 S4  P5  J1 
 S5  P1  J4 
 S5  P3  J2 
 S5  P3  J3 
 ```

Es necesario usar `DISTINCT`porque la proyección no duplica tuplas.

**Ejercicio 3.3**

```sql
select distinct * from pieza where (color='Gris' or color='Rojo') and ciudad='Madrid';
```

Salida:

```
COD NOMPIE     COLOR            PESO CIUDAD         
--- ---------- ---------- ---------- ---------------
P1  Tuerca     Gris              2,5 Madrid        
```

**Ejercicio 3.4**

```sql
select * from ventas where cantidad>=200 and cantidad<=300;
```

Salida:

```
COD COD COD   CANTIDAD FECHA   
--- --- --- ---------- --------
S1  P2  J1         200 26/07/18
S1  P4  J3         250 13/03/17
S1  P4  J4         290 13/03/17
```

**Ejercicio 3.5**

```sql
select * from pieza where nompie like '%_ornillo%';
```

Salida:

```
COD NOMPIE     COLOR            PESO CIUDAD         
--- ---------- ---------- ---------- ---------------
P2  Tornillo   Rojo             1,25 Paris          
```

**Ejercicio 3.6**

```sql
select table_name from ALL_TABLES where TABLE_NAME like '%ventas';
```

Salida:

```
no se ha seleccionado ninguna fila
```

Efectivamente, a pesar de existir la tabla ventas, no se selecciona ninguna.

**Ejercicio 3.7**

```sql
(select distinct ciudad from proveedor where status>2) INTERSECT (select distinct ciudad from pieza where codpie != 'P1');
```

Salida:

```
CIUDAD         
---------------
Lisboa
Paris
Roma
```

**Ejercicio 3.8**

```sql
(select distinct codpj from ventas where codpro='S1') MINUS (select distinct codpj from ventas where codpro!='S1');
```

Salida:

```
no se ha seleccionado ninguna fila
```

Seleccionamos todas las tablas con proveedor S1 y luego le quitamos las que tengan otro distinto a este. Simplemente coincide que no hay ninguna así.

**Ejercicio 3.9**

```sql
(select ciudad from proveedor) UNION (select ciudad from pieza) UNION (select ciudad from proyecto);
```

Salida:

```
CIUDAD         
---------------
Lisboa
Londres
Madrid
Paris
Roma
```

**Ejercicio 3.10**

```sql
(select ciudad from proveedor) UNION ALL (select ciudad from pieza) UNION ALL (select ciudad from proyecto);
```

Salida:

```
CIUDAD         
---------------
Madrid
Londres
Lisboa
Paris
Roma
Madrid
Paris
Londres
Lisboa
Roma
Londres

CIUDAD         
---------------
Londres
Paris
Roma

14 filas seleccionadas.
```

**Ejercicio 3.11**

```sql
select distinct * from ventas,proveedor;
```

Salida:

```
COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S1  P1  J1         150 22/09/20 S1           2 Madrid          Jose Fernandez                
S1  P1  J2         100 11/05/19 S1           2 Madrid          Jose Fernandez                
S1  P1  J3         500 11/05/19 S1           2 Madrid          Jose Fernandez                
S1  P2  J1         200 26/07/18 S1           2 Madrid          Jose Fernandez                
S4  P2  J3        1700 04/12/19 S1           2 Madrid          Jose Fernandez                
S1  P3  J1         800 26/07/18 S1           2 Madrid          Jose Fernandez                
S5  P3  J2          30 26/01/21 S1           2 Madrid          Jose Fernandez                
S1  P4  J1          10 26/07/18 S1           2 Madrid          Jose Fernandez                
S1  P4  J3         250 13/03/17 S1           2 Madrid          Jose Fernandez                
S3  P2  J1         190 20/04/21 S1           2 Madrid          Jose Fernandez                
S3  P5  J3          20 20/04/21 S1           2 Madrid          Jose Fernandez                

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S4  P5  J1          15 17/04/21 S1           2 Madrid          Jose Fernandez                
S4  P3  J1         100 17/04/21 S1           2 Madrid          Jose Fernandez                
S4  P1  J3        1500 01/02/20 S1           2 Madrid          Jose Fernandez                
S1  P4  J4         290 13/03/17 S1           2 Madrid          Jose Fernandez                
S1  P2  J4         175 13/03/17 S1           2 Madrid          Jose Fernandez                
S5  P1  J4         400 26/01/21 S1           2 Madrid          Jose Fernandez                
S5  P3  J3         400 26/01/21 S1           2 Madrid          Jose Fernandez                
S1  P1  J1         150 22/09/20 S2           1 Londres         Manuel Vidal                  
S1  P1  J2         100 11/05/19 S2           1 Londres         Manuel Vidal                  
S1  P1  J3         500 11/05/19 S2           1 Londres         Manuel Vidal                  
S1  P2  J1         200 26/07/18 S2           1 Londres         Manuel Vidal                  

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S4  P2  J3        1700 04/12/19 S2           1 Londres         Manuel Vidal                  
S1  P3  J1         800 26/07/18 S2           1 Londres         Manuel Vidal                  
S5  P3  J2          30 26/01/21 S2           1 Londres         Manuel Vidal                  
S1  P4  J1          10 26/07/18 S2           1 Londres         Manuel Vidal                  
S1  P4  J3         250 13/03/17 S2           1 Londres         Manuel Vidal                  
S3  P2  J1         190 20/04/21 S2           1 Londres         Manuel Vidal                  
S3  P5  J3          20 20/04/21 S2           1 Londres         Manuel Vidal                  
S4  P5  J1          15 17/04/21 S2           1 Londres         Manuel Vidal                  
S4  P3  J1         100 17/04/21 S2           1 Londres         Manuel Vidal                  
S4  P1  J3        1500 01/02/20 S2           1 Londres         Manuel Vidal                  
S1  P4  J4         290 13/03/17 S2           1 Londres         Manuel Vidal                  

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S1  P2  J4         175 13/03/17 S2           1 Londres         Manuel Vidal                  
S5  P1  J4         400 26/01/21 S2           1 Londres         Manuel Vidal                  
S5  P3  J3         400 26/01/21 S2           1 Londres         Manuel Vidal                  
S1  P1  J1         150 22/09/20 S3           3 Lisboa          Luisa Gomez                   
S1  P1  J2         100 11/05/19 S3           3 Lisboa          Luisa Gomez                   
S1  P1  J3         500 11/05/19 S3           3 Lisboa          Luisa Gomez                   
S1  P2  J1         200 26/07/18 S3           3 Lisboa          Luisa Gomez                   
S4  P2  J3        1700 04/12/19 S3           3 Lisboa          Luisa Gomez                   
S1  P3  J1         800 26/07/18 S3           3 Lisboa          Luisa Gomez                   
S5  P3  J2          30 26/01/21 S3           3 Lisboa          Luisa Gomez                   
S1  P4  J1          10 26/07/18 S3           3 Lisboa          Luisa Gomez                   

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S1  P4  J3         250 13/03/17 S3           3 Lisboa          Luisa Gomez                   
S3  P2  J1         190 20/04/21 S3           3 Lisboa          Luisa Gomez                   
S3  P5  J3          20 20/04/21 S3           3 Lisboa          Luisa Gomez                   
S4  P5  J1          15 17/04/21 S3           3 Lisboa          Luisa Gomez                   
S4  P3  J1         100 17/04/21 S3           3 Lisboa          Luisa Gomez                   
S4  P1  J3        1500 01/02/20 S3           3 Lisboa          Luisa Gomez                   
S1  P4  J4         290 13/03/17 S3           3 Lisboa          Luisa Gomez                   
S1  P2  J4         175 13/03/17 S3           3 Lisboa          Luisa Gomez                   
S5  P1  J4         400 26/01/21 S3           3 Lisboa          Luisa Gomez                   
S5  P3  J3         400 26/01/21 S3           3 Lisboa          Luisa Gomez                   
S1  P1  J1         150 22/09/20 S4           4 Paris           Pedro Sanchez                 

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S1  P1  J2         100 11/05/19 S4           4 Paris           Pedro Sanchez                 
S1  P1  J3         500 11/05/19 S4           4 Paris           Pedro Sanchez                 
S1  P2  J1         200 26/07/18 S4           4 Paris           Pedro Sanchez                 
S4  P2  J3        1700 04/12/19 S4           4 Paris           Pedro Sanchez                 
S1  P3  J1         800 26/07/18 S4           4 Paris           Pedro Sanchez                 
S5  P3  J2          30 26/01/21 S4           4 Paris           Pedro Sanchez                 
S1  P4  J1          10 26/07/18 S4           4 Paris           Pedro Sanchez                 
S1  P4  J3         250 13/03/17 S4           4 Paris           Pedro Sanchez                 
S3  P2  J1         190 20/04/21 S4           4 Paris           Pedro Sanchez                 
S3  P5  J3          20 20/04/21 S4           4 Paris           Pedro Sanchez                 
S4  P5  J1          15 17/04/21 S4           4 Paris           Pedro Sanchez                 

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S4  P3  J1         100 17/04/21 S4           4 Paris           Pedro Sanchez                 
S4  P1  J3        1500 01/02/20 S4           4 Paris           Pedro Sanchez                 
S1  P4  J4         290 13/03/17 S4           4 Paris           Pedro Sanchez                 
S1  P2  J4         175 13/03/17 S4           4 Paris           Pedro Sanchez                 
S5  P1  J4         400 26/01/21 S4           4 Paris           Pedro Sanchez                 
S5  P3  J3         400 26/01/21 S4           4 Paris           Pedro Sanchez                 
S1  P1  J1         150 22/09/20 S5           5 Roma            Maria Reyes                   
S1  P1  J2         100 11/05/19 S5           5 Roma            Maria Reyes                   
S1  P1  J3         500 11/05/19 S5           5 Roma            Maria Reyes                   
S1  P2  J1         200 26/07/18 S5           5 Roma            Maria Reyes                   
S4  P2  J3        1700 04/12/19 S5           5 Roma            Maria Reyes                   

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S1  P3  J1         800 26/07/18 S5           5 Roma            Maria Reyes                   
S5  P3  J2          30 26/01/21 S5           5 Roma            Maria Reyes                   
S1  P4  J1          10 26/07/18 S5           5 Roma            Maria Reyes                   
S1  P4  J3         250 13/03/17 S5           5 Roma            Maria Reyes                   
S3  P2  J1         190 20/04/21 S5           5 Roma            Maria Reyes                   
S3  P5  J3          20 20/04/21 S5           5 Roma            Maria Reyes                   
S4  P5  J1          15 17/04/21 S5           5 Roma            Maria Reyes                   
S4  P3  J1         100 17/04/21 S5           5 Roma            Maria Reyes                   
S4  P1  J3        1500 01/02/20 S5           5 Roma            Maria Reyes                   
S1  P4  J4         290 13/03/17 S5           5 Roma            Maria Reyes                   
S1  P2  J4         175 13/03/17 S5           5 Roma            Maria Reyes                   

COD COD COD   CANTIDAD FECHA    COD     STATUS CIUDAD          NOMPRO                        
--- --- --- ---------- -------- --- ---------- --------------- ------------------------------
S5  P1  J4         400 26/01/21 S5           5 Roma            Maria Reyes                   
S5  P3  J3         400 26/01/21 S5           5 Roma            Maria Reyes                   

90 filas seleccionadas. 
```

Podemos también usar `COUNT`:

``` sql
select count (*) from ventas,proveedor;
```

Salida:

```
  COUNT(*)
----------
        90
```

