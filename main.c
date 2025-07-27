#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

struct screen_size {
  int width;
  int height;
};

struct cmd_opt {
  char *screen_name;
  struct screen_size screen_size;
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

char *cmd_gen(struct cmd_opt _cmd) {

  const int buffer_size = 512;

  const char *cmd_temp =
      "ffmpeg -video_size %s -framerate 25 -f x11grab -i %s .mkv";

  char *cmd = malloc(buffer_size);

  struct screen_size screen_size = get_screen_size();

  const char *display_size_temp = "%dx%d";
  char display_size[128];
  snprintf(display_size, sizeof(display_size), display_size_temp,
           screen_size.width, screen_size.height);

  snprintf(cmd, buffer_size, cmd_temp, display_size, _cmd.screen_name);

  return cmd;
}

int main(int argc, char *argv[]) {

  struct cmd_opt _cmd_opt;
  _cmd_opt.screen_name = getenv("DISPLAY");
  _cmd_opt.screen_size = get_screen_size();

  char *cmd = cmd_gen(_cmd_opt);

  printf("%s", cmd);

  // const char *cmd =
  //     "ffmpeg -video_size 1366x768 -framerate 25 -f x11grab -i :1 .mkv";
  // system(cmd);
  // printf("record");

  free(cmd);
  return 0;
}
