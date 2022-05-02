#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Tarea{
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo * Siguiente;
}typedef Nodo;

Nodo * CrearListaVacia();
Nodo * CrearNodo(int ID, char * DescripcionAux, int DuracionAux);
void CargarLista(Nodo ** Lista, int CantidadTareas);
void InsertarAlInicio(Nodo ** Lista, int ID, char * DescripcionAux, int DuracionAux);
void InsertarAlFinal(Nodo ** Lista, int ID, char * DescripcionAux, int DuracionAux);
void MostrarLista(Nodo * Lista);
void MostrarUnaTarea(Tarea UnaTarea);
void MoverTareas(Nodo ** ListaPendientes, Nodo ** ListaRealizadas);
Nodo * BuscarTareaID(Nodo * Lista, int IdBuscado);
Nodo * BuscarTareaPalabra(Nodo * Lista, char * PalabraClave);
//void EliminarTareaEspecifica(Nodo * Lista, int ID); FALTA ARREGLAR ESTA FUNCION

void main()
{
    srand(time(NULL));
    Nodo * ListaPendientes, * ListaRealizadas;
    int CantidadTareas;
    
    ListaPendientes = CrearListaVacia();
    ListaRealizadas = CrearListaVacia();

    printf("===> Ingrese la cantidad de tareas:\n");
    scanf("%d", &CantidadTareas);
    
    printf("\n");

    printf("===> Cargar la ListaPendientes con tareas:\n");
    CargarLista(&ListaPendientes, CantidadTareas);

    printf("\n");

    printf("===>ListaPendientes cargada:\n");
    MostrarLista(ListaPendientes);

    printf("--------------------------------------\n");

    //Busco las tareas solo en ListaPendientes
    int IdBuscado;
    printf("===> Ingrese el numero de ID de la tarea a buscar (del 1 al %d):\n",CantidadTareas);
    scanf("%d",&IdBuscado);
    Nodo * NodoAux = BuscarTareaID(ListaPendientes, IdBuscado);
    printf("Tarea buscada:\n");
    MostrarUnaTarea(NodoAux->T);
    
    printf("\n");

    char PalabraClave[20];
    puts("===> Ingrese la palabra clave de la tarea a buscar:");
    fflush(stdin);
    gets(PalabraClave);
    Nodo * NodoAux2 = BuscarTareaPalabra(ListaPendientes, PalabraClave);
    printf("Tarea buscada:\n");
    MostrarUnaTarea(NodoAux2->T);

    printf("--------------------------------------\n");

    printf("===> Verificar si las tareas de ListaPendientes fueron realizadas:\n");
    MoverTareas(&ListaPendientes, &ListaRealizadas);

    printf("\n");
    
    printf("===> Tareas que fueron realizadas:\n");
    MostrarLista(ListaRealizadas);

    printf("\n");

    printf("===> Tareas que quedaron pendientes:\n");
    MostrarLista(ListaPendientes);

    free(NodoAux->T.Descripcion);
    free(NodoAux);
    free(NodoAux2->T.Descripcion);
    free(NodoAux2);
    free(ListaPendientes->T.Descripcion);
    free(ListaPendientes);
    free(ListaRealizadas->T.Descripcion);
    free(ListaRealizadas);
}

Nodo * CrearListaVacia()
{
    return NULL;
}

Nodo * CrearNodo(int ID, char * DescripcionAux, int DuracionAux)
{   
    Nodo * NuevoNodo;
    NuevoNodo = (Nodo *) malloc(sizeof(Nodo));
    
    // cargo los datos de la nueva tarea
    NuevoNodo->T.TareaID = ID;
    NuevoNodo->T.Descripcion = DescripcionAux;
    NuevoNodo->T.Duracion = DuracionAux;

    NuevoNodo->Siguiente = NULL;
    return NuevoNodo;
}

void CargarLista(Nodo ** Lista, int CantidadTareas)
{
    char * Buff = (char *) malloc(100);

    for (int i = 0; i < CantidadTareas; i++)
    {
        printf("Ingrese la descripcion de la tarea %d:\n", i+1);
        fflush(stdin);
        gets(Buff);
        char * DescripcionAux = (char *) malloc(strlen(Buff)+1);
        strcpy(DescripcionAux, Buff);

        InsertarAlFinal(Lista, i+1, DescripcionAux, 10+(rand()%91));
    }

    free(Buff);
}

void InsertarAlInicio(Nodo ** Lista, int ID, char * DescripcionAux, int DuracionAux)
{
    Nodo * NuevoNodo;
    NuevoNodo = CrearNodo(ID, DescripcionAux, DuracionAux);
    NuevoNodo->Siguiente = *Lista;
    *Lista = NuevoNodo;
}

void InsertarAlFinal(Nodo ** Lista, int ID, char * DescripcionAux, int DuracionAux)
{   
    Nodo * NuevoNodo;
    NuevoNodo = CrearNodo(ID, DescripcionAux, DuracionAux);
    
    if (*Lista != NULL)
    {
        Nodo * aux;
        aux = *Lista;

        while (aux->Siguiente) // aux->Siguiente != NULL
        {
            aux = aux->Siguiente;
        }
        aux->Siguiente = NuevoNodo;
    }
    else
    {
        NuevoNodo->Siguiente = *Lista;
        *Lista = NuevoNodo;
    }
}

void MostrarLista(Nodo * Lista)
{  
    if (Lista != NULL)
    {
        while (Lista != NULL)
        {
            MostrarUnaTarea(Lista->T);
            Lista = Lista->Siguiente;
        }
    }
    else
    {
        printf("La lista no tiene tareas\n");
    }
}

void MostrarUnaTarea(Tarea UnaTarea)
{
    printf("TareaID: %d\n", UnaTarea.TareaID);
    printf("Descripcion: %s\n", UnaTarea.Descripcion);
    printf("Duracion: %d\n", UnaTarea.Duracion);
    printf("\n");
}

void MoverTareas(Nodo ** ListaPendientes, Nodo ** ListaRealizadas)
{
    Nodo * AuxPendientes = *ListaPendientes;
    int opcion;
    
    while (AuxPendientes) // TareaAux != NULL
    {
        opcion = 0;

        MostrarUnaTarea(AuxPendientes->T);

        printf("La tarea fue realizada? (1: SI, 0: NO):\n");
        scanf("%d", &opcion);
        
        printf("------------------------\n");

        if (opcion == 1) 
        {   
            InsertarAlFinal(ListaRealizadas, AuxPendientes->T.TareaID, AuxPendientes->T.Descripcion, AuxPendientes->T.Duracion);
            //EliminarTareaEspecifica(*ListaPendientes, AuxPendientes->T.TareaID);
            AuxPendientes = AuxPendientes->Siguiente;
        }
        else
        {
            AuxPendientes = AuxPendientes->Siguiente;
        }    
    }
}

Nodo * BuscarTareaID(Nodo * Lista, int IdBuscado)
{
    Nodo * Aux = Lista;

    while (Aux && (Aux->T.TareaID != IdBuscado))
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

Nodo * BuscarTareaPalabra(Nodo * Lista, char * PalabraClave)
{
    Nodo * Aux = Lista;

    while (Aux && !(strstr(Aux->T.Descripcion, PalabraClave)))
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}


/* FALTA ARREGLAR ESTA FUNCION
void EliminarTareaEspecifica(Nodo * Lista, int ID)
{   
    int contador = 0;
    Nodo * Aux = Lista;
    Nodo * Anterior;

    while (contador < ID && Aux)
    {
        Anterior = Aux;
        Aux = Aux->Siguiente;
        contador++;
    }
    
    if (!Aux)
    {
        Anterior->Siguiente = Aux->Siguiente;
        free(Aux);
    }
}
*/




