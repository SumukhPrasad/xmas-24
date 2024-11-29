#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define H 21
#define W 79
#define SNOWFLAKE_COUNT 25
#define STAR_COUNT 40
#define ORNAMENT_COUNT 10
#define SNOWFLAKE_SPEED 1
#define GREEN_COLOR_START 22
#define GREEN_COLOR_END 46
#define GREEN_COLOR_JUMP 6
#define RESET "\x1b[0m"
#define clrscr() printf("\e[1;1H\e[2J")

typedef struct {
    int x, y;
} Snowflake;

typedef struct {
    int x, y;
} Star;

typedef struct {
    int x, y;
    int color;
} Ornament;

Snowflake snowflakes[SNOWFLAKE_COUNT];
Star stars[STAR_COUNT];
Ornament ornaments[ORNAMENT_COUNT];

char workingbuf[H][W][1];
int workingcolorbuf[H][W];
int screencolorbuf[H][W];
char screenbuf[H][W][1];

void initialise() {
	srand(time(0)); 
	for (size_t y = 0; y < H; y++) {
		for (size_t x = 0; x < W; x++) {
			workingbuf[y][x][0]=' ';
		}
	}

	for (int i = 0; i < SNOWFLAKE_COUNT; ++i) {
		snowflakes[i].x = rand() % W;
		snowflakes[i].y = rand() % H;
	}
	
	for (int i = 0; i < STAR_COUNT; ++i) {
		stars[i].x = rand() % W;
		stars[i].y = rand() % H;
	}
	for (int i = 0; i < ORNAMENT_COUNT; ++i) {
	    ornaments[i].x = 35 + rand() % 9;
	    ornaments[i].y = (H - 11) + rand() % 8;
	    ornaments[i].color = 196 + rand() % 6;
	}

}

void renderOrnaments() {
    for (int i = 0; i < ORNAMENT_COUNT; ++i) {
        if (21<workingcolorbuf[ornaments[i].y][ornaments[i].x]&&workingcolorbuf[ornaments[i].y][ornaments[i].x]<118) {
		  workingbuf[ornaments[i].y][ornaments[i].x][0] = 'O';
            workingcolorbuf[ornaments[i].y][ornaments[i].x] = ornaments[i].color;
        }
    }
}

void renderScreen() {
	for (size_t y = 0; y < H; y++) {
		for (size_t x = 0; x < W; x++) {
			printf("\x1b[38;5;%dm" "%c" RESET, screencolorbuf[y][x], screenbuf[y][x][0]);
		}
		printf("\n\r");
	}
	printf("Merry Christmas!\n\r");
}

int randomX() {
	return (rand() % (80));
}

void updateAndRenderSnow() {
	for (int i = 0; i < SNOWFLAKE_COUNT; ++i) {
		snowflakes[i].y += SNOWFLAKE_SPEED;
		if (snowflakes[i].y > H) {
			snowflakes[i].y = 0;
			snowflakes[i].x = randomX();
		}
		workingbuf[snowflakes[i].y][snowflakes[i].x][0] = '.';
		workingcolorbuf[snowflakes[i].y][snowflakes[i].x] = 231;
	}
}

void renderStars() {
	for (int i = 0; i < STAR_COUNT; ++i) {
		workingbuf[stars[i].y][stars[i].x][0] = '*';
		workingcolorbuf[stars[i].y][stars[i].x] = 55;
	}
}

void renderTree() {
	char luminanceIndex[7] = "@&%*=-.";
	char luminanceColorIndex[7] = {46, 118, 76, 40, 34, 28, 22};
	int w = 13;
	int l = H-14;
	for (size_t t = 2; t < 5; t++) {
		for (size_t i = t-1; i < (2*t); i++) {
			int lSize = (2*i)-1;
			for (size_t j =40-((lSize+1)/2); j < 39+((lSize+1)/2); j++) {
				workingbuf[l][j][0] = luminanceIndex[i-1];
				workingcolorbuf[l][j] = luminanceColorIndex[i-1];
			}
			l++;
		}
	}
	for (size_t i = H-2; i < H; i++) {
		for (size_t j = 38; j < 41; j++) {
			workingbuf[i][j][0] = '#';
			workingcolorbuf[i][j] = 52;
		}
	}
}

void renderSky() {
	char luminanceIndex[3] = "=-.";
	char luminanceColorIndex[3] = {19, 18, 17};
	int currentL = 0;
	for (size_t y = 0; y < H; y++) {
		for (size_t x = 0; x < W; x++) {
			workingbuf[y][x][0]=luminanceIndex[currentL];
			workingcolorbuf[y][x]=luminanceColorIndex[currentL];
		}
		currentL=y/(H/3);
	}
}

void swapAndClearBufs() {
	for (size_t y = 0; y < H; y++) {
		for (size_t x = 0; x < W; x++) {
			screenbuf[y][x][0]=workingbuf[y][x][0];
			screencolorbuf[y][x]=workingcolorbuf[y][x];
		}
	}
}


int main() {
	initialise();


	while (1==1) {
		renderSky();
		updateAndRenderSnow();
		renderStars();
		renderTree();
		renderOrnaments();

		swapAndClearBufs();
		clrscr();
		renderScreen();

		usleep(1000000);
	}    
}


int testColors() {
	for(size_t i = 0; i < ((GREEN_COLOR_END - GREEN_COLOR_START)/GREEN_COLOR_JUMP)+1; ++i){
		int n = 46-(i*6);
		printf("\x1b[38;5;%dm" "x1b[38;5;%dm" RESET "\n", n, n);
	}
	return 0;
}