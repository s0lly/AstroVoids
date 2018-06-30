#include "RetroContent.h"

void RetroContent::DrawString(Graphics& gfx, std::string word, Vec2 loc, int size, Color c)
{
	int offsetX = -((word.length() * size * fontWidth + (word.length() - 1) * fontPadding) / 2);

	for (int i = 0; i < word.length(); i++)
	{
		for (int y = 0; y < fontHeight; y++)
		{
			for (int x = 0; x < fontWidth; x++)
			{
				if (word[i] >= 65 && word[i] <= 90)
				{
					if (letters[word[i] - 65][y * fontWidth + x] == 1)
					{
						gfx.PutRect(offsetX + loc.x + i * (fontPadding + fontWidth * size) + x * size, loc.y + y * size, size, size, c);
					}
				}

				if (word[i] >= 32 && word[i] <= 32)
				{
					if (otherText[word[i] - 32][y * fontWidth + x] == 1)
					{
						gfx.PutRect(offsetX + loc.x + i * (fontPadding + fontWidth * size) + x * size, loc.y + y * size, size, size, c);
					}
				}

				if (word[i] >= 48 && word[i] <= 57)
				{
					if (numbers[word[i] - 48][y * fontWidth + x] == 1)
					{
						gfx.PutRect(offsetX + loc.x + i * (fontPadding + fontWidth * size) + x * size, loc.y + y * size, size, size, c);
					}
				}

			}
		}
	}

}
