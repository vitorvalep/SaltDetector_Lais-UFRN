/*
   Firmware para o hardware de leitura da condutividade da água
   permitindo a identificação de sal ou açucar no mesmo.

   Projeto realizado para seleção de bolsistas para o projeto
   sífilis não do Lais/UFRN para a área de sistemas embarcados
   e biosensores.

   Primeira versão do firmware(prototipo)
*/
//Bibliotecas
#include <Wire.h>
#include <Adafruit_INA219.h>  //biblioteca do sensor de corrente
#include <LiquidCrystal_I2C.h>  //biblioteca lcd i2c
#include <SPI.h>
#include <SD.h> //biblioteca SD card
#include <DS1307.h> //bilbioteca RTC

//funções
float max_value(float m, float n);
void media(float v, float i);

//Init RTC
// Init the DS1307
DS1307 rtc(4, 5);

//instancia do SDcard
File file;
byte chip_select = 10;


const int LCD_addr = 0x3F;
const int LCD_chars = 16;
const int LCD_lines = 2;
LiquidCrystal_I2C lcd(LCD_addr, LCD_chars, LCD_lines); //Indica o endereço do LCD  - 0x3F, com 16 caracteres e 2 linhas


//sensor de corrente
const int INA_addr = 0x40;  //endereço  INA219
Adafruit_INA219 ina219(INA_addr); // indica o endereço do INA219 - 0x40
float corrente_mA = 0;
float voltage = 0;


//váriaveis condutividade da agua
float condut_agua = 0;
float A_eletrodo = 0.001; //valor arbitrario
float L_eletrodo = 0.01; //valor arbitrario
float limite_condut = 500;

//Variáveis utilizadas na voltametria ciclica
byte ciclos = 5;
int tempo_degrau = 50;
float velocidade_varredura = (5 / 256) / tempo_degrau;
float I_max = 0;
float V_max = 0;
float I_med = 0;
float V_med = 0;


//Variavel de tela
boolean tela = 0;

void setup() {
  //Inicialização RTC
  rtc.halt(false);
  //Depois de configurado, pode ser comentado
  //rtc.setDOW(SUNDAY);        // dia da semana
  //rtc.setTime(12, 0, 0);     // hora (24hr formato)
  //rtc.setDate(3, 10, 2010);   // data


  //Inicialização do INA219
  ina219.begin();

  //incialização do LCD
  lcd.init();
  lcd.clear();
  lcd.backlight();

  //Tela de inicialização
  lcd.setCursor(0, 0);
  lcd.print("Leitura da");
  lcd.setCursor(0, 1);
  lcd.print("condutividade");
  delay(2000);

  //configura pino 3 como saída, esse pino vai servir como
  //fonte de tensão para o divisor de tensão e para leitura
  //dos valores de condutividade
  pinMode(3, 1);

  //SD card init
  if (!SD.begin(chip_select)) {
    lcd.print("Falha no SD");
    lcd.print("Verifique cartao");
    while (1);
  }

}

void loop() {
  if (digitalRead(2)) {
    tela = !tela;
  }
  if (!tela) {
    //Leitura da condutividade da agua
    digitalWrite(3, 1);
    voltage = analogRead(A0) * (5 / 1023);
    corrente_mA = ina219.getCurrent_mA();
    condut_agua = ((corrente_mA * L_eletrodo) / (voltage * A_eletrodo)) / 201.0; //201 é o valor do ganho do aplificador operacional
    //que faz a amplificação do sinal vindo do eletrodo

    lcd.setCursor(0, 0);
    lcd.print("con: "); lcd.print(condut_agua); lcd.print("S/cm");
    lcd.setCursor(0, 1);
    if (condut_agua > limite_condut) {
      lcd.print("agua com sal");
    } else {
      lcd.print("agua sem sal");
    }

  }

  if (tela) {
    //voltametria ciclica
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Voltametria");
    lcd.setCursor(0, 1);
    lcd.print("Aguarde");
    //Criando arquivo com nome da data e hora da voltametria
    String file_name = rtc.getDateStr();
    file_name = file_name + "_" + rtc.getTimeStr() + ".csv";
    file = SD.open(file_name, FILE_WRITE);
    //titulos das colunas do arquivo
    file.print("Tensão Corrente");

    for (int j = 0; j < ciclos; j++) {
      //Formação da onda triangular para a voltametria ciclica
      for (int i = 0; i < 256; i++) {
        analogWrite(3, i);

        //Leitura da tensão entre o eletrodo de trabalho e de referencia
        voltage = analogRead(A0) * (5 / 1023);

        //corrente passando pelo eletrodo de trabalho
        corrente_mA = ina219.getCurrent_mA();

        //Valor Maximo
        I_max = max_value(I_max, corrente_mA);
        V_max = max_value(V_max, voltage);

        //salvando dados no formato CSV para analises posteriores
        file.print(voltage);
        file.print(" ");
        file.println(corrente_mA);

        delay(tempo_degrau);
      }

      for (int i = 255; i > 0; i--) {
        analogWrite(3, i);

        //Leitura da tensão entre o eletrodo de trabalho e de referencia
        voltage = analogRead(A0) * (5 / 1023);

        //corrente passando pelo eletrodo de trabalho
        corrente_mA = ina219.getCurrent_mA();

        //Valor Maximo
        I_max = max_value(I_max, corrente_mA);
        V_max = max_value(V_max, voltage);

        //salvando dados no formato CSV para analises posteriores
        file.print(voltage);
        file.print(" ");
        file.println(corrente_mA);

        delay(tempo_degrau);
      }

    }
    file.close();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I_max: "); lcd.print(I_max);
    lcd.setCursor(0, 1);
    lcd.print("V_max: "); lcd.print(V_max);
    
    while (tela) {
      if (digitalRead(2)) {
        tela = !tela;
        delay(300);
      }
    }
  }
}


float max_value(float m, float n) {
  if (m > n) {
    return m;
  } else {
    return n;
  }
}

void media(float v, float i) {
  V_med = (V_med + v) / 2;
  I_med = (I_med + i) / 2;
}
