# SaltDetector_Lais-UFRN

Projeto foi feito como parte da seleção para bolsista do Laboratório de Inovação Tecnológica em Saúde.
Este projeto consiste em um hardware capaz de identificar a presença de sal ou açúcar em água. Para isso o projeto foi dividido em 3 partes

1 - Simulação de parte do projeto utilizando a ferramenta tinkerCAD e plataforma arduino

2 - Codificação do firmware utilizando a plataforma Arduino

3 - Desenvolvimento do hardware utilizando a ferramenta da autodesk Eagle.

## O projeto da placa de circuito impresso contém:

1 - Microcontrolador atmega328p, sendo o cérebro do sistema.

2 - Amplificadores operacionais para amplificação do sinal medido pelos eletrodos. Estes circuitos devem ser alterados durante calibração e testes.

3 - Suporte para cartão SD para que os dados sejam salvos em csv para análises posteriores.

4 - RTC para manter o horário atualizado e fazer o controle dos arquivos salvos no SD card

5 - Sistema de carregamento e utilização de baterias do tipo Lithium ion.

6 - Sensor de corrente I²C para medição de corrente para medição de corrente nos eletrodos.

7 - Display LCD 16x2 para visualização de informações dos sensores.

O Hardware desenvolvido é capaz de medir a condutividade da água por meio de uma célula formada por 3 eletrodos. Para a medição da condutividade, utilizou-se amplificadores operacionais para amplificar o sinal medido pelos eletrodos. A informação de que existe sal ou açúcar na água se dá por meio de um lcd 16x2, que mostra a condutividade da água e se há sal ou açúcar no mesmo. O dispositivo funciona com bateria do tipo Lithium ion e pode ser recarregado por uma entrada micro USB.

O dispositivo também é capaz de realizar a voltametria cíclica, experimento que consiste em enviar uma onda triangular de tensão e observar os valores de tensão e corrente nos eletrodos da célula Por meio do sensor de corrente embutido no hardware pode-se medir a corrente que flui pelo eletrodo de trabalho e o conversor A/D do chip atmeg328p junto com os amplificadores operacionais obtém o valor da tensão sobre o eletrodo de referência e o eletrodo de trabalho. Após a varredura, duas informações são mostradas no LCD, que são os picos de corrente e tensão durante o experimento. Há um slot para cartão SD que guarda todos os valores em um arquivo csv, cujo nome é a data e horário da voltametria. Com esse arquivo pode-se exportar as informações e gerar gráficos para análises posteriores

## Melhorias para o projeto.

1 - Utilizar de um display TFT touch para plotar gráficos e mostrar mais informações sobre a voltametria cíclica, bem como melhorar a interação entre o operador e hardware

2 - Utilizar um chip de comunicação GSM para que os dados sejam enviados em tempo real para a nuvem e lá contenha todas as informações coletadas pelo operador, eliminando assim, o uso do cartão SD

