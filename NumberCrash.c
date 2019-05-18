#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int patlat(int oyunAlani[][100],int boy,int en,int i,int j,int *patlama, int kontrol, int *count)
{
    int patlamaVarMi = 0,max;
    (*count)++;
    max = boy*en;
    if((*count)<=max) // sonsuz döngüyü engellemek icin
    {
        if((i-1>=0) && (oyunAlani[i][j] == oyunAlani[i-1][j]) && (kontrol != 3)) // Fonksiyona girilen inidisin yukari komşuluk baglantısını kontrol eder
        {
            patlat(oyunAlani,boy, en, i-1, j,patlama,1,count);
            patlamaVarMi = 1;
        }
        if((i+1<boy) && (oyunAlani[i][j] == oyunAlani[i+1][j]) && (kontrol != 1)) // Fonksiyona girilen inidisin aşağı komşuluk baglantısını kontrol eder
        {
            patlat(oyunAlani,boy, en, i+1, j,patlama,3,count);
            patlamaVarMi = 1;
        }
        if((j+1<en) && (oyunAlani[i][j] == oyunAlani[i][j+1]) && (kontrol != 2)) // Fonksiyona girilen inidisin sağ komşuluk baglantısını kontrol eder
        {
            patlat(oyunAlani,boy, en, i, j+1,patlama,4,count);
            patlamaVarMi = 1;
        }
        if((j-1>=0) && (oyunAlani[i][j] == oyunAlani[i][j-1]) && (kontrol != 4)) // Fonksiyona girilen inidisin sol komşuluk baglantısını kontrol eder
        {
            patlat(oyunAlani,boy, en, i, j-1,patlama,2,count);
            patlamaVarMi = 1;
        }
    }
    if ((patlamaVarMi == 1) || (kontrol != 0)) // patlama var ise patlama olan yerdeki indisi negatif bir sayi ile değiştirir
    {                                          // bu sayede patlama olmuş gibi gözükür
        oyunAlani[i][j] = (*patlama)--;
        return 1;
    }
    return 0;
}
void dusme(int oyunAlani[][100],int boy,int en)
{
    int i,j,kaymaBas = 0,tmp,kontrol;
    for(j=0;j<en;j++)
    {
        i=boy-1;
        kontrol = 0;
        while(i>=0)
        {
            while((oyunAlani[i][j] >= 0) && (kontrol == 0))
            {
                i--;
                if(i<0)
                    break;
            }
            if(i>=0)
            {
                while(oyunAlani[i][j] < 0)
                {
                    if(kontrol == 0)
                    {
                        kontrol = 1;
                        kaymaBas = i; // ilk boslugu kaydedip diger elemanaları buradan baslayarak kaydırmak icin
                    }
                    i--;
                }
            }
            if((i>=0) && (kontrol == 1))
            {
                if(oyunAlani[i][j] >= 0) //elemanları kaydırma
                {
                    tmp = oyunAlani[kaymaBas][j];
                    oyunAlani[kaymaBas][j] = oyunAlani[i][j];
                    oyunAlani[i][j] = tmp;
                    kaymaBas--;
                    i--;
                }
            }
        }
    }
}
void yazdir(int oyunAlani[][100],int boy,int en) // Matrisi ekrana yazdirma
{
    system("clear");
    int i,j;
    printf("\n\n\n\n\n");
    for(i=0;i<boy;i++)
    {
        printf("\t\t\t\t");
        for(j=0;j<en;j++)
        {
            if (oyunAlani[i][j] < 0) {
                printf("  ");
            }
            else
            {
                printf("%d ",oyunAlani[i][j]);
            }
        }
        
        printf("\n");
    }
}
void boslukDoldur(int oyunAlani[][100],int boy, int en, int *patlamaSayisi) //Bosluklari doldurma
{
    srand(time(NULL));
    int i,j;
    for (i=0; i<boy; i++) {
        for (j=0; j<en ; j++) {
            if(oyunAlani[i][j] < 0)
            {
                (*patlamaSayisi)++;
                oyunAlani[i][j] = rand() % 10;
            }
        }
    }
}
void tusaBas() // Devam etmek icin herhangi bi tusa bas
{
    char ch;
    ch = getchar();
}
char devamMi()
{
    char ch;
    ch = getchar();
    return ch;
}
void degistir(int oyunAlani[][100]) //indisleri degistirmek icin kullanılan fonksiyon
{
    int x1,x2,y1,y2,tmp;
    printf("\nYer degistiricek elemanlarin indislerini veriniz :\n");
    scanf("%d,%d    %d,%d",&x1,&y1,&x2,&y2);
    tmp = oyunAlani[x1][y1];
    oyunAlani[x1][y1] = oyunAlani[x2][y2];
    oyunAlani[x2][y2] = tmp;
}

int main(int argc, const char * argv[]) {
    srand(time(NULL));
    static int oyunAlani[100][100];
    int satir,sutun,i,j,count,patlama = -1,kontrol1,kontrol2,kontrol3 = 0,patlamaSayisi = 0;
    char secim;
    printf("Oyun alaninin satir ve sutun sayisini veriniz :");
    scanf("%d %d",&satir,&sutun);
    for(i=0;i<satir;i++)  // Kullanicidan alınan satir ve sutun sayilarina göre matris olusturulur
    {
        for(j=0;j<sutun;j++)
        {
            oyunAlani[i][j] = rand() % 10;
        }
    }
    do
    {
        if (kontrol3 > 0) {  // ilk dongude degistirme olmadıgı icin burayı es gecer
            degistir(oyunAlani);
        }
        
        yazdir(oyunAlani, satir, sutun);
        do
        {
            kontrol2 = 0;
            do
            {
                kontrol1 = 0;
                for (i=0; i<satir; i++) {          // Her döngüde matrisin indislerini patlat fonksiyonuna göndeririz 
                    for (j=0; j<sutun; j++) {      // patlama varsa matristeki degerler negatif başka bir sayi ile değiştirilir
                        count = 0;
                        kontrol1 += patlat(oyunAlani, satir, sutun, i, j, &patlama, 0,&count);
                    }
                }
                tusaBas();
                tusaBas();
                yazdir(oyunAlani, satir, sutun);
                tusaBas();
                dusme(oyunAlani, satir, sutun);
                yazdir(oyunAlani, satir, sutun);
            }while(kontrol1>0);
            i=0;
            j=0;
            while ((i<satir) && (kontrol2 == 0)) {
                while ((j<sutun) && (kontrol2 == 0)) {
                    if (oyunAlani[i][j] < 0) {
                        kontrol2 = 1;
                    }
                    j++;
                }
                i++;
            }
            tusaBas();
            boslukDoldur(oyunAlani, satir, sutun,&patlamaSayisi);
            yazdir(oyunAlani, satir, sutun);
        }while(kontrol2 == 1);
        
        
        printf("\n\n\nDevam etmek istiyor musunuz ?(E/H)");
        secim = devamMi();
        kontrol3++;
    }while((secim == 'e') || (secim == 'E')); // game loop
    
    printf("\n\nPuaniniz :%d\n",patlamaSayisi*patlamaSayisi); // Puan = patlama^2
    return 0;
    
}


