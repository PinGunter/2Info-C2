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

En mi caso, utilizaremos el algoritmo de coste uniforme para lograr el objetivo. Esto implica un cambio de la estructura de datos, pasamos de usar una cola a una cola con prioridad. Esta cola con prioridad está ordenada según el coste de ese nodo. Para ello se ha definido un operador "<".

Para calcular el coste he hecho uso de dos funciones, una para determinar el peso actual de esa casilla y otra para comprobar si estamos en una casilla de item (zapatillas o bikini). De esta manera cada vez que generamos los nodos hijos, calculamos sus pesos y si ahora llevan algún objeto.

Para este nivel, el número de nodos en memoria crece muy rápidamente. Esto no es solo importante a la hora del consumo de memoria, sino que también afecta al rendimiento puesto que cada vez que insertemos un elemento en la cola con prioridad, esta se tiene que ordenar. Esta ordenación puede suponer un aumento del tiempo considerable. Para solucionar esto simplemente en cada iteración del algoritmo principal nos encargamos de eliminar todos los nodos que ya estén en cerrados hasta encontrar uno que no esté.

```c++
 while (cerrados.find(current.st) != cerrados.end()){
            abiertos.pop();
            current = abiertos.top();
        }
        cerrados.insert(current.st);
```

#### Nivel 3

En este nivel se nos pide calcular el recorrido óptimo de batería que pase por 3 objetivos distintos. Para ello, tendremos que modificar la manera de detener el bucle principal y tendremos que tener en cuenta el número de objetivos (y cuáles son) a la hora de diferenciar nodos y ordenar.

Entonces, el primer cambio es agregar una lista de estados al estado actual para saber por cuales hemos pasado.

```c++
struct estado {
  int fila;
  int columna;
  int orientacion;
  bool bikini, zapatillas;
  list<estado> objetivos;
};
```

Además debemos modificar ComparaEstados para tener en cuenta los objetivos por los que pasa cada Estado. También he hecho un operador "<" para diferenciar entre Estados, esto se usará para comparar los estados de la lista objetivos. 

Puesto que tenemos que comprobar que pase por objetivos, tengo una función `actualizaObjetivo` para que se compruebe si se ha pasado por algún objetivo, en cuyo caso se elimina de la lista de estado.

Una vez ya tenemos todas estas herramientas, falta actualizar la manera en la que se comprueba el fin de la búsqueda. Ahora se detendrá si algún nodo llega a tener los 3 objetivos.

En este caso también hemos utilizado el bucle mencionado en el nivel 2 para eliminar de memoria los redundantes. Por esta razón era importante desarrollar el operador "<" entre estados y la modificación de ComparaEstados. Sin este bucle, el ejemplo 7 tarda unos 4 segundos. Con esta optimización tarda alrededor de 0.7-0.8 segundos.





