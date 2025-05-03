Format file yang digunakan pada program ini adalah file biner yang menggunakan library sqlite3. Data dalam file biner sqlite3 memiliki struktur tabel relasional dimana setiap table memiliki kolom dengan tipe data tertentu. Pada program ini, data siswa disimpan pada table students dengan kolom-kolom sebagai berikut.

| column name     | type | modifier    |
|-----------------|------|-------------|
| registration_id | TEXT | PRIMARY KEY |
| name            | TEXT | NOT NULL    |
| age             | INT  | NOT NULL    |

Format file dengan library sqlite3 ini kami pilih untuk memudahkan skalabilitas dan modularitas program. 

Format file sqlite3 sudah otomatis melakukan indexing pada kolom primary key, sehingga proses pencarian dan penghapusan data dapat dilakukan dengan kompleksitas waktu O(1). Hal ini memungkinkan program untuk menyimpan data dengan skala besar tanpa dampak performa yang signifikan dibandingkan menggunakan file txt atau csv yang mewajibkan penggunaan pencarian linear line demi line dengan kompleksitas waktu O(n) untuk proses pencarian dan penghapusan data.

Penggunaan library sqlite3 juga memudahkan modularisasi program sehingga setiap anggota tim dapat menulis function masing-masing tanpa saling menunggu. Sebagai contoh, function add_student dan delete_student keduanya melakukan proses pencarian yang sama persis dengan function find_student. Dengan menggunakan library sqlite3, setiap anggota tim dapat menulis function yang tidak saling berkaitan atau saling menunggu sehingga memudahkan proses penulisan, pengujian, dan pengumpulan.

Alokasi dan pembebasan memori pada program ini sepenuhnya merupakan tanggung jawab dari function main. Function main akan megalokasikan memori dan membuka koneksi ke file "siswa.db" menggunakan function sqlite3_open. Koneksi ini kemudian digunakan oleh function module (add_student, find_student, dan delete_student). Setiap function menerima koneksi file sebagai value, sehingga mereka tidak mungkin dapat melakukan mutasi pada koneksi file dan koneksi file yang mereka gunakan merupakan value dengan memori statis (stack allocated). Jika terjadi error, setiap function modul akan mengembalikan nilai bukan 0 yang akan ditangkap oleh function main. Function main kemudian akan menutup koneksi sebelum keluar dari program ketika menemukan nilai return bukan 0 dari function-function tersebut.

Dengan melakukan perjanjian parameter dan return value yang jelas antar function main dan function modul seperti yang telah dijelaskan di atas, setiap function modul hanya memegang satu tanggung jawab sesuai tugasnya dan tidak perlu memikirkan tentang membuka atau menutup koneksi dengan file. Function main juga tidak perlu mengetahui penggunaan koneksi file dalam function modul karena koneksi file yang masuk sebagai argumen function modul bersifat pass-by-value dan tidak mungkin terjadi perubahan.