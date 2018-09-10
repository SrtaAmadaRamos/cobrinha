#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

#ifndef _WIN32
	#include <termios.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include "funLinux.c"
#else
	#include <conio.h>
	#include <windows.h>
#endif
#include  "tempo.c"
