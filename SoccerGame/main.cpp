#include<iostream>
#include<vector>

using namespace std;

#define TABLE_X 30 //��Ʈ���� �� x �� ����
#define TABLE_Y 20 //��Ʈ���� �� y �� ����

class MainMenu {
public:
    MainMenu() {
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t"; cout << "������ �����Ϸ��� EnterŰ�� ��������.\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t"; cout << "SoccerGame 1.0\n";
        getchar(); // enterŰ �Է� ��ٸ�. enterŰ�Է� �Ǹ� ������ ����
        system("cls"); // �ܼ� â clear
    }
};


class GameTable {
private:
    int x; // ����
    int y; // ����

    // 2���� ���� ����
    vector<vector<int> > table; // ���̺� �� 0 = " ", 1 = "��" , 2  = "��"
public:
    GameTable(int x, int y) { 
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
                else cout << "  "; // �� ĭ ����
            }
            cout << "\n";
        }
    }
};
int main(void) {
    system("mode con cols=100 lines=40 | title �౸ ����"); // �ܼ�â ũ�� �� ���� ����
    GameTable gt(TABLE_X, TABLE_Y); //���� �� �׸��� ��ü ����
    MainMenu(); // ���� �޴� �׸��� ������ ȣ��
    gt.DrawGameTable(); // �������� �׸�
    getchar();
    return 0;
}