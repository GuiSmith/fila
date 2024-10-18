#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define TAMANHO 40
#define QUANTIDADE_JOGADORES 2

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

void mostrar_carta(Carta carta) {
    if(strcmp(carta.cor,"Vermelho") == 0){
        printf("\033[31m");
    }
    if(strcmp(carta.cor,"Amarelo") == 0){
        printf("\033[33m");
    }
    if(strcmp(carta.cor,"Verde") == 0){
        printf("\033[32m");
    }
    if(strcmp(carta.cor,"Azul") == 0){
        printf("\033[34m");
    }
    printf("\n");
    printf("╔══════╗\n");
    printf("║  %02d  ║\n", carta.numero);
    printf("║      ║\n");
    printf("║      ║\n");
    printf("╚══════╝\n");
    printf("\033[0m");
}

class Fila {
        public:
                Fila(bool show = false);
                bool Fila_cheia(bool show = false);
                bool Fila_Vazia(bool show = false);
                bool Inserir(Carta valor);
                Carta Retirar();
                bool Recalcular_Quantidade();
                int Quantidade();
                void Ver(bool show_qtd = false);
                void Dados(); //Fiz isso apenas para ver os dados do vetor, incluindo dados, inicio e fim
                void Baralho();
                void Embaralhar();
        private:
                int inicio = -1;
                int fim = -1;
                int qtd = 0;
                Carta fila[TAMANHO];
};

int main(){
    srand(time(NULL));
    Fila baralho;
    system(CLEAR_COMMAND);

    printf("Criando baralho...");
    sleep(1);
    baralho.Baralho();

    printf("\nEmbaralhando...");
    sleep(1);
    baralho.Embaralhar();

    //Criando jogadores
    printf("\nCriando %d jogadores...",QUANTIDADE_JOGADORES);
    sleep(1);
    Fila jogadores[QUANTIDADE_JOGADORES];
    for (int i = 0; i < QUANTIDADE_JOGADORES; i++){
        jogadores[i] = Fila();
    }

    //Jogadores pegando cartas
    printf("\nEntregando cartas para jogadores...");
    sleep(1);
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < QUANTIDADE_JOGADORES; j++){
            jogadores[j].Inserir(baralho.Retirar());
        }
    }

    printf("\nCarregando jogo...");
    sleep(1);
    bool game_over = false;
    int vencedor_index, perdedor_index = -1, vez = 0, rodadas = 0, menor_baralho_index;
    Fila* jogador = &jogadores[vez];
    Carta carta_descartada;

    rodadas++;
    printf("\n\n%d° rodada",rodadas);
    printf("\nJogador da vez: %d",vez);
    carta_descartada = jogador[vez].Retirar();
    printf("\nDescartou carta: %d %s",carta_descartada.numero,carta_descartada.cor);
    mostrar_carta(carta_descartada);
    sleep(1);
    menor_baralho_index = vez;
    //Mudando vez
    if (vez == QUANTIDADE_JOGADORES-1){
        vez = 0;
    }else{
        vez++;
    }
    sleep(1);
    while(!game_over){
        sleep(1);
        rodadas++;
        
        //Rodadas
        printf("\n\n%d° rodada",rodadas);
        
        //Vez do jogador
        printf("\nJogador da vez: %d",vez);
        jogador = &jogadores[vez];
        Carta carta_na_mao = jogador->Retirar();
        
        //Última carta descartada
        printf("\nÚltima carta descartada: %d %s", carta_descartada.numero, carta_descartada.cor);
        mostrar_carta(carta_descartada);
        sleep(1);

        //Carta na mão do jogador
        printf("\nCarta na mão: %d %s",carta_na_mao.numero,carta_na_mao.cor);
        mostrar_carta(carta_na_mao);
        sleep(1);
        
        //Compara carta descartada com carta na mão
        if (strcmp(carta_descartada.cor,carta_na_mao.cor) == 0 || carta_descartada.numero == carta_na_mao.numero){
            printf("\nDescartou carta");
            carta_descartada = carta_na_mao;
        }else{
            printf("\nNão descartou carta");
            jogador->Inserir(carta_na_mao);
            carta_na_mao = baralho.Retirar();
            printf("\nCompra carta: %d %s",carta_na_mao.numero,carta_na_mao.cor);
            mostrar_carta(carta_na_mao);
            sleep(1);
            
            //Compara carta na mão com carta comprada
            if(strcmp(carta_descartada.cor,carta_na_mao.cor) == 0 || carta_descartada.numero == carta_na_mao.numero){
                printf("\nDescartou carta comprada");
                carta_descartada = carta_na_mao;
            }else{
                printf("\nNão descartou carta e inseriu no próprio baralho");
                jogador->Inserir(carta_na_mao);
            }
        }

        //Definindo jogador com menor baralho
        if (jogador->Quantidade() <= jogadores[menor_baralho_index].Quantidade()){
            menor_baralho_index = vez;
        }

        //Se baralho acabar, quem tem menos cartas ganha
        if (baralho.Fila_Vazia()){
            printf("\n\nO baralho de compra acabou e o jogo foi finalizado");
            vencedor_index = menor_baralho_index;
            game_over = true;
        }

        //Se um dos jogadores descartar todas as cartas, este ganha
        if (jogador->Fila_Vazia()){
            printf("\n\nJogador atual descartou a última carta em seu baralho e ganhou o jogo");
            vencedor_index = vez;
            game_over = true;
        }

        //Se um dos jogadores ficar com a própria fila cheia, o jogo acaba e este perde e quem tem a menor fila ganha
        if (jogador->Quantidade() == 20){
            printf("\n\nJogador atual comprou sua vigésima carta e perdeu o jogo");
            vencedor_index = menor_baralho_index;
            perdedor_index = vez;
            game_over = true;
        }
        

        //Mudando vez
        if (vez == QUANTIDADE_JOGADORES-1){
            vez = 0;
        }else{
            vez++;
        }
    }
    printf("\n\nVencedor: jogador %d",vencedor_index);

    printf("\n\nSituação dos baralhos");
    if (baralho.Quantidade() > 0){
        baralho.Ver();
    }
    
    for (int i = 0; i < QUANTIDADE_JOGADORES; i++){
        printf("\nJogador %d: %d cartas",i,jogadores[i].Quantidade());
    }
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
            }else{
                if(fim == TAMANHO - 1){
                    fim = 0;
                }else{
                    fim++;
                }
            }
            //printf("%d: %d\n",fim,valor);
            fila[fim] = valor;
            qtd++;
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
        qtd--;
        return temp;
    }
}

bool Fila::Recalcular_Quantidade(){
    if(Fila_Vazia()){
        return false;
    }else{
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
        return true;
    }
}

int Fila::Quantidade(){
    return qtd;
}

void Fila::Ver(bool show_qtd){
    if (Fila_Vazia(true)){
        exit(1);
    }
    Carta temp;
    if(show_qtd){
        printf("\n%d cartas",qtd);
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
            printf("\n%d° carta: %s %d",i+1,temp.cor, temp.numero);
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