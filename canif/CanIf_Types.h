/*
 *  TOPPERS/A-CANIF
 *      Automotive CANIF
 *
 *  Copyright (C) 2013-2015 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2014-2015 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2013-2015 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2014-2015 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2015 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2014-2015 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2015 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2013-2015 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2015 by Witz Corporation
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
 *  $Id: CanIf_Types.h 1241 2015-03-25 07:26:02Z panasonic-ayane $
 */

#ifndef CANIF_TYPES_H
#define CANIF_TYPES_H

#include "ComStack_Types.h"     /* [CANIF643] */
#include "Can_GeneralTypes.h"   /* [CANIF142] */

typedef enum {
	CANIF_CS_UNINIT = 0,
	CANIF_CS_SLEEP = 1,
	CANIF_CS_STARTED = 2,
	CANIF_CS_STOPPED = 3
} CanIf_ControllerModeType;

typedef enum {
	CANIF_SET_OFFLINE = 0,
	CANIF_SET_ONLINE = 1,
	CANIF_SET_RX_OFFLINE = 2,
	CANIF_SET_RX_ONLINE = 3,
	CANIF_SET_TX_OFFLINE = 4,
	CANIF_SET_TX_OFFLINE_ACTIVE = 5,
	CANIF_SET_TX_ONLINE = 6
} CanIf_PduSetModeType;

typedef enum {
	CANIF_GET_OFFLINE = 0,
	CANIF_GET_OFFLINE_ACTIVE = 1,
	CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE = 2,
	CANIF_GET_ONLINE = 3,
	CANIF_GET_RX_ONLINE = 4,
	CANIF_GET_TX_ONLINE = 5
} CanIf_PduGetModeType;

typedef enum {
	CANIF_NO_NOTIFICATION = 0,
	CANIF_TX_RX_NOTIFICATION = 1
} CanIf_NotifStatusType;

#endif /* CANIF_TYPES_H */
