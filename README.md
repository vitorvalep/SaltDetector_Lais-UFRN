# SaltDetector_Lais-UFRN

Este projeto foi feito como parte da seleção para bolsista do Laboratório de Inovação Tecnológica em Saúde.

Este projeto consiste em um hardware capaz de identificar a presença de sal ou açucar em água.
Para isso o projeto foi dividio em 3 partes

1 - Simulação de parte do projeto utlizando a ferramente thinkerCAD e plataforma arduino

2 - Códificação do firmware utilizando a plataforma Arduino

3 - Desenvolvimento do hardware utilizando a ferramenta da autodesk Eagle.

## O projeto da placa de circuito impresso comtem: 
1 - Microcontrolador atmega328p, sendo o cerebro do sistema.

2 - Amplificadores operacionais para aplificação do sinal medido pelos eletrodos. Esses circuitos devem ser alterados durante calibração e testes.

3 - Suporte para cartão SD para que os dados sejam salvos em csv para analises posteriores.

4 - RTC para manter o horario atualizado e fazer o controle dos arquivos slvos no SD card

5 - Sistema de carregamento e utilização de baterias do tipo Lithium ion.

6 - Sensor de corrente I²C para medição de corrente para medição de corrente nos eletrodos.

7 - Display LCD 16x2 para visualização de informações dos sensores.

O Hardware desenvolvido é capaz de medir a condutividade da água por meio de uma celula formada por 3 eletrodos.
Para a medição da condutividade, utilizou-se amplificadores operacionais para aplificar o sinal medido pelos eletrodos.
A informação de que existe sal ou açucar na água se dá por meio  de um lcd 16x2, que mostra a condutividade da água e se há sal ou açucar no mesmo.
O dispositivo funciona com bateria do tipo Lithium ion e pode ser recarregado por um entrada micro USB.

O dispositivo também é capaz de realizar a voltametria ciclica, experimento que consite em enviar uma onda triangular de tensão e observar os valores de tensão e corrente nos eletrodos da celula 
Por meio do sensor de corrente imbutido no hardware pode-se medir a corrente que flui pelo eletrodo de trabalho e o conversor A/D do chip atmeg328p junto com os aplificadores operacionais obteem o valor da tensão sobre o eletrodo de referencia e o eletrodo de trabalho
Ápos a varredura, duas informações são mostrada no LCD, que são os picos de corrente e tensão durante o experimento.
Há um slot pra cartão sd que guarda todos os valores em um arquivo csv, cujo o nome é a data e horario da voltametria. Com esse arquivo pode-se exportar as informações e gerar graficos para analises posteriores

## Melhorias para o projeto.

1 - Utilizar de um display TFT touche para plotar graficos e mostrar mais informações sobre a voltametria ciclica, bem como melhorar a interação entre o operado e hardware

2 - Utilizar um chip de comunicação GSM para que os dados sejam enviados em tempo real para a nuvem e la contenha todas as informações coletadas pelo operador, eliminando assim, o uso do cartão SD
