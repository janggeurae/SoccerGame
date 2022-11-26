#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib> // rand
#include <ctime> // time
using namespace std;

#define TABLE_X 30 //��Ʈ���� �� x �� ����
#define TABLE_Y 20 //��Ʈ���� �� y �� ����

// Ű�ٿ� �ڵ�
#define LEFT 75 // ��
#define RIGHT 77  // ��
#define UP 72 // ��
#define DOWN 80 // ��

/*Ŀ�� �����(0) or ���̱�(1) */
void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

/*�ܼ� Ŀ�� ��ġ �̵�*/
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*1�� ��*/
const int block1[4][4] = {
        
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        
};

/*�� �θ� Ŭ����*/
class Block {
protected:
    int shape[4][4]; // shape[y][x]
    int x; // x��ǥ
    int y; // y��ǥ
public:
    int getShape(int y, int x) {
        return shape[y][x];
    }
    int getX() {
        return x;
    }
    int getY() {
        return y;
    }
    void up() { // �� �� ĭ �Ʒ� �̵�
        y--;
    }
    void down() { // �� �� ĭ �Ʒ� �̵�
        y++;
    }
    void left() { // �� �� ĭ ���� �̵�
        x--;
    }
    void right() { // �� �� ĭ ������ �̵�
        x++;
    }
 
};
/*1�� �� Ŭ����*/
class Block1 : public Block {
public:
    Block1() {
        x = TABLE_X / 2 - 3; // �ʱ� ���� �� �� �߾� ������ ����
        y = 1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                    shape[i][j] = block1[i][j]; // �� ��ü ���� ����
            }
        }
    }
};


class MainMenu {
public:
    MainMenu() {
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t"; cout << "������ �����Ϸ��� EnterŰ�� ��������.\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t"; cout << "SoccerGame 1.1\n";
        getchar(); // enterŰ �Է� ��ٸ�. enterŰ�Է� �Ǹ� ������ ����
        system("cls"); // �ܼ� â clear
    }
};


class GameTable {
private:
    int x; // ����
    int y; // ����

    Block* blockObject;

    // 2���� ���� ����
    vector<vector<int> > table; // ���̺� �� 0 = " ", 1 = "��" , 2  = "��"
public:
    GameTable(int x, int y) { 
        blockObject = nullptr;
        this->x = x;
        this->y = y;
        for (int i = 0; i < y; i++) {
            vector<int> temp;
            for (int j = 0; j < x; j++) {
                // 0�� ���� �߰� (0 =" ")
                temp.push_back(0);
            }
            table.push_back(temp);
        }
        //���� �ڸ� ���� ��ĥ (1 = "��")
        for (int i = 0; i < x; i++) { // ����
            table[0][i] = 1;
            table[y - 1][i] = 1;
        }
        for (int i = 1; i < y - 1; i++) {  // ����
            table[i][0] = 1;
            table[i][x - 1] = 1;
        }
    }

    // ������ �׸��� 
    void DrawGameTable() {
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (table[i][j] == 1) cout << "��";
                else if (table[i][j] == 2) cout << "��";
                else cout << "  "; // �� ĭ ����
            }
            cout << "\n";
        }
    }

    /*�� ����*/
    void createBlock() {
        blockObject = new Block1();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();
                table[Y][X] = blockObject->getShape(i, j);
                //�� ��ü�� ���̺� ������Ʈ
            }
        }
    }
    /*�� �̵�*/
    void MoveBlock(int key) {
        /*���̺��� �� ��ü �����*/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();
                if (table[Y][X] == 2) { // ���� ���̸�
                    table[Y][X] = 0; // ���̺��� �����
                }
            }
        }
        if (key == DOWN) blockObject->down(); // ���� ���ڷ� ���� key�� �Ʒ� �����̸� ���� �Ʒ��� �̵�
        else if (key == LEFT) blockObject->left();  // ���� ���ڷ� ���� key�� ���� �����̸� ���� �������� �̵�
        else if (key == RIGHT) blockObject->right(); // ���� ���ڷ� ���� key�� ������ �����̸� ���� ���������� �̵�
        else if (key == UP) blockObject->up(); // ���� ���ڷ� ���� key�� �� �����̸� ���� ���� �̵�

        /*�̵��� �� ���¸� ���̺� ����*/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();
                if (table[Y][X] == 0) { //������� ��쿡 �̵��� �� ������ ���̺� ����
                    table[Y][X] = blockObject->getShape(i, j);
                }
            }
        }
    }
   
};

/*���� ���� Ŭ����*/
class GamePlay {
private:
    GameTable* gt;
public:
    GamePlay() {
        gt = new GameTable(TABLE_X, TABLE_Y); //���� �� �׸��� ��ü ����
        gt->createBlock(); // �ʱ� �� ����
        gt->DrawGameTable(); // �������� �׸���.
        while (true) { // ����Ű �Է� �̺�Ʈ
            int nSelect;
            if (_kbhit()) {
                nSelect = _getch();
                if (nSelect == 224) {
                    nSelect = _getch();
                    switch (nSelect) {
                    case UP: // ȭ��ǥ �� ������ ��
                        gt->MoveBlock(UP); // ���� �� ĭ ���� �̵�
                        gotoxy(0, 0); //system("cls") �Ⱦ��� (0, 0)���� Ŀ�� �̵� ��
                        gt->DrawGameTable(); // ����� 
                        break;
                    case DOWN: // ȭ��ǥ �Ʒ� ������ ��
                        gt->MoveBlock(DOWN); // ���� �� ĭ �Ʒ��� �̵�
                        gotoxy(0, 0);
                        gt->DrawGameTable();
                        break;
                    case LEFT: // ȭ��ǥ ���� ������ ��
                        gt->MoveBlock(LEFT); // ���� �� ĭ �������� �̵�
                        gotoxy(0, 0);
                        gt->DrawGameTable();
                        break;
                    case RIGHT: // ȭ��ǥ ������ ������ ��
                        gt->MoveBlock(RIGHT); // ���� �� ĭ ���������� �̵�
                        gotoxy(0, 0);
                        gt->DrawGameTable();
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
    ~GamePlay() { // ���� ���� �̺�Ʈ
        delete gt;
    }
};

int main(void) {
    CursorView(false); // �ܼ� ȭ�� Ŀ�� ���� 
    system("mode con cols=100 lines=40 | title SoccerGame"); // �ܼ�â ũ�� �� ���� ����
    GameTable gt(TABLE_X, TABLE_Y);
    MainMenu(); // ���� �޴� �׸��� ������ ȣ��
    GamePlay(); // ���� �÷���
    getchar();
    
    return 0;
}