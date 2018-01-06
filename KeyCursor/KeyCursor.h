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

public:

	KeyCursor(const DevicePos &pos);
	
	void update();

	DevicePos getPos() const;
};


}