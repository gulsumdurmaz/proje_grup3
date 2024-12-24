#include <stdio.h>
#define max_personel 50 // Maksimum personel sayısı 50

// Veri yapısını tanımlayalım
typedef struct {
    int sicil_no;
    char ad[50];
    char soyad[50];
    int satis; // Satış miktarı
} Personel;

int main() {
    FILE *yillikDosya, *satisDosya; // Dosya işaretçileri
    Personel personeller[max_personel]; // Personel bilgilerini tutacak dizi
    int i, n = 0; // i: Döngü Değişkeni, n:Personel Sayacı
    int max_satis = 0; // Maksimum satış miktarı

    // Giriş dosyasını aç
    yillikDosya = fopen("yillik.dat", "r"); //r modu dosyayı okumak için açar
    if (yillikDosya == NULL) { //yıllık dosyası mevcut değilse null döner
        printf("yillik.dat dosyasi acilamadi.\n");
        return 1; //Hata kodu
    }

    // yillik.dat dosyasından personel bilgilerini oku
    while (fscanf(yillikDosya, "%d %s %s %d", &personeller[n].sicil_no, personeller[n].ad, personeller[n].soyad, &personeller[n].satis) != EOF) {
        //EOF(end of file): dosyanın sonuna gelindiğini,okuyacak başka değer kalmadığını gösterir
        if (personeller[n].satis > max_satis) { // Maksimum satış miktarını bulmak için
            max_satis = personeller[n].satis;
        }
        n++; // Personel sayısını arttır
    }

    fclose(yillikDosya); // Dosyayı kapat

    // Çıkış dosyasını oluştur
    satisDosya = fopen("satislar.dat", "w"); //w modunda dosyadaki eski içerik silinerek yenisi yazılır
    if (satisDosya == NULL) {  //satışlar dosyası bulunamadığında NULL döner
        printf("satislar.dat dosyasi olusturulamadi.\n");
        return 1;
    }

    // Her personelin ne kadar daha satış yapması gerektiğinin hesabı
    for (i = 0; i < n; i++) {
        int fark = max_satis - personeller[i].satis; // Farkı hesapla
        fprintf(satisDosya, "%d %s %s %d\n", personeller[i].sicil_no, personeller[i].ad,personeller[i].soyad, fark);
    }

    fclose(satisDosya); // Dosyayı kapat

    printf("\nSatislar.dat dosyasi basariyla olusturuldu.\n");

    return 0;
}
