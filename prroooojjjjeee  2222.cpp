#include <stdio.h>	
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

FILE *kayitli;
FILE  *yaz;
       
struct kisiler{
              char kayitad[10];
              int kayitpuan;
              int kayitsure;
              };
struct kisiler oyuncular[10];


struct oynakayit {
       char oynaharf;
       struct oynakayit *oynasonraki , *oynaonceki;
       };
struct oynakayit *oynailk=NULL , *oynason, *oynagecici, *oynayer, *oynakontrol;


struct Kayit {
       int harf_sayi;
       char harf;
       struct Kayit *sonraki , *onceki;
       };
struct Kayit *ilk=NULL , *son, *gecici, *yer, *dosyaharf, *tabloharf ,*harfkontrol;              


struct ipucukayit{
       int ipucu_sayi;
       char ipucu[20];
       struct ipucukayit *sonra , *once;
       };
struct ipucukayit *bas=NULL , *enson, *gec;


time_t baslangic,bitis;
int oynanansure,puan=0;
int ipucusayisi=1,harfsayisi=1;
int tablo[15][15];
int kutuhareket=40, kutualt=90, kutuust=50, kutusag=90, kutusol=50,a=0,b=0;
char sifir='0',bir='1',iki='2',uc='3',dort='4',bes='5',alti='6',yedi='7',sekiz='8',dokuz='9';
char buton;

void oynaekle();
void ekle();
void ipucuekle();
void oyna(void);
void ekrana_sayi_yaz(void);
void ipucu_sayisi_yaz(void);
void oynasayiyaz(void);
int kontrol(void);
void puan_hesapla(void);
void puan_kaydet(void);
void menu(void);

int main()
{
    int q;
    char z;
    yaz=fopen("yeni.txt","r");
    fscanf(yaz,"%c",&z);
    fclose(yaz);
    if(z!=' ')
    {
    yaz=fopen("yeni.txt","w+");
    fprintf(yaz, "%10s%10s%18s\n","ÝSÝM","PUAN","SÜRE(SANÝYE)");
    for(q=0;q<10;q++){
                      strcpy(oyuncular[q].kayitad, "a");
                      oyuncular[q].kayitpuan=0; 
                      oyuncular[q].kayitsure=0; 
                      fprintf(yaz, "%10s%10d%10d\n", oyuncular[q].kayitad,oyuncular[q].kayitpuan,oyuncular[q].kayitsure);
                      }
    fclose(yaz);
    }
    
    
    int gd=DETECT , gm , kod , w;
    int i,secim,m,k;
    char tus;
    char kelime[2];
    

    kelime[1]='\0';
    initgraph(&gd,&gm,"");
    kod=graphresult();
    if(kod!=grOk){printf("grafik hatasi :",kod);}
    initwindow(1020,700);
    
    for(i=1;i<=225;i++) {
                        ekle();    
                        }
    yer=ilk;
    dosyaharf=ilk;
    menu();
    
    if(buton==49){cleardevice();}
    else if(buton==50){exit(1);}
    else{exit(1);}
    
    setcolor(15);
    settextstyle(1,0,20);
    outtextxy(750,35,"WORD");
    settextstyle(1,0,29);
    outtextxy(665,65,"PUZZLE");
    rectangle(660,60,1010,135);
    settextstyle(1,0,17);
    outtextxy(665,180," ÝPUCU");
    line(665,195,740,195);
    outtextxy(665,205,":");
    outtextxy(665,350,"ÝPUCU GÝRMEK ÝÇÝN 1 'E");
    outtextxy(665,400,"ÝPUCUNU KAYDETMEK");
    outtextxy(665,420,"ÝÇÝN ENTER 'A");
    outtextxy(665,470,"OYUNU KAYDETMEK ÝÇÝN 2 'YE");
    outtextxy(665,520,"OYNAMAK ÝÇÝN 3 'E");
    outtextxy(665,570,"OYUNDAN ÇIKMAK ÝÇÝN 4 'E");
    outtextxy(665,620,"BASINIZ");
    
    
    setlinestyle(0,0,0);
    setcolor(1);
    for(w=50;w<=650;w+=40) line(50,w,650,w);
    for(w=50;w<=650;w+=40) line(w,50,w,650);
    
    setcolor(11);
    rectangle( kutusol , kutuust , kutusag , kutualt );
    
    while(1) {                
    tus=getch();
    switch(tus) {
                             case 72 :  //yon ust girildiyse basla
                                      --a; if(a>=0){ 
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutuust-=kutuhareket; 
                                      kutualt-=kutuhareket;
                                      if(kutuust<=50)  { 
                                                     kutuust=50;
                                                     kutualt=90;
                                                        }
                                      setcolor(11);
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      for(m=0;m<15;m++)yer=yer->onceki;
                                      }
                                      else a=0;
                                      break;  //yon ust girildiyse bitir
                                      
                                      
                             case 75 :  //yon sol girildiyse basla 
                                      --b; if(b>=0){
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutusol-=kutuhareket; 
                                      kutusag-=kutuhareket;
                                      if(kutusol<=50)  {
                                                     kutusol=50;
                                                     kutusag=90;
                                                        }
                                      setcolor(11); 
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      yer=yer->onceki;
                                      }
                                      else  b=0;
                                      break;  //yon sol girildiyse bitir
                                            
                                                  
                             case 77 :  //yon sag girildiyse basla
                                      ++b; if(b<=14){
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutusol=kutusol+kutuhareket; 
                                      kutusag=kutusag+kutuhareket;
                                      if(kutusag>=650)  { 
                                                     kutusol=610;
                                                     kutusag=650;
                                                        } 
                                      setcolor(11);                   
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      yer=yer->sonraki;
                                      }
                                      else  --b;
                                      break;  //yon sag girildiyse bitir
                                         
                                                             
                             case 80 : //yon alt girildiyse basla
                                      ++a; if(a<=14){
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutualt+=kutuhareket; 
                                      kutuust+=kutuhareket;
                                      if(kutualt>=650)  {
                                                     kutualt=650;
                                                     kutuust=610;
                                                        }
                                      setcolor(11);  
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      for(m=0;m<15;m++)yer=yer->sonraki;
                                      }
                                      else  --a;
                                      break;  //yon alt girildiyse bitir
                                      
                                      
                             case 49 :                  //ipucu eklemek için 1 e basýldýysa
                                      ipucuekle();
                                      ++harfsayisi;
                                      break;
                                      
                                      
                             case 50 :                  //oyunu kaydetmek için 2 ye basýldýysa
                                      gec=bas;
                                      kayitli=fopen("kayitlioyun.txt","w");
                                      
                                      while(dosyaharf!=NULL){
                                                             fprintf(kayitli,"%d%c",dosyaharf->harf_sayi,dosyaharf->harf);
                                                             dosyaharf=dosyaharf->sonraki;
                                                             }
                                      fprintf(kayitli,"\n");
                                      
                                      while(gec!=NULL){
                                                       fprintf(kayitli,"%d%s\n",gec->ipucu_sayi, gec->ipucu);
                                                       gec=gec->sonra;
                                                       }
                                      fclose(kayitli);
                                      settextstyle(1,0,17);
                                      outtextxy(665,250,"KAYDEDÝLÝYOR...");
                                      delay(500);
                                      setfillstyle(1,0);
                                      bar(665,250,1020,270);
                                      outtextxy(665,250,"KAYDEDÝLDÝ");
                                      delay(400);
                                      bar(665,250,1020,270);
                                      break;
                                      
                                      
                             case 51 :                     //oynamak için 3 e basýldýðýnda
                                      oyna();
                                      break;
                                      
                                      
                             case 52 :                     //çýkýþ için  4 e basýldýðýnda
                                      exit(1);
                                      break;
                                      
                                      
                             default :
                                      if(isalpha(tus)){
                                                       yer->harf=tus;
                                                       yer->harf_sayi=harfsayisi;
                                                       kelime[0]=tus;
                                                       settextstyle(6,0,1);
                                                       outtextxy( (kutusol+kutusag)/2-5 , (kutualt+kutuust)/2-5 , kelime);
                                                       ekrana_sayi_yaz();
                                                      }
                                      
                                      break;
                                      }
                                      
    }
    getch();
}

void ekrana_sayi_yaz(void)
{
     char ekran_kelime[2];
     int birler,onlar;
     
     ekran_kelime[1]='\0';
     
     if(yer->harf_sayi<10)
                          {
                          if(yer->harf_sayi==1)ekran_kelime[0]=bir;
                          if(yer->harf_sayi==2)ekran_kelime[0]=iki;
                          if(yer->harf_sayi==3)ekran_kelime[0]=uc;
                          if(yer->harf_sayi==4)ekran_kelime[0]=dort;
                          if(yer->harf_sayi==5)ekran_kelime[0]=bes;
                          if(yer->harf_sayi==6)ekran_kelime[0]=alti;
                          if(yer->harf_sayi==7)ekran_kelime[0]=yedi;
                          if(yer->harf_sayi==8)ekran_kelime[0]=sekiz;
                          if(yer->harf_sayi==9)ekran_kelime[0]=dokuz;
                          settextstyle(2,0,5);
                          outtextxy( kutusol+5 , kutuust+5 , ekran_kelime);
                          }
     else if(yer->harf_sayi>=10){
                                 onlar=(yer->harf_sayi)/10; birler=(yer->harf_sayi)%10;
                                 if(onlar==1)ekran_kelime[0]=bir;
                                 if(onlar==2)ekran_kelime[0]=iki;
                                 if(onlar==3)ekran_kelime[0]=uc;
                                 if(onlar==4)ekran_kelime[0]=dort;
                                 if(onlar==5)ekran_kelime[0]=bes;
                                 if(onlar==6)ekran_kelime[0]=alti;
                                 if(onlar==7)ekran_kelime[0]=yedi;
                                 if(onlar==8)ekran_kelime[0]=sekiz;
                                 if(onlar==9)ekran_kelime[0]=dokuz;
                                 settextstyle(2,0,5);
                                 outtextxy( kutusol+5 , kutuust+5 , ekran_kelime);
                                 
                                 if(birler==0)ekran_kelime[0]=sifir;
                                 if(birler==1)ekran_kelime[0]=bir;
                                 if(birler==2)ekran_kelime[0]=iki;
                                 if(birler==3)ekran_kelime[0]=uc;
                                 if(birler==4)ekran_kelime[0]=dort;
                                 if(birler==5)ekran_kelime[0]=bes;
                                 if(birler==6)ekran_kelime[0]=alti;
                                 if(birler==7)ekran_kelime[0]=yedi;
                                 if(birler==8)ekran_kelime[0]=sekiz;
                                 if(birler==9)ekran_kelime[0]=dokuz;
                                 settextstyle(2,0,5);
                                 outtextxy( kutusol+10 , kutuust+5 , ekran_kelime);
                                 }
}

void ipucu_sayisi_yaz(void)
{
     char ekran_kelime[2];
     int birler,onlar;
     int ipucu_sayisi_y=205;
     
     gec=bas;
     
     ekran_kelime[1]='\0';
     
     while(gec!=NULL)
     {
     
     if(gec->ipucu_sayi<10)
                          {
                          if(gec->ipucu_sayi==1)ekran_kelime[0]=bir;
                          if(gec->ipucu_sayi==2)ekran_kelime[0]=iki;
                          if(gec->ipucu_sayi==3)ekran_kelime[0]=uc;
                          if(gec->ipucu_sayi==4)ekran_kelime[0]=dort;
                          if(gec->ipucu_sayi==5)ekran_kelime[0]=bes;
                          if(gec->ipucu_sayi==6)ekran_kelime[0]=alti;
                          if(gec->ipucu_sayi==7)ekran_kelime[0]=yedi;
                          if(gec->ipucu_sayi==8)ekran_kelime[0]=sekiz;
                          if(gec->ipucu_sayi==9)ekran_kelime[0]=dokuz;
                          settextstyle(1,0,1);
                          outtextxy( 665 , ipucu_sayisi_y , ekran_kelime);
                          }
     else if(gec->ipucu_sayi>=10){
                                 onlar=(gec->ipucu_sayi)/10; birler=(gec->ipucu_sayi)%10;
                                 if(onlar==1)ekran_kelime[0]=bir;
                                 if(onlar==2)ekran_kelime[0]=iki;
                                 if(onlar==3)ekran_kelime[0]=uc;
                                 if(onlar==4)ekran_kelime[0]=dort;
                                 if(onlar==5)ekran_kelime[0]=bes;
                                 if(onlar==6)ekran_kelime[0]=alti;
                                 if(onlar==7)ekran_kelime[0]=yedi;
                                 if(onlar==8)ekran_kelime[0]=sekiz;
                                 if(onlar==9)ekran_kelime[0]=dokuz;
                                 settextstyle(1,0,1);
                                 outtextxy( 665 , ipucu_sayisi_y , ekran_kelime);
                                 
                                 if(birler==0)ekran_kelime[0]=sifir;
                                 if(birler==1)ekran_kelime[0]=bir;
                                 if(birler==2)ekran_kelime[0]=iki;
                                 if(birler==3)ekran_kelime[0]=uc;
                                 if(birler==4)ekran_kelime[0]=dort;
                                 if(birler==5)ekran_kelime[0]=bes;
                                 if(birler==6)ekran_kelime[0]=alti;
                                 if(birler==7)ekran_kelime[0]=yedi;
                                 if(birler==8)ekran_kelime[0]=sekiz;
                                 if(birler==9)ekran_kelime[0]=dokuz;
                                 settextstyle(1,0,1);
                                 outtextxy( 665 , ipucu_sayisi_y , ekran_kelime);
                                 }
     ipucu_sayisi_y+=25;
     gec=gec->sonra;
     }
}

void oynasayiyaz(void)
{
     char ekran_kelime[2];
     int birler,onlar,c,v;
     ekran_kelime[1]='\0';
     
     for(c=0;c<15;c++){
                       for(v=0;v<15;v++){
                                         if(tablo[c][v]>0){
                                                           if(tablo[c][v]<10)
                                                           {
                                                           if(tablo[c][v]==1)ekran_kelime[0]=bir;
                                                           if(tablo[c][v]==2)ekran_kelime[0]=iki;
                                                           if(tablo[c][v]==3)ekran_kelime[0]=uc;
                                                           if(tablo[c][v]==4)ekran_kelime[0]=dort;
                                                           if(tablo[c][v]==5)ekran_kelime[0]=bes;
                                                           if(tablo[c][v]==6)ekran_kelime[0]=alti;
                                                           if(tablo[c][v]==7)ekran_kelime[0]=yedi;
                                                           if(tablo[c][v]==8)ekran_kelime[0]=sekiz;
                                                           if(tablo[c][v]==9)ekran_kelime[0]=dokuz;
                                                           setcolor(11);
                                                           settextstyle(2,0,5);
                                                           outtextxy( v*40+50+5 , c*40+50+5 , ekran_kelime);
                                                           }
                                                           else if(tablo[c][v]>=10)
                                                           {
                                                           onlar=(tablo[c][v])/10; birler=(tablo[c][v])%10;
                                                           if(onlar==1)ekran_kelime[0]=bir;
                                                           if(onlar==2)ekran_kelime[0]=iki;
                                                           if(onlar==3)ekran_kelime[0]=uc;
                                                           if(onlar==4)ekran_kelime[0]=dort;
                                                           if(onlar==5)ekran_kelime[0]=bes;
                                                           if(onlar==6)ekran_kelime[0]=alti;
                                                           if(onlar==7)ekran_kelime[0]=yedi;
                                                           if(onlar==8)ekran_kelime[0]=sekiz;
                                                           if(onlar==9)ekran_kelime[0]=dokuz;
                                                           setcolor(11);
                                                           settextstyle(2,0,5);
                                                           outtextxy( v*40+50+5 , c*40+50+5 , ekran_kelime);
                                 
                                                           if(birler==0)ekran_kelime[0]=sifir;
                                                           if(birler==1)ekran_kelime[0]=bir;
                                                           if(birler==2)ekran_kelime[0]=iki;
                                                           if(birler==3)ekran_kelime[0]=uc;
                                                           if(birler==4)ekran_kelime[0]=dort;
                                                           if(birler==5)ekran_kelime[0]=bes;
                                                           if(birler==6)ekran_kelime[0]=alti;
                                                           if(birler==7)ekran_kelime[0]=yedi;
                                                           if(birler==8)ekran_kelime[0]=sekiz;
                                                           if(birler==9)ekran_kelime[0]=dokuz;
                                                           setcolor(11);
                                                           settextstyle(2,0,5);
                                                           outtextxy( v*40+50+10 , c*40+50+5 , ekran_kelime);
                                                           }
                                                           }
                                         }
                       }
}

void oyna(void)
{
     baslangic=time(NULL);
     char oyun_tus;
     char oynakelime[2];
     int p=0,y=0,a=0,b=0,m,s; 
     int grafik_y=205;
     
     oynakelime[1]='\0';
     tabloharf=ilk;
     for(s=1;s<=225;s++){
                        oynaekle();    
                        }
     oynayer=oynailk;
     
     for(p=0;p<15;p++){
                       for(y=0;y<15;y++){
                                         tablo[p][y]=tabloharf->harf_sayi;
                                         tabloharf=tabloharf->sonraki;
                                         }
                       }
     
     cleardevice();
                                      
     for(p=0;p<15;p++){
                       for(y=0;y<15;y++){
                                         if(tablo[p][y]!=0){
                                                            setlinestyle(0,0,0);
                                                            setcolor(1);                   
                                                            rectangle(y*40+50,p*40+50,y*40+90,p*40+90);
                                                            }
                                         }
                       }
     oynasayiyaz();
     setcolor(15);
     settextstyle(1,0,20);
     outtextxy(750,35,"WORD");
     settextstyle(1,0,29);
     outtextxy(665,65,"PUZZLE");
     rectangle(660,60,1010,135);
     settextstyle(1,0,17);
     outtextxy(665,180," ÝPUCU");
     line(665,195,740,195);
     ipucu_sayisi_yaz();
     gec=bas;
     while(gec!=NULL){
                      settextstyle(1,0,1);
                      outtextxy(690,grafik_y,gec->ipucu);
                      grafik_y+=25;
                      gec=gec->sonra;
                      }
     
                       
     for(p=0;p<15;p++){
                       for(y=0;y<15;y++){
                                         if(tablo[p][y]!=0){
                                                            a=p;
                                                            b=y;
                                                            goto z;
                                                            }
                                         }
                       }
     z:
     kutusol=b*40+50; kutuust=a*40+50; kutusag=b*40+90; kutualt=a*40+90;
     setcolor(11);
     rectangle( kutusol , kutuust , kutusag , kutualt );
     while(1)
     {
     oyun_tus=getch();
     switch(oyun_tus){
                 case 72 :  //yon ust girildiyse basla
                                      --a; 
                                      if(tablo[a][b]!=0)
                                      {
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutuust-=kutuhareket; 
                                      kutualt-=kutuhareket;
                                      if(kutuust<=50)  { 
                                                     kutuust=50;
                                                     kutualt=90;
                                                        }
                                      setcolor(11);
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      for(m=0;m<15;m++)oynayer=oynayer->oynaonceki;
                                      }
                                      else ++a;
                                      break;  //yon ust girildiyse bitir
                                      
                                      
                 case 75 :  //yon sol girildiyse basla 
                                      --b;
                                      if(tablo[a][b]!=0)
                                      {
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutusol-=kutuhareket; 
                                      kutusag-=kutuhareket;
                                      if(kutusol<=50)  { 
                                                     kutusol=50;
                                                     kutusag=90;
                                                        }
                                      setcolor(11); 
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      oynayer=oynayer->oynaonceki;
                                      }
                                      else ++b;
                                      break;  //yon sol girildiyse bitir
                                            
                                                  
                 case 77 :  //yon sag girildiyse basla
                                      ++b;
                                      if(tablo[a][b]!=0)
                                      {
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutusol=kutusol+kutuhareket; 
                                      kutusag=kutusag+kutuhareket;
                                      if(kutusag>=650)  { 
                                                     kutusol=610;
                                                     kutusag=650;
                                                        } 
                                      setcolor(11);                   
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      oynayer=oynayer->oynasonraki;
                                      }
                                      else  --b;
                                      break;  //yon sag girildiyse bitir
                                         
                                                             
                 case 80 : //yon alt girildiyse basla
                                      ++a;
                                      if(tablo[a][b]!=0)
                                      {
                                      setcolor(1);
                                      rectangle( kutusol , kutuust , kutusag , kutualt );
                                      kutualt+=kutuhareket; 
                                      kutuust+=kutuhareket;
                                      if(kutualt>=650)  { 
                                                     kutualt=650;
                                                     kutuust=610;
                                                        }
                                      setcolor(11);  
                                      rectangle( kutusol , kutuust , kutusag , kutualt ); //   bir sonraki kutuyu cizer.
                                      for(m=0;m<15;m++)oynayer=oynayer->oynasonraki;
                                      }
                                      else --a;
                                      break;  //yon alt girildiyse bitir
                 
                 
                 default :            
                                      if(isalpha(oyun_tus)){
                                                       oynayer->oynaharf=oyun_tus;
                                                       oynakelime[0]=oyun_tus;
                                                       settextstyle(6,0,1);
                                                       outtextxy( (kutusol+kutusag)/2-5 , (kutualt+kutuust)/2-5 , oynakelime);
                                                      }
                                      
                 }//switch sonu
                 
     if(kontrol())
     break;
     }//while sonu
     bitis=time(NULL);
     oynanansure=int(difftime(bitis,baslangic));
     puan_hesapla();
     puan_kaydet();
}


void puan_kaydet(void)
{
     int p,k,j,tut;
     int w=0;
     char kayit_harf;
     char kayit_kelime[10];
     char klm[2];
     char ilkharf1[20],ilkharf2[20],ilkharf3[20],isim[10];
     yaz=fopen("yeni.txt","r");
     fscanf(yaz,"%s%s%s\n",ilkharf1,ilkharf2,ilkharf3);
     for(p=0;p<10;p++){ 
                        fscanf(yaz,"%s",oyuncular[p].kayitad);
                        fscanf(yaz,"%d",&oyuncular[p].kayitpuan);
                        fscanf(yaz,"%d\n",&oyuncular[p].kayitsure);
                        }
     fclose(yaz);
     if(puan>oyuncular[9].kayitpuan) {
                                     setcolor(15);
                                     settextstyle(1,0,17);
                                     outtextxy(665,300,"ÝSÝM GÝRÝNÝZ");
                                     line(665,315,798,315);
                                     setcolor(15);
                                     outtextxy(660,320,":");
                                     klm[1]='\0';
                                     kayit_harf=getch();
                                     while(kayit_harf!=13){
                                                           klm[0]=kayit_harf;
                                                           kayit_kelime[w]=klm[0];
                                                           kayit_kelime[w+1]='\0';
                                                           settextstyle(1,0,17);
                                                           setcolor(11);
                                                           outtextxy(670,320,kayit_kelime);
                                                           kayit_harf=getch();
                                                           if(kayit_harf==13){
                                                                              kayit_kelime[w+1]='\0';
                                                                              }
                                                           w++;
                                                           }
                                     strcpy(oyuncular[9].kayitad,kayit_kelime);
                                     oyuncular[9].kayitpuan=puan;
                                     oyuncular[9].kayitsure=oynanansure;
                                     for(k=0;k<10;k++){
                                     for(j=0;j<9;j++){
                                                      if(oyuncular[j].kayitpuan<oyuncular[j+1].kayitpuan)
                                                                                               {             
                                                                  tut=oyuncular[j].kayitpuan;
                                                                  oyuncular[j].kayitpuan=oyuncular[j+1].kayitpuan;
                                                                  oyuncular[j+1].kayitpuan=tut;
                                                                  tut=oyuncular[j].kayitsure;
                                                                  oyuncular[j].kayitsure=oyuncular[j+1].kayitsure;
                                                                  oyuncular[j+1].kayitsure=tut;
                                                                  strcpy(isim,oyuncular[j].kayitad);
                                                                  strcpy(oyuncular[j].kayitad,oyuncular[j+1].kayitad);
                                                                  strcpy(oyuncular[j+1].kayitad,isim);
                                                                                                }
                                                      }
                                                      }
     
                                     }
     else{
          settextstyle(1,0,17);
          setcolor(11);
          outtextxy( 670 , 320 ,"DÜÞÜK PUAN");
          delay(400);
          }
     yaz=fopen("yeni.txt","w");
     fprintf(yaz, "%10s%10s%18s\n","ÝSÝM","PUAN","SÜRE(SANÝYE)");
     for(k=0;k<10;k++)fprintf(yaz, "%10s%10d%10d\n", oyuncular[k].kayitad ,oyuncular[k].kayitpuan,oyuncular[k].kayitsure);
     fclose(yaz);
     exit(1);
}


void puan_hesapla(void)
{
     oynakontrol=oynailk;
     harfkontrol=ilk;
     while(oynakontrol!=NULL){
                              if(oynakontrol->oynaharf!=0){
                                                           if(oynakontrol->oynaharf==harfkontrol->harf)
                                                           {
                                                           puan+=10;
                                                           }
                                                           }
                              oynakontrol=oynakontrol->oynasonraki;
                              harfkontrol=harfkontrol->sonraki;
                              }
     puan-=oynanansure;
}


int kontrol(void)
{
    int u,j,tablosayici=0,kontrolsayici=0;
    oynakontrol=oynailk;
    for(u=0;u<15;u++){
                      for(j=0;j<15;j++){
                                        if(tablo[u][j]!=0) ++tablosayici;
                                        }
                      }
                      
    while(oynakontrol!=NULL){
                             if(oynakontrol->oynaharf!=0) ++kontrolsayici;
                             oynakontrol=oynakontrol->oynasonraki;
                             }
    if(tablosayici==kontrolsayici) return 1;
    else return 0;
}


void ipucuekle(void)
{
     int w=0;
     char ipucu_harf;
     char ipucu_kelime[20];
     char klm[2];
     klm[1]='\0';
     
     ipucu_harf=getch();
     while(ipucu_harf!=13){
                           klm[0]=ipucu_harf;
                           ipucu_kelime[w]=klm[0];
                           ipucu_kelime[w+1]='\0';
                           settextstyle(1,0,17);
                           outtextxy(673,205,ipucu_kelime);
                           ipucu_harf=getch();
                           if(ipucu_harf==13){
                                              ipucu_kelime[w+1]='\0';
                                              setfillstyle(0,0);
                                              bar(673,205,1020,225);
                                              }
                           w++;
                           }
	 
	if(bas==NULL){// ilk kayitsa
	 
		bas=(ipucukayit *)malloc(sizeof(ipucukayit));
		strcpy(bas->ipucu,ipucu_kelime);
		bas->sonra =NULL;
		bas->once=NULL;
		enson= bas;
	}
	 
	else if(enson == bas){// ikinci kayitsa
	 
		enson=(ipucukayit *)malloc(sizeof(ipucukayit));
		strcpy(enson->ipucu,ipucu_kelime);
		bas->sonra = enson;
		enson->sonra =NULL;
		enson->once= bas;
	}
	 
	else{// ikiden fazla kayýt varsa
	 
		gec=(ipucukayit*)malloc(sizeof(ipucukayit));
		strcpy(gec->ipucu,ipucu_kelime);
		enson->sonra =gec;
		gec->once= enson;	
		enson=gec;
		enson->sonra =NULL;//bu iki satýrda da son iþaretçisi son gelen veriye aktarýldý.
	}
	enson->ipucu_sayi=ipucusayisi;
	++ipucusayisi;
	

}


void ekle(void)
{
     Kayit *yeni;
     
     yeni=(Kayit *)malloc(sizeof(Kayit));
     yeni->harf_sayi=0;
     yeni->harf=0;
     if(ilk!=0)
               {
               son->sonraki=yeni;
               yeni->onceki=son;
               son=yeni;
               son->sonraki='\0';
               }
    else
        {
        ilk=yeni;
        son=ilk;
        ilk->onceki='\0';
        ilk->sonraki='\0';
        }
}


void oynaekle(void)
{
     oynakayit *oynayeni;
     
     oynayeni=(oynakayit *)malloc(sizeof(oynakayit));
     oynayeni->oynaharf=0;
     if(oynailk!=0)
               {
               oynason->oynasonraki=oynayeni;
               oynayeni->oynaonceki=oynason;
               oynason=oynayeni;
               oynason->oynasonraki='\0';
               }
    else
        {
        oynailk=oynayeni;
        oynason=oynailk;
        oynailk->oynaonceki='\0';
        oynailk->oynasonraki='\0';
        }
}

void menu(void)
{
     int kayx1=25,kayx2=300,sallama;
     int hareket1=1,hareket2=-1;
     
     PlaySound("oyun_muzigi.wav",NULL,SND_FILENAME|SND_ASYNC);
     
     setcolor(4);
     settextstyle(1,0,28);
     outtextxy(150,500,"1 - YENÝ PUZZLE");
     outtextxy(150,600,"2 - ÇIKIÞ");
     
     while(1){
              if(kbhit()){
                          goto git;
                          }
              setcolor(0);
              settextstyle(1,0,32);
              outtextxy(kayx1,50," WORD ");
              outtextxy(kayx2,200,"PUZZLE");
              kayx1+=hareket1;
              if(kayx1==300 || kayx1<25)hareket1*=-1;
              kayx2+=hareket2;
              if(kayx2==25 || kayx2>300)hareket2*=-1;
              sallama=rand()%14+1;
              setcolor(sallama);
              settextstyle(1,0,32);
              outtextxy(kayx1,50," WORD ");
              outtextxy(kayx2,200,"PUZZLE");
              delay(5);
              }
              
     git:    
     buton=getch();
    
     
     
}
