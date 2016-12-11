/************************************************************************/
/* 
arthur:		cqf
date:		20161208
version:	1.0
brief��		ʵ������
*/
/***********************************************************************/

#ifndef __ENTITY_PROP__
#define __ENTITY_PROP__


#define  INVALID_PROP_VALUE  -1  	// �Ƿ�����ֵ

#define  INVALID_RULE_VALUE  -1		// �Ƿ���������ֵ

#define	 INVALID_MAX_VALUE	4294967295	// 32λ�������ֵ

// ʵ������
enum EEntityProp
{
	CREATURE_PROP_PDBID = 1,		//	��ɫPDBID 

	///////////////////////////////////
	CREATURE_PROP_MAX,				//  ��ǰ��������ֵ����������ֵ���ó���������
};

// ��������
enum EEntityRuleProp{
	CREATURE_RULE_ID = 1,			//	����ID , ����
	CREATURE_RULE_PDBID,		//	��ɫPDBID 
	CREATURE_RULE_TURN_FREE,		//  �Ƿ��ֿ�һ��, Ĭ�ϲ��ֿ�
	CREATURE_RULE_QUESTION,			//	������һ����ǰ����Ľ������߳ͷ�
	CREATURE_RULE_FOOT_RED,			//	�ȵ����ף�ԭ�����ˣ��ֿ�����
	CREATURE_RULE_YELLOW_STAR,		//  �������ǣ�֮���ܹ������أ��ȵ�������Ч��������
	CREATURE_RULE_RED_DOUBLESTAR,	//  ��˫�ǣ��ȵ��Է������ø��Ѽӱ�������������Ч
	CREATURE_RULE_FOOT_BLUE,		//  ��ѽ���ȿ��ˣ�ԭ����Ϣ
	CREATURE_RULE_BLUE_STAR,		//	�������ǣ�֮�����۹���ʲô���ض���ѣ��ȵ������ӱ�����������Ч
	CREATURE_RULE_BLUE_DOUBLESTAR,	//	��˫�ǣ��ȵ��Է�������ѣ�����������Ч

	///////////////////////////////////
	CREATURE_RULE_MAX,				//  ��ǰ��������ֵ����������ֵ���ó���������
};


#endif