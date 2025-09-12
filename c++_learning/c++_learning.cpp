#include<iostream>

#define rep(i,n) for(int i=0;i<n;i++)
#define BOARD_SIZE 8

using namespace std;

//0:- , 1:● , -1:○ 
int board[BOARD_SIZE][BOARD_SIZE] = {};
//1:● -1:○ 
int player = 1;

//盤面生成
void make_board() {
	board[3][3] = 1;
	board[4][4] = 1;
	board[3][4] = -1;
	board[4][3] = -1;
}

//盤面表示
void show_board() {
	cout << "---------------------------" << endl;
	cout << "  12345678" << endl;
	char t='a';
	rep(i, BOARD_SIZE) {
		cout << char(t + i)<<" ";
		rep(j, BOARD_SIZE) {
			int t = board[i][j];
			if (t == 0)cout << "-";
			else if (t == 1)cout << "●";
			else if (t == -1)cout << "○";
		}
		cout << endl;
	}
}

//手番表示
void show_player() {
	if (player == 1) {
		cout << "先手(●)の番です" << endl;
	}
	else {
		cout << "後手(○)の番です" << endl;
	}
}

void input_check(char* x, char* y) {
	//xが英字 yが数字になるようにする
	if (*x >= 1 && *x <= 9) {
		swap(x, y);
	}
	else {
		return;
	}
}

bool check_plc(int i, int j) {
	//盤面の範囲内かどうか
	if (i < 1 || i>9 || j < 1 || j>9)return false;

	//相手の駒を挟めるか
	for (int d_i = -1; d_i < 2; d_i++) {
		for (int d_j = -1; d_j < 2; d_j++) {
			//相手の駒が何個続くか
			int times = 1;
			//注目するマスが有効範囲内か
			if (i + d_i * times < 1 || i + d_i * times>9)break;
			if (j + d_j * times < 1 || j + d_j * times>9)break;

			//注目するマスが相手の駒だったら
			while (board[i + d_i*times][j + d_j*times] == player * -1) {
				times++;
			}
			//自分の駒で挟めていたら
			if (board[i + d_i * times][j + d_j * times] == player) {
				return true;
			}
		}
	}
	//そこには置けない
	return false;
}

void place_stn(int i, int j) {
	//挟んだ相手の駒を変更
	//相手の駒を挟めるか
	for (int d_i = -1; d_i < 2; d_i++) {
		for (int d_j = -1; d_j < 2; d_j++) {
			//相手の駒が何個続くか
			int times = 1;
			//注目するマスが有効範囲内か
			if (i + d_i * times < 1 || i + d_i * times>9)break;
			if (j + d_j * times < 1 || j + d_j * times>9)break;

			//注目するマスが相手の駒だったら
			while (board[i + d_i * times][j + d_j * times] == player * -1) {
				times++;
			}
			//自分の駒で挟めていたら
			if (board[i + d_i * times][j + d_j * times] == player) {
				rep(k, times) {
					board[i + d_i * k][j + d_j * k] = player;
				}
			}
		}
	}
	board[i][j] = player;
}

bool flag_fin() {
	rep(i, BOARD_SIZE) {
		rep(j, BOARD_SIZE) {
			//どこかに置ける
			if (check_plc(i, j))return true;
		}
	}

	//プレイヤー交代で続行可能か
	player *= -1;
	rep(i, BOARD_SIZE) {
		rep(j, BOARD_SIZE) {
			//どこかに置ける
			{
				cout << "パスしました" << endl;
				if (check_plc(i, j))return true;
			}
		}
	}
	return false;
}

void judge() {
	int bcount = 0, wcount = 0;
	rep(i, BOARD_SIZE) {
		rep(j, BOARD_SIZE) {
			if (board[i][j] == 1)wcount++;
			else if (board[i][j] == -1)bcount++;
		}
	}
	cout << "先手(●)：" << wcount << "　後手(○)：" << bcount << endl;
	if (wcount > bcount)cout << "先手の勝利です" << endl;
	else if (bcount > wcount)cout << "後手の勝利です" << endl;
	else if (wcount == bcount)cout << "引き分けです" << endl;
}


int main() {
	make_board();
	char a = 'a';
	while (flag_fin()) {
		show_board();
		show_player();
		char tx, ty;
		int x, y;
		do {
			//x行目y列目
			//英字が行　数字が列
			cout << "配置する座標を入力してください" << endl;
			cin >> tx >> ty;
			input_check(&tx, &ty);
			//数値に変換
			x = tx - 'a';
			y = ty - '1';
		} while (!check_plc(x, y));
		cout << x << "行" << y << "列目" << endl;
		place_stn(x, y);
		player *= -1;
	}
	show_board();
	judge();
	return 0;
}