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

		/* ボタン押下状態に遷移した場合のみ処理を行う */
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

		/* ウェイト */
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
