#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 50

class Fila {
	public:
		Fila();
		bool Fila_cheia();
		bool Fila_Vazia();
		bool Inserir(int valor);
		int Retirar();
		void Ver();
	private:
		int inicio = -1;
		int fim = -1;
		int fila[TAMANHO];
};

int main(){
	
	return 0;
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
		}else{
			fila[fim] = valor;
		}
		if(fim == TAMANHO-1){
			fim = 0;
		}else{
			fim++;
		}
		return true;
	}else{
		return false;
	}
}