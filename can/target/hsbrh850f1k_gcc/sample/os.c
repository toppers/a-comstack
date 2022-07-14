/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014-2015 by FUJI SOFT INCORPORATED, JAPAN
 *
 *  上記著作権者は，以下の(1)~(4)の条件を満たす場合に限り，本ソフトウェ
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

	/* SW状態初期化 */
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

		/* ウェイト */
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
	 * 拡張ボードあり：DIPスイッチ1ポート初期化
	 * 拡張ボードなし：SW2ポート初期化
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
