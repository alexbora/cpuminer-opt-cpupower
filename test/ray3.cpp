/**
 * @author      : alex (alexbora@gmail.com)
 * @file        : ray3
 * @created     : Vineri Mar 22, 2024 07:00:19 EET
 */

#include <curl/curl.h>
#include <stdlib.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "raylib.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

size_t callback(void *ptr, size_t size, size_t nmemb, std::string *data) {
  data->append((char *)ptr, size * nmemb);
  return size * nmemb;
}

void connect_to_url(const char *url, std::string &response_string) {
  CURL *curl = NULL;
  CURLcode res = CURLE_OK;
  curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "curl_easy_init() failed\n");
    exit(1);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
  curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
  curl_easy_setopt(
      curl, CURLOPT_WRITEFUNCTION,
      [](void *ptr, size_t size, size_t nmemb, void *data) -> size_t {
        std::cout << "Data: " << (char *)ptr << std::endl;
        return nmemb * size;
      });
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

  pthread_mutex_lock(&mutex);
  res = curl_easy_perform(curl);

  if (res == CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    exit(1);
  }

  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

void ThreadFunction() {
  // Simulate some worklay being done
  for (int i = 0; i < 10; ++i) {
    // Sleep for a short duration to simulate work
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Print a message to the console
    printf("Thread working...\n");
  }
}

class Window {
 public:
  Window(int x, int y);
  ~Window();

 private:
  int x, y;
};

Window::~Window() {
  // Close window and OpenGL context
  CloseWindow();
}

Window::Window(int x_, int y_) : x(x_), y(y_) {
  // Initialize window and OpenGL context
  InitWindow(800, 450, "Raylib Play Button");
}

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  // Initialize window and OpenGL context
  InitWindow(screenWidth, screenHeight, "Raylib Play Button");

  // Load play button texture
  Texture2D playButton = LoadTexture("play_button.png");

  // Calculate button position
  int buttonWidth = playButton.width;
  int buttonHeight = playButton.height;
  int buttonX = (screenWidth - buttonWidth) / 2;
  int buttonY = (screenHeight - buttonHeight) / 2;

  // Main loop
  while (!WindowShouldClose()) {
    // Check if the play button is pressed
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      // Check if the mouse is inside the play button
      if (CheckCollisionPointRec(GetMousePosition(),
                                 {(float)buttonX, (float)buttonY,
                                  (float)buttonWidth, (float)buttonHeight})) {
        // Start a new thread
        std::thread thread(ThreadFunction);
        // Detach the thread to let it run independently
        thread.detach();

        std::string response_string;
        std::thread thread_url;
        thread_url = std::thread(connect_to_url, "google.com",
                                 std::ref(response_string));
        thread_url.detach();

        /* std::thread t1(connect_to_url, "google.com",
         * std::ref(response_string)); */
        /* t1.detach(); */

        // Wait for the thread to finish
        /* thread.join(); */
        std::cout << "Response" << response_string << std::endl;
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

