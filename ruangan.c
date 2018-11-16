#include "ruangan.h"
#include "scanner.h"
#include <stdio.h>

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
	return ((i >= BrsMin) && (i <= BrsMax) && (j >= KolMin) && (j <= KolMax));
}
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (Ruangan R){
	return (BrsMin);
}
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (Ruangan R){
	return (KolMin);
}
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (Ruangan R){
	return (GetFirstIdxBrs(R)+NBrsEff(R)-1);
}
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (Ruangan R){
	return (GetFirstIdxKol(R)+NKolEff(R)-1);
}
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxEff (Ruangan R, indeks i, indeks j){
	return (IsIdxValid(i,j) && i <= NBrsEff(R) && j <= NKolEff(R));
}
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */



void CreateRuangan(Ruangan *R, char N[50], int NB, int NK){
	int i, j;
	
	strcpy(NamaR(*R),N);
	NBrsEff(*R) = NB;
	NKolEff(*R) = NK;

	char NO = 'L';
	Objek Lantai = CreateObjek(NO,0,false);

	for(i = GetFirstIdxBrs(*R); i <= GetLastIdxBrs(*R); i++){
		for(j = GetFirstIdxKol(*R); j <= GetLastIdxKol(*R); j++){
			SetObjek(R,Lantai,i,j);
		}
	}
}
//bikin ruangan baru yang isinya cuma lantai doang, ukurannya NBxNK

void SetObjek(Ruangan *R, Objek O, indeks i, indeks j){
	Elmt(*R,i,j).Nama = Nama(O);
	Elmt(*R,i,j).Kapasitas = Kapasitas(O);
	Elmt(*R,i,j).Fill = Fill(O);
}
//penempatan objek di ruangan di indeks i,j


Objek CreateObjek(char N, int K, boolean F){
	Objek result;

	Nama(result) = N;
	Kapasitas(result) = K;
	Fill(result) = F;

	return result;
}
//mengembalikan sebuah objek dengan nilai-nilai parameter di atas


void CetakRuangan(Ruangan R){

	int i, j;
	//cetak dinding atas, 
	for(i = GetFirstIdxKol(R); i <= GetLastIdxKol(R); i++){
		printf("========");
	}
	printf("\n");

	//cetak bagian 'tengah' ruangan
	for(i = GetFirstIdxBrs(R); i <= GetLastIdxBrs(R); i++ ){
		for(j = GetFirstIdxKol(R); j <= GetLastIdxKol(R); j++){
			printf("|      |");//beri sedikit ruang
		}
		printf("\n");

		for (j = GetFirstIdxKol(R); j <= GetLastIdxKol(R); j++){
			if(Nama(Elmt(R,i,j)) == 'L'){
				printf("|      |");//cetak lantai
			} else if(Nama(Elmt(R,i,j)) >  48 && Nama(Elmt(R,i,j)) < 58){
				printf("|   %c  |",Nama(Elmt(R,i,j)));//cetak meja
			}else if(Nama(Elmt(R,i,j)) == 'K' && !Fill(Elmt(R,i,j))){
				printf("|   K  |");//cetak kursi kosong
			}else if(Nama(Elmt(R,i,j)) == 'K' && Fill(Elmt(R,i,j))){
				printf("|   C  |");//cetak kursi yang ada pelanggannya
			}else if(Nama(Elmt(R,i,j)) == 'P'){
				printf("|  >w< |");//cetak player
			}else if(Nama(Elmt(R,i,j)) == 'M'){
				printf("|   M  |");
			}else if(Nama(Elmt(R,i,j)) == 'T'){
				printf("|   T  |");
			}
		}
		printf("\n");

		for(j = GetFirstIdxKol(R); j <= GetLastIdxKol(R); j++){
			printf("|      |");//beri sedikit ruang
		}
		printf("\n");

		for(j = GetFirstIdxKol(R); j <= GetLastIdxKol(R); j++){
			printf("========");//sekat pemmbatas antar blok objek
		}
		printf("\n");
		
	}

}
//cetak ruangan


void BacaRuangan(Ruangan *R, char File[]){
	char N[50];
	int panjang,lebar,kap,f,x,y;
	char namaobj;
	boolean fill;
	Objek bende;
	int i;

	STARTKATA(File);

	//strcpy(N,CKata.TabKata);//salin nama ruangan
	for(i = 1; i <= CKata.Length; i++){
		N[i] = CKata.TabKata[i];
	}
	IgnoreBlank();
	//printf("Nama ruangannya adalah :");
	//printf("%s\n",N);
	//for(int i = 1; i <= CKata.Length; i++){
	//	printf("%c",N[i]);
	//}
	//printf("\n");
	SalinInt(&panjang);//baca baris
	//printf("panjang :%d\n",panjang );

	SalinInt(&lebar);//baca kolom
	//printf("lebar :%d\n",lebar );

	CreateRuangan(R,N,panjang,lebar);

	while(CC != MARK){
	
		//while(CC != NEWLINE){//baca perbaris
			ADVKATA();
			namaobj = CKata.TabKata[1];//baca dan assign nama objek

			SalinInt(&kap);//baca dan assign kapasitas objek
	

			SalinInt(&f);//baca dan salin fill
			fill = (f==1?true:false);
	

			SalinInt(&x);//baca dan assign absis posisi objek
	

			SalinInt(&y);//baca dan assign ordinat posisi objek
	

			bende = CreateObjek(namaobj,kap,fill);//bikin objek baru
			SetObjek(R,bende,x,y);//letakkan objek di ruangan

		//}
	}

}
//membentuk ruangan baru dengan masukan dari file eksternal
//format dari file eksternal ini adalah
//cek aja file kosan.txt
//jangan lupa sebelum new line ada spasinya

POINT FindObjek(Ruangan R, char Nama){
	indeks i = GetFirstIdxBrs(R);
	indeks j = GetFirstIdxKol(R);
	POINT result;
	while(Nama(Elmt(R,i,j)) != Nama && i <= GetLastIdxBrs(R)){
		j = GetFirstIdxKol(R);
		while(Nama(Elmt(R,i,j)) != Nama && j <= GetLastIdxKol(R)){
			j++;
		}

		if(Nama(Elmt(R,i,j)) != Nama){
			i++;
		}
	}

	if(Nama(Elmt(R,i,j)) == Nama){//objeknya ketemu
		result = MakePOINT(i,j);
	} else {//objeknya ga ketemu
		result = MakePOINT(-999,-999);
	}
	

	return result;
}
//mengembalikan POINT tempat objek bernama Nama berada di Ruangan R
//jika ternyata objek tersebut tidak ada mengembalikan POINT dengan 
//absis dan ordinat -999


boolean BisaGerak(Ruangan R, char P, int Arah){

	POINT posisi = FindObjek(R, P);// menyimpan posisi objek

	if(Arah == 1){
		posisi = PlusDelta(posisi,-1,0);
	} else if (Arah == 2){
		posisi = PlusDelta(posisi,0,1);
	} else if (Arah == 3){
		posisi = PlusDelta(posisi,1,0);
	} else if (Arah == 4){
		posisi = PlusDelta(posisi,0,-1);
	}

	return (IsIdxEff(R,Absis(posisi), Ordinat(posisi)) && Nama(Elmt(R, Absis(posisi), Ordinat(posisi))) == 'L');


}
//mengembalikan nilai true atau false 
//arah merupakan angka 1, 2, 3, atau 4 yang 
//secara berurut merupakan arah atas, kanan, bawah, dan kiri
//jika Objek bernama P pada Ruangan R bisa bergerak ke arah Arah
//BisaGerak mengembalikan nilai true dan false jika tidak
//asumsi nilai Arah selalu valid

void GerakO(Ruangan *R, char P, int Arah){
	POINT sauce = FindObjek(*R, P);
	POINT dest;

	if(Arah == 1){
		dest = PlusDelta(sauce,-1,0);
	} else if (Arah == 2){
		dest = PlusDelta(sauce,0,1);
	} else if (Arah == 3){
		dest = PlusDelta(sauce,1,0);
	} else if (Arah == 4){
		dest = PlusDelta(sauce,0,-1);
	}

	Objek Pl = CreateObjek(P, 1, true);
	Objek L = CreateObjek('L', 0, false);//bikin lantai

	SetObjek(R, Pl, Absis(dest), Ordinat(dest));//set P di dest
	SetObjek(R, L, Absis(sauce), Ordinat(sauce));//sauce dijadiin lantai lagi





}
//menggerakkan Objek bernama P di Ruangan R ke arah Arah
//dimana Arah merupakan bilangan 1, 2, 3, atau 4
//yang secara berurutan merupakan arah atas, kanan, bawah, dan kiri


void UsirPelanggan(Ruangan *R, char Meja){

	POINT Posisi = FindObjek(*R, Meja);//catat posisi meja yangi ingin dikosongkan

	for(int i = Absis(Posisi)-1; i <= Absis(Posisi)+1; i++){
		for(int j = Ordinat(Posisi)-1; j <= Ordinat(Posisi)+1; j++){
			if(Nama(Elmt(*R,i,j)) == 'K' && Fill(Elmt(*R,i,j))){
				Fill(Elmt(*R,i,j)) = false;
			}
		}
	}

	Fill(Elmt(*R,Absis(Posisi),Ordinat(Posisi))) = false;

}
//mengosongkan kursi pelanggan yang sudah selesai makan
//pada Ruangan R di meja bernama Meja
//meja pasti terisi sebelum pelangga diusir