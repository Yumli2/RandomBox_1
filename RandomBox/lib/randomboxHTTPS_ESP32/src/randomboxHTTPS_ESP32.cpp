#include "randomboxHTTPS_ESP32.h"
/*
 * Construtor
 */
BOX::BOX(char* token_LojaIntegrada, char* keyApli) {
    _token_LojaIntegrada = token_LojaIntegrada;
    _keyApli = keyApli;
}


bool BOX::send(char * _Npedido)
{
  bool retorno = true;
    if( (wifiMulti.run() == WL_CONNECTED) ) {//se estiver conectado ->
		String bdata_Send = "";
		bdata_Send += HTTPSERVER_Loja_Integrada; //br/v1/(aqui fica as instruções)?format
		bdata_Send += "situacao/";
		bdata_Send += "pedido/";
		bdata_Send += _Npedido;
		bdata_Send += "?format=json&chave_api=";
		bdata_Send += _token_LojaIntegrada;
		bdata_Send += "&chave_aplicacao=";
		bdata_Send += _keyApli;
		#if DEBUG
			vPrintString("Montei http: ");
			vPrintString(&bdata_Send[0]);
		#endif
 //=========================================================================================================================================
		HTTPClient http_Send_Put;
		http_Send_Put.begin( bdata_Send, ca ); //aqui é apenas para estabelecer a conexão inical
		http_Send_Put.addHeader( "Content-Type", "application/json" );
		http_Send_Put.addHeader( "Connection", "close" );
		uint16_t httpCode_PUT = http_Send_Put.PUT(c[0]);//Envia o Json como se fosse no body
    http_Send_Put.end();
//=========================================================================================================================================
		vTaskDelay( 1000 / portTICK_PERIOD_MS );
//=========================================================================================================================================
		HTTPClient http_Send_Get;
		http_Send_Get.begin( bdata_Send, ca ); //aqui é apenas para estabelecer a conexão inical
		http_Send_Get.addHeader( "Content-Type", "application/json" );
		http_Send_Get.addHeader( "Connection", "close" );
		uint16_t httpCode_GET = http_Send_Get.GET();//Envia o Json como se fosse no body
			#if DEBUG
				vPrintStringAndInteger("HTTP_CODE_RETURN_PUT:", httpCode_PUT);
				vPrintStringAndInteger("HTTP_CODE_RETURN_GET:", httpCode_GET);
			#endif
			if( (httpCode_PUT > 0) && (httpCode_GET > 0) ) //Houve algum tipo de retorno, ai vamos saber que retorno foi esse
			{
			if( (httpCode_PUT == HTTP_CODE_OK) && (httpCode_PUT == HTTP_CODE_OK) ) //Code 200
			{
                String payload_2 = http_Send_Get.getString();
				#if DEBUG
					//if( payload_2.length() > 1 ) vPrintTwoStrings("Tamanho do Payload",&String(payload_2.length())[0]);
					  //vPrintTwoStrings( "Payload: ",payload_2.c_str());
				#endif
        if(autentic)
				{
	/*deletar*/	 	cJSON *json_situcao_send = cJSON_Parse(payload_2.c_str());
					if( json_situcao_send != NULL )
						{
							vPrintString( "Objeto Situacao de Entrega criado." );
							cJSON *codigo_send = cJSON_GetObjectItem((cJSON*)json_situcao_send,"codigo");//guarda a situação do pagamento
							if(codigo_send != NULL)
							{
								vPrintString( "Codigo SEND encontrado." );
								vPrintTwoStrings("codigo:",(char*)codigo_send->valuestring);
							}
							cJSON *id_send = cJSON_GetObjectItem((cJSON*)json_situcao_send,"id");
							if(id_send != NULL)
							{
								vPrintString( "id SEND encontrado." );
								vPrintStringAndInteger("id de pagamento: ",id_send->valueint);//"pedido_pago"= 4 "pedido_entregue"= 14
							}
							if((int)id_send->valueint == id_[1])
							{
								vPrintString( "Seu Pedido foi alterado para:");
								vPrintString( "--Pedido entregue--");
							}
							else
							{
								retorno=false;
								vPrintString( "Erro de comunicação!");
								vPrintString( "Tente novamente!");
							}

						}
/*deletado*/		cJSON_Delete(json_situcao_send);
				}
			 retorno==true?retorno:retorno=false;
            }
		}
		else
		{
          #if DEBUG
              vPrintTwoStrings( "[HTTP] POST.. falha, error: %s\n", http_Send_Get.errorToString(httpCode_PUT).c_str() );
		  #endif
		}

		http_Send_Get.end();
	}
	return retorno;
}

bool BOX::read( char * _Npedido, char* _cpf )
{
    bool retorno = false;
	//vPrintString( &String(Nsku)[0]);
    if( (wifiMulti.run() == WL_CONNECTED) )
	{
	  String bdata = "";
	  bdata += HTTPSERVER_Loja_Integrada; //br/v1/(aqui fica as instruções)?format
	  bdata += "pedido/";
	  bdata += _Npedido;
    bdata += "/?format=json&chave_api=";
	  bdata += _token_LojaIntegrada;
	  bdata += "&chave_aplicacao=";
    bdata += _keyApli;
    vPrintString(bdata.c_str());

    HTTPClient http;
    http.begin( bdata, ca );
    http.addHeader( "Content-Type", "application/json" );
    http.addHeader( "Connection", "close" );
    uint16_t httpCode = http.GET();
    if( httpCode > 0 )
    {
			vPrintStringAndInteger("HTTP_CODE_RETURN:", httpCode);
		    //A partir daqui é uma aplicação no Json //Yuri Lima // Aula 23 ajudou muito
        //======================================================================================================
      if( httpCode == HTTP_CODE_OK )
		  {
        String payload = http.getString();
        #if DEBUG
				if( payload.length() > 1 ) vPrintTwoStrings("Tamanho do Payload",&String(payload.length())[0]);
					  //vPrintTwoStrings( "Payload",payload.c_str());
				#endif
        vPrintString("Inicio Etapa cJSON");
//======================================================================================================
/*deletar*/cJSON *json_cliente = cJSON_Parse(payload.c_str()); //faz alocação dinamica para depois tem que deletar para nao fragmentar a memoria
        if( json_cliente != NULL ) //ve se foi alocado
        {
				  vPrintString( "Objeto cliente criado." );
				  cJSON *cliente = cJSON_GetObjectItem(json_cliente ,"cliente");//Dentro do objeto cliente puxo todos os dados para ser filtrado
				  if(cliente != NULL)
					{
					  vPrintString( "Objeto Cliente encontrado." );
					  cJSON *cpf = cJSON_GetObjectItem((cJSON*)cliente,"cpf");
					  if(cpf != NULL)
					  {
						  vPrintString( "Cpf encontrado." );
						  vPrintTwoStrings("Cpf:",(char*)cpf->valuestring);
					  }
            //Tem que consertar ainda -->
						/*cJSON *cnpj = cJSON_GetObjectItem((cJSON*)cliente,"cnpj");
						if(cnpj != NULL)
						{
						vPrintString( "Cnpj encontrado." );
						//vPrintTwoStrings("Cnpj:",(char*)cnpj->valuestring);
						} <-- */
            cJSON *nome = cJSON_GetObjectItem((cJSON*)cliente,"nome");
						if(nome != NULL)
						{
							vPrintString( "nome encontrado." );
							vPrintTwoStrings("Nome: ",(char*)nome->valuestring);
						}
						autentic=Verifica_1(nome->valuestring,cpf->valuestring, _cpf);//essa funação faz a comparação se for igua retorna 0
						vPrintTwoStrings("CPF validado:",autentic==0?"OK":"CPF Invalido");
						autentic==0?autentic=true:autentic=false;//se for zero inverte a situação do autentic recebendo verdadeiro, entao entra na condição de cpf valido
					}
				}
	/*deletado*/cJSON_Delete(json_cliente);
//======================================================================================================
				if(autentic)
				{
/*deletar*/cJSON *json_situcao = cJSON_Parse(payload.c_str());
					if( json_situcao != NULL )
						{
							vPrintString( "Objeto Situacao criado." );
							cJSON *situacao = cJSON_GetObjectItem(json_situcao,"situacao");//Dentro do objeto situação puxo todos os dados para ser filtrado
							if(situacao != NULL)
							{
								vPrintString( "Objeto Situacao encontrado." );
								cJSON *codigo = cJSON_GetObjectItem((cJSON*)situacao,"codigo");//guarda a situação do pagamento
								if(codigo != NULL)
								{
									vPrintString( "Codigo encontrado." );
									vPrintTwoStrings("codigo:",(char*)codigo->valuestring);
								}
								cJSON *id = cJSON_GetObjectItem((cJSON*)situacao,"id");
								if(id != NULL)
								{
									vPrintString( "id encontrado." );
									vPrintStringAndInteger("id de pagamento: ",id->valueint);//"pedido_pago"= 4 "pedido_entregue"= 14
								}
								if((uint16_t) id->valueint == id_[0])
								{
									vPrintString( "Pedido ok");
									//Aqui autentic continua verdadeiro
								}
								else if((uint16_t) id->valueint == id_[1])
								{
									autentic=false;
									vPrintString( "Seu Pedido ja foi entregue ");
								}
								else
								{
									autentic=false;
									vPrintString( "Erro de status");
								}
							}
						}
/*deletado*/		cJSON_Delete(json_situcao);
				 }
//======================================================================================================
				 if(autentic)
				 {
/*deletar*/cJSON *json_itens = cJSON_Parse(payload.c_str());
					if( json_itens != NULL )
					{
						byte i;
						vPrintString( "Objeto Itens criado." );
						cJSON *itens = cJSON_GetObjectItem(json_itens,"itens");//Dentro do objeto itens puxo todos os dados para ser filtrado
						if(itens != NULL)
						{
							vPrintString( "Objeto Itens encontrado." );
							for (i = 0 ; i < cJSON_GetArraySize(itens) ; i++)
							{
								cJSON * subitem = cJSON_GetArrayItem(itens, i);
								cJSON* quantidade = cJSON_GetObjectItem(subitem, "quantidade");
								vPrintTwoStrings("Quantidade: ",(char*)quantidade->valuestring);
								cJSON* sku = cJSON_GetObjectItem(subitem, "sku");
								vPrintTwoStrings("SKU: ",(char*)sku->valuestring);
							}
						}//aqui passo a fução que vai popular as variaveis dentro das task's que chamar no periodo correto.
					}
	/*deletado*/	cJSON_Delete(json_itens);
				 }
      }
    }
		else
		{
		#if DEBUG
			vPrintTwoStrings( "[HTTP] GET.. falha, error: %s\n", http.errorToString(httpCode).c_str() );
			#endif
		}
		http.end();
    }
	//Vai pedir para alterar o status do pedido para Entregue
	if(autentic) autentic==send(_Npedido)?retorno = true:retorno=false;//se esse cara retornar falso então não deu certo mudar o status da loja integrada e nao vai liberar os pedidos.
  return retorno;
}
bool BOX::Verifica_1(char* nome_do_cliente, char* cpf_GET, char* cpf_Digitado)//bate o CPF e recebe o nome do cliente para aparcer no display
{
	bool retorno=false;
    retorno=strcmp(cpf_GET,cpf_Digitado);//retorna 0 de for igual
	return retorno;
}
int BOX::strcmp(const char *cs, const char *ct)//Faz a compração de Strings
{
	unsigned char c1, c2;
	int res = 0;

	do {
		c1 = *cs++;
		c2 = *ct++;
		res = c1 - c2;
		if (res)
			break;
	} while (c1);
	return res;
}
bool BOX::validCpf(const char *_cpf)
{
  int v[12];
  bool flag=false, flag_=true;
  const char* Cpf_Invalido[11] = {"00000000000","11111111111","22222222222","33333333333","44444444444","66666666666", "77777777777","88888888888","99999999999","12345678912"};//555.555.555-55 é para teste de comunicação

  for(int x=0; x < 10; x++)
    if( flag_= !strcmp( Cpf_Invalido[x] , _cpf )  )//se retornar 1 é pq é diferente (valido)
    {
      flag=true;
    }
  if(flag) return false;
  if(!flag)
  {
    for(int x=0; x <= 10; x++)
    {
      v[x] = _cpf[x]-48;
    }
    //=============================================================================================================================================
    // Primeira etapa
    v[11] =  (v[0] * 10) + (v[1] * 9) + (v[2] * 8) + (v[3] * 7) + (v[4] * 6) + (v[5] * 5) + (v[6] * 4) + (v[7] * 3) + (v[8] * 2);
    v[11] = (v[11] /0.1);
    v[11] = (v[11] % 11);
    v[11] == 10 ? v[11] = 0 : v[11];

    //=============================================================================================================================================
    // Segunda etapa
    v[12] =  (v[0] * 11) + (v[1] * 10) + (v[2] * 9) + (v[3] * 8) + (v[4] * 7) + (v[5] * 6) + (v[6] * 5) + (v[7] * 4) + (v[8] * 3) + (v[9] * 2);
    v[12] = (v[12] /0.1);
    v[12] = (v[12] % 11);
    v[12] == 10 ? v[12] = 0 : v[12];
    vPrintint(v[9]);vPrintint(v[11]);vPrintint(v[10]);vPrintint(v[12]);
    if( ( v[11]==v[9] ) && ( v[12]== v[10] ) ) return true;
  }
}
bool BOX::wifiConnection(char* ssid, char* pass)
{
    wifiMulti.addAP(ssid, pass);

    if (wifiMulti.run() == WL_CONNECTED) {
       return true;
    } else {
        return false;
    }
}
void BOX::vPrintString( const char *pcString )
{
  taskENTER_CRITICAL( &myMutex );
  {
    Serial.println( (char*)pcString );
  }
  taskEXIT_CRITICAL( &myMutex );
}
void BOX::vPrintint( int pcInt )//fiz modificação
{
  taskENTER_CRITICAL( &myMutex );
  {
    Serial.println( pcInt );
  }
  taskEXIT_CRITICAL( &myMutex );
}
void BOX::vPrintStringAndFloat( const char *pcString, float ulValue )
{
  taskENTER_CRITICAL( &myMutex );
  {
    char buffer [50];
    sprintf( buffer, "%s %.4f", pcString, ulValue );
    Serial.println( (char*)buffer );
  }
  taskEXIT_CRITICAL( &myMutex );
}
void BOX::vPrintStringAndInteger( const char *pcString, uint32_t ulValue )
{
  taskENTER_CRITICAL( &myMutex );
  {
    char buffer [50];
    sprintf( buffer, "%s %lu", pcString, ulValue );//%lu
    Serial.println( (char*)buffer );
  }
  taskEXIT_CRITICAL( &myMutex );
}
void BOX::vPrintTwoStrings(const char *pcString1, const char *pcString2)
{
  taskENTER_CRITICAL( &myMutex  );
  {
    char buffer [500];
    sprintf(buffer, "%s %s", pcString1, pcString2);
    Serial.println( (char*)buffer );
  }
  taskEXIT_CRITICAL( &myMutex );
}
