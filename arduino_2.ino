/* 
ARDUINO ESCRAVO
----------------------------------------------------------------------------            

                                 I2C NETWORK
 Arduino UNO 1 | PINO A4 SDA <---|-------------> SDA PINO A4 | Arduino UNO 2
                 PINO A5 SCL <---|--|----------> SCL PINO A5 
                                 |  |
                                 Pull up 5V - 4K7
*/                           

#include <Wire.h>                                                               //Biblioteca I2C necessária para fazer a comunicação
#include <Ultrasonic.h>

Ultrasonic ultrassom(8,7);                                                      //Define o nome do sensor(ultrassom) - trig(8) | echo(7) respectivamente

#define ENDERECO_DESTE_ARDUINO_NA_REDE 11                                       //Define o endereço deste escravo na rede

int dado_recebido = 0;                                                          //Variável que armazena o valor do dados que será enviado
int dado_a_ser_enviado = 0;                                                     //Define o endereço do primeiro arduino escravo
int distancia;                                                                  //Variável que armazena a distância do objeto ao sensor

void setup()  //Inicia os ajustes iniciais
{
    Wire.begin(ENDERECO_DESTE_ARDUINO_NA_REDE);                                 //Inicia a comunicação I2C
    Serial.begin(9600);                                                         //Ajusta o baud rate da comunicação com o monitor serial
    Serial.println("--> DEBUG DE SINAIS RECEBIDOS PELO ESCRAVO");               //Envia para o monitor um label titulo constante
    delay(1000);                                                                //Aguarda 1 segundo para iniciar o laço loop
    Wire.onRequest(requestEvents);                                              //Inicia a interrupção para responder pergunta do mestre
}

void loop() {   //Inicia o Loop infinito
                                                                  
}

//FUNÇÕES DE INTERRUPÇÃO LIGADOS A COMUNICAÇÃO I2C

void requestEvents()                                                            //Interrupção para responder a uma pergunta do mestre
{
 distancia = ultrassom.Ranging(CM);                                             //Faz a medida de distância
 Serial.println(F("--> FOI RECEBIDA UMA REQUISIÇÃO DE DADOS DO MESTE"));        //Envia para o monitor um label titulo constante
 Serial.print(F("DISTÂNCIA ENVIADA PARA O MESTRE : "));                         //Envia para o monitor um label titulo constante
 Serial.println(distancia);                                                     //Envia para o monitor serial o dados que será enviado ao mestre
 Wire.write(distancia);                                                         //Envia a informação contida na variável "dado_a_ser_enviado"

}
