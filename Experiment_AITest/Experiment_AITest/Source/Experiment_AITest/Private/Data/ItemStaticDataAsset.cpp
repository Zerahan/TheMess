// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ItemStaticDataAsset.h"

UItemStaticDataAsset::UItemStaticDataAsset()
{
	DisplayName	= "Undefined";
	Icon		= nullptr;
	StackSize	= 99;
}

bool UItemStaticDataAsset::IsValidAsset() const { return DisplayName != "Undefined"; }

FName UItemStaticDataAsset::GetDisplayName() const { return DisplayName; }

UTexture* UItemStaticDataAsset::GetIcon() const { return Icon.LoadSynchronous(); }

int32 UItemStaticDataAsset::GetStackSize() const { return StackSize; }
