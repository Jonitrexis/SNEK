#include <bits/stdc++.h>
#include <conio.h>
#include <Windows.h>
#include <thread>
#include <mmsystem.h>
#include <unistd.h>
#include <chrono>
#include <deque>
#include <utility>

#define SPEED 200
#define spacebar 32
#define hash 35
#define star 42

int random_apple_coordinates(int n) {
    // function to set random apple coordinates
    return rand()%n;
}

struct Apple { // creating an apple
    int x;
    int y;
};
Apple apple;

struct obstacle{ //creating obstacle
    int w;
    int z;
};
obstacle wall;

void GameOver() {
    system("cls"); // clearing the screen
    // and exiting the game after the player looses
}

void hidecursor() { // function to hide coursor
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void set_cursor_position(int y, int x) { // function setting cursor posiotion
    static
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {
            (SHORT) x,
            (SHORT) y
    };
    SetConsoleCursorPosition(hOut, coord);
}

void set_console_colour(unsigned int colour) {
    // function setting terminal colours
    static
    const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    SetConsoleTextAttribute(hOut, colour);
}

void print_game_map(int n, char **_game_map) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
                // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); //settign colour of the borders
            std::cout << _game_map[i][j];
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);

            // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // setting default terminal colours
            if ((i == 0 || i == n - 1 || j == 0 || j == n - 2) && (j != n - 1))
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
                // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED); //settign colour of the borders
            std::cout << " ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
            // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);     // setting default terminal colours
        }
        std::cout << std::endl;
    }
}

bool stop = false;
bool if_apple_eaten;
bool apple_found;
bool fail;
int a; // for deciding which option you want while playing snake
int points = 0; // setting gamepoints to 0
std::deque<std::pair<int, int> > snek;

void ruch(std::pair<int, int> coordinates_front, std::pair<int, int> coordinates_back, char direction, char **_game_map,
          int size) {
    while (!stop) {
        apple_found = false;
        coordinates_front = snek.front(); // snake head coordinates
        coordinates_back = snek.back();
        if (direction == 'd') {
            apple_found = false;
            _game_map[snek[0].first][snek[0].second] = 'o';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting current head as a body
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000a);
            // setting snake colour to green
            // set_console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
            std::cout << "o";
            coordinates_front.first = (coordinates_front.first + 1) % (size - 1); // setting next snakes' head coordinates
            if (_game_map[coordinates_front.first][coordinates_front.second] == 111) {
                // player looses if snake tries to eat itself
                fail = true;
                break;
            }
            if (a == 2) { // loosing the game if snake tries to eat the wall
                if (_game_map[coordinates_front.first][coordinates_front.second] == hash) {
                    fail = true;
                    break;
                }
            }
            if (_game_map[coordinates_front.first][coordinates_front.second] == hash) { // if snake goes into the wall
                coordinates_front.first = 1;
            }
            snek.push_front(coordinates_front);
            _game_map[snek[0].first][snek[0].second] = 'O';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting snakes' head to new position
            std::cout << "O";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
            // setting default terminal colours
            // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
            if (coordinates_front.first == apple.x && coordinates_front.second == apple.y) {
                if_apple_eaten = true;
                // setting apple to eaten, no need to erase snakes' tail
                points += 10; // adding 10 points if you eat an apple
            } else {
                _game_map[coordinates_back.first][coordinates_back.second] = spacebar;
                set_cursor_position(coordinates_back.first + 2, 2 * coordinates_back.second); // erasing the tail if apple was not eaten
                std::cout << " ";
                snek.pop_back();
            }
            if (if_apple_eaten == 1) {
                while (apple_found == 0) {
                    apple.x = random_apple_coordinates(size);
                    apple.y = random_apple_coordinates(size);
                    if (_game_map[apple.x][apple.y] == spacebar) {
                        _game_map[apple.x][apple.y] = star;
                        set_cursor_position(apple.x + 2, 2 * apple.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0004);
                        // setting apple colour to red
                        // set_console_colour(FOREGROUND_RED);
                        std::cout << "*";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
                        // setting default terminal colours
                        // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
                        apple_found = true;
                        if_apple_eaten = false;
                    }
                }
            }
            
        }
        if (direction == 'u') {
            apple_found = false;
            _game_map[snek[0].first][snek[0].second] = 'o';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting current head as a body
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000a);
            // setting snake colour to green
            // set_console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
            std::cout << "o";
            coordinates_front.first =
                    (coordinates_front.first - 1) % (size - 2); // setting next snakes' head coordinates
            if (_game_map[coordinates_front.first][coordinates_front.second] ==
                111) { // player looses if snake tries to eat itself
                fail = true;
                break;
            }
            if (a == 2) { // loosing the game if snake tries to eat the wall
                if (_game_map[coordinates_front.first][coordinates_front.second] == hash) {
                    fail = true;
                    break;
                }
            }
            if (_game_map[coordinates_front.first][coordinates_front.second] == hash) { // if snake goes into the wall
                coordinates_front.first = size - 2;
            }
            snek.push_front(coordinates_front);
            _game_map[snek[0].first][snek[0].second] = 'O';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting snakes' head to new position
            std::cout << "O";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
            // setting default terminal colours
            // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
            if (coordinates_front.first == apple.x && coordinates_front.second == apple.y) {
                if_apple_eaten = true;
                // setting apple to eaten, no need to erase snakes' tail
                points += 10; // adding 10 points if you eat an apple
            } else {
                _game_map[coordinates_back.first][coordinates_back.second] = spacebar;
                set_cursor_position(coordinates_back.first + 2,
                                    2 * coordinates_back.second); // erasing the tail if apple was not eaten
                std::cout << " ";
                snek.pop_back();
            }
            if (if_apple_eaten == 1) {
                while (apple_found == 0) {
                    apple.x = random_apple_coordinates(size);
                    apple.y = random_apple_coordinates(size);
                    if (_game_map[apple.x][apple.y] == spacebar) {
                        _game_map[apple.x][apple.y] = star;
                        set_cursor_position(apple.x + 2, 2 * apple.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0004);
                        // set_console_colour(FOREGROUND_RED); // setting apple colour to red
                        std::cout << "*";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007);
                        // setting default terminal colours
                        // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
                        apple_found = true;
                        if_apple_eaten = false;
                    }
                }
            }
        }
        if (direction == 'l') {
            apple_found = false;
            _game_map[snek[0].first][snek[0].second] = 'o';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting current head as a body
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000a); // setting snake colour to green
            // set_console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
            std::cout << "o";
            coordinates_front.second =
                    (coordinates_front.second - 1) % (size - 2); // setting next snakes' head coordinates
            if (_game_map[coordinates_front.first][coordinates_front.second] ==
                111) { // player looses if snake tries to eat itself
                fail = true;
                break;
            }
            if (a == 2) { // loosing the game if snake tries to eat the wall
                if (_game_map[coordinates_front.first][coordinates_front.second] == hash) {
                    fail = true;
                    break;
                }
            }
            if (_game_map[coordinates_front.first][coordinates_front.second] == hash) { // if snake goes into the wall
                coordinates_front.second = size - 2;
            }
            snek.push_front(coordinates_front);
            _game_map[snek[0].first][snek[0].second] = 'O';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting snakes' head to new position
            std::cout << "O";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); // setting default terminal colours
            // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
            if (coordinates_front.first == apple.x && coordinates_front.second == apple.y) {
                if_apple_eaten = true;
                // setting apple to eaten, no need to erase snakes' tail
                points += 10; // adding 10 points if you eat an apple
            } else {
                _game_map[coordinates_back.first][coordinates_back.second] = spacebar;
                set_cursor_position(coordinates_back.first + 2,
                                    2 * coordinates_back.second); // erasing the tail if apple was not eaten
                std::cout << " ";
                snek.pop_back();
            }
            if (if_apple_eaten == 1) {
                while (apple_found == 0) {
                    apple.x = random_apple_coordinates(size);
                    apple.y = random_apple_coordinates(size);
                    if (_game_map[apple.x][apple.y] == spacebar) {
                        _game_map[apple.x][apple.y] = star;
                        set_cursor_position(apple.x + 2, 2 * apple.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0004); // setting apple colour to red
                        // set_console_colour(FOREGROUND_RED);
                        std::cout << "*";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); // setting default terminal colours
                        // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
                        apple_found = true;
                        if_apple_eaten = false;
                    }
                }
            }
        }
        if (direction == 'r') {
            apple_found = false;
            _game_map[snek[0].first][snek[0].second] = 'o';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting current head as a body
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000a); // setting snake colour to green
            // set_console_colour(FOREGROUND_GREEN| FOREGROUND_INTENSITY);
            std::cout << "o";
            coordinates_front.second =
                    (coordinates_front.second + 1) % (size - 1); // setting next snakes' head coordinates
            if (_game_map[coordinates_front.first][coordinates_front.second] ==
                111) { // player looses if snake tries to eat itself
                fail = true;
                break;
            }
            if (a == 2) { // loosing the game if snake tries to eat the wall
                if (_game_map[coordinates_front.first][coordinates_front.second] == hash) {
                    fail = true;
                    break;
                }
            }
            if (_game_map[coordinates_front.first][coordinates_front.second] == hash) { // if snake goes into the wall
                coordinates_front.second = 1;
            }
            snek.push_front(coordinates_front);
            _game_map[snek[0].first][snek[0].second] = 'O';
            set_cursor_position(snek[0].first + 2, 2 * snek[0].second); // setting snakes' head to new position
            std::cout << "O";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); // setting default terminal colours
            // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
            if (coordinates_front.first == apple.x && coordinates_front.second == apple.y) {
                if_apple_eaten = true;
                // setting apple to eaten, no need to erase snakes' tail
                points += 10; // adding 10 points if you eat an apple
            } else {
                _game_map[coordinates_back.first][coordinates_back.second] = spacebar;
                set_cursor_position(coordinates_back.first + 2,
                                    2 * coordinates_back.second); // erasing the tail if apple was not eaten
                std::cout << " ";
                snek.pop_back();
            }
            if (if_apple_eaten == 1) {
                while (apple_found == 0) {
                    apple.x = random_apple_coordinates(size);
                    apple.y = random_apple_coordinates(size);
                    if (_game_map[apple.x][apple.y] == spacebar) {
                        _game_map[apple.x][apple.y] = star;
                        set_cursor_position(apple.x + 2, 2 * apple.y);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0004); // setting apple colour to red
                        // set_console_colour(FOREGROUND_RED);
                        std::cout << "*";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); // setting default terminal colours
                        // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
                        apple_found = true;
                        if_apple_eaten = false;
                    }
                }
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(SPEED));
    }
}

int main() {
    PlaySound(TEXT("theme-music.wav"), NULL, SND_ASYNC | SND_LOOP);
    // function to play music in background
    hidecursor();       // running function to hide cursor
    SetConsoleTitle("SNAKE"); // changing console title
    std::fstream wynik; // creating .txt file with gamescore
    int map_size;
    srand(GetTickCount());
    std::cout << "Choose gamemode:" << std::endl << "1. Snake can go through walls." << std::endl;
    std::cout << "2. Snake dies if runs into the wall." << std::endl; // choosing gamemode
    std::cin >> a;
    while (a != 1 && a != 2) {
        std::cout << "Wrong number, choose \"1\" or \"2\": ";
        std::cin >> a;
    }
    system("cls");
    std::cout << "Choose map size:" << std::endl;
    std::cin >> map_size;
    char **game_map;
    game_map = new char *[map_size];
    for (int i = 0; i < map_size; i++) game_map[i] = new char[map_size];
    for (int i = 0; i < map_size; i++) {
        for (int j = 0; j < map_size; j++) {
            game_map[i][j] = spacebar; // spacebar
        }
    }
    for (int i = 0; i < map_size; i++) { // setting botders to hash
        game_map[0][i] = hash; // hasz
        game_map[i][0] = hash;
        game_map[map_size - 1][i] = hash;
        game_map[i][map_size - 1] = hash;
    }
    snek.push_front(
    std::make_pair((map_size - 1) / 2, (map_size - 1) / 2)); // setting snakes' head coordinates in the middle
    game_map[(map_size - 1) / 2][(map_size - 1) / 2] = 'O';
    apple_found = false;
    char direction;
    print_game_map(map_size, game_map);
    direction = 'u';
    bool if_apple_eaten = true;
    while (fail == 0) {
        hidecursor();
        char _key_press = 0;
        apple_found = false;
        if_apple_eaten == true;
        std::thread t(ruch, snek.front(), snek.back(), direction, game_map, map_size);
        _key_press = _getch();
        stop = true;
        t.join();
        if (_key_press == 72) { // UP
            direction = 'u';
        }
        if (_key_press == 80) { // DOWN
            direction = 'd';
        }
        if (_key_press == 75) { // LEFT
            direction = 'l';
        }
        if (_key_press == 77) { // RIGHT
            direction = 'r';
        }
        if (if_apple_eaten == 1) {
            while (apple_found == 0) {
                apple.x = random_apple_coordinates(map_size);
                apple.y = random_apple_coordinates(map_size);
                if (game_map[apple.x][apple.y] == spacebar) {
                    game_map[apple.x][apple.y] = star;
                    set_cursor_position(apple.x + 2, 2 * apple.y);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0004); // setting apple colour to red
                    // set_console_colour(FOREGROUND_RED);
                    std::cout << "*";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0007); // setting default terminal colours
                    // set_console_colour(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | COMMON_LVB_REVERSE_VIDEO);
                    apple_found = true;
                    if_apple_eaten = false;
                }
            }
        }
        stop = false;
    }
    if (fail == 1) { // what happens after loosing game
        GameOver();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x000f);
        wynik.open("wyniki.txt", std::ios::in | std::ios::out);
        // opening .txt file with game results
        double previous_results;
        wynik >> previous_results; // reading previous game results
        if (points > previous_results) {
            // if current points are higher then previous results
            wynik << points; // replacing previous results with new ones
            std::cout << " CONGRATULATIONS!!! NEW RECORD!!! - " << points << " PKT";
        } else {
            wynik << previous_results; // IF RECORD WAS NOT BEATEN
            std::cout << "You've lost, Your points: " << points << " PKT" << std::endl << "Current record: " <<
            previous_results << " PKT";
        }
        wynik.close(); // closing file
        stop = true;
        return 0;
    }
}
