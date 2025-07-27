#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

struct screen_size {
  int width;
  int height;
};

struct screen_size get_screen_size() {
  Display *d = XOpenDisplay(NULL);
  Screen *s = DefaultScreenOfDisplay(d);
  struct screen_size size;

  size.width = s->width;
  size.height = s->height;

  XCloseDisplay(d);

  return size;
}

int main(int argc, char *argv[]) {

  const char *display = getenv("DISPLAY");

  const char *cmd_temp =
      "ffmpeg -video_size %s -framerate 25 -f x11grab -i %s .mkv";

  char cmd[512];

  struct screen_size screen_size = get_screen_size();

  const char *display_size_temp = "%dx%d";
  char display_size[128];
  snprintf(display_size, sizeof(display_size), display_size_temp,
           screen_size.width, screen_size.height);

  snprintf(cmd, sizeof(cmd), cmd_temp, display_size, display);

  printf("%s", cmd);

  // const char *cmd =
  //     "ffmpeg -video_size 1366x768 -framerate 25 -f x11grab -i :1 .mkv";
  // system(cmd);
  // printf("record");
  return 0;
}
