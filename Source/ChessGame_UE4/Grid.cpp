// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Tile.h"
#include "ChessPawn.h"
#include "ChessGameState.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	InitGridSize();
	InitGrid();
	PlacePieces();
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::InitGrid()
{
	FVector TileScale = Tile->GetDefaultObject<ATile>()->GetSize();
	FVector Scale = FVector(TileSize / TileScale.X, TileSize / TileScale.Y, 1.f);
	FRotator Rotation = FRotator();
	
	UWorld* const World = GetWorld();
	if (World)
	{
		for (int i = 0; i < GridSize; i++)
		{
			for (int j = 0; j < GridSize; j++)
			{
				FVector Location = GetLocation(i, j);
				
				FName TileName = FName(FString::Printf(TEXT("Tile%d%c"), i + 1, 'A' + j));

				ATile* NewTile = SpawnTile(World, Location, Rotation, Scale, TileName);
				GameState->Grid.Add(NewTile);

				FLinearColor SelectedCollorOffset = FLinearColor(0.1f, 0.1f, 0.f);
				FLinearColor BaseColor, SelectedColor;

				BaseColor = FLinearColor::White * ((i + (j % 2)) % 2);
				SelectedColor = FLinearColor::Yellow / 2.f - (1 - ((i + (j % 2)) % 2) * 2) * SelectedCollorOffset;

				NewTile->SetDefaultColors(BaseColor, SelectedColor, 0.f);
				NewTile->Row = i;
				NewTile->Column = j;
			}
		}
	}
}

void AGrid::PlacePieces()
{
	FVector PawnScale = Pawn->GetDefaultObject<AChessPawn>()->GetSize();
	FVector Scale = FVector(TileSize / PawnScale.X, TileSize / PawnScale.Y, 1.f);
	FRotator Rotation = FRotator();

	UWorld* const World = GetWorld();
	if (World)
	{
		for (int i = 0; i < GridSize; i += GridSize - 1)
		{
			for (int j = 0; j < GridSize; j++)
			{
				FVector Location = GetLocation(i, j) + FVector::UpVector * 20.f;

				FName PawnName = FName(FString::Printf(TEXT("Pawn%d%d"), i + 1, j + 1));

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Name = PawnName;

				FTransform SpawnTransform = FTransform(Rotation, Location, Scale);
				AChessPawn* NewPawn = World->SpawnActor<AChessPawn>(Pawn, SpawnTransform, SpawnParams);
				Pieces.Add(NewPawn);

				FLinearColor SelectedCollorOffset = FLinearColor(0.1f, 0.1f, 0.f);
				FLinearColor BaseColor, SelectedColor;

				BaseColor = FLinearColor::White * ((float)i / (GridSize - 1));
				SelectedColor = FLinearColor::Yellow / 2.f - (1 - ((float)i / (GridSize - 1)) * 2) * SelectedCollorOffset;

				NewPawn->SetDefaultColors(BaseColor, SelectedColor, 0.f);
				ATile* OriginTile = GameState->Grid[i * GridSize + j];
				NewPawn->SetNextTile(OriginTile);

				GameState->ChessPiecesState.Add(OriginTile, NewPawn);
			}
		}
	}
}

FVector AGrid::GetLocation(int32 i, int32 j) const
{
	float Center = (float)GridSize / 2.f;
	float XOffset = (i - Center) * TileSize + TileOffset * (i - 1 - Center);
	float YOffset = (j - Center) * TileSize + TileOffset * (j - 1 - Center);

	return GetActorLocation() - FVector(XOffset, YOffset, 0);
}


void AGrid::InitGridSize()
{
	GridSize = 0;
	UE_LOG(LogClass, Log, TEXT("InitGridSize"));


	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		GameState = World->GetGameState<AChessGameState>();
		if (GameState != nullptr)
		{
			GridSize = GameState->TilesPerLine;
		}
	}
}


ATile* AGrid::SpawnTile(UWorld* World, FVector Location, FRotator Rotation, FVector Scale, FName TileName)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Name = TileName;

	FTransform SpawnTransform = FTransform(Rotation, Location, Scale);
	ATile* NewTile = World->SpawnActor<ATile>(Tile, SpawnTransform, SpawnParams);

	return NewTile;
}


