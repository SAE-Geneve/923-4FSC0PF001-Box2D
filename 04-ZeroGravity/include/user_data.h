#pragma once

enum class UserDataType
{
    BALL,
    LIMIT,
    BOUNCER,
    NONE
};

struct UserData
{
	// ReSharper disable once CppInconsistentNaming : stick to Box2D API
	UserDataType userData = UserDataType::NONE;
};
