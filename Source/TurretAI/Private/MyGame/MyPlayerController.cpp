#include "MyPlayerController.h"
#include "MyPlayerPawn.h"
#include "MyGameConfig.h"

#include "Util/Core/LogUtilLib.h"

MyPCType::AMyPlayerController()
{
}
 
void MyPCType::BeginPlay()
{
	M_LOGFUNC();

	Super::BeginPlay();
}


MyPawnType* MyPCType::GetMyPawn() const
{
	return Cast<MyPawnType>(GetPawn());
}

MyPawnType* MyPCType::GetMyPawnLogged(ELogFlags InLogFlags) const
{
	MyPawnType* const P = GetMyPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPawn() returned NULL"));
	}
	return P;
}

MyPawnType* MyPCType::GetMyPawnChecked() const
{
	MyPawnType* const P = GetMyPawn();
	checkf(P, TEXT("GetMyPawn must return non-NULL pawn!"));
	return P;
}

