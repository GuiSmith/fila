#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 5

class Fila {
        public:
                Fila();
                bool Fila_cheia();
                bool Fila_Vazia();
                bool Inserir(int valor);
                int Retirar();
                void Ver();
				void Dados();
        private:
                int inicio = -1;
                int fim = -1;
                int fila[TAMANHO];
};

int main(){
        Fila obj;
        obj.Inserir(9);
        obj.Inserir(9);
        obj.Inserir(9);
        obj.Inserir(9);
        obj.Inserir(9);
		obj.Dados();
        return 0;
}
Fila::Fila(){
    printf("Fila criada\n");
}

bool Fila::Fila_cheia(){
        if (Fila_Vazia()){
                return false;
        }else{
                /*
                Testando se inicio é a primeira posição da fila E fim é a última posição da fila
                OU
                Testando se inicio é não é a primeira posição da fila e fim é a posição anterior a do inicio
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
			}
			//printf("%d: %d\n",fim,valor);
			if(fim+1 == TAMANHO){
				if(inicio > 0){
					fim = 0;
				}
			}else{
				fim++;
			}
			fila[fim] = valor;
			return true;
        }else{
			printf("Fila está cheia\n");
            return false;
        }
}

void Fila::Dados(){
	printf("Inicio: %d. Fim: %d\n",inicio,fim);
	for(int i = 0; i< TAMANHO; i++){
		printf("%d: ", i);
		printf("%d\n",fila[i]);
	}
}