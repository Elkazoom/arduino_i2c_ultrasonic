/* 
ARDUINO MASTER
----------------------------------------------------------------------------            

                                 I2C NETWORK
 Arduino UNO 1 | PINO A4 SDA <---|-------------> SDA PINO A4 | Arduino UNO 2
                 PINO A5 SCL <---|--|----------> SCL PINO A5 
                                 |  |
                                 Pull up 5V - 4K7
*/                       

#include <Wire.h>                                                         //Biblioteca I2C necessária para fazer a comunicação

# define SLAVE1_ADDRESS 11                                                //Define o endereço do primeiro arduino escravo
# define SLAVE2_ADDRESS 12                                                //Define o endereço do segundo arduino escravo
# define SLAVE3_ADDRESS 13  

int dado_a_ser_enviado = 14;                                              //Variável que armazena o valor do dados que será enviado
int dado_recebido = 0;                                                    //Variável que armazena o valor do dado que será recebido

void setup()  //Inicia os ajustes iniciais
{
    Wire.begin();                                                         //Inicia a comunicação I2C
    Serial.begin(9600);                                                   //Ajusta o baud rate da comunicação com o monitor serial
    Serial.println(F("--> DEBUG DE SINAIS RECEBIDOS PELO MESTRE"));       //Envia para o monitor um label titulo constante
    delay(1000);                                                          //Aguarda 1 segundo para iniciar o laço loop
}

void loop()   //Inicia o Loop infinito
{

    //REQUISITA A DISTÂNCIA DO OBJETO
 
    Wire.requestFrom(SLAVE1_ADDRESS, 1);                                  //Requisita do escravo locado no endereço 11 o valor a ser enviado
    dado_recebido = Wire.read();                                          //Faz a leitura do valor enviado pelo escravo
    Serial.print(F(" Distancia do objeto : "));                           //Envia para o monitor serial o valor recebido do escravo no endereço "11"
    Serial.println(dado_recebido);                                        //Envia para o monitor o dado recebido
    
    delay(50);                                                            //Aguarda para o envio para iniciar o novo loop
}
