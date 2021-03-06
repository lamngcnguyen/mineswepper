#include <iostream> 
#include <stdlib.h>
#include <time.h>
#include <string.h>
using namespace std;

char mines_board[10][10]; //board de xem min
char play_board[10][10]; //board de choi cmm di
int m, n; //coordinate
char flag[2]; //place flag keyword
char unflag;//remove flag keyword
int mines_number; 

int generate_mines_number(int mines_number) {
	mines_number=rand()%20+10;
	return mines_number;	
} 

void generate_random_mines(int mines_number) {
	int m,n; //coordinate for generating mines
	int temp=0; 
	do {
		m=rand()%10; n=rand()%10;
		mines_board[m][n]=42;
		temp++;
	} while (temp<mines_number);
}
void generate_play_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			play_board[i][j]='-';
		}
	}
}
void generate_mines_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			mines_board[i][j]='-';
		}
	}
}
void display_play_board() {
	int i=0;
	while (i<10) {
		for (int j=	0; j<10; j++) {
			cout << play_board[i][j] << " ";
		}	
		cout << endl;
		i++;
	}
}
void display_mines_board() {
	int i=0;
	while (i<10) {
		for (int j=	0; j<10; j++) {
			cout << mines_board[i][j] << " ";
		}	
		cout << endl;
		i++;
	}
}

int surround_mines(int m, int n) {
	int surround_mines_count=0;
	if (mines_board[m+1][n]=='*'&&mines_board[m+1][n]!=' ') surround_mines_count++;
	if (mines_board[m+1][n+1]=='*'&&mines_board[m+1][n+1]!=' ') surround_mines_count++;
	if (mines_board[m+1][n-1]=='*'&&mines_board[m+1][n-1]!=' ') surround_mines_count++;
	if (mines_board[m][n+1]=='*'&&mines_board[m][n+1]!=' ') surround_mines_count++;
	if (mines_board[m][n-1]=='*'&&mines_board[m][n-1]!=' ') surround_mines_count++;
	if (mines_board[m-1][n]=='*'&&mines_board[m-1][n]!=' ') surround_mines_count++;
	if (mines_board[m-1][n+1]=='*'&&mines_board[m-1][n+1]!=' ') surround_mines_count++;
	if (mines_board[m-1][n-1]=='*'&&mines_board[m-1][n-1]!=' ') surround_mines_count++;
	return surround_mines_count;
}

int mines_check(int m, int n) {
	if (mines_board[m][n]==42) return 1;
	else return 0; 
}

void player_dont_hit_mines(int m, int n) {
	int a=surround_mines(m, n);
	play_board[m][n]=a+48;
}

void mines_position_check() { // for debugging only
	int count=0;
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (mines_board[i][j]=='*') {cout << "mine[" << count << "]: (" << i << ";" << j << ")" << endl;
			count++;}
		}
	}
}

void flag_placing(int m, int n) {
	play_board[m][n]='F';
}

void expand(int m, int n) {
	
}
void end_condition_play_board() {
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
			if (mines_board[i][j]=='*') play_board[i][j]='*';
		}
	}
}
int main() {
	srand(time(0));
	generate_play_board();
	generate_mines_board();
	int a=generate_mines_number(mines_number);
	int block_number = 100 - a; //so o trong
	int block_count = 0; // bo dem o trong da dc mo
	int mines_count = 0; // bo dem so min da dc cam co
	generate_random_mines(
	a);
	display_play_board();
	cout << endl;
	display_mines_board();	
	//mines_position_check();
	for (;;) {
		cout<< "Nhap toa do: " << endl;
		cin >> m >> n >> flag;
		if (strcmp(flag, "F")==0) {
			flag_placing(m,n);
			mines_count++;
			display_play_board(); cout << endl;
		}
		else if (strcmp(flag, "NF")==0){
		if (mines_check(m,n)==1) {
			end_condition_play_board(); cout << endl;
			display_play_board(); cout << endl;
			cout << "Too bad :( !! Game Over!!" << endl;
			return 0;
		}
		else {
			if (block_count == block_number && mines_number==a) {
				end_condition_play_board(); cout << endl;
				display_play_board(); cout << endl;
				cout << "Congratulation! You win :))))" << endl;;
				cout << "Nhap Y de thoat: ";
				char status;
				cin >> status;
				if (status=='Y'||status=='y') return 0;
			}
			player_dont_hit_mines(m,n);
			block_count++;
			display_play_board();
		}
	}
	} 
	return  0;
}
