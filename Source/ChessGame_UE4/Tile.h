// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableActor.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class CHESSGAME_UE4_API ATile : public AInteractableActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();


	virtual void BeginCursorOver_Implementation(class UPrimitiveComponent* Component) override;
	virtual void EndCursorOver_Implementation(class UPrimitiveComponent* Component) override;

	UPROPERTY(VisibleAnywhere, Category = "Position")
	int32 Row;
	
	UPROPERTY(VisibleAnywhere, Category = "Position")
	int32 Column;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UFUNCTION()
	bool ShouldHighlight();
};
