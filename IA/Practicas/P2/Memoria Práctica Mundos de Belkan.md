### Memoria Práctica Mundos de Belkan

###### Salvador Romero Cortés

---

#### Nivel 0

En este nivel tan sólo seguimos los pasos que nos muestra el tutorial, obteniendo un algoritmo que gire a la derecha cuando se topa con un obstáculo. Viene implementado por los profesores.

#### Nivel 1

En este caso se nos pide construir un algoritmo que encuentre el camino más corto entre los dos puntos (inicio y destino). Para ello utilizaremos un algoritmo de búsqueda en anchura.

Puesto que en el nivel 0 teníamos la búsqueda en profundidad, adaptar el código a una búsqueda en anchura es relativamente sencillo.

Para ello sustituimos la estructura de datos utilizada en el nivel 0 (una pila) por una cola. De esta manera realizamos el cambio principal que existe entre la búsqueda por profundidad y en anchura: la primera sigue una organización LIFO en la lista de abiertos mientras que la última una FIFO.

#### Nivel 2

En este nivel se nos pide un algoritmo que encuentre el camino con el coste mínimo, para ello se deberán tener en cuenta las casillas de "bikini" y de "zapatillas".

El primer cambio que realizamos es añadir a la estructura "estado" dos variables booleanas que indiquen si se posee en ese momento alguno de los dos objetos mencionados anteriormente. Esto influirá en la función "comparaEstados" de manera que habrá que añadir la condición de comparación sobre los objetos bikini y zapatillas para saber que estado debe ir antes.

En mi caso, utilizaremos el algoritmo de coste uniforme para lograr el objetivo. Esto implica un cambio de la estructura de datos, pasamos de usar una cola a una cola con prioridad. Esta cola con prioridad está ordenada según el coste de ese nodo.

Para calcular este coste he implementado una función que comprueba la casilla actual para saber si es agua, bosque, zapatillas... De esta manera y dependiendo del siguiente estado podemos calcular el coste de ese movimiento. Este peso o coste se determina cuando obtenemos los hijos de cada nodo.



