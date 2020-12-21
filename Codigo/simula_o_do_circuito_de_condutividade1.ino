#include <LiquidCrystal.h>

float max_value(float m, float n);
void media(float v, float i);
float corrente_mA = 0;
float voltage = 0;



//váriaveis condutividade da agua
float condut_agua = 0;
float A_eletrodo = 0.001; //valor arbitrario
float L_eletrodo = 0.01; //valor arbitrario
float limite_condut = 50;

//Variáveis utilizadas na voltametria ciclica
byte ciclos = 2;
int tempo_degrau = 10;
float velocidade_varredura = (5 / 256) / tempo_degrau;
float I_max = 0;
float V_max = 0;
float I_med = 0;
float V_med = 0;


//Variavel de tela
boolean tela = 0;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);

void setup()
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
  Serial.begin(9600);
  
  //Tela de inicialização
  lcd.setCursor(0, 0);
  lcd.print("Leitura da");
  lcd.setCursor(0, 1);
  lcd.print("condutividade");
  delay(4000);
  
}

void loop() {
  if (digitalRead(2)) {
    tela = !tela;
    
  }
  if (!tela) {
    //Leitura da condutividade da agua
    analogWrite(3, 255);
    voltage = analogRead(A0) * (5.0 / 1023.0);
    //valor arbitrario pois a plataforma não possui sensor de corrente para simulação
    corrente_mA = 1000;
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
    
    for (int j = 0; j < ciclos; j++) {
      //Formação da onda triangular para a voltametria ciclica
      for (int i = 0; i < 256; i++) {
        analogWrite(3, i);

        //Leitura da tensão entre o eletrodo de trabalho e de referencia
        voltage = analogRead(A0) * (5 / 1023);

        //corrente passando pelo eletrodo de trabalho
        corrente_mA = 1;

        //Valor Maximo
        I_max = max_value(I_max, corrente_mA);
        V_max = max_value(V_max, voltage);

        delay(tempo_degrau);
      }

      for (int i = 255; i > 0; i--) {
        analogWrite(3, i);

        //Leitura da tensão entre o eletrodo de trabalho e de referencia
        voltage = analogRead(A0) * (5 / 1023);

        //corrente passando pelo eletrodo de trabalho
        corrente_mA = 1;

        //Valor Maximo
        I_max = max_value(I_max, corrente_mA);
        V_max = max_value(V_max, voltage);

        delay(tempo_degrau);
      }

    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("I_max: "); lcd.print(I_max);
    lcd.setCursor(0, 1);
    lcd.print("V_max: "); lcd.print(V_max);
    
    while (tela) {
      if (digitalRead(2)) {
        tela = !tela;
        delay(500);
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