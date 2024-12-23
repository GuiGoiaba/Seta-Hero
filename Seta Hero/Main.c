#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
//adcionando os prototipos
#include "objeto.h"
//definindo as dimensoes da janela
#define ALTURA  720
#define LARGURA  480
#define QUANT_INIMIGOS 10
#define FPS 60
 
enum teclas{cima, baixo, esquerda, direita};
bool teclas[4] = {false, false, false, false};

//prototipos das funcoes aqui em cima para o codico ficar mais legivel
void initClemilson(Jogador clemilson);
void aparenciaClemilson(Jogador clemilson);

void initSeta(Seta setinha);
void setaDesenho (Seta setinha);
void updateSeta(Seta setinha);
void setaCima(Seta setinha);
void setaBaixo(Seta setinha);
void setaEsquerda(Seta setinha);
void setaDireita(Seta setinha);

void initInim(Inimigo inim[], int quant);
void inimigoAsset(Inimigo inim[], int quant);
void inimigoUpdate(Inimigo inim[], int quant);


int main(){
    bool fechar = false;
    bool redraw = true;
    //cria janela
    ALLEGRO_DISPLAY *Janela = NULL;
    //cria um evento para chamar uma entrada do computador
    ALLEGRO_EVENT_QUEUE *Evento = NULL;
    //clemilson é um nome engraçado
    ALLEGRO_TIMER *tempo = NULL;

    Jogador clemilson;
    Seta setinha;
    Inimigo inim[QUANT_INIMIGOS];


    //principal funcao para iniciar tudo
    if(!al_init()){
        printf("Erro ao iniciar\n");
        return EXIT_FAILURE;
    }

    //atribui as dimencoes a janela
    Janela = al_create_display(ALTURA, LARGURA);
    if(!Janela){
        printf("Erro ao criar janela\n");
        return EXIT_FAILURE;
    }

    //eu ainda tenho que definir esta
    al_init_primitives_addon();
    al_install_keyboard();

    //cria o evento :0
    Evento = al_create_event_queue();
    tempo = al_create_timer(1.0/FPS);

    al_register_event_source(Evento, al_get_keyboard_event_source());
    al_register_event_source(Evento, al_get_timer_event_source(tempo));
    al_register_event_source(Evento, al_get_display_event_source(Janela)); 

    srand(time(NULL));
    initClemilson(clemilson);
    initSeta(setinha);
    initInim(inim, QUANT_INIMIGOS);

    al_start_timer(tempo);
    //looping para manter a janela aberta
    while(!fechar){
        /*trecho para fechar a janela ao apertar aqueele X la em cima*/
        ALLEGRO_EVENT ev;
        al_wait_for_event(Evento, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER){
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            fechar = true;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    teclas[cima] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    teclas[baixo] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    teclas[esquerda] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    teclas[direita] = true;
                    break;
            }

        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    teclas[cima] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    teclas[baixo] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    teclas[esquerda] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    teclas[direita] = false;
                    break;
            }
        }

        if(redraw && al_is_event_queue_empty(Evento)){
            redraw = false;
            aparenciaClemilson(clemilson);
            setaDesenho(setinha);
            al_flip_display();
            al_clear_to_color(al_map_rgb(192, 192, 192));
            al_draw_filled_rectangle(0, 270, ALTURA, 200, al_map_rgb(128, 128, 128));
        }
    }
    al_destroy_display;
}

//dimensoes do jogador
void initClemilson(Jogador clemilson){
    clemilson.x = 10;
    clemilson.y = 15;
    clemilson.pontos = 0;
}

//cores do boneco   
void aparenciaClemilson(Jogador clemilson){
    al_draw_circle(200, 235, 25, al_map_rgb(0, 0, 0), 10);
    al_draw_filled_circle(200, 235, 25, al_map_rgb(255, 255, 255));
}

void initSeta(Seta setinha){
    setinha.x = 5;
    setinha.y = 7;
    setinha.acertou = false;
}

void setaDesenho (Seta setinha){
    al_draw_line(200, 255, 200, 215, al_map_rgb(0, 128, 128), 5);
    al_draw_line(190, 235, 200, 217, al_map_rgb(0, 128, 128), 5);
    al_draw_line(210, 235, 200, 217, al_map_rgb(0, 128, 128), 5);
}

void setaCima(Seta setinha){
    al_draw_line(200, 255, 200, 215, al_map_rgb(0, 128, 128), 5);
    al_draw_line(190, 235, 200, 217, al_map_rgb(0, 128, 128), 5);
    al_draw_line(210, 235, 200, 217, al_map_rgb(0, 128, 128), 5);
}
void setaBaixo(Seta setinha);
void setaEsquerda(Seta setinha);
void setaDireita(Seta setinha);

void initInim(Inimigo inim[], int quant){
    int i;
    for(i = 0; i < quant; i++){
        inim[i].x = 10;
        inim[i].y = 15;
        inim[i].velocidade = 0;
        inim[i].acertou = false;
    }
};
void inimigoAsset(Inimigo inim[], int quant){
    int i;
    for(i = 0; i < quant; i++){
    al_draw_circle(200, 235, 25, al_map_rgb(0, 0, 0), 10);
    al_draw_filled_circle(200, 235, 25, al_map_rgb(255, 255, 255));
    }
};

void seia(Inimigo inim[], int quant){
    int i;
    for(i = 0; i < quant; i++){
        inim[i].acertou = true;
        inim[i].x = LARGURA;
        inim[i].y = 30 + rand() % (LARGURA - 60);
        break;
    }
}

void inimigoUpdate(Inimigo inim[], int quant){
    int i;
    for (int i = 0; i < quant; i++){
        inim[i].x -= inim[i].velocidade;
    }
}