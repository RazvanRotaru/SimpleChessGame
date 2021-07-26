// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

UENUM(BlueprintType)
enum class EColor : uint8{
	WHITE = 0 UMETA(DispalyName = "White"),
	BLACK = 1 UMETA(DispalyName = "Black")
};

UCLASS()
class CHESSGAME_UE4_API AChessPiece : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessPiece();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void BeginCursorOver_Implementation(class UPrimitiveComponent* Component) override;
	virtual void EndCursorOver_Implementation(class UPrimitiveComponent* Component) override;

	UFUNCTION(BlueprintCallable, Category = "Select")
	void SelectPiece(bool bValue);

	UFUNCTION(BlueprintPure, Category = "Select")
	TArray<FVector2D> GetPossibleMoves();
	
	UFUNCTION(BlueprintPure, Category = "Select")
	int32 GetColor() const;

	UFUNCTION(BlueprintCallable, Category = "Select")
	void SetColor(EColor Color);

	UFUNCTION(BlueprintPure, Category = "Select")
	class ATile* GetCurrentTile() const;

	UFUNCTION(BlueprintCallable, Category = "Select")
	void SetNextTile(class ATile* NexTile);

	UFUNCTION(BlueprintCallable, Category = "Select")
	void MoveTo(class ATile* Tile);

	UFUNCTION(BlueprintPure, Category = "Destroy")
	virtual int32 GetValue() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ChessPieceDetails", Meta = (BlueprintProtected = "true"))
	int32 Value;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ChessPieceDetails", Meta = (BlueprintProtected = "true"))
	TArray<FVector2D> PossibleMoves;

private:
	UFUNCTION()
	bool ShouldHighlight();

	UPROPERTY()
	bool bIsSelected;

	UPROPERTY(VisibleAnywhere, Category = "ChessPieceDetails")
	EColor PieceColor;

	UPROPERTY(VisibleAnywhere, Category = "ChessPieceDetails")
	class ATile* CurrentTile;

	UPROPERTY(EditAnywhere, Category = "ChessPieceDetails")
	float SelectedElevationOffset;

	UPROPERTY(VisibleAnywhere, Category = "ChessPieceDetails")
	float SelectedElevation;
	
	UPROPERTY()
	FVector InitialElevation;

	UPROPERTY(EditAnywhere, Category = "ChessPieceDetails")
	float CurrentElevation;
};