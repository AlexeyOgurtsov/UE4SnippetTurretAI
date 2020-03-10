#include "MyGameMode.h"
#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyGameConfig.h"
#include "Util/Core/LogUtilLib.h"

MyGameModeType::AMyGameMode()
{
	DefaultPawnClass = MyPawnType::StaticClass();
	PlayerControllerClass = MyPCType::StaticClass();
}
