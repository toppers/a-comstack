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
 *  $Id: Can_Nios2.h 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

#ifndef CAN_NIOS2_H
#define CAN_NIOS2_H

#include "prc_sil.h"

#define CANC_0_BASE		0x08020000U    /* CANコントローラ0のベースアドレス */

#define EXTEND_CAN_ID_LENGTH	18U             /* 拡張分のCAN-ID幅 */
#define ACCEPTANCE_OFFSET		21U             /* アクセプタンスコードレジスタのオフセット */
#define ACCEPTANCE_MASK			0x001FFFFFU     /* アクセプタンスマスクレジスタに設定するマスク */

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
#define ERROR_IRQ			0x00000004U     /* エラー */
#define ERROR_OVW_IRQ		0x00000008U     /* オーバーライトエラー */
#define TXCANCEL_IRQ		0x00000010U     /* 送信キャンセル */
#define BUS_ERROR_IRQ		0x00000080U     /* 打ち落とし */

#define IRQ_SET_DISABLE		0x00000000U     /* [割込み許可レジスタ]全割込み要求を禁止 */
#define IRQ_SET_ENABLE		0x0000001FU     /* [割込み許可レジスタ]指定の割込み要求を許可(ソフトで処理している割り込みのみ許可とする) */
#define TXABORT_CLEAR		0x0000FFFFU     /* [送信キャンセルレジスタ]全メッセージボックス送信キャンセル */
#define TXCMP_CLEAR			0x0000FFFFU     /* [送信完了レジスタ]送信完了ビットクリア */
#define TXABORTCMP_CLEAR	0x0000FFFFU     /* [送信キャンセル完了レジスタ]送信キャンセル完了ビットクリア */
#define RXWAIT_OFF			0x00000000U     /* [受信ウェイトレジスタ]ウェイト処理OFF */
#define RXCMP_CLEAR			0xFFFFFFFFU     /* [受信完了レジスタ]受信完了ビットクリア */
#define RXSELFREQ_CLEAR		0x00000000U     /* [セルフ受信要求レジスタ]送受信要求なし */
#define ERROR_CNT_CLEAR		0x00000060U     /* [エラーカウンタレジスタ]エラーカウンタを初期値にする */
#define BAUDRATE_250		0x80007F03U     /* [クロック制御，バスタイミングレジスタ]ボーレート:250kbps */
//#define BAUDRATE_500		0x80007F01U     /* [クロック制御，バスタイミングレジスタ]ボーレート:500kbps */
#define BAUDRATE_500		0x80012F77U     /* [クロック制御，バスタイミングレジスタ]ボーレート:500kbps */
#define BAUDRATE_500_FD		0x80812F77U     /* [クロック制御，バスタイミングレジスタ]ボーレート:500kbps */
#define BAUDRATE_500_FD_ISO	0x80C12F77U     /* [クロック制御，バスタイミングレジスタ]ボーレート:500kbps */
#define IRQ_RXEN_PERMIT		0xFFFFFFFFU     /* [受信割り込み許可レジスタ]受信割り込み許可 */

#define MASK_CAN_ID_MASK	0x1FFFFFFFU     /* CanId取得マスク */
#define MASK_4BIT			0x0000000FU     /* 4ビットマスク */
#define MASK_8BIT			0x000000FFU     /* 8ビットマスク */

/*  */
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
#define CANC_TXMBOX_DATA0_REG				0x2000U
#define CANC_TXMBOX_DATA1_REG				0x2004U
#define CANC_TXMBOX_DATA2_REG				0x2008U
#define CANC_TXMBOX_DATA3_REG				0x200CU
#define CANC_TXMBOX_DATA4_REG				0x2010U
#define CANC_TXMBOX_DATA5_REG				0x2014U
#define CANC_TXMBOX_DATA6_REG				0x2018U
#define CANC_TXMBOX_DATA7_REG				0x201CU
#define CANC_TXMBOX_DATA8_REG				0x2020U
#define CANC_TXMBOX_DATA9_REG				0x2024U
#define CANC_TXMBOX_DATA10_REG				0x2028U
#define CANC_TXMBOX_DATA11_REG				0x202CU
#define CANC_TXMBOX_DATA12_REG				0x2030U
#define CANC_TXMBOX_DATA13_REG				0x2034U
#define CANC_TXMBOX_DATA14_REG				0x2038U
#define CANC_TXMBOX_DATA15_REG				0x203CU
#define CANC_TXMBOX_DATA16_REG				0x2040U
#define CANC_TXMBOX_DATA17_REG				0x2044U

#define CANC_RXMBOX_DATA0_REG				0x4000U
#define CANC_RXMBOX_DATA1_REG				0x4004U
#define CANC_RXMBOX_DATA2_REG				0x4008U
#define CANC_RXMBOX_DATA3_REG				0x400CU
#define CANC_RXMBOX_DATA4_REG				0x4010U
#define CANC_RXMBOX_DATA5_REG				0x4014U
#define CANC_RXMBOX_DATA6_REG				0x4018U
#define CANC_RXMBOX_DATA7_REG				0x401CU
#define CANC_RXMBOX_DATA8_REG				0x4020U
#define CANC_RXMBOX_DATA9_REG				0x4024U
#define CANC_RXMBOX_DATA10_REG				0x4028U
#define CANC_RXMBOX_DATA11_REG				0x402CU
#define CANC_RXMBOX_DATA12_REG				0x4030U
#define CANC_RXMBOX_DATA13_REG				0x4034U
#define CANC_RXMBOX_DATA14_REG				0x4038U
#define CANC_RXMBOX_DATA15_REG				0x403CU
#define CANC_RXMBOX_DATA16_REG				0x4040U
#define CANC_RXMBOX_DATA17_REG				0x4044U
//#define CANC_TXMBOX_DATA0_REG					0x0100U
//#define CANC_TXMBOX_DATA1_REG					0x0104U
//#define CANC_TXMBOX_DATA2_REG					0x0108U
//#define CANC_TXMBOX_DATA3_REG					0x010CU
//#define CANC_RXMBOX_DATA0_REG					0x0200U
//#define CANC_RXMBOX_DATA1_REG					0x0204U
//#define CANC_RXMBOX_DATA2_REG					0x0208U
//#define CANC_RXMBOX_DATA3_REG					0x020CU



#define SIL_REW_IOP_CANC_0_BASE(mem)		sil_rew_iop((void *) (CANC_0_BASE + (mem)))
#define SIL_WRW_IOP_CANC_0_BASE(mem, data)	sil_wrw_iop((void *) (CANC_0_BASE + (mem)), (data))

/* 読取り用レジスタアクセスマクロ */
#define CANC_RD_TXCMP_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_TXCMP_REG)
#define CANC_RD_TXABORTCMP_REG()					SIL_REW_IOP_CANC_0_BASE(CANC_TXABORTCMP_REG)
#define CANC_RD_RXWAIT_REG()						SIL_REW_IOP_CANC_0_BASE(CANC_RXWAIT_REG)
#define CANC_RD_RXCMP_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_RXCMP_REG)
#define CANC_RD_RXOVERWRITE_REG()					SIL_REW_IOP_CANC_0_BASE(CANC_RXOVERWRITE_REG)
#define CANC_RD_STATUS_REG()						SIL_REW_IOP_CANC_0_BASE(CANC_STATUS_REG)
#define CANC_RD_IRQ_REG()							SIL_REW_IOP_CANC_0_BASE(CANC_IRQ_REG)
#define CANC_RD_CLKDIV_BUSTIM_REG()					SIL_REW_IOP_CANC_0_BASE(CANC_CLKDIV_BUSTIM_REG)
#define CANC_RD_ERROR_CNT_REG()						SIL_REW_IOP_CANC_0_BASE(CANC_ERROR_CNT_REG)
#define CANC_RD_RXMBOX_DATA0_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA0_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA1_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA1_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA2_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA2_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA3_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA3_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA4_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA4_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA5_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA5_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA6_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA6_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA7_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA7_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA8_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA8_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA9_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA9_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA10_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA10_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA11_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA11_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA12_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA12_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA13_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA13_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA14_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA14_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA15_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA15_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA16_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA16_REG + (0x0100U * (box_num))))
#define CANC_RD_RXMBOX_DATA17_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA17_REG + (0x0100U * (box_num))))

//#define CANC_RD_RXMBOX_DATA0_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA0_REG + (0x0010U * (box_num))))
//#define CANC_RD_RXMBOX_DATA1_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA1_REG + (0x0010U * (box_num))))
//#define CANC_RD_RXMBOX_DATA2_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA2_REG + (0x0010U * (box_num))))
//#define CANC_RD_RXMBOX_DATA3_REG(box_num)			SIL_REW_IOP_CANC_0_BASE((CANC_RXMBOX_DATA3_REG + (0x0010U * (box_num))))

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
#define CANC_WR_TXMBOX_DATA0_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA0_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA1_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA1_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA2_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA2_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA3_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA3_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA4_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA4_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA5_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA5_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA6_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA6_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA7_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA7_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA8_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA8_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA9_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA9_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA10_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA10_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA11_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA11_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA12_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA12_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA13_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA13_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA14_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA14_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA15_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA15_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA16_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA16_REG + (0x0100U * (box_num))), data)
#define CANC_WR_TXMBOX_DATA17_REG(data, box_num)	SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA17_REG + (0x0100U * (box_num))), data)
//#define CANC_WR_TXMBOX_DATA0_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA0_REG + (0x0010U * (box_num))), data)
//#define CANC_WR_TXMBOX_DATA1_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA1_REG + (0x0010U * (box_num))), data)
//#define CANC_WR_TXMBOX_DATA2_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA2_REG + (0x0010U * (box_num))), data)
//#define CANC_WR_TXMBOX_DATA3_REG(data, box_num)		SIL_WRW_IOP_CANC_0_BASE((CANC_TXMBOX_DATA3_REG + (0x0010U * (box_num))), data)


#endif /* CAN_NIOS2_H */
