#include "KeyCursor.h"

namespace KeyCursor {


KeyCursor::KeyCursor(const DevicePos &pos) : _pos(pos), _lastV(0, 0) {}

void KeyCursor::update() {
	Point l(0, 0), r(0, 0);
	if (KeyE.pressed()) l.y--;
	if (KeyS.pressed()) l.x--;
	if (KeyD.pressed()) l.y++;
	if (KeyF.pressed()) l.x++;
	if (KeyI.pressed()) r.y--;
	if (KeyJ.pressed()) r.x--;
	if (KeyK.pressed()) r.y++;
	if (KeyL.pressed()) r.x++;
	bool validInput = true;
	if ((l + r).isZero()) validInput = false;
	Vec2 vl(l), vr(r);
	double multiplier = 2.0;
	if (!l.isZero() && !r.isZero()) multiplier *= 1.5;
	if (!vl.isZero()) vl.normalize();
	if (!vr.isZero()) vr.normalize();
	Vec2 v;
	if (validInput) {
		Vec2 end = (vl + vr)*multiplier;
		Vec2 diff(end - _lastV);
		if (diff.length() < 1e-3) v = end;
		else v = _lastV + diff.normalized()*std::min(114514.0, diff.length());
		_pos += v*multiplier;
		_lastV = v;
	}
	else {
		v = _lastV = Vec2(0, 0);
	}
	Circle(_pos, 4).draw(Palette::Black);
	//Line(_pos, _pos + vl*15*multiplier).drawArrow(2, Vec2(5, 5), Palette::Lightblue);
	//Line(_pos, _pos + vr*15*multiplier).drawArrow(2, Vec2(5, 5), Palette::Orange);
	_locus.drawCatmullRom(1, Palette::Gray);
	if (validInput) {
		Line(_pos, _pos + v*15).drawArrow(4, Vec2(8, 8), Palette::Darkgray);
	}
	_locus.push_front(_pos);
	while (_locus.size() > 20) _locus.pop_back();
}

DevicePos KeyCursor::getPos() const {
	return _pos;
}


}