/*
 *  TOPPERS/A-COM
 *      Automotive COM
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
 *  $Id: os.c 425 2014-09-17 00:46:01Z fsi-dankei $
 */

#include "Os.h"
#include "Com.h"
#include "t_syslog.h"
#include "sysmod/serial.h"
#include "sysmod/banner.h"
#include "histogram.h"
#include "target_timer.h"

#define LOOP_COUNT	10000U
#define MAX_TIME	3000U

/*
 *  �¹Ի���ʬ�ۤ�Ͽ��������ΰ�
 */
static uint32	histarea[MAX_TIME + 1];

const uint8		signal_type_info[84] = {
	COM_SINT8, COM_SINT16, COM_BOOLEAN, COM_UINT32, COM_UINT32, COM_UINT8, COM_UINT16, COM_UINT16, COM_SINT32, COM_SINT8, COM_SINT16, COM_BOOLEAN, COM_UINT32, COM_UINT32, COM_UINT8, COM_UINT16, COM_UINT16, COM_SINT32, COM_UINT16, COM_SINT16, COM_UINT32, COM_SINT32, COM_UINT8, COM_SINT8, COM_UINT16, COM_UINT32, COM_BOOLEAN, COM_UINT16, COM_SINT16, COM_UINT32, COM_SINT32, COM_UINT8, COM_SINT8, COM_UINT16, COM_UINT32, COM_BOOLEAN, COM_SINT32, COM_UINT8, COM_UINT16, COM_UINT16, COM_BOOLEAN, COM_UINT16, COM_SINT16, COM_UINT32, COM_SINT8, COM_UINT8, COM_UINT16, COM_UINT32, COM_SINT16, COM_UINT16, COM_SINT8, COM_SINT32, COM_UINT32, COM_UINT8_N, COM_BOOLEAN, COM_SINT8, COM_UINT8, COM_SINT32, COM_UINT32, COM_SINT16, COM_UINT16, COM_UINT16, COM_UINT32, COM_BOOLEAN, COM_UINT8_N, COM_UINT8_N, COM_UINT8, COM_SINT32, COM_UINT32, COM_SINT16, COM_UINT16, COM_UINT16, COM_UINT32, COM_BOOLEAN, COM_SINT8, COM_UINT8_N, COM_UINT8, COM_BOOLEAN, COM_BOOLEAN, COM_FLOAT32, COM_FLOAT64, COM_BOOLEAN, COM_UINT8_N, COM_UINT8
};

TASK(MainTask)
{
	uint8				ercd;
	volatile uint32		i, j, k, loop;
	Com_IpduGroupVector vector_on, vector_off;
	boolean				signal_boolean = TRUE;
	sint8				signal_sint8 = 10;
	sint16				signal_sint16 = -100;
	sint32				signal_sint32 = 1000;
	uint8				signal_uint8 = 10U;
	uint16				signal_uint16 = 100U;
	uint32				signal_uint32 = 1000U;
	float32				signal_float32 = 15.2F;
	float64				signal_float64 = -15.2F;
	uint8				signal_uint8n[10] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	};

	syslog(LOG_NOTICE, "== measure overhead ==");
	init_hist(1, MAX_TIME, histarea);
	for (i = 0; i < LOOP_COUNT; i++) {
		begin_measure(1);
		end_measure(1);
	}
	print_hist(1);

	syslog(LOG_NOTICE, "== 100us test ==");
	init_hist(1, MAX_TIME, histarea);
	loop = 179;
	for (i = 0; i < LOOP_COUNT; i++) {
		begin_measure(1);
		for (j = 0; j < loop; j++) {
		}
		end_measure(1);
	}
	print_hist(1);
/*
    syslog(LOG_NOTICE, "== 10s test start ==");
    loop = 179 * 100000;
    for (j = 0; j < loop; j++) {
    }
    syslog(LOG_NOTICE, "== 10s test end ==");
    ShutdownOS(E_OK);
 */

	//Com_Init(&com_config[0]);
	Com_Init(NULL_PTR);
	Com_SetIpduGroup(vector_on, 0, TRUE);
	Com_SetIpduGroup(vector_off, 0, FALSE);

	syslog(LOG_NOTICE, "== Com_IpduGroupControl  ==");
	init_hist(1, MAX_TIME, histarea);
	for (i = 0; i < LOOP_COUNT; i++) {
		begin_measure(1);
		Com_IpduGroupControl(vector_on, TRUE);
		end_measure(1);
		Com_IpduGroupControl(vector_off, TRUE);
	}
	print_hist(1);

	syslog(LOG_NOTICE, "== Com_MainFunctionTx ==");
	Com_IpduGroupControl(vector_on, TRUE);
	init_hist(1, MAX_TIME, histarea);
	for (i = 0; i < LOOP_COUNT; i++) {
		begin_measure(1);
		Com_MainFunctionTx();
		end_measure(1);
	}
	print_hist(1);
	Com_IpduGroupControl(vector_off, TRUE);

	for (k = 0; k < 84; k++) {
		syslog(LOG_NOTICE, "== Com_SendSignal(%d) ==", k);
		init_hist(1, MAX_TIME, histarea);
		for (i = 0; i < LOOP_COUNT; i++) {
			Com_IpduGroupControl(vector_on, TRUE);
			switch (signal_type_info[k]) {
			case COM_BOOLEAN:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_boolean);
				end_measure(1);
				break;
			case COM_SINT8:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_sint8);
				end_measure(1);
				break;
			case COM_SINT16:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_sint16);
				end_measure(1);
				break;
			case COM_SINT32:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_sint32);
				end_measure(1);
				break;
			case COM_UINT8:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_uint8);
				end_measure(1);
				break;
			case COM_UINT16:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_uint16);
				end_measure(1);
				break;
			case COM_UINT32:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_uint32);
				end_measure(1);
				break;
			case COM_FLOAT32:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_float32);
				end_measure(1);
				break;
			case COM_FLOAT64:
				begin_measure(1);
				ercd = Com_SendSignal(k, &signal_float64);
				end_measure(1);
				break;
			case COM_UINT8_N:
				begin_measure(1);
				ercd = Com_SendSignal(k, signal_uint8n);
				end_measure(1);
				break;
			}
			Com_IpduGroupControl(vector_off, TRUE);
		}
		print_hist(1);
	}

	Com_DeInit();
	ShutdownOS(E_OK);
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
	InitSerial();
	print_banner();
	StartOS(MainApp);
	while (1) {
	}
	return(0);
}
