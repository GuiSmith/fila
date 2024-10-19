#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 900
#define TAMANHO_TEXTO 9

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
                bool Inserir(const char *valor);
                char* Retirar();
                int Quantidade();
                void Dados(); //Fiz isso apenas para ver os dados do vetor, incluindo dados, inicio e fim
        private:
                int inicio = -1;
                int fim = -1;
                int qtd = 0;
                char fila[TAMANHO][TAMANHO_TEXTO];
};

int numero_de_texto(const char *entrada, int numero_se_falha);

int main() {
    Fila oeste, norte, sul, leste;
    Fila* ponto;
    char entrada[10];
    int ponto_cardeal;

    while (true) {
        // Lê o ponto cardeal
        scanf("%s", entrada);

        ponto_cardeal = numero_de_texto(entrada,-999);
        if (ponto_cardeal == 0){
            break;
        }else{
            switch(ponto_cardeal){
                case -1:
                    ponto = &oeste;
                    break;
                case -2:
                    ponto = &sul;
                    break;
                case -3:
                    ponto = &norte;
                    break;
                case -4:
                    ponto = &leste;
                    break;
                default:
                    ponto->Inserir(entrada);
                    break;
            }
        }
    }

    int filas_vazias = 0;
    while(
        !oeste.Fila_Vazia() ||
        !norte.Fila_Vazia() ||
        !sul.Fila_Vazia() ||
        !leste.Fila_Vazia()
    ){
        //Oeste
        if(!oeste.Fila_Vazia())
            printf("%s ",oeste.Retirar());
        
        //Norte
        if(!norte.Fila_Vazia())
            printf("%s ",norte.Retirar());

        //Sul
        if(!sul.Fila_Vazia())
            printf("%s ",sul.Retirar());

        //Leste
        if(!leste.Fila_Vazia())
            printf("%s ",leste.Retirar());
    }

    printf("\n");
    return 0;
}

int numero_de_texto(const char *entrada, int numero_se_falha){
    char *endptr;
    long numero = strtol(entrada, &endptr, 10);

    if (*endptr == '\0'){
        return (int)numero;
    }else{
        return numero_se_falha;
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

bool Fila::Inserir(const char *valor){
        if(!Fila_cheia(true)){
            if(Fila_Vazia()){
                inicio++;
                fim++;
            }else{
                if(fim == TAMANHO - 1){
                    fim = 0;
                }else{
                    fim++;
                }
            }
            strcpy(fila[fim],valor);
            qtd++;
            //printf("%d: %d\n",fim,valor);
            return true;
        }else{
            return false;
        }
}

char* Fila::Retirar(){
    if(Fila_Vazia()){
        return nullptr;
    }else{
        char* temp = (char*) malloc((strlen(fila[inicio]) + 1) * sizeof(char));

        strcpy(temp, fila[inicio]);

        fila[inicio][0] = '\0';
        qtd--;
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

int Fila::Quantidade(){
    return qtd;
}

void Fila::Dados(){
    printf("Inicio: %d. Fim: %d\n",inicio,fim);
    for(int i = 0; i< Quantidade(); i++){
            printf("%d: ", i);
            printf("%s\n",fila[i]);
    }
}