#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
}typedef Tarea;

void mostrarTareas(Tarea** T, int CantT);

int main()
{   
    srand(time(NULL));
    Tarea **Tareas;
    char *Buff;

    int CantidadTareas;

    printf("Ingrese la cantidad de tareas:\n");
    scanf("%d",&CantidadTareas);

    

    Tareas = (Tarea**)malloc(CantidadTareas*sizeof(Tarea*));

    Buff = (char*)malloc(50*sizeof(char));
    

    //cargo las tareas
    for (int i = 0; i < CantidadTareas; i++)
    {   
        Tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        Tareas[i]->TareaID = i+1;

        printf("Ingrese la descripcion de la tarea:");
        fflush(stdin);
        gets(Buff);
        Tareas[i]->Descripcion = (char*)malloc((strlen(Buff)+1)*sizeof(char*));
        strcpy(Tareas[i]->Descripcion, Buff);

        Tareas[i]->Duracion = 10+(rand()%91);
    }
    
    mostrarTareas(Tareas, CantidadTareas);

    return 0;
}

void mostrarTareas(Tarea** T, int CantT)
{   
    printf("Listado de tareas:\n");
    for (int i = 0; i < CantT; i++)
    {
        printf("Tarea %d\n",i+1);
        printf("TareaID: %d\n",T[i]->TareaID);
        printf("Descripcion: %s\n",T[i]->Descripcion);
        printf("Duracion: %d\n",T[i]->Duracion);
    }
}