/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2013-2014 by Center for Embedded Computing Systems
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2013-2014 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2013-2014 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2014 by Witz Corporation, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  $Id: Can_GeneralTypes.h 13 2015-07-15 08:58:53Z fujisft-kaitori $
 */

/* [CAN439] ���󥯥롼�ɥ����� */
#ifndef CAN_GENERAL_TYPES
#define CAN_GENERAL_TYPES

/*
 * [CAN436] �ܥե�����ˤϡ�Can��CanIf��CanTrcv�Ƕ���Ū�˻��Ѥ����ǡ�����������򵭽Ҥ���
 * [CAN437] Can�⥸�塼��Υ���ƥ��졼�����ܥե�������󶡤���
 * [CAN438] �ܥե�����ˤϡ�CanIf�⥸�塼��ǵ��ꤵ�줿�ǡ������������ޤ�
 * [CAN440] ʣ�������CAN�ɥ饤�Ф���Ѥ�����⡤1�Ĥ�Can_GeneralTypes.h����inlcude����
 */

/* [CAN416] STANDARD�Τߥ��ݡ��Ȥ��� */
typedef uint16 Can_IdType;

/* [CAN429] 8�ӥåȸ���Ȥ��� */
typedef uint8 Can_HwHandleType;

/* [CAN415] CAN PDU��¤�� */
typedef struct {
	PduIdType	swPduHandle;
	uint8		length;
	Can_IdType	id;
	uint8		*sdu;
} Can_PduType;

/* [CAN417] CAN����ȥ������ */
typedef enum {
	CAN_T_START,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

/* [CAN039] CAN�ɥ饤��ɸ������� */
typedef enum {
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

/* [CT�����б�] ɬ�פʷ����Ѱդ��� */
typedef enum {
	CANTRCV_TRCVMODE_NORMAL,
	CANTRCV_TRCVMODE_SLEEP,
	CANTRCV_TRCVMODE_STANDBY
} CanTrcv_TrcvModeType;

typedef enum {
	CANTRCV_WU_ERROR,
	CANTRCV_WU_BY_BUS,
	CANTRCV_WU_BY_PIN,
	CANTRCV_WU_INTERNALLY,
	CANTRCV_WU_NOT_SUPPORTED,
	CANTRCV_WU_POWER_ON,
	CANTRCV_WU_RESET,
	CANTRCV_WU_BY_SYSERR,
} CanTrcv_TrcvWakeupReasonType;

typedef enum {
	CANTRCV_WUMODE_ENABLE,
	CANTRCV_WUMODE_CLEAR,
	CANTRCV_WUMODE_DISABLE
} CanTrcv_TrcvWakeupModeType;

/* [#36]���ǡ����������ޥ��� */
#define CAN_MAX_DLC		8U

#endif /* CAN_GENERAL_TYPES */
