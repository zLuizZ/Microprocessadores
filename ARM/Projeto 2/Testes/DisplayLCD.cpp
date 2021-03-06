#include "mbed.h"
#include "C12832.h"

C12832 lcd(SPI_MOSI, SPI_SCK, SPI_MISO, p8, p11);   //configuração do display
int quilometragem = 400;

/*======================= Exibição no display LCD ==============*/
//botão para selecionar a função desejada 
InterruptIn btnFuncao(p10); //declarado como interrupção pra ser chamado sempre que pressionado
//botão para selecionar ou zerar valores
InterruptIn btnConfig(p11);
//função utilizada para indicar o que deve ser exibido no display (velocidade, quilometragem, umidade)

char exibicao; //será incrementado para realizar o controle do que será exibido

int statusViagem = 0;
int posicao = 800;

void BtnSelecPressed(){        //função utilizada para algumas configurações
    switch (exibicao){          //se tiver sendo exibindo a quilometragem
        case 0:
            quilometragem = 0;  //zera a quilometragem
            break;
        
        case 5:                 //se tiver sendo exibido a opçao de alterar status da viagem
            statusViagem++;
            lcd.printf("Status: %d", statusViagem);
            
            if(statusViagem >= 3){
                statusViagem = 0;
            }
            break;
        
        case 6:                 //se tiver sendo exibida a opçao de marcador 
            lcd.printf("Marcado em %d", posicao);
            break;
            
        default:
            lcd.printf("Exibicao: %d", exibicao);
    }
   
}

void BtnFncPressed(){ //função utilizada para indicar o que deve ser exibido no display (velocidade, quilometragem, umidade)
    lcd.cls();
    lcd.locate(3,3);
    
    exibicao++;
    
    if(exibicao >= 7){
        exibicao = 0;  //zera exibicao pra não passar das opções disponíveis
    }

    /*
    exibicao = 0 -> quilometragem
    exibicao = 1 -> velocidade instantanea
    exibicao = 2 -> velocidade media
    exibicao = 3 -> temperatura 
    exibicao = 4 -> umidade
    exibicao = 5 -> inicia/finaliza ida/volta ao pressionar o botao config
    exibicao = 6 -> insere marcador com o botao config
    */

    switch(exibicao){
        case 0:
            lcd.printf("Quilometragem");
            printf("Quilometragem");
            break;

        case 1:
            lcd.printf("Velocidade inst.");
            printf("Velocidade inst.");
            break;

        case 2:
            lcd.printf("Velocidade media");
            printf("Velocidade media");
            break;


        case 3:
            lcd.printf("Temperatura");
            printf("Temperatura");
            break;


        case 4:
             lcd.printf("Umidade");
             printf("Umidade");
            break;


        case 5:
            lcd.printf("Status viagem");
            printf("Alterar status viagem");
            break;

        case 6:
            lcd.printf("Marcadores");
            printf("Marcadores");
            break;
        
        default:
            exibicao = 0;

    }


    
   
}

/*============================== Função principal ==============*/


int main() {
    exibicao = 0;
    printf("Hello world!\n");
    
    lcd.printf("Quilometragem");
    
        btnFuncao.fall(&BtnSelecPressed);   //interrupção chamada sempre que o botão pra selecionar função for pressionado
        btnConfig.fall(&BtnFncPressed);  //interrupção chamada para zerar a quilometragem
    
    wait_ms(osWaitForever);
}