#pragma once
/// Boyer-Moore-Horspool Algorithm
/// Copyright (C) Flaviu Cibu. All rights reserved.
/// Created 27-may-2007
/// Updated 19-mar-2018

namespace stdext
{
	namespace bmh
	{
		template <const unsigned jumpTableLength, typename C, typename Length>
		void set_jump_table(Length* const jumpTable, const C* const pattern, const Length patternLength)
		{
			for (Length i = jumpTableLength - 1; i > 0; --i)
			{
				jumpTable[i] = patternLength;
			}

			jumpTable[0] = patternLength;
			for (Length i = 0; i < patternLength; ++i)
			{
				jumpTable[pattern[i]] -= i + 1;
			}
		}

		template <typename C, typename Length>
		const C* find(const C* const pattern, const Length patternLength, const C* const text, const C* const textEnd, const Length* const jumpTable)
		{
			const C* const patternEnd = pattern + patternLength;
			const C* patternPtr = patternEnd - 1;
			for (const C* textPtr = text + patternLength - 1; textPtr < textEnd; )
			{
				if (*textPtr == *patternPtr)
				{
					do
					{
						if (patternPtr == pattern)
						{
							return textPtr;
						}
					} 
					while (*--textPtr == *--patternPtr);

					const Length jump1 = Length(patternEnd - patternPtr);
					const Length jump2 = jumpTable[*textPtr];
					patternPtr = patternEnd - 1;
					textPtr += (jump1 > jump2) ? jump1 : jump2;
				}
				else
				{
					textPtr += jumpTable[*textPtr];
					textPtr += jumpTable[*textPtr];
					textPtr += jumpTable[*textPtr];
				}
			}

			return 0;
		}
	}
}
