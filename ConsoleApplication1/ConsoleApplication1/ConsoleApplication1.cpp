#include <SDL.h>
#include <iostream>
#include <vector>

using namespace std;

// Структура для стен лабиринта  
struct Wall {
    SDL_Rect rect;
};

struct Finish {
    SDL_Rect rect;
};


void clearScreen(SDL_Renderer* renderer, SDL_Color backgroundColor) {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);
}

// Функция для отрисовки лабиринта  
void drawMaze(SDL_Renderer* renderer, const vector<Wall>& walls) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Красный цвет для стен  
    for (const auto& wall : walls) {
        SDL_RenderFillRect(renderer, &wall.rect);
    }
}

void drawFinish(SDL_Renderer* renderer, const vector<Finish>& fin) {
    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 255); // Зеленый цвет для стен  
    for (const auto& Finish : fin) {
        SDL_RenderFillRect(renderer, &Finish.rect);
    }
}

int main(int argc, char* argv[]) {
    // Инициализация SDL  
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Ошибка инициализации SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Создаем окно  
    SDL_Window* window = SDL_CreateWindow("EZ GAMER 2",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Ошибка создания окна: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Создаем рендер  
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Ошибка создания рендера: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Загрузка изображения персонажа  
    SDL_Surface* tempSurface = SDL_LoadBMP("character.bmp");
    if (!tempSurface) {
        cout << "Ошибка загрузки изображения: " << SDL_GetError() << endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    SDL_Texture* characterTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_Rect characterRect = { 100, 100, 64, 64 }; // Положение и размер персонажа  
    double speed = 1; // Скорость перемещения  

    // Определяем границы окна  
    int windowWidth = 800;
    int windowHeight = 600;

    // Создаем лабиринт (стены)  
    vector<Wall> walls = {
        {{1, 0, 10, 600}},
        {{1, 0, 800, 10}},
        {{1, 590, 800, 10}},
        {{790, 10, 10, 400}},
        {{1, 200, 600, 10}},
        {{200, 400, 600, 10}}
    };

    //Создаем финиш
    vector<Finish> fin = {
        {{782, 410, 100, 180}}
    };

    // Основной цикл игры  
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // Обрабатываем события  
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Получение состояния клавиш  
        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // Временные переменные для нового положения персонажа  
        SDL_Rect newCharacterRect = characterRect;

        // Обработка нажатий клавиш WASD  
        if (keystate[SDL_SCANCODE_W]) {
            newCharacterRect.y -= speed;
        }
        if (keystate[SDL_SCANCODE_S]) {
            newCharacterRect.y += speed;
        }
        if (keystate[SDL_SCANCODE_A]) {
            newCharacterRect.x -= speed;
        }
        if (keystate[SDL_SCANCODE_D]) {
            newCharacterRect.x += speed;
        }

        
        SDL_Color backgroundColor = { 0, 0, 0, 255 }; // Цвет фона (черный)

        // Проверка столкновений со стенами  
        
        bool collision = false;
        bool fam = false;

        for (const auto& wall : walls) {
            if (SDL_HasIntersection(&newCharacterRect, &wall.rect)) {
                collision = true;
                break;
            }
        }

        for (const auto& Finish : fin) {
            if (SDL_HasIntersection(&newCharacterRect, &Finish.rect)) {
                fam = true;
                break;
            }
        }
        
        if (collision) {
            characterRect = { 100, 100, 64, 64 };
        }

        if (fam) {
            clearScreen(renderer, backgroundColor);
            SDL_RenderPresent(renderer);
        }
        

        // Перемещение персонажа, если нет столкновений  
        if (!collision && !fam) {
            characterRect = newCharacterRect;
            SDL_Delay(1);
        }


        

        // Очищаем экран  
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Черный фон  
        SDL_RenderClear(renderer);

        // Отрисовка лабиринта  
        drawMaze(renderer, walls);

        drawFinish(renderer, fin);
        // Отрисовка персонажа  
        SDL_RenderCopy(renderer, characterTexture, NULL, &characterRect);

        // Обновляем экран  
        SDL_RenderPresent(renderer);
    }

    // Очищаем ресурсы  
    SDL_DestroyTexture(characterTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}