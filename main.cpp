#include "ChessGame.h"

int main() {
    ChessGame game;
    game.displayBoard();

    int startX, startY, endX, endY;
    while (true) {
        if (game.isCheckmate(true)) {
            std::cout << "White is in checkmate. Black wins!" << std::endl;
            break;
        }
        if (game.isCheckmate(false)) {
            std::cout << "Black is in checkmate. White wins!" << std::endl;
            break;
        }

        std::cout << (game.getIsWhiteTurn() ? "White" : "Black") << "'s turn. Enter start (x y) and end (x y) coordinates: ";
        std::cin >> startX >> startY >> endX >> endY;
        if (game.movePiece(startX, startY, endX, endY)) {
            game.displayBoard();
        } else {
            std::cout << "Invalid move. Try again." << std::endl;
        }
    }

    return 0;
}
