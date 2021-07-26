// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPawn.h"

AChessPawn::AChessPawn()
{
	Value = 1;

	PossibleMoves.Add(FVector2D(1, 0));
	PossibleMoves.Add(FVector2D(2, 0));
}
