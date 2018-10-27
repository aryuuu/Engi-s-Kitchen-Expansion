#include "ruangan.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	Ruangan Kosan;

	CreateRuangan(&Kosan,"Kosan",3,4);//bikin kamar kosong

	Objek Meja = CreateObjek('M',2,false);//bikin meja baru

	SetObjek(&Kosan,Meja,1,1);//taruh meja di posisi 1,1

	CetakRuangan(Kosan);
	return 0;
}