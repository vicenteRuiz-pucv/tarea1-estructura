## Código de Ejemplo (tarea1)
Para ejecutar el ejemplo tarea1.c primero debemos guardar los cambios!
````
gcc tdas/*.c tarea1.c -o tarea1
````

Y luego ejecutar la version actualizada:
````
./tarea1
````

## TDAs

En mi codigo hice un programa que es un planificador de tareas dinamico.

Utilice el tda lista!
Pero emule una cola ya que hice pushbacks, para emular el comportamiento de esta misma.

Para la lista de categorias utilicé una lista, y ademas hice otra lista pero para las tareas pendientes.

Este programa tiene 7 funcionalidades
-1.REGISTRAR UNA NUEVA CATEGORIA.
-2.ELIMINAR CATEGORIA
-3.MOSTRAR CATEGORIA
-4.REGISTRAR PENDIENTE
-5.ATENDER SIGUIENTE
-6.VISUALIZACION DEL TABLERO GENERAL
-7.FILTRADO POR CATEGORIA
-8.SALIR..
1. Esta funcionalidad lo que hace es registrar un nombre de una categoria y se añade a la lista de categorias
2. Esta funcionalidad lo que hace es eliminar una de las categorias ya existentes
3. Esta funcionalidad muestra las categorias existentes de la lista de categorias
4. Esta funcionalidad registra una tarea en funcion de las categorias existentes, registrando una descripcion,la categoria y la hora.
5. Esta funcionalidad atiende y elimina al mas antiguo de la lista de pendientes.
6. Esta funcionalidad muestra la descripcion de todas las tareas pendientes.
7. Esta funcionalidad muestra las tareas de una funcionalidad especifica.

Probablemente hayan errores de manejo de casos.. por no considerar situaciones excepcionales fuera del comportamiento nornal.
