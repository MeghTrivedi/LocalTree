#include "headerfile.h"

/***************************************************************************
Student Name: Megh Trivedi			Student Number:0886172  
Date: january,11th,2017                  		Course Name: cis2500
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
     1) I have read and understood the University policy on academic integrity;
     2) I have completed the Computing with Integrity Tutorial on Moodle; and
     3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
****************************************************************************/

/*Include a library*/
#include "headerfile.h"

int main(int argc, char *argv[]){
	/*variables*/
	FILE *file;
	int column = 5;
	int row = 10;
	int xHero = 1, yHero = 1;
	int xpos, ypos;
	int i = 0, x = 0, z = 0;
	int ytemp, xtemp;
	int wordLength = 0;
	/*int doorPosition;
	char doorLocation;*/
	char inputChar;
	char *line[50];
	char *rowRead, *colRead;
	char *word, *wordA, *wordB, *wordC, *wordD;
	
	printf("ENTER THE FILE DIRECTORY \n");
	scanf("%s", argv[0]); 
	
	/*file reading*/
    file = fopen(argv[0], "r");
    
	/*time*/
	srand (time(NULL));
    /*ncurses initialization */
    initscr();/*starts the screen*/
    cbreak();
    noecho();
    start_color();
	/*structs*/
	
    /*assign color value*/
    col.red = 1;
    col.white = 2;
    col.blue = 3;
    col.green = 4;
    col.yellow = 5;
    col.cyan = 6;
    /*Set a colour pair*/
    start_color();
    init_pair(col.red, COLOR_BLACK, COLOR_RED);
    init_pair(col.white, COLOR_WHITE, COLOR_BLACK);
    init_pair(col.blue, COLOR_BLUE, COLOR_BLACK);
    init_pair(col.green, COLOR_GREEN, COLOR_BLACK); 
    init_pair(col.yellow, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(col.cyan, COLOR_CYAN, COLOR_BLACK);
    
    /*2d string array of word*/
    for(x=0;x<50;x++){
        line[x] = malloc(sizeof(char)*(150));
    }/*end for, 2d string array*/

    /*read each word in the txt line of the file*/
    while(!feof(file)){
		i = i + 1;
		fgets(line[i], 150, file);		
	}/*end loop*/
	fclose(file);
	
	for(x=1;x<7;x++){
		refresh();
		/*use token to braek each string in the file*/
		rowRead = strtok(line[x], "X");
		colRead = strtok(NULL, " \n");
		
		/*assign the column and row from the file  10X10 dn2 de4 g8,7 M2,4 p4,4*/
		row = atoi(rowRead);
		column = atoi(colRead);
		
		/*draw border room and get the ypos and xpos*/
		if(x == 1){
			drawBorder(column, row, 0, 0);
			ytemp = column;
			xtemp = row;
		}else if(x == 2){
			drawBorder(column, row, 25+2, 0);
			ytemp = column;
			xtemp = row;
		}else if(x == 3){
			drawBorder(column, row, 25+2+25+2, 0);
			ytemp = column;
			xtemp = row;
		}else if(x == 4){
			drawBorder(column, row, 0, 25+2);
			ytemp = column;
			xtemp = row;
		}else if(x == 5){
			drawBorder(column, row, 25+2, 25+2);
			ytemp = column;
			xtemp = row;
		}else if(x == 6){
			drawBorder(column, row, 25+2+25+2, 25+2);
			ytemp = column;
			xtemp = row;
		}/*end if*/
		
		/*checks the info of the word from the file*/	
		
		while(z == 0){
			if(x == 1){
				word = strtok(NULL, " \n");
			}else if(x == 2){
				wordA = strtok(NULL, " \n");
			}else if(x == 3){
				wordB = strtok(NULL, " \n");
			}else if(x == 4){
				wordC = strtok(NULL, " \n");
			}else if(x == 5){
				wordD = strtok(NULL, " \n");
			}
			
			if(word == NULL){
				z = 5;
			}else{	
				if(x == 1){
					objects(word, column, row, 0, 0);
				}else if(x == 2){
					objects(wordA, column, row, 0, xtemp+5);
				}else if(x == 3){
					objects(wordB, column, row, 0, (xtemp+5)*2);
				}else if(x == 4){
					objects(wordC, column, row, ytemp+4, (xtemp+5)*2);
				}else if(x == 5){
					objects(wordD, column, row, (ytemp+4)*2, (xtemp+5)*2);
				}
				
				if(word[0] == 'h'){
					yHero = atoi(&word[3]);
					xHero = atoi(&word[1]);
					attron(COLOR_PAIR(col.white));
					move(yHero, xHero);
					printw("h");
				}else if(word[0] == 'M'){
					ypos = atoi(&word[3]);
					xpos = atoi(&word[1]);
					attron(COLOR_PAIR(col.white));
					move(ypos, xpos);
					printw("M");
				}/*end if*/		
			}/*end if*/
		}/*end while loop*/
	}/*end for loop*/

	/*testing*/
	move(50,50);
	printw("%d, %d, %d, %s", column, row, wordLength, word);
	
	/*hero
	getyx(stdscr, yHero,xHero);*/
	move(yHero,xHero);

	/*start looping the program to play the game*/
    inputChar = getch();
    while(inputChar !='q'){
        userControl(inputChar);
        inputChar = getch();
    }/*end of while loop*/
    
    refresh();
	/*getch();*/
	endwin();
	return(0);
}/*end main*/

void drawBorder(int column, int row, int ypos, int xpos){
    /*variable for counter*/
    int y, x;
    /*set color*/
    attron(COLOR_PAIR(1));
    /*draw the border with x*/
    for (y = 0; y < column+2; y++){
		move(y+ypos, 0+xpos);
        printw("X");
    }/*end for*/
    for (x = 0; x < row; x++){
		move(0+ypos, x+1+xpos);
		printw("X");
    }/*end for*/
    for (y = 0; y < column+2; y++){
		move(y+ypos, row+1+xpos);
		printw("X");	
    }/*end for*/
    for (x = 0; x < row; x++){
		move(column+1+ypos, x+1+xpos);
		printw("X");
    }/*end for*/	
}/*end Border*/

#include "headerfile.h"

void objects(char *word, int column, int row, int y, int x){
	/*declare variables*/
	int doorPosition;
	char doorLocation;
	int ypos = 0, xpos = 0;
	/*int yHero = 0, xHero = 0;*/
	
	/*doorway*/
	attron(COLOR_PAIR(col.white));
	if(word[0] == 'd'){	
		doorLocation = word[1];
		if(doorLocation == 'e'){ 
			doorPosition = atoi(&word[2]);		
			move(doorPosition+y, row+1+x);
			printw("d");
		}else if(doorLocation == 'w'){
			doorPosition = atoi(&word[2]);		
			move(doorPosition+y, 0+x);
			printw("d");	
		}else if(doorLocation == 'n'){
			doorPosition = atoi(&word[2]);		
			move(0+y , doorPosition+x);
			printw("d");
		}else if(doorLocation == 's'){
			doorPosition = atoi(&word[2]);		
			move(column+1+y ,doorPosition+x);
			printw("d");
		}/*end else if*/
	}else if(word[0] == 's'){
		ypos = atoi(&word[3]);
		xpos = atoi(&word[1]);
		attron(COLOR_PAIR(col.white));
		move(ypos+y, xpos+x);
		printw("s");
	}else if(word[0] == 'g'){
		ypos = atoi(&word[3]);
		xpos = atoi(&word[1]);
		attron(COLOR_PAIR(col.yellow));
		move(ypos+y, xpos+x);
		printw("g");
	}else if(word[0] == 'm'){
		ypos = atoi(&word[3]);
		xpos = atoi(&word[1]);
		attron(COLOR_PAIR(col.blue));
		move(ypos+y, xpos+x);
		printw("m");
	}else if(word[0] == 'p'){
		ypos = atoi(&word[3]);
		xpos = atoi(&word[1]);
		attron(COLOR_PAIR(col.green));
		move(ypos+y, xpos+x);
		printw("p");
	}else if(word[0] == 'w'){
		ypos = atoi(&word[3]);
		xpos = atoi(&word[1]);
		attron(COLOR_PAIR(col.cyan));
		move(ypos+y, xpos+x);
		printw("w");
	}/*end else if*/
}/*end doorway*/
