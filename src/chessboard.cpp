#include "chessboard.h"
#include "exceptions.h"
#include "utils.h"

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
    return static_cast<Rank>(square / 8);
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

Chessboard::Chessboard(const std::string & fen)
{
    // TODO: split the string into the known sections:
    // 1. piece positions
    // 2. active player
    // 3. castle rights
    // 4. - ?
    // 5. 0 1 ?
    for (const char c : fen)
    {
        switch (c)
        {
            case 'P':
                break;
            case 'N':
                break;
            case 'B':
                break;
            case 'R':
                break;
            case 'Q':
                break;
            case 'K':
                break;
            case 'p':
                break;
            case 'n':
                break;
            case 'b':
                break;
            case 'r':
                break;
            case 'q':
                break;
            case 'k':
                break;
            case '/':
                break;
            case ' ':
                break;
            case 'w':
                break;
            case '8':
                break;
            case '-':
                break;
            case '0':
                break;
            case '1':
                break;
            case 'KQ':
                break;
            case 'kq':
                break;
        }
    }
}

const Bitboard Chessboard::getOccupiedSquares() const
{
    return getBitboard(Color::WHITE) | getBitboard(Color::BLACK);
}

const Bitboard &Chessboard::getBitboard(const PieceType piece) const
{
    return pieceBitboards_[piece];
}

const Bitboard &Chessboard::getBitboard(const Color color) const
{
    return colorBitboards_[color];
}

Bitboard Chessboard::getBitboard(const Color color, const PieceType piece) const
{
    return pieceBitboards_[piece] & colorBitboards_[color];
}

void Chessboard::applyMove(const Move &move)
{
    Color activeColor = move.color();
    PieceType movePieceType = move.pieceType();
    Square startSquare = move.startSquare();
    Square endSquare = move.endSquare();

    // Store the active player's castle rights state in case this move is later undone,
    // then we can quickly restore the castle rights back to this player
    previousCastleRightsState = castleRights[activeColor];

    if (move.isCapture() || move.isEnPassant())
    {
        if (move.capturedPiece().has_value() == false)
        {
            throw exceptions::chessboard::InvalidMove("Attempting to capture piece but the move's captured piece is not set. Move information: " + utils::moveToString(move));
        }

        CapturedPiece captured = move.capturedPiece().value();
        removePiece(captured.color, captured.type, captured.square);
    }

    if (move.isCastle())
    {
        if (move.castleSide().has_value() == false)
        {
            throw exceptions::chessboard::InvalidMove("Attempting to castle but the move's castle side is not set. Move information: " + utils::moveToString(move));
        }
        CastleSide side = move.castleSide().value();
        CastleMove castleInfo = constants::CASTLE_SQUARES[activeColor][static_cast<int>(side)];
        movePiece(activeColor, PieceType::ROOK, castleInfo.rookStart, castleInfo.rookEnd);
    }

    if (move.isPromotion())
    {
        if (move.promotionPiece().has_value() == false)
        {
            throw exceptions::chessboard::InvalidMove("Attempting to promote but the move's promotion piece is not set. Move information: " + utils::moveToString(move));
        }
        PieceType promotionPieceType = move.promotionPiece().value();
        removePiece(activeColor, movePieceType, startSquare);
        addPiece(activeColor, promotionPieceType, endSquare);
    }
    else
    {
        // This movePiece will happen to all moves except for promotion moves
        movePiece(activeColor, movePieceType, startSquare, endSquare);
    }

    if (movePieceType == PieceType::KING || movePieceType == PieceType::ROOK)
    {
        updateCastleRights(move);
    }

    moveHistory.push_back(move);
    toggleActivePlayer();
}

void Chessboard::removePiece(const Color color, const PieceType piece, const Square square)
{
    std::string error = "Can not remove " + utils::pieceTypeToString(piece) + " from square " + utils::squareToString(square) + ". It does not exist.";
    raiseExceptionIfPieceIsNotOnSquare(color, piece, square, error);

    pieceBitboards_[piece].clearBit(square);
    colorBitboards_[color].clearBit(square);
}

void Chessboard::raiseExceptionIfPieceIsNotOnSquare(const Color color, const PieceType piece, const Square square, const std::string & errorMessage)
{
    if (getBitboard(color, piece).getBit(square) == 0)
    {
        throw exceptions::chessboard::InvalidMove(errorMessage);
    }
}

void Chessboard::movePiece(const Color color, const PieceType piece, const Square start, const Square end)
{
    removePiece(color, piece, start);
    addPiece(color, piece, end);
}

void Chessboard::addPiece(const Color color, const PieceType piece, const Square square)
{
    std::string error = "Cannot add piece to " + utils::squareToString(square) + ". The square is already occupied.";
    raiseExceptionIfSquareIsOccupied(square, error);

    pieceBitboards_[piece].setBit(square);
    colorBitboards_[color].setBit(square);
}

void Chessboard::raiseExceptionIfSquareIsOccupied(const Square square, const std::string & errorMessage)
{
    if (squareIsOccupied(square))
    {
        throw exceptions::chessboard::InvalidMove(errorMessage);
    }
}

bool Chessboard::squareIsOccupied(const Square square)
{
    return static_cast<bool>(getOccupiedSquares() & Bitboard(square));
}

void Chessboard::updateCastleRights(const Move &move)
{
    if (castleRights[move.color()] == CastleRights::NONE)
    {
        return;
    }
    else if (move.pieceType() == PieceType::KING)
    {
        castleRights[move.color()] = CastleRights::NONE;
    }
    else if (move.pieceType() == PieceType::ROOK)
    {
        Square queenSideRookStartingSquare = Square::a1;
        Square kingSideRookStartingSquare = Square::h1;

        if (move.color() == Color::BLACK)
        {
            queenSideRookStartingSquare = Square::a8;
            kingSideRookStartingSquare = Square::h8;
        }

        const Bitboard activePlayerRookBitboard = getBitboard(move.color(), PieceType::ROOK);
        const bool queenSideRookHasMoved = (activePlayerRookBitboard.getBit(queenSideRookStartingSquare) == 0);
        const bool kingSideRookHasMoved = (activePlayerRookBitboard.getBit(kingSideRookStartingSquare) == 0);

        if (queenSideRookHasMoved && !kingSideRookHasMoved)
        {
            castleRights[move.color()] = CastleRights::ONLY_KING_SIDE;
        }
        else if (!queenSideRookHasMoved && kingSideRookHasMoved)
        {
            castleRights[move.color()] = CastleRights::ONLY_QUEEN_SIDE;
        }
        else if (queenSideRookHasMoved && kingSideRookHasMoved)
        {
            castleRights[move.color()] = CastleRights::NONE;
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
    else
    {
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

void Chessboard::undoMove(const Move &move)
{
    raiseExceptionIfMoveHistoryIsEmpty("There is no move history and therefore no moves to undo.");
    raiseExceptionIfMoveIsNotLastMove(move, "The requested move can not be undone. Only the last move to be made can be undone.");

    Color activeColor = move.color();
    PieceType movePieceType = move.pieceType();
    Square startSquare = move.startSquare();
    Square endSquare = move.endSquare();

    /* NOTE: This must come before handling captured pieces.
     * If a pawn captured a piece into promotion, we must first remove the promoted piece
     * from the capture square before we can add the captured piece back to that square.
     */
    if (move.isPromotion())
    {
        PieceType promotionPieceType = move.promotionPiece().value();
        removePiece(activeColor, promotionPieceType, endSquare);
        addPiece(activeColor, movePieceType, startSquare);
    }
    else
    {
        movePiece(activeColor, movePieceType, endSquare, startSquare);
    }

    // If the move captured a piece, we need to add that piece back to the board
    if (move.isCapture() || move.isEnPassant())
    {
        CapturedPiece captured = move.capturedPiece().value();
        addPiece(captured.color, captured.type, captured.square);
    }
    
    if (move.isCastle())
    {
        CastleSide side = move.castleSide().value();
        CastleMove castleInfo = constants::CASTLE_SQUARES[activeColor][static_cast<int>(side)];
        movePiece(activeColor, PieceType::ROOK, castleInfo.rookEnd, castleInfo.rookStart);
    }

    // If castle rights were changed in the prior move, then reverse that
    castleRights[activeColor] = previousCastleRightsState;

    // Remove the last move from the move history
    moveHistory.pop_back();

    toggleActivePlayer();
}

void Chessboard::raiseExceptionIfMoveHistoryIsEmpty(const std::string &errorMessage) const
{
    if (moveHistory.empty())
    {
        throw exceptions::chessboard::MoveHistoryIsEmpty(errorMessage);
    }
}

void Chessboard::raiseExceptionIfMoveIsNotLastMove(const Move &move, const std::string &errorMessage) const
{
    Move lastMove = moveHistory.back();
    const bool moveIsNotTheLastMove = !(lastMove == move);
    if (moveIsNotTheLastMove)
    {
        throw exceptions::chessboard::UndoMoveError(errorMessage);
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