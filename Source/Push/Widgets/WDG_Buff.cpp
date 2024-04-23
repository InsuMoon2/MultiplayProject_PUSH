#include "Widgets/WDG_Buff.h"

void UWDG_Buff::SetBuffUI(UTexture2D* image, float* playTime, float* lifeTime)
{
	UIImage = image;
	PlayTime = playTime;
	LifeTime = lifeTime;
}

void UWDG_Buff::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!LifeTime || !PlayTime)
		return;

	TimePercent =  *PlayTime / *LifeTime;
}
