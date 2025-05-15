//https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Engine/Classes/GameFramework/PlayerController.h
/** Input axes values, accumulated each tick. */
//FRotator RotationInput;
uintptr_t NetConnection_Offset = 0x518; /** The net connection this controller is communicating on, nullptr for local players on server */
uintptr_t RotationInput_Offset = NetConnection + sizeof(uintptr_t); //size of NetConnection (0x8)

bool memory_event(FVector newpos) 
{
	return write<FVector>(AController + RotationInput_Offset, newpos); //write Vectors to control rotation
}


void moveto(float x, float y, int smooth)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    FVector2D center(screenWidth / 2, screenHeight / 2);

    FVector delta((x - center.x) / smooth, (y - center.y) / smooth);

    // X Limit
    if (x != 0 && (delta.x + center.x < 0 || delta.x + center.x > screenWidth))
        delta.x = 0;

    // Y Limit
    if (y != 0 && (delta.y + center.y < 0 || delta.y + center.y > screenHeight))
        delta.y = 0;

    memory_event(FVector(-delta.y / 5.0f, delta.x / 5.0f, 0)); // You better to implement pixels to deg calculation instead of "x / 5.0f"
}
