#include "cmd_parser.h"
#include "game.h" //

GameSettings parseCmdParams(int, char*[])
{
    // TODO (optional): parse cmd params (see boost program option)
    GameSettings settings(PlayerType::human, PlayerType::AI);
    return settings;
}
