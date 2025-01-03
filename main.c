#include <stdio.h>
#include <SDL2/SDL.h>

#define TABLE_SIZE 5
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 200
#define RECT_WIDTH 60
#define RECT_HEIGHT 60

// Structure to represent a Hash Table slot
typedef struct {
    int key;
    int isOccupied; // 1 if occupied, 0 if empty
} HashTable;

// Hash function
unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

// Initialize the hash table
void initHashTable(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].key = -1;       // -1 indicates no valid key
        table[i].isOccupied = 0; // Slot is empty
    }
}

// Insert a key into the hash table
void insertKey(HashTable* table, int key) {
    unsigned int index = hash(key);
    table[index].key = key;
    table[index].isOccupied = 1; // Mark as occupied
}

// Render the hash table using SDL2
void renderHashTable(SDL_Renderer* renderer, HashTable* table) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int x = 50 + i * (RECT_WIDTH + 10); // Horizontal placement
        int y = 75;

        // Draw rectangles for hash table slots
        SDL_Rect rect = {x, y, RECT_WIDTH, RECT_HEIGHT};
        if (table[i].isOccupied) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for occupied
            SDL_RenderFillRect(renderer, &rect);
        } else {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for empty
            SDL_RenderFillRect(renderer, &rect);
        }

        // Draw the border
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black for border
        SDL_RenderDrawRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer); // Present all drawings
}

int main(int argc, char* argv[]) {
    HashTable table[TABLE_SIZE];
    initHashTable(table);

    // Sample keys to insert
    insertKey(table, 3);
    insertKey(table, 8);
    insertKey(table, 13);

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Hash Table Visualization",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window Creation Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer Creation Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int running = 1;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Render the hash table
        renderHashTable(renderer, table);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
