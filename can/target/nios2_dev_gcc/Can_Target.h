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
 *  $Id: Can_Target.h 599 2014-10-17 01:27:58Z shigihara $
 */

#ifndef TOPPERS_CAN_TARGET_H
#define TOPPERS_CAN_TARGET_H

#include "Can.h"
#include "prc_sil.h"


#define CANC_0_BASE		0x08020000U    /* CANコントローラ0のベースアドレス */

#define EXTEND_CAN_ID_LENGTH	18U             /* 拡張分のCAN-ID幅 */
#define ACCEPTANCE_OFFSET		21U             /* アクセプタンスレジスタのオフセット */
#define NO_MASK_VAL				0x001FFFFFU     /* アクセプタンスマスクレジスタ設定値(マスク設定無) */

/* モードレジスタ */
#define RESET_MODE			0x00000001U                                                                 /* 動作モードをRESET_MODEにする */
#define OPERATING_MODE		0x00000000U                                                                 /* 動作モードをOPERATING_MODEにする */
#define LISTEN_ONLY_MODE	0x00000002U                                                                 /* 送信禁止 */
#define NO_LISTEN_ONLY_MODE	0x00000000U                                                                 /* 送信許可 */
#define NO_SEND_ACK_MODE	0x00000004U                                                                 /* ACK送信禁止 */
#define SEND_ACK_MODE		0x00000000U                                                                 /* ACK送信 */
#define SINGLE_FILTER_MODE	0x00000008U                                                                 /* Single filter mode */
#define DUAL_FILTER_MODE	0x00000000U                                                                 /* Dual filter mode */
#define CANC_MODE_START		(OPERATING_MODE | NO_LISTEN_ONLY_MODE | SEND_ACK_MODE | SINGLE_FILTER_MODE) /* CANコントローラのSTART状態 */
#define CANC_MODE_STOP		(RESET_MODE     | NO_LISTEN_ONLY_MODE | SEND_ACK_MODE | SINGLE_FILTER_MODE) /* CANコントローラのSTOP状態 */

/* 割込み要求 */
#define RECEIVE_IRQ			0x00000001U     /* 受信完了 */
#define TRANSMIT_IRQ		0x00000002U     /* 送信完了 */

#define IRQ_SET_DISABLE		0x00000000U     /* [割込み許可レジスタ]全割込み要求を禁止 */
#define IRQ_SET_ENABLE		0x00000003U     /* [割込み許可レジスタ]指定の割込み要求を許可 */
#define TXABORT_CLEAR		0x0000FFFFU     /* [送信キャンセルレジスタ]全メッセージボックス送信キャンセル */
#define TXCMP_CLEAR			0x0000FFFFU     /* [送信完了レジスタ]送信完了ビットクリア */
#define TXABORTCMP_CLEAR	0x0000FFFFU     /* [送信キャンセル完了レジスタ]送信キャンセル完了ビットクリア */
#define RXWAIT_OFF			0x00000000U     /* [受信ウェイトレジスタ]ウェイト処理OFF */
#define RXCMP_CLEAR			0xFFFFFFFFU     /* [受信完了レジスタ]受信完了ビットクリア */
#define RXSELFREQ_CLEAR		0x00000000U     /* [セルフ受信要求レジスタ]送受信要求なし */
#define ERROR_CNT_CLEAR		0x00000060U     /* [エラーカウンタレジスタ]エラーカウンタを初期値にする */
#define BAUDRATE_250		0x80007F03U     /* [クロック制御，バスタイミングレジスタ]ボーレート:250kbps */
#define BAUDRATE_500		0x80007F01U     /* [クロック制御，バスタイミングレジスタ]ボーレート:500kbps */

#define MASK_CAN_ID_MASK	0x1FFFFFFFU     /* CanId取得マスク */
#define MASK_4BIT			0x0000000FU     /* 4ビットマスク */
#define MASK_8BIT			0x000000FFU     /* 8ビットマスク */

/* 各レジスタまでのオフセットアドレス */
#define CANC_MODE_REG							0x0000U     /* モード */
#define CANC_TXREQ_REG							0x0004U
#define CANC_TXABORT_REG						0x0008U     /* 送信キャンセルレジスタ */
#define CANC_TXCMP_REG							0x000CU
#define CANC_TXABORTCMP_REG						0x0010U
#define CANC_RXWAIT_REG							0x0014U
#define CANC_RXCMP_REG							0x0018U
#define CANC_RXOVERWRITE_REG					0x001CU
#define CANC_RXSELFREQ_REG						0x0020U
#define CANC_STATUS_REG							0x0024U
#define CANC_IRQ_REG							0x0028U
#define CANC_IRQ_EN_REG							0x002CU     /* 割込み許可レジスタ */
#define CANC_IRQ_RXEN_REG						0x0030U
#define CANC_CLKDIV_BUSTIM_REG					0x0034U     /* クロック制御，バスタイミング */
#define CANC_ACCEPTANCE_CODE_REG				0x0038U     /* アクセプタンスコードレジスタ */
#define CANC_ACCEPTANCE_MASK_REG				0x003CU     /* アクセプタンスマスクレジスタ */
#define CANC_ARBITRATION_LOST_CAPTURE_REG		0x0040U
#define CANC_ERROR_CAPTURE_CODE_REG				0x0044U
#define CANC_ERROR_CNT_REG						0x0048U
#define CANC_MBOXWIN_REG						0x004CU     /* メッセージボックスウィンドウレジスタ */
#define CANC_RXMBOX_ACCEPTANCE_CODE_REG			0x0070U     /* 受信メッセージボックスのアクセプタンスコードレジスタ */
#define CANC_RXMBOX_ACCEPTANCE_MASK_REG			0x0074U     /* 受信メッセージボックスのアクセプタンスマスクレジスタ */
#define CANC_TXMBOX_DATA0_REG					0x0100U
#define CANC_TXMBOX_DATA1_REG					0x0104U
#define CANC_TXMBOX_DATA2_REG					0x0108U
#define CANC_TXMBOX_DATA3_REG					0x010CU
#define CANC_RXMBOX_DATA0_REG					0x0200U
#define CANC_RXMBOX_DATA1_REG					0x0204U
#define CANC_RXMBOX_DATA2_REG					0x0208U
#define CANC_RXMBOX_DATA3_REG					0x020CU

#define SIL_REW_IOP_CANC_0_BASE(mem)		sil_rew_iop((void *) (CANC_0_BASE + (mem)))
#define SIL_WRW_IOP_CANC_0_BASE(mem, data)	sil_wrw_iop((void *) (CANC_0_BASE + (mem)), (data))

/* 読取り用レジスタアクセスマクロ */
#define CANC_RD_MODE_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_MODE_REG)
#define CANC_RD_TXCMP_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_TXCMP_REG)
#define CANC_RD_TXABORTCMP_REG()					SIL_REW_IOP_CANC_0_BASE(CANC_TXABORTCMP_REG)
#define CANC_RD_RXCMP_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_RXCMP_REG)
#define CANC_RD_RXOVERWRITE_REG()					SIL_REW_IOP_CANC_0_BASE(CANC_RXOVERWRITE_REG)
#define CANC_RD_STATUS_REG()						SIL_REW_IOP_CANC_0_BASE(CANC_STATUS_REG)
#define CANC_RD_IRQ_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_IRQ_REG)
#define CANC_RD_CLKDIV_BUSTIM_REG()					SIL_REW_IOP_CANC_0_BASE(CANC_CLKDIV_BUSTIM_REG)
#define CANC_RD_ERROR_CNT_REG()						SIL_REW_IOP_CANC_0_BASE(CANC_ERROR_CNT_REG)
#define CANC_RD_RXMBOX_DATA0_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA0_REG + (0x0010U * (box_num))))
#define CANC_RD_RXMBOX_DATA1_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA1_REG + (0x0010U * (box_num))))
#define CANC_RD_RXMBOX_DATA2_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA2_REG + (0x0010U * (box_num))))
#define CANC_RD_RXMBOX_DATA3_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA3_REG + (0x0010U * (box_num))))

/* 書込み用レジスタアクセスマクロ */
#define CANC_WR_MODE_REG(data)						SIL_WRW_IOP_CANC_0_BASE(CANC_MODE_REG, data)
#define CANC_WR_TXREQ_REG(data)						SIL_WRW_IOP_CANC_0_BASE(CANC_TXREQ_REG, data)
#define CANC_WR_TXABORT_REG(data)					SIL_WRW_IOP_CANC_0_BASE(CANC_TXABORT_REG, data)
#define CANC_WR_TXCMP_REG(data)						SIL_WRW_IOP_CANC_0_BASE(CANC_TXCMP_REG, data)
#define CANC_WR_TXABORTCMP_REG(data)				SIL_WRW_IOP_CANC_0_BASE(CANC_TXABORTCMP_REG, data)
#define CANC_WR_RXWAIT_REG(data)					SIL_WRW_IOP_CANC_0_BASE(CANC_RXWAIT_REG, data)
#define CANC_WR_RXCMP_REG(data)						SIL_WRW_IOP_CANC_0_BASE(CANC_RXCMP_REG, data)
#define CANC_WR_RXSELFREQ_REG(data)					SIL_WRW_IOP_CANC_0_BASE(CANC_RXSELFREQ_REG, data)
#define CANC_WR_IRQ_EN_REG(data)					SIL_WRW_IOP_CANC_0_BASE(CANC_IRQ_EN_REG, data)
#define CANC_WR_IRQ_RXEN_REG(data)					SIL_WRW_IOP_CANC_0_BASE(CANC_IRQ_RXEN_REG, data)
#define CANC_WR_CLKDIV_BUSTIM_REG(data)				SIL_WRW_IOP_CANC_0_BASE(CANC_CLKDIV_BUSTIM_REG, data)
#define CANC_WR_ACCEPTANCE_CODE_REG(data)			SIL_WRW_IOP_CANC_0_BASE(CANC_ACCEPTANCE_CODE_REG, data)
#define CANC_WR_ACCEPTANCE_MASK_REG(data)			SIL_WRW_IOP_CANC_0_BASE(CANC_ACCEPTANCE_MASK_REG, data)
#define CANC_WR_ERROR_CNT_REG(data)					SIL_WRW_IOP_CANC_0_BASE(CANC_ERROR_CNT_REG, data)
#define CANC_WR_MBOXWIN_REG(box_num)				SIL_WRW_IOP_CANC_0_BASE(CANC_MBOXWIN_REG, ((box_num) << 16))
#define CANC_WR_RXMBOX_ACCEPTANCE_CODE_REG(data)	SIL_WRW_IOP_CANC_0_BASE(CANC_RXMBOX_ACCEPTANCE_CODE_REG, data)
#define CANC_WR_RXMBOX_ACCEPTANCE_MASK_REG(data)	SIL_WRW_IOP_CANC_0_BASE(CANC_RXMBOX_ACCEPTANCE_MASK_REG, data)
#define CANC_WR_TXMBOX_DATA0_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA0_REG + (0x0010U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA1_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA1_REG + (0x0010U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA2_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA2_REG + (0x0010U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA3_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA3_REG + (0x0010U * (box_num))), data)

/*
 * [CAN077][CAN284][CAN385][CAN386] ターゲット依存部処理
 */
#define BYTE_LENGTH		4U

extern const CAN_CTRL_INIB	*p_cur_can_ctrl_inib_table;
extern uint8				can_interrupt_nested_cnt[];

/* 内部関数プロトタイプ宣言 */
LOCAL_INLINE boolean can_target_init_unit_phase1(const Can_ConfigType *p_can_config);
LOCAL_INLINE boolean can_target_init_controller_phase1(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_init_controller_phase2(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_init_controller_phase3(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_rbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hrh_idx);
LOCAL_INLINE boolean can_target_tbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hth_idx);
LOCAL_INLINE boolean can_target_init_unit_phase2(const Can_ConfigType *p_can_config);
LOCAL_INLINE boolean can_target_change_baudrate(uint8 ctrl_id, const Can_ControllerBaudrateConfigType *p_baudrate_table);
LOCAL_INLINE boolean can_target_start_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_stop_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_sleep_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_wakeup_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib);
LOCAL_INLINE boolean can_target_disable_controller_interrupts(uint8 ctrl_id);
LOCAL_INLINE boolean can_target_enable_controller_interrupts(uint8 ctrl_id);
LOCAL_INLINE boolean can_target_check_wakeup(uint8 ctrl_id);
LOCAL_INLINE Can_ReturnType can_target_transmit(uint8 ctrl_id, uint8 mb_idx, const Can_PduType *PduInfo);
LOCAL_INLINE boolean can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx);
LOCAL_INLINE boolean can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[]);
LOCAL_INLINE boolean can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx);
LOCAL_INLINE Can_StateTransitionType can_target_get_mode(uint8 ctrl_id);
LOCAL_INLINE void can_target_busy_wait(void);

/* [CAN407] Can_Init：unit_phase1 */
LOCAL_INLINE boolean
can_target_init_unit_phase1(const Can_ConfigType *p_can_config)
{
	/* ユニットに関する初期化は無し */
	return(TRUE);
}

/* [CAN407] Can_Init：controller_phase1 */
LOCAL_INLINE boolean
can_target_init_controller_phase1(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN259] コントローラを停止状態で初期化 */
	CANC_WR_MODE_REG(CANC_MODE_STOP);

	return(TRUE);
}

/* [CAN407] Can_Init：controller_phase2 */
LOCAL_INLINE boolean
can_target_init_controller_phase2(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* 割込み禁止 */
	can_target_disable_controller_interrupts(ctrl_id);

	/* アクセプタンスフィルタの設定 */
	/* 全体のアクセプタンスコードレジスタ(全て許可)の設定 */
	CANC_WR_ACCEPTANCE_CODE_REG(0xFFFFFFFFU);

	/* 全体のアクセプタンスマスクレジスタ(全て許可)の設定 */
	CANC_WR_ACCEPTANCE_MASK_REG(0xFFFFFFFFU);

	return(TRUE);
}

/* [CAN407] Can_Init：controller_phase3 */
LOCAL_INLINE boolean
can_target_init_controller_phase3(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	uint8	i;
	uint32	irq_rxen_reg_set_bit = 1U;
	uint32	bit_offset = 1U;

	/* [CAN236][CAN237][CAN419] レジスタの初期化 */
	/* 未送信のメッセージをキャンセルする */
	CANC_WR_TXABORT_REG(TXABORT_CLEAR);

	/* エラーカウンタレジスタの値を初期化する(送信，受信ともに値が0で無い場合，受信エラーカウンタの変更は不可) */
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
	CANC_RD_RXOVERWRITE_REG();

	/* 受信割込み許可レジスタを割り込み許可にする */
	for (i = 0U; i < p_ctrl_inib->tnum_hrh; i++) {
		CANC_WR_IRQ_RXEN_REG(irq_rxen_reg_set_bit);
		irq_rxen_reg_set_bit <<= bit_offset;
		irq_rxen_reg_set_bit += bit_offset;
	}

	/* 割り込み要求レジスタを割り込み未発生にする */
	CANC_RD_IRQ_REG();

	return(TRUE);
}

/* [CAN407] Can_Init：受信メールボックス初期化 */
LOCAL_INLINE boolean
can_target_rbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hrh_idx)
{
	uint32	can_id_reg;
	uint32	filtermask_val;

	/* 対象を設定する */
	CANC_WR_MBOXWIN_REG(hrh_idx);

	/* 各受信メッセージボックスのアクセプタンスコードレジスタの設定 */
	can_id_reg = ((uint32) GET_RBOX_CAN_ID(ctrl_id, hrh_idx)) << ACCEPTANCE_OFFSET;
	CANC_WR_RXMBOX_ACCEPTANCE_CODE_REG(can_id_reg);

	/* 対象の受信メッセージボックスのフィルタマスク有無判定 */
	if (GET_RBOX_FILTER_MASK_IDX(ctrl_id, hrh_idx) != CAN_NO_MASK_IDX) {
		/* 対象のフィルタマスク値設定 */
		filtermask_val = ((uint32) p_ctrl_inib->p_filtermask_table[hrh_idx]) << ACCEPTANCE_OFFSET;
		CANC_WR_RXMBOX_ACCEPTANCE_MASK_REG(filtermask_val);
	}
	else {
		/* 対象のフィルタマスク値がCAN_NO_MASK_IDX */
		CANC_WR_RXMBOX_ACCEPTANCE_MASK_REG(NO_MASK_VAL);
	}

	return(TRUE);
}

/* [CAN407] Can_Init：送信メールボックス初期化 */
LOCAL_INLINE boolean
can_target_tbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hth_idx)
{
	return(TRUE);
}

/* [CAN407] Can_Init：unit_phase2 */
LOCAL_INLINE boolean
can_target_init_unit_phase2(const Can_ConfigType *p_can_config)
{
	/* ユニットに関する初期化は無し */
	return(TRUE);
}

/* Can_ChangeBaudrate */
LOCAL_INLINE boolean
can_target_change_baudrate(uint8 ctrl_id, const Can_ControllerBaudrateConfigType *p_baudrate_table)
{
	/* [CAN255] ボーレートの設定 */
	if (p_baudrate_table->CanControllerBaudRate == 250U) {
		CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_250);
	}
	else {
		CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_500);
	}

	return(TRUE);
}

/* Can_SetControllerMode：CAN_T_START */
LOCAL_INLINE boolean
can_target_start_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN261] モード切替処理 */
	CANC_WR_MODE_REG(CANC_MODE_START);

	/* [CAN204][CAN425] 割込み禁止ネストカウント判定 */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/* [CAN196] 割込み許可処理 */
		can_target_enable_controller_interrupts(ctrl_id);
	}

	return(TRUE);
}

/* Can_SetControllerMode：CAN_T_STOP */
LOCAL_INLINE boolean
can_target_stop_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN204][CAN426] 割込み禁止ネストカウント判定 */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/* [CAN197] 割込み禁止処理 */
		can_target_disable_controller_interrupts(ctrl_id);
	}

	/* [CAN263] モード切替処理 */
	CANC_WR_MODE_REG(CANC_MODE_STOP);

	return(TRUE);
}

/* Can_SetControllerMode：CAN_T_SLEEP */
LOCAL_INLINE boolean
can_target_sleep_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* CAN_T_SLEEPは未サポート */
	return(FALSE);
}

/* Can_SetControllerMode：CAN_T_WAKEUP */
LOCAL_INLINE boolean
can_target_wakeup_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* CAN_T_WAKEUPは未サポート */
	return(FALSE);
}

/* Can_DisableControllerInterrupts */
LOCAL_INLINE boolean
can_target_disable_controller_interrupts(uint8 ctrl_id)
{
	/* 割込み禁止処理 */
	CANC_WR_IRQ_EN_REG(IRQ_SET_DISABLE);

	return(TRUE);
}

/* Can_EnableControllerInterrupts */
LOCAL_INLINE boolean
can_target_enable_controller_interrupts(uint8 ctrl_id)
{
	/* 割込み許可処理 */
	CANC_WR_IRQ_EN_REG(IRQ_SET_ENABLE);

	return(TRUE);
}

/* Can_CheckWakeup */
LOCAL_INLINE boolean
can_target_check_wakeup(uint8 ctrl_id)
{
	/* ウェイクアップは未サポート */
	return(FALSE);
}

/* Can_Write：送信データ及び送信要求設定 */
LOCAL_INLINE Can_ReturnType
can_target_transmit(uint8 ctrl_id, uint8 mb_idx, const Can_PduType *PduInfo)
{
	uint8	i, j;
	uint32	temp_data1 = 0;         /* データ(1〜4byte)格納用 */
	uint32	temp_data2 = 0;         /* データ(5〜8byte)格納用 */
	uint32	request_bit;

	if (PduInfo->length > BYTE_LENGTH) {
		/* 5〜8byteのデータをコピーする */
		for (i = 0U; i < (PduInfo->length - BYTE_LENGTH); i++) {
			if (i > 0U) {
				temp_data2 = temp_data2 << 8U;
			}
			temp_data2 = (temp_data2 | PduInfo->sdu[PduInfo->length - (1U + i)]);
		}
	}
	else {
		i = 0U;
	}

	/* メッセージのデータが1byte以上なら，1byte目以降を取得する */
	if (PduInfo->length > 0) {
		/* 1〜4byteのデータをコピーする */
		for (j = i; j < PduInfo->length; j++) {
			if (j > i) {
				temp_data1 = temp_data1 << 8U;
			}
			temp_data1 = (temp_data1 | PduInfo->sdu[PduInfo->length - (1U + j)]);
		}
	}

	/* CAN-IDの格納 */
	CANC_WR_TXMBOX_DATA0_REG((PduInfo->id << EXTEND_CAN_ID_LENGTH), mb_idx);

	/* データ長の格納 */
	CANC_WR_TXMBOX_DATA1_REG(PduInfo->length, mb_idx);

	/* [CAN059][CAN427] データ格納 */
	if (PduInfo->length > 0) {
		/* データ(1〜4)の格納 */
		CANC_WR_TXMBOX_DATA2_REG(temp_data1, mb_idx);
	}
	/* データが5byte以上なら格納 */
	if (PduInfo->length > BYTE_LENGTH) {
		/* データ(5〜8)の格納 */
		CANC_WR_TXMBOX_DATA3_REG(temp_data2, mb_idx);
	}

	/* 送信要求 */
	request_bit = 1U << mb_idx;
	CANC_WR_TXREQ_REG(request_bit);

	return(CAN_OK);
}

/* Can_IsrRx：受信メールボックス取得 */
LOCAL_INLINE boolean
can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx)
{
	boolean	ret;
	uint8	i;
	uint32	cmp_reg;

	/* HRH初期化(DET処理でエラー検知できるよう0xFFで初期化する) */
	*p_rbox_idx = 0xFFU;

	/* 受信完了情報取得 */
	cmp_reg = CANC_RD_RXCMP_REG();

	/* 受信メッセージ有無判定 */
	if (cmp_reg != 0x00000000U) {
		for (i = 0U; i < GET_HRH_NUM(ctrl_id); i++) {
			if ((cmp_reg & 1U) != 0U) {

				/* HRH設定 */
				*p_rbox_idx = i;
				break;
			}
			else {
				cmp_reg >>= 1U;
			}
		}
		/* 受信メッセージ有り */
		ret = TRUE;
	}
	else {
		/* 受信メッセージ無し */
		ret = FALSE;
	}

	return(ret);
}

/* Can_IsrRx：受信IDのデータ取得 */
LOCAL_INLINE boolean
can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[])
{
	uint8	j;
	uint8	local_can_dlc;
	uint32	temp_data;
	uint32	clear_bit;

	/* 受信完了クリアビット設定 */
	clear_bit = 1U;
	clear_bit <<= (uint32) rbox_id;

	/* CAN-ID取出し */
	*p_can_id = ((CANC_RD_RXMBOX_DATA0_REG(rbox_id) &MASK_CAN_ID_MASK) >> EXTEND_CAN_ID_LENGTH);

	/* DLCの取り出し */
	local_can_dlc = (uint8) (CANC_RD_RXMBOX_DATA1_REG(rbox_id) &MASK_4BIT);
	*p_can_dlc = local_can_dlc;

	/* [CAN012][CAN060][CAN299][CAN300] データ取り出し*/
	if (local_can_dlc > BYTE_LENGTH) {
		/* 5byte以上の場合，5byte目以降のレジスタも読み込む */
		/* SDU(1〜4byte)の取り出し */
		temp_data = CANC_RD_RXMBOX_DATA2_REG(rbox_id);
		for (j = 0U; j < BYTE_LENGTH; j++) {
			can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
			temp_data >>= 8U;
		}
		/* SDU(5〜8byte)の取り出し */
		temp_data = CANC_RD_RXMBOX_DATA3_REG(rbox_id);
		for (j = BYTE_LENGTH; j < local_can_dlc; j++) {
			can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
			temp_data >>= 8U;
		}
	}
	else {
		/* 4byte以下の場合，5byte目以降のレジスタは読み込まない */
		/* SDU(1〜4byte)の取り出し */
		temp_data = CANC_RD_RXMBOX_DATA2_REG(rbox_id);
		for (j = 0U; j < local_can_dlc; j++) {
			can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
			temp_data >>= 8U;
		}
	}

	/* [CAN420] 受信完了ビットクリア */
	CANC_WR_RXCMP_REG(clear_bit);

	return(TRUE);
}

/* Can_IsrTx：送信メールボックスチェック取得 */
LOCAL_INLINE boolean
can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx)
{
	boolean	ret;
	uint8	i;
	uint32	cmp_reg;
	uint32	clear_bit;

	/* HTH初期化(DET処理でエラー検知できるよう0xFFで初期化する) */
	*p_tbox_idx = 0xFFU;

	/* 送信完了クリアビット設定 */
	clear_bit = 1U;

	/* 送信完了情報取得 */
	cmp_reg = CANC_RD_TXCMP_REG();

	/* 送信メッセージ有無判定 */
	if (cmp_reg != 0x00000000U) {
		for (i = 0U; i < GET_HTH_NUM(ctrl_id); i++) {
			if ((cmp_reg & 1U) != 0U) {
				/* [CAN420] 送信完了ビットのクリア */
				CANC_WR_TXCMP_REG(clear_bit);

				/* HTH設定 */
				*p_tbox_idx = i;
				break;
			}
			else {
				cmp_reg >>= 1U;
				clear_bit <<= 1U;
			}
		}
		/* 送信メッセージ有り */
		ret = TRUE;
	}
	else {
		/* 送信メッセージ無し */
		ret = FALSE;
	}

	return(ret);
}

LOCAL_INLINE Can_StateTransitionType
can_target_get_mode(uint8 ctrl_id)
{
	Can_StateTransitionType	ret;
	uint32					mode_reg;

	/* 動作モード取得 */
	mode_reg = CANC_RD_MODE_REG();

	/* [CAN384][CAN409][CAN410] 動作モード判定 */
	if (mode_reg == CANC_MODE_START) {
		ret = CAN_T_START;
	}
	else {
		ret = CAN_T_STOP;
	}

	return(ret);
}

LOCAL_INLINE void
can_target_busy_wait(void)
{
	volatile uint32 i;

	/* ビジーウェイト処理 */
	for (i = 0U; i < 100000U; i++) {
	}
}

/*
 *  ■依存部での未サポート機能
 *    <CAN048><CAN294><CAN361><CAN461> ウェイクアップは未サポートのため，対応しない
 *    <CAN257><CAN265><CAN267><CAN411><CAN412> ハードウェアがSLEEPモードを未サポートのため，対応しない
 *    <CAN282><CAN283> 送信キャンセルは未サポートのため，対応しない
 *    <CAN238><CAN242><CAN391><CAN244> nios2では未サポートのため，対応しない
 *    <CAN258><CAN290><CAN404><CAN405>論理的なSLEEPモードは未サポートのため，対応しない
 *    <CAN062><CAN256><CAN260><CAN422><CAN453> ボーレートの設定は固定のため，対応しない
 *    <CAN272><CAN273><CAN274> バスオフ処理は未サポートのため，対応しない
 *    <CAN239> I/Oポートの初期化はOS側で対応しているため，依存部では対応しない
 */

#endif /* TOPPERS_CAN_TARGET_H */
