#include "movegenerator.h"

#include "move.h"
#include "attacktables.h"

MoveVector LegalMoveGenerator::generatePsuedoLegalMoves(const Chessboard & gameState) const
{
    MoveVector pawnMoves = generatePawnMoves(gameState);
    MoveVector knightMoves = generateKnightMoves(gameState);
    MoveVector bishopMoves = generateBishopMoves(gameState);
    // MoveVector rookMoves = getRookMoves();
    // MoveVector queenMoves = getQueenMoves();
    // MoveVector kingMoves = getKingMoves();

    return pawnMoves;
}

// TODO: This currently doesn't handle single push, double push, or en pessant
MoveVector LegalMoveGenerator::generatePawnMoves(const Chessboard & gameState) const
{
    // What we use from gameState: side to move, we get the position of the pawns, thats it
    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerPawns = gameState.getBitboard(activePlayer, PieceType::PAWN);
    
    const int numberOfPawnsOnBoard = activePlayerPawns.numberOfSetBits();
    for (int i = 0; i < numberOfPawnsOnBoard; i++)
    {
        const Square startingSquare = (Square)(activePlayerPawns.clearAndReturnLSB());

        Bitboard psuedoLegalPawnMoves = attack_tables::PAWN_ATTACKS[activePlayer][startingSquare];

        // For every psuedo legal pawn move, remove attacks to our own pieces, and append the move to the move vector
        int numberOfPsuedoLegalPawnMoves = psuedoLegalPawnMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalPawnMoves; j++)
        {
            // Remove any moves that attack our own pieces
            psuedoLegalPawnMoves &= ~(activePlayerPieces & psuedoLegalPawnMoves);

            const Square targetSquare = (Square)(psuedoLegalPawnMoves.clearAndReturnLSB());
            Move m(activePlayer, PAWN, startingSquare, targetSquare);
            moves.push_back(m);
        }
    }

    return moves;
}

MoveVector LegalMoveGenerator::generateKnightMoves(const Chessboard & gameState) const
{
    // variables: PieceType::KNIGHT, KNIGHT_ATTACKS (and how to index it)

    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerKnights = gameState.getBitboard(activePlayer, PieceType::KNIGHT);
    
    const int numberOfKnightsOnBoard = activePlayerKnights.numberOfSetBits();
    for (int i = 0; i < numberOfKnightsOnBoard; i++)
    {
        const Square startingSquare = (Square)(activePlayerKnights.clearAndReturnLSB());
        Bitboard psuedoLegalKnightMoves = attack_tables::KNIGHT_ATTACKS[startingSquare];

        // Remove any moves that attack our own pieces
        psuedoLegalKnightMoves &= ~(activePlayerPieces & psuedoLegalKnightMoves);

        int numberOfPsuedoLegalMoves = psuedoLegalKnightMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalMoves; j++)
        {
            const Square targetSquare = (Square)(psuedoLegalKnightMoves.clearAndReturnLSB());
            Move m(activePlayer, PAWN, startingSquare, targetSquare);
            moves.push_back(m);
        }
    }

    return moves;
}

MoveVector LegalMoveGenerator::generateBishopMoves(const Chessboard & gameState) const
{
    // variables: PieceType::BISHOP, BISHOP_ATTACKS (and how to index it)

    MoveVector moves;
    const Color activePlayer = gameState.getActivePlayer();
    const Bitboard activePlayerPieces = gameState.getBitboard(activePlayer);
    Bitboard activePlayerBishops = gameState.getBitboard(activePlayer, PieceType::BISHOP);
    
    const int numberOfActivePlayerBishops = activePlayerBishops.numberOfSetBits();
    for (int i = 0; i < numberOfActivePlayerBishops; i++)
    {
        const Square startingSquare = (Square)(activePlayerBishops.clearAndReturnLSB());
        Bitboard psuedoLegalBishopMoves = attack_tables::getSliderPieceAttacks(SliderPiece::BISHOP, startingSquare, gameState.getOccupiedSquares());
        
        // Remove any moves that attack our own pieces
        psuedoLegalBishopMoves &= ~(activePlayerPieces & psuedoLegalBishopMoves);

        int numberOfPsuedoLegalPawnMoves = psuedoLegalBishopMoves.numberOfSetBits();
        for (int j = 0; j < numberOfPsuedoLegalPawnMoves; j++)
        {
            const Square targetSquare = (Square)(psuedoLegalBishopMoves.clearAndReturnLSB());
            Move m(activePlayer, PAWN, startingSquare, targetSquare);
            moves.push_back(m);
        }
    }

    return moves;
}

Bitboard LegalMoveGenerator::filterLegalPawnMoves(Bitboard & psuedoLegalPawnMoves)
{}

MoveVector LegalMoveGenerator::generateLegalMoves(const Chessboard & gameState)
{
    // MoveList psuedoLegalMoves = getPsuedoLegalMoves(gameState);
    // MoveList legalMoves = filterOutIllegalMoves(psuedoLegalMoves);

    // return legalMoves;
}