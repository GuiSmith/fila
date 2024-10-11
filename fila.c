#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 5

class Fila {
        public:
                Fila(bool show = false);
                bool Fila_cheia();
                bool Fila_Vazia();
                bool Inserir(int valor);
                int Retirar();
                void Ver();
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
        printf("\nRetirando\n");
        for(int i = 0; i < limit; i++){
            if(!obj.Retirar()){
                printf("Erro: %d\n",i);
            }else{
                printf("Sucesso: %d\n",i);
            }
        }
        obj.Dados();
        return 0;
}

Fila::Fila(bool show){
    if(show){
        printf("Fila criada\n");
    }
}

bool Fila::Fila_cheia(){
        if (Fila_Vazia()){
            return false;
        }else{
            /*
            Testando se inicio é a primeira posição da fila E fim é a última posição da fila
            OU
            Testando se inicio não é a primeira posição da fila e fim é a posição anterior a do inicio
            */
            if((inicio == 0 && fim == TAMANHO-1) || (inicio != 0 && fim==inicio-1)){
                    return true;
            }else{
                    return false;
            }
        }
}

bool Fila::Fila_Vazia(){
        if(inicio == -1 && fim == -1){
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
    		    //printf("%d: %d\n",fim,valor);
    			if(fim+1 == TAMANHO){
    				if(inicio > 0){
    					fim = 0;
    				}
    			}else{
    				fim++;
    			}
    			fila[fim] = valor;
    		}
    		return true;
        }else{
			printf("Fila está cheia\n");
            return false;
        }
}

int Fila::Retirar(){
    if(Fila_Vazia()){
        printf("Fila vazia");
        return 0;
    }else{
        int temp = fila[inicio];
        fila[inicio] = 0;
        if(inicio+1 == TAMANHO){
            if(inicio == fim){
                inicio = -1;
                fim = -1;
            }else{
                fim = 0;
            }
        }else{
            if(inicio == fim-1){
                inicio = -1;
                fim = -1;
            }else{
                inicio++;
            }
        }
        return temp;
    }
}

void Fila::Dados(){
	printf("Inicio: %d. Fim: %d\n",inicio,fim);
	for(int i = 0; i< TAMANHO; i++){
		printf("%d: ", i);
		printf("%d\n",fila[i]);
	}
}
