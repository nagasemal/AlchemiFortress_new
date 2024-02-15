#include "pch.h"
#include "BinaryFile.h"

#include <fstream>
#include <assert.h>


BinaryFile BinaryFile::LoadFile(const wchar_t* fileName)
{
	BinaryFile bin;

	std::ifstream ifs;

	// �t�@�C���I�[�v��
	ifs.open(fileName, std::ios::in | std::ios::binary);

	// �ǂݍ��ݎ��s���A�����I��
	assert(ifs);

	// �t�@�C���T�C�Y���擾
	ifs.seekg(0, std::fstream::end);
	std::streamoff eofPos = ifs.tellg();
	ifs.clear();
	ifs.seekg(0, std::fstream::beg);
	std::streamoff begPos = ifs.tellg();
	bin.m_size = (unsigned int)(eofPos - begPos);

	// �ǂݍ��ނ��߂̃��������m��
	bin.m_data.reset(new char[bin.m_size]);

	// �t�@�C���擪����o�b�t�@�փR�s�[ 
	ifs.read(bin.m_data.get(), bin.m_size);

	// �t�@�C���N���[�Y
	ifs.close();

	return bin;
}

BinaryFile::BinaryFile() noexcept
{
	m_size = 0;
}

BinaryFile::BinaryFile(BinaryFile&& in) noexcept
{
	m_data = std::move(in.m_data);
	m_size = in.m_size;
}