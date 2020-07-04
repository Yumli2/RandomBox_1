<!-- Headings --> <!-- Strong --> <!-- Italics --> <!-- Blockquote --> <!-- Links --> <!-- UL --> <!-- OL --> <!-- Images --> <!-- Code Blocks --> <!-- Tables --> 
<!-- Task Lists -->

# RandomBox (Vending Machine)
> ### Integration: [API](https://lojaintegrada.docs.apiary.io/#reference) + [Loja Integrada](https://lojaintegrada.com.br/) + [FreeRTO's](https://www.freertos.org/) + [ESP32](https://www.espressif.com/en/products/socs/esp32/overview)

- The main objective of the project has the intention of providing resources for **Hardware developers** , as well as providing access to the most diverse development platform options such as the module family of [Espressif](https://www.espressif.com/en), [Arduino](https://www.arduino.cc/en/main/products), [STM32](https://www.st.com/content/st_com/en/support/learning/stm32-education/stm32-step-by-step.html), and various electronic components that every developer would like to have access to.

> ### How is RandomBox going to work?
- Flow process:
***I'm going to translate the flow process as soon as possible***
![](Images)
<img src="Images/FlowRandomBox1.png">

> ### Softaware
1. VsCode
1. AWS IOT, Lambda
1. SolidWorks

> ### Hardware
1. ESP32
1. Keyboard TTP229

> ### Security
1. Key Registers(Polices) from AWS
1. Tokens provides by API (Loja Integrada)
1. MQTT Protocols

> ### Protoypes Videos
**Click on the text below to watch on Youtube Channel**
[Esp_32 + FreeRTO's + API_Loja_Integrada](https://youtu.be/USlRwm8FtBU)
[Esp_32 + FreeRTO's + API_Loja_Integrada New Functions](https://youtu.be/Byxi9N65fug) 
[Central Suport Assenbly + Motor Assenbly](https://youtu.be/GkYKwFoSeXg) **Rendered**
[Central Suport Assenbly + Motor Assenbly](https://youtu.be/XT-ZBJUHyEo) **No Rendered**


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
