#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor3.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;

/**
 * @class ADoorActor3
 * @brief Oyuncuya yaklsinca acilan, uzaklasinca kapanan kapi aktoru.
 *
 * Bu sinif, bir kapi cercevesi, doner kapi kanadi ve tetikleme kutusu icerir.
 * Oyuncu tetikleme alanina girdiginde kapi acilir, ciktiginda kapanir.
 */

UCLASS()
class DOOR_API ADoorActor3 : public AActor
{
    GENERATED_BODY()

public:
    /** @brief Varsayilan kurucu fonksiyon */
    ADoorActor3();

protected:
    /** @brief Oyun basladiginda cagrilir */
    virtual void BeginPlay() override;

public:
    /** @brief Her karede calisir, kapi rotasyonunu gunceller */
    virtual void Tick(float DeltaTime) override;

    // Bilesenler
     /** @name Bilesenler */
    /// @{
    /** @brief Aktorun kok bileseni */
    UPROPERTY(EditAnywhere, Category = "Door")
    USceneComponent* RootComp;

    /** @brief Kapi cercevesi (statik mesh) */
    UPROPERTY(EditAnywhere, Category = "Door")
    UStaticMeshComponent* DoorFrame;

    /** @brief Kapi kanadi (doner mesh) */
    UPROPERTY(EditAnywhere, Category = "Door")
    UStaticMeshComponent* DoorMesh;

    /** @brief Kapiyi tetikleyen kutu bileseni */
    UPROPERTY(EditAnywhere, Category = "Door")
    UBoxComponent* TriggerBox;
    /// @}

     /** @name Ayarlar */
    /// @{
    /** @brief Kapinin acilacagi aci (derece) */
    UPROPERTY(EditAnywhere, Category = "Door")
    float OpenAngle = 90.f;

    /** @brief Kapinin acilip kapanma hizini belirler */
    UPROPERTY(EditAnywhere, Category = "Door")
    float InterpSpeed = 4.f;
    /// @}

private:

    /** @brief Mevcut kapi yaw acisi */
    float CurrentYaw;

    /** @brief Hedef kapi yaw acisi */
    float TargetYaw;

    /** @brief Kapinin acilmak isteyip istemedigi durumu */
    bool bWantsOpen;

    /**
    * @brief Tetikleme alanina giris olayi
    * @param OverlappedComp [in] cakisan bilesen
    * @param OtherActor [in] Tetiklemeyi baslatan aktor
    * @param OtherComp [in] Diger aktorun bileseni
    * @param OtherBodyIndex [in] cakisma indeks numarasi
    * @param bFromSweep [in] Sweep testi sonucu mu
    * @param SweepResult [in] Sweep sonucu carpisma bilgisi
    */
    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    /**
    * @brief Tetikleme alanindan cikis olayi
    * @param OverlappedComp [in] cakisan bilesen
    * @param OtherActor [in] Tetiklemeyi baslatan aktor
    * @param OtherComp [in] Diger aktorun bileseni
    * @param OtherBodyIndex [in] cakisma indeks numarasi
    */
    UFUNCTION()
    void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
