#include "Widgets/WDG_BuffBoard.h"

void UWDG_BuffBoard::NativeConstruct()
{
	Super::NativeConstruct();
	RemoveChildDelegate.BindUFunction(this, "OnRemoveChild");
}

void UWDG_BuffBoard::SubWidget(UWDG_Buff* widget)
{
	RemoveChildDelegate.Execute(widget);
}
