#include "UnrealSkipper.h"
#include "Engine/DataTable.h"
#include "Engine/Texture2D.h"
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"

// Assure-toi que cette struct correspond à celle dans ton Blueprint
USTRUCT(BlueprintType)
struct S_flag : public TestFlag
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Country")
    FString CountryCode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Country")
    UTexture2D* FlagTexture;
};

void FillDataTable()
{
    // Charger la DataTable
    UDataTable* MyDataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/Path/To/YourDataTable.YourDataTable"));

    // Chemin du dossier où se trouvent les textures
    FString TextureDirectoryPath = TEXT("/Game/Path/To/Textures");

    // Vérifier si la DataTable existe
    if (MyDataTable == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("La DataTable n'existe pas."));
        return;
    }

    // Supposons que tu as une liste de codes de pays et de chemins de textures
    TArray<FString> CountryCodes = { TEXT("US"), TEXT("FR") };
    TArray<FString> TexturePaths = { TEXT("/Game/Path/To/US_Texture"), TEXT("/Game/Path/To/FR_Texture") };

    for (int32 i = 0; i < CountryCodes.Num(); ++i)
    {
        FCountryFlagInfo NewRow;

        // Charger la texture
        NewRow.FlagTexture = LoadObject<UTexture2D>(nullptr, *TexturePaths[i]);

        // Définir le code du pays
        NewRow.CountryCode = CountryCodes[i];

        // Ajouter la nouvelle ligne à la DataTable
        MyDataTable->AddRow(FName(*CountryCodes[i]), NewRow);

        // Optionnel : Marquer la DataTable comme modifiée
        MyDataTable->MarkPackageDirty();
    }
}
