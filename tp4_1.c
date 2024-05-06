#include <stdio.h>

 typedef struct Tarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10– 100
 } Tarea;


 typedef struct Nodo{
    Tarea T;
    struct Nodo * Siguiente;
 } Nodo;

 Nodo * crearNodo(Tarea nuevaTarea);
 void insertarNodo(Nodo ** listaTareas, Nodo * nuevoNodo);
 Nodo * crearLista();
 Nodo * quitarNodo(Nodo ** listaTareas, int id);
 void mostrarLista(Nodo * listaTareas);
 void consultarTareaPorId(Nodo * listaTareas, int id);
 void consultarTareaPorPalabraClave(Nodo * listaTareas, char * palabraClave);

 int main() {
    Nodo * listaTareasPendientes = crearLista();
    int seguir = 1;
    int id = 999;
    while (seguir ==1) {
        id++;
        printf("Está por cargar una nueva tarea pendiente\n");
        Tarea nuevaTarea;
        char * Buffer = (char*)malloc(sizeof(char[50]));
        printf("Ingrese la descripción de la tarea: \n");
        fflush(stdin);
        gets(Buffer);
        char * descripcion = (char*)malloc(sizeof(Buffer)+1);
        strcpy(descripcion,Buffer);
        nuevaTarea.Descripcion = descripcion;
        printf("La descrip es: %s\n", nuevaTarea.Descripcion);
        printf("Ingrese la duración de la tarea entre 10 y 100: \n");
        scanf("%d", &nuevaTarea.Duracion);
        nuevaTarea.TareaID = id;
        insertarNodo(&listaTareasPendientes,crearNodo(nuevaTarea));
        printf("¿Desea seguir cargando tareas?\n");
        printf("Inserte 1 para SI o 0 para NO\n");
        scanf("%d", &seguir);
    }
    Nodo * listaTareasRealizadas = crearLista();
    int idRealizada;
    seguir=1;
    while (seguir == 1) { 
        printf("Escriba el ID de la tarea que ya realizó: \n");
        scanf("%d", &idRealizada);
        insertarNodo(&listaTareasRealizadas, quitarNodo(&listaTareasPendientes, idRealizada));
        printf("¿Desea marcar otra tarea como realizada?\n");
        printf("Inserte 1 para SI o 0 para NO\n");
        scanf("%d", &seguir);
    }
    printf("\nLas tareas que quedaron pendientes son:\n\n");
    mostrarLista(listaTareasPendientes);
    printf("\nLas tareas que fueron realizadas son:\n\n");
    mostrarLista(listaTareasRealizadas);
    consultarTareaPorId(listaTareasPendientes,1000);
    consultarTareaPorId(listaTareasRealizadas,1000);
    consultarTareaPorId(listaTareasPendientes,1001);
    consultarTareaPorId(listaTareasRealizadas,1001);
    consultarTareaPorPalabraClave(listaTareasPendientes,"limpiar");
    consultarTareaPorPalabraClave(listaTareasRealizadas,"limpiar");
    consultarTareaPorPalabraClave(listaTareasPendientes,"ordenar");
    consultarTareaPorPalabraClave(listaTareasRealizadas,"ordenar"); 
 }

 Nodo * crearNodo(Tarea nuevaTarea) {
    Nodo * nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->T = nuevaTarea;
    nuevoNodo->Siguiente = NULL;
    return nuevoNodo;
 }

 void insertarNodo(Nodo ** listaTareas, Nodo * nuevoNodo) {
    nuevoNodo->Siguiente = *listaTareas;
    *listaTareas = nuevoNodo;
 }

 Nodo * crearLista() {
    return NULL;
 }

 Nodo * quitarNodo(Nodo ** listaTareas, int id) {
    Nodo ** Aux = listaTareas;
    while ((*Aux)->Siguiente != NULL && (*Aux)->T.TareaID != id) {
        Aux = &(*Aux)->Siguiente;
    }
    if (*Aux) {
        Nodo * nodoRealizado = *Aux;
        *Aux = (*Aux)->Siguiente;
        nodoRealizado->Siguiente = NULL;
        return nodoRealizado;
    }
 }

 void mostrarLista(Nodo * listaTareas) {
    Nodo * Aux = listaTareas;
    while (Aux)
    {
        printf("ID: %d\n", Aux->T.TareaID);
        printf("Descripción: %s\n", Aux->T.Descripcion);
        printf("Duración: %d\n\n", Aux->T.Duracion);
        Aux = Aux->Siguiente;
    }
 }

 void consultarTareaPorId(Nodo * listaTareas, int id) {
   Nodo * Aux = listaTareas;
   while (Aux && Aux->T.TareaID != id) {
      Aux = Aux->Siguiente;
   }
   if (Aux) {
      printf("La tarea se encuentra en esta lista\n");
      printf("Descripción: %s\n", Aux->T.Descripcion);
      printf("Duración: %d\n", Aux->T.Duracion);
   } else {
      printf("La tarea no se encuentra en esta lista\n");
   }
 }

 void consultarTareaPorPalabraClave(Nodo * listaTareas, char * palabraClave) {
   Nodo * Aux = listaTareas;
   while (Aux && strstr(Aux->T.Descripcion,palabraClave) == NULL ) {
      Aux = Aux->Siguiente;
   }
   if (Aux) {
      printf("La tarea se encuentra en esta lista\n");
      printf("Descripción: %s\n", Aux->T.Descripcion);
      printf("Duración: %d\n", Aux->T.Duracion);
   } else {
      printf("La tarea no se encuentra en esta lista\n");
   }
 }