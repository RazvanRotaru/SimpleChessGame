// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "ChessGameState.h"
#include "ChessPlayerController.h"
#include "ChessPlayerState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATile::ATile()
{

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

void ATile::BeginCursorOver_Implementation(UPrimitiveComponent* Component)
{
	if (ShouldHighlight())
	{
		DynamicMaterialInstance->SetScalarParameterValue(FName("BlendFactor"), 1.f);
	}
}

void ATile::EndCursorOver_Implementation(UPrimitiveComponent* Component)
{
	DynamicMaterialInstance->SetScalarParameterValue(FName("BlendFactor"), 0.f);
}

bool ATile::ShouldHighlight()
{
	UWorld* World = GetWorld();
	if (World != nullptr) {
		AGameStateBase* CurrentState = World->GetGameState();
		if (CurrentState != nullptr && CurrentState->IsA(AChessGameState::StaticClass()))
		{
			AChessGameState* GameState = Cast<AChessGameState>(CurrentState);
			if (GameState != nullptr)
			{
				APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), GameState->CurrentPlayer);
				if (PlayerController != nullptr)
				{
					AChessPlayerState* PlayerState = PlayerController->GetPlayerState<AChessPlayerState>();

					if (PlayerState != nullptr && PlayerState->IsHoldingPiece())
					{
						return true;
					}
				}

			}
		}
	}
	return false;
}

