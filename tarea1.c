#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//NECESITO VER COMO IMPLEMENTAR LA HORA..
typedef struct
{
    char* descripcion;
    char* categoria;
    struct tm hora;
    
}tipoTarea;

typedef struct
{
    //usare cadenas dinamicas!
    char* nombreCat;
    //conservare solo el nombre de cada categoria..
}tipoCategoria;
/*
typedef struct
{
    List* pendientes;
}tipoPendientes;
*/
//FUNCION LLENAR LISTA O POBLARLA

void llenarLista(List* categorias)
{
  /*
  que es lo que queremos hacer?
  debemos registrar una categoria, por lo que necesitamos un bucle? 
  o algo para poder llenar la lista de categorias ya inicializada
  QUE NECESITAMOS?
  LISTA DE CATEGORIAS-> CONTIENE DATOS TIPOCATEGORIA -> CONTIENEN LISTA DE TAREAS EN CADA POS!
  LA LISTA DE CATEGORIAS YA SE INICIALIZO!
  FALTA POBLAR ESA LISTA CON LA NUEVA CATEGORIA!
  EL PASO A PASO SERA.
  
  DECLARAR EL STRUCT TIPO CATEGORIA, LEER Y GUARDAR EN SU CAMPO EL NOMBRE INGRESADO!
  USAR OPCIONES DE FORMATO? 

  y debo pasar ese struct a la lista de categorias! con un casting?

  el nombre de cada categoria seria el campo con el string!
  */
  //declaraciones y reservas de memoria para el struct y su nombre
  tipoCategoria* nuevaCategoria = (tipoCategoria *)malloc(sizeof(tipoCategoria));
  nuevaCategoria->nombreCat= (char*) malloc(16 * sizeof(char));
  //nuevaCategoria->tareas = list_create();
  //formato
  printf("Ingrese un nombre para su categoria: ");
  //guardamos en el struct
  scanf("%16s", nuevaCategoria->nombreCat);
  //prueba de lo guardado
  printf("nombre guardado: %s\n",nuevaCategoria->nombreCat);
  printf("Su Registro se ha guardado exitosamente!\n");
  list_pushBack(categorias,nuevaCategoria);
}
  
//funcion eliminar categoria
/*
en resumen, lo que debe hacer es a partir de una coincidencia de categoria
recorrer la lista de categorias y en cada pos preguntar si la coincidencia
es igual, si lo es, eliminar el nodo completo! con pop
*/
void eliminarCat(List* categorias)
{
  //PEDIR EL STRING CORRESPONDIENTE
  char *buscado = (char *)malloc(16 * sizeof(char));
  scanf("%15s",buscado);
 //EN UN BUCLE WHILE INDEXAR Y BUSCAR LA COINCIDENCIA
  tipoCategoria* actual= (tipoCategoria *) list_first(categorias);
  while(actual != NULL)
  {
        if(strcmp(actual->nombreCat,buscado) == 0)
        {
          tipoCategoria *aEliminar= (tipoCategoria *)list_popCurrent(categorias);
          free(aEliminar->nombreCat);
          free(aEliminar);
          printf("se ha eliminado la categoria %s\n",buscado);
          return;
        }
        actual= (tipoCategoria *) list_next(categorias);
  }
  if(actual == NULL) printf("La Categoria Ingresada No Existe.\n");
}

void guardarHora(tipoTarea* tarea){
  time_t actual = time(NULL);
  
  //PASAR A LA HORA DE CHILE
  time_t horaChilena = actual - (4 * 3600);
  struct tm *info = gmtime(&horaChilena);
  tarea->hora = *info;
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Planificador dinamico de tareas");
  puts("========================================");

  puts("1) Nueva Categoría");
  puts("2) Eliminar Categoría");
  puts("3) Mostrar Categorías");
  puts("4) Registrar Pendiente");
  puts("5) Atender Siguiente");
  puts("6) Visualización del Tablero General");
  puts("7) Filtrado por Categoría");
  puts("8) Salir");
}

void registrar_categorias(List *categorias) {
  printf("Registrar nueva categoría\n");
  // Aquí implementarías la lógica para registrar una nueva categoría
  llenarLista(categorias);
}

void eliminar_categorias(List* categorias){
  printf("Eliminar una categoria\n");
  if(list_first(categorias) == NULL) printf("La lista de categorias esta vacía, seleccione otra opcion\n");
  else
  {
      eliminarCat(categorias);
  }
  
}

void mostrar_categorias(List *categorias) {
  // Mostrar categorías
  printf("Categorías:\n");
  // Aquí implementarías la lógica para mostrar las categorías
  if(list_first(categorias) == NULL) printf("La lista de categorias esta vacía, seleccione otra opcion\n");
  else
  {
  tipoCategoria* actual= (tipoCategoria *) list_first(categorias);
  
  while(actual != NULL)
  {
        printf("%s\n",actual->nombreCat);    
        actual= (tipoCategoria *) list_next(categorias);
  }
  } 
}

void registrar_pendiente(List *categorias,List *pendientes) {
  /*
  esta funcion lo que hara sera registrar una tarea en funcion del nombre de la categoria a la que le corresponde
  Paso a paso:
  LLENAR EL STRUCT
  1.guardar la descripcion de la tarea
  2.llenar la hora de la categoria
  3.pedimos que ingresen el nombre de la categoria donde asignaremos la tarea
  ASIGNARLO EN LA LISTA DE CATEGORIAS.
  -asignamos el struct a la categoria donde corresponde la tarea.
  */
  //declarar el struct
  tipoTarea* tarea = (tipoTarea *) malloc(sizeof(tipoTarea));
  tarea->categoria= (char *) malloc(16 * sizeof(char));
  printf("Ingrese la categoria de su Tarea\n");
  scanf("%16s",tarea->categoria);
  //PRIMERO VERIFICAMOS QUE HAYA ALGUNA CATEGORIA DISPONIBLE!!
  
  if(list_first(categorias) == NULL) printf("La lista de categorias esta vacía, seleccione otra opcion\n");
  else
  {
  tipoCategoria* actual= (tipoCategoria *) list_first(categorias);
  
  while(actual != NULL)
  {
        if(strcmp(actual->nombreCat,tarea->categoria) == 0)
        {
          //REGISTRAMOS LA CATEGORIA SI HAY UNA COINCIDENCIA!
          tarea->descripcion = (char *) malloc(30 * sizeof(char));
          printf("Ingrese la descripción de su tarea:\n");
          getchar();
          fgets(tarea->descripcion,30,stdin);
          tarea->descripcion[strcspn(tarea->descripcion, "\n")] = '\0';
          //printf("la descripcion es %s\n",tarea->descripcion);
          guardarHora(tarea);
          printf("la hora registrada fue %02d:%02d:%02d\n",tarea->hora.tm_hour,tarea->hora.tm_min,tarea->hora.tm_sec);
          //aqui cambia
          list_pushBack(pendientes,tarea);
          return;
        }
        actual= (tipoCategoria *) list_next(categorias);
  }
  if(actual == NULL) printf("La Categoria Ingresada No Existe.\n");
  }
  /*
  //FIN DE LA VERIFICACION
  tarea->descripcion = (char *) malloc(30 * sizeof(char));
  printf("Ingrese la descripción de su tarea:\n");
  getchar();
  fgets(tarea->descripcion,30,stdin);
  //printf("la descripcion es %s\n",tarea->descripcion);
  guardarHora(tarea);
  printf("la hora registrada fue %02d:%02d:%02d\n",tarea->hora.tm_hour,tarea->hora.tm_min,tarea->hora.tm_sec);
  */
}

void atender_siguiente(List* pendientes){
  //HARE UNA LISTA PARA TODOS LOS PENDIENTES!!!
  
  
  if(list_first(pendientes) == NULL) printf("¡Libre de pendientes!\n");
  else
  {
  //SI NO, ENTRAMOS AQUI!!
  tipoTarea* actual= (tipoTarea *) list_first(pendientes);
  //COMO ELIMINAMOS EL MAS ANTIGUO, NO HAY QUE RECORRER NADA, SOLO UN CURRENT(YA QUE EL ACTUAL YA ES EL FIRST!!
  /*
  printf("Atendiendo: [%s] | Categoría: [%s] | Registrada a las: [",actual->descripcion,actual->categoria);
  printf("%02d:%02d:%02d]\n",actual->hora.tm_hour,actual->hora.tm_min,actual->hora.tm_sec);
  */
  
  printf("Atendiendo: [%s]\n",actual->descripcion);
  printf("Categoría: [%s]\n",actual->categoria);
  printf("Registrada a las: [%02d:%02d:%02d]\n",actual->hora.tm_hour,actual->hora.tm_min,actual->hora.tm_sec);  
  actual= (tipoTarea *) list_popCurrent(pendientes);
  printf("La tarea ha sido atendida!\n");
  free(actual->descripcion);
  free(actual->categoria);
  free(actual);  
  
  }

}


void mostrarTablero(List* pendientes)
{
  tipoTarea* actual= (tipoTarea *) list_first(pendientes);
  
  while(actual != NULL)
  {
        printf("tarea : %s|categoria : %s\n",actual->descripcion,actual->categoria);    
        actual= (tipoTarea *) list_next(pendientes);
  }
}

void mostrarCategoria(List* pendientes)
{
  //PEDIR EL STRING CORRESPONDIENTE
  printf("Elija una categoria para mostrar sus pendientes: ");
  char *buscado = (char *)malloc(16 * sizeof(char));
    scanf("%15s",buscado);
   //EN UN BUCLE WHILE INDEXAR Y BUSCAR LA COINCIDENCIA
    tipoTarea* actual= (tipoTarea *) list_first(pendientes);
    while(actual != NULL)
    {
          if(strcmp(actual->categoria,buscado) == 0)
          {
            printf("%s\n",actual->descripcion);
          }
          actual= (tipoTarea *) list_next(pendientes);
    }
    free(buscado);
}
int main() {
  char opcion;
  //LISTA DE CATEGORIAS YA INICIALIZADA
  List *categorias = list_create(); // Lista para almacenar categorías
  //LISTA DE PENDIENTES YA INICIALIZADA!
  List *pendientes = list_create();
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_categorias(categorias);
      break;
    case '2':
      // Lógica para eliminar una categoría
      eliminar_categorias(categorias);
      break;
    case '3':
      mostrar_categorias(categorias);
      break;
    case '4':
      // Lógica para registrar una tarea
      registrar_pendiente(categorias,pendientes);
      break;
    case '5':
      // Lógica para limpiar la lista
      atender_siguiente(pendientes);
      break;
    case '6':
      // Lógica para mostrar el tablero general
      if(list_first(pendientes) == NULL) printf("No hay pendientes\n");
      else mostrarTablero(pendientes);
      break;
    case '7':
      // Lógica para filtrar por categoría
      if(list_first(categorias) == NULL) printf("No hay Categorias");
      else
      {  
        if(list_first(pendientes) == NULL) printf("No hay pendientes\n");
        else mostrarCategoria(pendientes);
      }
      
      break;
    case '8':
      puts("Saliendo del sistema de gestión de tareas...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '8');

  // Liberar recursos, si es necesario
  list_clean(categorias);

  return 0;
}
