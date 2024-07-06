#include "ChessGame.h"

// Pawn의 이동 규칙 구현
bool Pawn::isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) {
    int direction = isWhite ? 1 : -1;
    if (startX == endX && board[endX][endY] == nullptr) {
        if (endY - startY == direction) {
            return true;
        }
        if ((isWhite && startY == 1 || !isWhite && startY == 6) && endY - startY == 2 * direction) {
            return true;
        }
    } else if (abs(startX - endX) == 1 && endY - startY == direction && board[endX][endY] != nullptr && board[endX][endY]->isWhite != isWhite) {
        return true;
    }
    return false;
}

// Rook의 이동 규칙 구현
bool Rook::isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) {
    if (startX == endX || startY == endY) {
        int xStep = startX == endX ? 0 : (endX - startX) / abs(endX - startX);
        int yStep = startY == endY ? 0 : (endY - startY) / abs(endY - startY);
        int x = startX + xStep;
        int y = startY + yStep;
        while (x != endX || y != endY) {
            if (board[x][y] != nullptr) return false;
            x += xStep;
            y += yStep;
        }
        return board[endX][endY] == nullptr || board[endX][endY]->isWhite != isWhite;
    }
    return false;
}

// Knight의 이동 규칙 구현
bool Knight::isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    return dx * dy == 2 && (board[endX][endY] == nullptr || board[endX][endY]->isWhite != isWhite);
}

// Bishop의 이동 규칙 구현
bool Bishop::isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) {
    if (abs(startX - endX) == abs(startY - endY)) {
        int xStep = (endX - startX) / abs(endX - startX);
        int yStep = (endY - startY) / abs(endY - startY);
        int x = startX + xStep;
        int y = startY + yStep;
        while (x != endX || y != endY) {
            if (board[x][y] != nullptr) return false;
            x += xStep;
            y += yStep;
        }
        return board[endX][endY] == nullptr || board[endX][endY]->isWhite != isWhite;
    }
    return false;
}

// Queen의 이동 규칙 구현
bool Queen::isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) {
    return Rook(isWhite).isValidMove(startX, startY, endX, endY, board) || Bishop(isWhite).isValidMove(startX, startY, endX, endY, board);
}

// King의 이동 규칙 구현
bool King::isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) {
    int dx = abs(startX - endX);
    int dy = abs(startY - endY);
    return dx <= 1 && dy <= 1 && (board[endX][endY] == nullptr || board[endX][endY]->isWhite != isWhite);
}

// ChessGame 클래스의 생성자
ChessGame::ChessGame() : isWhiteTurn(true) {
    initializeBoard();
}

// ChessGame 클래스의 소멸자
ChessGame::~ChessGame() {
    for (auto& row : board) {
        for (auto& piece : row) {
            delete piece;
        }
    }
}

void ChessGame::initializeBoard() {
    board.resize(8, std::vector<Piece*>(8, nullptr));
    // 체스 말 초기화
    for (int i = 0; i < 8; ++i) {
        board[1][i] = new Pawn(true);  // 백 폰
        board[6][i] = new Pawn(false); // 흑 폰
    }
    board[0][0] = board[0][7] = new Rook(true);
    board[7][0] = board[7][7] = new Rook(false);
    board[0][1] = board[0][6] = new Knight(true);
    board[7][1] = board[7][6] = new Knight(false);
    board[0][2] = board[0][5] = new Bishop(true);
    board[7][2] = board[7][5] = new Bishop(false);
    board[0][3] = new Queen(true);
    board[7][3] = new Queen(false);
    board[0][4] = new King(true);
    board[7][4] = new King(false);
}

void ChessGame::displayBoard() {
    for (const auto& row : board) {
        for (const auto& piece : row) {
            if (piece) {
                std::cout << piece->symbol << ' ';
            } else {
                std::cout << ". ";
            }
        }
        std::cout << std::endl;
    }
}

bool ChessGame::movePiece(int startX, int startY, int endX, int endY) {
    Piece* piece = board[startX][startY];
    if (piece && piece->isWhite == isWhiteTurn && piece->isValidMove(startX, startY, endX, endY, board)) {
        if (board[endX][endY]) delete board[endX][endY];
        board[endX][endY] = piece;
        board[startX][startY] = nullptr;
        isWhiteTurn = !isWhiteTurn;
        return true;
    }
    return false;
}

bool ChessGame::isInCheck(bool isWhite) {
    int kingX, kingY;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->symbol == (isWhite ? 'K' : 'k')) {
                kingX = i;
                kingY = j;
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] && board[i][j]->isWhite != isWhite && board[i][j]->isValidMove(i, j, kingX, kingY, board)) {
                return true;
            }
        }
    }
    return false;
}

bool ChessGame::isCheckmate(bool isWhite) {
    if (!isInCheck(isWhite)) return false;
    for (int startX = 0; startX < 8; ++startX) {
        for (int startY = 0; startY < 8; ++startY) {
            if (board[startX][startY] && board[startX][startY]->isWhite == isWhite) {
                for (int endX = 0; endX < 8; ++endX) {
                    for (int endY = 0; endY < 8; ++endY) {
                        Piece* capturedPiece = board[endX][endY];
                        if (movePiece(startX, startY, endX, endY)) {
                            bool check = isInCheck(isWhite);
                            board[startX][startY] = board[endX][endY];
                            board[endX][endY] = capturedPiece;
                            if (capturedPiece) delete capturedPiece;
                            if (!check) return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool ChessGame::getIsWhiteTurn() const {
    return isWhiteTurn;
}
