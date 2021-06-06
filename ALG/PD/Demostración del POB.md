### Demostración del POB

Partimos de una secuencia de $x_1, x_2, x_3 ... x_n $ que representa las decisiones de asignar los recursos de manera que $x_i$ muestra el número de recursos que se le asignan al proyecto $i$ . Definimos esta secuencia como la solución óptima con n proyectos y r recursos. De esta manera, la secuencia cumple:

* $\sum_1^n{x_i} \le r$
* $\sum_1^n{N(i,x_i)}$ es máximo. Siendo $N(i,x_i)$ el beneficio obtenido con la decisión $x_i$ ; esto es asignar los $x_i$ recursos de esa decisión al proyecto $i$ .

Vamos a demostrar por contradicción que la subsecuencia $x_1, x_2, x_3, ... x_{n-1}$ es óptima para un subproblema con $n-1$ proyectos y $r-k$ recursos.

Si la subsecuencia $x$ no fuera óptima existiría una subsecuencia $y$ que sí sería la óptima para $n-1$ proyectos. De esta manera:

* $\sum_1^{n-1}{y_i} \le r -k$
* $\sum_1^{n-1}N(i,y_i) > \sum_1^{n-1}{N(i,x_i)}$

Pero entonces, haciendo $y_n = x_n$ tenemos que:

* $\sum_1^{n-1}{y_i} + k \le r$

* $(\sum_1^{n-1}N(i,y_i)) + N(n,y_n) > (\sum_1^{n-1}{N(i,x_i)}) + N(n,x_n)$

  Con esto último llegamos a una contradicción con la hipótesis planteada, puesto que habríamos encontrado una sucesión $y_1, y_2, y_3, ... y_n$ que sería mejor que la que hemos definido como óptima.





