// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"
#include "ChessGameState.h"
#include "ChessPlayerController.h"
#include "ChessPlayerState.h"
#include "Tile.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
AChessPiece::AChessPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SelectedElevationOffset = 200.f;
	bIsSelected = false;
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	InitialElevation = GetActorLocation();
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentElevation = bIsSelected ? SelectedElevation : 0.f;
	FVector TargetPosition = InitialElevation;
	TargetPosition.Z += CurrentElevation;
	SetActorLocation(FMath::Lerp(GetActorLocation(), TargetPosition, DeltaTime * 20.f));
}

void AChessPiece::BeginCursorOver_Implementation(UPrimitiveComponent* Component)
{
	if (ShouldHighlight())
	{
		DynamicMaterialInstance->SetScalarParameterValue(FName("BlendFactor"), 0.6f);
	}
}

void AChessPiece::EndCursorOver_Implementation(UPrimitiveComponent* Component)
{
	DynamicMaterialInstance->SetScalarParameterValue(FName("BlendFactor"), 0.f);
}

void AChessPiece::SelectPiece(bool bValue)
{
	bIsSelected = bValue;
}

TArray<FVector2D> AChessPiece::GetPossibleMoves()
{
	//TArray<FVector2D> CurrentPossibleMoves;
	//FVector2D CurrentTilePosition = FVector2D(CurrentTile->Row, CurrentTile->Column);

	//for (FVector2D Move : PossibleMoves)
	//{
	//	CurrentPossibleMoves.Add(CurrentTilePosition + Move);
	//}

	return PossibleMoves;
}

int32 AChessPiece::GetColor() const
{
	return (uint8)PieceColor;
}

void AChessPiece::SetColor(EColor Color)
{
	PieceColor = Color;
}

ATile* AChessPiece::GetCurrentTile() const
{
	return CurrentTile;
}

void AChessPiece::SetNextTile(ATile* NextTile)
{
	CurrentTile = NextTile;
}

void AChessPiece::MoveTo(ATile* Tile)
{
	FVector TargetLocation = Tile->GetActorLocation();
	InitialElevation.X = TargetLocation.X;
	InitialElevation.Y = TargetLocation.Y;

	SetNextTile(Tile);
}

int32 AChessPiece::GetValue() const
{
	return 1;
}

bool AChessPiece::ShouldHighlight()
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

					if (PlayerState != nullptr && !PlayerState->IsHoldingPiece())
					{
						return true;
					}
				}

			}
		}
	}
	return false;
}

