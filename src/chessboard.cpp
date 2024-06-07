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

Square Chessboard::coordinatesToSquare(const int rank, const int file)
{
    return static_cast<Square>(8 * rank + file);
}

Color Chessboard::getOpponentColor(const Color color)
{
    if (color == Color::BLACK) { return Color::WHITE; }
    return Color::BLACK;
}

const GameState Chessboard::parseFEN(const std::string & fen)
{
    std::vector<std::string> fenSections = utils::tokenizeString(fen);
    std::string piecePositions = fenSections[0];
    std::string activePlayer = fenSections[1];
    std::string castleAvailability = fenSections[2];
    std::string enPassantTargetSquare = fenSections[3];
    std::string halfMoveClock = fenSections[4];
    std::string moveNumber = fenSections[5];

    GameState gameState = parsePiecePositions(piecePositions);
    gameState.activePlayer = parseActivePlayer(activePlayer);

    std::pair<CastleRights, CastleRights> castleRights = parseCastleRights(castleAvailability);
    gameState.whiteCastleRights = castleRights.first;
    gameState.blackCastleRights = castleRights.second;

    gameState.enPassantSquare = parseEnPassantSquare(enPassantTargetSquare);
    gameState.halfMoveClock = parseHalfMoveClock(halfMoveClock);
    gameState.moveNumber = parseMoveNumber(moveNumber);

    return gameState;
}

const GameState Chessboard::parsePiecePositions(const std::string & piecePositionsFEN)
{    
    // TODO: Make this more readable
    GameState state;

    int squarePosition = 0;
    for (std::size_t i = 0; i < piecePositionsFEN.length(); ++i) {
        int j = utils::bigEndianRankFileToLittleEndianRankFile(squarePosition);
        const char c = piecePositionsFEN[i];
        switch (c)
        {
            case 'P':
            {
                state.pawns |= (constants::ONE << j);
                state.whiteOccupied |= (constants::ONE << j);
                break;
            }
            case 'N':
            {
                state.knights |= (constants::ONE << j);
                state.whiteOccupied |= (constants::ONE << j);
                break;
            }
            case 'B':
            {
                state.bishops |= (constants::ONE << j);
                state.whiteOccupied |= (constants::ONE << j);
                break;
            }
            case 'R':
            {
                state.rooks |= (constants::ONE << j);
                state.whiteOccupied |= (constants::ONE << j);
                break;
            }
            case 'Q':
            {
                state.queens |= (constants::ONE << j);
                state.whiteOccupied |= (constants::ONE << j);
                break;
            }
            case 'K':
            {
                state.kings |= (constants::ONE << j);
                state.whiteOccupied |= (constants::ONE << j);
                break;
            }
            case 'p':
            {
                state.pawns |= (constants::ONE << j);
                state.blackOccupied |= (constants::ONE << j);
                break;
            }
            case 'n':
            {
                state.knights |= (constants::ONE << j);
                state.blackOccupied |= (constants::ONE << j);
                break;
            }
            case 'b':
            {
                state.bishops |= (constants::ONE << j);
                state.blackOccupied |= (constants::ONE << j);
                break;
            }
            case 'r':
            {
                state.rooks |= (constants::ONE << j);
                state.blackOccupied |= (constants::ONE << j);
                break;
            }
            case 'q':
            {
                state.queens |= (constants::ONE << j);
                state.blackOccupied |= (constants::ONE << j);
                break;
            }
            case 'k':
            {
                state.kings |= (constants::ONE << j);
                state.blackOccupied |= (constants::ONE << j);
                break;
            }
            case '/':
            {
                squarePosition -= 1;
                break;
            }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            {
                int charToInt = c - '0';
                squarePosition += (charToInt - 1);
                break;
            }
            default:
            {
                throw exceptions::fen::InvalidFEN("Unable to parse piece positions. Received unknwon character: '" + utils::charToString(c) + "'");
            }
        }
        squarePosition++;
    }

    return state;
}

Color Chessboard::parseActivePlayer(const std::string & colorFEN)
{
    if (colorFEN.length() != 1)
    {
        throw exceptions::fen::InvalidFEN("Unable to parse active player. Received multiple characters: '" + colorFEN + "'");
    }

    Color activePlayer = Color::NO_COLOR;
    for (const char c : colorFEN)
    {
        switch (c)
        {
            case 'w':
            {
                activePlayer = Color::WHITE;
                break;
            }
            case 'b':
            {
                activePlayer = Color::BLACK;
                break;
            }
            default:
            {
                throw exceptions::fen::InvalidFEN("Unable to parse active player. Received unknown character: '" + utils::charToString(c) + "'");
            }
        }
    }

    return activePlayer;
}

const std::pair<CastleRights, CastleRights> Chessboard::parseCastleRights(const std::string & castleRightsFEN)
{
    std::pair<CastleRights, CastleRights> castleRights(CastleRights::NONE, CastleRights::NONE);

    if (castleRightsFEN == "-")
    {
        return castleRights;
    }
    
    for (const char c : castleRightsFEN)
    {
        switch (c)
        {
            case 'K':
            {
                castleRights.first = static_cast<CastleRights>(static_cast<uint8_t>(castleRights.first) | static_cast<uint8_t>(CastleRights::ONLY_KINGSIDE));
                break;
            }
            case 'Q':
            {
                castleRights.first = static_cast<CastleRights>(static_cast<uint8_t>(castleRights.first) | static_cast<uint8_t>(CastleRights::ONLY_QUEENSIDE));
                break;
            }
            case 'k':
            {
                castleRights.second = static_cast<CastleRights>(static_cast<uint8_t>(castleRights.second) | static_cast<uint8_t>(CastleRights::ONLY_KINGSIDE));
                break;
            }
            case 'q':
            {
                castleRights.second = static_cast<CastleRights>(static_cast<uint8_t>(castleRights.second) | static_cast<uint8_t>(CastleRights::ONLY_QUEENSIDE));
                break;
            }
            default:
            {
                throw exceptions::fen::InvalidFEN("Unable to parse castle rights. Received unknown character: '" + utils::charToString(c) + "'");
            }
        }
    }

    return castleRights;
}

Square Chessboard::parseEnPassantSquare(const std::string & enPassantSquareFEN)
{
    if (enPassantSquareFEN.length() > 2)
    {
        throw exceptions::fen::InvalidFEN("Unable to parse en passant square. Received string with more than two characters: '" + enPassantSquareFEN + "'");
    }

    Rank rank = Rank::NO_RANK;
    File file = File::NO_FILE;

    for (const char c : enPassantSquareFEN)
    {
        switch (c)
        {
            case 'a':
            case 'A':
            {
                file = File::FILE_A;
                break;
            }
            case 'b':
            case 'B':
            {
                file = File::FILE_B;
                break;
            }
            case 'c':
            case 'C':
            {
                file = File::FILE_C;
                break;
            }
            case 'd':
            case 'D':
            {
                file = File::FILE_D;
                break;
            }
            case 'e':
            case 'E':
            {
                file = File::FILE_E;
                break;
            }
            case 'f':
            case 'F':
            {
                file = File::FILE_F;
                break;
            }
            case 'g':
            case 'G':
            {
                file = File::FILE_G;
                break;
            }
            case 'h':
            case 'H':
            {
                file = File::FILE_H;
                break;
            }
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            {
                int charToInt = c - '0';
                int rankConvertedToZeroBasedIndex = charToInt - 1;
                rank = static_cast<Rank>(rankConvertedToZeroBasedIndex);
                break;
            }
            case '-':
            {
                return Square::NO_SQUARE;
            }
            default:
            {
                throw exceptions::fen::InvalidFEN("Unable to parse en passant square. Received unknown character: '" + utils::charToString(c) + "'");
            }
        }
    }

    return Chessboard::coordinatesToSquare(rank, file);
}

int Chessboard::parseHalfMoveClock(const std::string & halfMoveClockFEN)
{
    int halfMoveClock = 0;
    try
    {
        halfMoveClock = std::stoi(halfMoveClockFEN);
    }
    catch (std::logic_error & e)
    {
        std::cerr << "Exception caught from std::stoi(): " << e.what() << std::endl;
        throw exceptions::fen::InvalidFEN("Unable to parse half move clocked. Received input: '" + halfMoveClockFEN + "'");
    }

    return halfMoveClock;
}

int Chessboard::parseMoveNumber(const std::string & moveNumberFEN)
{
    int moveNumber = 0;

    try
    {
        moveNumber = std::stoi(moveNumberFEN);
    }
    catch (std::logic_error & e)
    {
        std::cerr << "Exception caught from std::stoi(): " << e.what() << std::endl;
        throw exceptions::fen::InvalidFEN("Unable to parse move number. Received input: '" + moveNumberFEN + "'");
    }

    return moveNumber;
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
    castleRights[Color::WHITE] = CastleRights::KING_AND_QUEENSIDE;
    castleRights[Color::BLACK] = CastleRights::KING_AND_QUEENSIDE;
    previousCastleRightsState[Color::WHITE] = CastleRights::KING_AND_QUEENSIDE;
    previousCastleRightsState[Color::BLACK] = CastleRights::KING_AND_QUEENSIDE;
}

Chessboard::Chessboard(const std::string & fen)
{
    GameState parsedState = Chessboard::parseFEN(fen);

    // Set bitboards
    pieceBitboards_[PieceType::PAWN].setBoard(parsedState.pawns);
    pieceBitboards_[PieceType::KNIGHT].setBoard(parsedState.knights);
    pieceBitboards_[PieceType::BISHOP].setBoard(parsedState.bishops);
    pieceBitboards_[PieceType::ROOK].setBoard(parsedState.rooks);
    pieceBitboards_[PieceType::QUEEN].setBoard(parsedState.queens);
    pieceBitboards_[PieceType::KING].setBoard(parsedState.kings);

    // Initialize the white and black bitboards
    colorBitboards_[Color::WHITE] = parsedState.whiteOccupied;
    colorBitboards_[Color::BLACK] = parsedState.blackOccupied;

    // Initialize castle rights
    castleRights[Color::WHITE] = parsedState.whiteCastleRights;
    castleRights[Color::BLACK] = parsedState.blackCastleRights;
    
    previousCastleRightsState[Color::WHITE] = parsedState.whiteCastleRights;
    previousCastleRightsState[Color::BLACK] = parsedState.blackCastleRights;

    activePlayer_ = parsedState.activePlayer;
    nonActivePlayer_ = Chessboard::getOpponentColor(activePlayer_);
    enPassantSquare_ = parsedState.enPassantSquare;
    halfMoveClock_ = parsedState.halfMoveClock;
    moveNumber_ = parsedState.moveNumber;
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
    previousCastleRightsState[activeColor] = castleRights[activeColor];
    previousCastleRightsState[nonActivePlayer_] = castleRights[nonActivePlayer_];

    if (move.isCapture() || move.isEnPassant())
    {
        if (move.capturedPiece().has_value() == false)
        {
            throw exceptions::chessboard::InvalidMove("Attempting to capture piece but the move's captured piece is not set. Move information: " + utils::moveToString(move));
        }

        CapturedPiece captured = move.capturedPiece().value();
        removePiece(captured.color, captured.type, captured.square);

        // TODO: Clean up this montrosity
        if (captured.type == PieceType::ROOK && castleRights[captured.color] != CastleRights::NONE)
        {
            const Bitboard captureSquare(captured.square);
            bool isKingsideRook = (captureSquare & constants::DEFAULT_KINGSIDE_ROOKS).anyBitsSet();
            bool isQueensideRook = (captureSquare & constants::DEFAULT_QUEENSIDE_ROOKS).anyBitsSet();
            uint8_t currentCastleRights = static_cast<uint8_t>(castleRights[captured.color]);
            if (isKingsideRook)
            { 
                uint8_t updatedCastleRights = currentCastleRights ^ static_cast<uint8_t>(CastleRights::ONLY_KINGSIDE);
                castleRights[captured.color] = static_cast<CastleRights>(updatedCastleRights);
            }
            if (isQueensideRook)
            {
                uint8_t updatedCastleRights = currentCastleRights ^ static_cast<uint8_t>(CastleRights::ONLY_QUEENSIDE);
                castleRights[captured.color] = static_cast<CastleRights>(updatedCastleRights);
            }
        }
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
            castleRights[move.color()] = CastleRights::ONLY_KINGSIDE;
        }
        else if (!queenSideRookHasMoved && kingSideRookHasMoved)
        {
            castleRights[move.color()] = CastleRights::ONLY_QUEENSIDE;
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

    // Toggling the active player first will put the active player variable in sync with the move's color
    toggleActivePlayer();

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
    // Also, the move is now being given back to the non active player, so
    // set the previous castle rights state to the non active player's castle rights
    castleRights[activeColor] = previousCastleRightsState[activeColor];
    castleRights[nonActivePlayer_] = previousCastleRightsState[nonActivePlayer_];

    // Remove the last move from the move history
    moveHistory.pop_back();
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

Square Chessboard::getEnPassantSquare() const
{
    return enPassantSquare_;
}

int Chessboard::getHalfMoveClock() const
{
    return halfMoveClock_;
}

int Chessboard::getMoveNumber() const
{
    return moveNumber_;
}