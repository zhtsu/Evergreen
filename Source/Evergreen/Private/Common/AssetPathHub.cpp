// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AssetPathHub.h"

FName UAssetPathHub::GetStringTableID(EStringTableType Type)
{
	if (Type == EStringTableType::ItemName) return ST_ItemName_TableID;
	else if (Type == EStringTableType::ItemDescription) return ST_ItemDescription_TableID;
	else if (Type == EStringTableType::UI) return ST_UI_TableID;
	else if (Type == EStringTableType::UI_Test) return ST_UI_Test_TableID;
	else return FName();
}
