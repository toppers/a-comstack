/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014-2015 by FUJI SOFT INCORPORATED, JAPAN
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
 *  $Id: Can_Prc.h 1064 2015-02-12 04:25:57Z shigihara $
 */

#ifndef TOPPERS_CAN_PRC_H
#define TOPPERS_CAN_PRC_H

#include "Can.h"
#include "Can_InlineSymbols.h"
#include "prc_sil.h"


/*
 *  定数定義
 */

/* 送信バッファ番号 */
#define CAN_TX_BUFF_NO(ch)	((ch) * 16U + 15U)

/* 送信キュー段数(設定値範囲:2〜15) */
#define CAN_TXQ_NUM			15U

/* 送受信FIFOバッファ(受信用)番号 */
#define CAN_TXRX_FIFO_BUFF_NO(ch, hrh_no)	((ch) * 3U + (hrh_no))

/* ビット操作用 */
#define CAN_BIT0	0x00000001U
#define CAN_BIT1	0x00000002U
#define CAN_BIT2	0x00000004U
#define CAN_BIT3	0x00000008U
#define CAN_BIT4	0x00000010U
#define CAN_BIT5	0x00000020U
#define CAN_BIT6	0x00000040U
#define CAN_BIT7	0x00000080U
#define CAN_BIT8	0x00000100U
#define CAN_BIT9	0x00000200U
#define CAN_BIT10	0x00000400U
#define CAN_BIT11	0x00000800U
#define CAN_BIT12	0x00001000U
#define CAN_BIT13	0x00002000U
#define CAN_BIT14	0x00004000U
#define CAN_BIT15	0x00008000U
#define CAN_BIT16	0x00010000U
#define CAN_BIT17	0x00020000U
#define CAN_BIT18	0x00040000U
#define CAN_BIT19	0x00080000U
#define CAN_BIT20	0x00100000U
#define CAN_BIT21	0x00200000U
#define CAN_BIT22	0x00400000U
#define CAN_BIT23	0x00800000U
#define CAN_BIT24	0x01000000U
#define CAN_BIT25	0x02000000U
#define CAN_BIT26	0x04000000U
#define CAN_BIT27	0x08000000U
#define CAN_BIT28	0x10000000U
#define CAN_BIT29	0x20000000U
#define CAN_BIT30	0x40000000U
#define CAN_BIT31	0x80000000U

/*
 *  レジスタ定義
 */
/* RSCAN0 のベースアドレス */
#define RSCAN0_BASE			0xFFD00000U

/* グローバル */
#define RSCAN0GCFG					(*(volatile uint32 *) (RSCAN0_BASE + 0x0084U))
#define RSCAN0GCTR					(*(volatile uint32 *) (RSCAN0_BASE + 0x0088U))
#define RSCAN0GSTS					(*(volatile uint32 *) (RSCAN0_BASE + 0x008CU))
#define RSCAN0GAFLCFG0				(*(volatile uint32 *) (RSCAN0_BASE + 0x009CU))
#define RSCAN0GAFLCFG1				(*(volatile uint32 *) (RSCAN0_BASE + 0x00A0U))
#define RSCAN0GAFLECTR				(*(volatile uint32 *) (RSCAN0_BASE + 0x0098U))

/* チャネル */
#define RSCAN0CmCFG(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0000U + ((ch) * 0x10U)))
#define RSCAN0CmCTR(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0004U + ((ch) * 0x10U)))
#define RSCAN0CmSTS(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0008U + ((ch) * 0x10U)))
#define RSCAN0THLCC(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x0400U + ((ch) * 0x04U)))

/* 受信ルール */
#define RSCAN0GAFLID(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0500U + ((rule) * 0x10U)))
#define RSCAN0GAFLM(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0504U + ((rule) * 0x10U)))
#define RSCAN0GAFLP0(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0508U + ((rule) * 0x10U)))
#define RSCAN0GAFLP1(rule)			(*(volatile uint32 *) (RSCAN0_BASE + 0x050CU + ((rule) * 0x10U)))

/* 送受信FIFOバッファ(受信用) */
#define RSCAN0CFCC(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0118U + ((buf_no) * 0x04U)))
#define RSCAN0CFSTS(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0178U + ((buf_no) * 0x04U)))
#define RSCAN0CFPCTR(buf_no)		(*(volatile uint32 *) (RSCAN0_BASE + 0x01D8U + ((buf_no) * 0x04U)))
#define RSCAN0CFID(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0E80U + ((buf_no) * 0x10U)))
#define RSCAN0CFPTR(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0E84U + ((buf_no) * 0x10U)))
#define RSCAN0CFDF0(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x0E88U + ((buf_no) * 0x10U) + (byte)))
#define RSCAN0CFDF1(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x0E8CU + ((buf_no) * 0x10U) + (byte)))

/* 送信バッファ */
#define RSCAN0TMID(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x1000U + ((buf_no) * 0x10U)))
#define RSCAN0TMPTR(buf_no)			(*(volatile uint32 *) (RSCAN0_BASE + 0x1004U + ((buf_no) * 0x10U)))
#define RSCAN0TMDF0(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x1008U + ((buf_no) * 0x10U) + (byte)))
#define RSCAN0TMDF1(buf_no, byte)	(*(volatile uint8 *) (RSCAN0_BASE + 0x100CU + ((buf_no) * 0x10U) + (byte)))
#define RSCAN0TMSTS(buf_no)			(*(volatile uint8  *) (RSCAN0_BASE + 0x02D0U + ((buf_no) * 0x01U)))

/* 送信キュー */
#define RSCAN0TXQCC(ch)				(*(volatile uint32 *) (RSCAN0_BASE + 0x03A0U + ((ch) * 0x04U)))
#define RSCAN0TXQSTS(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x03C0U + ((ch) * 0x04U)))
#define RSCAN0TXQPCTR(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x03E0U + ((ch) * 0x04U)))

/* 送信履歴 */
#define RSCAN0THLSTS(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0420U + ((ch) * 0x04U)))
#define RSCAN0THLACC(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x1800U + ((ch) * 0x04U)))
#define RSCAN0THLPCTR(ch)			(*(volatile uint32 *) (RSCAN0_BASE + 0x0440U + ((ch) * 0x04U)))

/* 送受信FIFO受信完了割込み用 */
extern uint16 * const	p_irc_can_rec_addr[6];

/* 送信割込み完了用 */
extern uint16 * const	p_irc_can_trx_addr[6];

/* 割込み許可設定マクロ(割込み制御コントローラ) */
#define ENABLE_ICRCANREC(ch)	(*p_irc_can_rec_addr[(ch)] &= ~CAN_BIT7)
#define ENABLE_ICRCANTRX(ch)	(*p_irc_can_trx_addr[(ch)] &= ~CAN_BIT7)

/* 割込み禁止設定マクロ(割込み制御コントローラ) */
#define DISABLE_ICRCANREC(ch)	(*p_irc_can_rec_addr[(ch)] |= CAN_BIT7)
#define DISABLE_ICRCANTRX(ch)	(*p_irc_can_trx_addr[(ch)] |= CAN_BIT7)

/* C_ISO_CANOSCクロック分周レジスタ */
#define CKSC_ICANOSCD_CTL			0xFFF8AA00U

/* 受信ルール数設定(ch0〜3)用 */
#define GAFLCFG0_REG_BIT_SHIFT(ch)	(24U - ((ch) * 8U))

/* 受信ルール数設定(ch4〜5)用 */
#define GAFLCFG1_REG_BIT_SHIFT(ch)	(24U - (((ch) - 4U) * 8U))

/*
 * [CAN077][CAN284][CAN385][CAN386] ターゲット依存部処理
 */
extern const Can_ConfigType	*p_cur_can_config;
extern const CAN_CTRL_INIB	*p_cur_can_ctrl_inib_table;
extern uint8				can_interrupt_nested_cnt[];

/* 内部関数プロトタイプ宣言 */
LOCAL_INLINE void port_init(void);
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
LOCAL_INLINE Can_ReturnType can_target_transmit(uint8 ctrl_id, Can_HwHandleType mb_idx, const Can_PduType *PduInfo);
LOCAL_INLINE boolean can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx);
LOCAL_INLINE boolean can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[]);
LOCAL_INLINE boolean can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx);
LOCAL_INLINE Can_StateTransitionType can_target_get_mode(uint8 ctrl_id);
LOCAL_INLINE void can_target_busy_wait(void);

/* RCCANポート初期化 */
LOCAL_INLINE void
port_init(void)
{
	/* CANで使用するクロック(C_ISO_CANOSC)に メインクロック(MainOsc)を設定する */
	sil_wrw_mem((void *) PROTCMD1, 0x000000A5U);
	sil_wrw_mem((void *) CKSC_ICANOSCD_CTL, 0x00000001U);
	sil_wrw_mem((void *) CKSC_ICANOSCD_CTL, 0xFFFFFFFEU);
	sil_wrw_mem((void *) CKSC_ICANOSCD_CTL, 0x00000001U);

	/* CAN0RXポート(P10_0)初期化 */
	sil_wrh_mem((void *) PFCAE(10U), sil_reh_mem((void *) PFCAE(10U)) & ~0x0001U);
	sil_wrh_mem((void *) PFCE(10U), sil_reh_mem((void *) PFCE(10U)) & ~0x0001U);
	sil_wrh_mem((void *) PFC(10U), sil_reh_mem((void *) PFC(10U)) | 0x0001U);
	sil_wrh_mem((void *) PM(10U), sil_reh_mem((void *) PM(10U)) | 0x0001U);
	sil_wrh_mem((void *) PMC(10U), sil_reh_mem((void *) PMC(10U)) | 0x0001U);

	/* CAN0TXポート(P10_1)初期化 */
	sil_wrh_mem((void *) PFCAE(10U), sil_reh_mem((void *) PFCAE(10U)) & ~0x0002U);
	sil_wrh_mem((void *) PFCE(10U), sil_reh_mem((void *) PFCE(10U)) & ~0x0002U);
	sil_wrh_mem((void *) PFC(10U), sil_reh_mem((void *) PFC(10U)) | 0x0002U);
	sil_wrh_mem((void *) P(10U), sil_reh_mem((void *) P(10U)) | 0x0002U);
	sil_wrh_mem((void *) PM(10U), sil_reh_mem((void *) PM(10U)) & ~0x0002U);
	sil_wrh_mem((void *) PMC(10U), sil_reh_mem((void *) PMC(10U)) | 0x0002U);

	/* CAN1RXポート(P0_2)初期化 */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0004U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0004U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) | 0x0004U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) | 0x0004U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0004U);

	/* CAN1TXポート(P0_3)初期化 */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0008U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0008U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) | 0x0008U);
	sil_wrh_mem((void *) P(0U), sil_reh_mem((void *) P(0U)) | 0x0008U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) & ~0x0008U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0008U);

	/* CAN2RXポート(P0_5)初期化 */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0020U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0020U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x0020U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) | 0x0020U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0020U);

	/* CAN2TXポート(P0_4)初期化 */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) & ~0x0010U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x0010U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x0010U);
	sil_wrh_mem((void *) P(0U), sil_reh_mem((void *) P(0U)) | 0x0010U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) & ~0x0010U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x0010U);

	/* CAN3RX(P1_2)ポート初期化 */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x0004U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) | 0x0004U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x0004U);

	/* CAN3TXポート(P1_3)初期化 */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x0008U);
	sil_wrh_mem((void *) P(1U), sil_reh_mem((void *) P(1U)) | 0x0008U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) & ~0x0008U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x0008U);

	/* CAN4RX(P1_12)ポート初期化 */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x1000U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) | 0x1000U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x1000U);

	/* CAN4TX(P1_13)ポート初期化 */
	sil_wrh_mem((void *) PFC(1U), sil_reh_mem((void *) PFC(1U)) & ~0x2000U);
	sil_wrh_mem((void *) P(1U), sil_reh_mem((void *) P(1U)) | 0x2000U);
	sil_wrh_mem((void *) PM(1U), sil_reh_mem((void *) PM(1U)) & ~0x2000U);
	sil_wrh_mem((void *) PMC(1U), sil_reh_mem((void *) PMC(1U)) | 0x2000U);

	/* CAN5RX(P0_13)ポート初期化 */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) | 0x2000U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x2000U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x2000U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) | 0x2000U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x2000U);

	/* CAN5TX(P0_14)ポート初期化 */
	sil_wrh_mem((void *) PFCAE(0U), sil_reh_mem((void *) PFCAE(0U)) | 0x4000U);
	sil_wrh_mem((void *) PFCE(0U), sil_reh_mem((void *) PFCE(0U)) & ~0x4000U);
	sil_wrh_mem((void *) PFC(0U), sil_reh_mem((void *) PFC(0U)) & ~0x4000U);
	sil_wrh_mem((void *) P(0U), sil_reh_mem((void *) P(0U)) | 0x4000U);
	sil_wrh_mem((void *) PM(0U), sil_reh_mem((void *) PM(0U)) & ~0x4000U);
	sil_wrh_mem((void *) PMC(0U), sil_reh_mem((void *) PMC(0U)) | 0x4000U);

	/* CANトランシーバポート初期化(現状CanTrcvが存在しないため，ここで初期化する) */
	sil_wrh_mem((void *) P(2U), sil_reh_mem((void *) P(2U)) & 0xFFC0U);
	sil_wrh_mem((void *) PM(2U), sil_reh_mem((void *) PM(2U)) & 0xFFC0U);
	sil_wrh_mem((void *) PMC(2U), sil_reh_mem((void *) PMC(2U)) & 0xFFC0U);
}

/* [CAN407] Can_Init：unit_phase1 */
LOCAL_INLINE boolean
can_target_init_unit_phase1(const Can_ConfigType *p_can_config)
{
	boolean	ret;

	/* [CAN239] RCCANポート初期化 */
	port_init();

	/* CAN用RAMクリアステータスフラグチェック */
	if ((RSCAN0GSTS & CAN_BIT3) != 0U) {
		ret = FALSE;
		goto error_exit;
	}

	/* グローバルストップモードを解除 */
	RSCAN0GCTR &= ~CAN_BIT2;

	/* グローバルリセットモードに遷移 */
	RSCAN0GCTR |= CAN_BIT0;

	/* CANで使用するクロックをCKSCLK_ICANOSC(clk_xincan)に設定 */
	RSCAN0GCFG |= CAN_BIT4;

	ret = TRUE;

  error_exit:
	return(ret);
}

/* [CAN407] Can_Init：controller_phase1 */
LOCAL_INLINE boolean
can_target_init_controller_phase1(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* チャネルストップモードを解除 */
	RSCAN0CmCTR(ctrl_id) &= ~CAN_BIT2;

	/* [CAN259] チャネルリセットモードに遷移 */
	RSCAN0CmCTR(ctrl_id) |= CAN_BIT0;

	return(TRUE);
}

/* [CAN407] Can_Init：controller_phase2 */
LOCAL_INLINE boolean
can_target_init_controller_phase2(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	uint32 txdqc_bit;

	/* 送信キュー段数取得 */
	txdqc_bit = CAN_TXQ_NUM << 8U;

	/* [CAN236][CAN237][CAN419] レジスタの初期化 */
	/* 送信キュー設定 */
	/* 割込み要因:1メッセージ送信完了毎 */
	/* 送信キュー段数設定 */
	RSCAN0TXQCC(ctrl_id) = (CAN_BIT13 | txdqc_bit);

	/* 送信履歴バッファ設定 */
	/* 割込み要因:1送信履歴データの格納完了時 */
	/* 送信履歴バッファ割込み許可 */
	RSCAN0THLCC(ctrl_id) = (CAN_BIT9 | CAN_BIT8);

	/* コントローラが4ch以上か判定*/
	if (ctrl_id < 4U) {
		/* 受信ルール数設定(ch0〜3) */
		RSCAN0GAFLCFG0 |= p_ctrl_inib->tnum_hrh << GAFLCFG0_REG_BIT_SHIFT(ctrl_id);
	}
	else {
		/* 受信ルール数設定(ch4〜5) */
		RSCAN0GAFLCFG1 |= p_ctrl_inib->tnum_hrh << GAFLCFG1_REG_BIT_SHIFT(ctrl_id);
	}

	return(TRUE);
}

/* [CAN407] Can_Init：controller_phase3 */
LOCAL_INLINE boolean
can_target_init_controller_phase3(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	return(TRUE);
}

/* [CAN407] Can_Init：受信メールボックス初期化 */
LOCAL_INLINE boolean
can_target_rbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hrh_idx)
{
	static uint8	rx_rule_index_cnt = 0U;
	uint8			rx_rule_index;
	uint32			filter_mask_id;

	/* 受信ルールテーブル書き込み許可 */
	RSCAN0GAFLECTR |= CAN_BIT8;

	/* ルール番号の抽出 */
	rx_rule_index = rx_rule_index_cnt % 16U;

	/* ページ番号が切り替わるか判定 */
	if (rx_rule_index == 0U) {
		/* ページ番号を設定 */
		RSCAN0GAFLECTR = (CAN_BIT8 | (uint32) (rx_rule_index_cnt / 16U));
	}

	/* フィルタマスクインデックス取得 */
	filter_mask_id = GET_RBOX_FILTER_MASK_IDX(ctrl_id, hrh_idx);

	/* フィルタマスクの有無判定 */
	if (filter_mask_id != CAN_NO_MASK_IDX) {
		/* フィルタマスク設定 */
		RSCAN0GAFLM(rx_rule_index) = (CAN_BIT31 | ((uint32) (p_ctrl_inib->p_filtermask_table[filter_mask_id])));
	}
	else {
		/* フィルタマスク設定 */
		RSCAN0GAFLM(rx_rule_index) = (CAN_BIT31 | 0x07FFU);
	}

	/* 受信ルールID設定(CAN-IDレジスタ) */
	RSCAN0GAFLID(rx_rule_index) = (uint32) GET_RBOX_CAN_ID(ctrl_id, hrh_idx);

	/* 受信ルールラベル設定(HRH) */
	RSCAN0GAFLP0(rx_rule_index) = hrh_idx << 16U;

	/* 受信ルールを使用する送受信FIFOバッファ(受信用)の指定 */
	RSCAN0GAFLP1(rx_rule_index) = 1U << (8U + CAN_TXRX_FIFO_BUFF_NO(ctrl_id, hrh_idx));

	/*
	 *  送受信FIFOバッファ(受信用)設定
	 *  1メッセージ受信毎に割込みを入れる
	 */
	RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, hrh_idx)) = (CAN_BIT12 | CAN_BIT9);

	/* 受信ルールインデックスをインクリメント */
	rx_rule_index_cnt++;

	/* 受信ルールテーブル書き込み禁止 */
	RSCAN0GAFLECTR &= ~CAN_BIT8;

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
	/* グローバルリセットモードからグローバル動作モードに遷移 */
	RSCAN0GCTR &= ~(CAN_BIT1 | CAN_BIT0);

	return(TRUE);
}

/* Can_ChangeBaudrate */
LOCAL_INLINE boolean
can_target_change_baudrate(uint8 ctrl_id, const Can_ControllerBaudrateConfigType *p_baudrate_table)
{
	/* [CAN255] ボーレート設定値判定 */
	if (p_baudrate_table->CanControllerBaudRate == 250U) {
		/* チャネルコンフィグレーション設定(ボーレート:250kbps) */
		RSCAN0CmCFG(ctrl_id) = RSCAN_BRP_250;
	}
	else {
		/* チャネルコンフィグレーション設定(ボーレート:500kbps) */
		RSCAN0CmCFG(ctrl_id) = RSCAN_BRP_500;
	}

	return(TRUE);
}

/* Can_SetControllerMode：CAN_T_START */
LOCAL_INLINE boolean
can_target_start_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	uint8 i;

	/* [CAN261] チャネル通信モードに遷移 */
	RSCAN0CmCTR(ctrl_id) &= ~(CAN_BIT1 | CAN_BIT0);

	/* チャネル通信モードになるまでループ(#67) */
	while ((RSCAN0CmSTS(ctrl_id) &CAN_BIT7) == 0U) {
	}

	/* 送信キュー使用有無設定 */
	RSCAN0TXQCC(ctrl_id) |= CAN_BIT0;

	/* 送信履歴バッファ使用有無設定 */
	RSCAN0THLCC(ctrl_id) |= CAN_BIT0;

	/* [CAN204][CAN425] 割込み禁止ネストカウント判定 */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/*
		 *  [CAN196] 割込み許可処理
		 *  送受信FIFOバッファ(受信用)の割込み許可の設定を
		 *  行う場合は送受信FIFOバッファ(受信用)の使用有無
		 *  設定の前に実施する
		 */
		can_target_enable_controller_interrupts(ctrl_id);
	}

	/* 送受信FIFOバッファ(受信用)使用有無設定 */
	for (i = 0; i < p_ctrl_inib->tnum_hrh; i++) {
		RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) |= CAN_BIT0;
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

	/* [CAN263] チャネルリセットモードに遷移 */
	RSCAN0CmCTR(ctrl_id) &= 0xFFFFFFFDU;

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
	uint8 i;

	/* 送受信FIFOバッファ受信割込み禁止(CAN_BIT1をクリア) */
	for (i = 0; i < GET_HRH_NUM(ctrl_id); i++) {
		RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) &= 0xFFFFFFFDU;
	}

	/* 送信履歴バッファ割込み禁止(CAN_BIT8をクリア) */
	RSCAN0THLCC(ctrl_id) &= 0xFFFFFEFFU;

	DISABLE_ICRCANREC(ctrl_id);
	DISABLE_ICRCANTRX(ctrl_id);

	return(TRUE);
}

/* Can_EnableControllerInterrupts */
LOCAL_INLINE boolean
can_target_enable_controller_interrupts(uint8 ctrl_id)
{
	uint8 i;

	/* 送受信FIFOバッファ受信割込み許可 */
	for (i = 0; i < GET_HRH_NUM(ctrl_id); i++) {
		RSCAN0CFCC(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) |= CAN_BIT1;
	}

	/* 送信履歴バッファ割込み許可 */
	RSCAN0THLCC(ctrl_id) |= CAN_BIT8;

	ENABLE_ICRCANREC(ctrl_id);
	ENABLE_ICRCANTRX(ctrl_id);

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
can_target_transmit(uint8 ctrl_id, Can_HwHandleType mb_idx, const Can_PduType *PduInfo)
{
	Can_ReturnType	ret;
	uint8			i;
	uint32			tm_bit;

	/* 送信要求判定 */
	if ((RSCAN0TXQSTS(ctrl_id) &CAN_BIT1) == 0U) {
		/* CAN-ID設定 */
		RSCAN0TMID(CAN_TX_BUFF_NO(ctrl_id)) = (CAN_BIT29 + ((uint32) PduInfo->id));

		/* DLCと送信ラベル情報取得 */
		tm_bit = (uint32) PduInfo->length << 28U;
		tm_bit |= (uint32) mb_idx << 16U;

		/* DLCと送信ラベル設定 */
		RSCAN0TMPTR(CAN_TX_BUFF_NO(ctrl_id)) = tm_bit;

		/* [CAN059][CAN427] データ格納 */
		/* データ設定(0〜3バイト) */
		for (i = 0U; i < 4U; i++) {
			RSCAN0TMDF0(CAN_TX_BUFF_NO(ctrl_id), i) = PduInfo->sdu[i];
		}

		/* 4バイト以降のメッセージ有無判定 */
		if (PduInfo->length > 4U) {
			/* データ設定(4〜7バイト) */
			for (i = 4U; i < PduInfo->length; i++) {
				RSCAN0TMDF1(CAN_TX_BUFF_NO(ctrl_id), (i - 4U)) = PduInfo->sdu[i];
			}
		}
	}
	else {
		ret = CAN_BUSY;
		goto error_exit;
	}

	/* 送信要求(RSCAN0TXQPCTR.TXQPC) */
	RSCAN0TXQPCTR(ctrl_id) = 0xFFU;

	ret = CAN_OK;

  error_exit:
	return(ret);
}

/* Can_IsrRx：受信メールボックス取得 */
LOCAL_INLINE boolean
can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx)
{
	boolean	ret;
	uint8	i;
	uint32	rx_rabel;

	/* HRH初期化(DET処置のエラー検知用) */
	*p_rbox_idx = 0xFFU;

	for (i = 0; i < GET_HRH_NUM(ctrl_id); i++) {
		/* 未読メッセージ有無確認(RSCAN0CFSTS.CFEMP) */
		if ((RSCAN0CFSTS(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) & CAN_BIT0) == 0U) {
			ret = TRUE;

			/* 受信ラベル取得(HRH) */
			rx_rabel = RSCAN0CFPTR(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, i)) & 0x0FFF0000U;

			/* HRH設定 */
			*p_rbox_idx = (Can_HwHandleType) (rx_rabel >> 16U);

			break;
		}
		else {
			/* メールボックスに受信データ無し */
			ret = FALSE;
		}
	}

	return(ret);
}

/* Can_IsrRx：受信IDのデータ取得 */
LOCAL_INLINE boolean
can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[])
{
	uint8	i;
	uint8	local_dlc;

	/* CAN-ID取得(RSCAN0CFID.CFID) */
	*p_can_id = (Can_IdType) RSCAN0CFID(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id));

	/* DLC取得(RSCAN0CFPTR.CFDLC) */
	local_dlc = (uint8) (RSCAN0CFPTR(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)) >> 28U);
	*p_can_dlc = local_dlc;

	/* [CAN012][CAN060][CAN299][CAN300] データ取得 */
	/* データ格納(0〜3バイト) */
	for (i = 0U; i < 4U; i++) {
		can_sdu[i] = RSCAN0CFDF0((CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)), i);
	}

	/* データが4byte以上か判定 */
	if (local_dlc > 4U) {
		/* データ格納(4〜7バイト) */
		for (i = 4U; i < local_dlc; i++) {
			can_sdu[i] = RSCAN0CFDF1((CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)), (i - 4U));
		}
	}

	/* リードポインタ移動(RSCAN0CFPCTR.CFPC) */
	RSCAN0CFPCTR(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)) = 0xFFU;

	/* [CAN420] 送受信FIFO受信割込み要求フラグクリア */
	RSCAN0CFSTS(CAN_TXRX_FIFO_BUFF_NO(ctrl_id, rbox_id)) &= ~CAN_BIT3;

	return(TRUE);
}

/* Can_IsrTx：送信メールボックスチェック取得 */
LOCAL_INLINE boolean
can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx)
{
	boolean	ret;

	/* 送信履歴バッファが空か判定 */
	if ((RSCAN0THLSTS(ctrl_id) &CAN_BIT0) == 0U) {
		/* メールボックスインデックス(送信ラベル)設定 */
		*p_tbox_idx = (Can_HwHandleType) (RSCAN0THLACC(ctrl_id) >> 8U);

		/* 送信履歴バッファのリードポインタ移動 */
		RSCAN0THLPCTR(ctrl_id) = 0xFFU;

		ret = TRUE;
	}
	else {
		/* [CAN420] 送信履歴割込み要求フラグクリア */
		RSCAN0THLSTS(ctrl_id) &= ~CAN_BIT3;

		/* 未リードのメールボックス無し */
		ret = FALSE;
	}

	return(ret);
}

LOCAL_INLINE Can_StateTransitionType
can_target_get_mode(uint8 ctrl_id)
{
	Can_StateTransitionType	ret;
	uint32					cmsts_reg;

	/* チャネルモード取得 */
	cmsts_reg = RSCAN0CmSTS(ctrl_id);

	/* [CAN384][CAN409][CAN410] 動作モード判定 */
	if ((cmsts_reg & CAN_BIT7) != 0U) {
		ret = CAN_T_START;
	}
	else {
		ret = CAN_T_STOP;
	}

	return(ret);
}

/* Can_MainFunction_Write */
LOCAL_INLINE boolean
can_target_polling_tx(uint8 ctrl_id)
{
	/* ポーリングによる送信は未サポート */
	return(FALSE);
}

/* Can_MainFunction_Read */
LOCAL_INLINE boolean
can_target_polling_rx(uint8 ctrl_id)
{
	/* ポーリングによる送信は未サポート */
	return(FALSE);
}

/* Can_MainFunction_BusOff */
LOCAL_INLINE boolean
can_target_polling_busoff(uint8 ctrl_id)
{
	/* バスオフ処理は未サポート */
	return(FALSE);
}

/* Can_MainFunction_Wakeup */
LOCAL_INLINE boolean
can_target_polling_wakeup(uint8 ctrl_id)
{
	/* ウェイクアップは未サポート */
	return(FALSE);
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
 *    <CAN258><CAN290><CAN404><CAN405>論理的なSLEEPモードは未サポートのため，対応しない
 *    <CAN238><CAN242><CAN391><CAN244> fl850f1lでは未サポートのため，対応しない
 *    <CAN062><CAN256><CAN260><CAN422><CAN453> ボーレートの設定は固定のため，対応しない
 *    <CAN272><CAN273><CAN274> バスオフ処理は未サポートのため，対応しない
 */

#endif /* TOPPERS_CAN_PRC_H */
