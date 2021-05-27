### Ejercicios Cuadernillo 

###### Salvador Romero Cortés

---

**3.60 Muestra la información disponible acerca de los encuentros de la liga**

```sql
select * from encuentros;
```

Salida:

```
EQ1 EQ2 FECHA          RES1       RES2
--- --- -------- ---------- ----------
CAL VAL 23/10/11         72         82
UNI VAL 26/02/12         58         68
RMA VAL 04/11/11         81         64
RMA FCB 04/01/12         78         74
UNI RMA 13/11/11         80         96
CAL FCB 18/12/11         71         60
FCB UNI 11/12/11         72         62
FCB VAL 24/05/12         84         57
RMA CAL 22/01/12         84         73
UNI CAL 26/11/11         79         66
REG BIZ 29/09/12         73         89

EQ1 EQ2 FECHA          RES1       RES2
--- --- -------- ---------- ----------
BLR VLB 01/10/12         78        111
REG BLR 09/10/12        101         89
BIZ VLB 12/10/12         87         99
VLB REG 15/10/12        120         80
BLR BIZ 18/10/12        110         99
REG VLB 29/10/12         91         99
BIZ BLR 01/11/12         97         89
BIZ REG 07/11/12         79         88
VLB BLR 12/11/12         71         88
```



**3.61 Muestra los nombres de los equipos y de los jugadores ordenados alfabéticamente.**

```sql
select code,nombrej from jugadores order by nombrej;
```

Salida:

```
COD NOMBREJ                       
--- ------------------------------
UNI Alberto Diaz                  
VAL Alberto Perez                 
CAL Andres Nocioni                
RMA Ante Tomic                    
UNI Berni Rodriguez               
FCB Boniface Ndong                
RMA Carlos Suarez                 
BLR Doellman, Justin              
BLR Dubljevic, Bojan              
CAL F. San Emeterio               
BLR Faverani, Vitor               

COD NOMBREJ                       
--- ------------------------------
RMA Felipe Reyes                  
FCB Fran Vazquez                  
BIZ Hamilton, Lamont              
BLR Hanley, Will                  
VLB Hrycaniuk, Adam               
REG Huertas, Marcelinho           
REG Jasikeviius, Arnas            
REG Jawai, Nathan                 
FCB Joe Ingles                    
UNI Joel Freeland                 
UNI Jorge Garbajosa               

COD NOMBREJ                       
--- ------------------------------
FCB Juan Carlos Navarro           
VAL Juanlu Navarro                
VLB Kelati, Thomas                
REG Lorbek, Eraem                 
UNI Luka Zoric                    
BLR Markovick, Stefan             
VLB Martinez, Rafa                
CAL Pablo Prigioni                
CAL Pau Ribas                     
VLB Pietrus, Florent              
BIZ Pilepic, Fran                 

COD NOMBREJ                       
--- ------------------------------
BIZ Rakovich, Milovan             
VLB Robinson, Jason               
VAL Rodrigo San Miguel            
RMA Sergio Llull                  
RMA Sergio Rodriguez              
VAL Taquan Dean                   
REG Tomic, Ante                   
CAL Unai Calbarro                 
BIZ Vasileiadis, Kostas           
VAL Victor Claver                 
FCB Victor Sada                   

COD NOMBREJ                       
--- ------------------------------
BIZ Zisis, Nikolaos          
```

**3.62 Muestra los jugadores que no tienen ninguna falta.**

```sql
select nombrej from jugadores natural join (select codj from faltas f where f.num=0);
```

Salida:

```
no se ha seleccionado ninguna fila
```

**3.63 Muestra los compañeros de equipo del jugador que tiene por código x (codJ='x) y donde x es uno elegido por ti.'**

He elegido x=B5

```sql
select nombrej from jugadores where code=(select code from jugadores where codj='B5') and codj!='B5';
```

Salida:

```
NOMBREJ                       
------------------------------
Carlos Suarez                 
Felipe Reyes                  
Sergio Rodriguez              
Sergio Llull     
```

**3.64 Muestra los jugadores y la localidad donde juegan (la de sus equipos).**

```sql
select j.nombrej, e.localidad from equipo e, jugadores j where e.code=j.code;
```

Salida:

```
NOMBREJ                        LOCALIDAD                     
------------------------------ ------------------------------
Pau Ribas                      Vitoria                       
F. San Emeterio                Vitoria                       
Unai Calbarro                  Vitoria                       
Andres Nocioni                 Vitoria                       
Pablo Prigioni                 Vitoria                       
Carlos Suarez                  Madrid                        
Felipe Reyes                   Madrid                        
Sergio Rodriguez               Madrid                        
Sergio Llull                   Madrid                        
Ante Tomic                     Madrid                        
Victor Sada                    Barcelona                     

NOMBREJ                        LOCALIDAD                     
------------------------------ ------------------------------
Juan Carlos Navarro            Barcelona                     
Fran Vazquez                   Barcelona                     
Joe Ingles                     Barcelona                     
Boniface Ndong                 Barcelona                     
Berni Rodriguez                Malaga                        
Jorge Garbajosa                Malaga                        
Luka Zoric                     Malaga                        
Alberto Diaz                   Malaga                        
Joel Freeland                  Malaga                        
Rodrigo San Miguel             Valencia Basket               
Victor Claver                  Valencia Basket               

NOMBREJ                        LOCALIDAD                     
------------------------------ ------------------------------
Alberto Perez                  Valencia Basket               
Taquan Dean                    Valencia Basket               
Juanlu Navarro                 Valencia Basket               
Huertas, Marcelinho            Barcelona                     
Jawai, Nathan                  Barcelona                     
Lorbek, Eraem                  Barcelona                     
Tomic, Ante                    Barcelona                     
Jasikeviius, Arnas             Barcelona                     
Zisis, Nikolaos                Bilbao                        
Rakovich, Milovan              Bilbao                        
Pilepic, Fran                  Bilbao                        

NOMBREJ                        LOCALIDAD                     
------------------------------ ------------------------------
Hamilton, Lamont               Bilbao                        
Vasileiadis, Kostas            Bilbao                        
Faverani, Vitor                Valladolid                    
Markovick, Stefan              Valladolid                    
Doellman, Justin               Valladolid                    
Dubljevic, Bojan               Valladolid                    
Hanley, Will                   Valladolid                    
Pietrus, Florent               Valencia                      
Kelati, Thomas                 Valencia                      
Robinson, Jason                Valencia                      
Hrycaniuk, Adam                Valencia                      

NOMBREJ                        LOCALIDAD                     
------------------------------ ------------------------------
Martinez, Rafa                 Valencia                      
```

