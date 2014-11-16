#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <stdio.h>

#include "test5.h"

// TEST ///////////////////////////////////////////////////////
#include "video_gr.h"
#include "timer.h"

static int proc_args(int argc, char *argv[]);
static unsigned long parse_ulong(char *str, int base);
static long parse_long(char *str, int base);
static void print_usage(char *argv[]);

int main(int argc, char **argv)
{

  sef_startup();

  if ( argc == 1 ) {
      print_usage(argv);
      return 0;
  } else {
      proc_args(argc, argv);
  }

  return 0;

}

static void print_usage(char *argv[]) {
	printf("Usage: one of the following:\n"
			"\t service run %s -args \"init <hex-code> <int-delay>\" \n"
			"\t service run %s -args \"square <int-x> <int-y> <int-size> <int-color>\" \n"
			"\t service run %s -args \"line <int-xi> <int-yi> <int-xf> <int-yf> <int-color>\" \n"
			"\t service run %s -args \"xpm <int-xi> <int-yi> <char*-xpm>\" \n"
			"\t service run %s -args \"move <int-xi> <int-yi> <char*-xpm> <int-hor> <int-delta> <int-time>\" \n",
			argv[0], argv[0], argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char *argv[])
{

  if (strncmp(argv[1], "init", strlen("init")) == 0) {
	  if( argc != 4 ) {
		  printf("vbe: wrong no of arguments for test_init() \n");
		  return 1;
	  }

	  unsigned short mode = parse_ulong(argv[2], 16);
	  unsigned short delay = parse_ulong(argv[3], 10);

	  printf("vbe:: test_init(0x%X, %u)\n", mode, delay);

	  test_init(mode, delay);

	  return 0;
  } else {
	  printf("vbe: non valid function \"%s\" to test\n", argv[1]);
	  return 1;
  }
}

static unsigned long parse_ulong(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtoul(str, &endptr, base);

  if ((errno == ERANGE && val == ULONG_MAX )
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return ULONG_MAX;
  }

  if (endptr == str) {
	  printf("video_txt: parse_ulong: no digits were found in %s \n", str);
	  return ULONG_MAX;
  }

  /* Successful conversion */
  return val;
}

static long parse_long(char *str, int base) {
  char *endptr;
  unsigned long val;

  val = strtol(str, &endptr, base);

  if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
	  || (errno != 0 && val == 0)) {
	  perror("strtol");
	  return LONG_MAX;
  }

  if (endptr == str) {
	  printf("video_txt: parse_long: no digits were found in %s \n", str);
	  return LONG_MAX;
  }

  /* Successful conversion */
  return val;
}
