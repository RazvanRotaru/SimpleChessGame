// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class CHESSGAME_UE4_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "GridCreation")
	void InitGrid();

	UFUNCTION(BlueprintCallable, Category = "GridCreation")
	void PlacePieces();

	UFUNCTION(BlueprintPure, Category = "TileLocation")
	FVector GetLocation(int32 i, int32 j) const;

private:
	UFUNCTION()
	void InitGridSize();

	UFUNCTION()
	class ATile* SpawnTile(UWorld* World, FVector Location, FRotator Rotation, FVector Scale, FName TileName);

	UPROPERTY(EditDefaultsOnly, Category = "GridTile")
	TSubclassOf<class ATile> Tile;

	UPROPERTY(EditDefaultsOnly, Category = "GridTile")
	int32 TileSize;

	UPROPERTY(EditDefaultsOnly, Category = "GridTile")
	int32 TileOffset;

	UPROPERTY(VisibleAnywhere, Category = "Grid")
	TArray<class ATile*> Grid;

	UPROPERTY(VisibleAnywhere, Category = "Grid")
	int32 GridSize;

	UPROPERTY(EditDefaultsOnly, Category = "ChessPieces")
	TSubclassOf<class AChessPawn> Pawn;

	UPROPERTY(VisibleAnywhere, Category = "ChessPieces")
	TArray<class AChessPiece*> Pieces;

	UPROPERTY()
	class AChessGameState* GameState;
};
