# RandomBox_1
Integração API Loja Integrada + FreeRTO's + ESP32
//Autor da Matriz do Codigo: Microgenios
//Autor das modificações gerais: Yuri lima, contato para duvidas whatsapp: 85-98769.9288
//O.B.S. Importante: Ainda estou refatorando o codigo, portanto sem mimimi... Ta achando ruim, procura outro codigo na web.

Devido a erros de I2C com o uso das interrupções usadas pelo teclado TTP229, problema esse muito comentado em vários foruns, nos Git's, pelos desenvolvedores.

https://github.com/espressif/arduino-esp32/issues/839
https://github.com/espressif/arduino-esp32/issues/1071
https://github.com/espressif/arduino-esp32/issues/834
Dentre outros....

Tive problemas na criação de task's, para o uso do Display LCD que tbm foi usado como I2C, por esse motivo e por estar conhecendo as ferramentas do FreeRTO's, tive que criar artificios para usar apenas 2 task, 1 exclusiva para o Touch e outra geral. Tentei por várias vezes criar uma task exclusiva para o Display LCD, mas ao criar,o comportamento era instavel, sempre ocorria erros de timeout I2C no barramento dele. Problema que nos foruns estão tentando acertar.

https://github.com/espressif/esp-idf/issues/1503
https://github.com/espressif/esp-idf/issues/680
https://github.com/espressif/arduino-esp32/issues/811

Caso alguem queira contrbnuir com as melhorias, agradeço.

O resto das implementações, é o basicão com a manipulação do Jason e os Certificados de sua Loja Integrada. 

Para conseguir a sua Chava de Aplicação, você deve abrir uma solicitação pelo suporte da loja. 
O Token, é gerado -> Painel -> na aba de configurações. 
