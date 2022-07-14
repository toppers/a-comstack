/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2013-2017 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2013-2017 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2013-2014 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2013-2017 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2017 by Witz Corporation
 *
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
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
 *  $Id: Can.c 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

/* [CAN034] */
#include "Os.h"
#include "ComStack_Types.h"
#include "Can.h"
#include "CanIf_Cbk.h"

/* SchM_Can.hはRTEジェネレータにより生成される */
#include "SchM_Can.h"

#include "Can_Nios2.h"

#define MAX_DLC			64
//#define MAX_DLC			8
#define BYTE_LENGTH		4

/*
 *  現在実行中のCanIfコンフィギュレーション情報
 */
const Can_ConfigType		*p_cur_can_config;
const Can_HwHandleType		*p_cur_hoh_box_table;
const Can_HwHandleType		*p_cur_rbox_hrh_table;
const Can_IdType			*p_cur_rbox_filter_table;
PduIdType					*p_cur_saved_pduid;
const CAN_CTRL_INIB			*p_cur_can_ctrl_inib_table;

/* デフォルトのCanIfコンフィギュレーション情報 */
extern const Can_ConfigType	can_config[];
//LOCAL_INLINE void CanIf_debug_irq(uint16 param);
//uint32 irq_reg_debug;
uint32 error_flag;

/*
 *  [CAN223] Can_Init
 */
void
Can_Init(const Can_ConfigType *Config)
{
	Can_HwHandleType	i;
	uint32				can_id_reg;
	uint32				rxen_reg;
	uint32				temp_reg;
	const CAN_CTRL_INIB	*p_ctrl_cb;

	if (Config == NULL_PTR) {
		/* NULL_PTRの場合，先頭のコンフィギュレーション情報を使用する */
		Config = &can_config[0];
	}

	/* 現在実行中のコンフィグレーション情報を保持 */
	p_cur_can_config = Config;
	p_cur_hoh_box_table = Config->p_hoh_box_table;
	p_cur_rbox_hrh_table = Config->p_rbox_hrh_table;
	p_cur_rbox_filter_table = Config->p_rbox_filter_table;
	p_cur_saved_pduid = Config->p_saved_pduid;
	p_cur_can_ctrl_inib_table = Config->p_can_ctrl_inib_table;

	p_ctrl_cb = GET_CAN_CTRL_INIB(0);

	/* コントローラを停止状態で初期化 */
	CANC_WR_MODE_REG(CANC_MODE_STOP);

	/* デフォルトボーレートを設定する */
	Can_ChangeBaudrate(0U, p_ctrl_cb->default_baudrate);

	/* 割込み許可 */
	CANC_WR_IRQ_EN_REG(IRQ_SET_ENABLE);

	/* アクセプタンスフィルタの設定 */
	/* 全体のアクセプタンスコードレジスタ(全て許可)の設定 */
	CANC_WR_ACCEPTANCE_CODE_REG(0xFFFFFFFFU);

	/* 全体のアクセプタンスマスクレジスタ(全て許可)の設定 */
	CANC_WR_ACCEPTANCE_MASK_REG(0xFFFFFFFFU);

	/* 受信割り込み許可ビットの初期化 */
	rxen_reg = 0U;
	
	/* メッセージボックスウィンドウレジスタでそれぞれのボックスに対してフィルタを設定する */
	for (i = 0U; i < GET_HRH_NUM(); i++) {
		/* 対象を設定する */
		CANC_WR_MBOXWIN_REG(i);

		/* 各受信メッセージボックスのアクセプタンスコードレジスタの設定 */
		can_id_reg = ((uint32) GET_RBOX_CAN_ID_FILTER(i)) << ACCEPTANCE_OFFSET;
		CANC_WR_RXMBOX_ACCEPTANCE_CODE_REG(can_id_reg);

		/* 各受信メッセージボックスのアクセプタンスマスクレジスタの設定 */
		CANC_WR_RXMBOX_ACCEPTANCE_MASK_REG(ACCEPTANCE_MASK);
		
		/* 受信割り込み許可ビットの設定 */
		rxen_reg = (rxen_reg << 1U) | 1U;
	}

	/* レジスタの初期化 */
	/* 未送信のメッセージをキャンセルする */
	CANC_WR_TXABORT_REG(TXABORT_CLEAR);

	/* エラーカウンタレジスタの値を初期化する(送信、受信ともに値が0で無い場合、受信エラーカウンタの変更は不可) */
	CANC_WR_ERROR_CNT_REG(ERROR_CNT_CLEAR);

	/* セルフ送受信要求レジスタを送受信要求を無しにする */
	CANC_WR_RXSELFREQ_REG(RXSELFREQ_CLEAR);

	/* 受信ウェイトレジスタをウェイト処理オフにする */
	CANC_WR_RXWAIT_REG(RXWAIT_OFF);

	/* 送信完了レジスタを送信未完了にする */
	CANC_WR_TXCMP_REG(TXCMP_CLEAR);

	/* 送信キャンセル完了レジスタを送信キャンセル未完了にする */
	CANC_WR_TXABORTCMP_REG(TXABORTCMP_CLEAR);

	/* 受信完了レジスタを受信データ無しにする */
	CANC_WR_RXCMP_REG(RXCMP_CLEAR);

	/* 受信オーバーライトレジスタを上書き未発生にする */
	temp_reg = CANC_RD_RXOVERWRITE_REG();

	/* 受信割込み許可レジスタを割り込み許可にする */
	CANC_WR_IRQ_RXEN_REG(rxen_reg);

	/* 割り込み要求レジスタを割り込み未発生にする */
	/* readすることで、値が初期値(割込み未発生)にリセットされる */
	CANC_RD_IRQ_REG();
}

/*
 *  [CAN224] Can_GetVersionInfo
 */
/* [CAN252] */
#if CAN_VERSION_INFO_API == STD_ON
void
Can_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	versioninfo->vendorID = CAN_VENDOR_ID;
	versioninfo->moduleID = CAN_MODULE_ID;
	versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
}
#endif /* CAN_VERSION_INFO_API */

/*
 *  [CAN454][CAN455] Can_CheckBaudrate
 */
Std_ReturnType
Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate)
{
	uint8				i;
	Std_ReturnType		ercd = E_NOT_OK;
	const CAN_CTRL_INIB	*p_ctrl_cb;

	/* コントローラは1つのみ */
	if (Controller >= TNUM_CONTROLLER) {
		goto error_exit;
	}

	p_ctrl_cb = GET_CAN_CTRL_INIB(Controller);

	for (i = 0U; i < p_ctrl_cb->tnum_baudrate; i++) {
		if (p_ctrl_cb->p_baudrate_table[i] == Baudrate) {
			ercd = E_OK;
			break;
		}
	}

  error_exit:
	return(ercd);
}

/*
 *  [CAN449] Can_ChangeBaudrate
 */
Std_ReturnType
Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate)
{
	Std_ReturnType ercd;

	ercd = Can_CheckBaudrate(Controller, Baudrate);

	/* E_OKの場合，250か500しかあり得ない */
	if (ercd == E_OK) {
		if (Baudrate == 250U) {
			CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_250);
		}
		else {
			/* Baudrate == 500U */
			CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_500_FD);
//			CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_500_FD_ISO);
//			CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_500);
		}
	}

  error_exit:
	return(ercd);
}

/*
 *  [CAN230] Can_SetControllerMode
 */
Can_ReturnType
Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition)
{
	Can_ReturnType		ercd;
	const CAN_CTRL_INIB	*p_ctrl_cb;

	/* コントローラは1つのみ */
	if (Controller >= TNUM_CONTROLLER) {
		ercd = CAN_NOT_OK;
		goto error_exit;
	}

	p_ctrl_cb = GET_CAN_CTRL_INIB(Controller);

	if (Transition == CAN_T_START) {
		CANC_WR_MODE_REG(CANC_MODE_START);
		CanIf_ControllerModeIndication(p_ctrl_cb->CanIfCtrlId, CANIF_CS_STARTED);
		ercd = CAN_OK;
	}
	else if (Transition == CAN_T_STOP) {
		CANC_WR_MODE_REG(CANC_MODE_STOP);
		CanIf_ControllerModeIndication(p_ctrl_cb->CanIfCtrlId, CANIF_CS_STOPPED);
		ercd = CAN_OK;
	}
	else {
		ercd = CAN_NOT_OK;
	}

  error_exit:
	return(ercd);
}

/*
 *  [CAN360] Can_CheckWakeup
 */
Can_ReturnType
Can_CheckWakeup(uint8 Controller)
{
	/* ウェイクアップは未サポート */
	return(CAN_OK);
}


uint8
GET_frame_bytes(uint8 length)
{
	uint8 conv_length = 0U;

	switch(length)
	{
	case 0:		conv_length = 0; break;
	case 1:		conv_length = 1; break;
	case 2:		conv_length = 2; break;
	case 3:		conv_length = 3; break;
	case 4:		conv_length = 4; break;
	case 5:		conv_length = 5; break;
	case 6:		conv_length = 6; break;
	case 7:		conv_length = 7; break;
	case 8:		conv_length = 8; break;
	case 9:		conv_length = 12; break;
	case 10:	conv_length = 16; break;
	case 11:	conv_length = 20; break;
	case 12:	conv_length = 24; break;
	case 13:	conv_length = 32; break;
	case 14:	conv_length = 48; break;
	case 15:	conv_length = 64; break;
	default:	break;
	}

	return conv_length;
}

uint8
GET_frame_dlc(uint8 length)
{
	uint8 conv_length = 0U;

	if(length < 9) {
		conv_length = length;
	}
	else if(length < 13) {
		conv_length = 9;
	}
	else if(length < 17) {
		conv_length = 10;
	}
	else if(length < 21) {
		conv_length = 11;
	}
	else if(length < 25) {
		conv_length = 12;
	}
	else if(length < 33) {
		conv_length = 13;
	}
	else if(length < 49) {
		conv_length = 14;
	}
	else {
		conv_length = 15;
	}
	
	return conv_length;
}

/*
 *  [CAN233] Can_Write
 */
Can_ReturnType
Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
	Can_ReturnType	ercd;
	uint8			i;
	uint32			temp = 0;
	uint32			temp_data1 = 0;
	uint32			temp_data[16] = {0};
	uint32			request_bit;
	uint32			fd_bit;
	uint8			tbox;
	uint8			length = 0;

	/* Hthが不正の場合 */
	if (Hth >= GET_HOH_NUM()) {
		ercd = CAN_NOT_OK;
		goto error_exit;
	}

	tbox = GET_BOX_ID(Hth);

	/* Hthが受信用IDの場合(送受信どちらも存在するIDの場合はチェックしない) */
	if (tbox >= GET_HTH_NUM()) {
		ercd = CAN_NOT_OK;
		goto error_exit;
	}

	/* CAN-FDモード中ではないとき，CAN-FDは送信しない */
//	if (PduInfo->edl > 0) {
//		ercd = CAN_NOT_OK;
//		goto error_exit;
//	}

	/* 送信完了通知用にPDU-IDを保持する */
	GET_SAVED_PDU_ID(tbox) = PduInfo->swPduHandle;

//	length = GET_frame_bytes(PduInfo->length);
	length = GET_frame_dlc(PduInfo->length);
	for (i = 0; i < PduInfo->length; i++) {
		temp = PduInfo->sdu[i] << ((i&3U)<<3U);
		temp_data1 |= temp;
		if ((i & 3U) == 3U) {
			temp_data[i >> 2U] = temp_data1;
			temp_data1 = 0U;
		}
	}
	if ((i & 3U) != 0U) {
		temp_data[i >> 2U] = temp_data1;
	}

	/* CAN-IDの格納 */
	CANC_WR_TXMBOX_DATA0_REG((PduInfo->id << EXTEND_CAN_ID_LENGTH), tbox);

	/* データ長の格納とCAN-FDモードの格納 */
//	CANC_WR_TXMBOX_DATA1_REG((PduInfo->brs << 6) | (PduInfo->edl << 5) | PduInfo->length, tbox);
	/* ビットレートは高速で固定 */
	if((PduInfo->id & CAN_FDTYPE) == 0) {
		fd_bit = 0;
	}
	else {
		fd_bit = 0x00000020;
	}
	CANC_WR_TXMBOX_DATA1_REG(0x0040 | fd_bit | length, tbox);

	if (PduInfo->length > 0) {
		/* データ(1～4)の格納 */
		CANC_WR_TXMBOX_DATA2_REG(temp_data[0], tbox);
	}
	/* データが5byte以上なら格納 */
	if (PduInfo->length > BYTE_LENGTH) {
		/* データ(5～8)の格納 */
		CANC_WR_TXMBOX_DATA3_REG(temp_data[1], tbox);
	}

	if (PduInfo->length >= (BYTE_LENGTH*3)) {		// over 12(9b)
		CANC_WR_TXMBOX_DATA4_REG(temp_data[2], tbox);

		if (PduInfo->length >= (BYTE_LENGTH*4)) {		// over 16(10b)
			CANC_WR_TXMBOX_DATA5_REG(temp_data[3], tbox);

			if (PduInfo->length >= (BYTE_LENGTH*5)) {		// over 20(11b)
				CANC_WR_TXMBOX_DATA6_REG(temp_data[4], tbox);

				if (PduInfo->length >= (BYTE_LENGTH*6)) {		// over 24(12b)
					CANC_WR_TXMBOX_DATA7_REG(temp_data[5], tbox);

					if (PduInfo->length >= (BYTE_LENGTH*8)) {		// over 32(13b)
						CANC_WR_TXMBOX_DATA8_REG(temp_data[6], tbox);
						CANC_WR_TXMBOX_DATA9_REG(temp_data[7], tbox);

						if (PduInfo->length >= (BYTE_LENGTH*12)) {	// over 48(14b)
							CANC_WR_TXMBOX_DATA10_REG(temp_data[8], tbox);
							CANC_WR_TXMBOX_DATA11_REG(temp_data[9], tbox);
							CANC_WR_TXMBOX_DATA12_REG(temp_data[10], tbox);
							CANC_WR_TXMBOX_DATA13_REG(temp_data[11], tbox);

							if (PduInfo->length >= (BYTE_LENGTH*16)) {	// over 64(15b)
								CANC_WR_TXMBOX_DATA14_REG(temp_data[12], tbox);
								CANC_WR_TXMBOX_DATA15_REG(temp_data[13], tbox);
								CANC_WR_TXMBOX_DATA16_REG(temp_data[14], tbox);
								CANC_WR_TXMBOX_DATA17_REG(temp_data[15], tbox);
							}
						}
					}
				}
			}
		}
	}
	/* add↓2016.11.25 */
	ercd = CAN_OK;
	/* add↑2016.11.25 */

	SuspendAllInterrupts();

	request_bit = 1U << tbox;
	CANC_WR_TXREQ_REG(request_bit);

	ResumeAllInterrupts();

  error_exit:
	return(ercd);
}

/*
 *  [CAN035] CAN用割込みサービスルーチン
 */
void
Can_ISR(uint8 Controller)
{
	Can_HwHandleType	i;
	uint8				j;
	uint32				irq_reg;
	uint32				clear_bit;
	uint32				cmp_reg;
	uint32				wait_reg;
	Can_IdType			can_id;
	uint8				can_dlc;
	uint8				can_sdu[MAX_DLC];
	uint32				temp_data;
	/* debug */
	uint16				can_flag;
	/* debug */

	/* コントローラは1つのみ */
	if (Controller >= TNUM_CONTROLLER) {
		goto error_exit;
	}

	irq_reg = CANC_RD_IRQ_REG();

	//CanIf_debug_irq(irq_reg);

	/* 受信完了割込み */
	if ((irq_reg & RECEIVE_IRQ) != 0U) {
		clear_bit = 1U;
		cmp_reg = CANC_RD_RXCMP_REG();

		if (cmp_reg != 0U) {

			for (i = 0U; i < GET_HRH_NUM(); i++) {
				if ((cmp_reg & 1U) != 0U) {

					/* 対象受信ウェイトレジスタの該当するビットをウェイト処理ONにする */
					wait_reg = CANC_RD_RXWAIT_REG();
					wait_reg |= clear_bit;
					CANC_WR_RXWAIT_REG(wait_reg);

					/* CAN-ID取出し */
					can_id = ((CANC_RD_RXMBOX_DATA0_REG(i) & MASK_CAN_ID_MASK) >> EXTEND_CAN_ID_LENGTH);

					/* DLCの取り出し */
					can_dlc = (uint8) (CANC_RD_RXMBOX_DATA1_REG(i) & MASK_4BIT);

					/* debug */
					can_flag = (uint16) ((CANC_RD_RXMBOX_DATA1_REG(i) & 0x000000F0) << 8);
					can_id = can_flag | can_id;

					/* debug */
					
					if (can_dlc > BYTE_LENGTH) {
						/* 5byte以上の場合、5byte目以降のレジスタも読み込む */
						/* SDU(1～4byte)の取り出し */
						temp_data = CANC_RD_RXMBOX_DATA2_REG(i);
						for (j = 0U; j < BYTE_LENGTH; j++) {
							can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
							temp_data >>= 8U;
						}
						/* SDU(5～8byte)の取り出し */
						temp_data = CANC_RD_RXMBOX_DATA3_REG(i);
						for (j = BYTE_LENGTH; j < can_dlc; j++) {
							can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
							temp_data >>= 8U;
						}
					}
					else {
						/* 4byte以下の場合、5byte目以降のレジスタは読み込まない */
						/* SDU(1～4byte)の取り出し */
						temp_data = CANC_RD_RXMBOX_DATA2_REG(i);
						for (j = 0U; j < can_dlc; j++) {
							can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
							temp_data >>= 8U;
						}
					}

					/* add kurachi */
#if 1 // testdebug
					if (can_dlc >= 9) {
					  temp_data = CANC_RD_RXMBOX_DATA4_REG(i);
					  for (j = BYTE_LENGTH*2; j < BYTE_LENGTH*2+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
					if (can_dlc >= 10) {
					  temp_data = CANC_RD_RXMBOX_DATA5_REG(i);
					  for (j = BYTE_LENGTH*3; j < BYTE_LENGTH*3+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
					if (can_dlc >= 11) {
					  temp_data = CANC_RD_RXMBOX_DATA6_REG(i);
					  for (j = BYTE_LENGTH*4; j < BYTE_LENGTH*4+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
					if (can_dlc >= 12) {
					  temp_data = CANC_RD_RXMBOX_DATA7_REG(i);
					  for (j = BYTE_LENGTH*5; j < BYTE_LENGTH*5+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
					if (can_dlc >= 13) {
					  temp_data = CANC_RD_RXMBOX_DATA8_REG(i);
					  for (j = BYTE_LENGTH*6; j < BYTE_LENGTH*6+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }

					  temp_data = CANC_RD_RXMBOX_DATA9_REG(i);
					  for (j = BYTE_LENGTH*7; j < BYTE_LENGTH*7+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
					if (can_dlc >= 14) {
					  temp_data = CANC_RD_RXMBOX_DATA10_REG(i);
					  for (j = BYTE_LENGTH*8; j < BYTE_LENGTH*8+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					  temp_data = CANC_RD_RXMBOX_DATA11_REG(i);
					  for (j = BYTE_LENGTH*9; j < BYTE_LENGTH*9+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					  temp_data = CANC_RD_RXMBOX_DATA12_REG(i);
					  for (j = BYTE_LENGTH*10; j < BYTE_LENGTH*10+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					  temp_data = CANC_RD_RXMBOX_DATA13_REG(i);
					  for (j = BYTE_LENGTH*11; j < BYTE_LENGTH*11+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
					if (can_dlc >= 15) {
					  temp_data = CANC_RD_RXMBOX_DATA14_REG(i);
					  for (j = BYTE_LENGTH*12; j < BYTE_LENGTH*12+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					  temp_data = CANC_RD_RXMBOX_DATA15_REG(i);
					  for (j = BYTE_LENGTH*13; j < BYTE_LENGTH*13+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					  temp_data = CANC_RD_RXMBOX_DATA16_REG(i);
					  for (j = BYTE_LENGTH*14; j < BYTE_LENGTH*14+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					  temp_data = CANC_RD_RXMBOX_DATA17_REG(i);
					  for (j = BYTE_LENGTH*15; j < BYTE_LENGTH*15+4; j++) {
					    can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
					    temp_data >>= 8U;
					  }
					}
#endif // testdebug
					/* add kurachi */

					CANC_WR_RXCMP_REG(clear_bit);

					/* 対象受信ウェイトレジスタの該当するビットをウェイト処理OFFにする */
					wait_reg = wait_reg ^ clear_bit;
					CANC_WR_RXWAIT_REG(wait_reg);

					CanIf_RxIndication(GET_RBOX_CAN_OBJ_ID(i), can_id, GET_frame_bytes(can_dlc), can_sdu);
				}
				cmp_reg >>= 1U;
				clear_bit <<= 1U;
			}
		}
	}

	/* 送信完了割込み */
	if ((irq_reg & TRANSMIT_IRQ) != 0U) {
		clear_bit = 1U;
		cmp_reg = CANC_RD_TXCMP_REG();

		if (cmp_reg != 0U) {
			for (i = 0U; i < GET_HTH_NUM(); i++) {
				if ((cmp_reg & 1U) != 0U) {
					CANC_WR_TXCMP_REG(clear_bit);
					CanIf_TxConfirmation(GET_SAVED_PDU_ID(i));
				}
				cmp_reg >>= 1U;
				clear_bit <<= 1U;
			}
		}
	}

//	irq_reg_debug = irq_reg;
	if ((irq_reg & ERROR_IRQ) != 0U) {
		CANC_WR_TXABORT_REG(TXABORT_CLEAR);
		error_flag = 1U;
	}

	if ((irq_reg & TXCANCEL_IRQ) != 0U) {
		CANC_WR_TXABORTCMP_REG(TXABORTCMP_CLEAR);
		CANC_RD_TXABORTCMP_REG();
	}

	/* add↓2016.11.03 */
	if ((irq_reg & ERROR_OVW_IRQ) != 0U) {
		/* オーバーライトクリア処理(読み出すとクリアされる) */
		temp_data = CANC_RD_RXOVERWRITE_REG();
	}
	/* add↑2016.11.03 */

	error_exit:
	return;
}
