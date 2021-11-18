#include "mbed.h"

/*==================================== Definições ===============================*/
DigitalIn btnAcelerador(p13);   //define o botão conectado ao pino 13 (Acelerador) como entrada
DigitalIn btnFreio(p12);        //define o botão conectado ao pino 13 (Freio) como entrada

PwmOut ledInjecao(p23);         //define o pino 23 como saída PWM

Ticker timerPedais;             //interrupção que será chamada repetidamente pra ler os pedais

/*================================== Leitura dos pedais ===================================================================*/

void LeituraPedais(){                   //função que será chamada a cada 0.5 s pra verificar o estado dos pedais
    if (btnFreio.read()){               //verifica se o freio foi pressionado
        ledInjecao = ledInjecao - 0.5;  //decrementa o duty cycle em 50%
    }

    else if (btnAcelerador.read()){     //se não estiver pressionado, verifica se o acelerador foi pressionado
        ledInjecao = ledInjecao + 0.1;  //incrementa o duty cycle
    }
    
    else{                               //se nenhum tiver sido pressionado
        ledInjecao = ledInjecao - 0.1;
        //espera 1s
        wait(0.5f);                     //como a funçao é chamada a cada 0.5 s, então se não tiver nada pressionado espera 0.5 s
    }
    
    //impede que o duty cycle fique negativo
    if(ledInjecao <= 0){
        ledInjecao = 0;
    }

    //impede que o duty cycle fique acima de 100%
    if(ledInjecao >= 1){
        ledInjecao = 1;
    }
    
    printf("\nDuty cycle injecao: %f \n", ledInjecao);
    
}

/*============================== Função principal ==============*/


int main() {
    ledInjecao.period_ms(20);                   //define o período do PWM do led de injeção como 20 ms 
    
    timerPedais.attach(&LeituraPedais, 0.5f);   //chama a função que le o estado dos pedais a cada 0.5s
    
    wait_ms(osWaitForever);
}