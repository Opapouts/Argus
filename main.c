#include <stdio.h>
#include <curl/curl.h>
#include "raylib.h"

int main(void)
{
    // 1. Test libcurl
    // This will print the current version of curl installed on the machine
    printf("--- Testing libcurl ---\n");
    printf("libcurl version: %s\n\n", curl_version());

    // 2. Test Raylib
    // This will briefly open a small window and close it immediately 
    // to prove the GPU/graphics linker works.
    printf("--- Testing Raylib ---\n");
    InitWindow(400, 200, "Makefile Test");
    
    if (IsWindowReady())
    {
        printf("Raylib successfully initialized and linked!\n");
        CloseWindow();
    }
    else
    {
        printf("Error: Raylib window could not be created.\n");
        return (1);
    }

    printf("\nSuccess! Both libraries are fully accessible.\n");
    return (0);
}
