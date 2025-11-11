#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int play[11][11];   
int check[11][11];  

void start_game(void);
void place_mines(void);
void print_play(int end);   
int winning_checker(void);
int check_around(int r, int c); 

int main(void)
{
    int r, c;

    srand((unsigned int)time(NULL));

    start_game();
    place_mines();

    printf("--- 지뢰찾기게임 (9x9 격자, 지뢰 10개) ---\n");
    
    while (1) {
        print_play(0);  

        printf("\n열고 싶은 칸 입력 (행(1~9) 열(1~9)) : ");
        if (scanf("%d %d", &r, &c) != 2) {
            printf("입력 오류.\n");
            return 0;
        }

        // 범위 체크
        if (r < 1 || r > 9 || c < 1 || c > 9) {
            printf("범위를 벗어났습니다. 다시 입력.\n");
            continue;
        }

        r--; 
        c--;

        if (check[r][c] == 1) {
            printf("이미 연 칸입니다. 다시 입력.\n");
            continue;
        }

        check[r][c] = 1;

        if (play[r][c] == 1) {
            printf("\n💥 LOSE.\n");
            print_play(1);
            break;
        }

        if (winning_checker()) {
            printf("\n🎉 WIN.\n");
            print_play(1); 
            break;
        }
    }

    return 0;
}

void start_game(void)
{
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            play[i][j] = 0;
            check[i][j] = 0;
        }
    }
}

void place_mines(void)
{
    int cnt = 0;
    while (cnt < 10) {
        int r = rand() % 9;
        int c = rand() % 9;
        if (play[r][c] == 0) {
            play[r][c] = 1;
            cnt++;
        }
    }
}

int check_around(int r, int c)
{
    int sum = 0;
    for (int i = r - 1; i <= r + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if (i < 0 || i >= 9 || j < 0 || j >= 9) continue;
            if (i == r && j == c) continue;
            sum += play[i][j];
        }
    }
    return sum;
}

void print_play(int end)
{
    printf("\n   ");
    for (int c = 0; c < 9; c++) printf("%d ", c + 1);
    printf("\n   ");
    for (int c = 0; c < 9; c++) printf("--");
    printf("\n");

    for (int r = 0; r < 9; r++) {
        printf("%2d| ", r + 1);
        for (int c = 0; c < 9; c++) {

            if (!end && check[r][c] == 0) {
                // 아직 안 연 칸
                printf("# ");
            } else if (play[r][c] == 1) {
                // 지뢰
                printf("* ");
            } else {
                // 안전 칸 → 주변 지뢰 수
                int k = check_around(r, c);
                if (k == 0) printf(". ");
                else printf("%d ", k);
            }
        }
        printf("\n");
    }
}

int winning_checker(void)
{
    int safe = 9 * 9 - 10;
    int opened = 0;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (check[r][c] == 1 && play[r][c] == 0)
                opened++;
        }
    }
    return (opened == safe);
}