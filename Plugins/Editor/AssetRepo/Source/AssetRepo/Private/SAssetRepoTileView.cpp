// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SAssetRepoTileView.h"
#include "ImageUtils.h"
#include "SlateOptMacros.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Widgets/Layout/SScrollBox.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

struct DirectoryVisitor : public IPlatformFile::FDirectoryVisitor
{
	TArray<TSharedPtr<FAssetInstanceData>>& AssetList;

	DirectoryVisitor(TArray<TSharedPtr<FAssetInstanceData>>& OutAssetList) : AssetList(OutAssetList)
	{
		
	}
	
	bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
	{
		if (bIsDirectory)
		{
			TSharedPtr<FAssetInstanceData> AssetInstanceData = FAssetInstanceData::New();
			AssetInstanceData->Path = FString(FilenameOrDirectory);
			
			const FString AssetConfigFilePath = FString(FilenameOrDirectory) / "Asset.config";
			if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*AssetConfigFilePath))
			{
				UE_LOG(LogTemp, Warning, TEXT("Invalid asset config file path: %s"), *AssetConfigFilePath);
				return true;
			}
			
			FString JsonStr;
			FFileHelper::LoadFileToString(JsonStr, *AssetConfigFilePath);
			TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(JsonStr);
			TSharedPtr<FJsonObject> JsonObject;
			if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
			{
				if (JsonObject->HasField(TEXT("Name")))
				{
					AssetInstanceData->Name = JsonObject->GetStringField(TEXT("Name"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to read Name property!"));
				}
				if (JsonObject->HasField(TEXT("Uploader")))
				{
					AssetInstanceData->Uploader = JsonObject->GetStringField(TEXT("Uploader"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to read Uploader property!"));
				}
				if (JsonObject->HasField(TEXT("Date")))
				{
					AssetInstanceData->Date = JsonObject->GetStringField(TEXT("Date"));
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Failed to read Date property!"));
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to deserialize json:\n%s"), *JsonStr);
			}
			
			const FString ThumbnailFilePath = FString(FilenameOrDirectory) / "Thumbnail.png";
			if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*ThumbnailFilePath))
            {
            	UE_LOG(LogTemp, Warning, TEXT("Invalid asset thumbnail image file path: %s"), *ThumbnailFilePath);
            	return true;
            }
			
			UTexture2D* Thumbnail = FImageUtils::ImportFileAsTexture2D(ThumbnailFilePath);
			Thumbnail->AddToRoot();
			
			AssetInstanceData->ThumbnailBrush = new FSlateBrush();
			AssetInstanceData->ThumbnailBrush->DrawAs = ESlateBrushDrawType::Image;
			AssetInstanceData->ThumbnailBrush->SetResourceObject(Thumbnail);
			
			AssetList.Emplace(AssetInstanceData);
		}

		return true;
	}
};

void SAssetRepoTileView::InitializeAssetList(FString InAssetRepoRootPath)
{
	DirectoryVisitor Visitor(AssetList);
	if (IFileManager::Get().IterateDirectory(*InAssetRepoRootPath, Visitor) == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid asset repository root path: %s"), *InAssetRepoRootPath);
	}
}

void SAssetRepoTileView::OnListMouseButtonLeftClick(TSharedPtr<FAssetInstanceData> Item)
{
	SelectedAssetNameText->SetText(FText::FromString(Item->Name));
	SelectedAssetUploaderText->SetText(FText::FromString(Item->Uploader));
	SelectedAssetDateText->SetText(FText::FromString(Item->Date));
	SelectedAssetPathText->SetText(FText::FromString(Item->Path));
}

void SAssetRepoTileView::OnAssetRepoRootPathChanged(const FText& Text)
{
	AssetRepoRootPath = Text.ToString();
}

FReply SAssetRepoTileView::OpenAssetPath()
{
	if (SelectedAssetPathText->GetText().ToString() == TEXT("未选中"))
	{
		return FReply::Handled();
	}

	if (FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*SelectedAssetPathText->GetText().ToString()))
	{
		FPlatformProcess::ExploreFolder(*SelectedAssetPathText->GetText().ToString());
	}

	return FReply::Handled();
}

FReply SAssetRepoTileView::FlushAssetTileView()
{
	SelectedAssetNameText->SetText(FText::FromString(TEXT("未选中")));
	SelectedAssetUploaderText->SetText(FText::FromString(TEXT("未选中")));
	SelectedAssetDateText->SetText(FText::FromString(TEXT("未选中")));
	SelectedAssetPathText->SetText(FText::FromString(TEXT("未选中")));

	TileViewBox->RemoveSlot(TileViewPtr.ToSharedRef());
	TileViewPtr.Reset();

	AssetList.Reset();
	InitializeAssetList(AssetRepoRootPath);
	
	SAssignNew(TileViewPtr, STileView<TSharedPtr<FAssetInstanceData>>)
	.ListItemsSource(&AssetList)
	.OnGenerateTile(this, &SAssetRepoTileView::MakeTileViewWidget)
	.OnMouseButtonClick(this, &SAssetRepoTileView::OnListMouseButtonLeftClick);
	
	TileViewBox->AddSlot()
	[
		TileViewPtr.ToSharedRef()
	];
	
	return FReply::Handled();
}

void SAssetRepoTileView::Construct(const FArguments& InArgs)
{
	AssetRepoRootPath = InArgs._AssetRepoRootPath.Get();
	InitializeAssetList(AssetRepoRootPath);
	
	SAssignNew(SelectedAssetNameText, STextBlock);
	SelectedAssetNameText->SetText(FText::FromString(TEXT("未选中")));
	SAssignNew(SelectedAssetUploaderText, STextBlock);
	SelectedAssetUploaderText->SetText(FText::FromString(TEXT("未选中")));
	SAssignNew(SelectedAssetDateText, STextBlock);
	SelectedAssetDateText->SetText(FText::FromString(TEXT("未选中")));
	SAssignNew(SelectedAssetPathText, STextBlock);
	SelectedAssetPathText->SetText(FText::FromString(TEXT("未选中")));
	
	SAssignNew(TileViewPtr, STileView<TSharedPtr<FAssetInstanceData>>)
	.ListItemsSource(&AssetList)
	.OnGenerateTile(this, &SAssetRepoTileView::MakeTileViewWidget)
	.OnMouseButtonClick(this, &SAssetRepoTileView::OnListMouseButtonLeftClick);

	SAssignNew(TileViewBox, SScrollBox);
	TileViewBox->AddSlot()
	[
		TileViewPtr.ToSharedRef()
	];

	ChildSlot
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.0f)
			[
				SNew(SEditableText)
				.Text(FText::FromString(AssetRepoRootPath))
				.OnTextChanged(this, &SAssetRepoTileView::OnAssetRepoRootPathChanged)
			]
			+SHorizontalBox::Slot()
			.AutoWidth()
			[
				SNew(SButton)
				.Text(FText::FromString(TEXT("更新")))
				.OnClicked(this, &SAssetRepoTileView::FlushAssetTileView)
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("资产名称：")))
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SelectedAssetNameText.ToSharedRef()
					]
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("上传人员：")))
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SelectedAssetUploaderText.ToSharedRef()
					]
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("上传日期：")))
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SelectedAssetDateText.ToSharedRef()
					]
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+SHorizontalBox::Slot()
					.AutoWidth()
					[
						SNew(STextBlock)
						.Text(FText::FromString(TEXT("资产路径：")))
					]
					+SHorizontalBox::Slot()
					.HAlign(HAlign_Center)
					[
						SelectedAssetPathText.ToSharedRef()
					]
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SButton)
					.HAlign(HAlign_Center)
					.Text(FText::FromString(TEXT("打开资产目录")))
					.OnClicked(this, &SAssetRepoTileView::OpenAssetPath)
				]
			]
		]
		+SVerticalBox::Slot()
		.FillHeight(1.0f)
		[
			TileViewBox.ToSharedRef()
		]
	];
}

TSharedRef<ITableRow> SAssetRepoTileView::MakeTileViewWidget(TSharedPtr<FAssetInstanceData> ClientItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	if (ClientItem.IsValid() == false)
	{
		return SNew(STableRow<TSharedPtr<FAssetInstanceData>>, OwnerTable)
		[
			SNew(SBox)
			.MinDesiredHeight(160.0f)
			.MinDesiredWidth(160.0f)
			.Padding(4.0f)
			.Padding(4.0f)
			[
				SNew(STextBlock)
				.Justification(HAlign_Center)
				.Text(FText::FromString(TEXT("加载错误")))
			]
		];
	}
	
	return SNew(STableRow<TSharedPtr<FAssetInstanceData>>, OwnerTable)
		[
			SNew(SBox)
			.MinDesiredHeight(160.0f)
			.MinDesiredWidth(160.0f)
			.Padding(4.0f)
			[
				SNew(SOverlay)
				+ SOverlay::Slot()
				[
					SNew(SButton)
				]
				+ SOverlay::Slot()
				.Padding(4.0f)
				.HAlign(EHorizontalAlignment::HAlign_Fill)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.VAlign(VAlign_Fill)
					[
						SNew(SBox)
						[
							SNew(SImage)
							.Image(ClientItem->ThumbnailBrush)
						]
					]
				]
			]
		];
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
