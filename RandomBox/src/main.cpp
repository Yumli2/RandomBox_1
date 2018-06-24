//Autor principal do Codigo: Microgenios
//Autor das modificações gerais: Yuri lima, contato para duvidas whatsapp: 85-98769.9288
//O.B.S. Importante: Ainda estou refatorando o codigo, portanto sem mimimi... Ta achando ruim, procura outro cod. na web, ok.
/*
Devido a erros de I2C com o uso das interrupções usadas pelo teclado TTP229, problema esse muito comentado nos Git's, pelos desenvolvedores,
tive problemas na criação de task's, para o uso do Display LCD que tbm foi usado como I2C, por esse motivo, tive que criar artificios para
usar apenas 1 task.
Caso alguem queira contrbnuir com as melhorias, agradeço.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>
//=====================================
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
//=====================================
#include "Arduino.h"
#include "LiquidCrystal_I2C.h"
//=====================================
#include "WiFi.h"
#include "WiFiMulti.h"
#include "HTTPClient.h"
//=====================================
#include "driver/gpio.h"
#include "driver/adc.h"
#include <driver/i2c.h>
#include "esp_system.h"
#include "esp_adc_cal.h"
#include "esp_err.h"
#include "esp_log.h"
#include "sdkconfig.h"
//=====================================
#include "randomboxHTTPS_ESP32.h"
//=====================================
#include "touchpanel.h"
//=====================================
//=====================================
#define debug 1
//Prototipos das funçoes
void prvSetupHardware( void );
void Task_Geral( void *pvParameters );
void vTask2( void *pvParameters );
void vTask1_1( void *pvParameters );
void touch_task(void *pvParameters);
//=====================================
//Difinição de Cores a utilizar
#define CORE_0 0
#define CORE_1 1  //OU tskNO_AFFINITY
//=====================================
//Criação de Filas
QueueHandle_t xQueue_typed, xQueue_Npedido, xQueue_Ncpf;
SemaphoreHandle_t xMutex;
//=====================================
//Informações de Conexões Wifi//ClienteGenio!12345
#define WIFISSID "Homefi2"
#define PASSWORD "48291110"
//=====================================
//Dados Loja Integrada
#define TOKEN_BOX  "10651a74b9171bab9bf9" //TOKEN_Loja_Integrada
#define keyApli  "50d155b7-4425-43e2-9d81-5bfee116b9b8"  //Chave de aplicação
#define evento  "pedido"  //nome do evento
//=====================================
//Display LCD
#define _SDA 21 //verde
#define _SCL 22 //amarelo
#define colunas 20
#define linhas 4
LiquidCrystal_I2C lcd(0x3C, colunas, linhas);//LCD 16x2
//=====================================//=====================================
//Teste de I2C
char tag[] = "i2cscanner";
//=====================================
//Instanciar o construtores
BOX box_client((char*)TOKEN_BOX, (char*)keyApli);
//=====================================
//Pinos de saida
const byte bob_1 = 25;
String  Ncpf, Npedido;

//=============================================================================
void prvSetupHardware()
{
  portMUX_TYPE myMutex_2 = portMUX_INITIALIZER_UNLOCKED;
  #if debug
    Serial.begin( 115200 );
    #endif
    lcd.begin(_SDA,_SCL);
    lcd.setBacklight(true);

 //=====================================
 //Status da conexão realizada
 uint8_t t = 1;
 loop:
  //lcd.setCursor(5,1); se acionar inicia os problemas de I2C com uso do display, é instavel, as vezes funciona e outras não.
  //lcd.printf("Conexao_%d", t);
  #if debug
      box_client.vPrintStringAndInteger( "[SETUP] Tentativa_: ",t);
  #endif
  t++;
  vTaskDelay( 1500 / portTICK_PERIOD_MS );

 if(!(box_client.wifiConnection((char*)WIFISSID, (char*)PASSWORD) ) )
 {
    goto loop;
  }

 //=====================================
 //Status da conexão realizada
 taskENTER_CRITICAL( &myMutex_2 );
 {
   /* Print chip information */
   esp_chip_info_t chip_info;
   esp_chip_info(&chip_info);
   printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
         chip_info.cores,
         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

   printf("silicon revision %d, ", chip_info.revision);
   //lcd.clear();
   //lcd.setCursor(5,0);
   //lcd.print("RandomBox");
   //lcd.setCursor(0,2);
   ///lcd.print("WiFi connected.");
   //lcd.setCursor(0,3);
   //lcd.print(WiFi.localIP());
   //vTaskDelay( 5000 / portTICK_PERIOD_MS );

    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("MAC address: ");
    Serial.println(WiFi.macAddress());
    fflush(stdout);
  }
  taskEXIT_CRITICAL( &myMutex_2 );
 //=====================================
 //Pinos de saida
  pinMode(bob_1, OUTPUT);
}

void touch_task(void *pvParameters) {
  //criei esse semaforo, mais ficou pendente avaliar a real necessidade, visto os problemas nas interrupções do I2C, PENDENTE analisar.
  xSemaphoreTake(xMutex,portMAX_DELAY);
  BaseType_t xStatus;
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  TOUCHPANEL touch(GPIO_NUM_23, GPIO_NUM_19);//SCL e SDA //ttp229 touch
	uint8_t i;
	uint16_t bitmap;
	while(1)
  {
		if(xQueueReceive(touch.queue_touch, &bitmap, portMAX_DELAY))
			for(i = 0; i < 16; i++)
				if(bitmap & (1 << i))
        {
          //box_client.vPrintStringAndInteger("touch_task: ", i );
          xStatus = xQueueSend( xQueue_typed, &i, portMAX_DELAY);
          if( xStatus != pdPASS )
          {
          }
        }
	}
  static bool _size = true;
  if(_size)
  {
    uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
    box_client.vPrintStringAndInteger( "touch_task Size: ", uxHighWaterMark );
    _size=!_size;
  }
   xSemaphoreGive(xMutex);
}

void Task_Geral( void *pvParameters )
{
  //=======================================================
  //BaseType_t xStatus;
  //Verificar o tamanho de memoria para alocação
  UBaseType_t uxHighWaterMark;
  uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
  //=======================================================
  uint8_t  i, tam=0;
  char num[] = {'0','1','2','3','4','5','6','7','8','9','\0'};
  char _typed[16], _buffer[2];//tive que fazer assim, tentei usar ponteiros, mais sempre que uso, apresenta um erro para I2C do displayLCD
  bool flag = true, flag_cpf = false, cpf_e = false, _size = true;

  for(;;)
  {
    lcd.setCursor(5,0);
    lcd.print("RandomBox");
    lcd.setCursor(0,1);
    lcd.print("N.Order: ");
    lcd.setCursor(0,2);
    lcd.print("N.Cpf:");
    lcd.setCursor(0,3);
    lcd.print("Conf.Cpf:");
    lcd.display();
    if(!flag_cpf)
    {
      //lcd.noCursor();
      lcd.setCursor(8,1);
      lcd.cursor();
      lcd.print(_typed);
    }
    else
    {
      lcd.setCursor(8,1);
      lcd.print(Npedido);
      lcd.setCursor(7,2);
      lcd.print(_typed);
    }
    if(cpf_e)
    {
      lcd.setCursor(8,1);
      lcd.print(Npedido);
      lcd.setCursor(9,3);
      lcd.print(Ncpf);

      vTaskDelay(4000 / portTICK_PERIOD_MS );
      Npedido="";
      Ncpf="";
      //Limpa essas posições, pois o LCD clear ficou ineficiente. erro de stack devido a esses problemas com as interrupções do I2c
      lcd.setCursor(8,1);
      lcd.print("            ");
      lcd.setCursor(7,2);
      lcd.print("            ");
      lcd.setCursor(9,3);
      lcd.print("            ");
      //lcd.display();
      cpf_e = !cpf_e;
      flag_cpf = !flag_cpf;
      //lcd.clear();
    }
    if(xQueueReceive(xQueue_typed, &i, portMAX_DELAY))//portMAX_DELAY
    {
      sprintf(_buffer, "%d", i );//Tive que fazer isso por milhoes de teste feitos com outros meios e da erro na I2c
      box_client.vPrintStringAndInteger("Touch at button_1: ", i);
      //box_client.vPrintStringAndInteger("Touch at button_2: ", strcmp(_buffer,"14")!=0 );

      if( (strcmp(_buffer,"15")!=0) )
      {
        if(strcmp(_buffer,"12")==0)//condição que apaga os digitos
        {
            tam--;
            _typed[tam] = {};
            lcd.clear();
        }
        //box_client.vPrintTwoStrings("Touch at button_3: ", &_buffer[0]);
        for(uint8_t x=0;x<=9;x++)
        {
          if(i==x)
          {
            _typed[tam]=num[x];
            tam++;//posso saber quantos numeros foram digitados
            //box_client.vPrintTwoStrings("Touch at button_4: ", &_buffer[0]);
          }
        }
      }
      else
      {
        if(tam >0)//tam > para liberar o enter para escrever o CPF
        {
          flag_cpf = true;
            if(flag)
            {
              Npedido = String(_typed);
              flag=!flag;
              box_client.vPrintTwoStrings("Touch at Npedido_3: ", &Npedido[0]);
              box_client.vPrintTwoStrings("Touch at Tamanho_4: ", &String(tam)[0]);
              //Npedido="";//temporario
            }
            else
            {
              //flag_cpf=false;
              Ncpf = String(_typed);
              //Ncpf = String("00000000000");
              if(Ncpf.length() == 11 && box_client.validCpf(&Ncpf[0]))
              {
                cpf_e=true;
                bool retorno = box_client.read(&Npedido[0],&Ncpf[0]);
                box_client.vPrintTwoStrings("Retorno da função read: ",&String(retorno)[0]);
                //Aqui é preciso fazer um tratamento de erro. Para mostrar o erro correto que vem no retorno.
                retorno ? Ncpf = String("Validado") : Ncpf = String("Erro...");
              }
              else
              {
                cpf_e=true;
                Ncpf="Invalido";
              }
              flag=!flag;
              box_client.vPrintTwoStrings("Numero do Ncpf: ", &Ncpf[0]);
              box_client.vPrintTwoStrings("Tamanho_Digitado: ", &String(tam)[0]);
            }
            tam=0;
            memset(_typed, 0, sizeof(_typed));//zerar array
            _size = true;
          }
        }
      }
    // --------------------------------------------------------------------
      if(_size)
      {
        uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
        box_client.vPrintStringAndInteger( "Task_Geral Stack Size: ", uxHighWaterMark );
        _size=!_size;

      }
      vTaskDelay( 50 / portTICK_PERIOD_MS );
  }
}

void task_i2cscanner(void *ignore) {
	ESP_LOGD(tag, ">> i2cScanner");
	i2c_config_t conf;
	conf.mode = I2C_MODE_MASTER;
	conf.sda_io_num = GPIO_NUM_21;
	conf.scl_io_num = GPIO_NUM_22;
	conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
	conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
	conf.master.clk_speed = 100000;
	i2c_param_config(I2C_NUM_0, &conf);

	i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

	int i;
	esp_err_t espRc;
	printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
	printf("00:         ");
	for (i=3; i< 0x78; i++) {
		i2c_cmd_handle_t cmd = i2c_cmd_link_create();
		i2c_master_start(cmd);
		i2c_master_write_byte(cmd, (i << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
		i2c_master_stop(cmd);

		espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
		if (i%16 == 0) {
			printf("\n%.2x:", i);
		}
		if (espRc == 0) {
			printf(" %.2x", i);
		} else {
			printf(" --");
		}
		//ESP_LOGD(tag, "i=%d, rc=%d (0x%x)", i, espRc, espRc);
		i2c_cmd_link_delete(cmd);
	}
	printf("\n");
	vTaskDelete(NULL);
}


void setup() {
  gpio_install_isr_service(0);//TTP229 servio que gerencia as interrupções para os pinos de GPIO
  //interrupção para o teclado Touch http://esp-idf.readthedocs.io/en/latest/api-reference/peripherals/gpio.html
  //Criação das filas
  xQueue_typed = xQueueCreate( 1, sizeof(int));
  xQueue_Npedido = xQueueCreate( 10, sizeof(String));
  xQueue_Ncpf = xQueueCreate( 10, sizeof(String));
  if(xQueue_typed!= NULL && xQueue_Npedido != NULL && xQueue_Ncpf != NULL)
  {
    xTaskCreatePinnedToCore( Task_Geral, "Task_Geral", configMINIMAL_STACK_SIZE+18000, NULL, 4, NULL, CORE_0 );
    //xTaskCreatePinnedToCore( task_i2cscanner, "task_i2cscanner", configMINIMAL_STACK_SIZE+1500, NULL, 1, NULL, CORE_1 );
    //=================================================================================================
    xMutex = xSemaphoreCreateMutex();//tive que criar esse semaforo, para conter os erros de core
    if(xMutex != NULL)
    {
      xTaskCreate(&touch_task, "touchtask", 2048, NULL, 5, NULL);
    }
  }
  vTaskStartScheduler();//Inicia o planejador em tempo real. Não vai iniciar, a menos que haja RAM suficiente.
  prvSetupHardware();
}

void loop() {
  vTaskDelay( 100 / portTICK_PERIOD_MS );
}
