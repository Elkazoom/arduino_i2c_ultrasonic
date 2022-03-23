###################################################################
###############	    ARDUINO MASTER TESTE       ####################
###################################################################

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

    //CÓDIGO PARA REQUISITAR UM VALOR DO MÓDULO ESCRAVO
    
    Wire.requestFrom(SLAVE1_ADDRESS, 1);                                  //Requisita do escravo locado no endereço 11 o valor a ser enviado
    dado_recebido = Wire.read();                                          //Faz a leitura do valor enviado
    Serial.print(F("recieved value : "));                                 //Envia para o monitor serial o valor recebido do escravo no endereço "11"
    Serial.println(dado_recebido);                                        //Envia para o monitor o dado recebido
    
    //CÓDIGO PARA ENVIAR UMA INFORMAÇÃO AO MÓDULO ESCRAVO

    Wire.beginTransmission(SLAVE1_ADDRESS);                               //Aponta para os escravo da rede que irá receber a transmissão
    Wire.write(dado_a_ser_enviado);                                       //Envia a informação numéria "12"
    Serial.print(F("Valor enviado para o escravo : "));                   //Envia para o monitor um label titulo constante
    Serial.println(dado_a_ser_enviado);                                   //Envia para o monitor serial o dados recebido 
    Wire.endTransmission();                                               //Finaliza o envio das inforção 
    Serial.print(" ");                                                    //Envia para o monitor uma linha vazia
    
    //VERIFICA SE O CÓDIGO ENVIADO ANTERIORMENTE CHEGOU AO ESCRAVO
 
    Wire.requestFrom(SLAVE1_ADDRESS, 1);                                  //Requisita do escravo locado no endereço 11 o valor a ser enviado
    dado_recebido = Wire.read();                                          //Faz a leitura do valor enviado pelo escravo
    Serial.print(F(" Valor recebido do escravo : "));                     //Envia para o monitor serial o valor recebido do escravo no endereço "11"
    Serial.println(dado_recebido);                                        //Envia para o monitor o dado recebido
    
 delay(100);                                                              //Aguarda para o envio para iniciar o novo loop
}

###################################################################
###############	   ARDUINO ESCRAVO TESTE	###################
###################################################################

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

#define ENDERECO_DESTE_ARDUINO_NA_REDE 11                                       //Define o endereço deste escravo na rede

int dado_recebido = 0;                                                          //Variável que armazena o valor do dados que será enviado
int dado_a_ser_enviado = 0;                                                     //Define o endereço do primeiro arduino escravo

void setup()  //Inicia os ajustes iniciais
{
    Wire.begin(ENDERECO_DESTE_ARDUINO_NA_REDE);                                 //Inicia a comunicação I2C
    Serial.begin(9600);                                                         //Ajusta o baud rate da comunicação com o monitor serial
    Serial.println("--> DEBUG DE SINAIS RECEBIDOS PELO ESCRAVO");               //Envia para o monitor um label titulo constante
    delay(1000);                                                                //Aguarda 1 segundo para iniciar o laço loop
    Wire.onRequest(requestEvents);                                              //Inicia a interrupção para responder pergunta do mestre
    Wire.onReceive(receiveEvents);                                              //Inicia a interrupção para receber um dado novo do mestre
}

void loop() {   //Inicia o Loop infinito
  
  

}

//FUNÇÕES DE INTERRUPÇÃO LIGADOS A COMUNICAÇÃO I2C

void requestEvents()                                                            //Interrupção para responder a uma pergunta do mestre
{
 Serial.println(F("--> FOI RECEBIDA UMA REQUISIÇÃO DE DADOS DO MESTE"));        //Envia para o monitor um label titulo constante
 Serial.print(F("Valor enviado pelo mestre : "));                               //Envia para o monitor um label titulo constante
 Serial.println(dado_a_ser_enviado);                                            //Envia para o monitor serial o dados que será enviado ao mestre
 Wire.write(dado_a_ser_enviado);                                                //Envia a informação contida na variável "dado_a_ser_enviado"
}

void receiveEvents(int numero_de_bytes_recebido)                                //Interrupção para receber um dado enviado pelo mestre
{
 Serial.println(F("--> FOI RECEBIDO UM NOVO DADO ENVIADO PELO MESTRE"));        //Envia para o monitor um label titulo constante
 dado_recebido = Wire.read();                                                   //Faz a leitura do valor enviado pelo mestre
 Serial.print(numero_de_bytes_recebido);                                        //Envia para o monitor a quantidade de dados recebidos           
 Serial.println(F(" byte(s) Recebido"));                                        //Envia para o monitor um label titulo constante
 Serial.print(F("Valor Recebido : "));                                          //Envia para o monitor um label titulo constante
 Serial.println(dado_recebido);                                                 //Envia para o monitor o dado recebido do mestre
 dado_a_ser_enviado = (dado_recebido+1);                                        //Atualiza a variável "dado recebido" para ser enviado novamente durante a interrupção "requestEvents"
}

###################################################################
###############	   ARDUINO MASTER ULTRASOM	###################
###################################################################

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
    
 delay(500);                                                              //Aguarda para o envio para iniciar o novo loop
}


###################################################################
###############	   ARDUINO ESCRAVO ULTRASOM	###################
###################################################################

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