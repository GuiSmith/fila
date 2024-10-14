#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 5

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
    #define PAUSE_COMMAND "pause"
#else
    #define CLEAR_COMMAND "clear"
    #define PAUSE_COMMAND "bash -c 'read -p \"Press Enter to continue...\"'"
#endif

class Fila {
        public:
                Fila(bool show = false);
                bool Fila_cheia(bool show = false);
                bool Fila_Vazia(bool show = false);
                bool Inserir(int valor);
                int Retirar();
                void Ver(bool show_qtd = false);
                void Dados(); //Fiz isso apenas para ver os dados do vetor, incluindo dados, inicio e fim
        private:
                int inicio = -1;
                int fim = -1;
                int fila[TAMANHO];
};

int main(){

    int option = 1, valor, temp;
    Fila obj;
    while(option != 0){
        system(CLEAR_COMMAND);
        printf("Fila de numeros inteiros\n\n");
        printf("1 - Inserir item na fila\n");
        printf("2 - Retirar item da fila\n");
        printf("3 - Visualizar fila\n");
        printf("4 - Ver dados (nao usa fila para mostrar dados, criado apenas para controle interno)\n");
        printf("0 - Sair\n\n");
        printf("Opcao: ");
        scanf("%d",&option);
        if(option == 1){
            printf("\nValor: ");
            scanf("%d",&valor);
            if(obj.Inserir(valor)){
                printf("Valor inserido\n");
            }
        }else{
            if (option == 2){
                printf("Valor retirado: %d\n",obj.Retirar());
            }else{
                if (option == 3){
                    obj.Ver();
                }else{
                    if (option == 4){
                        obj.Dados();
                    }else{
                        if (option == 0){
                            break;
                        }else{
                            printf("\nOpcao invalida\n");
                        }
                    }
                }
            }
        }
        printf("\n");
        system(PAUSE_COMMAND);
    }
}

Fila::Fila(bool show){
    if(show){
        printf("Fila criada\n");
    }
}

bool Fila::Fila_cheia(bool show){
        if (Fila_Vazia()){
            return false;
        }else{
            if((inicio == 0 && fim == TAMANHO-1) || (inicio != 0 && fim==inicio-1)){
                    if(show){
                        printf("\nFila Cheia\n");
                    }
                    return true;
            }else{
                    return false;
            }
        }
}

bool Fila::Fila_Vazia(bool show){
        if(inicio == -1 && fim == -1){
                if(show){
                    printf("\nFila Vazia\n");
                }
                return true;
        }else{
                return false;
        }
}

bool Fila::Inserir(int valor){
        if(!Fila_cheia(true)){
            if(Fila_Vazia()){
                inicio++;
                fim++;
                fila[fim] = valor;
             }else{
                 if(fim == TAMANHO - 1){
                     fim = 0;
                 }else{
                     fim++;
                 }
                 fila[fim] = valor;
             }
             //printf("%d: %d\n",fim,valor);
             return true;
        }else{
            return false;
        }
}

int Fila::Retirar(){
    if(Fila_Vazia(true)){
        return 0;
    }else{
        int temp = fila[inicio];
        fila[inicio] = 0;
        if(fim == inicio){
            inicio = -1;
            fim = -1;
        }else{
            if(inicio == TAMANHO - 1){
                inicio = 0;
            }else{
                inicio++;
            }
        }
        return temp;
    }
}

void Fila::Ver(bool show_qtd){
    if (Fila_Vazia(true)){
        exit(1);
    }
    int qtd, temp;
    //Calculando a quantidade de itens
    if(fim > inicio){
        qtd = (fim - inicio) + 1;
    }else{
        if(fim < inicio){
            qtd = (fim + 1) + (TAMANHO - inicio);
        }else{
            qtd = 1;
        }
    }
    if(show_qtd){
        printf("\nQuantidade: %d\n",qtd);
    }
    //Mostrando na tela
    if(qtd == 1){
        temp = Retirar();
        Inserir(temp);
        printf("\n%d\n",temp);
    }else{
        for(int i = 0; i < qtd; i++){
            temp = Retirar();
            Inserir(temp);
            printf("\n(%d)",temp);
        }
    }
}

void Fila::Dados(){
        printf("Inicio: %d. Fim: %d\n",inicio,fim);
        for(int i = 0; i< TAMANHO; i++){
                printf("%d: ", i);
                printf("%d\n",fila[i]);
        }
}