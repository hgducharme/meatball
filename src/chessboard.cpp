#include "chessboard.h"

#include "exceptions.h"

File Chessboard::squareToFile(const int square)
{
   /*
   Let n be the square's rank [0, 8]
   A file squares are multiples of 8
   B file squares are multiples of 8n + 1
   ...
   H file squares are multiples of 8n + 7
   Therefore, file = square % 8
   */
   return static_cast<File>(square % 8);
}

Rank Chessboard::squareToRank(const int square)
{
   /*
   Let n be the square's file [0, 8]
   Rank 0 squares are in the range [0, 7] (less than 8*1)
   Rank 1 squares are in the range [8, 15] (between 8*1 and 8*2)
   ...
   Rank 8 squares are in the range [56, 63] (between 8*7 and 8*8)
   Therefore, rank = floor(square / 8)
   Since integer division in C++ truncates towards zero, (square / 8) will produce the same result.
   */
   return static_cast<Rank>(square/8);
}

Chessboard::Chessboard()
{
    // Initialize the bitboards for each piece type
    pieceBitboards_[PieceType::PAWN].setBoard(constants::DEFAULT_PAWN_STRUCTURE);
    pieceBitboards_[PieceType::KNIGHT].setBoard(constants::DEFAULT_KNIGHT_STRUCTURE);
    pieceBitboards_[PieceType::BISHOP].setBoard(constants::DEFAULT_BISHOP_STRUCTURE);
    pieceBitboards_[PieceType::ROOK].setBoard(constants::DEFAULT_ROOK_STRUCTURE);
    pieceBitboards_[PieceType::QUEEN].setBoard(constants::DEFAULT_QUEEN_STRUCTURE);
    pieceBitboards_[PieceType::KING].setBoard(constants::DEFAULT_KING_STRUCTURE);

    // Initialize the white and black bitboards
    colorBitboards_[Color::WHITE] = constants::DEFAULT_WHITE_OCCUPIED;
    colorBitboards_[Color::BLACK] = constants::DEFAULT_BLACK_OCCUPIED;

    // Initialize castle rights
    castleRights[Color::WHITE] = CastleRights::KING_AND_QUEEN_SIDE;
    castleRights[Color::BLACK] = CastleRights::KING_AND_QUEEN_SIDE;
    previousCastleRightsState = CastleRights::KING_AND_QUEEN_SIDE;
}

const Bitboard Chessboard::getOccupiedSquares() const
{
    return getBitboard(Color::WHITE) | getBitboard(Color::BLACK);
}

const Bitboard & Chessboard::getBitboard(const PieceType piece) const
{
    return pieceBitboards_[piece];
}

const Bitboard & Chessboard::getBitboard(const Color color) const
{
    return colorBitboards_[color];
}

Bitboard Chessboard::getBitboard(const Color color, const PieceType piece) const
{
    return pieceBitboards_[piece] & colorBitboards_[color];
}

void Chessboard::applyMove(const Move & move)
{
    // Store the active player's castle rights state in case this move is later undone,
    // then we can quickly restore the castle rights back to this player
    previousCastleRightsState = castleRights[move.color];

    updateBitboards(move.color, move.piece, move.startSquare, move.endSquare);
    updateCastleRights(move);
    moveHistory.push_back(move);
    toggleActivePlayer();
}

void Chessboard::raiseExceptionIfSquareIsOccupied(const Square square)
{
    if (squareIsOccupied(square))
    {
        throw exceptions::SquareAlreadyOccupied("Cannot add piece to " + utils::squareToString(square) + ". The square is already occupied.");
    }
}

bool Chessboard::squareIsOccupied(const Square square)
{
    return static_cast<bool>(getOccupiedSquares() & Bitboard(square));
}

void Chessboard::updateCastleRights(const Move & move)
{
    if (castleRights[move.color] == CastleRights::NONE)
    {
        return;
    }
    else if (move.piece == PieceType::KING)
    {
        castleRights[move.color] = CastleRights::NONE;
    }
    else if (move.piece == PieceType::ROOK)
    {
        Square queenSideRookStartingSquare = Square::a1;
        Square kingSideRookStartingSquare = Square::h1;

        if (move.color == Color::BLACK)
        {
            queenSideRookStartingSquare = Square::a8;
            kingSideRookStartingSquare = Square::h8;
        }

        const Bitboard activePlayerRookBitboard = getBitboard(move.color, PieceType::ROOK);
        const bool queenSideRookHasMoved = (activePlayerRookBitboard.getBit(queenSideRookStartingSquare) == 0);
        const bool kingSideRookHasMoved = (activePlayerRookBitboard.getBit(kingSideRookStartingSquare) == 0);

        if (queenSideRookHasMoved && !kingSideRookHasMoved) {
            castleRights[move.color] = CastleRights::ONLY_KING_SIDE;
        }
        else if (!queenSideRookHasMoved && kingSideRookHasMoved)
        {
            castleRights[move.color] = CastleRights::ONLY_QUEEN_SIDE;
        }
        else if (queenSideRookHasMoved && kingSideRookHasMoved)
        {
            castleRights[move.color] = CastleRights::NONE;
        }
        else {}
    }
    else {}
}

void Chessboard::toggleActivePlayer()
{
    nonActivePlayer_ = activePlayer_;

    if (activePlayer_ == Color::WHITE) 
    {
        activePlayer_ = Color::BLACK;
    }
    else {
        activePlayer_ = Color::WHITE;
    }
}

Color Chessboard::getActivePlayer() const
{
    return activePlayer_;
}

Color Chessboard::getNonActivePlayer() const
{
    return nonActivePlayer_;
}

void Chessboard::undoMove(const Move & move)
{
    raiseExceptionIfMoveHistoryIsEmpty("There is no move history and therefore no moves to undo.");
    raiseExceptionIfMoveIsNotLastMove(move, "The requested move can not be undone. Only the last move to be made can be undone.");

    // Move the piece back to its original square
    updateBitboards(move.color, move.piece, move.endSquare, move.startSquare);

    // If the move captured a piece, we need to add that piece back to the board
    if (move.isCapture)
    {
        updateBitboards(move.capturedPiece.value().color, move.capturedPiece.value().type, move.endSquare, move.endSquare);
    }

    // If castle rights were changed in the prior move, then reverse that
    castleRights[move.color] = previousCastleRightsState;

    // Remove the last move from the move history
    moveHistory.pop_back();

    toggleActivePlayer();
}

void Chessboard::raiseExceptionIfMoveHistoryIsEmpty(const std::string & errorMessage) const
{
    if (moveHistory.empty())
    {
        throw exceptions::MoveHistoryIsEmpty(errorMessage);
    }
}

void Chessboard::raiseExceptionIfMoveIsNotLastMove(const Move & move, const std::string & errorMessage) const
{
    Move lastMove = moveHistory.back();
    const bool moveIsNotTheLastMove = !(lastMove == move);
    if (moveIsNotTheLastMove)
    {
        throw exceptions::UndoMoveError(errorMessage);
    }
}

const std::optional<const Move> Chessboard::getLastMove() const
{
    std::optional<const Move> lastMove;
    if (!moveHistory.empty())
    {
        return moveHistory.back();
    }
    return lastMove;
}

CastleRights Chessboard::getCastleRights(const Color color) const
{
    return castleRights[color];
}
std::optional<Piece> Chessboard::getPieceAt(const Square square) const
{
    Piece piece;
    Bitboard squareBitboard(square);

    // Find the type of piece on this square, if any
    if (getBitboard(PieceType::PAWN) & squareBitboard) { piece.type = PieceType::PAWN; }
    else if (getBitboard(PieceType::KNIGHT) & squareBitboard) { piece.type = PieceType::KNIGHT; }
    else if (getBitboard(PieceType::BISHOP) & squareBitboard) { piece.type = PieceType::BISHOP; }
    else if (getBitboard(PieceType::ROOK) & squareBitboard) { piece.type = PieceType::ROOK; }
    else if (getBitboard(PieceType::QUEEN) & squareBitboard) { piece.type = PieceType::QUEEN; }
    else if (getBitboard(PieceType::KING) & squareBitboard) { piece.type = PieceType::KING; }
    else { return std::nullopt; }

    // Find the color of the piece
    if (getBitboard(Color::WHITE, piece.type) & squareBitboard) { piece.color = Color::WHITE; }
    else { piece.color = Color::BLACK; }
    
    return piece;
}