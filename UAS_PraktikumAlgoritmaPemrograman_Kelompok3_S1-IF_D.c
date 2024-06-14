#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum StatusPeminjaman {
    Tersedia,
    Dipinjam
};

struct Buku {
    char judul[50];
    char penulis[50];
    int tahunTerbit;
    enum StatusPeminjaman status;
};

struct Peminjaman {
    char nama[50];
    char nim[20];
    char judulBuku[50];
    char tanggalPeminjaman[11]; // Format: YYYY-MM-DD
    char tanggalPengembalian[11]; // Format: YYYY-MM-DD
};

struct Buku daftarBuku[100];
struct Peminjaman daftarPeminjaman[100];
int jumlahBuku = 0;
int jumlahPeminjaman = 0;

void bacaDariBerkas(struct Buku *daftarBuku, int *jumlahBuku) {
    FILE *file = fopen("daftar_buku.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka berkas. Mungkin ini adalah eksekusi pertama program.\n");
        return;
    }

    while (fscanf(file, " %[^;];%[^;];%d;%d", daftarBuku[*jumlahBuku].judul,
                  daftarBuku[*jumlahBuku].penulis, &daftarBuku[*jumlahBuku].tahunTerbit,
                  &daftarBuku[*jumlahBuku].status) == 4) {
        (*jumlahBuku)++;
    }

    fclose(file);
}

void tampilkanDaftarBuku(struct Buku *daftarBuku, int jumlahBuku) {
    printf("\n=== Daftar Buku ===\n");
    printf("%-30s%-20s%-15s%s\n", "Judul", "Penulis", "Tahun Terbit", "Status");
    for (int i = 0; i < jumlahBuku; i++) {
        printf("%-30s%-20s%-15d", daftarBuku[i].judul, daftarBuku[i].penulis, daftarBuku[i].tahunTerbit);
        if (daftarBuku[i].status == Tersedia) {
            printf("Tersedia\n");
        } else {
            printf("Dipinjam\n");
        }
    }
}

void tampilkanDaftarPeminjaman(struct Peminjaman *daftarPeminjaman, int jumlahPeminjaman) {
    printf("\n=== Daftar Peminjaman ===\n");
    printf("%-30s%-20s%-30s%-15s%s\n", "Nama", "NIM", "Judul Buku", "Tanggal Peminjaman", "  Tenggang Pengembalian");
    for (int i = 0; i < jumlahPeminjaman; i++) {
        printf("%-30s%-20s%-30s%-15s     %s\n", daftarPeminjaman[i].nama, daftarPeminjaman[i].nim, daftarPeminjaman[i].judulBuku, daftarPeminjaman[i].tanggalPeminjaman, daftarPeminjaman[i].tanggalPengembalian);
    }
}

void tambahTanggalPengembalian(char *tanggalPeminjaman, char *tanggalPengembalian) {
    struct tm waktuPinjam = {0};
    sscanf(tanggalPeminjaman, "%4d-%2d-%2d", &waktuPinjam.tm_year, &waktuPinjam.tm_mon, &waktuPinjam.tm_mday);
    waktuPinjam.tm_year -= 1900;
    waktuPinjam.tm_mon -= 1;
    waktuPinjam.tm_mday += 14;
    mktime(&waktuPinjam);
    strftime(tanggalPengembalian, 11, "%Y-%m-%d", &waktuPinjam);
}

void pinjamBuku(struct Buku *daftarBuku, int jumlahBuku, struct Peminjaman *daftarPeminjaman, int *jumlahPeminjaman) {
    char judulCari[50];
    printf("\nMasukkan judul buku yang ingin dipinjam: ");
    scanf(" %[^\n]", judulCari);

    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].judul, judulCari) == 0 && daftarBuku[i].status == Tersedia) {
            daftarBuku[i].status = Dipinjam;

            struct Peminjaman peminjaman;
            printf("Masukkan nama: ");
            scanf(" %[^\n]", peminjaman.nama);
            printf("Masukkan NIM: ");
            scanf(" %[^\n]", peminjaman.nim);
            strcpy(peminjaman.judulBuku, judulCari);
            printf("Masukkan tanggal peminjaman (YYYY-MM-DD): ");
            scanf(" %[^\n]", peminjaman.tanggalPeminjaman);

            tambahTanggalPengembalian(peminjaman.tanggalPeminjaman, peminjaman.tanggalPengembalian);

            daftarPeminjaman[*jumlahPeminjaman] = peminjaman;
            (*jumlahPeminjaman)++;

            printf("Buku '%s' berhasil dipinjam. Tenggat pengembalian: %s\n", judulCari, peminjaman.tanggalPengembalian);
            return;
        }
    }

    printf("Buku dengan judul '%s' tidak ditemukan atau sedang dipinjam.\n", judulCari);
}

void kembalikanBuku(struct Buku *daftarBuku, int jumlahBuku, struct Peminjaman *daftarPeminjaman, int *jumlahPeminjaman) {
    char judulCari[50];
    printf("\nMasukkan judul buku yang ingin dikembalikan: ");
    scanf(" %[^\n]", judulCari);

    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftarBuku[i].judul, judulCari) == 0 && daftarBuku[i].status == Dipinjam) {
            daftarBuku[i].status = Tersedia;

            // Menghapus data peminjaman
            for (int j = 0; j < *jumlahPeminjaman; j++) {
                if (strcmp(daftarPeminjaman[j].judulBuku, judulCari) == 0) {
                    for (int k = j; k < *jumlahPeminjaman - 1; k++) {
                        daftarPeminjaman[k] = daftarPeminjaman[k + 1];
                    }
                    (*jumlahPeminjaman)--;
                    break;
                }
            }

            printf("Buku '%s' berhasil dikembalikan.\n", judulCari);
            return;
        }
    }

    printf("Buku dengan judul '%s' tidak ditemukan atau tidak sedang dipinjam.\n", judulCari);
}

void simpanKeBerkas(struct Buku *daftarBuku, int jumlahBuku, struct Peminjaman *daftarPeminjaman, int jumlahPeminjaman) {
    FILE *file = fopen("daftar_buku.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka berkas.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < jumlahBuku; i++) {
        fprintf(file, "%s;%s;%d;%d\n", daftarBuku[i].judul, daftarBuku[i].penulis,
                daftarBuku[i].tahunTerbit, daftarBuku[i].status);
    }

    fclose(file);

    file = fopen("daftar_peminjaman.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka berkas peminjaman.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < jumlahPeminjaman; i++) {
        fprintf(file, "%s;%s;%s;%s;%s\n", daftarPeminjaman[i].nama, daftarPeminjaman[i].nim,
                daftarPeminjaman[i].judulBuku, daftarPeminjaman[i].tanggalPeminjaman, daftarPeminjaman[i].tanggalPengembalian);
    }

    fclose(file);
}

void bacaPeminjamanDariBerkas(struct Peminjaman *daftarPeminjaman, int *jumlahPeminjaman) {
    FILE *file = fopen("daftar_peminjaman.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka berkas peminjaman. Mungkin ini adalah eksekusi pertama program.\n");
        return;
    }

    while (fscanf(file, " %[^;];%[^;];%[^;];%[^;];%s", daftarPeminjaman[*jumlahPeminjaman].nama,
                  daftarPeminjaman[*jumlahPeminjaman].nim, daftarPeminjaman[*jumlahPeminjaman].judulBuku,
                  daftarPeminjaman[*jumlahPeminjaman].tanggalPeminjaman, daftarPeminjaman[*jumlahPeminjaman].tanggalPengembalian) == 5) {
        (*jumlahPeminjaman)++;
    }

    fclose(file);
}

void selectionSort(struct Buku *daftarBuku, int jumlahBuku) {
    for (int i = 0; i < jumlahBuku - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahBuku; j++) {
            if (strcmp(daftarBuku[j].judul, daftarBuku[minIdx].judul) < 0) {
                minIdx = j;
            }
        }
        struct Buku temp = daftarBuku[minIdx];
        daftarBuku[minIdx] = daftarBuku[i];
        daftarBuku[i] = temp;
    }
    printf("Daftar buku berhasil diurutkan berdasarkan judul menggunakan Selection Sort.\n");
}

void insertionSort(struct Peminjaman *daftarPeminjaman, int jumlahPeminjaman) {
    for (int i = 1; i < jumlahPeminjaman; i++) {
        struct Peminjaman key = daftarPeminjaman[i];
        int j = i - 1;
        while (j >= 0 && strcmp(daftarPeminjaman[j].nim, key.nim) > 0) {
            daftarPeminjaman[j + 1] = daftarPeminjaman[j];
            j = j - 1;
        }
        daftarPeminjaman[j + 1] = key;
    }
    printf("Daftar peminjaman berhasil diurutkan berdasarkan NIM menggunakan Insertion Sort.\n");
}

void merge(struct Peminjaman *daftarPeminjaman, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    struct Peminjaman L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = daftarPeminjaman[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = daftarPeminjaman[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i].tanggalPengembalian, R[j].tanggalPengembalian) <= 0) {
            daftarPeminjaman[k] = L[i];
            i++;
        } else {
            daftarPeminjaman[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        daftarPeminjaman[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        daftarPeminjaman[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Peminjaman *daftarPeminjaman, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(daftarPeminjaman, l, m);
        mergeSort(daftarPeminjaman, m + 1, r);
        merge(daftarPeminjaman, l, m, r);
    }
}

void urutkanPeminjamanTerlambat(struct Peminjaman *daftarPeminjaman, int jumlahPeminjaman) {
    mergeSort(daftarPeminjaman, 0, jumlahPeminjaman - 1);
    printf("Daftar peminjaman berhasil diurutkan berdasarkan tanggal pengembalian menggunakan Merge Sort.\n");
}

void masukkanBuku(struct Buku *daftarBuku, int *jumlahBuku) {
    struct Buku bukuBaru;
    printf("\nMasukkan judul buku: ");
    scanf(" %[^\n]", bukuBaru.judul);
    printf("Masukkan penulis buku: ");
    scanf(" %[^\n]", bukuBaru.penulis);
    printf("Masukkan tahun terbit buku: ");
    scanf("%d", &bukuBaru.tahunTerbit);
    bukuBaru.status = Tersedia;

    daftarBuku[*jumlahBuku] = bukuBaru;
    (*jumlahBuku)++;
    printf("Buku berhasil ditambahkan.\n");
}

void sequentialSearch(struct Buku *daftarBuku, int jumlahBuku) {
    char kataKunci[50];
    printf("\nMasukkan judul atau penulis buku yang ingin dicari: ");
    scanf(" %[^\n]", kataKunci);

    int ditemukan = 0;
    printf("\n=== Hasil Pencarian Sekuensial ===\n");
    printf("%-30s%-20s%-15s%s\n", "Judul", "Penulis", "Tahun Terbit", "Status");
    for (int i = 0; i < jumlahBuku; i++) {
        if (strstr(daftarBuku[i].judul, kataKunci) != NULL || strstr(daftarBuku[i].penulis, kataKunci) != NULL) {
            printf("%-30s%-20s%-15d", daftarBuku[i].judul, daftarBuku[i].penulis, daftarBuku[i].tahunTerbit);
            if (daftarBuku[i].status == Tersedia) {
                printf("Tersedia\n");
            } else {
                printf("Dipinjam\n");
            }
            ditemukan = 1;
        }
    }

    if (!ditemukan) {
        printf("Buku dengan kata kunci '%s' tidak ditemukan.\n", kataKunci);
    }
}

int main() {
    bacaDariBerkas(daftarBuku, &jumlahBuku);
    bacaPeminjamanDariBerkas(daftarPeminjaman, &jumlahPeminjaman);

    int pilihan;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Tampilkan daftar buku\n");
        printf("2. Tampilkan daftar peminjaman\n");
        printf("3. Pinjam buku\n");
        printf("4. Kembalikan buku\n");
        printf("5. Urutkan daftar buku berdasarkan judul\n");
        printf("6. Urutkan daftar peminjaman berdasarkan NIM\n");
        printf("7. Urutkan peminjaman terlambat berdasarkan tanggal pengembalian\n");
        printf("8. Masukkan Buku Baru\n");
        printf("9. Cari Buku\n");
        printf("10. Simpan dan keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tampilkanDaftarBuku(daftarBuku, jumlahBuku);
                break;
            case 2:
                tampilkanDaftarPeminjaman(daftarPeminjaman, jumlahPeminjaman);
                break;
            case 3:
                pinjamBuku(daftarBuku, jumlahBuku, daftarPeminjaman, &jumlahPeminjaman);
                break;
            case 4:
                kembalikanBuku(daftarBuku, jumlahBuku, daftarPeminjaman, &jumlahPeminjaman);
                break;
            case 5:
                selectionSort(daftarBuku, jumlahBuku);
                break;
            case 6:
                insertionSort(daftarPeminjaman, jumlahPeminjaman);
                break;
            case 7:
                urutkanPeminjamanTerlambat(daftarPeminjaman, jumlahPeminjaman);
                break;
            case 8:
                masukkanBuku(daftarBuku, &jumlahBuku);
                break;
           case 9:
                sequentialSearch(daftarBuku, jumlahBuku);
                break;
            case 10:
                simpanKeBerkas(daftarBuku, jumlahBuku, daftarPeminjaman, jumlahPeminjaman);
                printf("Data berhasil disimpan. Keluar dari program.\n");
                break;

            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 10);

    return 0;
}
