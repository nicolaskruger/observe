#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  const char *display = getenv("DISPLAY");

  const char *cmd_temp =
      "ffmpeg -video_size %s -framerate 25 -f x11grab -i %s .mkv";

  char cmd[512];

  Display *d = XOpenDisplay(NULL);
  Screen *s = DefaultScreenOfDisplay(d);
  int w = s->width;
  int h = s->height;

  const char *display_size_temp = "%dx%d";
  char display_size[128];
  snprintf(display_size, sizeof(display_size), display_size_temp, w, h);

  snprintf(cmd, sizeof(cmd), cmd_temp, display_size, display);

  printf("%s", cmd);

  // const char *cmd =
  //     "ffmpeg -video_size 1366x768 -framerate 25 -f x11grab -i :1 .mkv";
  // system(cmd);
  // printf("record");
  return 0;
}
