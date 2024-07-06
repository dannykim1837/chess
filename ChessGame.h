#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <iostream>
#include <vector>
#include <string>

class Piece {
public:
    char symbol;
    bool isWhite;

    Piece(char s, bool isW) : symbol(s), isWhite(isW) {}
    virtual ~Piece() {}

    virtual bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) = 0;
};

class Pawn : public Piece {
public:
    Pawn(bool isW) : Piece(isW ? 'P' : 'p', isW) {}

    bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) override;
};

class Rook : public Piece {
public:
    Rook(bool isW) : Piece(isW ? 'R' : 'r', isW) {}

    bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) override;
};

class Knight : public Piece {
public:
    Knight(bool isW) : Piece(isW ? 'N' : 'n', isW) {}

    bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) override;
};

class Bishop : public Piece {
public:
    Bishop(bool isW) : Piece(isW ? 'B' : 'b', isW) {}

    bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) override;
};

class Queen : public Piece {
public:
    Queen(bool isW) : Piece(isW ? 'Q' : 'q', isW) {}

    bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) override;
};

class King : public Piece {
public:
    King(bool isW) : Piece(isW ? 'K' : 'k', isW) {}

    bool isValidMove(int startX, int startY, int endX, int endY, std::vector<std::vector<Piece*>>& board) override;
};

class ChessGame {
private:
    std::vector<std::vector<Piece*>> board;
    bool isWhiteTurn;

public:
    ChessGame();
    ~ChessGame();

    void initializeBoard();
    void displayBoard();
    bool movePiece(int startX, int startY, int endX, int endY);
    bool isInCheck(bool isWhite);
    bool isCheckmate(bool isWhite);
    bool getIsWhiteTurn() const;
};

#endif
