#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include "../template.cpp"
#else
#define debug(...) 1419
#define debugArr(...) 1419
#endif
#define int long long
#define INF 1e18
const int MOD = 1e9 + 7;
#define F first
#define S second

enum class MOVES { UP, LEFT, RIGHT, DOWN };
class Game2048 {
public:
  Game2048(int _height, int _width) : height(_height), width(_width) {
    board.assign(height, vector<int>(width));
    spawnRandomly();
  }
  // check if game ended
  bool isGameFinished() {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board[i][j] == 0) {
          return false;
        }
      }
    }
    return true;
  }
  // spawnRandomly
  bool spawnRandomly() {
    if (isGameFinished())
      return false;
    int zeroCnt = 0;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board[i][j] == 0) {
          zeroCnt++;
        }
      }
    }
    int pos = rand() % zeroCnt;
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        if (board[i][j] == 0) {
          if (pos == 0) {
            board[i][j] = ((rand() % 2) + 1) * 2;
            return true;
          }
          pos--;
        }
      }
    }
    return false;
  }
  // slide a row to left
  vector<int> transformRow(vector<int> v) {
    vector<int> temp;
    for (int val : v)
      if (val != 0)
        temp.push_back(val);

    vector<int> res;
    int i = 0;
    while (i < temp.size()) {
      if (i + 1 < temp.size() && temp[i] == temp[i + 1]) {
        res.push_back(temp[i] * 2);
        i += 2;
      } else {
        res.push_back(temp[i]);
        i++;
      }
    }

    while (res.size() < v.size())
      res.push_back(0);

    return res;
  }

  // slide left
  bool slideLeft() {
    vector<vector<int>> original(board);
    for (int i = 0; i < height; i++) {
      board[i] = transformRow(board[i]);
    }
    if (original == board)
      return false;
    spawnRandomly();
    return true;
  }
  // slide right
  bool slideRight() {
    vector<vector<int>> original(board);
    for (int i = 0; i < height; i++) {
      reverse(board[i].begin(), board[i].end());
      board[i] = transformRow(board[i]);
      reverse(board[i].begin(), board[i].end());
    }
    if (original == board)
      return false;
    spawnRandomly();
    return true;
  }
  // slide up
  bool slideUp() {
    vector<vector<int>> original(board);

    for (int i = 0; i < width; i++) {
      vector<int> temp(height);
      for (int j = 0; j < height; j++) {
        temp[j] = board[j][i];
      }
      temp = transformRow(temp);
      for (int j = 0; j < height; j++) {
        board[j][i] = temp[j];
      }
    }
    if (original == board)
      return false;
    spawnRandomly();
    return true;
  }
  // slide down
  bool slideDown() {
    vector<vector<int>> original(board);

    for (int i = 0; i < width; i++) {
      vector<int> temp(height);
      for (int j = 0; j < height; j++) {
        temp[j] = board[j][i];
      }
      reverse(temp.begin(), temp.end());
      temp = transformRow(temp);
      reverse(temp.begin(), temp.end());
      for (int j = 0; j < height; j++) {
        board[j][i] = temp[j];
      }
    }
    if (original == board)
      return false;
    spawnRandomly();
    return true;
  }
  void printBoard() {
    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        cout << setw(4) << board[i][j];
      }
      cout << endl;
    }
  }
  void invalid() { cout << "Invalid Move" << endl; }

private:
  int height, width;
  vector<vector<int>> board;
};


signed main() {
  srand(time(0));
  int n, m;
  cout<<"Enter the height and width of board respectively"<<endl;
  cin >> n >> m;
  Game2048 game(n, m);
  while (!game.isGameFinished()) {
    cout<<"Enter a Move (U,R,L,D): "<<endl;
    char move;
    cin >> move;
    debug(move);
    if (move == 'U') {
      if (game.slideUp() == false)
        game.invalid();
    } else if (move == 'R') {
      if (game.slideRight() == false)
        game.invalid();
    } else if (move == 'L') {
      if (game.slideLeft() == false)
        game.invalid();
    } else if (move == 'D') {
      if (game.slideDown() == false)
        game.invalid();
    } else {
      cout << "Please Enter a valid move" << endl;
    }

    game.printBoard();
  }
  cout << "Game Over!! \nScore reached: ";
}
