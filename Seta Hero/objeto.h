//criando os objetos a serem usados
enum teste{jogador, escolha, setas};

//atributos do jogador
typedef struct jogador{
    int x;
    int y;
    int pontos;
} Jogador;

typedef struct seta{
    int x;
    int y;
    bool acertou;
} Seta;

typedef struct inimigo{
    int x;
    int y;
    int velocidade;
    bool acertou;
} Inimigo;