#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define FONK_SAYISI 3
#define QUANTUM 2000 // milisaniye

void ledYak(){
    printf("Led yandi.\n");
}

void sensorOku(){
    printf("Sensor calistir.\n");
}

void mesaj(){
    printf("Kullaniciya mesaj gonderildi.\n");
}

typedef struct{

    int kalan_sure;
    void(*gorevler)(void); 
    bool tamamlandi;

}Islemler;

int main(){

    Islemler islemler[] ={

        {5000, ledYak, false},
        {7000, sensorOku, false},
        {3000, mesaj, false}

    };
   
    int n = sizeof(islemler) / sizeof(islemler[0]); // eleman sayısı

    int tamamlananlar = 0;
    while(tamamlananlar < n){
        for(int i = 0; i<n; i++){
            if(islemler[i].tamamlandi)
             continue;

            islemler[i].gorevler(); // fonksiyon çağırmak için () gerekir

            if(islemler[i].kalan_sure > QUANTUM){
                Sleep(QUANTUM);
                islemler[i].kalan_sure -=QUANTUM;
                printf("QUANTUM suresi doldu. Kalan sure %d ms\n", islemler[i].kalan_sure / 1000);
            }
            else{
                Sleep(islemler[i].kalan_sure);
                islemler[i].kalan_sure = 0;
                islemler[i].tamamlandi = true;
                tamamlananlar ++;
                printf("Tamamlandi\n");
            }

        }
    }

    printf("Tum islemler tamamlandi.\n");
    return 0;

}

