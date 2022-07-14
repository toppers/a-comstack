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
 *  $Id: os.c 599 2014-10-17 01:27:58Z shigihara $
 */

#include "Os.h"
#include "Can.h"
#include "t_syslog.h"
#include "prc_sil.h"

#define SW_BASE		0x08000410
#define KEY_BASE	0x08000400
#define KEY_0		0x01
#define KEY_1		0x02
#define KEY_2		0x04
#define KEY_3		0x08

TASK(MainTask){
	volatile uint32 i;
	uint8			Hth;
	uint32			cur_key;
	uint8			data[8] = {
		0x00U, 0x01U, 0x02U, 0x03U,
		0x04U, 0x05U, 0x06U, 0x07U
	};
	static uint32	pre_key = 0xFFFF;
	Can_PduType		send_data;

	Can_Init(NULL_PTR);

	Can_SetControllerMode(0U, CAN_T_START);

	syslog(LOG_NOTICE, "");
	syslog(LOG_NOTICE, "== Can_Init ==");
	syslog(LOG_NOTICE, "");

	while (1) {
		cur_key = sil_rew_iop((void *) KEY_BASE);

		send_data.length = 8U;
		send_data.sdu = data;

		/* �ܥ��󲡲����֤����ܤ������Τ߽�����Ԥ� */
		if (((pre_key & KEY_0) != 0) && ((cur_key & KEY_0) == 0)) {
			send_data.swPduHandle = 4U;
			send_data.id = 0x00U;
			Hth = 4U;
			syslog(LOG_NOTICE, "[KEY0] Can_Write(%d) CAN-ID:0x%x", Hth, send_data.id);
			for (i = 0U; i < send_data.length; i++) {
				syslog(LOG_NOTICE, "DATA[%d]:0x%x", i, send_data.sdu[i]);
			}
			Can_Write(Hth, &send_data);
			syslog(LOG_NOTICE, "");
		}
		else if (((pre_key & KEY_1) != 0) && ((cur_key & KEY_1) == 0)) {
			send_data.swPduHandle = 5U;
			send_data.id = 0x01U;
			Hth = 5U;
			syslog(LOG_NOTICE, "[KEY1] Can_Write(%d) CAN-ID:0x%x", Hth, send_data.id);
			for (i = 0U; i < send_data.length; i++) {
				syslog(LOG_NOTICE, "DATA[%d]:0x%x", i, send_data.sdu[i]);
			}
			Can_Write(Hth, &send_data);
			syslog(LOG_NOTICE, "");
		}
		else if (((pre_key & KEY_2) != 0) && ((cur_key & KEY_2) == 0)) {
			send_data.swPduHandle = 6U;
			send_data.id = 0x02U;
			Hth = 6U;
			syslog(LOG_NOTICE, "[KEY2] Can_Write(%d) CAN-ID:0x%x", Hth, send_data.id);
			for (i = 0U; i < send_data.length; i++) {
				syslog(LOG_NOTICE, "DATA[%d]:0x%x", i, send_data.sdu[i]);
			}
			Can_Write(Hth, &send_data);
			syslog(LOG_NOTICE, "");
		}
		else if (((pre_key & KEY_3) != 0) && ((cur_key & KEY_3) == 0)) {
			send_data.swPduHandle = 7U;
			send_data.id = 0x03U;
			Hth = 7U;
			syslog(LOG_NOTICE, "[KEY3] Can_Write(%d) CAN-ID:0x%x", Hth, send_data.id);
			for (i = 0U; i < send_data.length; i++) {
				syslog(LOG_NOTICE, "DATA[%d]:0x%x", i, send_data.sdu[i]);
			}
			Can_Write(Hth, &send_data);
			syslog(LOG_NOTICE, "");
		}

		pre_key = cur_key;

		/* �������� */
		for (i = 0U; i < 100000U; i++) {
		}
	}

	ShutdownOS(E_OK);
}

boolean
CanCalloutFunction(uint8 Hrh, Can_IdType CanId, uint8 CanDlc, const uint8 *CanSduPtr)
{
	uint8 i;

	syslog(LOG_NOTICE, "CanCalloutFunction:Hrh = 0x%x, CanId = 0x%x, CanDlc = 0x%x", Hrh, CanId, CanDlc);

	for (i = 0U; i < CanDlc; i++) {
		syslog(LOG_NOTICE, "CanCalloutFunction:CanSduPtr[%d] = 0x%x", i, CanSduPtr[i]);
	}

	return(TRUE);
}

ProtectionReturnType
ProtectionHook(StatusType FatalError)
{
	syslog(LOG_NOTICE, "## ProtectionHook is called !! (%d)", FatalError);

	return(PRO_SHUTDOWN);
}

sint32
main(void)
{
	StartOS(MainApp);
	while (1) ;
	return(0);
}
