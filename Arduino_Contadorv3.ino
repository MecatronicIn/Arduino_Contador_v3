/*
Date: jue., 30 de septiembre de 2021 12:22
Project: programa arduino contador v3
By: Mecatronic_IN
*/

#define APAGAR_TODOS 0x44
const int led =13;
int ledState= LOW;
const int SEG_A = 2;
const int SEG_B = 3;
const int SEG_C = 4;
const int SEG_D = 5;
const int SEG_E = 6;
const int SEG_F = 7;
const int SEG_G = 8;
const int SEG_P = 9;
const int DISPLAYU= 10 ;
const int DISPLAYD= 12;
const int DISPLAYC= 11;



void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_P, OUTPUT);
   pinMode(DISPLAYU, OUTPUT);
   pinMode(DISPLAYD, OUTPUT);
   pinMode(DISPLAYC, OUTPUT);
   
  Serial.begin(9600);
}//FIN SETUP------------------------------------------

 
#define  init 0;
char a[3];
int i=init;
void loop() {
char j;

   if(i++>999)
        i=init;
   convUDC2(i,&a[0]);
   convertZeros(&a[0]);
  Serial.print(a[0]);Serial.print(" ");
  Serial.print(a[1]);Serial.print(" ");
  Serial.print(a[2]);Serial.print(" ");
  Serial.print(i,DEC);Serial.println(" ");
 
  for(j=0;j<50;j++){
    Encender_display(1,a[0]+'0');delay(8);
    Encender_display(2,a[1]+'0');delay(8);
    Encender_display(3,a[2]+'0');delay(8);}
  display1(APAGAR_TODOS);
  delay(20);
             

}//FIN LLOOOP-----------------------------------------------

void convertZeros(char *a){
    if(*a=='0'){
         *a=0;
         if(*(a+1)=='0'){
              *(a+1)=0;
              return;}
         else return;}
    else return;
 
  }//fin  convert Zeros-----------------------------------


int centena(int n,int x,char *a){
   if(x==0){
       *a='0';
       return 0;}    
   if(n>(x*100-1)){
       *a=x+'0';
       return (x*100);}
   else{centena(n,x-1,a);}    
}//fin centena recursiva-----------------------------------------

void convUDC2(int n,char *a){
int n1,i,j,b;
char aa,bb;
      b=centena(n,9,a);
      n1=n-b;
      if(n1==0){
         *(a+1)='0';
         *(a+2)='0';
         return;}
      if(n1<10){
          if(*a=='0')
              *(a+1)='0';
              *(a+2)=n1+'0';}
      else{ for(i=10,j='1';i<=90;i+=10,j++){
                  if((n1-i)<10)
                        break;}
            *(a+1)=j;
            n1=n1-i;
            *(a+2)=n1+'0';}    
  }//fin conversor de Unidd decena y centena version 2



//para convertir Unidad-decena-centena
void convUDC(int n,char *a){
  //const int b[10]={10,20,30,40,50,60,70,80,90};
int b,n1,i,j;  

 if(n>499){
    *a='5';
     b=500;}
 else{
    if(n>399){
        *a='4';
        b=400;  }
    else{if(n>299){
         *a='3';
          b=300;}
        else{ if(n>199){
                 *a='2';
                  b=200;}
              else {if(n>99){
                     *a='1';
                     b=100;   }
                    else{ *a='0';
                          b=0; }} }}}
         
      n1=n-b;
      if(n1<10){
          if(*a=='0')
              *(a+1)='0';
              *(a+2)=n1+'0';}
      else{ for(i=10,j='1';i<=90;i+=10,j++){
                  if((n1-i)<10)
                        break;}
            *(a+1)=j;
            n1=n1-i;
            *(a+2)=n1+'0';}          
                         
}//fin  convUDC----------------------------------------



void Encender_display(int d,char n){
  if(n==0){
     numero(0xFF);//que no prenda nada
     display1(d);}
  else{n-=0x30;//'0'
       numero(n);
       display1(d);}
} //fin encender display-----------------------------------    


 
void display1(int d){
  switch(d){
    case 1:  digitalWrite(DISPLAYU, LOW);
             digitalWrite(DISPLAYD, HIGH);
             digitalWrite(DISPLAYC, HIGH);
           
             break;
    case 2:  digitalWrite(DISPLAYU, HIGH);
             digitalWrite(DISPLAYD, LOW );
             digitalWrite(DISPLAYC, HIGH);
             
             break;
    case 3:  digitalWrite(DISPLAYU, HIGH);
             digitalWrite(DISPLAYD, HIGH);
             digitalWrite(DISPLAYC, LOW);
             break;
    default: digitalWrite(DISPLAYU, HIGH);
             digitalWrite(DISPLAYD, HIGH);
             digitalWrite(DISPLAYC, HIGH);      
             break;}  
}//fin  --- display1---------------------------
 
 
void numero(char n){
//  Serial.print("num:");Serial.println(n,HEX);
  switch(n){
    case '0': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, HIGH);
            digitalWrite(SEG_E, HIGH);
            digitalWrite(SEG_F, HIGH);
            digitalWrite(SEG_G, LOW);
            digitalWrite(SEG_P, LOW);
            break;
    case '8': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, HIGH);
            digitalWrite(SEG_E, HIGH);
            digitalWrite(SEG_F, HIGH);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
    case '1': digitalWrite(SEG_A, LOW);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, LOW);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, LOW);
            digitalWrite(SEG_G, LOW);
            digitalWrite(SEG_P, LOW);
            break;        
    case '2': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, LOW);
            digitalWrite(SEG_D, HIGH);
            digitalWrite(SEG_E, HIGH);
            digitalWrite(SEG_F, LOW);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
   case '3': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, HIGH);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, LOW);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
   case '4': digitalWrite(SEG_A, LOW);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, LOW);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, HIGH);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
    case '5': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, LOW);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, HIGH);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, HIGH);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
    case '6': digitalWrite(SEG_A, LOW);
            digitalWrite(SEG_B, LOW);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, HIGH);
            digitalWrite(SEG_E, HIGH);
            digitalWrite(SEG_F, HIGH);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
    case '9': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, LOW);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, HIGH);
            digitalWrite(SEG_G, HIGH);
            digitalWrite(SEG_P, LOW);
            break;
 case '7': digitalWrite(SEG_A, HIGH);
            digitalWrite(SEG_B, HIGH);
            digitalWrite(SEG_C, HIGH);
            digitalWrite(SEG_D, LOW);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, LOW);
            digitalWrite(SEG_G, LOW);
            digitalWrite(SEG_P, LOW);
            break;    
    default:digitalWrite(SEG_A, LOW);
            digitalWrite(SEG_B, LOW);
            digitalWrite(SEG_C, LOW);
            digitalWrite(SEG_D, LOW);
            digitalWrite(SEG_E, LOW);
            digitalWrite(SEG_F, LOW);
            digitalWrite(SEG_G, LOW);
            digitalWrite(SEG_P, LOW);
            break;    }//fin switch--------------  
} //fin numero------------------------------------ 