#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO 40

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
    #define PAUSE_COMMAND "pause"
#else
    #define CLEAR_COMMAND "clear"
    #define PAUSE_COMMAND "bash -c 'read -p \"Press Enter to continue...\"'"
#endif

static void shuffle(void *array, size_t n, size_t size) {
    char tmp[size]; // Temporary storage to hold an element during swapping.
    char *arr = (char *)array; // Treat the input array as a char array (byte by byte).
    size_t stride = size * sizeof(char); // Calculate the size of each element in bytes.

    if (n > 1) {
        for (size_t i = 0; i < n - 1; ++i) {
            // Generate a random index j in the range [i, n-1].
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            // Swap the elements at positions i and j.
            memcpy(tmp, arr + j * stride, size); // Copy arr[j] to tmp.
            memcpy(arr + j * stride, arr + i * stride, size); // Copy arr[i] to arr[j].
            memcpy(arr + i * stride, tmp, size); // Copy tmp (old arr[j]) to arr[i].
        }
    }
}

struct Carta {
    char *cor;
    int numero;
};

Carta criar(const char *cor, int numero){
    Carta p;
    p.cor = (char *)malloc(strlen(cor)+1);
    if (p.cor != nullptr){
        strcpy(p.cor, cor);
    }
    p.numero = numero;
    return p;
}

class Fila {
        public:
                Fila(bool show = false);
                bool Fila_cheia(bool show = false);
                bool Fila_Vazia(bool show = false);
                bool Inserir(Carta valor);
                Carta Retirar();
                void Ver(bool show_qtd = false);
                void Dados(); //Fiz isso apenas para ver os dados do vetor, incluindo dados, inicio e fim
                void Baralho();
                void Embaralhar();
        private:
                int inicio = -1;
                int fim = -1;
                Carta fila[TAMANHO];
};

int main(){
    Fila baralho;
    baralho.Baralho();
    baralho.Ver();
    baralho.Embaralhar();
    printf("\n\nEmbaralhando\n\n");
    baralho.Ver();
    printf("\n");
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

bool Fila::Inserir(Carta valor){
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

Carta Fila::Retirar(){
    Carta carta_vazia = criar("",0);
    if(Fila_Vazia(true)){
        return carta_vazia;
    }else{
        Carta temp = fila[inicio];
        fila[inicio] = carta_vazia;
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
        printf("\n(%s %d)",temp.cor, temp.numero);
    }
    //Mostrando na tela
    if(qtd == 1){
        temp = Retirar();
        Inserir(temp);
        printf("\n%s %d\n",temp.cor,temp.numero);
    }else{
        for(int i = 0; i < qtd; i++){
            temp = Retirar();
            Inserir(temp);
            printf("\n(%s %d)",temp.cor, temp.numero);
        }
    }
}

void Fila::Dados(){
        printf("Inicio: %d. Fim: %d\n",inicio,fim);
        for(int i = 0; i< TAMANHO; i++){
                printf("%d: ", i);
                printf("%s %d\n",fila[i].cor,fila[i].numero);
        }
}

void Fila::Baralho(){
    Carta temp_obj;
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 10; j++){
            switch(i){
                case 0:
                    temp_obj = criar("Vermelho",j);
                    break;
                case 1:
                    temp_obj = criar("Amarelo",j);
                    break;
                case 2:
                    temp_obj = criar("Verde",j);
                    break;
                case 3:
                    temp_obj = criar("Azul",j);
                    break;
                default:
                    temp_obj = criar("",0);
            }
            Inserir(temp_obj);
        }
    }
}

void Fila::Embaralhar(){
    shuffle(fila, sizeof(fila) / sizeof(fila[0]), sizeof(fila[0]));
}