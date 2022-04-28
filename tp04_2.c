#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef Tarea;

void cargarTareasPendientes(Tarea** TPendientes, int CantT);
void mostrarPendientesYmover(Tarea** TPendientes, Tarea** TRealizadas, int CantT);
void mostrarTareas(Tarea** ListaTareas, int CantT);
void mostrarUnaTarea(Tarea* UnaTarea);
Tarea* BuscarTarea(Tarea** TPendientes, Tarea** TRealizadas, int CantT, int id);
void liberarMemoria(Tarea** ListaTareas, int CantT);

int main()
{   
    srand(time(NULL));
    Tarea **TareasPendientes, **TareasRealizadas;
    int CantidadTareas;

    printf("Ingrese la cantidad de tareas:\n");
    scanf("%d",&CantidadTareas);

    TareasPendientes = (Tarea** )malloc(CantidadTareas*sizeof(Tarea*));
    TareasRealizadas = (Tarea** )malloc(CantidadTareas*sizeof(Tarea*));

    cargarTareasPendientes(TareasPendientes, CantidadTareas);
    
    printf("\n");
    printf("-------------------------------\n");
    printf("\n");
    
    mostrarPendientesYmover(TareasPendientes, TareasRealizadas, CantidadTareas);

    printf("\n");
    printf("-------------------------------\n");
    printf("\n");

    printf("#### Tareas REALIZADAS ####\n");
    mostrarTareas(TareasRealizadas, CantidadTareas);
    
    printf("\n");
    printf("-------------------------------\n");
    printf("\n");

    printf("#### Tareas PENDIENTES ####\n");
    mostrarTareas(TareasPendientes, CantidadTareas);
    
    liberarMemoria(TareasPendientes, CantidadTareas);
    liberarMemoria(TareasRealizadas, CantidadTareas);
    
    return 0;
}

void cargarTareasPendientes(Tarea** TPendientes, int CantT)
{
    char* Buff = (char*)malloc(50*sizeof(char));

    for (int i = 0; i < CantT; i++)
    {   
        TPendientes[i] = (Tarea *)malloc(sizeof(Tarea)); // *(TPendientes + i) = (Tarea *)malloc(sizeof(Tarea));

        TPendientes[i]->TareaID = i+1; // (*(TPendientes + i))->TareaIp = i+1

        printf("Ingrese la descripcion de la tarea %d:\n",i+1);
        fflush(stdin);
        gets(Buff);
        TPendientes[i]->Descripcion = (char*)malloc((strlen(Buff)+1)*sizeof(char));
        // TPendientes[i]->Descripcion = (char*)malloc(strlen(Buff)+1);
        // porque char vale 1 y es como multiplicar por 1
        strcpy(TPendientes[i]->Descripcion, Buff);

        TPendientes[i]->Duracion = 10+(rand()%91);
    }
    free(Buff);
}

void mostrarPendientesYmover(Tarea** TPendientes, Tarea** TRealizadas, int CantT)
{
    int opcion;

    printf("#### Tareas PENDIENTES ####\n");
    for (int i = 0; i < CantT; i++)
    {   
        printf("\n");
        mostrarUnaTarea(TPendientes[i]);
        printf("La tarea fue realizada? 1(Si), 0(No)\n");
        scanf("%d",&opcion);

        if (opcion)
        {                                    // *(TRealizadas + i) = *(TPendientes + i)
            TRealizadas[i] = TPendientes[i]; // igualo los contenidos (que son estructuras) de adonde apuntan los punteros
            TPendientes[i] = NULL;
        }
        else
        {
            TRealizadas[i] = NULL;
        }        
    }
}

void mostrarTareas(Tarea** ListaTareas, int CantT)
{
    for (int i = 0; i < CantT; i++)
    {
        if (ListaTareas[i] != NULL) // *(Tareas + i) != NULL
        {
            mostrarUnaTarea(ListaTareas[i]);
        }
    }
}

void mostrarUnaTarea(Tarea* UnaTarea)
{
    printf("===> Tarea %d\n",UnaTarea->TareaID);
    printf("TareaID: %d\n",UnaTarea->TareaID); // (*(Tarea + i))->TareaID
    printf("Descripcion: %s\n",UnaTarea->Descripcion);
    printf("Duracion: %d\n",UnaTarea->Duracion);
    printf("\n");
}

void liberarMemoria(Tarea** ListaTareas, int CantT)
{
    for (int i = 0; i < CantT; i++)
    {
        if (ListaTareas[i] != NULL)
        {
            free(ListaTareas[i]->Descripcion);
            free(ListaTareas[i]);
        }
        free(ListaTareas);
    }
}

Tarea* BuscarTarea(Tarea** TPendientes, Tarea** TRealizadas, int CantT, int id)
{
    for (int i = 0; i < CantT; i++)
    {
        if ((TPendientes[i]!=NULL) && (id == TPendientes[i]->TareaID))
        {
            return TPendientes[i];
        }
        else
        {
            if ((TRealizadas[i]!=NULL) && (id == TRealizadas[i]->TareaID))
            {
                return TRealizadas[i];
            } 
        }
    }
}

/* OTRA OPCION DE MOVER LAS TAREAS:
void mostrarPendientesYmover(Tarea** TPendientes, Tarea** TRealizadas, int CantT)
{
    int opcion;

    printf("#### Tareas PENDIENTES ####\n");
    for (int i = 0; i < CantT; i++)
    {   
        printf("\n");
        mostrarUnaTarea(TPendientes[i], i);
        printf("La tarea fue realizada? 1(Si), 0(No)\n");
        scanf("%d",&opcion);

        TRealizadas[i] = (Tarea *)malloc(sizeof(Tarea));  <=== RESERVO MEMORIA DINAMICA XQ LUEGO ASIGNO CAMPO A CAMPO (SINO DA SEGMENTATION FAULT)

        if (opcion)
        {   
            TRealizadas[i]->TareaID = TPendientes[i]->TareaID;
            TRealizadas[i]->Descripcion = (char*)malloc((strlen(TPendientes[i]->Descripcion)+1)*sizeof(char*)); <=== RESERVO MEMORIA DINAMICA
            strcpy(TRealizadas[i]->Descripcion, TPendientes[i]->Descripcion);
            TRealizadas[i]->Duracion = TPendientes[i]->Duracion;
            TPendientes[i] = NULL;
        }
        else
        {
            TRealizadas[i] = NULL;
        }        
    }
}
*/