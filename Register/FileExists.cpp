#include "..\Include\Register.h"

using namespace std;

namespace Register
{
	std::vector<bool>* FileExists(const std::string& dir, const std::vector<std::string>& files)
	{
		auto result = new vector<bool>();
        // ��ȡ�ļ����������ļ���ȷ��ȫ���ɶ���д
        intptr_t hFile = 0;
        struct _finddata_t _fileInfo;
        if (_access(dir.c_str(), 0) != 0)
            throw "ע����ļ��д�ʧ�ܣ�������ע�ᣡ";
        if ((hFile = _findfirst((dir + "\\*").c_str(), &_fileInfo)) != -1)
        {
            for (auto i = files.begin(); i != files.end(); i++)
                result->push_back(false);
            do
            {
                if (!(_fileInfo.attrib & _A_SUBDIR))
                {
                    string file(_fileInfo.name);
                    transform(file.begin(), file.end(), file.begin(), ::tolower);
                    for (auto i = 0; i != files.size(); i++)
                        if (file == files[i])
                            (*result)[i] = true;
                    if (_access((dir + "\\" + file).c_str(), 6) != 0)
                        throw dir + "\\" + file + "û�ж�дȨ�ޣ�";
                }
            } while (_findnext(hFile, &_fileInfo) == 0);
            return result;
        }
	}
}