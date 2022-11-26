#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <cstdlib> // rand
#include <ctime> // time
using namespace std;

#define TABLE_X 30 //테트리스 판 x 축 길이
#define TABLE_Y 20 //테트리스 판 y 축 길이

// 키다운 코드
#define LEFT 75 // ←
#define RIGHT 77  // →
#define UP 72 // ↑
#define DOWN 80 // ↓

/*커서 숨기기(0) or 보이기(1) */
void CursorView(char show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

/*콘솔 커서 위치 이동*/
void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/*1번 블럭*/
const int block1[4][4] = {
        
                        {0, 0, 0, 0},
                        {0, 2, 2, 0},
                        {0, 2, 2, 0},
                        {0, 0, 0, 0}
        
};

/*블럭 부모 클래스*/
class Block {
protected:
    int shape[4][4]; // shape[y][x]
    int x; // x좌표
    int y; // y좌표
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
    void up() { // 블럭 한 칸 아래 이동
        y--;
    }
    void down() { // 블럭 한 칸 아래 이동
        y++;
    }
    void left() { // 블럭 한 칸 왼쪽 이동
        x--;
    }
    void right() { // 블럭 한 칸 오른쪽 이동
        x++;
    }
 
};
/*1번 블럭 클래스*/
class Block1 : public Block {
public:
    Block1() {
        x = TABLE_X / 2 - 3; // 초기 생성 맨 위 중앙 쯤으로 맞춤
        y = 1;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                    shape[i][j] = block1[i][j]; // 블럭 객체 정보 저장
            }
        }
    }
};


class MainMenu {
public:
    MainMenu() {
        cout << "\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t"; cout << "게임을 시작하려면 Enter키를 누르세요.\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t"; cout << "SoccerGame 1.1\n";
        getchar(); // enter키 입력 기다림. enter키입력 되면 다음줄 실행
        system("cls"); // 콘솔 창 clear
    }
};


class GameTable {
private:
    int x; // 가로
    int y; // 세로

    Block* blockObject;

    // 2차원 벡터 생성
    vector<vector<int> > table; // 테이블 판 0 = " ", 1 = "▦" , 2  = "■"
public:
    GameTable(int x, int y) { 
        blockObject = nullptr;
        this->x = x;
        this->y = y;
        for (int i = 0; i < y; i++) {
            vector<int> temp;
            for (int j = 0; j < x; j++) {
                // 0번 원소 추가 (0 =" ")
                temp.push_back(0);
            }
            table.push_back(temp);
        }
        //가장 자리 뼈대 색칠 (1 = "▦")
        for (int i = 0; i < x; i++) { // 가로
            table[0][i] = 1;
            table[y - 1][i] = 1;
        }
        for (int i = 1; i < y - 1; i++) {  // 세로
            table[i][0] = 1;
            table[i][x - 1] = 1;
        }
    }

    // 게임판 그리기 
    void DrawGameTable() {
        for (int i = 0; i < y; i++) {
            for (int j = 0; j < x; j++) {
                if (table[i][j] == 1) cout << "▦";
                else if (table[i][j] == 2) cout << "■";
                else cout << "  "; // 두 칸 띄우기
            }
            cout << "\n";
        }
    }

    /*블럭 생성*/
    void createBlock() {
        blockObject = new Block1();

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();
                table[Y][X] = blockObject->getShape(i, j);
                //블럭 객체를 테이블에 업데이트
            }
        }
    }
    /*블럭 이동*/
    void MoveBlock(int key) {
        /*테이블에서 블럭 객체 지우기*/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();
                if (table[Y][X] == 2) { // 만약 블럭이면
                    table[Y][X] = 0; // 테이블에서 지운다
                }
            }
        }
        if (key == DOWN) blockObject->down(); // 만약 인자로 들어온 key가 아랫 방향이면 블럭을 아래로 이동
        else if (key == LEFT) blockObject->left();  // 만약 인자로 들어온 key가 왼쪽 방향이면 블럭을 왼쪽으로 이동
        else if (key == RIGHT) blockObject->right(); // 만약 인자로 들어온 key가 오른쪽 방향이면 블럭을 오른쪽으로 이동
        else if (key == UP) blockObject->up(); // 만약 인자로 들어온 key가 윗 방향이면 블럭을 위로 이동

        /*이동한 블럭 상태를 테이블에 갱신*/
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int Y = j + blockObject->getY();
                int X = i + blockObject->getX();
                if (table[Y][X] == 0) { //빈공간인 경우에 이동한 블럭 정보를 테이블에 갱신
                    table[Y][X] = blockObject->getShape(i, j);
                }
            }
        }
    }
   
};

/*게임 시작 클래스*/
class GamePlay {
private:
    GameTable* gt;
public:
    GamePlay() {
        gt = new GameTable(TABLE_X, TABLE_Y); //게임 판 그리기 객체 생성
        gt->createBlock(); // 초기 블럭 생성
        gt->DrawGameTable(); // 게임판을 그린다.
        while (true) { // 방향키 입력 이벤트
            int nSelect;
            if (_kbhit()) {
                nSelect = _getch();
                if (nSelect == 224) {
                    nSelect = _getch();
                    switch (nSelect) {
                    case UP: // 화살표 위 눌렀을 때
                        gt->MoveBlock(UP); // 블럭을 한 칸 위로 이동
                        gotoxy(0, 0); //system("cls") 안쓰고 (0, 0)으로 커서 이동 후
                        gt->DrawGameTable(); // 덮어쓰기 
                        break;
                    case DOWN: // 화살표 아래 눌렀을 때
                        gt->MoveBlock(DOWN); // 블럭을 한 칸 아래로 이동
                        gotoxy(0, 0);
                        gt->DrawGameTable();
                        break;
                    case LEFT: // 화살표 왼쪽 눌렀을 떄
                        gt->MoveBlock(LEFT); // 블럭을 한 칸 왼쪽으로 이동
                        gotoxy(0, 0);
                        gt->DrawGameTable();
                        break;
                    case RIGHT: // 화살표 오른쪽 눌렀을 때
                        gt->MoveBlock(RIGHT); // 블럭을 한 칸 오른쪽으로 이동
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
    ~GamePlay() { // 게임 종료 이벤트
        delete gt;
    }
};

int main(void) {
    CursorView(false); // 콘솔 화면 커서 제거 
    system("mode con cols=100 lines=40 | title SoccerGame"); // 콘솔창 크기 및 제목 설정
    GameTable gt(TABLE_X, TABLE_Y);
    MainMenu(); // 메인 메뉴 그리기 생성자 호출
    GamePlay(); // 게임 플레이
    getchar();
    
    return 0;
}