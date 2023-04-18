//https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Engine/Classes/GameFramework/PlayerController.h
/** Input axes values, accumulated each tick. */
//FRotator RotationInput;
uintptr_t NetConnection = 0x510; /** The net connection this controller is communicating on, nullptr for local players on server */
uintptr_t RotationInput = NetConnection + 0x8; //size of NetConnection (0x8)

bool memory_event(Vector3 newpos) 
{
	write<Vector3>(fn::playercontroller + RotationInput, newpos); //write Vectors to control rotation
	return true;
}


void moveto(float x, float y, int smooth)
{
	int Width = GetSystemMetrics(SM_CXSCREEN);
	int Height = GetSystemMetrics(SM_CYSCREEN);
	Vector2 center(Width / 2, Height / 2);
	Vector2 target(0, 0);

	if (x != 0)
	{
		if (x > center.x)
		{
			target.x = -(center.x - x);
			target.x /= smooth;
			if (target.x + center.x > center.x * 2)
				target.x = 0;
		}

		if (x < center.x)
		{
			target.x = x - center.x;
			target.x /= smooth;
			if (target.x + center.x < 0)
				target.x = 0;
		}
	}
	if (y != 0)
	{
		if (y > center.y)
		{
			target.y = -(center.y - y);
			target.y /= smooth;
			if (target.y + center.y > center.y * 2)
				target.y = 0;
		}

		if (y < center.y)
		{
			target.y = y - center.y;
			target.y /= smooth;
			if (target.y + center.y < 0)
				target.y = 0;
		}
	}

	if (settings::aimmode == 0) //mouse aimbot
	{
		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(target.x), static_cast<DWORD>(target.y), NULL, NULL);
	}
	if (settings::aimmode == 1) //memory aimbot
	{
		if (fn::camera::fov > 40)
		{
			memory_event(Vector3(-target.y / 5, target.x / 5, 0));
		}
		else
		{
			memory_event(Vector3(-target.y / 15, target.x / 15, 0));
		}
	}
}
