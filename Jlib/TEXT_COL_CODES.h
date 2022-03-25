#ifndef TEXT_COL_CODES
#define TEXT_COL_CODES
/*This is a set of defines that will ease making fancy console colouring.*/
#include <stdio.h>
//coloured text code for foreground.
#define fg_BLACK "\033[0;30m"
#define fg_RED "\033[0;31m"
#define fg_GREEN "\033[0;32m"
#define fg_YELLOW "\033[0;33m"
#define fg_BLUE "\033[0;34m"
#define fg_PURPLE "\033[0;35m"
#define fg_CYAN "\033[0;36m"
#define fg_WHITE "\033[0;37m"

#define bg_BLACK "\033[0;40m"
#define bg_RED "\033[0;41m"
#define bg_GREEN "\033[0;42m"
#define bg_YELLOW "\033[0;43m"
#define bg_BLUE "\033[0;44m"
#define bg_PURPLE "\033[0;45m"
#define bg_CYAN "\033[0;46m"
#define bg_WHITE "\033[0;47m"

void setPrintBackgroundBLACK(){printf(bg_BLACK);}
void setPrintBackgroundRED(){printf(bg_RED);}
void setPrintBackgroundGREEN(){printf(bg_GREEN);}
void setPrintBackgroundYELLOW(){printf(bg_YELLOW);}
void setPrintBackgroundBLUE(){printf(bg_BLUE);}
void setPrintBackgroundPURPLE(){printf(bg_PURPLE);}
void setPrintBackgroundCYAN(){printf(bg_CYAN);}
void setPrintBackgroundWHITE(){printf(bg_WHITE);}

void setPrintForegroundBLACK(){printf(fg_BLACK);}
void setPrintForegroundRED(){printf(fg_RED);}
void setPrintForegroundGREEN(){printf(fg_GREEN);}
void setPrintForegroundYELLOW(){printf(fg_YELLOW);}
void setPrintForegroundBLUE(){printf(fg_BLUE);}
void setPrintForegroundPURPLE(){printf(fg_PURPLE);}
void setPrintForegroundCYAN(){printf(fg_CYAN);}
void setPrintForegroundWHITE(){printf(fg_WHITE);}
//
void printTextWithBLACKBackground(char* buffer){printf(bg_BLACK"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithREDBackground(char* buffer){printf(bg_RED"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithGREENBackground(char* buffer){printf(bg_GREEN"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithYELLOWBackground(char* buffer){printf(bg_YELLOW"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithBLUEBackground(char* buffer){printf(bg_BLUE"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithPURPLEBackground(char* buffer){printf(bg_PURPLE"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithCYANBackground(char* buffer){printf(bg_CYAN"%s", buffer); setPrintBackgroundBLACK();}
void printTextWithWHITEBackground(char* buffer){printf(bg_WHITE"%s", buffer); setPrintBackgroundBLACK();}

void PXL(int col)
{
	char* frgnd[] =
	{
		fg_BLACK
		fg_RED
		fg_GREEN
		fg_YELLOW
		fg_BLUE
		fg_PURPLE
		fg_CYAN
		fg_WHITE
	};
	char* bckgnd[] =
	{
		bg_BLACK
		bg_RED
		bg_GREEN
		bg_YELLOW
		bg_BLUE
		bg_PURPLE
		bg_CYAN
		bg_WHITE
	};
	printf("%s%s", frgnd[col], bckgnd[col]);
}

void resetPrintColours()
{
	setPrintBackgroundBLACK();
	setPrintForegroundWHITE();
}

#endif
