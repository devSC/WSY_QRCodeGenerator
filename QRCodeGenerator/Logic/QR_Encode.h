// QR_Encode.h : CQR_Encode �N���X�錾����уC���^�[�t�F�C�X��`
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

/////////////////////////////////////////////////////////////////////////////
// �萔

#import <Foundation/Foundation.h>
// ���������x��
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// �f�[�^���[�h
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// �o�[�W����(�^��)�O���[�v
#define QR_VRESION_S	0 // 1 �` 9
#define QR_VRESION_M	1 // 10 �` 26
#define QR_VRESION_L	2 // 27 �` 40

#define MAX_ALLCODEWORD	 3706 // ���R�[�h���[�h���ő�l
#define MAX_DATACODEWORD 2956 // �f�[�^�R�[�h���[�h�ő�l(�o�[�W����40-L)
#define MAX_CODEBLOCK	  153 // �u���b�N�f�[�^�R�[�h���[�h���ő�l(�q�r�R�[�h���[�h���܂�)
#define MAX_MODULESIZE	  177 // ��Ӄ��W���[�����ő�l

// �r�b�g�}�b�v�`�掞�}�[�W��
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	NSInteger ncRSBlock;		// �q�r�u���b�N��
	NSInteger ncAllCodeWord;	// �u���b�N���R�[�h���[�h��
	NSInteger ncDataCodeWord;	// �f�[�^�R�[�h���[�h��(�R�[�h���[�h�� - �q�r�R�[�h���[�h��)

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// QR�R�[�h�o�[�W����(�^��)�֘A���

typedef struct tagQR_VERSIONINFO
{
	NSInteger nVersionNo;	   // �o�[�W����(�^��)�ԍ�(1�`40)
	NSInteger ncAllCodeWord; // ���R�[�h���[�h��

	// �ȉ��z��Y���͌�������(0 = L, 1 = M, 2 = Q, 3 = H) 
	NSInteger ncDataCodeWord[4];	// �f�[�^�R�[�h���[�h��(���R�[�h���[�h�� - �q�r�R�[�h���[�h��)

	NSInteger ncAlignPoint;	// �A���C�����g�p�^�[�����W��
	NSInteger nAlignPoint[6];	// �A���C�����g�p�^�[�����S���W

	RS_BLOCKINFO RS_BlockInfo1[4]; // �q�r�u���b�N���(1)
	RS_BLOCKINFO RS_BlockInfo2[4]; // �q�r�u���b�N���(2)

} QR_VERSIONINFO, *LPQR_VERSIONINFO;

typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef BYTE* LPBYTE;
typedef const char* LPCSTR;

#define ZeroMemory(Destination,Length) memset((Destination),0,(Length))


@interface CQR_Encode : NSObject
{
    @public
    NSInteger m_nLevel;		// ���������x��
    NSInteger m_nVersion;		// �o�[�W����(�^��)
    BOOL m_bAutoExtent;	// �o�[�W����(�^��)�����g���w��t���O
    NSInteger m_nMaskingNo;	// �}�X�L���O�p�^�[���ԍ�
    NSInteger m_nSymbleSize;
    BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE]; // [x][y]
    
    @private
    NSInteger m_ncDataCodeWordBit; // �f�[�^�R�[�h���[�h�r�b�g��
    BYTE m_byDataCodeWord[MAX_DATACODEWORD]; // ���̓f�[�^�G���R�[�h�G���A
    NSInteger m_ncDataBlock;
    BYTE m_byBlockMode[MAX_DATACODEWORD];
    NSInteger m_nBlockLength[MAX_DATACODEWORD];
    NSInteger m_ncAllCodeWord; // ���R�[�h���[�h��(�q�r�������f�[�^���܂�)
    BYTE m_byAllCodeWord[MAX_ALLCODEWORD]; // ���R�[�h���[�h�Z�o�G���A
    BYTE m_byRSWork[MAX_CODEBLOCK]; // �q�r�R�[�h���[�h�Z�o���[�N
}

    -(BOOL) EncodeData:(NSInteger) nLevel nVersion:(NSInteger) nVersion bAutoExtent:(BOOL) bAutoExtent nMaskingNo:(NSInteger)nMaskingNo lpsSource:(LPCSTR) lpsSource ncSource: (NSInteger) ncSource;
    -(NSInteger) GetEncodeVersion:(NSInteger) nVersion lpsSource:(LPCSTR) lpsSource ncLength:(NSInteger) ncLength;
    -(BOOL) EncodeSourceData:(LPCSTR) lpsSource ncLength:(NSInteger) ncLength nVerGroup:(NSInteger) nVerGroup;

    -(NSInteger) GetBitLength:(BYTE) nMode ncData:(NSInteger) ncData nVerGroup:(NSInteger) nVerGroup;
    -(NSInteger)SetBitStream:(NSInteger) nIndex wData:(WORD) wData ncData:(NSInteger) ncData;

    -(BOOL) IsNumeralData:(unsigned char) c;
    -(BOOL) IsAlphabetData:(unsigned char) c;
    -(BOOL) IsKanjiData:(unsigned char) c1 c2:(unsigned char) c2;

    -(BYTE) AlphabetToBinaly:(unsigned char) c;
    -(WORD) KanjiToBinaly:(WORD) wc;

    -(void) GetRSCodeWord:(LPBYTE)lpbyRSWork ncDataCodeWord:(NSInteger)ncDataCodeWord ncRSCodeWord:(NSInteger) ncRSCodeWord;
	-(void) FormatModule;
	-(void) SetFunctionModule;
    -(void) SetFinderPattern:(NSInteger)x y:(NSInteger)y;
    -(void) SetAlignmentPattern:(NSInteger)x y:(NSInteger)y;
	-(void) SetVersionPattern;
	-(void) SetCodeWordPattern;
    -(void) SetMaskingPattern:(NSInteger) nPatternNo;
    -(void) SetFormatInfoPattern:(NSInteger) nPatternNo;
	-(NSInteger) CountPenalty;
@end
