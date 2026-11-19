#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Mahasiswa {
    char nama[50];
    char NRP[20];
    float nilai_akhir;
    char indeks[3];
};

int konfirmasi();
void tambah_mahasiswa(struct Mahasiswa *mhs, int *jumlah);
void input_nilai(struct Mahasiswa mhs[], int jumlah);
void tampilkan_data(struct Mahasiswa mhs[], int jumlah);
void cari_mahasiswa(struct Mahasiswa mhs[], int jumlah);
int cari_nilai_tertinggi(struct Mahasiswa mhs[], int n);
void tampilkan_nilai_tertinggi(struct Mahasiswa mhs[], int jumlah);
void tampilkan_statistik(struct Mahasiswa mhs[], int jumlah);
void tampilkan_persentase_kelulusan(struct Mahasiswa mhs[], int jumlah);

int main() {
    struct Mahasiswa data_mhs[100];
    int jumlah_mhs = 0;
    int pilihan;

    do {
        system("cls");

        printf("=================================================\n");
        printf("           SISTEM PENILAIAN MAHASISWA            \n");
        printf("=================================================\n");
        printf("1.Tambah Data Mahasiswa\n");
        printf("2.Input Nilai Mata Kuliah\n");
        printf("3.Tampilkan Data Mahasiswa\n");
        printf("4.Cari Mahasiswa\n");
        printf("5.Tampilkan Nilai Tertinggi\n");
        printf("6.Statistik Nilai\n");
        printf("7.Tampilkan Persentase Kelulusan\n");
        printf("0.Keluar\n");
        printf("=================================================\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        printf("\n");
        getchar();

        switch(pilihan) {
            case 1:
                tambah_mahasiswa(&data_mhs[jumlah_mhs], &jumlah_mhs);
                break;

            case 2:
                input_nilai(data_mhs, jumlah_mhs);
                break;

            case 3:
                tampilkan_data(data_mhs, jumlah_mhs);
                break;

            case 4:
                cari_mahasiswa(data_mhs, jumlah_mhs);
                break;

            case 5:
                tampilkan_nilai_tertinggi(data_mhs, jumlah_mhs);
                break;

            case 6:
                tampilkan_statistik(data_mhs, jumlah_mhs);
                break;
            
            case 7:
                tampilkan_persentase_kelulusan(data_mhs, jumlah_mhs);
                break;
            
            case 0:
                printf("Keluar dari program. Terima kasih!\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }
        
        if (pilihan != 0) {
            printf("\n");
            pilihan = konfirmasi();
        }

    } while(pilihan != 0);

    return 0;
}

int konfirmasi() {
    char kembali;
    while(1) {
        printf("Kembali ke menu utama? (Y/N): ");
        scanf(" %c", &kembali);

        while(getchar() != '\n');

        if (kembali == 'Y' || kembali == 'y') {
            return 1;
        } else if (kembali == 'N' || kembali == 'n') {
            printf("\nKeluar dari program. Terima kasih!\n");
            return 0;
        } else {
            printf("Peringatan: Input tidak valid! Silakan masukkan huruf Y atau N.\n");
        }
    }
}

void tambah_mahasiswa(struct Mahasiswa *mhs, int *jumlah) {
    if (*jumlah >= 100) {
        printf("Kapasitas penyimpanan penuh (maksimal 100 mahasiswa)!\n");
        return;
    }

    printf("--------- Tambah Data Mahasiswa ---------\n");
    printf("Masukkan Nama: ");
    fgets(mhs->nama, sizeof(mhs->nama), stdin);
    mhs->nama[strcspn(mhs->nama, "\n")] = '\0';
    printf("Masukkan NRP: ");
    fgets(mhs->NRP, sizeof(mhs->NRP), stdin);
    mhs->NRP[strcspn(mhs->NRP, "\n")] = '\0';
    printf("-----------------------------------------\n");

    mhs->nilai_akhir = 0; 
    strcpy(mhs->indeks, "E");
    
    (*jumlah)++;
    printf("Data berhasil ditambahkan!\n");
}

void input_nilai(struct Mahasiswa mhs[], int jumlah) {
    if (jumlah == 0) {
        printf("Data mahasiswa masih kosong!\n");
        return;
    }

    for (int i = 0; i < jumlah; i++) {
        int jumlah_matkul;
        float total_nilai = 0;

        printf("--------- Input Nilai Mahasiswa ---------\n");
        printf("Input nilai untuk %s (%s):\n", mhs[i].nama, mhs[i].NRP);
        printf("Jumlah mata kuliah : ");
        scanf("%d", &jumlah_matkul);
        for (int j = 1; j <= jumlah_matkul; j++) {
            float nilai_matkul;
            printf("Nilai Mata Kuliah ke-%d: ", j); 
            scanf("%f",&nilai_matkul);

            total_nilai += nilai_matkul;
        }
        printf("-----------------------------------------\n");

        if (jumlah_matkul > 0) {
            mhs[i].nilai_akhir = total_nilai / jumlah_matkul;
        } else {
            mhs[i].nilai_akhir = 0;
        }
        
        if (mhs[i].nilai_akhir >= 86) {
            strcpy(mhs[i].indeks, "A");
        } else if (mhs[i].nilai_akhir >= 76) {
            strcpy(mhs[i].indeks, "AB");
        } else if (mhs[i].nilai_akhir >= 66) {
            strcpy(mhs[i].indeks, "B");
        } else if (mhs[i].nilai_akhir >= 61) {
            strcpy(mhs[i].indeks, "BC");
        } else if (mhs[i].nilai_akhir >= 56) {
            strcpy(mhs[i].indeks, "C");
        } else if (mhs[i].nilai_akhir >= 41) {
            strcpy(mhs[i].indeks, "D");
        } else {
            strcpy(mhs[i].indeks, "E");
        }
    }

    printf("Nilai berhasil diinput!\n");
}

void tampilkan_data(struct Mahasiswa mhs[], int jumlah) {
    if (jumlah == 0) {
        printf("Data mahasiswa masih kosong!\n");
        return;
    }

    printf("======================================================================\n");
    printf("                            DATA MAHASISWA                            \n");
    printf("======================================================================\n");
    printf("| %-3s | %-20s | %-12s | %-11s | %-5s |\n", "No", "Nama", "NRP", "Nilai Akhir", "Grade");
    printf("======================================================================\n");
    for (int i = 0; i < jumlah; i++) {
        printf("| %-3d | %-20s | %-12s | %-11.2f | %-5s |\n", i + 1, mhs[i].nama, mhs[i].NRP, mhs[i].nilai_akhir, mhs[i].indeks);
    }
    printf("======================================================================\n");
}

void cari_mahasiswa(struct Mahasiswa mhs[], int jumlah) {
    if (jumlah == 0) {
        printf("Data mahasiswa masih kosong!\n");
        return;
    }

    char kata_kunci[50];
    int ditemukan = 0;

    printf("Masukkan Nama atau NRP: ");
    fgets(kata_kunci, sizeof(kata_kunci), stdin);
    kata_kunci[strcspn(kata_kunci, "\n")] = '\0';

    printf("------------------------ Hasil Pencarian ------------------------\n");
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(mhs[i].nama, kata_kunci) == 0 || strcmp(mhs[i].NRP, kata_kunci) == 0) {
            printf("Nama: %s | NRP: %s | Nilai Akhir: %.2f | Grade: %s\n", mhs[i].nama, mhs[i].NRP, mhs[i].nilai_akhir, mhs[i].indeks);
            ditemukan = 1;
        }
    }
    if (!ditemukan) {
        printf("Mahasiswa dengan Nama/NRP '%s' tidak ditemukan.\n", kata_kunci);
    }
    printf("-----------------------------------------------------------------\n");
}

int cari_nilai_tertinggi(struct Mahasiswa mhs[], int n) {
    if (n == 1) {
        return 0;
    }

    int pemilik_nilai_tertinggi = cari_nilai_tertinggi(mhs, n - 1);

    if (mhs[n - 1].nilai_akhir > mhs[pemilik_nilai_tertinggi].nilai_akhir) {
        return n - 1;
    } else {
        return pemilik_nilai_tertinggi;
    }
}

void tampilkan_nilai_tertinggi(struct Mahasiswa mhs[], int jumlah) {
    if (jumlah > 0) {
        int max = cari_nilai_tertinggi(mhs, jumlah);
        printf("--- MAHASISWA DENGAN NILAI TERTINGGI ---\n");
        printf("Nama        : %s\n", mhs[max].nama);
        printf("NRP         : %s\n", mhs[max].NRP);
        printf("Nilai Akhir : %.2f\n", mhs[max].nilai_akhir);
        printf("Grade       : %s\n", mhs[max].indeks);
        printf("----------------------------------------\n");
    } else {
        printf("Data mahasiswa masih kosong.\n");
    }
}

void tampilkan_statistik(struct Mahasiswa mhs[], int jumlah) {
    if (jumlah == 0) {
        printf("Data mahasiswa masih kosong!\n");
        return;
    }

    float total_nilai = 0;
    int A = 0, AB = 0, B = 0, BC = 0, C = 0, D = 0, E = 0;

    int i = 0;
    while (i < jumlah) {
        total_nilai += mhs[i].nilai_akhir;
        if (strcmp(mhs[i].indeks, "A") == 0) {
            A++;
        } else if (strcmp(mhs[i].indeks, "AB") == 0) {
            AB++;
        } else if (strcmp(mhs[i].indeks, "B") == 0) {
            B++;
        } else if (strcmp(mhs[i].indeks, "BC") == 0) {
            BC++;
        } else if (strcmp(mhs[i].indeks, "C") == 0) {
            C++;
        } else if (strcmp(mhs[i].indeks, "D") == 0) {
            D++;
        } else if (strcmp(mhs[i].indeks, "E") == 0) {
            E++;
        }
        i++;
    }

    float rata_rata = total_nilai / jumlah;

    printf("=================================================\n");
    printf("               STATISTIK NILAI KELAS             \n");
    printf("=================================================\n");
    printf("Total Mahasiswa      : %d mahasiswa\n", jumlah);
    printf("Rata-rata Nilai Kelas: %.2f\n", rata_rata);
    printf("-------------------------------------------------\n");
    printf("Distribusi Grade:\n");
    printf("- Grade A  : %d mahasiswa\n", A);
    printf("- Grade AB : %d mahasiswa\n", AB);
    printf("- Grade B  : %d mahasiswa\n", B);
    printf("- Grade BC : %d mahasiswa\n", BC);
    printf("- Grade C  : %d mahasiswa\n", C);
    printf("- Grade D  : %d mahasiswa\n", D);
    printf("- Grade E  : %d mahasiswa\n", E);
    printf("=================================================\n");
}

void tampilkan_persentase_kelulusan(struct Mahasiswa mhs[], int jumlah) {
    if (jumlah == 0) {
        printf("Data mahasiswa masih kosong!\n");
        return;
    }

    int lulus = 0;
    int tidak_lulus = 0;

    for (int i = 0; i < jumlah; i++) {
        if (mhs[i].nilai_akhir >= 56.0) {
            lulus++;
        } else {
            tidak_lulus++;
        }
    }

    float persentase_lulus = ((float)lulus / jumlah) * 100.0;
    float persentase_tidak_lulus = ((float)tidak_lulus / jumlah) * 100.0;

    printf("=================================================\n");
    printf("            PERSENTASE KELULUSAN KELAS           \n");
    printf("=================================================\n");
    printf("Total Mahasiswa      : %d mahasiswa\n", jumlah);
    printf("Jumlah Lulus         : %d mahasiswa (%.2f%%)\n", lulus, persentase_lulus);
    printf("Jumlah Tidak Lulus   : %d mahasiswa (%.2f%%)\n", tidak_lulus, persentase_tidak_lulus);
    printf("=================================================\n");
}