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
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 *
 *  本ソフトウェアは，AUTOSAR（AUTomotive Open System ARchitecture）仕
 *  様に基づいている．上記の許諾は，AUTOSARの知的財産権を許諾するもので
 *  はない．AUTOSARは，AUTOSAR仕様に基づいたソフトウェアを商用目的で利
 *  用する者に対して，AUTOSARパートナーになることを求めている．
 *
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
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
 *  実行時間分布を記録するメモリ領域
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
