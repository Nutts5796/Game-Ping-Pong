#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h> 

// Константы
#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define WIN_SCORE 21

// Символы
#define BALL_CHAR 'O'
#define PADDLE_CHAR '|'
#define EMPTY_CHAR ' '

// Структуры
typedef struct {
    int x, y;       // Положение мяча
    int dx, dy;     // Направление движения мяча
} Ball;

typedef struct {
    int y;          // Верхняя координата ракетки
    int score;      // Очки игрока
} Paddle;

// Глобальные переменные
Paddle left_paddle, right_paddle;
Ball ball;

// Инициализация игры
void init_game() {
    left_paddle.y = HEIGHT / 2 - PADDLE_SIZE / 2;
    left_paddle.score = 0;

    right_paddle.y = HEIGHT / 2 - PADDLE_SIZE / 2;
    right_paddle.score = 0;

    ball.x = WIDTH / 2;
    ball.y = HEIGHT / 2;
    ball.dx = 1;
    ball.dy = 1;
}

// Отрисовка игрового поля
void draw_field() {
    clear();

    // Верхняя граница
    for (int x = 0; x < WIDTH; x++) mvaddch(0, x, '-');

    // Игровое поле
    for (int y = 1; y < HEIGHT - 1; y++) {
        mvaddch(y, 0, '|'); // Левая граница
        mvaddch(y, WIDTH - 1, '|'); // Правая граница

        // Левая ракетка
        for (int i = 0; i < PADDLE_SIZE; i++) {
            if (y == left_paddle.y + i) mvaddch(y, 2, PADDLE_CHAR);
        }

        // Правая ракетка
        for (int i = 0; i < PADDLE_SIZE; i++) {
            if (y == right_paddle.y + i) mvaddch(y, WIDTH - 3, PADDLE_CHAR);
        }

        // Мяч
        if (y == ball.y && ball.x > 0 && ball.x < WIDTH - 1) mvaddch(ball.y, ball.x, BALL_CHAR);
    }

    // Нижняя граница
    for (int x = 0; x < WIDTH; x++) mvaddch(HEIGHT - 1, x, '-');

    // Счет
    mvprintw(HEIGHT, 0, "Player 1: %d\tPlayer 2: %d", left_paddle.score, right_paddle.score);
    refresh();
}

// Обработка ввода
void handle_input() {
    int ch = getch();
    if (ch == 'q' || ch == 'Q') {
        clear(); 
        mvprintw(HEIGHT / 2, (WIDTH - 9) / 2, "Game Over"); // Сообщение "Game Over" в центре
        refresh();
        usleep(2000000); // Подождать 2 секунды перед выходом
        endwin(); // Завершение работы ncurses
        exit(0);  // Выход из программы
    }

    // Управление левой ракеткой
    if (ch == 'a' || ch == 'A') {
        if (left_paddle.y > 0) left_paddle.y--;
    } else if (ch == 'z' || ch == 'Z') {
        if (left_paddle.y + PADDLE_SIZE < HEIGHT - 1) left_paddle.y++;
    }

    // Управление правой ракеткой
    if (ch == 'k' || ch == 'K') {
        if (right_paddle.y > 0) right_paddle.y--;
    } else if (ch == 'm' || ch == 'M') {
        if (right_paddle.y + PADDLE_SIZE < HEIGHT - 1) right_paddle.y++;
    }
}

// Обновление положения мяча
void update_ball() {
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Проверка на отскок от верхней и нижней границ
    if (ball.y <= 1 || ball.y >= HEIGHT - 2) ball.dy *= -1;

    // Проверка на отскок от ракеток
    if (ball.x == 3 && ball.y >= left_paddle.y && ball.y < left_paddle.y + PADDLE_SIZE) ball.dx *= -1;
    if (ball.x == WIDTH - 4 && ball.y >= right_paddle.y && ball.y < right_paddle.y + PADDLE_SIZE) ball.dx *= -1;

    // Проверка на гол
    if (ball.x <= 0) {
        right_paddle.score++;
        ball.x = WIDTH / 2;
        ball.y = HEIGHT / 2;
        ball.dx = 1;
        ball.dy = 1;
    }

    if (ball.x >= WIDTH - 1) {
        left_paddle.score++;
        ball.x = WIDTH / 2;
        ball.y = HEIGHT / 2;
        ball.dx = -1;
        ball.dy = 1;
    }
}

// Проверка победителя
int check_winner() {
    if (left_paddle.score >= WIN_SCORE) {
        mvprintw(HEIGHT + 1, 0, "Player 1 wins!");
        return 1;
    }
    if (right_paddle.score >= WIN_SCORE) {
        mvprintw(HEIGHT + 1, 0, "Player 2 wins!");
        return 1;
    }
    return 0;
}

// Главный игровой цикл
void game_loop() {
    while (1) {
        draw_field();
        handle_input();
        update_ball();
        if (check_winner()) break;
        usleep(50000); // Задержка для плавности
    }
}

// Главная функция
int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(0); 

    init_game();
    game_loop();

    getch();
    endwin();
    return 0;
}