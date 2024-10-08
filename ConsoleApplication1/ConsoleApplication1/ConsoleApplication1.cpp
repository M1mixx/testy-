#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Ошибка инициализации SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Создание окна
    SDL_Window* window = SDL_CreateWindow("Моя игра",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Ошибка создания окна: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
    printf("Ошибка создания рендера: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}
    SDL_SetRenderDrawColor(renderer, 432, 122, 200, 167); // Устанавливаем цвет для отрисовки (синий)
    SDL_RenderClear(renderer); // Очищаем экран (заливаем синим цветом)

    SDL_Rect rect = { 100, 100, 200, 150 }; // Определяем прямоугольник
    SDL_SetRenderDrawColor(renderer, 255, 160, 122, 255); // Устанавливаем цвет для прямоугольника (красный)
    SDL_RenderFillRect(renderer, &rect); // Отрисовываем заполненный прямоугольник

    SDL_RenderPresent(renderer); // Выводим результат на экран

    SDL_Surface* surface = SDL_LoadBMP("image.bmp");
    if (!surface) {
        printf("Ошибка загрузки изображения: %s\n", SDL_GetError());
    }

    // Задержка перед закрытием окна (пока просто держим окно открытым)
    SDL_Delay(5000);

    // Уничтожение окна и завершение работы SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}