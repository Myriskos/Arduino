////////////////////////////////////////////// BIBLIOTECAS //////////////////////////////////////////

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include <U8g2_for_Adafruit_GFX.h>

////////////////////////////////////////////// DEFINES /////////////////////////////////////////////

#define MINPRESSURE 400
#define MAXPRESSURE 2000
#define PRETO     0x0000
#define VERMELHO  0xF800
#define VERDE     0x07E0
#define BRANCO    0xFFFF
#define AZUL      0x001F
#define ROXO      0x9339
#define AMARELO   0xFFE0
#define CIANO     0x07FF
#define CIANO_2   0x03EF
#define MAGENTA 0xF81F
#define XP 8
#define XM A2
#define YP A3
#define YM 9
#define TS_LEFT 78
#define TS_RT 889
#define TS_TOP 896
#define TS_BOT 126
#define ROTATION 1
#define TOTAL_BOTOES 6

///////////////////////////////////////////////// OBJETOS ////////////////////////////////////

TouchScreen ts = TouchScreen(XP, YP, XM, YM, MINPRESSURE);
Adafruit_GFX_Button botoes[TOTAL_BOTOES];
MCUFRIEND_kbv tft;
U8G2_FOR_ADAFRUIT_GFX u8g2_for_adafruit_gfx;

///////////////////////////////////////////////////////////////////////////// ESTRUTURAS //////////////////////////////////////////////////////////////////////////////

typedef struct frase_2_partes{

  String parte_1, parte_2;
  byte resp_1, resp_2;
  
}fp2;

typedef struct frase_3_partes{

  String parte_1, parte_2, parte_3;
  byte resp_1, resp_2, resp_3;
  
}fp3;

typedef struct frase_4_partes{

  String parte_1, parte_2, parte_3, parte_4;
  byte resp_1, resp_2, resp_3, resp_4;
  
}fp4;

//////////////////// Nível 1
fp2 vet_N1_p2[2];
fp3 vet_N1_p3[9];
fp4 vet_N1_p4[4];

////////////////// Nível 2
fp2 vet_N2_p2[1];
fp3 vet_N2_p3[5];
fp4 vet_N2_p4[9];

///////////////// Nível 3
fp2 vet_N3_p2[1];
fp3 vet_N3_p3[9];
fp4 vet_N3_p4[5];

//////////////// Vírgula nível 1
fp3 vet_V1_p3[18];
fp4 vet_V1_p4[11];

///////////////// Vírgula nível 2
fp4 vet_V2_p4[5];

//////////////////////////////////////////////// VARIÁVEIS GLOBAIS //////////////////////////////////

bool pressionado = false;
int posX;
int posY;
byte estado = 0;
byte pontos_N_1 = 0, pontos_N_2 = 0, pontos_N_3 = 0, pontos_Virgula_N_1 = 0, pontos_Virgula_N_2 = 0;

/////////////////////////////////////////////// CORPO DE FUNÇÕES ////////////////////////////////////

//////////////////////////////////////////////////////// Opções iniciais
byte tela_Opcoes(){

  byte i, opcao_Escolhida;
  bool toque_Opcoes = false;
  tft.fillScreen(PRETO);

  char bt2[8] = {'V', char(161), 'r', 'g', 'u', 'l', 'a', '\0'};
  char bt1[8] = {'A', 'n', char(134), 'l', 'i', 's', 'e', '\0' };
  botoes[0].initButton(&tft, 160,  95, 255, 50, BRANCO, CIANO, PRETO, (char *)bt1, 2);
  botoes[1].initButton(&tft, 160, 153, 255, 50, BRANCO, AZUL, PRETO, (char *)bt2, 2);
  botoes[2].initButton(&tft, 160, 210, 255, 50, BRANCO, ROXO, PRETO, (char *)"Encerrar", 2);

  for(i = 0 ; i < 3 ; i++){
  
      botoes[i].drawButton(false);
      
  }
  
  tft.fillRect(0, 0, 320, 60, BRANCO);
  u8g2_for_adafruit_gfx.setFont(u8g2_font_helvB12_te);  // extended font
  u8g2_for_adafruit_gfx.setFontMode(1);
  u8g2_for_adafruit_gfx.setForegroundColor(PRETO);
  u8g2_for_adafruit_gfx.setCursor(65,16);
  u8g2_for_adafruit_gfx.print(F("ESCOLHA O EXERCÍCIO"));

  while(toque_Opcoes == false){
  
      toque_Opcoes = obter_Toque();
      opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 3);
  
  }
  
  botoes[opcao_Escolhida].drawButton(true);
  espera_Soltar();
  botoes[opcao_Escolhida].drawButton();

  return opcao_Escolhida;
  
}

///////////////////////////////////////////////////////////////// Opções de níveis 

byte tela_Escolha_Nivel(byte exr){

    byte i, opcao_Escolhida;
    bool toque_Opcoes = false;
    
    tft.fillScreen(PRETO);
    tft.fillRect(0, 0, 320, 60, BRANCO);
    u8g2_for_adafruit_gfx.setFont(u8g2_font_helvB12_te);  // extended font
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setCursor(80,16);
    u8g2_for_adafruit_gfx.setForegroundColor(PRETO); 
    u8g2_for_adafruit_gfx.print(F("ESCOLHA O NÍVEL"));
    
    char bt1[8] = {'N', char(161), 'v', 'e', 'l', ' ', '1', '\0'};
    char bt2[8] = {'N', char(161), 'v', 'e', 'l', ' ', '2', '\0'};
    char bt3[8] = {'N', char(161), 'v', 'e', 'l', ' ', '3', '\0'};
    char bt4[7] = {'P', 'o', 'n', 't', 'o', 's', '\0'};
    
    botoes[0].initButton(&tft,  70, 110, 140, 40, BRANCO, CIANO, PRETO, (char *)bt1, 2);
    botoes[1].initButton(&tft, 240, 110, 150, 40, BRANCO, AZUL, PRETO, (char *)bt2, 2);
    botoes[2].initButton(&tft,  70, 160, 140, 40, BRANCO, VERMELHO, PRETO, (char *)bt3, 2);
    botoes[3].initButton(&tft, 240, 160, 150, 40, BRANCO, ROXO, PRETO, (char *)"Voltar", 2);
    botoes[4].initButton(&tft, 240, 210, 150, 40, BRANCO, MAGENTA, PRETO, (char *)bt4, 2);

    for(i = 0 ; i < 5 ; i++){

        if((exr == 1) && (i == 2)){
              continue;
        }

        else{
              botoes[i].drawButton(false); 
        }
      
    }

    while(toque_Opcoes == false){
  
        toque_Opcoes = obter_Toque();
        opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 5);
  
    }
  
    botoes[opcao_Escolhida].drawButton(true);
    espera_Soltar();
    botoes[opcao_Escolhida].drawButton();

   return opcao_Escolhida;

}

///////////////////////////////////////////////// Exercícios de análise sintática

void tela_Ex_Func_Sint(byte nivel, fp2 vet_p2[], fp3 vet_p3[], fp4 vet_p4[], byte tamanho_p2, byte tamanho_p3, byte tamanho_p4){

    byte opcao_Escolhida, j, chamado, cont = 1;
    bool toque_Opcoes = false;

        
        for(j = 0 ; j < tamanho_p2 ; j++){

            for(chamado = 0 ; chamado < 2 ; chamado++){

                desenha_botoes_frases(cont);
                escreve_frases_Analise(vet_p2[j], vet_p3[0], vet_p4[0], chamado, 2);

                while(toque_Opcoes == false){

                    toque_Opcoes = obter_Toque();
                    opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 5);
  
                }
  
                botoes[opcao_Escolhida].drawButton(true);
                espera_Soltar();
                botoes[opcao_Escolhida].drawButton();

                if( ((chamado == 0) && (opcao_Escolhida == vet_p2[j].resp_1)) || ((chamado == 1) && (opcao_Escolhida == vet_p2[j].resp_2)) ){

                          correto(nivel);
                  
                }

                else{
                     
                          incorreto();
                
                }

                toque_Opcoes = false;

           }

           cont++;
      }


      for(j = 0 ; j < tamanho_p3 ; j++){

            for(chamado = 0 ; chamado < 3 ; chamado++){

                  desenha_botoes_frases(cont);
                  escreve_frases_Analise(vet_p2[0], vet_p3[j], vet_p4[0], chamado, 3);

                  while(toque_Opcoes == false){
  
                    toque_Opcoes = obter_Toque();
                    opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 5);
  
                  }
  
                  botoes[opcao_Escolhida].drawButton(true);
                  espera_Soltar();
                  botoes[opcao_Escolhida].drawButton();

                  if( ((chamado == 0) && (opcao_Escolhida == vet_p3[j].resp_1)) || ((chamado == 1) && (opcao_Escolhida == vet_p3[j].resp_2)) || ((chamado == 2) && (opcao_Escolhida == vet_p3[j].resp_3)) ){

                          correto(nivel);

                  }

                  else{

                          incorreto();
                
                  } 

                  toque_Opcoes = false;

            }

            cont++;
            
        }

        
        for(j = 0 ; j < tamanho_p4 ; j++){

            for(chamado = 0 ; chamado < 4 ; chamado++){

                  desenha_botoes_frases(cont);
                  escreve_frases_Analise(vet_p2[0], vet_p3[0], vet_p4[j], chamado, 4);

                  while(toque_Opcoes == false){
  
                    toque_Opcoes = obter_Toque();
                    opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 5);
  
                  }
  
                  botoes[opcao_Escolhida].drawButton(true);
                  espera_Soltar();
                  botoes[opcao_Escolhida].drawButton();

                  if( ((chamado == 0) && (opcao_Escolhida == vet_p4[j].resp_1)) || ((chamado == 1) && (opcao_Escolhida == vet_p4[j].resp_2)) || ((chamado == 2) && (opcao_Escolhida == vet_p4[j].resp_3)) || ((chamado == 3) && (opcao_Escolhida == vet_p4[j].resp_4)) ){

                          correto(nivel);

                  }

                  else{

                          incorreto();
                
                  } 

                  toque_Opcoes = false;

            }

            cont ++;
        }
        
}

/////////////////////////////////////////////////// Exercício de estudo de vírgulas

void tela_Ex_Virg(byte nivel, fp3 vet_p3[], fp4 vet_p4[], byte tamanho_p3, byte tamanho_p4, bool flag){
    
    byte opcao_Escolhida, j, chamado, cont = 1, total;
    bool toque_Opcoes = false;
    
    if(nivel == 0){
      total = 29;
    }

    else{
      total = 5;
    }

    nivel = nivel + 3;
    
   if(flag == true){
     for(j = 0 ; j < tamanho_p3 ; j++){

            for(chamado = 0 ; chamado < 2 ; chamado++){

                  desenha_botoes_virgula(cont, total);
                  escreve_frases_Virgula(vet_p3[j], vet_p4[0], chamado, 3);

                  while(toque_Opcoes == false){
  
                    toque_Opcoes = obter_Toque();
                    opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 2);
  
                  }
  
                  botoes[opcao_Escolhida].drawButton(true);
                  espera_Soltar();
                  botoes[opcao_Escolhida].drawButton();

                  if( ((chamado == 0) && (opcao_Escolhida == vet_p3[j].resp_1)) || ((chamado == 1) && (opcao_Escolhida == vet_p3[j].resp_2)) ){

                          correto(nivel);

                  }

                  else{

                          incorreto();
                
                  } 

                  toque_Opcoes = false;

            }

            cont++;
            
        }
   }
      
      for(j = 0 ; j < tamanho_p4 ; j++){

            for(chamado = 0 ; chamado < 3 ; chamado++){

                  desenha_botoes_virgula(cont, total);
                  escreve_frases_Virgula(vet_p3[0], vet_p4[j], chamado, 4);

                  while(toque_Opcoes == false){
  
                    toque_Opcoes = obter_Toque();
                    opcao_Escolhida = tecla_Pressionada(toque_Opcoes, 2);
  
                  }
  
                  botoes[opcao_Escolhida].drawButton(true);
                  espera_Soltar();
                  botoes[opcao_Escolhida].drawButton();

                  if( ((chamado == 0) && (opcao_Escolhida == vet_p4[j].resp_1)) || ((chamado == 1) && (opcao_Escolhida == vet_p4[j].resp_2)) || ((chamado == 2) && (opcao_Escolhida == vet_p4[j].resp_3)) ){

                          correto(nivel);

                  }

                  else{

                          incorreto();
                
                  } 

                  toque_Opcoes = false;

            }

            cont ++;
        }
}

/////////////////////////////////////////////////// Obtem toque na tela

bool obter_Toque(){
  
    TSPoint p = ts.getPoint();
    pinMode(YP, OUTPUT);      
    pinMode(XM, OUTPUT);
    digitalWrite(YP, HIGH);   
    digitalWrite(XM, HIGH);
    bool pressed = (p.z > MINPRESSURE);
    
    if (pressed) {
      
          posX = map(p.y, TS_LEFT, TS_RT, 0, 320); 
          posY = map(p.x, TS_TOP, TS_BOT , 0, 240);
    
          return true;
        
    }
    
    return false; 
}

///////////////////////////////////////////////////////////////// Busca qual parte da tela foi pressionada
byte tecla_Pressionada(bool teclaTocada, byte total_Botoes){
  
  for (byte i = 0; i < total_Botoes ; i++){
    
      botoes[i].press(teclaTocada && botoes[i].contains(posX,posY));
    
  }
  
  return checa_Tecla_Pressionada(total_Botoes);
  
}

//////////////////////////////////////////////////////////// Checa qual tecla foi pressionada na tela
byte checa_Tecla_Pressionada(byte num_botoes){
  
  for (byte i = 0 ; i < num_botoes ; i++){
    
      if (botoes[i].justPressed()){
      
          return i;
      
      }
    
  }

  return -1;
  
}

////////////////////////////////////////////////////////// Espera um tempo para a tecla ser solta

void espera_Soltar(){
  
  while (obter_Toque()){
    
    delayMicroseconds(100);
    
  }
  
}

////////////////////////////////////////////////// Tela de opção correta

void correto(byte op){
            
            tft.fillScreen(PRETO);
            tft.setCursor(100,100);
            tft.setTextColor(VERDE);
            tft.setTextSize(3);
            tft.print(F("Correto"));
            delay(500);

            switch (op){

                case 0:
                
                    pontos_N_1++;
                    
                break;


                case 1:
                
                    pontos_N_2++;
                    
                break;


                case 2:
                
                    pontos_N_3++;
                    
                break;


                case 3:
                
                    pontos_Virgula_N_1++;
                    
                break;


                case 4:
                
                    pontos_Virgula_N_2++;
                    
                break;


                default:

                break;
            
            }
            
}

///////////////////////////////////////////////////// Tela de opção incorreta

void incorreto(){
       
            tft.fillScreen(PRETO);
            tft.setCursor(70,100);
            tft.setTextColor(VERMELHO);
            tft.setTextSize(3);
            tft.print(F("Incorreto"));
            delay(500);
            
}

/////////////////////////////////////////////////////////////// Tela de encerramentor
void encerrar(){
    
    byte i;
    bool toque_Opcoes = false;
    
    tft.fillScreen(BRANCO);
    tft.setCursor(25,10);
    tft.setTextColor(AZUL);
    tft.setTextSize(3);
    tft.println(F("TOTAL DE PONTOS"));

    u8g2_for_adafruit_gfx.setFont(u8g2_font_helvB12_te);  // extended font
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setCursor(10, 50);
    u8g2_for_adafruit_gfx.setForegroundColor(PRETO);
    u8g2_for_adafruit_gfx.print(F("ANÁLISE SINTÁTICA"));

    u8g2_for_adafruit_gfx.setCursor(30, 80);
    u8g2_for_adafruit_gfx.setForegroundColor(VERMELHO);
    u8g2_for_adafruit_gfx.print(F("Nível 1: "));

    u8g2_for_adafruit_gfx.setForegroundColor(MAGENTA);
    u8g2_for_adafruit_gfx.print(pontos_N_1);
    u8g2_for_adafruit_gfx.setForegroundColor(AZUL);
    u8g2_for_adafruit_gfx.println("/47");

    u8g2_for_adafruit_gfx.setCursor(30, 110);
    u8g2_for_adafruit_gfx.setForegroundColor(VERMELHO);
    u8g2_for_adafruit_gfx.print(F("Nível 2: "));

    u8g2_for_adafruit_gfx.setForegroundColor(MAGENTA);
    u8g2_for_adafruit_gfx.print(pontos_N_2);
    u8g2_for_adafruit_gfx.setForegroundColor(AZUL);
    u8g2_for_adafruit_gfx.println("/53");

    u8g2_for_adafruit_gfx.setCursor(30, 140);
    u8g2_for_adafruit_gfx.setForegroundColor(VERMELHO);
    u8g2_for_adafruit_gfx.print(F("Nível 3: "));

    u8g2_for_adafruit_gfx.setForegroundColor(MAGENTA);
    u8g2_for_adafruit_gfx.print(pontos_N_3);
    u8g2_for_adafruit_gfx.setForegroundColor(AZUL);
    u8g2_for_adafruit_gfx.println("/49");

    u8g2_for_adafruit_gfx.setCursor(10, 170);
    u8g2_for_adafruit_gfx.setForegroundColor(PRETO);
    u8g2_for_adafruit_gfx.print(F("ESTUDO DA VÍRGULA"));
    
    u8g2_for_adafruit_gfx.setCursor(30, 200);
    u8g2_for_adafruit_gfx.setForegroundColor(VERMELHO);
    u8g2_for_adafruit_gfx.print(F("Nível 1: "));

    u8g2_for_adafruit_gfx.setForegroundColor(MAGENTA);
    u8g2_for_adafruit_gfx.print(pontos_Virgula_N_1);
    u8g2_for_adafruit_gfx.setForegroundColor(AZUL);
    u8g2_for_adafruit_gfx.println("/69");
    
    u8g2_for_adafruit_gfx.setCursor(30, 230);
    u8g2_for_adafruit_gfx.setForegroundColor(VERMELHO);
    u8g2_for_adafruit_gfx.print(F("Nível 2: "));

    u8g2_for_adafruit_gfx.setForegroundColor(MAGENTA);
    u8g2_for_adafruit_gfx.print(pontos_Virgula_N_2);
    u8g2_for_adafruit_gfx.setForegroundColor(AZUL);
    u8g2_for_adafruit_gfx.println("/15");


    while(toque_Opcoes == false){
  
              toque_Opcoes = obter_Toque();
    }
  
}

//////////////////////////////////// Escreve frases dos exercícios de análise sintática

void escreve_frases_Analise(fp2 p2, fp3 p3, fp4 p4, byte chamada, byte tamanho){

    byte i, j, cont = 0;
    int cor[4];
    String frase[4];
    
    tft.fillRect(0, 0, 320, 70, BRANCO);
    u8g2_for_adafruit_gfx.setFont(u8g2_font_helvB12_te);  // extended font
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setCursor(1,16);

    if(chamada == 0){
        cor[0] = AZUL;
        cor[1] = PRETO;
        cor[2] = PRETO;
        cor[3] = PRETO;
    }

    else if(chamada == 1){
        cor[0] = PRETO;
        cor[1] = AZUL;
        cor[2] = PRETO;
        cor[3] = PRETO;
    }

    else if(chamada == 2){
        cor[0] = PRETO;
        cor[1] = PRETO;
        cor[2] = AZUL;
        cor[3] = PRETO;
    }

    else{
        cor[0] = PRETO;
        cor[1] = PRETO;
        cor[2] = PRETO;
        cor[3] = AZUL;
    }

    if(tamanho == 2){
        frase[0] = p2.parte_1;
        frase[1] = p2.parte_2;
    }

    else if(tamanho == 3){
        frase[0] = p3.parte_1;
        frase[1] = p3.parte_2;
        frase[2] = p3.parte_3;
    }

    else{
        frase[0] = p4.parte_1;
        frase[1] = p4.parte_2;
        frase[2] = p4.parte_3;
        frase[3] = p4.parte_4;
    }

    for(j = 0 ; j < tamanho ; j++){
        u8g2_for_adafruit_gfx.setForegroundColor(cor[j]);
        for(i = 0 ; i < frase[j].length() ; i++){
                if(cont == 37){
                      u8g2_for_adafruit_gfx.write('\n');
                      if(frase[j][i] != ' '){
                            u8g2_for_adafruit_gfx.write(frase[j][i]);
                      }
                      
                      cont = 0;
                }

                else{
                     u8g2_for_adafruit_gfx.write(frase[j][i]);
                }

                cont++;
        }
          
    }
}


////////////////////////////////////////////// Escreve frases dos exercícios de vírgula

void escreve_frases_Virgula(fp3 p3, fp4 p4, byte chamada, byte tamanho){

    byte i, j, cont = 0;
    int cor[4];
    String frase[4];
    
    tft.fillRect(0, 0, 320, 90, BRANCO);
    u8g2_for_adafruit_gfx.setFont(u8g2_font_helvB12_te);  // extended font
    u8g2_for_adafruit_gfx.setFontMode(1);
    u8g2_for_adafruit_gfx.setCursor(1,16);

    if(chamada == 0){
        cor[0] = AZUL;
        cor[1] = MAGENTA;
        cor[2] = PRETO;
        cor[3] = PRETO;
    }

    else if(chamada == 1){
        cor[0] = PRETO;
        cor[1] = AZUL;
        cor[2] = MAGENTA;
        cor[3] = PRETO;
    }

    else{
        cor[0] = PRETO;
        cor[1] = PRETO;
        cor[2] = AZUL;
        cor[3] = MAGENTA;
    }

    if(tamanho == 3){
        frase[0] = p3.parte_1;
        frase[1] = p3.parte_2;
        frase[2] = p3.parte_3;
    }

    else{
        frase[0] = p4.parte_1;
        frase[1] = p4.parte_2;
        frase[2] = p4.parte_3;
        frase[3] = p4.parte_4;
    }

    for(j = 0 ; j < tamanho ; j++){
        u8g2_for_adafruit_gfx.setForegroundColor(cor[j]);
        for(i = 0 ; i < frase[j].length() ; i++){
                if(cont == 38){
                      u8g2_for_adafruit_gfx.write('\n');
                      if(frase[j][i] != ' '){
                            u8g2_for_adafruit_gfx.write(frase[j][i]);
                      }
                      
                      cont = 0;
                }

                else{
                     u8g2_for_adafruit_gfx.write(frase[j][i]);
                }

                cont++;
        }
          
    }
}

///////////////////////////////// Desenhar as opções nos exercícios de análise sintática

void desenha_botoes_frases(byte num){

           tft.fillScreen(PRETO);
           botoes[0].initButton(&tft,  70, 110, 140, 40, BRANCO, VERMELHO, PRETO, (char *)"Sujeito", 2);
           botoes[1].initButton(&tft, 240, 110, 150, 40, BRANCO, ROXO, PRETO, (char *)"Verbo", 2);
           botoes[2].initButton(&tft,  70, 160, 140, 40, BRANCO, VERDE, PRETO, (char *)"Complemento", 2);
           botoes[3].initButton(&tft, 240, 160, 150, 40, BRANCO, AMARELO, PRETO, (char *)"Predicativo", 2);
           botoes[4].initButton(&tft,  70, 210, 140, 40, BRANCO, CIANO, PRETO, (char *)"Adjunto", 2);
  
           for (byte i = 0 ; i < 5 ; i++){
                
                botoes[i].drawButton(false);
           
           }

           tft.setCursor(240,210);
           tft.setTextColor(BRANCO);
           tft.setTextSize(2);
           tft.print(num);
           tft.print("/15");
           
}

void desenha_botoes_virgula(byte num, byte total){
            
           tft.fillScreen(PRETO);
           char bt[4] = {'N', char(131), 'o', '\0'};
           botoes[0].initButton(&tft,  70, 130, 140, 40, BRANCO, AZUL, PRETO, (char *)"Sim", 2);
           botoes[1].initButton(&tft, 240, 130, 150, 40, BRANCO, AMARELO, PRETO, (char *)bt, 2);
  
           for (byte i = 0 ; i < 2 ; i++){
                
                botoes[i].drawButton(false);
           
           }

           tft.setCursor(240,210);
           tft.setTextColor(BRANCO);
           tft.setTextSize(2);
           tft.print(num);
           tft.print("/");
           tft.print(total);

}

/////////////////////////////////// Tela de apresentação

void tela_Inicial(){


    tft.fillScreen(BRANCO);
    tft.setCursor(50,100);
    tft.setTextColor(PRETO);
    tft.setTextSize(3);
    tft.print(F("GramaticB"));
    tft.write(147);
    tft.print(" ");
    tft.setTextColor(VERMELHO);
    tft.write(2);
    delay(5000);
    
}

////////////////////////////////////////////// SETUP ////////////////////////////////////////////////
void setup() {

  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  tft.setRotation(ROTATION);
  u8g2_for_adafruit_gfx.begin(tft); 
  tela_Inicial();

  //////////////////// Nível 1

  vet_N1_p2[0].parte_1 = F("Clarisse "); // N1 - 1
  vet_N1_p2[0].parte_2 = F("chorou.");
  vet_N1_p2[0].resp_1 = 0;
  vet_N1_p2[0].resp_2 = 1;

  vet_N1_p2[1].parte_1 = F("Choveu "); // N1 - 2
  vet_N1_p2[1].parte_2 = F("ontem.");
  vet_N1_p2[1].resp_1 = 1;
  vet_N1_p2[1].resp_2 = 4;


  vet_N1_p3[0].parte_1 = F("Cristiane "); // N1 - 3
  vet_N1_p3[0].parte_2 = F("gosta ");
  vet_N1_p3[0].parte_3 = F("de sair.");
  vet_N1_p3[0].resp_1 = 0;
  vet_N1_p3[0].resp_2 = 1;
  vet_N1_p3[0].resp_3 = 2;

  vet_N1_p3[1].parte_1 = F("Ele ");      // N1 - 4
  vet_N1_p3[1].parte_2 = F("comprou ");
  vet_N1_p3[1].parte_3 = F("o jeans.");
  vet_N1_p3[1].resp_1 = 0;
  vet_N1_p3[1].resp_2 = 1;
  vet_N1_p3[1].resp_3 = 2;

  vet_N1_p3[2].parte_1 = F("Os gatos ");  // N1 - 5
  vet_N1_p3[2].parte_2 = F("viram ");
  vet_N1_p3[2].parte_3 = F("os móveis.");
  vet_N1_p3[2].resp_1 = 0;
  vet_N1_p3[2].resp_2 = 1;
  vet_N1_p3[2].resp_3 = 2;

  vet_N1_p3[3].parte_1 = F("A terra e as plantas "); // N1 - 6
  vet_N1_p3[3].parte_2 = F("estavam ");
  vet_N1_p3[3].parte_3 = F("úmidas.");
  vet_N1_p3[3].resp_1 = 0;
  vet_N1_p3[3].resp_2 = 1;
  vet_N1_p3[3].resp_3 = 3;

  vet_N1_p3[4].parte_1 = F("Poetas ");          // N1 - 7
  vet_N1_p3[4].parte_2 = F("escrevem ");
  vet_N1_p3[4].parte_3 = F("coisas bonitas.");
  vet_N1_p3[4].resp_1 = 0;
  vet_N1_p3[4].resp_2 = 1;
  vet_N1_p3[4].resp_3 = 2;

  vet_N1_p3[5].parte_1 = F("As crianças ");         // N1 - 8
  vet_N1_p3[5].parte_2 = F("comeram ");
  vet_N1_p3[5].parte_3 = F("o bolo de chocolate.");
  vet_N1_p3[5].resp_1 = 0;
  vet_N1_p3[5].resp_2 = 1;
  vet_N1_p3[5].resp_3 = 2;

  vet_N1_p3[6].parte_1 = F("As árvores ");          // N1 - 9
  vet_N1_p3[6].parte_2 = F("balaçam ");
  vet_N1_p3[6].parte_3 = F("fortemente.");
  vet_N1_p3[6].resp_1 = 0;
  vet_N1_p3[6].resp_2 = 1;
  vet_N1_p3[6].resp_3 = 4;

  vet_N1_p3[7].parte_1 = F("Essa música ");       // N1 - 10
  vet_N1_p3[7].parte_2 = F("é ");
  vet_N1_p3[7].parte_3 = F("maravilhosa.");
  vet_N1_p3[7].resp_1 = 0;
  vet_N1_p3[7].resp_2 = 1;
  vet_N1_p3[7].resp_3 = 3;

  vet_N1_p3[8].parte_1 = F("O amor ");              // N1 - 11
  vet_N1_p3[8].parte_2 = F("comeu ");
  vet_N1_p3[8].parte_3 = F("meu nome.");
  vet_N1_p3[8].resp_1 = 0;
  vet_N1_p3[8].resp_2 = 1;
  vet_N1_p3[8].resp_3 = 2;

  vet_N1_p4[0].parte_1 = F("Mariana e Felipe ");      // N1 - 12
  vet_N1_p4[0].parte_2 = F("entregaram ");
  vet_N1_p4[0].parte_3 = F("os convites de casamento ");
  vet_N1_p4[0].parte_4 = F("aos familiares.");
  vet_N1_p4[0].resp_1 = 0;
  vet_N1_p4[0].resp_2 = 1;
  vet_N1_p4[0].resp_3 = 2;
  vet_N1_p4[0].resp_4 = 2;

  vet_N1_p4[1].parte_1 = F("Eu e Helena ");     // N1 - 13
  vet_N1_p4[1].parte_2 = F("vamos ");
  vet_N1_p4[1].parte_3 = F("ao cinema ");
  vet_N1_p4[1].parte_4 = F("mais tarde.");
  vet_N1_p4[1].resp_1 = 0;
  vet_N1_p4[1].resp_2 = 1;
  vet_N1_p4[1].resp_3 = 4;
  vet_N1_p4[1].resp_4 = 4;

  vet_N1_p4[2].parte_1 = F("Igor ");              // N1 - 14
  vet_N1_p4[2].parte_2 = F("assiste ");
  vet_N1_p4[2].parte_3 = F("aos jogos de futebol ");
  vet_N1_p4[2].parte_4 = F("todo domingo.");
  vet_N1_p4[2].resp_1 = 0;
  vet_N1_p4[2].resp_2 = 1;
  vet_N1_p4[2].resp_3 = 2;
  vet_N1_p4[2].resp_4 = 4;

  vet_N1_p4[3].parte_1 = F("Pedro e Paula ");       // N1 - 15
  vet_N1_p4[3].parte_2 = F("jantaram ");
  vet_N1_p4[3].parte_3 = F("juntos ");
  vet_N1_p4[3].parte_4 = F("ontem.");
  vet_N1_p4[3].resp_1 = 0;
  vet_N1_p4[3].resp_2 = 1;
  vet_N1_p4[3].resp_3 = 4;
  vet_N1_p4[3].resp_4 = 4;
  
////////////////////////////// Nível 2

  vet_N2_p2[0].parte_1 = F("Carregamos ");             // N2 - 1
  vet_N2_p2[0].parte_2 = F("os móveis da mudança.");
  vet_N2_p2[0].resp_1 = 1;
  vet_N2_p2[0].resp_2 = 2;


  vet_N2_p3[0].parte_1 = F("Sem olhar para trás, "); // N2 - 2
  vet_N2_p3[0].parte_2 = F("Alice ");
  vet_N2_p3[0].parte_3 = F("correu.");
  vet_N2_p3[0].resp_1 = 4;
  vet_N2_p3[0].resp_2 = 0;
  vet_N2_p3[0].resp_3 = 1;
 
  vet_N2_p3[1].parte_1 = F("Daiane ");         // N2 - 3
  vet_N2_p3[1].parte_2 = F("está ");
  vet_N2_p3[1].parte_3 = F("feliz.");
  vet_N2_p3[1].resp_1 = 0;
  vet_N2_p3[1].resp_2 = 1;
  vet_N2_p3[1].resp_3 = 3;

  vet_N2_p3[2].parte_1 = F("Durante as manhãs, "); // N2 - 4
  vet_N2_p3[2].parte_2 = F("cantavam ");
  vet_N2_p3[2].parte_3 = F("os passarinhos.");
  vet_N2_p3[2].resp_1 = 4;
  vet_N2_p3[2].resp_2 = 1;
  vet_N2_p3[2].resp_3 = 0;

  vet_N2_p3[3].parte_1 = F("Era ");                 // N2 - 5
  vet_N2_p3[3].parte_2 = F("feliz ");
  vet_N2_p3[3].parte_3 = F("o final do livro.");
  vet_N2_p3[3].resp_1 = 1;
  vet_N2_p3[3].resp_2 = 3;
  vet_N2_p3[3].resp_3 = 0;

  vet_N2_p3[4].parte_1 = F("Compraram, ");            // N2 - 6
  vet_N2_p3[4].parte_2 = F("para a ceia de Natal, ");
  vet_N2_p3[4].parte_3 = F("os ingredientes.");
  vet_N2_p3[4].resp_1 = 1;
  vet_N2_p3[4].resp_2 = 4;
  vet_N2_p3[4].resp_3 = 2;


  vet_N2_p4[0].parte_1 = F("Cansado, ");           // N2 - 7
  vet_N2_p4[0].parte_2 = F("Carlos ");
  vet_N2_p4[0].parte_3 = F("dormiu ");
  vet_N2_p4[0].parte_4 = F("na reunião.");
  vet_N2_p4[0].resp_1 = 3;
  vet_N2_p4[0].resp_2 = 0;
  vet_N2_p4[0].resp_3 = 1;
  vet_N2_p4[0].resp_4 = 4;
 
  vet_N2_p4[1].parte_1 = F("Em Brasília, ");                // N2 - 8
  vet_N2_p4[1].parte_2 = F("ela ");
  vet_N2_p4[1].parte_3 = F("encontrou ");
  vet_N2_p4[1].parte_4 = F("com seu amigo de infância.");
  vet_N2_p4[1].resp_1 = 4;
  vet_N2_p4[1].resp_2 = 0;
  vet_N2_p4[1].resp_3 = 1;
  vet_N2_p4[1].resp_4 = 2;

  vet_N2_p4[2].parte_1 = F("Assim que leu a pergunta, ");    // N2 - 9
  vet_N2_p4[2].parte_2 = F("Marcos ");
  vet_N2_p4[2].parte_3 = F("já sabia ");
  vet_N2_p4[2].parte_4 = F("a resposta.");
  vet_N2_p4[2].resp_1 = 4;
  vet_N2_p4[2].resp_2 = 0;
  vet_N2_p4[2].resp_3 = 1;
  vet_N2_p4[2].resp_4 = 2;
 
  vet_N2_p4[3].parte_1 = F("Alunos, ");             // N2 - 10
  vet_N2_p4[3].parte_2 = F("nas escolas, ");
  vet_N2_p4[3].parte_3 = F("testam ");
  vet_N2_p4[3].parte_4 = F("seus conhecimentos.");
  vet_N2_p4[3].resp_1 = 0;
  vet_N2_p4[3].resp_2 = 4;
  vet_N2_p4[3].resp_3 = 1;
  vet_N2_p4[3].resp_4 = 2;

  vet_N2_p4[4].parte_1 = F("Com medo da prova, ");         // N2 - 11
  vet_N2_p4[4].parte_2 = F("Juliana ");
  vet_N2_p4[4].parte_3 = F("estudou ");
  vet_N2_p4[4].parte_4 = F("muito.");
  vet_N2_p4[4].resp_1 = 4;
  vet_N2_p4[4].resp_2 = 0;
  vet_N2_p4[4].resp_3 = 1;
  vet_N2_p4[4].resp_4 = 4;

  vet_N2_p4[5].parte_1 = F("Pela manhã, ");         // N2 - 12
  vet_N2_p4[5].parte_2 = F("os carros ");
  vet_N2_p4[5].parte_3 = F("corriam ");
  vet_N2_p4[5].parte_4 = F("na avenida.");
  vet_N2_p4[5].resp_1 = 4;
  vet_N2_p4[5].resp_2 = 0;
  vet_N2_p4[5].resp_3 = 1;
  vet_N2_p4[5].resp_4 = 4;
 
  vet_N2_p4[6].parte_1 = F("Lívia ");                 // N2 - 13
  vet_N2_p4[6].parte_2 = F("estava ");
  vet_N2_p4[6].parte_3 = F("rouca ");
  vet_N2_p4[6].parte_4 = F("após o show.");
  vet_N2_p4[6].resp_1 = 0;
  vet_N2_p4[6].resp_2 = 1;
  vet_N2_p4[6].resp_3 = 3;
  vet_N2_p4[6].resp_4 = 2;

  vet_N2_p4[7].parte_1 = F("Assim que ouviu a notícia, ");         // N2 - 14
  vet_N2_p4[7].parte_2 = F("Luana ");
  vet_N2_p4[7].parte_3 = F("ficou ");
  vet_N2_p4[7].parte_4 = F("feliz.");
  vet_N2_p4[7].resp_1 = 4;
  vet_N2_p4[7].resp_2 = 0;
  vet_N2_p4[7].resp_3 = 1;
  vet_N2_p4[7].resp_4 = 3;

  vet_N2_p4[8].parte_1 = F("As crianças, ");                  // N2 - 15
  vet_N2_p4[8].parte_2 = F("na semana da Páscoa, ");
  vet_N2_p4[8].parte_3 = F("fizeram ");
  vet_N2_p4[8].parte_4 = F("um coelhinho.");
  vet_N2_p4[8].resp_1 = 0;
  vet_N2_p4[8].resp_2 = 4;
  vet_N2_p4[8].resp_3 = 1;
  vet_N2_p4[8].resp_4 = 2;

///////////////////// Nível 3
  vet_N3_p2[0].parte_1 = F("Preciso ");                   // N3 - 1
  vet_N3_p2[0].parte_2 = F("que você venha me ajudar.");
  vet_N3_p2[0].resp_1 = 1;
  vet_N3_p2[0].resp_2 = 2;


  vet_N3_p3[0].parte_1 = F("Eles ");                       // N3 - 2
  vet_N3_p3[0].parte_2 = F("disseram ");
  vet_N3_p3[0].parte_3 = F("que o trabalho não estava pronto.");
  vet_N3_p3[0].resp_1 = 0;
  vet_N3_p3[0].resp_2 = 1;
  vet_N3_p3[0].resp_3 = 2;

  vet_N3_p3[1].parte_1 = F("Nossa vontade ");               // N3 - 3
  vet_N3_p3[1].parte_2 = F("era ");
  vet_N3_p3[1].parte_3 = F("que o filme fosse lançado.");
  vet_N3_p3[1].resp_1 = 0;
  vet_N3_p3[1].resp_2 = 1;
  vet_N3_p3[1].resp_3 = 3;

  vet_N3_p3[2].parte_1 = F("Ela ");                           // N3 - 4
  vet_N3_p3[2].parte_2 = F("desejava ");
  vet_N3_p3[2].parte_3 = F("que lhe dessem um carro.");
  vet_N3_p3[2].resp_1 = 0;
  vet_N3_p3[2].resp_2 = 1;
  vet_N3_p3[2].resp_3 = 2;
 
  vet_N3_p3[3].parte_1 = F("É ");                          // N3 - 5
  vet_N3_p3[3].parte_2 = F("possível ");
  vet_N3_p3[3].parte_3 = F("que ela chegue tarde hoje para o jantar.");
  vet_N3_p3[3].resp_1 = 1;
  vet_N3_p3[3].resp_2 = 3;
  vet_N3_p3[3].resp_3 = 0;

  vet_N3_p3[4].parte_1 = F("Meu anseio ");            // N3 - 6
  vet_N3_p3[4].parte_2 = F("é ");
  vet_N3_p3[4].parte_3 = F("que ele chegue logo.");
  vet_N3_p3[4].resp_1 = 0;
  vet_N3_p3[4].resp_2 = 1;
  vet_N3_p3[4].resp_3 = 3;

  vet_N3_p3[5].parte_1 = F("Eu ");                       // N3 - 7
  vet_N3_p3[5].parte_2 = F("revelei ");
  vet_N3_p3[5].parte_3 = F("que sou apaixonada por Silvana.");
  vet_N3_p3[5].resp_1 = 0;
  vet_N3_p3[5].resp_2 = 1;
  vet_N3_p3[5].resp_3 = 2;

  vet_N3_p3[6].parte_1 = F("Fiz ");                        // N3 - 8
  vet_N3_p3[6].parte_2 = F("todos os exercícios ");
  vet_N3_p3[6].parte_3 = F("conforme a professora pediu.");
  vet_N3_p3[6].resp_1 = 1;
  vet_N3_p3[6].resp_2 = 2;
  vet_N3_p3[6].resp_3 = 4;

  vet_N3_p3[7].parte_1 = F("Quando saíram, ");          // N3 - 9
  vet_N3_p3[7].parte_2 = F("uma chuva forte ");
  vet_N3_p3[7].parte_3 = F("começou.");
  vet_N3_p3[7].resp_1 = 4;
  vet_N3_p3[7].resp_2 = 0;
  vet_N3_p3[7].resp_3 = 1;
 
  vet_N3_p3[8].parte_1 = F("Foi ");                 // N3 - 10
  vet_N3_p3[8].parte_2 = F("importante ");
  vet_N3_p3[8].parte_3 = F("que você participasse da aula.");
  vet_N3_p3[8].resp_1 = 1;
  vet_N3_p3[8].resp_2 = 3;
  vet_N3_p3[8].resp_3 = 0;


  vet_N3_p4[0].parte_1 = F("Luiza e João ");            // N3 - 11
  vet_N3_p4[0].parte_2 = F("procuravam ");
  vet_N3_p4[0].parte_3 = F("pelos doces, ");
  vet_N3_p4[0].parte_4 = F("quando sentiram fome.");
  vet_N3_p4[0].resp_1 = 0;
  vet_N3_p4[0].resp_2 = 1;
  vet_N3_p4[0].resp_3 = 2;
  vet_N3_p4[0].resp_4 = 4;

  vet_N3_p4[1].parte_1 = F("Embora não estudasse, ");    // N3 - 12
  vet_N3_p4[1].parte_2 = F("Ricardo ");
  vet_N3_p4[1].parte_3 = F("tirava ");
  vet_N3_p4[1].parte_4 = F("notas altas.");
  vet_N3_p4[1].resp_1 = 4;
  vet_N3_p4[1].resp_2 = 0;
  vet_N3_p4[1].resp_3 = 1;
  vet_N3_p4[1].resp_4 = 2;

  vet_N3_p4[2].parte_1 = F("As rosas ");                // N3 - 13
  vet_N3_p4[2].parte_2 = F("estão ");
  vet_N3_p4[2].parte_3 = F("murchas, ");
  vet_N3_p4[2].parte_4 = F("porque não foram molhadas.");
  vet_N3_p4[2].resp_1 = 0;
  vet_N3_p4[2].resp_2 = 1;
  vet_N3_p4[2].resp_3 = 3;
  vet_N3_p4[2].resp_4 = 4;

  vet_N3_p4[3].parte_1 = F("Nós ");                   // N3 - 14
  vet_N3_p4[3].parte_2 = F("usaremos ");
  vet_N3_p4[3].parte_3 = F("casaco ");
  vet_N3_p4[3].parte_4 = F("enquanto estiver frio.");
  vet_N3_p4[3].resp_1 = 0;
  vet_N3_p4[3].resp_2 = 1;
  vet_N3_p4[3].resp_3 = 2;
  vet_N3_p4[3].resp_4 = 4;

  vet_N3_p4[4].parte_1 = F("Ele ");                // N3 - 15
  vet_N3_p4[4].parte_2 = F("só me dará ");
  vet_N3_p4[4].parte_3 = F("presente ");
  vet_N3_p4[4].parte_4 = F("se eu sair com ele.");
  vet_N3_p4[4].resp_1 = 0;
  vet_N3_p4[4].resp_2 = 1;
  vet_N3_p4[4].resp_3 = 2;
  vet_N3_p4[4].resp_4 = 4;

  //////////////////////////////// Vígulas nível 1
  
  vet_V1_p3[0].parte_1 = F("Sem olhar para trás ");        // V1 - 1
  vet_V1_p3[0].parte_2 = F("Alice ");
  vet_V1_p3[0].parte_3 = F("correu.");
  vet_V1_p3[0].resp_1 = 0;
  vet_V1_p3[0].resp_2 = 1;

  vet_V1_p3[1].parte_1 = F("Cansado ");                    // V1 - 2
  vet_V1_p3[1].parte_2 = F("Carlos dormiu ");
  vet_V1_p3[1].parte_3 = F("na reunião.");
  vet_V1_p3[1].resp_1 = 0;
  vet_V1_p3[1].resp_2 = 1;

  vet_V1_p3[2].parte_1 = F("Daiane ");                    // V1 - 3
  vet_V1_p3[2].parte_2 = F("professora de Literatura ");
  vet_V1_p3[2].parte_3 = F("está de férias.");
  vet_V1_p3[2].resp_1 = 0;
  vet_V1_p3[2].resp_2 = 0;

  vet_V1_p3[3].parte_1 = F("Os adolescentes sabiam que a prova seria fácil e ");  // V1 - 4
  vet_V1_p3[3].parte_2 = F("mesmo assim ");
  vet_V1_p3[3].parte_3 = F("estudaram.");
  vet_V1_p3[3].resp_1 = 0;
  vet_V1_p3[3].resp_2 = 0;

  vet_V1_p3[4].parte_1 = F("Esther queria ser atriz quando pequena ");      // V1 - 5
  vet_V1_p3[4].parte_2 = F("mas ");
  vet_V1_p3[4].parte_3 = F("se tornou engenheira.");
  vet_V1_p3[4].resp_1 = 0;
  vet_V1_p3[4].resp_2 = 1;

  vet_V1_p3[5].parte_1 = F("Sem saber onde estava ");                     // V1 - 6
  vet_V1_p3[5].parte_2 = F("a família decidia ");
  vet_V1_p3[5].parte_3 = F("se seguia o mapa ou as placas da estrada.");
  vet_V1_p3[5].resp_1 = 0;
  vet_V1_p3[5].resp_2 = 1;

  vet_V1_p3[6].parte_1 = F("Nessa semana ");                  // V1 - 7
  vet_V1_p3[6].parte_2 = F("o filme que todos esperavam ");
  vet_V1_p3[6].parte_3 = F("será lançado.");
  vet_V1_p3[6].resp_1 = 0;
  vet_V1_p3[6].resp_2 = 1;

  vet_V1_p3[7].parte_1 = F("Rogério ");                      // V1 - 8
  vet_V1_p3[7].parte_2 = F("o pai de Adalberto ");
  vet_V1_p3[7].parte_3 = F("comprou uma casa próximo ao centro da cidade.");
  vet_V1_p3[7].resp_1 = 0;
  vet_V1_p3[7].resp_2 = 0;

  vet_V1_p3[8].parte_1 = F("Ela queria comprar o quadro do artista ");    // V1 - 9
  vet_V1_p3[8].parte_2 = F("mas estava "); 
  vet_V1_p3[8].parte_3 = F("sem dinheiro.");
  vet_V1_p3[8].resp_1 = 0;
  vet_V1_p3[8].resp_2 = 1;

  vet_V1_p3[9].parte_1 = F("Já que estavam precisando de dinheiro ");       // V1 - 10
  vet_V1_p3[9].parte_2 = F("eles venderam ");
  vet_V1_p3[9].parte_3 = F("a casa.");
  vet_V1_p3[9].resp_1 = 0;
  vet_V1_p3[9].resp_2 = 1;

  vet_V1_p3[10].parte_1 = F("Quando chegou o Natal ");          // V1 - 11
  vet_V1_p3[10].parte_2 = F("perceberam ");
  vet_V1_p3[10].parte_3 = F("que o ano havia passado rápido.");
  vet_V1_p3[10].resp_1 = 0;
  vet_V1_p3[10].resp_2 = 1;

  vet_V1_p3[11].parte_1 = F("Quando amanheceu ");            // V1 - 12
  vet_V1_p3[11].parte_2 = F("a família ");
  vet_V1_p3[11].parte_3 = F("decidiu viajar.");
  vet_V1_p3[11].resp_1 = 0;
  vet_V1_p3[11].resp_2 = 1;

  vet_V1_p3[12].parte_1 = F("O circo ");                   // V1 - 13
  vet_V1_p3[12].parte_2 = F("a atração mais esperada "); 
  vet_V1_p3[12].parte_3 = F("chega à cidade hoje.");
  vet_V1_p3[12].resp_1 = 0;
  vet_V1_p3[12].resp_2 = 0;

  vet_V1_p3[13].parte_1 = F("Briana queria sair ");       // V1 - 14
  vet_V1_p3[13].parte_2 = F("mas estava ");
  vet_V1_p3[13].parte_3 = F("chovendo muito.");
  vet_V1_p3[13].resp_1 = 0;
  vet_V1_p3[13].resp_2 = 1;

  vet_V1_p3[14].parte_1 = F("Carolina se matriculou na academia "); // V1 - 15
  vet_V1_p3[14].parte_2 = F("porém ");
  vet_V1_p3[14].parte_3 = F("não foi nenhuma vez.");
  vet_V1_p3[14].resp_1 = 0;
  vet_V1_p3[14].resp_2 = 1;

  vet_V1_p3[15].parte_1 = F("Alex ");                     // V1 - 16
  vet_V1_p3[15].parte_2 = F("gerente do banco ");
  vet_V1_p3[15].parte_3 = F("me ligou hoje pela manhã.");
  vet_V1_p3[15].resp_1 = 0;
  vet_V1_p3[15].resp_2 = 0;

  vet_V1_p3[16].parte_1 = F("Ele ");                    // V1 - 17
  vet_V1_p3[16].parte_2 = F("de fato ");
  vet_V1_p3[16].parte_3 = F("sempre foi amado.");
  vet_V1_p3[16].resp_1 = 0;
  vet_V1_p3[16].resp_2 = 0;

  vet_V1_p3[17].parte_1 = F("Durante as manhãs ");        // V1 - 18
  vet_V1_p3[17].parte_2 = F("cantavam ");
  vet_V1_p3[17].parte_3 = F("os passarinhos.");
  vet_V1_p3[17].resp_1 = 0;
  vet_V1_p3[17].resp_2 = 1;


 vet_V1_p4[0].parte_1 = F("Em Brasília ");             // V1 - 19
 vet_V1_p4[0].parte_2 = F("ela encontrou ");
 vet_V1_p4[0].parte_3 = F("com seu amigo ");
 vet_V1_p4[0].parte_4 = F("de infância.");
 vet_V1_p4[0].resp_1 = 0;
 vet_V1_p4[0].resp_2 = 1;
 vet_V1_p4[0].resp_3 = 1;

 vet_V1_p4[1].parte_1 = F("Assim que leu a pergunta ");  // V1 - 20
 vet_V1_p4[1].parte_2 = F("Marcos ");
 vet_V1_p4[1].parte_3 = F("já sabia ");
 vet_V1_p4[1].parte_4 = F("a resposta.");
 vet_V1_p4[1].resp_1 = 0;
 vet_V1_p4[1].resp_2 = 1;
 vet_V1_p4[1].resp_3 = 1;

 vet_V1_p4[2].parte_1 = F("Maria e Adalberto saíram para comprar "); // V1 - 21
 vet_V1_p4[2].parte_2 = F("alface ");
 vet_V1_p4[2].parte_3 = F("tomate ");
 vet_V1_p4[2].parte_4 = F("arroz e manjericão.");
 vet_V1_p4[2].resp_1 = 1;
 vet_V1_p4[2].resp_2 = 0;
 vet_V1_p4[2].resp_3 = 0;

 vet_V1_p4[3].parte_1 = F("O livro tinha ");                // V1 - 22
 vet_V1_p4[3].parte_2 = F("aventura ");
 vet_V1_p4[3].parte_3 = F("romance ");
 vet_V1_p4[3].parte_4 = F("ficção e mistério.");
 vet_V1_p4[3].resp_1 = 1;
 vet_V1_p4[3].resp_2 = 0;
 vet_V1_p4[3].resp_3 = 0;

 vet_V1_p4[4].parte_1 = F("Maria ");                       // V1 - 23
 vet_V1_p4[4].parte_2 = F("Paula ");
 vet_V1_p4[4].parte_3 = F("Roberto e Diego ");
 vet_V1_p4[4].parte_4 = F("saíram para pescar.");
 vet_V1_p4[4].resp_1 = 0;
 vet_V1_p4[4].resp_2 = 0;
 vet_V1_p4[4].resp_3 = 1;

 vet_V1_p4[5].parte_1 = F("Antônio ");                // V1 - 24
 vet_V1_p4[5].parte_2 = F("filho de José ");
 vet_V1_p4[5].parte_3 = F("amou o presente ");
 vet_V1_p4[5].parte_4 = F("que ganhou do pai.");
 vet_V1_p4[5].resp_1 = 0;
 vet_V1_p4[5].resp_2 = 0;
 vet_V1_p4[5].resp_3 = 1;

 vet_V1_p4[6].parte_1 = F("Ricardo viajou para a capital e trouxe ");        // V1 - 25
 vet_V1_p4[6].parte_2 = F("roupas ");
 vet_V1_p4[6].parte_3 = F("celulares ");
 vet_V1_p4[6].parte_4 = F("bolsas e chaveiros para suas filhas.");
 vet_V1_p4[6].resp_1 = 1;
 vet_V1_p4[6].resp_2 = 0;
 vet_V1_p4[6].resp_3 = 0;

 vet_V1_p4[7].parte_1 = F("Ao sair de casa ");                  // V1 - 26
 vet_V1_p4[7].parte_2 = F("Ana ");
 vet_V1_p4[7].parte_3 = F("se deu conta ");
 vet_V1_p4[7].parte_4 = F("que havia esquecido as chaves.");
 vet_V1_p4[7].resp_1 = 0;
 vet_V1_p4[7].resp_2 = 1;
 vet_V1_p4[7].resp_3 = 1;

 vet_V1_p4[8].parte_1 = F("Na feira ");               // V1 - 27
 vet_V1_p4[8].parte_2 = F("Igor vende maçã ");
 vet_V1_p4[8].parte_3 = F("pêra ");
 vet_V1_p4[8].parte_4 = F("banana e abacaxi.");
 vet_V1_p4[8].resp_1 = 0;
 vet_V1_p4[8].resp_2 = 0;
 vet_V1_p4[8].resp_3 = 0;

 vet_V1_p4[9].parte_1 = F("Após o almoço ");              // V1 - 28
 vet_V1_p4[9].parte_2 = F("como era de costume ");
 vet_V1_p4[9].parte_3 = F("Augusto ");
 vet_V1_p4[9].parte_4 = F("tomou café.");
 vet_V1_p4[9].resp_1 = 0;
 vet_V1_p4[9].resp_2 = 0;
 vet_V1_p4[9].resp_3 = 1;

 vet_V1_p4[10].parte_1 = F("Milhares de alunos ");          // V1 - 29
 vet_V1_p4[10].parte_2 = F("nas escolas públicas ");
 vet_V1_p4[10].parte_3 = F("testam ");
 vet_V1_p4[10].parte_4 = F("seus conhecimentos.");
 vet_V1_p4[10].resp_1 = 0;
 vet_V1_p4[10].resp_2 = 0;
 vet_V1_p4[10].resp_3 = 1;

 /////////////////////// Virgula nível 2

 
 vet_V2_p4[0].parte_1 = F("Porque estava cansada ");       // V2 - 2
 vet_V2_p4[0].parte_2 = F("Marlene deixou o dinheiro ");
 vet_V2_p4[0].parte_3 = F("com o assitente ");
 vet_V2_p4[0].parte_4 = F("para que ela comprasse os materiais e fosse ao banco.");
 vet_V2_p4[0].resp_1 = 0;
 vet_V2_p4[0].resp_2 = 1;
 vet_V2_p4[0].resp_3 = 1;

 vet_V2_p4[1].parte_1 = F("Não obstante o recesso ");  // V2 - 3
 vet_V2_p4[1].parte_2 = F("convém que Antônio ");
 vet_V2_p4[1].parte_3 = F("estude ");
 vet_V2_p4[1].parte_4 = F("para as provas.");
 vet_V2_p4[1].resp_1 = 0;
 vet_V2_p4[1].resp_2 = 1;
 vet_V2_p4[1].resp_3 = 1;

 vet_V2_p4[2].parte_1 = F("Ao sair o sol ");    // V2 - 4
 vet_V2_p4[2].parte_2 = F("os meninos ");
 vet_V2_p4[2].parte_3 = F("que jogavam cartas dentro de casa ");
 vet_V2_p4[2].parte_4 = F("foram nadar.");
 vet_V2_p4[2].resp_1 = 0;
 vet_V2_p4[2].resp_2 = 0;
 vet_V2_p4[2].resp_3 = 0;

 vet_V2_p4[3].parte_1 = F("Quando o ônibus parou ");    // V2 - 5
 vet_V2_p4[3].parte_2 = F("os passageiros ");
 vet_V2_p4[3].parte_3 = F("desceram ");
 vet_V2_p4[3].parte_4 = F("e caminharam em direção a faculdade.");
 vet_V2_p4[3].resp_1 = 0;
 vet_V2_p4[3].resp_2 = 1;
 vet_V2_p4[3].resp_3 = 1;

 vet_V2_p4[4].parte_1 = F("Embora não soubesse onde estava ");   // V2 - 1
 vet_V2_p4[4].parte_2 = F("a família decidia ");
 vet_V2_p4[4].parte_3 = F("se seguia o mapa ");
 vet_V2_p4[4].parte_4 = F("ou as placas da estrada.");
 vet_V2_p4[4].resp_1 = 0;
 vet_V2_p4[4].resp_2 = 1;
 vet_V2_p4[4].resp_3 = 1;
  
}
///////////////////////////////////////////// LOOP //////////////////////////////////////////////////
void loop() {

  byte opcao, nivel;
  bool flag_op;

  switch (estado){
      case 0:

            opcao = tela_Opcoes();
            opcao++;
            estado = opcao;
            
      break;


      case 1:

             nivel = tela_Escolha_Nivel(0);

             if(nivel == 0){
                  tela_Ex_Func_Sint(nivel, vet_N1_p2, vet_N1_p3, vet_N1_p4, 2, 9, 4);
             }

             else if(nivel == 1){
                  tela_Ex_Func_Sint(nivel, vet_N2_p2, vet_N2_p3, vet_N2_p4, 1, 5, 9);
             }

             else if(nivel == 2){
                  tela_Ex_Func_Sint(nivel, vet_N3_p2, vet_N3_p3, vet_N3_p4, 1, 9, 5);
             }

             else if(nivel == 3){

                  estado = 0;
             }

             else{
                  encerrar();
             }
             
      break;


      case 2:

            nivel = tela_Escolha_Nivel(1);

            if(nivel == 0){
                  flag_op = true;
                  tela_Ex_Virg(nivel, vet_V1_p3, vet_V1_p4, 18, 11, flag_op);
            }

            else if(nivel == 1){
                  flag_op = false;
                  tela_Ex_Virg(nivel, vet_V1_p3, vet_V2_p4, 0, 5, flag_op);
            }

            else if(nivel == 3){
                  estado = 0;
            }

            else{
                encerrar();
            }
            
      break;


      case 3:

            encerrar();
            pontos_N_1 = 0;
            pontos_N_2 = 0;
            pontos_N_3 = 0;
            pontos_Virgula_N_1 = 0;
            pontos_Virgula_N_2 = 0;
            estado = 0;
            
      break;


      default:

            estado = 0;
            
      break;
  }
        
  
}
