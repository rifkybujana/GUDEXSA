# GUDEXSA (Guard, Detect, Extinguish, Safe)
anti fire robot based on arduino

# Kelompok (STAY)
1.	Ararya Pandya Arjana (X MIPA 3)
2.	Hakim Robbani Ridwan (X MIPA 3)
3.	Mohamad Abyhafsy Al Ayuby (X MIPA 3)
4.	Muhammad Rafly (X MIPA 3)
5.	Rifky Bujana Bisri (X MIPA 3)

# Deskripsi robot
Robot kelompok kami merupakan robot yang memiliki fungsi sebagai pendeteksi dan pemadam kebakaran. Robot kami bisa dipergunakan di area Gedung perkantoran/rumah, dengan ini kami mengambil tema sustainable cities and communities. Untuk deskripsi lemgkap nya seperti tertera dibawah.

# Fungsi Utama
1.	Mendeteksi kebakaran
2.	Memadamkan
3.	Memutus listrik pada ruangan tersebut dan mengganti ke lampu darurat
4.	Melaporkan kebakaran kepada :	 
      1.Pemilik property (melewati IOT yang terhubung ke jaringan)
		  2.orang yang berada di ruangan tersebut (alaram kebakaran)
# Manfaat/keunggulan
1.	Jika terjadi kebakaran, informasi bisa sampai ke pada pemilik properti walaupun sedang tidak ada di tempat
2.	Memperkecil kemungkinan terjadinya kebakaran besar
3.	Pemilik properti dapat menentukan metode penanganan
4.	Mengurangi potensi terjadi nya korsleting, karena kami tidak menggunakan air dan robot akan memutus listrik pada ruangan tersebut.
5.	Meminimalisir efek setelah pemadaman, karena hanya mengaktifkan alat terbatas pada ruangan tersebut

# Perbandingan dengan system yang ada sekarang
1.	Dengan adanya system IOT maka laporan akan lebih cepat. Untuk system yang ada sekarang hanya terbatas pada alaram saja dan mayoritas laporan masih dilakukan secara manual
2.	Dengan menggantikan air dengan fire extinguisher sejenis foam maka akan mengurangi kemungkinan terjadi nya korsleting akibat air. Sedangkan pada system yang ada sekarang masih menggunakan air
3.	Alat ini dapat memutuskan listrik pada ruangan tersebut sehingga menurunkan kemungkinan terjadinya korsleting. Pada system yang ada sekarang pada saat pemadaman listrik tidak di putus terlebih dahulu sehingga berbahaya.
4.	Saat listrik dipadamkan, maka lampu darurat pada alat akan menyala sebagai pengganti penerangan untuk mempermudah proses evakuasi. Pada system yang ada sekarang, jika terjadi kebakaran karena arus pendek maka ruangan akan sangat gelap dan mempersulit evakuasi
Cara Mendeteksi 

Untuk mendeteksi kebakaran, kami memakai 3 sensor berbeda, yaitu :
1.	Sensor api (4-pin IR flame sensor module)
2.	Sensor suhu (DHT11)
3.	Sensor asap/gas (4-pin MQ-2 sensor module)

# Cara kerja
1.	Robot akan mendeteksi jika terjadi kebakaran
2.	Jika terdeteksi maka robot akan:
    •	Memutus listrik pada ruangan tersebut (robot memiliki powersuply tersendiri)
    •	Menyalakan lampu darurat (terletak pada alat)
    •	Menyalakan buzzer
    •	Melaporkan ke HP pemilik property (IOT)
3.	Berusaha memadamkan api (selama … menit) dengan menyemprotkan fire extinguisher
4.	Melaporkan kembali kepada pemilik properti apakah api sudah padam atau belum (menggunakan sensor)
5.	Tindak lanjut:
  a.	Jika api belum padam, maka pemilik properti dapat memilih apakah system akan mengulang tahap pemadaman (tahap 3)/tidak (jika ingin       dan sekiranya bisa memadamkan sisa api sendiri/alasan teknis lainnya).
  b.	Jika api sudah padam, maka alat akan kembali ke kondisi siaga (tahap 1)

# Future Development
1.	Menambahkan powersuply cadangan (baterai)
2.	Memperindah desain atau tampilan
3.	Meminimalisir ukuran alat
4.	Memperkecil area pemadaman (menjadi 1 titik api)
5.	Membuat seluruh bagian robot dalam 1 modul (guna mempermudah instalasi/pemasangan)
