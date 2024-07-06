/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : ray3
 * @created     : Vineri Mar 22, 2024 07:15:42 EET
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __cplusplus
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/ostream.h"
#include "fmt/printf.h"
#include "fmt/ranges.h"
#include "fmt/xchar.h"
#endif
#include <curl/curl.h>

#include "raylib.h"

size_t cb(char* d, size_t n, size_t l, void* p) {
  /* fwrite(d, n, l, (FILE*)p); */
  fprintf(stderr, "Data: %s\n", d);
  return l;
}

void* ThreadFunction(void* arg) {
  // Simulate some worklay being done
  for (int i = 0; i < 10; ++i) {
    // Sleep for a short duration to simulate work
    sleep(1);
    // Print a message to the console
    printf("Thread working...\n");
  }

  CURL* curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "http://example.com");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    curl_easy_cleanup(curl);
  }

  return NULL;
}

/* typedef void (*TraceLogCallback)(int logLevel, const char *text, va_list
 * args);  // Logging: Redirect trace log messages */

TraceLogCallback logging_func;

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  TraceLog(LOG_INFO, "Starting raylib play button example");

  SetTraceLogCallback(logging_func);
  // Initialize window and OpenGL context
  InitWindow(screenWidth, screenHeight, "Raylib Play Button");

  // Load play button texture
  Texture2D playButton = LoadTexture("play_button.png");

  // Calculate button position
  float buttonWidth = playButton.width;
  float buttonHeight = playButton.height;
  float buttonX = (screenWidth - buttonWidth) / 2;
  float buttonY = (screenHeight - buttonHeight) / 2;

  // Main loop
  while (!WindowShouldClose()) {
    // Check if the play button is pressed
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      // Check if the mouse is inside the play button

      Rectangle position = {buttonX, buttonY, buttonWidth, buttonHeight};
      if (CheckCollisionPointRec(GetMousePosition(), position)) {
        // Start a new thread
        /* std::thread thread(ThreadFunction); */
        pthread_t thread;
        pthread_create(&thread, NULL, ThreadFunction, NULL);
        // Detach the thread to let it run independently
        pthread_detach(thread);
      }
    }

    // Draw
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw play button
    DrawTexture(playButton, buttonX, buttonY, WHITE);

    EndDrawing();
  }

  // Unload texture
  UnloadTexture(playButton);

  // Close window and OpenGL context
  CloseWindow();

  return 0;
}

