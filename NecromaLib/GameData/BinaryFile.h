#pragma once
class BinaryFile
{
public:

	// �t�@�C�������w�肵�ă��[�h
	static BinaryFile LoadFile(const wchar_t* fileName);

	// ���[�u�R���X�g���N�^
	BinaryFile(BinaryFile&& in)noexcept;

	BinaryFile() noexcept;

	// �A�N�Z�T
	char* GetData() { return m_data.get(); }
	unsigned int GetSize() { return m_size; }

private:

	// �f�[�^
	std::unique_ptr<char[]> m_data;

	// �T�C�Y
	unsigned int m_size;

};