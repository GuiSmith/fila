#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO 40

struct Carta { 
    char cor;
    int num;
};

class Fila {
        public:
                Fila(bool show = false);
                bool Fila_cheia(bool show = false);
                bool Fila_Vazia(bool show = false);
                bool Inserir(Carta carta);
                Carta Retirar();
                void Ver(bool show_qtd = false);
                void Dados(); //Fiz isso apenas para ver os dados do vetor, incluindo dados, inicio e fim
        private:
                int inicio = -1;
                int fim = -1;
                Carta fila[TAMANHO];
};

int main(){
    Fila baralho;
    if (baralho.Inserir({"Vermelho",0})){
        printf("Sucesso");
    }else{
        printf("Fracasso");
    }
    
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

bool Fila::Inserir(Carta carta){
        if(!Fila_cheia()){
            if(Fila_Vazia()){
                inicio++;
                fim++;
                fila[fim] = carta;
             }else{
                 if(fim == TAMANHO - 1){
                     fim = 0;
                 }else{
                     fim++;
                 }
                 fila[fim] = carta;
             }
             //printf("%d: %d\n",fim,carta);
             return true;
        }else{
            return false;
        }
}

Carta Fila::Retirar(){
    if(Fila_Vazia()){
        Carta temp = {"",NULL};
        return {"",NULL};
    }else{
        Carta temp = fila[inicio];
        fila[inicio] = {"",NULL};
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
    int qtd;
    Carta temp;
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
        printf("\nCor: %s. Numero: %d\n",temp.cor,temp.num);
    }else{
        for(int i = 0; i < qtd; i++){
            temp = Retirar();
            Inserir(temp);
            printf("\nCor: %s. Numero: %d\n",temp.cor,temp.num);
        }
    }
}

void Fila::Dados(){
        printf("Inicio: %d. Fim: %d\n",inicio,fim);
        for(int i = 0; i < TAMANHO; i++){
                printf("%d: ", i);
                printf("\nCor: %s. Numero: %d\n",fila[i].cor,fila[i].num);
        }
}