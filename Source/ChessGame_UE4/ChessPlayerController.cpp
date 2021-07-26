// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerController.h"
#include "ChessPlayerState.h"
#include "ChessGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ChessPiece.h"
#include "Tile.h"


AChessPlayerController::AChessPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;

	Color = EPlayerColor::WHITE;
	PlayerState = CreateDefaultSubobject<AChessPlayerState>(FName("State"));
	State = (AChessPlayerState*)PlayerState;

	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
		if (GameMode != nullptr && GameMode->IsA(AChessGameMode::StaticClass()))
		{
			ChessGameMode = Cast<AChessGameMode>(GameMode);
		}
	}
}

void AChessPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("LeftMouseClick", IE_Pressed, this, &AChessPlayerController::OnLeftClick);
}

int32 AChessPlayerController::GetPoints(int32 Ammount)
{
	return State->GetCurrentScore();
}

bool AChessPlayerController::CanGrab(AChessPiece* Piece) const
{
	return !State->IsHoldingPiece() && Piece->GetColor() == GetColor();
}

void AChessPlayerController::Grab(AChessPiece* Piece) const
{
	State->SelectPiece(Piece);
	ChessGameMode->HighlightPossibleMoves(Piece);
}

int32 AChessPlayerController::GetColor() const
{
	return (uint8)Color;
}

void AChessPlayerController::SetColor(EPlayerColor NewColor)
{
	Color = NewColor;
}

void AChessPlayerController::OnLeftClick_Implementation()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit != nullptr && ActorHit->IsA(AInteractableActor::StaticClass()))
	{
		if (!State->IsHoldingPiece())
		{
			AChessPiece* ChessPiece = Cast<AChessPiece>(ActorHit);
			if (ChessPiece != nullptr && CanGrab(ChessPiece))
			{
				Grab(ChessPiece);
			}
		}
		else 
		{
			ATile* ChessTile = Cast<ATile>(ActorHit);
			if (ChessTile != nullptr && ChessGameMode->CanPlaceOn(ChessTile))
			{
				AChessPiece* CurrentChessPiece = State->GetSelectedPiece();
				AChessPiece* PreviousChessPiece = ChessGameMode->PlaceOn(ChessTile, CurrentChessPiece);
				if (PreviousChessPiece != nullptr)
				{
					State->GainPoints(PreviousChessPiece->GetValue());
					PreviousChessPiece->Destroy();
				}
				State->UnselectPiece();
				ChessGameMode->SwitchPlayers();
			}
			else
			{
				UE_LOG(LogClass, Log, TEXT("You cannot place that here or that is null"));
			}
		}
	}
}

void AChessPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}
