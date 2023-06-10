#include "attacktables.h"

namespace attack_tables
{

void init()
{
    initializePawnAttackTable();
}

void initializePawnAttackTable()
{
    for (int i = 0; i < 63; i++)
    {
        pawn[i] = 0;
    }
}

}