#include "raylib.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

void swap(int *x_pointer, int *y_pointer)
{
    int temp = *x_pointer;
    *x_pointer = *y_pointer;
    *y_pointer = temp;
}
int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "sorting visualizer");
    SetTargetFPS(144);
    double curTime = GetTime();
    
    ///////SETUP RANDOM VECTOR///////
    std::vector<int> v(screenHeight);
    std::iota (std::begin(v), std::end(v), 0);
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(v), std::end(v), rng);
    int n = v.size();
    ////////////////////////////////
    
    int min_val = screenHeight + 1;
    int index = 0;
    int cur = 0;
    
    bool selection_start = false;
    bool insertion_start = false;
    bool bubble_start = false;
    
    bool render = false;
    bool menu  = true;
    bool done = false;
    
    while (!WindowShouldClose()) {
        
        BeginDrawing();
            ClearBackground(BLACK);
            
                /////////////
                /*MAIN MENU*/
                /////////////
                if (menu) {
                    DrawText("Sorting Visualizer", 40, 200, 80, LIGHTGRAY);
                    DrawText("Press Enter to Start", 270, 400, 20, LIGHTGRAY);
                }
                
                //KEY PRESS
                if (IsKeyPressed(KEY_ONE)) {
                    selection_start = true;
                    curTime = GetTime();
                    render = false;
                }
                if (IsKeyPressed(KEY_TWO)) {
                    insertion_start = true;
                    curTime = GetTime();
                    render = false;
                }
                if (IsKeyPressed(KEY_THREE)) {
                    bubble_start = true;
                    curTime = GetTime();
                    render = false;
                }
                if (IsKeyPressed(KEY_ENTER)) {
                    done = false;
                    render = true;
                    auto rng = std::default_random_engine {};
                    std::shuffle(std::begin(v), std::end(v), rng);
                    menu =  false;
                    selection_start = false;
                    insertion_start = false;
                    bubble_start = false;
                    min_val = screenHeight + 1;
                    cur = 0; 
                } 
                
                //////////////////
                /*SHUFFLE MENU*///
                //////////////////
                if (render) {                   
                    for (int i = 0; i < n;i++) {
                        DrawRectangle(i, 0, 1, v[i], RED);
                    }
                    DrawText("Press Enter to shuffle", 200, 300, 30, RAYWHITE);
                    DrawText("Press 1 for selection sort", 200, 340, 30, RAYWHITE);
                    DrawText("Press 2 for insertion sort", 200, 380, 30, RAYWHITE);
                    DrawText("Press 3 for bubble sort", 200, 420, 30, RAYWHITE);
                }
                
                //////////////////
                /*SELECTION SORT*/
                //////////////////
                if ((GetTime() > curTime) && selection_start) {
                    //selection sort
                    
                    if (cur < n) {
                        for(int i = cur+1; i < n; i++){
                            if (v[i] < min_val) {
                                index = i;
                                min_val = v[i];
                            }
                        }
                        v[index] = v[cur];
                        v[cur] = min_val;
                        cur ++;
                        min_val = screenHeight + 1;
                    }else {
                        done = true;
                    }
                    //render  
                    for (int i = 0; i < n;i++) {
                        DrawRectangle(i, 0, 1, v[i], RED);
                    }
                    
                }
                //////////////////
                /*INSERTION SORT*/
                //////////////////
                if ((GetTime() > curTime) && insertion_start) {
                    //insertion sort
                    if (cur < n) {
                        int key, j;
                        key = v[cur];
                        j = cur - 1;
                        while (j >= 0 && v[j] > key){
                            v[j + 1] = v[j];
                            j = j - 1;
                        }
                        v[j + 1] = key;
                        cur++;
                    }else {
                        done = true;
                    }
                    
                    //render  
                    for (int i = 0; i < n;i++) {
                        DrawRectangle(i, 0, 1, v[i], RED);
                    }
                    
                }
                ///////////////
                /*BUBBLE SORT*/
                ///////////////
                if ((GetTime() > curTime) && bubble_start) {
                    //bubble sort
                    if (cur < n) {
                        for (int j = 0; j < n-cur-1; j++){
                            if (v[j] > v[j+1]){
                                swap(&v[j], &v[j+1]);
                            }
                        }
                        cur++;
                    } else {
                        done = true;
                    }
                    
                    //render  
                    for (int i = 0; i < n;i++) {
                        DrawRectangle(i, 0, 1, v[i], RED);
                    }
                    
                }
                
                if (done) {
                    for (int i = 0; i < n;i++) {
                        DrawRectangle(i, 0, 1, v[i], GREEN);
                    }
                    DrawText("Done! Press Enter to go again.", 50, 400, 20, GREEN);
                }
            
            
            
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
