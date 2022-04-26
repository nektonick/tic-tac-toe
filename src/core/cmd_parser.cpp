#include "cmd_parser.h"
#include "game.h" //

GameSettings parseCmdParams(int, char*[])
{
    // TODO (optional): parse cmd params (see boost program option)
    const int cellsInLineToWin = 3;
    GameSettings settings(PlayerType::human, PlayerType::AI, cellsInLineToWin);
    return settings;
}
