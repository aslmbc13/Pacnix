#ifndef __PACNIX_H
#define __PACNIX_H

#include "asprite.h"

#define DOWN 0
#define RIGHT 1
#define UP 2
#define LEFT 3

#define DOWN_ARROW 0x50
#define RIGHT_ARROW 0x4D
#define UP_ARROW 0x48
#define LEFT_ARROW 0x4B

typedef struct {
	AnimSprite *img;
	int direction;	// 0 - down, 1 - right, 2 - up, 3 - left
	int desired_direction; // same as previous. Indicates the direction the
						   // user wants pacman to go. It only goes that direction
						   // if there are no obstacles
	int mode;	// 0 - normal, 1 - powered (has eaten Energizer)
} Pacman;

int fps_tick();

Pacman * pacman_init(int xi, int yi, int speed);
void pacman_rotate_scan(Pacman * pacman, unsigned long scan_code);
void pacman_rotate(Pacman * pacman, int direction);
void pacman_read_key(Pacman * pacman, unsigned long scan_code);
void pacman_try_rotate(Pacman * pacman);
void pacman_move_tick(Pacman * pacman);
int pacman_check_surroundings(Pacman * pacman);

char ** pacman_maps(int direction);
char ** pacman_right_maps();
char ** pacman_left_maps();
char ** pacman_up_maps();
char ** pacman_down_maps();




typedef struct {
	AnimSprite *img;
	int direction;	// 0 - down, 1 - right, 2 - up, 3 - left
	int mode;	// 0 - random, 1 - chase, 2 - user controlled
	int color;	// 0 - orange, 1 - red, 2 - blue, 3 - pink
} Ghost;

Ghost * ghost_init(int xi, int yi, int speed, int color, int mode);
void ghost_rotate(Ghost * ghost, int direction);
//void ghost_dir_map(int color, int direction);







char *pixel(char* map, int width, int heigth, int x, int y);


void pacnix_start();
void interrupts();


#endif /*__PACNIX_H */
