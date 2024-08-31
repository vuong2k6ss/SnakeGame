#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#define MAX 100
using namespace std;

int sl = 7;
int diem = 0;

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ve_tuong();
void khoi_tao_ran(int toadox[], int toadoy[]);
void ve_ran(int toadox[], int toadoy[], int mau_ran);
void xoa_ran(int toadox[], int toadoy[]);
void xu_ly_ran(int toadox[], int toadoy[], int x, int y);
void them(int a[], int x);
void xoa(int a[], int vt);
bool kt_ran(int toadox[], int toadoy[]);
void tao_qua(int& xqua, int& yqua, int& mau_qua);
bool ran_an_qua(int x, int y, int xqua, int yqua);
void xu_ly_xuyen_tuong(int& x, int& y);
int tao_mau_ngau_nhien();

int main() {
    srand(time(NULL));
    int xqua = 0, yqua = 0, mau_qua = 7;
    tao_qua(xqua, yqua, mau_qua);

    bool gameover = false;
    int toadox[MAX], toadoy[MAX];
    ve_tuong();
    khoi_tao_ran(toadox, toadoy);

    int x = 50, y = 13;
    int check = 2;
    int mau_ran = 7;

    while (!gameover) {
        xoa_ran(toadox, toadoy);

        if (_kbhit()) {
            char kitu = _getch();
            if (kitu == -32) {
                kitu = _getch();
                if (kitu == 72 && check != 0) {
                    check = 1;
                }
                else if (kitu == 80 && check != 1) {
                    check = 0;
                }
                else if (kitu == 77 && check != 3) {
                    check = 2;
                }
                else if (kitu == 75 && check != 2) {
                    check = 3;
                }
            }
        }

        if (check == 0) {
            y++;
        }
        else if (check == 1) {
            y--;
        }
        else if (check == 2) {
            x++;
        }
        else if (check == 3) {
            x--;
        }

        xu_ly_xuyen_tuong(x, y);

        if (ran_an_qua(x, y, xqua, yqua)) {
            sl++;
            diem++;
            mau_ran = mau_qua; // Đổi màu rắn theo màu quả
            tao_qua(xqua, yqua, mau_qua);
        }

        xu_ly_ran(toadox, toadoy, x, y);
        ve_ran(toadox, toadoy, mau_ran); // Hiển thị rắn với màu sắc đã cập nhật
        gameover = kt_ran(toadox, toadoy);
        Sleep(150);
    }

    cout << "Game over! Diem cua ban: " << diem << endl;
    _getch();
    return 0;
}

void ve_tuong() {
    for (int x = 10; x <= 100; x++) {
        gotoXY(x, 1);
        cout << "_";
        gotoXY(x, 26);
        cout << "_";
    }
    for (int y = 1; y <= 26; y++) {
        gotoXY(10, y);
        cout << "|";
        gotoXY(100, y);
        cout << "|";
    }
}

void khoi_tao_ran(int toadox[], int toadoy[]) {
    int x = 50, y = 13;
    for (int i = 0; i < sl; i++) {
        toadox[i] = x;
        toadoy[i] = y;
        x--;
    }
}

void ve_ran(int toadox[], int toadoy[], int mau_ran) {
    setColor(mau_ran); // Đặt màu rắn
    for (int i = 0; i < sl; i++) {
        gotoXY(toadox[i], toadoy[i]);
        if (i == 0) {
            cout << "0";
        }
        else {
            cout << "o";
        }
    }
    setColor(7); // Đặt lại màu trắng sau khi vẽ rắn
}

void xoa_ran(int toadox[], int toadoy[]) {
    for (int i = 0; i < sl; i++) {
        gotoXY(toadox[i], toadoy[i]);
        cout << " ";
    }
}

void xu_ly_ran(int toadox[], int toadoy[], int x, int y) {
    them(toadox, x);
    them(toadoy, y);
    xoa(toadox, sl - 1);
    xoa(toadoy, sl - 1);
}

void them(int a[], int x) {
    for (int i = sl; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = x;
    sl++;
}

void xoa(int a[], int vt) {
    for (int i = vt; i < sl - 1; i++) {
        a[i] = a[i + 1];
    }
    sl--;
}

bool kt_ran(int toadox[], int toadoy[]) {
    for (int i = 1; i < sl; i++) {
        if ((toadox[0] == toadox[i]) && (toadoy[0] == toadoy[i])) {
            return true;
        }
    }
    return false;
}

void tao_qua(int& xqua, int& yqua, int& mau_qua) {
    xqua = rand() % (99 - 11 + 1) + 11;
    yqua = rand() % (25 - 2 + 1) + 2;
    mau_qua = tao_mau_ngau_nhien();
    gotoXY(xqua, yqua);
    setColor(mau_qua);
    cout << "s";
    setColor(7);
}

bool ran_an_qua(int x, int y, int xqua, int yqua) {
    return (x == xqua && y == yqua);
}

void xu_ly_xuyen_tuong(int& x, int& y) {
    if (x < 10) x = 100;
    else if (x > 100) x = 10;
    if (y < 1) y = 26;
    else if (y > 26) y = 1;
}

int tao_mau_ngau_nhien() {
    return rand() % 14 + 1;
}