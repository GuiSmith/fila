#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 5

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
        Fila obj;
        int limit = 5;
        for(int i = 0; i < limit; i++){
            if(!obj.Inserir(9)){
                printf("Erro: %d\n",i);
            }else{
                printf("Sucesso: %d\n",i);
            }
        }
        obj.Retirar();
        obj.Inserir(5);
        obj.Dados();
        obj.Ver();
        return 0;
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
        if(!Fila_cheia()){
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
    if(Fila_Vazia()){
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
    if (Fila_Vazia()){
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