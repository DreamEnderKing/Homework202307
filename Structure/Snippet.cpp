#include "..\Include\Structure.h"

using namespace Structure;

const std::string __Snippet__::to_b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void __Snippet__::MyDebugError(std::string message)
{
	std::cout << message << std::endl;
}

std::string __Snippet__::EncodeBase64(std::string content)
{
	std::string result = "";
	int i = 0, j = 0, len = content.size(), index = 0;
	unsigned char undealed[3] = { 0 }, dealed[4] = { 0 };

	while (len)
	{
		undealed[i] = content[index];
		index++, i++;
		if (i == 3)
		{
			dealed[0] = (undealed[0] & 0xFC) >> 2;
			dealed[1] = ((undealed[0] & 0x03) << 4) + ((undealed[1] & 0xF0) >> 4);
			dealed[2] = ((undealed[1] & 0x0F) << 2) + ((undealed[2] & 0xC0) >> 6);
			dealed[3] = undealed[2] & 0x3F;
			for (i = 0; i < 4; i++)
				result += to_b64[dealed[i]];
			i = 0;
		}
		len--;
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			undealed[j] = '\0';
		dealed[0] = (undealed[0] & 0xFC) >> 2;
		dealed[1] = ((undealed[0] & 0x03) << 4) + ((undealed[1] & 0xF0) >> 4);
		dealed[2] = ((undealed[1] & 0x0F) << 2) + ((undealed[2] & 0xC0) >> 6);
		for (j = 0; j < i + 1; j++)
			result += to_b64[dealed[j]];
		while (i < 3)
			result += '=', i++;
	}
	return result;
}

std::string __Snippet__::DecodeBase64(std::string content)
{
	size_t in_len = content.size();
	int i = 0, j = 0, index = 0;
	unsigned char undealed[4] = { 0 }, dealed[3] = { 0 };
	std::string result = "";

	while (in_len && (content[index] != '='))
	{
		undealed[i] = content[index];
		i++, index++;

		if (i == 4)
		{
			for (i = 0; i < 4; i++)
				undealed[i] = to_b64.find(undealed[i]) & 0xFF;
			dealed[0] = ((undealed[0]) << 2) + ((undealed[1] & 0x30) >> 4);
			dealed[1] = ((undealed[1] & 0x0F) << 4) + ((undealed[2] & 0x3C) >> 2);
			dealed[2] = ((undealed[2] & 0x03) << 6) + undealed[3];
			for (i = 0; i < 3; i++)
				result += dealed[i];
			i = 0;
		}
		in_len--;
	}

	if (i)
	{
		for (j = 0; j < i; j++)
			undealed[j] = to_b64.find(undealed[j]) & 0xFF;
		dealed[0] = ((undealed[0]) << 2) + ((undealed[1] & 0x30) >> 4);
		dealed[1] = ((undealed[1] & 0x0F) << 4) + ((undealed[2] & 0x3C) >> 2);
		dealed[2] = 0;
		for (j = 0; j < i - 1; j++)
			result += dealed[j];
	}
	return result;
}
