#include "Label.h"
#include "GameGlobal.h"


Label::Label(string s, int w, int h,D3DXVECTOR2 position, D3DCOLOR color)
{
	m_string = s;
	D3DXCreateFont(GameGlobal::GetCurrentDevice()
		, w, h
		, FW_NORMAL, 1
		, false, DEFAULT_CHARSET
		, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, (LPCWSTR) "Arial", &my_font);


	my_rect.left = position.x;
	my_rect.top =position.y;
	my_rect.bottom = my_rect.top + 500;
	my_rect.right = my_rect.left + 500;

	my_color = color;
}

Label::~Label()
{
}

Label::Label()
{
}

void Label::Update(float dt)
{
}

void Label::Draw(string s)
{
	if(s._Equal(""))
	my_font->DrawTextA(GameGlobal::GetCurrentSpriteHandler(), m_string.c_str(), -1, &my_rect, DT_LEFT,my_color);
	else 	my_font->DrawTextA(GameGlobal::GetCurrentSpriteHandler(), s.c_str(), -1, &my_rect, DT_LEFT, my_color);
}
