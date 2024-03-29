#include "TextManager.h"
#include "Game.h"

TextManager* TextManager::s_pInstance = nullptr;

// 텍스트 초기화
bool TextManager::InitFont(const char* fontFile, int fontSize)
{
	if (TTF_Init() < 0) { printf("오류: 폰트를 초기화할 수 없습니다. (%s)\n", TTF_GetError()); return false; }
	m_pFont = TTF_OpenFont(fontFile, fontSize);
	if (m_pFont == NULL) { printf("오류: 폰트를 열 수 없습니다. (%s)\n", TTF_GetError()); return false; }

	return true;
}

// int형 텍스트 갱신하는 함수
void TextManager::RefreshIntText(Text* text, SDL_Color fgColor, SDL_Color bgColor, int contents)
{
	text->FreeTexture();

	SDL_Texture* t_texture;
	char tempContents[128]; // 윈도우 전용
	sprintf_s(tempContents, sizeof(tempContents), "%4d", contents); // 윈도우 전용

	SDL_Surface* t_textSurface = TTF_RenderText_Blended(m_pFont, tempContents, fgColor);
	t_texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), t_textSurface);
	SDL_FreeSurface(t_textSurface);

	text->SetTexture(t_texture);
}

// int형 텍스트를 Text 오브젝트로 반환
Text* TextManager::LoadIntToText(SDL_Color fgColor, SDL_Color bgColor, int x, int y, int width, int height, int contents, bool isUI)
{
	SDL_Texture* t_texture;
	char tempContents[128]; // 윈도우 전용
	sprintf_s(tempContents, sizeof(tempContents), "%4d", contents); // 윈도우 전용

	SDL_Surface* t_textSurface = TTF_RenderText_Blended(m_pFont, tempContents, fgColor);

	if (t_textSurface == 0) return 0;

	t_texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), t_textSurface);
	SDL_FreeSurface(t_textSurface);

	if (t_texture == 0) return 0;

	Text* tempText = new Text(x, y, width, height, isUI);
	tempText->SetTexture(t_texture);

	return tempText;
}

// 한글이 가능한 텍스트 불러오기 함수
bool TextManager::LoadHanguelText(SDL_Color fgColor, SDL_Color bgColor, int x, int y, int width, int height, const wchar_t* textContents, bool isUI)
{
	SDL_Texture* t_texture;
	SDL_Surface* t_textSurface = TTF_RenderUNICODE_Shaded(m_pFont, (Uint16*)textContents, fgColor, bgColor);

	if (t_textSurface == 0) return false;

	t_texture = SDL_CreateTextureFromSurface(TheGame::Instance()->getRenderer(), t_textSurface);
	SDL_FreeSurface(t_textSurface);

	if (t_texture == 0) return false;

	Text* tempText = new Text(x, y, width, height, isUI);
	tempText->SetTexture(t_texture);
	TheGame::Instance()->CreateText(tempText);

	return true;
}

// 삭제
void TextManager::clean()
{
	TTF_CloseFont(m_pFont);
	TTF_Quit();

	delete s_pInstance;
	s_pInstance = nullptr;
}