#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>

/*
PASO A PASO PARA ESTE PROGRAMA
DEBO HACER 3 FUNCIONALIDADES.. NUEVA CATEGORIA, ELIMINAR CATEGORIA Y MOSTRAR CATEGORIA.
DEBO DEFINIR Y DECLARAR BIEN LOS STRUCTS QUE UTILIZARE, Y SIMPLEMENTE DEBO USAR LOS TDAS, MAS NO IMPLEMENTARLOS
*/
//NECESITO VER COMO IMPLEMENTAR LA HORA..
typedef struct
{
    char* descripcion;
    char* categoria;
    char* hora;

}tipoTarea;

typedef struct
{
    //usare cadenas dinamicas!
    char* nombreCat;
    //lista que va a contener structs de tipo tarea
    List* tareas;
}tipoCategoria;

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
  //formato
  printf("Ingrese un nombre para su categoria: ");
  //guardamos en el struct
  scanf("%15s", nuevaCategoria->nombreCat);
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
  while(1)
  {
        if(strcmp(actual->nombreCat,buscado) == 0)
        {
          list_popCurrent(categorias);
          printf("se ha eliminado la categoria %s\n",buscado);
          return;
        }
        actual= (tipoCategoria *) list_next(categorias);
  }
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
  if(list_first(categorias) == NULL) printf("La lista esta vacía, seleccione otra opcion\n");
  else
  {
      eliminarCat(categorias);
  }
  
}

void mostrar_categorias(List *categorias) {
  // Mostrar categorías
  printf("Categorías:\n");
  // Aquí implementarías la lógica para mostrar las categorías
  if(list_first(categorias) == NULL) printf("La lista esta vacía, seleccione otra opcion\n");
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

int main() {
  char opcion;
  //LISTA DE CATEGORIAS YA INICIALIZADA
  List *categorias = list_create(); // Lista para almacenar categorías

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
      // Lógica para registrar un paciente
      break;
    case '5':
      // Lógica para atender al siguiente paciente
      break;
    case '6':
      // Lógica para mostrar el tablero general
      break;
    case '7':
      // Lógica para filtrar por categoría
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
