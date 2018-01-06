#pragma once
#include <Siv3D.hpp>
#include <queue>

namespace KeyCursor {


using DevicePos = Vec2;


class KeyCursor {
private:

	DevicePos _pos;

	Vec2 _lastV;

	LineString _locus;

	Vec2 _leftStickDir, _rightStickDir;

public:

	KeyCursor(const DevicePos &pos);
	
	void update();

	Vec2 leftStickDir() const;

	Vec2 rightStickDir() const;

	DevicePos getPos() const;
};


}