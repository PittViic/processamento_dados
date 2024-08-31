#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    char name[50];
    int hour;
    int min;
    int quantity;
    Node *next;
} node;

typedef struct{
    node *top;
} ref;

void start(ref *q){
    q->top = NULL;
}

void queue(ref *q, node *New){
    if(q->top == NULL){
        q->top = New;
    } else {
        node *present = q->top;

        while(present->next != NULL){
            present = present->next;
        }
        present->next = New;
    }   
    New->next = NULL;
}

void insert(ref *q){
    node *New = (node *)malloc(sizeof(node));

    if(New == NULL){
        return;
    } else {
        printf("Operacao realizada: ");
        getchar();
        scanf("%50[^\n]s", New->name);

        do{
            printf("Momento que processo foi realizado(Horas): ");
            scanf("%d", &New->hour);
        } while(New->hour < 0 && New->hour >= 60);
        
        do{
            printf("Momento que processo foi realizado(Minutos): ");
            scanf("%d", &New->min);
        } while(New->min < 0 && New->min >= 60);

        printf("Quantidade de operacoes: ");
        scanf("%d", &New->quantity);

        queue(q, New);
    }
}

void executar(ref *q){
    node *present = q->top;

    if(present == NULL){
        printf("A fila esta vazia!\n");
        return;
    } else {
        int rem = 100;
        present->quantity -= rem;

        if(present->quantity > 0 && present->next != NULL){
            
            node *guarda = present;

            q->top = guarda->next;
            while(present->next != NULL){
                present = present->next;
            }
            present->next = guarda;
            present->next->next = NULL;
        } else if(present->next == NULL && present->quantity >= 100){
            present->next = NULL;
        } else {
            node *toRemove = q->top;

            q->top = present->next;
            free(toRemove);
        }
    }
}

void operation_calculator(ref *q){
    node *present = q->top;
    int counter = 0;

    if(present != NULL){
        while(present != NULL){
            counter += present->quantity;
            present = present->next;
        }
    } else {
        printf("Sua fila esta vazia!\n");
        return;
    }
    printf("Existem %d processos a serem realizados!\n", counter);
}



void process_time(ref *q){
    node *present = q->top;
    int hour = 0;
    int cont = 0;

    if(present == NULL){
        printf("Nao ha processos na fila!\n");
        return;
    } else {
        do{
            printf("Digite a hora buscada: ");
            scanf("%d", &hour);
        }while(hour < 0 || hour >= 60);
        system("clear || cls");

        printf("Processos criados antes de %d:\n", hour);
        while(present != NULL){
            if(present->hour < hour){
                printf("Nome do processo: %s\n", present->name);
                cont++;
            } 
            present = present->next;
        }
        printf("Existem %d processos criados antes da hora informada!\n", cont);
    }
}


void print(ref *q){
    node *present = q->top;

    if(present == NULL){
        printf("A fila esta vazia!\n");
        return;
    } else {
        while(present != NULL){
            printf("Processo: %s | Quantidade: %d | Hora do processo: %d %d\n", present->name, present->quantity, present->hour, present->min);

            present = present->next;
        }
    }
}


void menu(){
    printf("+----------MENU----------+\n");
    printf("| 1 - Inserir processo   |\n");
    printf("| 2 - Executar           |\n");
    printf("| 3 - Total de processos |\n");
    printf("| 4 - Busca por hora     |\n");
    printf("| 5 - Imprimir fila      |\n");
    printf("| 0 - Sair               |\n");
    printf("+------------------------+\n");
    printf("Escolha uma opcao: ");
}

int main(){
    ref q;
    int op;

    start(&q);

    do{
        menu();
        scanf("%d", &op);
        system("clear || cls");

        switch(op){
            case 1:
                insert(&q);
                break;
            case 2:
                executar(&q);
                break;
            case 3:
                operation_calculator(&q);
                break;
            case 4:
                process_time(&q);
                break;
            case 5:
                print(&q);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while(op != 0);

    return 0;
}
