#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>


using namespace std;

void printboard(char board[][8], int x1, int y1, int x2, int y2) { // Fungsi untuk menampilkan peta
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i == y1) && (j == x1)) {
                board[i][j] = 'R';
            }
            else if ((i == y2) && (j == x2)) {
                board[i][j] = 'K';
            }
            else {
                board[i][j] = '.';
            }
            cout << board[i][j];
        }
        cout << endl;
    }
}

void check_pilihan(int* pilihan) {// Fungsi untuk menngecek pilihan
    if (*pilihan > 3 || *pilihan < 1) {
        cout << "Pilihan tidak tersedia. Coba lagi. \n";
        cout << "1. Bergerak\n2. Menyerang\n3. Keluar \n" << endl;
        cout << "Masukkan pilihan :  ";

        cin >> *pilihan;
        check_pilihan(*&pilihan);
    }
}


bool keluar(int pilihan) {   // Fungsi untuk keluar
    if (pilihan == 3) {
        cout << "TERIMA KASIH SUDAH BERMAIN GAME INI\n";
        return false;
    }
    else {
        return true;
    }
}

int jarak_robot(int x1, int y1, int x2, int y2) { //Fungsi untuk menghitung jarak robot dengan bunshin
    return abs(x1 - x2) + abs(y1 - y2);
}

bool check_jarak(int x1, int y1, int x2, int y2) { //Fungsi untuk mengecek jarak robot dengan bunshin
    if (jarak_robot(x1, y1, x2, y2) <= 3) {
        return true;
    }
    else {
        return false;
    }
}

void gerak_robot(int arah, int* x, int* y) {    //Fungsi untuk menggerakkan robot
    if (arah == 1) { //kanan
        *x = *x + 1;
    }
    else if (arah == 2) { //kiri
        *x = *x - 1;
    }
    else if (arah == 3) {// atas
        *y = *y - 1;
    }
    else if (arah == 4) { // bawah
        *y = *y + 1;
    }
}



bool check_lokasi(int arah, int x, int y) { //Fungsi untuk mengecek lokasi robot
    if (arah == 1) {
        if ((x + 1) <= 7) { //kanan
            return true;
        }
        else {
            return false;
        }
    }
    else if (arah == 2) {  //kiri
        if ((x - 1) >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else if (arah == 3) {  //atas
        if ((y - 1) >= 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else {  //bawah
        if ((y + 1) <= 7) {
            return true;
        }
        else {
            return false;
        }
    }
}



void check_arah(int* arah) { //Fungsi untuk mengecek masukan arah robot
    if (*arah > 4 || *arah < 1) {
        cout << "Pilihan tidak tersedia. Coba lagi. \n";
        cout << "Masukkan arah gerak (angka)  \n";
        cout << "1. Kanan  \n";
        cout << "2. Kiri  \n";
        cout << "3. Atas  \n";
        cout << "4. Bawah  \n";
        cin >> *arah;
        check_arah(*&arah);
    }
}



void update_health_bunshin(int* health_bunshin, int damage_robot) { //Fungsi untuk mengupdate health bunshin
    *health_bunshin = *health_bunshin - damage_robot;
}

void update_health_robot(int* health_robot, int damage_bunshin) { //Fungsi untuk mengupdate health robot
    *health_robot = *health_robot - damage_bunshin;
}

void update_lokasi_bunshin(int x1, int y1, int* x2, int* y2) {//Fungsi untuk mengupdate lokasi bunshin
    *x2 = (rand() % 7) + 1; //random x untuk bunshin
    *y2 = (rand() % 7) + 1; //random y untuk bunshin
    if ((*x2 == x1) || (*y2 == y1)) {
        update_lokasi_bunshin(x1, y1, *&x2, *&y2);
    }
}

bool check_tabrak(int arah, int x1, int y1, int x2, int y2) { //Fungsi untuk mengecek apakah robot bertabrakan dengan bunshin

    if ((x1 < x2) && jarak_robot(x1, y1, x2, y2) == 1) { // bunshin di kanan
        if (arah == 1) {
            return false;
        }
        else {
            return true;
        }
    }
    else if ((x1 > x2) && jarak_robot(x1, y1, x2, y2) == 1) { // bunshin di kiri
        if (arah == 2) {
            return false;
        }
        else {
            return true;
        }
    }
    else if ((y1 > y2) && jarak_robot(x1, y1, x2, y2) == 1) { // bunshin di atas
        if (arah == 3) {
            return false;
        }
        else {
            return true;
        }
    }
    else { // bunshin di bawah
        if ((arah == 4) && jarak_robot(x1, y1, x2, y2) == 1) {
            return false;
        }
        else {
            return true;
        }
    }

}


int main() {
    int x = 0, y = 7, x_bunshin, y_bunshin, pilihan;
    int health_bunshin = 15, health_robot = 15;
    int damage_robot = 5, damage_bunshin = (rand() % 4) + 1;
    int death_count = 0;
    
    char board[8][8];

    //inisiasi lokasi bunshin
    x_bunshin = (rand() % 7) + 1; //random x 
    y_bunshin = (rand() % 7) + 1; //random y 

    cout << "############################################" << endl;
    cout << "###########     ROBOT CAKRU     ############" << endl;
    cout << "############################################" << endl << endl;

    cout << "----------------------------------\n";
    cout << "|ATRIBUT ROBOT DAN BUNSHIN KURAMA|\n";
    cout << "----------------------------------\n";
    cout << "|HP ROBOT CAKRU        : 15      |\n";
    cout << "|HP BUNSHIN KURAMA     : 15      |\n";
    cout << "|DAMAGE ROBOT CAKRU    : 5       |\n";
    cout << "|DAMAGE BUNSHIN KURAMA : 1-5     |\n";
    cout << "----------------------------------\n";
    cout << "JARAK ROBOT DENGAN BUNSHIN = " << jarak_robot(x, y, x_bunshin, y_bunshin) << " petak" << endl;
    cout << "ROBOT HANYA BISA MENYERANG BUNSHIN KETIKA ROBOT DENGAN BUNSHIN BERJARAK <= 3 PETAK" << endl;
    cout << endl;

    printboard(board, x, y, x_bunshin, y_bunshin);
    cout << "1. Bergerak\n2. Menyerang\n3. Keluar Game \n" << endl;
    cout << "Masukkan perintah: ";
    cin >> pilihan;
    check_pilihan(&pilihan);
    cout << endl;

bool maen = true;
while (maen == true) {

///////////////PILIHAN 1///////////////
        if (pilihan == 1) {
            int arah;
            cout << "Masukkan arah gerak (1/2/3/4)  \n";
            cout << "1. Kanan  \n";
            cout << "2. Kiri  \n";
            cout << "3. Atas  \n";
            cout << "4. Bawah  \n";
            cout << "Arah: ";
            cin >> arah;
            if (arah > 4 || arah < 1) {
                check_arah(&arah);
            }
            cout << endl;
            if (check_lokasi(arah, x, y) && check_tabrak(arah, x, y, x_bunshin, y_bunshin)) {
                gerak_robot(arah, &x, &y); 
            }
            else {
                cout << "ROBOT TIDAK BISA BERGERAK KE LUAR ZONA ATAU MENABRAK BUNSHIN KURAMA!!!" << endl;
            }
            cout << "---------------------------------------------" << endl << endl;
            cout << "JARAK ROBOT DENGAN BUNSHIN = " << jarak_robot(x, y, x_bunshin, y_bunshin) << " petak" << endl;
            printboard(board, x, y, x_bunshin, y_bunshin);


            if (check_jarak(x, y, x_bunshin, y_bunshin)) {
                cout << "ROBOT DAPAT MENYERANG !!!" << endl << endl;
            }
            else {
                cout << endl;
            }

        }

///////////////PILIHAN 2///////////////
        else if (pilihan == 2) {
            if (check_jarak(x, y, x_bunshin, y_bunshin)) {
                cout << "\nROBOT MENYERANG BUNSHIN KURAMA\n";
                cout << endl;
                update_health_bunshin(&health_bunshin, damage_robot);

                if (health_bunshin > 0) {
                    update_health_robot(&health_robot, damage_bunshin);
                }

                cout << "------------------------\n";
                cout << "|HP ROBOT          : " << health_robot << "|\n";
                cout << "|HP BUNSHIN KURAMA : " << health_bunshin << "|\n";
                cout << "------------------------\n";
                cout << "|DAMAGE BUNSHIN = " << damage_bunshin << "    |\n";
                cout << "|DAMAGE ROBOT   = " << damage_robot << "    |\n";
                cout << "------------------------\n";
                

                if (health_bunshin <= 0) {
                    srand((unsigned)time(0));
                    cout << "\n1 BUNSHIN KURAMA SUDAH DIKALAHKAN\n" << endl;
                    cout << "---------------------------------------------" << endl << endl;
                    death_count = death_count + 1;
                    health_bunshin = 20;
                    damage_bunshin = (rand() % 4) + 1;
                }

                if (health_robot <= 0) {
                    cout << "ROB0T CAKRU TELAH MEMBUNUH BUNSHIN KURAMA SEBANYAK " << death_count << " BUNSHIN";
                    exit(1);
                }

                else {
                    update_lokasi_bunshin(x, y, &x_bunshin, &y_bunshin); // Bunshin berpindah tempat
                    cout << "\nBUNSHIN BERPINDAH LOKASI !!!\n\n";
                    cout << "JARAK ROBOT DENGAN BUNSHIN = " << jarak_robot(x, y, x_bunshin, y_bunshin) << " petak" << endl;
                    if (check_jarak(x, y, x_bunshin, y_bunshin)) {
                        cout << "ROBOT DAPAT MENYERANG !!!" << endl << endl;
                    }
                    else {
                        cout << endl;
                    }
                    printboard(board, x, y, x_bunshin, y_bunshin);
                }

            }
            else {
                cout << "---------------------------------------------" << endl << endl;
                cout << "BUNSHIN KURAMA DILUAR JANGKAUAN " << endl;
                printboard(board, x, y, x_bunshin, y_bunshin);
            }

        }

        else {
            if (pilihan == 3) {
                cout << "TERIMA KASIH SUDAH BERMAIN GAME INI\n";
                exit(1);
            }
            cout << "Masukkan invalid, dikembalikan ke menu awal" << endl;
            main();
        }
        
        cout << "1. Bergerak\n2. Menyerang\n3. Keluar Game\n" << endl;
        cout << "Masukkan perintah: ";
        cin >> pilihan;
  
        check_pilihan(&pilihan);
       
        maen = keluar(pilihan);

    }
    cout << "\nANDA TELAH MENGALAHKAN " << death_count << " BUNSHIN KURAMA" << endl;
    return 0;
}