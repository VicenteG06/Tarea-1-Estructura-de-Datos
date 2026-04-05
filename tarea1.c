#include "tdas/list.h"
#include "tdas/queue.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct{
  char nombre_categoria[100];
  List* tareas;
  int cant_tareas;
} categoria;

typedef struct{
  char descripcion[30];
  time_t hora;
  char categoria[30];
} tarea;

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Gestión De Tareas");
  puts("========================================");

  puts("1) Nueva Categoría");
  puts("2) Eliminar Categoría");
  puts("3) Mostrar Categorías");
  puts("4) Registrar Tarea");
  puts("5) Atender Siguiente Tarea");
  puts("6) Visualización del Tablero General");
  puts("7) Filtrado por Categoría");
  puts("8) Salir");
}

void registrar_categorias(List *categorias) {
  printf("Registrar nueva categoría\n");
  // Aquí implementarías la lógica para registrar una nueva categoría
  
  //Se reserva memoria para la nueva categoría 
  categoria* nueva_categoria = (categoria*) malloc(sizeof(categoria)); 
  
  //Se verifica si se reservó memoria correctamente
  if(nueva_categoria == NULL) exit(EXIT_FAILURE);
  
  scanf("%s", nueva_categoria -> nombre_categoria); // El usuario ingresa el nombre de la categoría
  
  nueva_categoria -> tareas = list_create(); //Se crea la lista para las tareas de la categoria
  list_pushBack(categorias, nueva_categoria); //Se ingresa la categoria a la lista categorias
}

// Función para eliminar las tareas en la cola de una categoría deseada

void eliminar_tareas_categoria(Queue* cola_de_tareas, char* categoria){
  List* lista_aux = list_create(); // Lista auxiliar para guardar los elementos de la cola
  
  // Se guardan los elementos de la cola en la lista auxiliar a la vez que se vacia la cola
  while(queue_front(cola_de_tareas) != NULL){
    list_pushFront(lista_aux, queue_remove(cola_de_tareas));
  }
  queue_clean(cola_de_tareas); // Se limpia nuestra cola de tareas
  
  int tamaño_lista_aux = list_size(lista_aux); // El tamaño de la lista auxiliar

  tarea* aux = list_first(lista_aux); // Variable auxiliar para recorrer la lista
  
  //Se rellena la cola nuevamente, pero sin las tareas que son de la categoría eliminada
  for(size_t i = 0; i < tamaño_lista_aux; i++){
    if(strcmp(aux -> categoria, categoria) != 0){
      queue_insert(cola_de_tareas, aux);
    }
    aux = list_next(lista_aux);
  }
  
  list_clean(lista_aux); //Se limpia la lista auxiliar
  free(lista_aux); // Se libera la memoria de nuestra lista auxiliar
  free(aux); //Se libera la memoria de nuestra variable auxiliar
}

void eliminar_categoria(List *categorias, Queue* cola_de_tareas){
  int tamaño_lista = list_size(categorias); // El tamaño de la lista categorias 
  
  if(tamaño_lista == 0){
    printf("NO HAY CATEGORÍAS INGRESADAS.\n"); // Error por si no hay categorías registradas
    return;
  }
  
  printf("Ingrese la categoría a eliminar:\n");
  char categoria_a_eliminar[30];
  scanf("%s", categoria_a_eliminar);
  
  categoria* aux = list_first(categorias); // Auxiliar para recorrer la lista

  // Se recorre la lista en busca de la categoria deseada
  for(size_t i = 0; i < tamaño_lista; i++){
    if(strcmp(aux -> nombre_categoria, categoria_a_eliminar) == 0){
      if(list_first(aux -> tareas) != NULL){
        //Se elimina las tareas de la cola de tareas correspondientes a la categoría
        eliminar_tareas_categoria(cola_de_tareas, categoria_a_eliminar);
      }
      list_popCurrent(categorias); // Se elimina la categoría de la lista
      return;
    }
    aux = list_next(categorias);
  }
  
  printf("LA CATEGORÍA NO EXISTE\n"); //Error por si no se ha eliminado ninguna categoría
}

void mostrar_categorias(List *categorias) {
  int tamaño_lista = list_size(categorias); // El tamaño de la lista de categorías
  
  // Error por si no hay categorías ingresadas.
  if(tamaño_lista == 0){
    printf("NO HAY CATEGORÍAS INGRESADAS.\n");
    return;
  }
  // Mostrar categorías
  printf("Categorías:\n");
  // Aquí implementarías la lógica para mostrar las categorías
  categoria* aux = list_first(categorias); // Auxiliar para recorrer la lista

  // Se recorre la lista de categorías y se imprime el nombre de cada una
  for(size_t i = 0; i < tamaño_lista; i ++){
    printf(" %s\n", aux -> nombre_categoria);
    aux = list_next(categorias);
  }
}

void insertar_tarea_a_lista_categorias(List* categorias, tarea* nueva_tarea){
  int tamaño_lista = list_size(categorias); 
  categoria* aux = list_first(categorias); //Auxiliar para recorrer la lista

  for(size_t i = 0; i < tamaño_lista; i++){
    if(strcmp(nueva_tarea -> categoria, aux -> nombre_categoria) == 0){
      list_pushBack(aux -> tareas, nueva_tarea);
      aux -> cant_tareas ++;
    }
    aux = list_next(categorias);
  }
}

int existe_categoria(List* categorias, char* categoria_tarea){
  categoria* aux = list_first(categorias);
  int tamaño_lista = list_size(categorias);
  
  for(size_t i = 0; i < tamaño_lista; i++){
    if(strcmp(aux -> nombre_categoria, categoria_tarea) == 0) return 1;
    aux = list_next(categorias);
  }
  return 0;
}

void registrar_tarea(List* categorias, Queue* cola_de_tareas){
  tarea* nueva_tarea = (tarea *) malloc(sizeof(tarea));
  printf("Ingrese la tarea:\n");
  scanf(" %s", nueva_tarea -> descripcion);
  
  printf("Ingrese la categoría de la tarea:\n");
  scanf(" %s", nueva_tarea -> categoria);

  //Error por si la categoría de la tarea no existe
  if(existe_categoria(categorias, nueva_tarea -> categoria) == 0){
    printf("NO EXISTE LA CATEGORÍA.\n");
    return;
  }
  
  time(&(nueva_tarea -> hora));

  queue_insert(cola_de_tareas, nueva_tarea);
  
  insertar_tarea_a_lista_categorias(categorias, nueva_tarea);
}

void atender_siguiente(Queue* cola_de_tareas){
  if(queue_front(cola_de_tareas) == NULL){
    printf("NO HAY TAREAS INGRESADAS\n");
    return;
  }
  tarea* tarea_atendida = queue_remove(cola_de_tareas);
  printf("Datos de la tarea atendida: \n");
  printf("DESCRIPCIÓN | CATEGORÍA | FECHA \n");
  printf("%s | %s | %s", tarea_atendida -> descripcion, tarea_atendida -> categoria, ctime(&(tarea_atendida -> hora)));
}
    
void mostrar_tareas(Queue* cola_de_tareas){
  tarea* aux = queue_front(cola_de_tareas);
  if(aux == NULL) {
    printf("NO HAY TAREAS INGRESADAS\n");
    return;
  }
  printf("DESCRIPCIÓN   | CATEGORÍA    | FECHA\n");
  while(aux != NULL){
    if(aux == NULL) return;
    printf("%s| %5s | %s", aux -> descripcion, aux -> categoria, ctime(&(aux -> hora)));
    aux = queue_next(cola_de_tareas); 
  }
}

void mostrar_tareas_por_categoria(List* lista, int tamaño){
  tarea* aux = list_first(lista);
  printf("DESCRIPCIÓN   | CATEGORÍA    | FECHA\n");
  for(size_t i = 0; i < tamaño ; i++){
    printf("%s | %s | %s", aux -> descripcion, aux -> categoria, ctime(&(aux -> hora)));
    aux = list_next(lista);
  }
  
}

void filtrar_por_categoria(List* categorias){
  printf("Ingrese la categoría:\n");
  char categoria_a_filtrar[30];
  scanf("%s", categoria_a_filtrar);

  if(existe_categoria(categorias, categoria_a_filtrar) == 0){
    printf("NO EXISTE LA CATEGORÍA.\n");
    return;
  }

  int tamaño_lista = list_size(categorias);

  categoria* aux = list_first(categorias);
  for(size_t i = 0; i < tamaño_lista; i++){
    if(strcmp(categoria_a_filtrar, aux -> nombre_categoria) == 0){
      int tamaño_lista = aux -> cant_tareas;
      if(tamaño_lista == 0) printf("NO HAY TAREAS CON ESTA CATEGORÍA\n");
      else mostrar_tareas_por_categoria(aux -> tareas, tamaño_lista);
      return; 
    }
    aux = list_next(categorias);
  }
}

int main() {
  char opcion;
  List *categorias = list_create(); // Lista para almacenar categorías
  Queue *cola_de_tareas = queue_create(cola_de_tareas); // Cola para almacenar las tareas
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
      eliminar_categoria(categorias, cola_de_tareas);
      break;
    case '3':
      mostrar_categorias(categorias);
      break;
    case '4':
      // Lógica para registrar una tarea
      registrar_tarea(categorias, cola_de_tareas);
      break;
    case '5':
      // Lógica para atender la siguiente tarea
      atender_siguiente(cola_de_tareas);
      break;
    case '6':
      // Lógica para mostrar el tablero general
      mostrar_tareas(cola_de_tareas);
      break;
    case '7':
      // Lógica para filtrar por categoría
      filtrar_por_categoria(categorias);
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
