/*
VERSÃO API: 5.0 (10-01-2018)
AUTOR: FERNANDO SIMPLICIO
API PARA NODEMCU ESP32

Copyright (c) 2013-2016 Microgenios.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/
#ifndef _RANDOMBOX_HTTPS_H_
#define _RANDOMBOX_HTTPS_H_



#include <Arduino.h>
#include "cJSON.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <stdio.h>
#include <sys/reent.h>
#include <machine/ieeefp.h>
#include "_ansi.h"
#include <math.h>
#include <sys/string.h>
#include <stddef.h>
#include <sys/cdefs.h>
#include <sys/features.h>

#define HTTPSERVER_Loja_Integrada "https://api.awsli.com.br/v1/"
#define DEBUG true

class BOX {
 public:
	//==================================================================================
	//Construtor
  BOX(char* token_LojaIntegrada, char* keyApli=NULL);
    //==================================================================================
	//Funções para post(Send) e para fazer um GET(Read)
	bool send( char* _Npedido);
	bool read( char * _Npedido, char* _cpf );
	//==================================================================================
	//Funções que passa usuario e senha de conexão wifi
  bool wifiConnection(char *ssid, char *pass);
	//==================================================================================
	//Funções de escrita segura na serial
	void vPrintString( const char *pcString);
	void vPrintint( int pcInt);
	void vPrintStringAndFloat( const char *pcString, float ulValue );
	void vPrintStringAndInteger( const char *pcString, uint32_t ulValue );
	void vPrintTwoStrings(const char *pcString1, const char *pcString2);
	//==================================================================================
	//Funções para popular as variaveis  recebidas pelo Get(json)
	bool Verifica_1(char* _nome, char* cpf_, char* _cpf);
  bool validCpf(const char *_cpf);
  int strcmp(const char *cs, const char *ct);
	//==================================================================================
  //Id's de pagamento da Loja Integrada
	//"aguardando_pagamento"= 2
	//"em_producao"= 17
	//"pagamento_devolvido"= 7
	//"pagamento_em_analise"= 3
	//"pedido_chargeback"= 16
	//"pagamento_em_disputa"= 6
	//"pedido_cancelado"= 8
	//"pedido_efetuado"= 9
	//"pedido_em_separacao"= 15
	//"pedido_entregue"= 14
	//pedido_enviado"= 11
	//"pedido_pago"= 4
	//"pronto_para_retirada"= 13
	const char* c[2]={" {\"codigo\": \"pedido_entregue\"} ", " {\"codigo\":\"pedido_enviado\"} "};//aqui vc pode personalizar da forma como quiser
	const int id_[2]={4,14};
	bool autentic=false;


 private:

  char* _token_BOX;
	char* _token_LojaIntegrada;
	char* _keyApli;

  WiFiMulti wifiMulti;
	portMUX_TYPE myMutex = portMUX_INITIALIZER_UNLOCKED;

	const char* ca = \
  "-----BEGIN CERTIFICATE-----\n" \
  "MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \
  "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
  "DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \
  "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \
  "GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \
  "AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \
  "q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \
  "SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \
  "Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \
  "a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \
  "/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \
  "AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \
  "CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \
  "bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \
  "c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \
  "VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \
  "ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \
  "MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \
  "Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \
  "AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \
  "uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \
  "wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \
  "X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \
  "PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \
  "KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \
  "-----END CERTIFICATE-----\n";

};
#endif
/*
Informações do certificado:
Nome comum: COMODO RSA Validação de Domínio Servidor Seguro CA
Organização: COMODO CA Limited
Localidade: Salford
Estado: Greater Manchester
País: GB
Válido a partir de: 11 de fevereiro de 2014
Válido para: 11 de fevereiro de 2029
Emissor: COMODO RSA Autoridade de Certificação, COMODO CA Limited Escreva uma crítica de Comodo
Número de série: 2b2e6eead975366c148a6edba37c8c07*/
