//Panturu Gloria Sara
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void print(FILE* fd, struct winsize *ws);
void show_more_or_less(FILE* fd, struct winsize *ws, int page);

int main(int argc,char *argv[])
{
	struct winsize ws;
	FILE* fd = fopen(argv[1], "r");

	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}

	show_more_or_less(fd, &ws, 0);

	printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
	ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);

	fclose(fd);
	return 0;
}

void show_more_or_less(FILE *fd, struct winsize *ws, int page) {
    rewind(fd);
    if (fd == 0)
		{
			return;
		}
    int count_row = 0;
    while (count_row <= page) {
        system("clear");
        print(fd, ws);
        count_row++;
    }
    char letter = getchar();
    if (!feof(fd) && letter == '\n') {
        show_more_or_less(fd, ws, page+1);
    }

		else if (letter == 'b' && page > 0) {
        while (letter != '\n')
            letter = getchar();
        show_more_or_less(fd, ws, page-1);
    }
		else if (letter != '\n') {
			 while (letter != '\n')
					 letter = getchar();
			 show_more_or_less(fd, ws, page);
	 }
}

void print(FILE* fd, struct winsize *ws)
{
    char* row = malloc(sizeof(char) * (ws->ws_col + 1));

    for (int i = 0; i < ws->ws_row && !feof(fd); i++) {
        fgets(row, ws->ws_col, fd);
        printf("%s", row);
    }
    free(row);
}
