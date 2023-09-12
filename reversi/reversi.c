#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

void printBoard(char board[][26], int n) {
  for (int i = 0; i < n; i++) {
    if (i == 0) {
      printf("  ");
      for (int m = 0; m < n; m++) {
        printf("%c", 'a' + m);
      }
      printf("\n");
    }
    printf("%c ", 'a' + i);
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}
bool positionInBounds(int n, int row, int col) {
  return row >= 0 && row <= n - 1 && col >= 0 && col <= n - 1;
}
int scoreOf(char board[][26], int size, char colour){
  int count = 0;
  for(int i = 0; i<size*size; i++){
    if(board[i/size][i%size]==colour){
      count++;
    }
  }
  return count;
}
void updateRowCol(int* row, int* col, int deltarow, int deltacol) {
  *row += deltarow;
  *col += deltacol;
}
void initializeBoard(int size, char board[][26]) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if ((i == (size / 2) - 1 && j == (size / 2) - 1) ||
          (i == (size / 2) && j == (size / 2))) {
        board[i][j] = 'W';
      } else if ((i == (size / 2) - 1 && j == (size / 2)) ||
                 (i == (size / 2) && j == (size / 2) - 1)) {
        board[i][j] = 'B';
      } else {
        board[i][j] = 'U';
      }
    }
  }
  printBoard(board, size);
}
bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
  char colourCheck = 'B';
  bool done = false;
  int prevrow,prevcol;
  if (colour == 'B') {
    colourCheck = 'W';
  }
  if(!positionInBounds(n,row,col)){
    return false;
  }
  for (int i = 0; positionInBounds(n, row, col); i++) {
    prevrow=row,prevcol=col;
    updateRowCol(&row, &col, deltaRow, deltaCol);
    if(prevrow == row && prevcol == col){
      return false;
    }
    if (positionInBounds(n, row, col)) {
      
      if (board[row][col] == colourCheck) {
        done = true;
      } else if (board[row][col] == 'U' && done) {
        return false;
      } else if (board[row][col] == colour && done) {
        return true;
      } else {
        return false;
      }
    }
    else{
      return false;
    }
  }
  return false;
}
int getAllMoves(char board[][26], int size, char colour, int mover[64], int movec[64]) {
  int totalmoves = 0;
  int emptyCells = 0;
  for (int i = 0; i < size * size; i++) {
    if (board[i / size][i % size] == 'U') {
      emptyCells++;
    }
  }
  if (emptyCells == 0) {
    return 0;
  }
  for (int x = 0; x < size * size; x++) {
    bool done = false;
    if (board[x / size][x % size] == 'U') {
      for (int r = 1; r > -2; r--) {
        for (int c = -1; c < 2; c++) {
          if (r == 0 && c == 0) {
            continue;
          }
          if (checkLegalInDirection(board, size, x / size, x % size, colour, r, c)) {
            mover[totalmoves] = x / size;
            movec[totalmoves] = x % size;
            totalmoves++;
            done = true;
            break;
          }
        }
        if (done) {
          break;
        }
      }
    }
  }
  return totalmoves;
}
int displayAllMoves(char board[][26], int size,char colour) {
  int cr = 0, cc, totalmoves = 0;
    for(; cr<size; cr++){
        for(cc=0; cc<size; cc++){
            bool done = false;
            for (int r = 1; r > -2; r--) {
                for (int c = -1; c < 2; c++) {
                    if (r == 0 && c == 0) {
                        continue;
                    }
                    if(checkLegalInDirection(board, size, cr, cc, colour, r, c)&&board[cr][cc]=='U') {
                        totalmoves++; 
                        done = true;
                        break;
                    }
                }
                if(done){
                    break;
                }     
            }
        }
    }
    return totalmoves;
}
void fill(char board[][26], int size, char colour, int row, int col){
  int flipped = 0;
   for (int r = 1; r > -2; r--) {
    for (int c = -1; c < 2; c++) {
      int cr = row, cc = col;
      if (checkLegalInDirection(board, size, cr, cc, colour, r, c)) {
        updateRowCol(&cr, &cc, r, c);
        while (positionInBounds(size, cr, cc) && board[cr][cc] != colour) {
          board[cr][cc] = colour;
          flipped++;
          updateRowCol(&cr, &cc, r, c);
        }
        board[row][col] = colour;
      }
    }
  }
   return;
}
int makeMoveFill(char board[][26], int size, char colour, int row, int col, bool *filled) {
  int cr = row, cc = col, flipped = 0;
  for (int r = 1; r > -2; r--) {
    for (int c = -1; c < 2; c++) {
      cr = row, cc = col;
      if (checkLegalInDirection(board, size, cr, cc, colour, r, c)) {

        updateRowCol(&cr, &cc, r, c);
        while (positionInBounds(size, cr, cc) && board[cr][cc] != colour) {
          board[cr][cc] = colour;
          flipped++;
          updateRowCol(&cr, &cc, r, c);
        }
        board[row][col] = colour;
        *filled = true;
      }
    }
  }
  return flipped;
}
int numFlipped(char board[][26], int size, char colour, int row, int col) {
  int cr = row, cc = col, flipped = 0;
  for (int r = 1; r > -2; r--) {
    for (int c = -1; c < 2; c++) {
      cr = row, cc = col;
      if (checkLegalInDirection(board, size, cr, cc, colour, r, c)) {
        updateRowCol(&cr, &cc, r, c);
        while (positionInBounds(size, cr, cc) && board[cr][cc] != colour) {
          flipped++;
          updateRowCol(&cr, &cc, r, c);
        }
      }
    }
  }
  return flipped;
}
int numFrontier(char board[][26], char colour, int row, int col){
  int frontier = 0;
  if(board[row][col] == colour){
    for (int r = 1; r > -2; r--) {
      for (int c = -1; c < 2; c++) {
        if(board[row+r][col+c]=='U'){
          frontier++;
        }
      }
    }
  }
  return frontier;
}
bool isStable(char board[][26], char colour, int row, int col){
    if (row == 0 || row == 7 || col == 0 || col == 7) {
        return true;
    }
    if ((row == 1 || row == 6) && (col == 1 || col == 6)) {
        return 1;
    }
    int i;
    for (i = 0; i < 8; i++) {
        if (board[i][col] != board[row][col] && i != row) {
            break;
        }
    }
    if (i == 8) {
        return 1;
    }
    for (i = 0; i < 8; i++) {
        if (board[row][i] != board[row][col] && i != col) {
            break;
        }
    }
    if (i == 8) {
        return 1;
    }
    // Check if disk is in a stable diagonal
    if ((row == col || row + col == 8 - 1) && (row > 0 && row < 8 - 1 && col > 0 && col < 8 - 1)) {
        int i, j;
        for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] != board[row][col]) {
                break;
            }
        }
        if (i < 0 || j < 0) {
            return 1;
        }
        for (i = row + 1, j = col + 1; i < 8 && j < 8; i++, j++) {
            if (board[i][j] != board[row][col]) {
                break;
            }
        }
        if (i == 8 || j == 8) {
            return 1;
        }
        for (i = row - 1, j = col + 1; i >= 0 && j < 8; i--, j++) {
            if (board[i][j] != board[row][col]) {
                break;
            }
        }
        if (i < 0 || j == 8) {
            return 1;
        }
        for (i = row + 1, j = col - 1; i < 8 && j >= 0; i++, j--) {
            if (board[i][j] != board[row][col]) {
                break;
            }
        }
        if (i == 8 || j < 0) {
            return 1;
        }
    }
    return 0;
}

int StaticScore(char board[][26], char colour){
  int computerMoves = 0, playerMoves = 0, computerFrontier = 0, playerFrontier =  0, mobility = 0, frontier = 0, parity = 0, computerStability = 0, playerStability = 0, stability = 0;
  char otherColour = 'B';
  if(colour == 'B'){
    otherColour = 'W';
  }
	int weights[8][8]= {{1000, -18, 8, 6, 6, 8, -18, 1000},
                      {-18, -24, -14, -12, -12, -14, -24, -18},
                      {8, -14, 15, 15, 15, 15, -14, 8},
                      {6, -12, 15, 10, 10, 15, -12, 6},
                      {6, -12, 15, 10, 10, 15, -12, 6},
                      {8, -14, 15, 15, 15, 15, -14, 8},
                      {-18, -24, -14, -12, -12, -14, -24, -18},
                      {1000, -18, 8, 6, 6, 8, -18, 1000}
                    };
    for(int i = 0; i < 8; i++){
      for(int j = 0; j<8; j++){
        if(board[i][j]==colour){
          parity += weights[i][j];
          computerFrontier +=numFrontier(board,colour,i,j);
        }
        if(board[i][j]==otherColour){
          parity -= weights[i][j];
          playerFrontier +=numFrontier(board,otherColour,i,j);
        }
      }
    }
  if(computerFrontier>playerFrontier){
		frontier = 100*(computerFrontier/(computerFrontier + playerFrontier));
  }
	else if(computerMoves<playerMoves){
		frontier = 100*(-computerFrontier/(computerFrontier + playerFrontier));
  }

  computerMoves = displayAllMoves(board,8,colour);
	playerMoves = displayAllMoves(board,8,otherColour); 
	if(computerMoves>playerMoves){
		mobility = 100*(computerMoves/(computerMoves + playerMoves));
  }
	else if(computerMoves<playerMoves){
		mobility = 100*(-computerMoves/(computerMoves + playerMoves));
  }
  

	int score = (10 * parity) + (100 * mobility) + (30*frontier) + (50*stability);
  return score;
}

int miniMax(char board[][26], bool AI, char computerColour, int depth, int alpha, int beta, clock_t start){
  int score;
  int bestVal = 1000000;
  if(depth == 0||scoreOf(board, 8,'U')==0||((clock() - start) * 1000 / CLOCKS_PER_SEC)>2000){
    printf("depth %d\n", depth);
    return StaticScore(board,computerColour);
  }
  int allRows[64];
  int allCols[64];
  int numOfMoves = getAllMoves(board,8,computerColour,allRows,allCols);
  /*for(int i = 0; i<numOfMoves; i++){
    printf("row: %d col: %d\n",allRows[i],allCols[i]);
  }*/
  if(allRows[0] == -1 && allCols[0] == -1){
    return miniMax(board, !AI, computerColour, depth, alpha, beta, start);
  }
  
  if(AI){
    bestVal = -bestVal;
    for(int i = 0; i<numOfMoves; i++){
      char boardCopy[26][26];
      memcpy(boardCopy, board, 26*26*sizeof(char));
      fill(boardCopy, 8, computerColour, allRows[i], allCols[i]);
      score = miniMax(boardCopy, !AI, computerColour, depth-1, alpha, beta, start);
      if(score>bestVal){
        bestVal = score;
      }
      if(bestVal>alpha){
        alpha = bestVal;
      }
      if(alpha>=beta){
        break;
      }
    }
    return score;
  } else if(!AI){
    for(int i = 0; i<numOfMoves; i++){
      char boardCopy[26][26];
      memcpy(boardCopy,board, 26*26*sizeof(char));
      fill(boardCopy, 8, computerColour, allRows[i], allCols[i]);
      score = miniMax(boardCopy, !AI, computerColour, depth-1, alpha, beta, start);
      if(score<bestVal){
        bestVal = score;
      }
      if(beta>score){
        beta = score;
      }
      if(alpha>=beta){
        break;
      }
    }
    return score;
  }
}
int makeMove(char board[][26], int n, char color, int *row, int *col){
  clock_t start = clock();
  int allRows[64];
  int allCols[64];
  int bestVal = -1000000, tempVal;
  int numMoves = getAllMoves(board, 8, color, allRows, allCols);
  if(numMoves>0){
    for(int i = 0; i<numMoves; i++){
      char testMove[26][26];
      memcpy(testMove, board, 26*26*sizeof(char));
      fill(testMove, 8, color, allRows[i], allCols[i]);
      tempVal = miniMax(testMove, true, color, 100, -1000000, 1000000, start);
      if(tempVal>bestVal){
        *row = allRows[i];
        *col = allCols[i];
        bestVal = tempVal;
      }
      if (((clock() - start) * 1000 / CLOCKS_PER_SEC)>2000) {
            break;
        }
    }
  }
  return 0;
}

int main() {
  srand(time(NULL));
  int computerWins = 0, overTimeCount = 0, games = 0;
  for(int i = 0; i<1000; i++){
    char board[26][26], colour, row, col, computerColour, playerColour='W';
    int size = 8, computerMoves=0, zero, totalmoves = 0, playerScore = 0, computerScore = 0, cRow, cCol, bools;
    bool playermove = false;
    /*printf("Enter the board dimension: ");
    scanf("%d", &size);
    */
   /* printf("Computer plays (B/W): ");
    scanf(" %c", &computerColour);

    if(computerColour=='W'){
      playerColour='B';
      playermove = true;
    }*/
    bools = rand()%2;
    if(bools == 0){
      computerColour = 'W';
      playerColour = 'B';
      playermove = true;
    }else{
      computerColour = 'B';
      playerColour = 'W';
      playermove = false;
    }
    initializeBoard(size, board);
      printf("game: %d", games);
      games++;
      while(1){
        bool filled = false;
        int playerRow[64], playerCol[64], numOfMoves=0, moveindex=0;
        if(playermove){
          totalmoves = displayAllMoves(board, size, playerColour);
          /*printf("Enter move for colour %c (RowCol): ",playerColour);
          scanf(" %c%c", &row, &col);*/
          numOfMoves= getAllMoves(board, 8, playerColour, playerRow, playerCol);
          if(numOfMoves>0){
            moveindex = rand()%numOfMoves;
          }
          row = 'a'+playerRow[moveindex];
          col = 'a'+playerCol[moveindex];
          if (positionInBounds(size, row - 'a', col - 'a') && board[row - 'a'][col - 'a']=='U'&&totalmoves>0) {
            playerScore += makeMoveFill(board, size, playerColour, row - 'a', col - 'a',&filled);
          }
          if(!filled&&totalmoves!=0) {
            printf("Invalid move.\n");
            printf("%c player wins.",computerColour);
            computerWins++;
            break;
          }
          printBoard(board, size);
          playermove = false;
        }
        else{
          clock_t tic = clock();
          zero = makeMove(board,size,computerColour,&cRow,&cCol);
          clock_t toc = clock();
          printf("\nElapsed: %f seconds\n\n", (double)(toc - tic) / CLOCKS_PER_SEC);
            if ((double)(toc - tic) / CLOCKS_PER_SEC > 1) {
            overTimeCount++;
          }
          if((double)(toc - tic) / CLOCKS_PER_SEC >10){
            break;
          }
          computerMoves=makeMoveFill(board, size, computerColour, cRow, cCol, &filled);
          if(computerMoves!=0){
            printf("Computer places %c at %c%c.\n", computerColour, 'a'+cRow,'a'+cCol);
            printBoard(board, size);
          }
          else{
            printf("%c player has no valid move.\n",computerColour);
          }
          playermove = true;
        }
        if(scoreOf(board,size,'U')==0|| (computerMoves == 0 && totalmoves==0)){
            computerScore = scoreOf(board,size,computerColour);
            playerScore = scoreOf(board,size,playerColour);
            if(playerScore>computerScore){
              printf("%c player wins.",playerColour);
            }
            else if(computerScore>playerScore){
              printf("%c player wins.",computerColour);
              computerWins++;
            }
            else{
              printf("tie");
            }
            break;
          } 
          else if(displayAllMoves(board, size, playerColour)==0){
            printf("%c player has no valid move.\n",playerColour);
          }
      }
  }
  printf("computer won %d out of %d games, overtime %d times",computerWins,games,overTimeCount);
  return 0;
}