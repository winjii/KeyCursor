# include <Siv3D.hpp> // OpenSiv3D v0.1.7
#include "KeyCursor.h"

void Main()
{
	Circle c;
	KeyCursor::KeyCursor cursor(Window::Size()/2);
	Window::Resize(Size(1280, 720));
	Graphics::SetBackground(Palette::White);
	int score = 0;
	Stopwatch sw;
	Font font(30);
	Vec2 lastPos = cursor.getPos();
	RectF rect(Vec2(0, 25), Vec2(Window::Width(), Window::Height() - 25));
	while (System::Update()) {
		cursor.update();
		Color color = Palette::Black;
		if (!sw.isRunning()) {
			if (KeySpace.down()) {
				c = Circle(RandomVec2(rect), 10);
				score = 0;
				sw.start();
			}
		}
		else if (sw.isRunning() && (KeySpace.down() || sw.elapsed().count() > 20*1000)) {
			sw.reset();
		}
		else if (sw.isRunning()) {
			if (c.intersects(Line(lastPos, cursor.getPos()))) {
				c = Circle(RandomVec2(rect), 10);
				score++;
			}
			color = Palette::Red;
			c.draw(Palette::Red);
		}
		font(L"スペースキーで開始/停止").draw(Arg::topCenter(Vec2(Window::Width()/2, 0)), Palette::Black);
		font(sw.format()).draw(Arg::topLeft(20, 20), color);
		font(score).draw(Arg::topRight(Vec2(Window::Width() - 50, 20)), color);
		lastPos = cursor.getPos();
	}
}
