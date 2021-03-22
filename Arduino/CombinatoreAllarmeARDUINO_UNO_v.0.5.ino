/*****************************************************************************************************/
/*                                                                                                   */
/*              COMBINATORE TELEFONICO PER ALLARME - VERSIONE 0.5 DEL 13.01.2020                     */
/*                                                                                                   */
/* - Inserito controllo accensione display TFT su A3                                                 */
/*                                                                                                   */
/*****************************************************************************************************/

#include <Keypad.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
//#include <SPI.h>  
//#include <Wire.h>
#include <TimerOne.h>
#include <TFT.h>  

// Define PIN for display 1.8 TFT SPI 128*160
#define cs   10 
#define dc   9 
#define rst  14 // rst non usato, messo digital pin out of range

// Define colors
#define  ST77XX_BLACK      0x0000
#define ST77XX_WHITE      0xFFFF
//#define ST77XX_RED        0xF800
//#define ST77XX_GREEN      0x07E0
//#define ST77XX_BLUE       0x001F
//#define ST77XX_CYAN       0x07FF
//#define ST77XX_MAGENTA    0xF81F
//#define ST77XX_YELLOW     0xFFE0
//#define ST77XX_ORANGE     0xFC00

//SIM800 TX is connected to Arduino D2
#define SIM800_TX_PIN 2
 
//SIM800 RX is connected to Arduino D3
#define SIM800_RX_PIN 3
#define TEMPO_CHIAMATE 120 //Minimo tempo in secondi tra due chiamate successive
#define TEMPO_IN1_LOW 86400  //Minimo tempo in secondi tra 2 stati bassi successivi, senza che sia ritornato alto, perché si possa considerare allarme valido
#define TEMPO_IN2_LOW 86400  //Minimo tempo in secondi tra 2 stati bassi successivi, senza che sia ritornato alto, perché si possa considerare allarme valido

//Timeout diplay
#define TIMEOUT_DISPLAY 30
//Ingressi e uscite digitali
#define IN1 A0
#define IN2 A1
#define OUT1 A2
#define OUT2 A3


//Create software serial object to communicate with SIM800
SoftwareSerial serialSIM800(SIM800_TX_PIN,SIM800_RX_PIN);

// Create an instance of the library TFT
TFT TFTscreen = TFT(cs, dc, rst);

const byte ROWS = 1; //four rows
const byte COLS = 5; //three columns
char keys[ROWS][COLS] = {
  {'r','l','u','d','o'},
};
byte rowPins[ROWS] = {4}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {19, 5, 6, 7, 8}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char spegni_display=0;
char timeout=0;
int ultima_chiamata;
int secondi_in1_low; // Numero di secondi in cui IN1 è LOW
int secondi_in2_low; // Numero di secondi in cui IN1 è LOW
char stato_in1=1; //Stato dell'ingresso IN1. Viene letto subito nel loop() ma si inizializza ad 1 perché si presuppone che all'accensione non ci sia allarme.
char stato_in2=1; //Stato dell'ingresso IN2. Viene letto subito nel loop() ma si inizializza ad 1 perché si presuppone che all'accensione non ci sia allarme.
char verifica_connessione=0;
char verifica_sms=0;
char conta_GSM_down=0;

char codice[]="1234";
char numero_tel[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char nome_utente[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/*** Funzione setup ***/
void setup() {
// put your setup code here, to run once:
// Definisce bitmap
// uint8_t quadrato[8] = {0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f};
// uint8_t freccia_giu[8] = {0x4,0x4,0x4,0x4,0x15,0xe,0x4};
// uint8_t freccia_su[8] = {0x4,0xe,0x15,0x4,0x4,0x4,0x4};
byte value;
cli();//stop interrupts
//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
sei();//allow interrupts
Serial.begin(9600);
// Le righe qui sotto servono per inizializzare le nuove schede con codice rrrr
 EEPROM.write(0, 'r');
 EEPROM.write(1, 'r');
 EEPROM.write(2, 'r');
 EEPROM.write(3, 'r');
 codice[0] = EEPROM.read(0);
 codice[1] = EEPROM.read(1);
 codice[2] = EEPROM.read(2);
 codice[3] = EEPROM.read(3);

// Initialize TFT library
TFTscreen.begin();
// Clear the screen with a black background
TFTscreen.background(0, 0, 0);
// Set the text size
TFTscreen.setTextSize(3);

// Verifica il codice, se 0000 lo mette a 1234
if (!((EEPROM.read(0) == 0)&&(EEPROM.read(1) == 0)&&(EEPROM.read(2) == 0)&&(EEPROM.read(3) == 0)))
{
// Serial.println("Leggo password da EEPROM");
 codice[0] = EEPROM.read(0);
 codice[1] = EEPROM.read(1);
 codice[2] = EEPROM.read(2);
 codice[3] = EEPROM.read(3);
}

 serialSIM800.begin(9600);
 delay(5000); // Attende per 5 secondi l'accensione del SIM800L

 Serial.write(0x1a);

 serialSIM800.println("AT+CMGF=1"); //Seleziona SMS in text mode
 serialSIM800.flush();
 svuota_buffer(2);
 serialSIM800.println("AT+CMIC=0,10"); //Imposta a 10 il livello del microfono
 serialSIM800.flush();
 svuota_buffer(2);
 serialSIM800.println("AT+CPMS=\"SM\""); //Legge i messaggi SMS dalla SIM
 serialSIM800.flush();
 svuota_buffer(1);
 serialSIM800.println("AT+CLVL=100"); //Mette il volume a 100
 serialSIM800.flush();
 svuota_buffer(1);
 serialSIM800.println("AT+CRSL=100"); //Mette il livello suoneria a 100
 serialSIM800.flush();
 svuota_buffer(1);
// serialSIM800.println("AT+CNMI=0,0,0,0,0"); //Non notifica gli SMS
// serialSIM800.flush();
// svuota_buffer(1);

// Collega allarme al pin 13
 pinMode(IN1, INPUT_PULLUP);
 pinMode(OUT1, OUTPUT);
 pinMode(IN2, INPUT_PULLUP);
 pinMode(OUT2, OUTPUT);
 digitalWrite(OUT2, HIGH); // Accende il display

 ultima_chiamata=0; //Azzera all'avvio per evitare che partano chiamate all'accensione del dispositivo
 secondi_in1_low=TEMPO_IN1_LOW; //Inizializza ad un valore alto per non compromettere il rilievo di eventuali passaggi a low subito dopo l'accensione
 secondi_in2_low=TEMPO_IN2_LOW; //Inizializza ad un valore alto per non compromettere il rilievo di eventuali passaggi a low subito dopo l'accensione
}
/*** FINE setup() ***/


/*** Interrupt Service Routine ***/
ISR(TIMER1_COMPA_vect){
 spegni_display += 1;
 if (spegni_display >= TIMEOUT_DISPLAY)spegni_display = TIMEOUT_DISPLAY;
 if (spegni_display >= TIMEOUT_DISPLAY) {
  timeout = 1;
 }
 if (spegni_display < TIMEOUT_DISPLAY) {
  timeout = 0;
 }
 ultima_chiamata+=1;
 verifica_connessione+=1;
 if (ultima_chiamata >=10000) ultima_chiamata=10000; // Mette un limite all'incremento per evitare di andare oltre il massimo valore per un intero
 verifica_connessione+=1; // Timer per la verifica connessione SIM800
 if (verifica_connessione >=200) verifica_connessione=200; // Mette un limite all'incremento per evitare di andare oltre il massimo valore per un char
 verifica_sms+=1; // Timer per verificare l'arrivo si SMS
 if (verifica_sms >=200) verifica_sms=200; // Mette un limite all'incremento per evitare di andare oltre il massimo valore per un char

 secondi_in1_low++;
 if (secondi_in1_low >= TEMPO_IN1_LOW) secondi_in1_low=TEMPO_IN1_LOW;
 secondi_in2_low++;
 if (secondi_in2_low >= TEMPO_IN2_LOW) secondi_in2_low=TEMPO_IN2_LOW;
}
/*** FINE Interrupt Service Routine ***/


/*** Funzione svuota buffer ***/
void svuota_buffer(char secondi)
{
char lastCharRead;
unsigned long tempo_inizio;
int millesimi;
millesimi = secondi*1000;
tempo_inizio=millis();
Serial.print(F("Svuota per "));
Serial.print((int)secondi);
Serial.println(F(" secondi il buffer serialSIM800"));
Serial.flush();
while((millis()-tempo_inizio)<millesimi)  //Attende la risposta 
{

 while(serialSIM800.available()>0)
 {
  lastCharRead = serialSIM800.read();
   Serial.print(lastCharRead);
 }
}
// Serial.print(F("FINE dei "));
// Serial.print((int)secondi);
// Serial.println(F(" secondi"));
 
 Serial.flush();
}
/*** FINE Funzione svuota buffer ***/


/*** Funzione che dato ID ricava numero di telefono e nome ***/
char leggi_id(char id[3])
{
 char lastCharRead;
 char indice=0;
 char currentLine[100]="";
 unsigned long tempo_inizio;
 tempo_inizio = millis();
// char numero_tel[20];
// char nome_utente[10];
// String comando;
 char comando[]= "AT+CPBR=2";
// svuota_buffer(5);
// comando = "AT+CPBR="+id+"\r\n";
 comando[8]=id[0];
 comando[9]=0;
// Serial.print(F("Comando leggi_id :"));
// Serial.println(comando);
 serialSIM800.println(comando); //Stampa il numero id in rubrica
 serialSIM800.flush();
  Serial.println(F("Lettura rubrica"));
  delay(500);
 while((millis()-tempo_inizio)<1000)  //Attende la risposta per 1 secondo
 {
  while (serialSIM800.available())
  {
   lastCharRead = serialSIM800.read();
   Serial.print(lastCharRead);
   currentLine[indice]=lastCharRead; 
   indice++;
  }
 }
  currentLine[indice]=0; 
  char pos_virg[4]={0};
  char indice_pos = 0;
  for( indice = 0; indice < sizeof(currentLine); indice++ ) {
   if (currentLine[indice] == '\"')
   {
    pos_virg[indice_pos]=indice;
    indice_pos++;
   }
  }
// Estrae numero telefono
  indice_pos=0;
  for( indice = pos_virg[0]+1; indice < pos_virg[1]; indice++ ) {
//   Serial.println("Dentro al primo ciclo FOR");
   numero_tel[indice_pos] = currentLine[indice];
   indice_pos++;
  }
  if (indice_pos != 0)
   numero_tel[indice_pos]=0;
  else
  {
   numero_tel[0]='X';
   numero_tel[1]=0;
  }
//  Serial.print("Indice_pos telefono = ");
//  Serial.println((int)indice_pos);

// Estrae nome
  indice_pos=0;
  nome_utente[0] = " ";
  nome_utente[1] = 0;
  for( indice = pos_virg[2]+1; indice < pos_virg[3]; indice++ ) {
//   Serial.println("Dentro al secondo ciclo FOR");
   nome_utente[indice_pos] = currentLine[indice];
   indice_pos++;
  }
  if (indice_pos != 0)
   nome_utente[indice_pos]=0;
  else
  {
   nome_utente[0]='X';
   nome_utente[1]=0;
  }

}
/*** FINE Funzione che dato ID ricava numero di telefono e nome ***/


/*** Funzione di visualizzazione numeri da chiamare ***/
void visualizza_numeri()
{
  char key,indice=1;
  int riga=30;
  char id[2];
  char buf[12];
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(20,1);
  TFTscreen.print(F("NUMERI TEL"));

  spegni_display=0;
  for (indice=1;indice<=3;indice++)
  {
   id[0]=48+indice;
   id[1]=0;
   leggi_id(id);
//   a=48+indice;

   TFTscreen.setTextSize(1);
   TFTscreen.text(itoa(indice,buf,10), 10, riga);
   TFTscreen.text(") ", 15, riga);
   TFTscreen.text(nome_utente, 24, riga);
   TFTscreen.text(numero_tel, 10, riga+10);
   riga+=25;
  } 
  TFTscreen.text("<Premi SEL per uscire>", 15, 110);

while (1)
{
   key=keypad.getKey();
   while ((key == NO_KEY)||((key!='d')&&(key!='u')&&(key!='o')))   
   {
    key=keypad.getKey();
    if (timeout == 1) return;
   }
   if (key == 'o')
   {
    spegni_display=0;
    return;
   }
}
}
/*** FINE Funzione di visualizzazione numeri da chiamare ***/


/*** Funzione di rimozione numeri ***/
void rimuovi_numeri()
{
  char numero_imposta=1;
  char key;
  char id_i[2];
  char buf[12];
  
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(1,10);
  TFTscreen.print(F("RIMUOVI NUM."));
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(1,40);
  TFTscreen.print(F("SELEZIONA ID (1-3):"));
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);

  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 

  id_i[0] = numero_imposta+48;
  id_i[1] = 0;
  String id((char*)id_i);
  String comando;
  comando = "AT+CPBW="+id;
//  Serial.println("Comando = "+comando);
  serialSIM800.println(comando); //Rimuovi dalla rubrica
//  Serial.println("RIMOSSO numero "+id);
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(50,20);
  TFTscreen.print(F("NUMERO"));
  TFTscreen.setCursor(40,60);
  TFTscreen.print(F("RIMOSSO"));
  TFTscreen.setTextSize(1);
  svuota_buffer(2);
}
/*** Funzione di rimozione numeri ***/


/*** Funzione di aggiunta numeri in rubrica ***/
void aggiungi_numeri()
{
  char key,carattere=48;
  char id_vect_tel=0;
//  char numero_imposta_ascii=49;
  char numero_imposta=1;
  char numero_telefono[15];
  char indice_tel=45;
  char nome[20];
  char indice_nome=0;
  char colonna=0;
//  char cifra_tel_ascii=48;
  char cifra_tel=0;
  char id_i[2];
  char buf[12];
  char lettera[2]={' ',0};

  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("AGGIUNGI NUM.", 1, 10);
  TFTscreen.setTextSize(1);
  TFTscreen.text("SELEZIONA ID (1-3):", 1, 40);
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);

  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.text("SELEZIONA ID (1-3):             ", 1, 40);
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.text("SELEZIONA ID (1-3):              ", 1, 40);
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 

  TFTscreen.text("Numero:", 1, 60);

//  Serial.println("Inserisci il numero:");
  key=keypad.getKey();
  while ((key == NO_KEY)||(key!='o'))
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if ((key=='u'))
   {
    spegni_display=0;
    cifra_tel++;
    if (cifra_tel > 9) cifra_tel=0;
    TFTscreen.fillRect(indice_tel,60,7,12,ST77XX_BLACK);
    TFTscreen.text(itoa(cifra_tel,buf,10), indice_tel, 60);
    numero_telefono[id_vect_tel]=cifra_tel+48;
   }
   if (key=='d')
   {
    spegni_display=0;
    cifra_tel--;
    if (cifra_tel < 0) cifra_tel=9;
    TFTscreen.fillRect(indice_tel,60,7,12,ST77XX_BLACK);
    TFTscreen.text(itoa(cifra_tel,buf,10), indice_tel, 60);
    numero_telefono[id_vect_tel]=cifra_tel+48;
//    indice_tel++;
   }
   if (key=='r')
   {
    spegni_display=0;
    if (id_vect_tel<15)
    {
     indice_tel+=6;
     id_vect_tel++;
     TFTscreen.fillRect(indice_tel,60,7,12,ST77XX_BLACK);
     TFTscreen.text(itoa(cifra_tel,buf,10), indice_tel, 60);
     numero_telefono[id_vect_tel]=cifra_tel+48;
    }
   }
   if (key=='l')
   {
    spegni_display=0;
    if (id_vect_tel>0)
    {
     spegni_display=0;
     TFTscreen.fillRect(indice_tel,60,7,12,ST77XX_BLACK);
     numero_telefono[id_vect_tel]="";
     indice_tel-=6;
     id_vect_tel--;
     TFTscreen.fillRect(indice_tel,60,7,12,ST77XX_BLACK);
     TFTscreen.text(itoa(numero_telefono[id_vect_tel]-48,buf,10), indice_tel, 60);
     cifra_tel=numero_telefono[id_vect_tel]-48;
    }
   }
  }
  if (id_vect_tel > 0)
   numero_telefono[id_vect_tel+1]=0;
  else
   numero_telefono[id_vect_tel]=0;
  
  
  String str((char*)numero_telefono);
  id_i[0] = numero_imposta+48;
  id_i[1] = 0;
  String id((char*)id_i);

  String comando;
//  lcd.print(str);
  TFTscreen.text("Nome:", 1, 70);
  colonna=40;
  key=keypad.getKey();
  carattere=64;
  while ((key == NO_KEY)||(key!='o'))
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key=='u')
   {
    spegni_display=0;
    carattere++;
    if (carattere > 122) carattere=122;
    nome[indice_nome]=carattere;
 //   Serial.print(carattere);
    lettera[0]=carattere;
    lettera[1]=0;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
   if (key=='d')
   {
    spegni_display=0;
    carattere--;
    if (carattere < 65) carattere=65;
    nome[indice_nome]=carattere;
    lettera[0]=carattere;
    lettera[1]=0;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
   if (key=='r')
   {
    spegni_display=0;
    indice_nome++;
    colonna+=6;
    if (indice_nome > 15) {
      indice_nome=15;
      colonna-=6;
    }
    nome[indice_nome]=carattere;
    lettera[0]=carattere;
    lettera[1]=0;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
   if (key=='l')
   {
    spegni_display=0;
    nome[indice_nome]="";
    indice_nome--;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    colonna-=6;
    if (indice_nome < 0) {
      indice_nome=0;
      colonna+=6;
    }
    nome[indice_nome]=carattere;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
  } 
  if (indice_nome > 0)
   nome[indice_nome+1]=0;
  else
   nome[indice_nome]=0;
  
  String nomestr((char*)nome);
//  Serial.println(" ");
//  Serial.println("Nome inserito = "+nomestr);
  comando = "AT+CPBW="+id+",\""+str+"\",129,\""+nomestr+"\"";
//  Serial.println("Comando = "+comando);
  serialSIM800.println(comando); //Salva in rubrica

  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);

  TFTscreen.setCursor(35,60);
  TFTscreen.print(F("INSERITO"));
  TFTscreen.setTextSize(1);

  svuota_buffer(2);
}
/*** FINE Funzione di aggiunta numeri in rubrica ***/


/*** Funzione di aggiunta SMS ***/
void aggiungi_sms()
{
  char key,carattere;
  char numero_imposta=1;
  char numero_telefono[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  char indice_tel=0;
  char nome[15]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  char indice_nome=0;
  char colonna=0;
  char cifra_tel_ascii=48;
  char id_i[3];
  char buf[12];
  char lettera[2]={' ',0};

  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(5,10);
  TFTscreen.print(F("AGGIUNGI SMS"));
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(1,40);
  TFTscreen.print(F("SELEZIONA ID (1-3):"));
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
  
  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 
  spegni_display=0;
  id_i[0] = 51+numero_imposta;
  id_i[1] = 0;

  String id((char*)id_i);

  String comando;
//  lcd.print(str);
  TFTscreen.setCursor(1,60);
  TFTscreen.print(F("INSERISCI IL TESTO :"));

  key=keypad.getKey();
  carattere=64;
  while ((key == NO_KEY)||(key!='o'))
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key=='u')
   {
    spegni_display=0;
    carattere++;
    if (carattere > 122) carattere=122;
    if ((carattere > 57)&&(carattere < 65)) carattere=65;
    if ((carattere > 90)&&(carattere < 97)) carattere=32;
    if ((carattere > 32)&&(carattere < 48)) carattere=97;
 //   Serial.print(carattere);
    nome[indice_nome]=carattere;
    lettera[0]=carattere;
    lettera[1]=0;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
   if (key=='d')
   {
    spegni_display=0;
    carattere--;
    if (carattere < 32) carattere=90;
    if ((carattere < 97)&&(carattere > 90)) carattere=32;
    if ((carattere < 65)&&(carattere > 57)) carattere=57;
    if ((carattere < 48)&&(carattere != 32)) carattere=48;
    nome[indice_nome]=carattere;
    lettera[0]=carattere;
    lettera[1]=0;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
   if (key=='r')
   {
    spegni_display=0;
    nome[indice_nome]=carattere;
    indice_nome++;
    colonna+=6;
    if (indice_nome > 13) { //Massima lunghezza SMS 14 caratteri. Limite determinato dal fatto che si utilizza il campo 'nome' per registrare il testo dell'SMS. Vedi AT+CPBW=? per tlength
      indice_nome=13;
      colonna-=6;
    }
    nome[indice_nome]=carattere;
    lettera[0]=carattere;
    lettera[1]=0;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
   if (key=='l')
   {
    spegni_display=0;
    nome[indice_nome]="";
    indice_nome--;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    colonna-=6;
    if (indice_nome < 0) {
      indice_nome=0;
      colonna+=6;
    }
    nome[indice_nome]=carattere;
    TFTscreen.fillRect(colonna,70,7,12,ST77XX_BLACK);
    TFTscreen.text(lettera, colonna, 70);
   }
  } 

  if (indice_nome > 0)
   nome[indice_nome+1]=0;
  else
   nome[indice_nome]=0;
  String nomestr((char*)nome);
//  Serial.println(" ");
//  Serial.println("Nome inserito = "+nomestr);
// Scrive negli id 11, 12, 13
  comando = "AT+CPBW="+id+",\"1111\",129,\""+nomestr+"\"";
  
 Serial.println("Comando SMS = "+comando);
  serialSIM800.println(comando); //Salva in rubrica
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("INSERITO", 30, 60);
  TFTscreen.setTextSize(1);
  svuota_buffer(2);
}
/*** FINE Funzione di aggiunta SMS ***/


/*** Funzione di visualizzazione SMS ***/
void visualizza_sms()
{
  char key,a,indice=1;
  int riga=40;
  char id[3];
  char buf[12];
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("MESSAGGI", 30, 10);
  spegni_display=0;

  for (indice=1;indice<=3;indice++)
  {
   id[0]=51+indice;
   id[1]=0;
   leggi_id(id);

   TFTscreen.setTextSize(1);
   TFTscreen.text(itoa(indice,buf,10), 10, riga);
   TFTscreen.text(") ", 15, riga);
   TFTscreen.text(nome_utente, 24, riga);
//   TFTscreen.text(numero_tel, 10, riga+10);
   riga+=25;
  } 
  TFTscreen.text("<Premi SEL per uscire>", 15, 110);

while (1)
{
   key=keypad.getKey();
   while ((key == NO_KEY)||(key!='o'))   
   {
    key=keypad.getKey();
    if (timeout == 1) return;
   }
   if (key == 'o')
   {
    spegni_display=0;
    return;
   }
}

}
/*** FINE Funzione di visualizzazione SMS ***/


/*** Funzione di rimozione SMS ***/
void rimuovi_sms()
{
  char numero_imposta=1;
  char key;
  char id_i[3];
  char buf[12];
  
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(10,10);
  TFTscreen.print(F("RIMUOVI SMS"));

  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(1,40);
  TFTscreen.print(F("SELEZIONA ID (1-3):"));
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);

  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 
  id_i[0] = 51+numero_imposta;
  id_i[1] = 0;

  String id((char*)id_i);
  String comando;
  comando = "AT+CPBW="+id;
  Serial.println("Comando rimozione SMS = "+comando);
  serialSIM800.println(comando); //Rimuovi dalla rubrica
//  Serial.println("RIMOSSO numero "+id);
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(15,60);
  TFTscreen.print(F("SMS RIMOSSO"));
  TFTscreen.setTextSize(1);
  svuota_buffer(2);
}
/*** Funzione di rimozione SMS ***/


/*** Funzione di verifica codice ***/
void verifica_codice(char tasto) {
char key;
char x=0;
char riga=0;
char colonna=50;
char resta=0;

digitalWrite(OUT2, HIGH); // Accende il display

TFTscreen.setTextSize(2);
TFTscreen.text("*", colonna, 80);

if (tasto == codice[x])
 resta=0;
else
 resta = 1;
colonna+=15;

  for (x=1;x<4;x++)
  {
   key=keypad.getKey();
   while (key == NO_KEY)
   {   
    key=keypad.getKey();
    if (timeout == 1) return;
   }
Serial.println(key);
   
   if ((key == codice[x])&&(resta==0))
    resta=0;
   else
    resta = 1;
   spegni_display = 0;
   TFTscreen.text("*", colonna, 80);
   colonna+=15;
  }
 if (resta == 0)
 {
  TFTscreen.background(0, 0, 0);
  TFTscreen.text("SBLOCCATO", 30, 50);
 // Serial.println("SBLOCCATO");
  delay(1000);
  primo_menu();
 }
 else if (resta == 1)
 {
  TFTscreen.background(0, 0, 0);
  TFTscreen.text("ERRORE CODICE", 2, 50);
  delay(6000);
 }

}
/*** FINE Funzione di verifica codice ***/


/*** Funzione Viualizzazione Menu Imposta Numeri***/
void visualizza_menu_imposta_numeri() {
 TFTscreen.background(0, 0, 0);
 TFTscreen.setTextSize(2);
 TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 TFTscreen.setCursor(20,1);
 TFTscreen.print(F("NUMERI TEL"));
 TFTscreen.setTextSize(1);
 TFTscreen.setCursor(3,40);
 TFTscreen.print(F("Visualizza"));
 TFTscreen.setCursor(3,50);
 TFTscreen.print(F("Aggiungi"));
 TFTscreen.setCursor(3,60);
 TFTscreen.print(F("Rimuovi"));
 TFTscreen.setCursor(3,70);
 TFTscreen.print(F("ESCI"));

/* 
 TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 TFTscreen.setCursor(3,40);
 TFTscreen.print(F("Visualizza"));
 TFTscreen.setCursor(3,50);
 TFTscreen.print(F("Aggiungi"));
 TFTscreen.setCursor(3,60);
 TFTscreen.print(F("Rimuovi"));
 TFTscreen.setCursor(3,70);
 TFTscreen.print(F("ESCI"));*/
}
/*** FINE Funzione Viualizzazione Menu Imposta Numeri***/


/*** Funzione Secondo Menu - Impostazione numeri da chiamare ***/
void imposta_numeri() {
int posizione_attuale = 1;
char key;
visualizza_menu_imposta_numeri();
while (1)
{
// Serial.println("Dentro secondo menu - Imposta numeri");
 if (posizione_attuale == 1)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Visualizza"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Aggiungi"));
 }
 if (posizione_attuale == 2)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Aggiungi"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Visualizza"));
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
 }
 if (posizione_attuale == 3)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Aggiungi"));
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("ESCI"));
 }
 if (posizione_attuale == 4)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("ESCI"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
 }

 key=keypad.getKey();
 while (key == NO_KEY)
 {   
  key=keypad.getKey();
  if (timeout == 1) return;
 }
 spegni_display=0;
 switch (key)
 {
  case 'd':
   posizione_attuale++;
   if (posizione_attuale>4) posizione_attuale=4;
   break;  
  case 'u':
   posizione_attuale--;
   if (posizione_attuale<1) posizione_attuale=1;
   break;  
  case 'o':
   if (posizione_attuale == 1)
   {
    visualizza_numeri();
    visualizza_menu_imposta_numeri();
   }
   if (posizione_attuale == 2)
   {
    aggiungi_numeri();
    visualizza_menu_imposta_numeri();
   }
   if (posizione_attuale == 3)
   {
    rimuovi_numeri();
    visualizza_menu_imposta_numeri();
   }
   if (posizione_attuale == 4)
    return;
   break;
 }
}
}
/*** FINE Funzione di impostazione numeri da chiamare ***/


/*** Funzione di registrazione messaggi ***/
void registra_audio()
{
  char key;
  char numero_imposta=1;
  int colonna=0;
  char id_i[2];
  char buf[12];
  char conta_lampeggio=0;
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("REGISTRA", 30, 10);
  TFTscreen.setTextSize(1);
  TFTscreen.text("SELEZIONA ID (1-3):", 1, 40);
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
  
  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 
  spegni_display=0;
 
//  serialSIM800.println("AT+CMIC=0,10"); //Ripristina livello audio microfono
  serialSIM800.println("AT+CEXTERNTONE=0"); //Ripristina livello audio microfono

  id_i[0] = numero_imposta+48;
  id_i[1] = 0;
  String id((char*)id_i);
  String comando;
  comando = "AT+CREC=1,"+id+",0,10,0,1,0";
  Serial.println("Comando REC = "+comando);
  serialSIM800.println(comando); //Registra audio
  TFTscreen.setCursor(1,100);
  TFTscreen.print(F("REGISTRAZIONE IN CORSO"));
//  delay (4000); //Attende 4 secondi prima di far partire la barra
  for (colonna=0; colonna<140; colonna+=1)
  {
      TFTscreen.fillRect(colonna,70,1,20,ST77XX_WHITE);
      delay(71); // 71*140 fa circa 10 secondi che è la dirata della registrazione
      conta_lampeggio++;
      if (conta_lampeggio == 10){
       TFTscreen.fillRect(1,100,150,20,ST77XX_BLACK);
      }
      if (conta_lampeggio == 20){
       TFTscreen.setCursor(10,100);
       TFTscreen.print(F("REGISTRAZIONE IN CORSO"));
       conta_lampeggio=0;
      }
  }
  svuota_buffer(2);
  spegni_display=0;
}
/*** FINE Funzione di registrazione messaggi ***/


/*** Funzione di ascolto messaggi registrati ***/
void ascolta_audio()
{
  char key;
  char numero_imposta=1;
  int colonna=0;
  char id_i[2];
  char buf[12];

  serialSIM800.println("AT+CLVL=100"); //Mette il volume al massimo
  serialSIM800.flush();
  svuota_buffer(1);

  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(40,10);
  TFTscreen.print(F("ASCOLTA"));
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(1,40);
  TFTscreen.print(F("SELEZIONA ID (1-3):"));
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);

  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 
  spegni_display=0;

  id_i[0] = numero_imposta + 48;
  id_i[1] = 0;
  String id((char*)id_i);
  String comando;
  comando = "AT+CREC=4,"+id+",0,100";
//  Serial.println("Comando = "+comando);
  serialSIM800.println(comando); //Riproduce audio
  for (colonna=0; colonna<140; colonna+=1)
  {
//    TFTscreen.text("|", colonna, 60);
      TFTscreen.fillRect(colonna,70,1,20,ST77XX_WHITE);
      delay(71); // Con 71ms per 140 colonne fa circa 10 secondi che è la durata del messaggio
  }
  svuota_buffer(2);
  spegni_display=0;
  serialSIM800.println("AT+CLVL=0"); //Rimette il volume a 0
  serialSIM800.flush();
  svuota_buffer(1);
 // Serial.println(F("FINE Audio"));

}
/*** FINE Funzione di ascolto messaggi registrati ***/


/*** Funzione di rimozione messaggi registrati ***/
void rimuovi_audio()
{
  char key;
  char numero_imposta=1;
  char colonna=0;
  char id_i[2];
  char buf[12];

  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.text("RIMUOVI", 40, 10);
  TFTscreen.setTextSize(1);
  TFTscreen.text("SELEZIONA ID (1-3):", 1, 40);
  TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);

  key=keypad.getKey();
  while (key != 'o')   
  {
   if (timeout == 1) return;
   key=keypad.getKey();
   if (key == 'u')
   {
    spegni_display=0;
    numero_imposta++;
    if (numero_imposta > 3) numero_imposta = 3;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
   if (key == 'd')
   {
    spegni_display=0;
    numero_imposta--;
    if (numero_imposta < 1) numero_imposta=1;
    TFTscreen.fillRect(115,30,20,20,ST77XX_BLACK);
    TFTscreen.text(itoa(numero_imposta,buf,10), 120, 40);
   }
  } 
  spegni_display=0;

  id_i[0] = numero_imposta+48;
  id_i[1] = 0;
  String id((char*)id_i);
  String comando;
  comando = "AT+CREC=3,"+id;
  Serial.println("Comando rimuovi messaggio = "+comando);
  serialSIM800.println(comando); //Salva in rubrica
  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(40,50);
  TFTscreen.print(F("RIMOSSO"));
  svuota_buffer(2);
  spegni_display=0;
}
/*** FINE Funzione di rimozione messaggi registrati ***/


/*** Funzione Visualizzazione Menu Audio ***/
void visualizza_menu_audio() {
 TFTscreen.background(0, 0, 0);
 TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 TFTscreen.setTextSize(2);
 TFTscreen.setCursor(45,10);
 TFTscreen.print(F("AUDIO"));
 TFTscreen.setTextSize(1);
 TFTscreen.setCursor(3,40);
 TFTscreen.print(F("Ascolta"));
 TFTscreen.setCursor(3,50);
 TFTscreen.print(F("Registra"));
 TFTscreen.setCursor(3,60);
 TFTscreen.print(F("Rimuovi"));
 TFTscreen.setCursor(3,70);
 TFTscreen.print(F("ESCI"));
}
/*** FINE Funzione Visualizzazione Menu Audio ***/


/*** Funzione Terzo Menu - Registra Messaggi Audio ***/
void messaggi_audio() {
int posizione_attuale = 1;
char key;
visualizza_menu_audio();
while (1)
{
 if (posizione_attuale == 1)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Ascolta"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Registra"));
 }
 if (posizione_attuale == 2)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Registra"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Ascolta"));
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
 }
 if (posizione_attuale == 3)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("ESCI"));
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Registra"));
 }
 if (posizione_attuale == 4)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("ESCI"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
 }

 key=keypad.getKey();
 while (key == NO_KEY)
 {   
  key=keypad.getKey();
  if (timeout == 1) return;
 }
 spegni_display=0;
 switch (key)
 {
  case 'd':
   posizione_attuale++;
   if (posizione_attuale>4) posizione_attuale=4;
   break;  
  case 'u':
   posizione_attuale--;
   if (posizione_attuale<1) posizione_attuale=1;
   break;  
  case 'o':
   if (posizione_attuale == 1)
   {
    ascolta_audio();
    visualizza_menu_audio();
   }
   if (posizione_attuale == 2)
   {
    registra_audio();
    visualizza_menu_audio();
   }
   if (posizione_attuale == 3)
   {
    rimuovi_audio();
    visualizza_menu_audio();
   }
   if (posizione_attuale == 4)
    return;
   break;
 }
}
}
/*** FINE Funzione di impostazione numeri da chiamare ***/


/*** Funzione Visualizzazione Menu SMS ***/
void visualizza_menu_SMS() {
 TFTscreen.background(0, 0, 0);
 TFTscreen.setTextSize(2);
 TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 TFTscreen.text("SMS", 60, 10);
 TFTscreen.setTextSize(1);
 TFTscreen.setCursor(3,40);
 TFTscreen.print(F("Visualizza"));
 TFTscreen.setCursor(3,50);
 TFTscreen.print(F("Aggiungi"));
 TFTscreen.setCursor(3,60);
 TFTscreen.print(F("Rimuovi"));
 TFTscreen.setCursor(3,70);
 TFTscreen.print(F("ESCI"));
}
/*** FINE Funzione Visualizzazione Menu SMS ***/


/*** Funzione Quarto Menu - Messaggi SMS ***/
void messaggi_sms() {
int posizione_attuale = 1;
char key;
visualizza_menu_SMS();
while (1)
{
 if (posizione_attuale == 1)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Visualizza"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Aggiungi"));
 }
 if (posizione_attuale == 2)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Aggiungi"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Visualizza"));
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
 }
 if (posizione_attuale == 3)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Aggiungi"));
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("ESCI"));
 }
 if (posizione_attuale == 4)
 {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("ESCI"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Rimuovi"));
 }
 
 key=keypad.getKey();
 while (key == NO_KEY)
 {   
  key=keypad.getKey();
  if (timeout == 1) return;
 }
 spegni_display=0;
 switch (key)
 {
  case 'd':
   posizione_attuale++;
   if (posizione_attuale>4) posizione_attuale=4;
   break;  
  case 'u':
   posizione_attuale--;
   if (posizione_attuale<1) posizione_attuale=1;
   break;  
  case 'o':
   if (posizione_attuale == 1)
   {
    visualizza_sms();
    visualizza_menu_SMS();
   }
   if (posizione_attuale == 2)
   {
    aggiungi_sms();
    visualizza_menu_SMS();
   }
   if (posizione_attuale == 3)
   {
    rimuovi_sms();
    visualizza_menu_SMS();
   }
   if (posizione_attuale == 4)
    return;
   break;
 }
}
}
/*** FINE Funzione SMS ***/

/*** Funzione che associa all'ingresso i messaggi da inviare o le chiamate da eseguire ***/
void associa_messaggi()
{
 char pos_cur=9;
 char key;
 char sms_in1=EEPROM.read(4);
 char sms_in2=EEPROM.read(5);
 char voc_in1=EEPROM.read(6);
 char voc_in2=EEPROM.read(7);
 char in_sel=1; // All'inizio della funzione si seleziona l'ingresso 1
 char colonna=1;

  TFTscreen.background(0, 0, 0);
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(20,1);
  TFTscreen.print(F("IN/SMS/VOC"));
  TFTscreen.setTextSize(1);
  TFTscreen.setCursor(1,30);
  TFTscreen.print(F("Ingresso"));
  TFTscreen.setCursor(75,30);
  TFTscreen.print(F("SMS"));
  TFTscreen.setCursor(128,30);
  TFTscreen.print(F("Audio"));

while (1)
{
 if (in_sel == 1)
 {
  TFTscreen.setCursor(10,50);
  TFTscreen.print((int)in_sel);

  if (colonna == 1) TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  else TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.fillRect(80,50,10,10,ST77XX_BLACK);
  TFTscreen.setCursor(80,50);
  TFTscreen.print((int)sms_in1);

  if (colonna == 2) TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  else TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.fillRect(138,50,10,10,ST77XX_BLACK);
  TFTscreen.setCursor(138,50);
  TFTscreen.print((int)voc_in1);
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 }
 if (in_sel == 2)
 {
  TFTscreen.setCursor(10,70);
  TFTscreen.print((int)in_sel);

  if (colonna == 1) TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  else TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.fillRect(80,70,10,10,ST77XX_BLACK);
  TFTscreen.setCursor(80,70);
  TFTscreen.print((int)sms_in2);

  if (colonna == 2) TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  else TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.fillRect(138,70,10,10,ST77XX_BLACK);
  TFTscreen.setCursor(138,70);
  TFTscreen.print((int)voc_in2);
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 }
 key=keypad.getKey();
 while (key == NO_KEY)
 {   
  key=keypad.getKey();
  if (timeout == 1) return;
 }
 spegni_display=0;
 switch (key)
 {
   case 'r':
    if (colonna == 1) colonna=2;
     else colonna=2;
   break;  
 
   case 'l':
    if (colonna == 2) colonna=1;
     else colonna=1;
   break;  

   case 'u':
    if ((colonna == 1)&&(in_sel==1)) sms_in1++;
    if ((colonna == 1)&&(in_sel==2)) sms_in2++;
    if ((colonna == 2)&&(in_sel==1)) voc_in1++;
    if ((colonna == 2)&&(in_sel==2)) voc_in2++;
    if (voc_in1>3) voc_in1=3;
    if (voc_in2>3) voc_in2=3;
    if (sms_in1>3) sms_in1=3;
    if (sms_in2>3) sms_in2=3;
    EEPROM.write(4,sms_in1);
    EEPROM.write(5,sms_in2);
    EEPROM.write(6,voc_in1);
    EEPROM.write(7,voc_in2);
   break;  

    case 'd':
    if ((colonna == 1)&&(in_sel==1)) sms_in1--;
    if ((colonna == 1)&&(in_sel==2)) sms_in2--;
    if ((colonna == 2)&&(in_sel==1)) voc_in1--;
    if ((colonna == 2)&&(in_sel==2)) voc_in2--;
    if (voc_in1<1) voc_in1=1;
    if (voc_in2<1) voc_in2=1;
    if (sms_in1<1) sms_in1=1;
    if (sms_in2<1) sms_in2=1;
    EEPROM.write(4,sms_in1);
    EEPROM.write(5,sms_in2);
    EEPROM.write(6,voc_in1);
    EEPROM.write(7,voc_in2);
   break;  

    case 'o':
    if (in_sel==1) {
      in_sel=2;
      TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
      TFTscreen.fillRect(80,50,80,10,ST77XX_BLACK);
      TFTscreen.setCursor(80,50);
      TFTscreen.print((int)sms_in1);
      TFTscreen.setCursor(138,50);
      TFTscreen.print((int)voc_in1);
      break;
    }
    if (in_sel==2) return;
     break;  

 }
}
}
/*** FINE Funzione che associa all'ingresso i messaggi da inviare o le chiamate da eseguire ***/

/*** Funzione che visualizza il livello del segnale GSM ***/ 
void segnale_gsm()
{
char trovato = 0; 
char trovato_op=0;
char indice_nome_op=0;
char indice=0;
char lastCharRead; 
//char messaggio_op[]="+CSPN: \"";
char messaggio_op[]="+COPS: 0,0,\"";
char messaggio_liv[]="+CSQ: ";
char nome_op[17]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned long tempo_inizio;
char key;
/** Cerca il nome operatore nella SIM **/
TFTscreen.background(0, 0, 0);
TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
TFTscreen.setTextSize(2);
TFTscreen.setCursor(40,1);
TFTscreen.print(F("RICERCA"));
TFTscreen.setTextSize(1);

//serialSIM800.println("AT+CSPN?"); // COmando per visualizzare l'operatore
serialSIM800.println("AT+COPS?"); // COmando per visualizzare l'operatore
serialSIM800.flush();
// Attende per 2 secondi la risposta
tempo_inizio=millis();
  while (((millis()-tempo_inizio)<2000)&&(trovato_op==0))
  {
   while (serialSIM800.available())
   {
    lastCharRead = serialSIM800.read();
    if ((lastCharRead == messaggio_op[indice])&&(trovato==0))
    {
     indice++;
     if (indice == (sizeof(messaggio_op)-1)) {
      trovato=1;
      lastCharRead = serialSIM800.read(); //Se arriva a leggere +CSPN: " allora legge anche il carattere successivo perché trovato=1 ed esce dal ciclo
     }
    }
    else indice=0;
    Serial.print(lastCharRead);
    if (trovato == 1)
    {
      if ((lastCharRead != 34)&&(indice_nome_op<=15)&&(trovato_op == 0))  // 34 sono le virgolette
      {
       nome_op[indice_nome_op]=lastCharRead;
       indice_nome_op++;
      }
     if (lastCharRead ==34) {
      trovato_op=1;
//      Serial.println(F("TROVATE LE VRIGOLETTE"));
      }
    }
    Serial.flush();
   }  
  }
//  Serial.print(F("Indice_nome_op="));    
//  Serial.println((int)indice_nome_op);
  if (trovato_op == 1) 
  {
//   Serial.print(F("RILEVATA RISPOSTA NOME OPERATORE"));
   TFTscreen.text(nome_op,1,30);
   svuota_buffer(2);
  }
  else
  {
   TFTscreen.setCursor(1,30);
   TFTscreen.print(F("NESSUN OPERATORE"));
   svuota_buffer(2);
   return;
  }
  svuota_buffer(2);
/* FINE cerca nome operatore nella SIM */


/** Cerca il livello del segnale **/
trovato=0;
indice=0;
char livello_segnale;
char letto_livello=0;
char livello_percento;
char livello_percento_char[5];
// secondi_pausa=serialSIM800.parseInt(); 
serialSIM800.println("AT+CSQ"); // Comando per visualizzare l'operatore
serialSIM800.flush();
// Attende per 2 secondi la risposta
tempo_inizio=millis();
  while (((millis()-tempo_inizio)<2000)&&(trovato==0))
  {
   while (serialSIM800.available())
   {
    lastCharRead = serialSIM800.read();
    if ((lastCharRead == messaggio_liv[indice])&&(trovato==0))
    {
     indice++;
     if (indice == (sizeof(messaggio_liv)-1))
      trovato=1;
    }
    else indice=0;
    Serial.print(lastCharRead);
    if ((trovato == 1)&&(letto_livello==0))
    {
     livello_segnale = serialSIM800.parseInt();
     letto_livello=1;
    }
    Serial.flush();
   }  
  }
  svuota_buffer(1);
  if (trovato == 1) 
  {
//   Serial.print(F("Trovato segnale:"));
//   Serial.println((int)livello_segnale);
   livello_percento = (int)((float)livello_segnale*100/31);
//   Serial.println((int)livello_percento);
   itoa(livello_percento,livello_percento_char,10);
   TFTscreen.setCursor(1,50);
   if (livello_segnale == 99){
    TFTscreen.print(F("NESSUN OPERATORE"));
   }
   else
    {
     TFTscreen.print(F("Livello:"));
     TFTscreen.text(livello_percento_char,90,50);
     TFTscreen.text("%",100,50);
    }
   svuota_buffer(2);
  }
  else
  {
   TFTscreen.setCursor(1,50);
   TFTscreen.print(F("NESSUN SEGNALE"));
   svuota_buffer(2);
   return;
  }
  svuota_buffer(2);
/* FINE cerca livello segnale */


 key=keypad.getKey();
 while (key == NO_KEY)
 {   
  key=keypad.getKey();
  if (timeout == 1) return;
  //Per l'ok ricordarsi di mettere  spegni_display=0; così quando ritorna indietro di un menu il timer riparte
  
 }
 spegni_display=0;
}
/*** FINE Funzione che visualizza il livelo del segnale GSM ***/ 


/*** Funzione Viualizzazione Primo Menu ***/
void visualizza_primo_menu() {
 TFTscreen.background(0, 0, 0);
 TFTscreen.setTextSize(2);
 TFTscreen.text("MENU", 55, 10);
 TFTscreen.setTextSize(1);
 TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 TFTscreen.setCursor(3,40);
 TFTscreen.print(F("Cambio codice"));
 TFTscreen.setCursor(3,50);
 TFTscreen.print(F("Imposta numeri"));
 TFTscreen.setCursor(3,60);
 TFTscreen.print(F("Messaggi audio"));
 TFTscreen.setCursor(3,70);
 TFTscreen.print(F("SMS"));
 TFTscreen.setCursor(3,80);
 TFTscreen.print(F("Associa audio e sms"));
 TFTscreen.setCursor(3,90);
 TFTscreen.print(F("Connessione GSM"));
 TFTscreen.setCursor(3,100);
 TFTscreen.print(F("ESCI"));
}
/*** FINE Funzione Visualizzazione Primo Menu ***/


/*** Funzione Primo Menu ***/
void primo_menu() {
int posizione_attuale = 1;
char key;
visualizza_primo_menu ();
while (1)
{
 if (posizione_attuale == 1) {
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Cambio codice"));
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Imposta numeri"));
 }
 if (posizione_attuale == 2)
 {
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,40);
  TFTscreen.print(F("Cambio codice"));
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Messaggi audio"));
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Imposta numeri"));
 }
 if (posizione_attuale == 3)
 {
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,50);
  TFTscreen.print(F("Imposta numeri"));
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("SMS"));
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Messaggi audio"));
 }
 if (posizione_attuale == 4)
 {
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,60);
  TFTscreen.print(F("Messaggi audio"));
  TFTscreen.setCursor(3,80);
  TFTscreen.print(F("Associa audio e sms"));
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("SMS"));
 }
 if (posizione_attuale == 5)
 {
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,70);
  TFTscreen.print(F("SMS"));
  TFTscreen.setCursor(3,90);
  TFTscreen.print(F("Connessione GSM"));
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,80);
  TFTscreen.print(F("Associa audio e sms"));
 }
 if (posizione_attuale == 6)
 {
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,100);
  TFTscreen.print(F("ESCI"));
  TFTscreen.setCursor(3,80);
  TFTscreen.print(F("Associa audio e sms"));
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,90);
  TFTscreen.print(F("Connessione GSM"));
 }
 if (posizione_attuale == 7)
 {
  TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
  TFTscreen.setCursor(3,90);
  TFTscreen.print(F("Connessione GSM"));
  TFTscreen.setTextColor(ST77XX_BLACK,ST77XX_WHITE);
  TFTscreen.setCursor(3,100);
  TFTscreen.print(F("ESCI"));
 }

 key=keypad.getKey();
 while (key == NO_KEY)
 {   
  key=keypad.getKey();
  if (timeout == 1) return;
 }
 spegni_display=0;
 switch (key)
 {
  case 'd':
   posizione_attuale++;
   if (posizione_attuale>7) posizione_attuale=7;
   break;  
  case 'u':
   posizione_attuale--;
   if (posizione_attuale<1) posizione_attuale=1;
   break;  
  case 'o':
   if (posizione_attuale == 1)
   {
    cambio_codice();
    visualizza_primo_menu();    
   }
   if (posizione_attuale == 2)
   {
    imposta_numeri();
    visualizza_primo_menu();    
   }
   if (posizione_attuale == 3)
   {
    messaggi_audio();
    visualizza_primo_menu();    
   }
   if (posizione_attuale == 4)
   {
    messaggi_sms();
    visualizza_primo_menu();    
   }
   if (posizione_attuale == 5)
   {
    associa_messaggi();
    visualizza_primo_menu();    
   }
   if (posizione_attuale == 6)
   {
    segnale_gsm();
    visualizza_primo_menu();    
   }
   if (posizione_attuale == 7)
    return;
   break;
 }
}
}
/*** FINE Funzione Primo Menu ***/

/*** Funzione di cambio password. ATTENZIONE: La prima volta che si usa la scheda i valori EEPROM vanno inizializzati. ***/
void cambio_codice()
{
char x;
char key;
char colonna = 50;
 TFTscreen.background(0, 0, 0);
 TFTscreen.setTextSize(2);
 TFTscreen.setCursor(2,10);
 TFTscreen.print(F("CAMBIO CODICE"));
//Serial.println("CAMBIO CODICE");
 for (x=0;x<4;x++)
 {
   key=keypad.getKey();
   while (key == NO_KEY)
   {   
    key=keypad.getKey();
    if (timeout == 1) return;
   }
   spegni_display = 0;
   EEPROM.write(x, key);
  // Serial.print(key);
   TFTscreen.text("*", colonna, 80);
   colonna+=15;
   codice[x]=key;
 } 
//Serial.println(" ");
//Serial.println("Codice Cambiato");
 TFTscreen.background(0, 0, 0);
 TFTscreen.setTextSize(2);
 TFTscreen.setCursor(45,20);
 TFTscreen.print(F("CODICE"));
 TFTscreen.setCursor(35,60);
 TFTscreen.print(F("CAMBIATO"));
 delay (3000);
 TFTscreen.background(0, 0, 0);

}
/*** FINE Funzione Cambio Codice ***/

/*** Funzione Chiamata Allarme ***/
void chiamata_allarme(char ingresso)
{
 char id[3];
 char lastCharRead;
 char st_connect[]="MO CONNECTED";
 char indice=0;
 char i;
 char trovato = 0;
 char ingresso_ascii;
 char sms_ingresso; //Numero dell'SMS in funzione dell'ingresso passato in argomento
 char voc_ingresso; //Numero dell'audio in funzione dell'ingresso passato in argomento
 char testo_sms[16];
 char comando_sms[25]={0};
 char tasto_premuto=0;
 unsigned long tempo_inizio;
 unsigned long tempo_parziale;
 char comando_mic[17] = "AT+CEXTERNTONE=1"; //Chiude il microfono

 comando_mic[16]=0;
 tempo_inizio = millis();
 //svuota_buffer();
// Serial.print(F("ALLARME SU INGRESSO n. "));
 ingresso_ascii = ingresso+48;
// Serial.println(ingresso_ascii);
 Serial.flush();
 indice=0;
 delay (1000);
// char num_audio=49;

 if (ingresso == 1)
 {
  sms_ingresso = EEPROM.read(4);
  voc_ingresso = EEPROM.read(6);
 }
 if (ingresso == 2)
 {
  sms_ingresso = EEPROM.read(5);
  voc_ingresso = EEPROM.read(7);
 }
// Serial.println(F("Voc ingresso: "));
// Serial.println((int)voc_ingresso);
 Serial.flush();

/*** Invio degli SMS ***/
//if (ingresso == 1)
//{
// id[0]=52;
 id[0]=sms_ingresso+51;
 id[1]=0;
//}
svuota_buffer(5);
leggi_id(id);
strcpy(testo_sms,nome_utente);
// Serial.println(F("Invio SMS con testo:"));
// Serial.println(testo_sms);
Serial.flush();
for (i=1;i<=3;i++)
{
 id[0]=48+i;
 id[1]=0;
 svuota_buffer(1);
 leggi_id(id);
// Serial.print(F("Al numero:"));
// Serial.print(numero_tel);
// Serial.print(F(" dell'ID "));
// Serial.println(id);
 
 Serial.flush();
 strcpy(comando_sms,"AT+CMGS=\"");
 strcat(comando_sms,numero_tel);
 strcat(comando_sms,"\"");
// Serial.print(F("Con comando:"));
// Serial.println(comando_sms);
 serialSIM800.println(comando_sms); //Invio SMS
 serialSIM800.flush();
 svuota_buffer(1);
 serialSIM800.println(testo_sms); //Invio SMS
 serialSIM800.flush();
 svuota_buffer(2);
 serialSIM800.write(0x1a);
 serialSIM800.flush();
 svuota_buffer(2); // Era 7
 Serial.print(F("SMS INVIATO"));
}
/*** FINE Invio degli SMS ***/


/*      serialSIM800.println(comando_mic); //Metti mute
      serialSIM800.flush();
      svuota_buffer(2);
*/

 char comando_setup[12]= "AT+MORING=1";
 comando_setup[11]=0;
 serialSIM800.println(comando_setup); //Visualizza tutti i messaggi
 serialSIM800.flush();

 svuota_buffer(2); // 15.12.2019 Era 5
 
if (ultima_chiamata>=TEMPO_CHIAMATE)
{
for (i=1;i<=3;i++) // Cicla tutti i numeri di telefono
{

svuota_buffer(2); // 15.12.2019 era 5

ultima_chiamata=0;
id[0]=48+i;
id[1]=0;
leggi_id(id);
// Serial.println(nome_utente);
// Serial.println(numero_tel);
Serial.flush();
serialSIM800.flush();

if (numero_tel[0]!='X')
{
 char comando_chiamata[8]= "ATD>";
 comando_chiamata[4]=48+i;
 comando_chiamata[5]=';';
 comando_chiamata[6]=0;
 
 ultima_chiamata=0; //Azzera timer chiamate
 serialSIM800.println(comando_chiamata); //Esegui chiamata
 serialSIM800.flush();
// Attende per 30 secondi il MO CONNECT
 tempo_inizio=millis();
   while (((millis()-tempo_inizio)<30000)&&(trovato==0))
   {
    while (serialSIM800.available())
    {
     lastCharRead = serialSIM800.read();
     if ((lastCharRead == st_connect[indice])&&(trovato==0))
     {
      indice++;
      if (indice == (sizeof(st_connect)-1)) trovato=1;
     }
     else indice=0;
     Serial.print(lastCharRead);
     Serial.flush();
    }  
   }

  char comando_play[17]="AT+CREC=4,1,0,20";
  comando_play[10] = voc_ingresso+48;
  comando_play[16] = 0;
    if (trovato == 1)
    {
      serialSIM800.println(comando_mic); //Metti mute
      serialSIM800.flush();
      svuota_buffer(2);
      serialSIM800.println(comando_play); //Play audio
      serialSIM800.flush();
      svuota_buffer(1); // Andare a leggere esito comando play e CEXTERTONE
    }
    else
    {
     // Nessuna Risposta
//     Serial.println(F("NESSUNA RISPOSTA"));
     Serial.flush();
     char comando_fine[4] = "ATH";
     comando_fine[3]=0;
     serialSIM800.println(comando_fine); //Drop chiamata
     serialSIM800.flush();
     svuota_buffer(1); // Andare a leggere esito comando ATH

    }

    serialSIM800.println("AT+DDET=1"); //Abilita DTMF
    serialSIM800.flush();
    svuota_buffer(1); 

    tempo_parziale=millis();
    while ((millis()-tempo_parziale)<10000)  // Attende 10 secondi che termini il play del messaggio
    {
      if (serialSIM800.find("+DTMF:")) {
       tasto_premuto=serialSIM800.parseInt();  // Nel frattempo ascolta i tasti premuti sulla tastiera tramite DTMF
       if (tasto_premuto == 9) i=5;  // Se si preme il tasto 9 blocca le chiamate successive mettendo i ad un valore superiore a 3 così esce dal ciclo for
 //      Serial.println(F("Ricevuto tono"));
       svuota_buffer(2);
      }
    }
//    Serial.print(F("Premuto il tasto:"));
//    Serial.println((int)tasto_premuto);
    
    serialSIM800.println("AT+DDET=0"); //Disabilita DTMF
    serialSIM800.flush();
    svuota_buffer(1); // Andare a leggere esito comando ATH


//    delay (10000); // Attende 10 secondi che termini il messaggio poi chiude la chiamata
    serialSIM800.println("ATH"); //Drop chiamata
    serialSIM800.flush();
//    Serial.println(F("Eseguito DROP chiamata"));
    Serial.flush();
    svuota_buffer(1); // Andare a leggere esito comando ATH
 trovato=0;
}// FINE if numero_tel != 'X'
else
 {
//  Serial.println(F("Trovato X come numero di telefono"));     
  Serial.flush();
 }
//Serial.print(F("Prossimo indice:"));
//Serial.println((int)i);
}// FINE for cicla i numeri di telefono
//Serial.println(F("Uscito da FOR"));
}//FINE if ultima_chiamata>=TEMPO_CHIAMATE 

else
{
 // Serial.print(F("Deve trascorrere un certo tempo tra due chiamate successive. Ora siamo a "));
 // Serial.println(ultima_chiamata);
}
// Serial.println(F("Esce da funzione"));
 digitalWrite(A2,LOW); // TEST
}
/*** FINE Funzione Chiamata Allarme ***/


/*** Funzione Controllo Connessione e SMS ***/
void controllo_connessione()
{
  char messaggio_connesso[]="CREG: 0,";
  char trovato=0;
  char comando_suono[20]="AT+STTONE=1,16,2000";
  char comando_controllo[9]= "AT+CREG?";
  char lastCharRead;
  char indice=0;
  char indice_connessione;
  comando_controllo[8]=0;
  comando_suono[19]=0;
  unsigned long tempo_inizio;
 
  verifica_connessione=0; //Azzera timer chiamate
  serialSIM800.println(comando_controllo); //Esegui controllo
  serialSIM800.flush();
// Attende per 2 secondi il CREG: 0,1
  tempo_inizio=millis();
   while (((millis()-tempo_inizio)<1500)&&(trovato==0))
   {
    while (serialSIM800.available())
    {
     lastCharRead = serialSIM800.read();
     if ((lastCharRead == messaggio_connesso[indice])&&(trovato==0))
     {
      indice++;
      if (indice == (sizeof(messaggio_connesso)-1)) {
        trovato=1;
        indice_connessione = serialSIM800.parseInt();
      }
     }
     else indice=0;
     Serial.print(lastCharRead);
     Serial.flush();
    }  
   }
  if ((trovato == 1)&&((indice_connessione==1)||(indice_connessione==5)))
  {
   if (indice_connessione == 1)
    Serial.println(F("CONNESSIONE CONFERMATA CON DEFAULT"));
   if (indice_connessione == 5)
    Serial.println(F("CONNESSIONE CONFERMATA IN ROAMING"));
   conta_GSM_down=0;
  }
  else
  {
 //  Serial.println(F("PERDITA CONNESSIONE GSM"));
   serialSIM800.println(comando_suono); //Esegui suono
   serialSIM800.flush();
   conta_GSM_down++;
 //  Serial.print(F("CONTEGGIO DOWN = "));
 //  Serial.println((int)conta_GSM_down);
   if (conta_GSM_down == 2) // Dopo 1 minuto di down esegue il restart del modulo GSM
   {
//    digitalWrite(ALIM, HIGH);   
//    delay (3000);
//    digitalWrite(ALIM, LOW);   
//    Serial.println(F("ESEGUITO RESTART MODULO GSM"));
//    delay (5000);
//    svuota_buffer(3);
//    serialSIM800.println("AT+CMGF=1"); //Seleziona SMS in text mode
//    serialSIM800.flush();
//    svuota_buffer(1);
//    serialSIM800.println("AT+CMIC=0,10"); //Imposta a 10 il livello del microfono
//    serialSIM800.flush();
//    svuota_buffer(1);
//    serialSIM800.println("AT+CPMS=\"SM\""); //Legge i messaggi SMS dalla SIM
//    serialSIM800.flush();
//    svuota_buffer(1);
//    serialSIM800.println("AT+CLVL=0"); //Mette il volume a 0
//    serialSIM800.flush();
//    svuota_buffer(1);
    conta_GSM_down=0;
   }
  }
  svuota_buffer(1);

/***** CONTROLLO SMS *****/
/*********************************************************************************************/
/* MESSAGGI POSSIBILI                                                                        */
/* OUTx ON --> Mette l'uscita x in ON. x=1 o 2                                               */  
/* OUTx OFF --> Mette l'uscita x in OFF. x=1 o 2                                             */
/* OUTx A,y  --> Mette l'uscita x in ON per y secondi e poi in OFF. y=1-9                    */
/*********************************************************************************************/

  char messaggio_sms_1on[]="OUT1 ON";
  char messaggio_sms_1off[]="OUT1 OFF";
//  char messaggio_sms_2on[]="OUT2 ON";
//  char messaggio_sms_2off[]="OUT2 OFF";
  char messaggio_sms_1A[]="OUT1 A,";
//  char messaggio_sms_2A[]="OUT2 A,";
  
  char trovato1on=0;
  char trovato1off=0;
//  char trovato2on=0;
//  char trovato2off=0;
  char trovato1A=0;
//  char trovato2A=0;

  char indice1on=0;
  char indice1off=0;
//  char indice2on=0;
//  char indice2off=0;
  char indice1A=0;
//  char indice2A=0;
  char secondi_pausa;
  char secondi_pausa_veri;
  
//  unsigned long tempo_inizio;
// tasto_premuto=serialSIM800.parseInt(); 

  verifica_connessione=0; //Azzera timer chiamate
  serialSIM800.println("AT+CMGL=\"REC UNREAD\""); //Visualizza i messaggi non letti
  serialSIM800.flush();
// Attende per 1,5 secondi la lettura dei messaggi
  tempo_inizio=millis();
   while (((millis()-tempo_inizio)<1500)&&(trovato1on==0)&&(trovato1off==0))
   {
    while (serialSIM800.available())
    {
     lastCharRead = serialSIM800.read();
     if ((lastCharRead == messaggio_sms_1on[indice1on])&&(trovato1on==0))
     {
      indice1on++;
      if (indice1on == (sizeof(messaggio_sms_1on)-1)) trovato1on=1;
     }
     else indice1on=0;
     if ((lastCharRead == messaggio_sms_1off[indice1off])&&(trovato1off==0))
     {
      indice1off++;
      if (indice1off == (sizeof(messaggio_sms_1off)-1)) trovato1off=1;
     }
     else indice1off=0;
     if ((lastCharRead == messaggio_sms_1A[indice1A])&&(trovato1A==0))
     {
      indice1A++;
      if (indice1A == (sizeof(messaggio_sms_1A)-1)) {
        trovato1A=1;
        secondi_pausa=serialSIM800.parseInt(); 
      }
     }
     else indice1A=0;
     
     Serial.print(lastCharRead);
     Serial.flush();
    }  
   }
  if (secondi_pausa > 10) secondi_pausa=10;  // Astabile per massimo 10 secondi
  if (trovato1on == 1) 
  {
//   Serial.println(F("TROVATO 1 ON"));
   digitalWrite(OUT1, HIGH);   
  }
  else if (trovato1off == 1)
  {
//   Serial.println(F("TROVATO 1 OFF"));
   digitalWrite(OUT1, LOW);   
  }
  else if (trovato1A == 1)
  {
 //  Serial.print(F("TROVATO 1A con secondi pausa :"));
 //  Serial.println((int)secondi_pausa);
   digitalWrite(OUT1, HIGH);
   delay (secondi_pausa*1000);
   digitalWrite(OUT1, LOW);
  }
  else 
   Serial.println(F("TROVATO NIENTE"));
  serialSIM800.println("AT+CMGDA=\"DEL READ\""); //Cancella i messaggi già letti
  serialSIM800.flush();
  svuota_buffer(1);
  verifica_sms=0;
  
/***** FINE CONTROLLO SMS *****/
}
/*** FINE Funzione Controllo Connessione e SMS ***/


void loop() {
char key;
int Reading;
char chiamata_allarme_in1 = 1;
char chiamata_allarme_in2 = 1;
unsigned long tempo_inizio;
char messaggio_ring[]="RING";
char messaggio_drop[]="NO CARRIER";
char trovato_ring=0;
char indice_ring=0;
char trovato_drop=0;
char indice_drop=0;
char lastCharRead;
char chiamata_in_corso=0;
char show_audio = 0;
char ring_in_corso = 0;
char n=0;

// Inserimento codice
 Serial.println(F("TELCODE  2.0"));
 Serial.println(F("Inserisci codice sblocco"));
 TFTscreen.background(0, 0, 0);
 TFTscreen.stroke(255, 255, 255);
 TFTscreen.setTextSize(2);
 
 
 TFTscreen.setTextColor(ST77XX_WHITE,ST77XX_BLACK);
 TFTscreen.setCursor(10,10);
 TFTscreen.print(F("TELCODE 2.0"));
 
 TFTscreen.setTextSize(1);
 TFTscreen.text("Inserisci codice", 30, 50);


 key=keypad.getKey();
 while ((key == NO_KEY)||(chiamata_in_corso == 1)||(ring_in_corso == 1))
 {
  key=keypad.getKey();

// Verifica messaggio RING
   tempo_inizio=millis();
    while ((serialSIM800.available())&&(trovato_ring==0))
    {
     lastCharRead = serialSIM800.read();
     if ((lastCharRead == messaggio_ring[indice_ring])&&(trovato_ring==0))
     {
      indice_ring++;
      if (indice_ring == (sizeof(messaggio_ring)-1)) {
        trovato_ring=1;
        ring_in_corso = 1;
      }
     }
     else {
      indice_ring=0;
     }

     if ((lastCharRead == messaggio_drop[indice_drop])&&(trovato_drop==0))
     {
      indice_drop++;
      if (indice_drop == (sizeof(messaggio_drop)-1)) {
        trovato_drop=1;
        ring_in_corso = 0;
      }
     }
     else indice_drop=0;    
    Serial.print(lastCharRead); // Spostato qui
    }
//    Serial.print(lastCharRead);  // Tolto da qui
    Serial.flush();
   if (trovato_ring == 1)
   {
    spegni_display = 0;
    digitalWrite(OUT2, HIGH); // Accende il display
    TFTscreen.background(0, 0, 0);
    TFTscreen.setTextSize(2);
    TFTscreen.text("CHIAMATA", 35, 50);
    delay(50);
    for (n=0; n<12; n++)
    {
     if (key == NO_KEY) key=keypad.getKey();
     TFTscreen.rect(23-n*2,46-n*2,114+n*4,24+n*4);
     delay(50); 
    }
    
    tempo_inizio=millis();
    while (((millis()-tempo_inizio)<2000)&&(key==NO_KEY)) // Attende per 2 secondi la pressione del tasto ok
    {
      key=keypad.getKey();
    }
    
//    delay(2000);
    if (key == NO_KEY) key=keypad.getKey();
    TFTscreen.background(0, 0, 0);
   }
   if ((trovato_ring == 1)&&(key!=NO_KEY))
   {
    serialSIM800.println("ATA"); //Risponde alla chiamata
    serialSIM800.flush();
    svuota_buffer(1);
    serialSIM800.println("AT+CLVL=100"); //Mette il volume a 80
    serialSIM800.flush();
    svuota_buffer(1);
    chiamata_in_corso = 1;
    ring_in_corso = 0;
    key=keypad.getKey();
   }
   if (key == NO_KEY) key=keypad.getKey(); // OCCHIO
   if (chiamata_in_corso == 1)
   {
    spegni_display = 0;
    if (show_audio == 0)
     TFTscreen.text("AUDIO", 45, 50);
    show_audio=1;
    ring_in_corso = 0;
   }
   if ((chiamata_in_corso == 1)&&(key!=NO_KEY))
   {
    serialSIM800.println("ATH"); //Chiude la chiamata
    serialSIM800.flush();
    svuota_buffer(1);
    TFTscreen.background(0, 0, 0);
    TFTscreen.text("TERMINATA", 30, 50);
    delay(2000);
    key == NO_KEY;
    chiamata_in_corso = 0;
    show_audio=0;
    timeout=1;
    ring_in_corso = 0;
   }
   if (trovato_drop == 1)
   {
    TFTscreen.background(0, 0, 0);
    TFTscreen.text("TERMINATA", 30, 50);
    delay(2000);
    key == NO_KEY;
    chiamata_in_corso = 0;
    trovato_drop = 0;
    show_audio=0;
    timeout=1;
    ring_in_corso = 0;
   }
   trovato_ring=0;
// FINE verifica messaggio RING
  
  if (timeout == 1) digitalWrite(OUT2, LOW); // Spegne il display - Era: TFTscreen.background(0, 0, 0);
   else if (timeout == 0)  digitalWrite(OUT2, HIGH); // Accende il display;
  // ROUTINE VERIFICA INGRESSI
  Reading = digitalRead(IN1); // Reading status of Arduino digital Pin 12. Corrispondente a ingresso n.1
  if ((Reading==LOW)&&(stato_in1==HIGH)) //IN1 era HIGH e ora è LOW
  {
    secondi_in1_low=0; // Azzera il contaggio dei secondi in cui è basso perché è appena andato LOW
    chiamata_allarme_in1=1; // Si può chiamare l'allarme per IN1
  }
  if ((Reading==LOW)&&(stato_in1==LOW)) //IN1 era LOW ed è ancora LOW
  {
    if (secondi_in1_low >= TEMPO_IN1_LOW) {
      chiamata_allarme_in1=1; // Se era a LOW da più dei secondi impostati da TEMPO_IN1_LOW chiama allarme
      secondi_in1_low=0; 
    }
    else chiamata_allarme_in1=0;
  }
  if ((Reading==HIGH)&&(stato_in1==LOW)) //IN1 era LOW ed è passato a HIGH
  {
    chiamata_allarme_in1=0; // Allarme cessato e non chiama la funzione
    secondi_in1_low=TEMPO_IN1_LOW;    // Siccome è passato da LOW a HIGH un allarme successivo deve scattare subito quindi imposta i secondi a TEMPO_IN1_LOW
  }
  if ((Reading==HIGH)&&(stato_in1==HIGH)) //IN1 era HIGH ed è rimasto HIGH
  {
    chiamata_allarme_in1=0; // Non serve chiamare la funzione di allarme
    secondi_in1_low=TEMPO_IN1_LOW;    // Nel caso di un allarme successivo deve scattare subito quindi imposta i secondi a TEMPO_IN1_LOW
  }
  stato_in1 = Reading;

  if(chiamata_allarme_in1 == 1)  // Se dopo tutte le analisi di cui sopra chiamata_allarme_in1 è a 1 allora chiama la funzione di allarme
  {
    chiamata_allarme(1); // Allarme ingresso 1
  }
  
  Reading = digitalRead(IN2); // Reading status of Arduino digital Pin 12. Corrispondente a ingresso n.1
  if ((Reading==LOW)&&(stato_in2==HIGH)) //IN2 era HIGH e ora è LOW
  {
    secondi_in2_low=0; // Azzera il contaggio dei secondi in cui è basso perché è appena andato LOW
    chiamata_allarme_in2=1; // Si può chiamare l'allarme per IN2
  }
  if ((Reading==LOW)&&(stato_in2==LOW)) //IN2 era LOW ed è ancora LOW
  {
    if (secondi_in2_low >= TEMPO_IN2_LOW) {
      chiamata_allarme_in2=1; // Se era a LOW da più dei secondi impostati da TEMPO_IN2_LOW chiama allarme
      secondi_in2_low=0; 
    }
    else chiamata_allarme_in2=0;
  }
  if ((Reading==HIGH)&&(stato_in2==LOW)) //IN2 era LOW ed è passato a HIGH
  {
    chiamata_allarme_in2=0; // Allarme cessato e non chiama la funzione
    secondi_in2_low=TEMPO_IN2_LOW;    // Siccome è passato da LOW a HIGH un allarme successivo deve scattare subito quindi imposta i secondi a TEMPO_IN2_LOW
  }
  if ((Reading==HIGH)&&(stato_in2==HIGH)) //IN2 era HIGH ed è rimasto HIGH
  {
    chiamata_allarme_in2=0; // Non serve chiamare la funzione di allarme
    secondi_in2_low=TEMPO_IN2_LOW;    // Nel caso di un allarme successivo deve scattare subito quindi imposta i secondi a TEMPO_IN2_LOW
  }

  stato_in2 = Reading;

  if(chiamata_allarme_in2 == 1)
  {
    chiamata_allarme(2); // Allarme ingresso 2
  }
  // FINE ROUTINE VERIFICA INGRESSI
  if (verifica_connessione>=60) controllo_connessione();  // Ogni 30 secondi verifica che il SIM800 sia connesso e se sono arrivati SMS ***** 20.09.2019 DA RIABILITARE ****
 }
//  Serial.println("Uscito");
 if (timeout == 1)
 {
//  Serial.println("Display spento");
  spegni_display = 0;
  timeout = 0; // Se il timeout era scaduto accende il display e basta
 }
 else
 {
//  Serial.println("Display acceso");
  spegni_display = 0;
  if ((ring_in_corso == 0)&&(chiamata_in_corso == 0))
  verifica_codice(key); // Se il timeout non era scaduto e non ci sono chiamate o ring in corso va alla verifica codice passandogli il primo tasto premuto
 }
}
