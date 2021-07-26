// Copyright Epic Games, Inc. All Rights Reserved.

#include "ChessGame_UE4GameMode.h"
#include "ChessGame_UE4PlayerController.h"
#include "ChessGame_UE4Character.h"
#include "UObject/ConstructorHelpers.h"

AChessGame_UE4GameMode::AChessGame_UE4GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AChessGame_UE4PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}