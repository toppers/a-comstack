/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014-2015 by FUJI SOFT INCORPORATED, JAPAN
 *
 *  �嵭����Ԥϡ��ʲ���(1)���(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
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
 *  $Id: os.c 13 2015-07-15 08:58:53Z fujisft-kaitori $
 */

#include "Os.h"
#include "Can.h"
#include "sysmod/serial.h"
#include "sysmod/syslog.h"
#include "sysmod/banner.h"
#include "target_serial.h"
#include "prc_sil.h"

static uint8 cur_ch = 0U;

TASK(MainTask)
{
	volatile uint32 i;
	static uint16 pre_sw = 0U;
	uint16 cur_sw;

	Can_Init(NULL_PTR);

	syslog(LOG_NOTICE, "== Can_Init ==");
	Can_SetControllerMode(0U, CAN_T_START);
//	Can_SetControllerMode(1U, CAN_T_START);

	/* SW���ֽ���� */
	cur_sw = sil_reh_mem((void *) PPR(3));
	pre_sw = cur_sw;

	while (1) {
		cur_sw = sil_reh_mem((void *) PPR(3));
		if (cur_sw != pre_sw) {
			if (cur_ch == 0U) {
				cur_ch = 1U;
			}
			else {
				cur_ch = 0U;
			}
		}
		pre_sw = cur_sw;

		/* �������� */
		for (i = 0U; i < 100000U; i++) {
		}
	}

	syslog(LOG_NOTICE, "== Call ShutdownOS ==");
	ShutdownOS(E_OK);
}

TASK(SendTask)
{
	uint32	i;
	uint8	Hth;
	static uint8 data[8] = {
		0x00U, 0x01U, 0x02U, 0x03U,
		0x04U, 0x05U, 0x06U, 0x07U
	};
	Can_PduType		send_data;

	send_data.length = 8U;
	send_data.sdu = data;
	if (cur_ch == 0U) {
		/* Controller_0 */
		send_data.swPduHandle = 3U;
		send_data.id = 0x01U;
		Hth = 3U;
	}
	else {
		/* Controller_1 */
		send_data.swPduHandle = 8U;
		send_data.id = 0x03U;
		Hth = 8U;
	}

	syslog(LOG_NOTICE, "[FCN%d] Can_Write(%d) CAN-ID:0x%x", cur_ch, Hth, send_data.id);
	for (i = 0U; i < send_data.length; i++) {
		syslog(LOG_NOTICE, "DATA[%d]:0x%x", i, send_data.sdu[i]);
		if (send_data.sdu[i] < 0xFFU) {
			send_data.sdu[i]++;
		}
	}
	Can_Write(Hth, &send_data);
	syslog(LOG_NOTICE, "");
		syslog(LOG_NOTICE, "== finished SendTask ==");

	TerminateTask();
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

void
StartupHook(void)
{
	syslog_initialize();
	syslog_msk_log(LOG_UPTO(LOG_INFO));
	InitSerial();
	print_banner();

	/*
	 * ��ĥ�ܡ��ɤ��ꡧDIP�����å�1�ݡ��Ƚ����
	 * ��ĥ�ܡ��ɤʤ���SW2�ݡ��Ƚ����
	 */
/*
	sil_wrh_mem((void *) PMC(3), sil_reh_mem((void *) PMC(3)) | 0x40U);
	sil_wrh_mem((void *) PFCE(3), sil_reh_mem((void *) PFCE(3)) & ~0x40U);
	sil_wrh_mem((void *) PFC(3), sil_reh_mem((void *) PFC(3)) & ~0x40U);
	sil_wrh_mem((void *) PM(3), sil_reh_mem((void *) PM(3)) | 0x40U);
*/
		syslog(LOG_NOTICE, "== finished StartupHook ==");
}

sint32
main(void)
{
	StartOS(MainApp);
	while (1) ;
	return(0);
}
