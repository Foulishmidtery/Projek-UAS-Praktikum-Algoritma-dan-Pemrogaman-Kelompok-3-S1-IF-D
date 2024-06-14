# Program Manajemen Perpustakaan

#### Deskripsi

Program manajemen perpustakaan berbasis C ini dirancang untuk membantu dalam pengelolaan data buku, peminjaman, dan pengembalian buku di perpustakaan. Program ini menyediakan fitur-fitur utama seperti pembacaan dan penulisan data dari dan ke berkas, penambahan dan pengelolaan buku, peminjaman dan pengembalian buku, pencarian buku, pengurutan data, serta tampilan daftar buku dan peminjaman.

#### Fitur Utama

1. **Pembacaan dan Penulisan Data dari Berkas:**
   - Membaca data buku dan peminjaman dari berkas teks saat program dimulai.
   - Menyimpan perubahan data kembali ke berkas saat program berakhir.

2. **Manajemen Buku:**
   - Menambahkan buku baru ke dalam daftar perpustakaan.
   - Menampilkan daftar buku yang tersedia dan yang sedang dipinjam.
   - Mengurutkan daftar buku berdasarkan judul menggunakan Selection Sort.

3. **Manajemen Peminjaman:**
   - Mencatat peminjaman buku oleh anggota perpustakaan.
   - Menghitung dan menampilkan tenggat waktu pengembalian buku.
   - Mencatat pengembalian buku dan memperbarui status buku menjadi tersedia.
   - Mengurutkan daftar peminjaman berdasarkan NIM menggunakan Insertion Sort.
   - Mengurutkan daftar peminjaman berdasarkan tanggal pengembalian menggunakan Merge Sort.

4. **Pencarian Buku:**
   - Pencarian buku berdasarkan judul atau penulis menggunakan pencarian sekuensial.

#### Cara Penggunaan

1. **Kompilasi Program:**
   - Gunakan perintah berikut untuk mengompilasi program:
     ```
     gcc -o manajemen_perpustakaan manajemen_perpustakaan.c
     ```

2. **Menjalankan Program:**
   - Jalankan program yang telah dikompilasi:
     ```
     ./manajemen_perpustakaan
     ```

3. **Menu Utama:**
   - Pilih opsi yang tersedia di menu utama untuk mengelola buku dan peminjaman:
     1. Tampilkan daftar buku
     2. Tampilkan daftar peminjaman
     3. Pinjam buku
     4. Kembalikan buku
     5. Urutkan daftar buku berdasarkan judul
     6. Urutkan daftar peminjaman berdasarkan NIM
     7. Urutkan peminjaman terlambat berdasarkan tanggal pengembalian
     8. Masukkan Buku Baru
     9. Cari Buku
     10. Simpan dan keluar

4. **Menyimpan dan Keluar:**
   - Pilih opsi "Simpan dan keluar" untuk menyimpan perubahan ke berkas dan keluar dari program.

#### Saran Pengembangan

Untuk lebih menyempurnakan program ini, berikut beberapa saran pengembangan:

1. Mengembangkan antarmuka pengguna grafis (GUI) untuk membuat program lebih user-friendly.
2. Menambahkan fitur manajemen anggota perpustakaan.
3. Implementasi sistem notifikasi otomatis untuk mengingatkan pengguna tentang tenggat waktu pengembalian buku.
4. Menambahkan fitur penanganan denda keterlambatan pengembalian buku.
5. Meningkatkan fitur pencarian dengan kemampuan pencarian lanjutan.
6. Mengembangkan fitur laporan dan statistik yang lebih lengkap.

#### Lisensi

Program ini dikembangkan untuk tujuan pendidikan dan dapat digunakan dan dimodifikasi sesuai kebutuhan. Pastikan untuk memberikan kredit kepada penulis asli saat menggunakan atau mendistribusikan program ini.
