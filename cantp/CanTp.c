/*
 *  TOPPERS/A-CANTP
 *      Automotive CANTP
 *
 *  Copyright (C) 2016-2017 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2016-2017 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2016-2017 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2016-2017 by SCSK Corporation, JAPAN
 *  Copyright (C) 2016-2017 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2016-2017 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2016-2017 by Witz Corporation
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
 *  $Id: CanTp.c 3480 2017-03-08 11:51:15Z suzuki-kawaguchi $
 */

/* CanTp.c */

/*
 *  開発方針
 *  - [SWS_CanTp_00033] ISO 15765-2とISO 15765-4に基づいた仕様とする
 *  - [SWS_CanTp_00216] CANTPの機能を実現するためにCANIF,PDURのインタフェースが必要となる
 *  - [SWS_CanTp_00285] 接続チャネルはCANTPの内部でのみ使用され，外部からアクセスできない
 *  - [NCanTp_00032] 各NPDUは１つのNSDUからのみ参照可能
 */

/* [SWS_CanTp_00156] */
#include "CanTp.h"
#include "CanTp_Cfg.h"		/* [SWS_CanTp_00221] */
#include "CanTp_Cbk.h"

#if CANTP_DEV_ERROR_DETECT == STD_ON
#include "Det.h"			/* [SWS_CanTp_00264] */
#endif /* CANIF_PUBLIC_DEV_ERROR_DETECT == STD_ON */

#include "MemMap.h"

/* PduR_CanTp.hはPduRジェネレータにより生成される */
#include "PduR_CanTp.h"		/* [NCanTp_00033] */
/* SchM_CanTp.hはRTEジェネレータにより生成される */
#include "SchM_CanTp.h"

#include "CanIf.h"			/* [NCanTp_00033] */

/*
 *  [SWS_CanTp_00296] 内部関数の戻り値
 */
typedef enum {
	CANTP_E_OK,
	CANTP_E_NOT_OK,
	CANTP_E_BUSY
} CanTp_ReturnType;

/*
 *  内部関数のプロトタイプ宣言
 */
/* 共通 */
static void init_internal(void);

/* 受信処理 */
LOCAL_INLINE void rcv_sf(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType can_dlc);
LOCAL_INLINE void rcv_sf_sub(PduIdType CanTpPduId, uint8* data, PduLengthType sf_dl);
LOCAL_INLINE void rcv_ff(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType len);
LOCAL_INLINE void rcv_ff_sub(PduIdType CanTpPduId, uint8* data, PduLengthType len, PduLengthType ff_dl);
LOCAL_INLINE void rcv_cf(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType len, uint8 padding_err);
LOCAL_INLINE void rcv_cf_sub(PduIdType CanTpPduId, uint8* data, PduLengthType len);
LOCAL_INLINE void rcv_fc(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType len, uint8 padding_err);
LOCAL_INLINE void rcv_fc_sub(PduIdType CanTpPduId, const uint8 data[], PduLengthType len);
LOCAL_INLINE uint8* chk_address_info(const NSDU_INIB *p_nsdu_inib, uint8 data[], PduLengthType *ret_len);

/* 受信時状態確認処理 */
LOCAL_INLINE CanTp_ReturnType chk_state_RcvSf(PduIdType CanTpPduId);
LOCAL_INLINE CanTp_ReturnType chk_state_RcvFf(PduIdType CanTpPduId);
LOCAL_INLINE CanTp_ReturnType chk_state_RcvCf(PduIdType CanTpPduId);
LOCAL_INLINE CanTp_ReturnType chk_state_RcvFc(PduIdType CanTpPduId);

/* DLCチェック処理 */
LOCAL_INLINE CanTp_ReturnType chk_dlc(PduLengthType len, uint8 taType);

/* 送信処理 */
LOCAL_INLINE void snd_sf(PduIdType CanTpPduId, PduLengthType SduLen);
LOCAL_INLINE CanTp_ReturnType make_sf(PduIdType CanTpPduId, PduLengthType *sf_dl, uint8 data[], PduLengthType *ret_len);
LOCAL_INLINE void snd_ff(PduIdType CanTpPduId, PduLengthType SduLen);
LOCAL_INLINE CanTp_ReturnType make_ff(PduIdType CanTpPduId, PduLengthType *ff_dl, uint8 data[], PduLengthType *ret_len);
LOCAL_INLINE void snd_cf(PduIdType CanTpPduId, PduLengthType SduLen);
LOCAL_INLINE CanTp_ReturnType make_cf(PduIdType CanTpPduId, PduLengthType *data_len, uint8 data[], PduLengthType *ret_len);
LOCAL_INLINE void snd_fc(PduIdType CanTpPduId, uint8 fs_type);
LOCAL_INLINE CanTp_ReturnType make_fc(PduIdType CanTpPduId, uint8 fs_type, uint8 data[], PduLengthType *ret_len);
LOCAL_INLINE uint8* set_address_info(const NSDU_INIB *p_nsdu_inib, uint8 data[], uint8 *ret_len);

/* 送信時状態確認処理 */
LOCAL_INLINE CanTp_ReturnType chk_state_Snd(PduIdType CanTpPduId);

/* 送信完了処理 */
LOCAL_INLINE void end_cf(CH_TX_CB *p_ch_tx_cb, const NSDU_INIB *p_nsdu_inib);
LOCAL_INLINE void end_fc(CH_RX_CB *p_ch_rx_cb, const NSDU_INIB *p_nsdu_inib);

/* チャネル受信周期処理 */
LOCAL_INLINE void ch_rcv_main(CH_RX_CB *p_ch_rx_cb);
LOCAL_INLINE void rcv_wait(CH_RX_CB *p_ch_rx_cb);

/* チャネル送信周期処理 */
LOCAL_INLINE void ch_snd_main(CH_TX_CB *p_ch_tx_cb);

/* タイムアウト確認処理 */
LOCAL_INLINE CanTp_ReturnType chk_timeout(uint8 timer, uint32 *time_cnt);

/* STminカウント値取得処理 */
LOCAL_INLINE uint8 get_stmin_cnt(uint8 stmin);

/*
 *  現在実行中のCanTpコンフィギュレーション情報
 */
static const CanTp_ConfigType	*p_cur_cantp_config;

/*
 *  CanTpの初期化状態[SWS_CanTp_00168][SWS_CanTp_00161]
 */
static CanTp_StatusType			cantp_state = CANTP_UNINIT;

/* CANFD 送信DLC変換テーブル */
/* 0-8:0-8 */
/* 9-12:12 */
/* 13-16:16 */
/* 17-20:20 */
/* 21-24:24 */
/* 25-32:32 */
/* 33-48:48 */
/* 49-64:64 */
static const uint8	cantp_canfd_dlc_snd_table[65] = {
	0U,		1U,		2U,		3U,		4U,		5U,		6U,		7U,
	8U,		12U,	12U,	12U,	12U,	16U,	16U,	16U,
	16U,	20U,	20U,	20U,	20U,	24U,	24U,	24U,
	24U,	32U,	32U,	32U,	32U,	32U,	32U,	32U,
	32U,	48U,	48U,	48U,	48U,	48U,	48U,	48U,
	48U,	48U,	48U,	48U,	48U,	48U,	48U,	48U,
	48U,	64U,	64U,	64U,	64U,	64U,	64U,	64U,
	64U,	64U,	64U,	64U,	64U,	64U,	64U,	64U,
	64U
};

/* CANFD 受信DLCチェックテーブル */
/* 1-8,12,16,20,24,32,48,64の場合正常 */
static const uint8	cantp_canfd_dlc_rcv_chk_table[65] = {
	CANTP_FALSE,	CANTP_TRUE,		CANTP_TRUE,		CANTP_TRUE,		CANTP_TRUE,		CANTP_TRUE,		CANTP_TRUE,		CANTP_TRUE,
	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_TRUE,		CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,	CANTP_FALSE,
	CANTP_TRUE
};

/*
 *  [SWS_CanTp_00208] CanTp_Init
 */
void
CanTp_Init(const CanTp_ConfigType* CfgPtr)
{
	boolean						config_invalid = TRUE;				/* 無効コンフィグ確認用 */
	uint32						j;									/* ループカウンタ */
	
	SchM_Enter_CanTp_Reentrant_0();	/* [NCanTp_00008] */

	/* [SWS_CanTp_00169]未初期化状態のときのみポストビルドコンフィグの更新が可能 */
	if (cantp_state == CANTP_UNINIT) {
		if (CfgPtr == NULL_PTR) {
			/* [NCanTp_00011]デフォルトコンフィグレーション設定 */
			p_cur_cantp_config = &cantp_config[CANTP_ZERO];
		}
		else {
			/* [NCanTp_00031] 引数configが不正 */
			for (j = CANTP_ZERO; j < CANTP_CONFIG_NUM; j++) {
				if (CfgPtr == &cantp_config[j]) {
					config_invalid = FALSE;
					break;
				}
			}
			CANTP_CHECK_PARAM(config_invalid == FALSE, CanTpServiceId_Init, CANTP_E_INIT_FAILED);
			
			/* 現在実行中のコンフィグレーション情報を保持 */
			p_cur_cantp_config = CfgPtr;
		}
	}
	
	/* [SWS_CanTp_00111][SWS_CanTp_00273] 初期化状態で呼ばれた場合も同様に初期化する */
	
	/* [SWS_CanTp_00030] グローバル変数，内部変数を初期化 */
	init_internal();

	/* [SWS_CanTp_00170][SWS_CanTp_00161] 初期化状態 */
	cantp_state = CANTP_INIT;

	SchM_Exit_CanTp_Reentrant_0();	/* [NCanTp_00008] */

  error_exit:
	return;
}


/*
 *  [SWS_CanTp_00210] CanTp_GetVersionInfo
 */
/* [ECUC_CanTp_00283] */
#if CANTP_VERSION_INFO_API == STD_ON
void
CanTp_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
	/* [SWS_CanTp_00319][SWS_CanTp_00352] NULLチェック */
	CANTP_CHECK_PARAM((versioninfo != NULL_PTR), CanTpServiceId_GetVersionInfo, CANTP_E_PARAM_POINTER);

	/* [SWS_CanTp_00267][NCanTp_00012] ソフトウェアバージョンの取得 */
	versioninfo->vendorID = CANTP_VENDOR_ID;
	versioninfo->moduleID = CANTP_MODULE_ID;
	versioninfo->sw_major_version = CANTP_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CANTP_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CANTP_SW_PATCH_VERSION;

  error_exit:
	return;
}
#endif /* CANTP_VERSION_INFO_API == STD_ON */


/*
 *  [SWS_CanTp_00211] CanTp_Shutdown
 */
void
CanTp_Shutdown(void)
{
	uint16						ch;									/* チャネル用ループカウンタ */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */

	SchM_Enter_CanTp_Reentrant_0();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_Shutdown, CANTP_E_UNINIT);
	
	/* [SWS_CanTp_00010] CanTpモジュールを正常に停止 */
	/* [SWS_CanTp_00202] 通信切断、リソースの解放 */
	/* [SWS_CanTp_00200] Pendingフレームの送受信については通知しない */
	
	/* 状態を初期化 */
	for (ch = CANTP_ZERO; ch < GET_CH_NUM(); ch++) {
		/* 受信 */
		p_ch_rx_cb = GET_CH_RX_CB(ch);
		/* 管理ブロックのデータ初期化 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		p_ch_rx_cb->rx_time = CANTP_TIME_STOP;
		p_ch_rx_cb->rx_time_cnt = CANTP_TIMECNT_CLR;
		
		/* 送信 */
		p_ch_tx_cb = GET_CH_TX_CB(ch);
		/* 管理ブロックのデータ初期化 */
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		p_ch_tx_cb->tx_time = CANTP_TIME_STOP;
		p_ch_tx_cb->tx_time_cnt = CANTP_TIMECNT_CLR;
	}
	
	/* 現在使用中のコンフィグクリア */
	p_cur_cantp_config = (CanTp_ConfigType*)NULL_PTR;

	/* [SWS_CanTp_00202] 未初期化状態 */
	cantp_state = CANTP_UNINIT;

  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return;
}


/*
 *  [SWS_CanTp_00212] CanTp_Transmit
 */
/* [SWS_CanTp_00096] 同時にいくつかの通信をサポート */
/* [SWS_CanTp_00176] 非同期 */
/* [SWS_CanTp_00225][SWS_CanTp_00299] specific connectionではCanTpTxInfoPtr->SduLengthのみ使用し、*/
/*                                    CanTpTxInfoPtr->SduDataPtrは使用しない                    */
/* [SWS_CanTp_00294] エラーを検出した場合E_NOT_OKを返す */
/*  */
Std_ReturnType
CanTp_Transmit(PduIdType CanTpTxSduId, const PduInfoType* CanTpTxInfoPtr)
{
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	Std_ReturnType				ercd = E_NOT_OK;					/* 戻り値 */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */

	SchM_Enter_CanTp_Reentrant_0();
	
	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_Transmit, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [NCanTp_00013] IDチェック */
	CANTP_CHECK_PARAM((CanTpTxSduId < GET_NSDU_NUM()), CanTpServiceId_Transmit, CANTP_E_PARAM_ID);
	/* [SWS_CanTp_00321][SWS_CanTp_00352] NULLチェック */
	CANTP_CHECK_PARAM((CanTpTxInfoPtr != NULL_PTR), CanTpServiceId_Transmit, CANTP_E_PARAM_POINTER);

	p_nsdu_inib = GET_NSDU_INIB(CanTpTxSduId);	/* NSDU初期化ブロック */
	
	/* [NCanTp_00013] 送信NSDUチェック */
	CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_SEND), CanTpServiceId_Transmit, CANTP_E_PARAM_ID);

	ch = GET_CH_FROM_ID(CanTpTxSduId);	/* Id->Ch番号取得 */
	p_ch_tx_cb = GET_CH_TX_CB(ch);		/* チャネル送信管理ブロック */
	
	/* [SWS_CanTp_00123][SWS_CanTp_00288] 送信接続チャネルが使用中の場合送信要求は破棄 */
	/* [NCanTp_00013][SWS_CanTp_00206] 使用中のSDUIDの場合は何もしない */
	retCanTp = chk_state_Snd(CanTpTxSduId);
	if (retCanTp == CANTP_E_OK) {
		/* [SWS_CanTp_00092] 機能アドレスの確認 */
		if ((p_nsdu_inib->CanTpTaType == CANTP_FUNCTIONAL) ||
			(p_nsdu_inib->CanTpTaType == CANTP_CANFD_FUNCTIONAL)) {
			/* 指定されたデータ長がSFデータ長最大値以下 */
			if (CanTpTxInfoPtr->SduLength <= p_nsdu_inib->sdu_max_sf) {
				/* 送信情報保持 */
				p_ch_tx_cb->id = CanTpTxSduId;
				p_ch_tx_cb->sdu_len = CanTpTxInfoPtr->SduLength;
				p_ch_tx_cb->data_len = CanTpTxInfoPtr->SduLength;
				
				/* SF送信待ち状態 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_SND_SF;
				ercd = E_OK;
			}
			/* 指定されたデータ長がSFデータ長最大値を超える */
			else {
				/* [SWS_CanTp_00093] 機能アドレスかつSFで送信できないデータ長 */
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_Transmit, CANTP_E_INVALID_TATYPE);
				/* 戻り値は初期化時に設定済み(E_NOT_OK) */
			}
		}
		
		/* 物理アドレス */
		else {
			/* 指定されたデータ長がSDUデータ長最大値以下 */
			if (CanTpTxInfoPtr->SduLength <= p_nsdu_inib->sdu_max_ff) {
				/* 送信情報保持 */
				p_ch_tx_cb->id = CanTpTxSduId;
				p_ch_tx_cb->sdu_len = CanTpTxInfoPtr->SduLength;
				p_ch_tx_cb->data_len = CanTpTxInfoPtr->SduLength;
				
				/* データ長判定 */
				if (CanTpTxInfoPtr->SduLength <= p_nsdu_inib->sdu_max_sf) {
					/* [SWS_CanTp_00231] SFで送信できるデータ長の場合シングルフレーム送信 */
					/* SF送信待ち状態 */
					p_ch_tx_cb->tx_status = CANTP_STATUS_SND_SF;
				}
				else {
					/* [SWS_CanTp_00232] SFで送信できないデータ長の場合マルチフレーム送信 */
					p_ch_tx_cb->fc_cts = CANTP_FALSE;
					/* FF送信待ち状態 */
					p_ch_tx_cb->tx_status = CANTP_STATUS_SND_FF;
				}
				ercd = E_OK;
			}
			/* 指定されたデータ長がSDUデータ長最大値を超える */
			else {
				/* DETエラー */
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_Transmit, CANTP_E_PARAM_ID);
				/* 戻り値は初期化時に設定済み(E_NOT_OK) */
			}
		}
	}

  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return(ercd);
}


/*
 *  [SWS_CanTp_00246] CanTp_CancelTransmit
 */
/* [SWS_CanTp_00294] エラーを検出した場合E_NOT_OKを返す */
Std_ReturnType
CanTp_CancelTransmit(PduIdType CanTpTxSduId)
{
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	Std_ReturnType				ercd = E_NOT_OK;					/* 戻り値 */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	SchM_Enter_CanTp_Reentrant_0();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_CancelTransmit, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [SWS_CanTp_00254] IDチェック */
	CANTP_CHECK_PARAM((CanTpTxSduId < GET_NSDU_NUM()), CanTpServiceId_CancelTransmit, CANTP_E_PARAM_ID);

	p_nsdu_inib = GET_NSDU_INIB(CanTpTxSduId);	/* NSDU初期化ブロック */
	
	/* 送信NSDUチェック */
	CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_SEND), CanTpServiceId_CancelTransmit, CANTP_E_PARAM_ID);
	
	/* [SWS_CanTp_00242] CanTpTc（機能の有効無効）チェック */
	if (p_nsdu_inib->CanTpTc == CANTP_ON) {
		ch = GET_CH_FROM_ID(CanTpTxSduId);	/* Id->Ch番号取得 */
		p_ch_tx_cb = GET_CH_TX_CB(ch);		/* チャネル送信管理ブロック */
		
		/* 送信中のIDと一致する場合 */
		if (p_ch_tx_cb->id == CanTpTxSduId) {
			/* [SWS_CanTp_00254] 送信状態確認 */
			switch (p_ch_tx_cb->tx_status) {
			case CANTP_STATUS_SND_SF :	/* SF送信待ち */
			case CANTP_STATUS_SND_FF :	/* FF送信待ち */
			case CANTP_STATUS_END_FF :	/* FF送信完了待ち */
			case CANTP_STATUS_WAIT_FC :	/* FC受信待ち */
			case CANTP_STATUS_SND_CF :	/* CF送信待ち */
				/* [SWS_CanTp_00274][SWS_CanTp_00243] 中止処理を行う */
				PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
				/* [SWS_CanTp_00255][SWS_CanTp_00256] 送信中止 */
				/* 送信異常通知 */
				PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
				/* タイマ停止 */
				CANTP_CLR_TX_TIMER(p_ch_tx_cb);
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
				ercd = E_OK;
				break;
			case CANTP_STATUS_END_CF :	/* CF送信完了待ち */
				/* 最後でないCF送信要求済み（残りのデータ長 > CFデータ長） */
				if (p_ch_tx_cb->data_len != (PduLengthType) CANTP_ZERO) {
					/* [SWS_CanTp_00274][SWS_CanTp_00243] 中止処理を行う */
					PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
					
					/* [SWS_CanTp_00255][SWS_CanTp_00256] 送信中止 */
					/* 送信異常通知 */
					PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
					/* タイマ停止 */
					CANTP_CLR_TX_TIMER(p_ch_tx_cb);
					/* 送信状態更新 */
					p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
					ercd = E_OK;
				}
				/* 最後のCF送信要求済み（残りのデータ長 <= CFデータ長）の場合は破棄する */
				break;
			case CANTP_STATUS_IDLE :	/* IDLE */
				/* [SWS_CanTp_00254][SWS_CanTp_00352] 送信状態確認 */
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_CancelTransmit, CANTP_E_OPER_NOT_SUPPORTED);
				/* 戻り値は初期化時に設定済み(E_NOT_OK) */
				break;
			case CANTP_STATUS_END_SF :	/* SF送信完了待ち */
			default :
				/* 何もしない */
				/* 戻り値は初期化時に設定済み(E_NOT_OK) */
				break;
			}
		}
		else {
			/* [SWS_CanTp_00254][SWS_CanTp_00352] 送信状態確認 */
			CANTP_SWITCH_DET_ERROR(CanTpServiceId_CancelTransmit, CANTP_E_OPER_NOT_SUPPORTED);
			/* 戻り値は初期化時に設定済み(E_NOT_OK) */
		}
	}
	
  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return(ercd);
}


/*
 *  [SWS_CanTp_00257] CanTp_CancelReceive
 */
/* [SWS_CanTp_00294] エラーを検出した場合E_NOT_OKを返す */
Std_ReturnType
CanTp_CancelReceive(PduIdType CanTpRxSduId)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	Std_ReturnType				ercd = E_NOT_OK;					/* 戻り値 */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	SchM_Enter_CanTp_Reentrant_0();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_CancelReceive, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [SWS_CanTp_00260] IDチェック */
	CANTP_CHECK_PARAM((CanTpRxSduId < GET_NSDU_NUM()), CanTpServiceId_CancelReceive, CANTP_E_PARAM_ID);

	p_nsdu_inib = GET_NSDU_INIB(CanTpRxSduId);	/* NSDU初期化ブロック */
	
	/* 送信NSDUチェック */
	CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_CancelReceive, CANTP_E_PARAM_ID);
	
	/* [NCanTp_00024] CanTpTc（機能の有効無効）チェック */
	if (p_nsdu_inib->CanTpTc == CANTP_ON) {
		/* Id->Ch番号取得 */
		ch = GET_CH_FROM_ID(CanTpRxSduId);
		p_ch_rx_cb = GET_CH_RX_CB(ch);
		
		/* 受信中のIDと一致する場合 */
		if (p_ch_rx_cb->id == CanTpRxSduId) {
			/* [SWS_CanTp_00260] 受信状態確認 */
			switch (p_ch_rx_cb->rx_status) {
			case CANTP_STATUS_SND_FC :	/* FC送信待ち */
			case CANTP_STATUS_END_FC :	/* FC送信完了待ち */
				/* [SWS_CanTp_00257] 中止処理を行う */
				PduR_id = ((const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Indication;
				/* [SWS_CanTp_00261][SWS_CanTp_00263] */
				/* 受信異常通知 */
				PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
				/* タイマ停止 */
				CANTP_CLR_RX_TIMER(p_ch_rx_cb);
				/* 受信状態更新 */
				p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
				ercd = E_OK;
				break;
			case CANTP_STATUS_WAIT_CF :	/* CF受信待ち */
				/* 最後でないCF受信待ち（残りのデータ長 > CFデータ長） */
				if (p_ch_rx_cb->data_len > p_nsdu_inib->sdu_max_cf_data) {
					/* 中止処理を行う */
					PduR_id = ((const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Indication;
					/* [SWS_CanTp_00261][SWS_CanTp_00263] 受信中止 */
					/* 受信異常通知 */
					PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
					/* タイマ停止 */
					CANTP_CLR_RX_TIMER(p_ch_rx_cb);
					/* 受信状態更新 */
					p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
					ercd = E_OK;
				}
				/* 最後のCF受信待ち（残りのデータ長 <= CFデータ長）の場合は破棄する */
				break;
			case CANTP_STATUS_IDLE :	/* IDLE */
				/* [SWS_CanTp_00260][SWS_CanTp_00352] 受信状態確認 */
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_CancelReceive, CANTP_E_OPER_NOT_SUPPORTED);
				/* 戻り値は初期化時に設定済み(E_NOT_OK) */
				break;
			default :
				/* [SWS_CanTp_00262] 何もしない */
				/* 戻り値は初期化時に設定済み(E_NOT_OK) */
				break;
			}
		}
		else {
			/* [SWS_CanTp_00260][SWS_CanTp_00352] 受信状態確認 */
			CANTP_SWITCH_DET_ERROR(CanTpServiceId_CancelReceive, CANTP_E_OPER_NOT_SUPPORTED);
			/* 戻り値は初期化時に設定済み(E_NOT_OK) */
		}
	}
	
  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return(ercd);
}


/*
 *  [SWS_CanTp_00302] CanTp_ChangeParameter
 */
/* [SWS_CanTp_00294] エラーを検出した場合E_NOT_OKを返す */
/* [ECUC_CanTp_00299] */
#if CANTP_CHANGE_PARAMETER_API == STD_ON
Std_ReturnType
CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	Std_ReturnType				ercd = E_NOT_OK;					/* 戻り値 */

	SchM_Enter_CanTp_Reentrant_0();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_ChangeParameter, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [SWS_CanTp_00305] IDチェック */
	CANTP_CHECK_PARAM((id < GET_NSDU_NUM()), CanTpServiceId_ChangeParameter, CANTP_E_PARAM_ID);
	
	p_nsdu_inib = GET_NSDU_INIB(id);	/* NSDU初期化ブロック */
	
	/* 受信NSDUチェック */
	CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_ChangeParameter, CANTP_E_PARAM_ID);
	/* パラメータ */
	CANTP_CHECK_PARAM((value <= CANTP_UINT8_MAX), CanTpServiceId_ChangeParameter, CANTP_E_PARAM_ID);

	/* 各情報取得 */
	ch = GET_CH_FROM_ID(id);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);

	/* [SWS_CanTp_00304] 受信中のSDUIDの場合は何もしない */
	/* [SWS_CanTp_00303] 受信中でないSDUIDの場合パラメータの変更をする */
	if ((p_ch_rx_cb->rx_status == CANTP_STATUS_IDLE) || (p_ch_rx_cb->id != id)) {
		/* パラメータチェック */
		if (parameter == TP_STMIN) {
			/* [SWS_CanTp_00091] STminの設定 */
			p_rx_inib->p_rx_cb->stmin = (uint8) value;
			ercd = E_OK;
		}
		else if (parameter == TP_BS) {
			/* [SWS_CanTp_00091] BSの設定 */
			p_rx_inib->p_rx_cb->bs = (uint8) value;
			ercd = E_OK;
		}
		else {
			/* パラメータエラー通知 */
			CANTP_SWITCH_DET_ERROR(CanTpServiceId_ChangeParameter, CANTP_E_PARAM_ID);
			/* 戻り値は初期化時に設定済み(E_NOT_OK) */
		}
	}

  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return(ercd);
}
#endif /* CANTP_CHANGE_PARAMETER_API == STD_ON */


/*
 *  [SWS_CanTp_00323] CanTp_ReadParameter
 */
/* [SWS_CanTp_00294] エラーを検出した場合E_NOT_OKを返す */
/* [ECUC_CanTp_00300] */
#if CANTP_READ_PARAMETER_API == STD_ON
Std_ReturnType
CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16* value)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	Std_ReturnType				ercd = E_NOT_OK;					/* 戻り値 */

	SchM_Enter_CanTp_Reentrant_0();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_ReadParameter, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [SWS_CanTp_00324] IDチェック */
	CANTP_CHECK_PARAM((id < GET_NSDU_NUM()), CanTpServiceId_ReadParameter, CANTP_E_PARAM_ID);
	
	p_nsdu_inib = GET_NSDU_INIB(id);	/* NSDU初期化ブロック */
	
	/* 受信NSDUチェック */
	CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_ReadParameter, CANTP_E_PARAM_ID);
	
	/* [SWS_CanTp_00352] NULLチェック */
	CANTP_CHECK_PARAM((value != NULL_PTR), CanTpServiceId_ReadParameter, CANTP_E_PARAM_POINTER);

	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	
	/* パラメータチェック */
	if (parameter == TP_STMIN) {
		/* STminの取得 */
		*value = (uint16) (p_rx_inib->p_rx_cb->stmin);
		ercd = E_OK;
	}
	else if (parameter == TP_BS) {
		/* BSの取得 */
		*value = (uint16) (p_rx_inib->p_rx_cb->bs);
		ercd = E_OK;
	}
	else {
		/* パラメータエラー通知 */
		CANTP_SWITCH_DET_ERROR(CanTpServiceId_ReadParameter, CANTP_E_PARAM_ID);
		/* 戻り値は初期化時に設定済み(E_NOT_OK) */
	}

  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return(ercd);
}
#endif /* CANTP_READ_PARAMETER_API == STD_ON */


/*
 *  [SWS_CanTp_00214][SWS_CanTp_00078] CanTp_RxIndication
 */
/* [SWS_CanTp_00096] 同時にいくつかの通信をサポート */
/* [SWS_CanTp_00116] パディング有効・無効のどちらのモードでも、上位モジュールへ使用されたデータを渡す */
void
CanTp_RxIndication(PduIdType RxPduId, const PduInfoType* PduInfoPtr)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	CanTp_Frame_Normal 			*p_can_frame = NULL_PTR;			/* CANフレームフォーマット変換 */
	uint8						n_pci;								/* 受信NPDU */
	PduLengthType				len = CANTP_ZERO;					/* 受信フレームのデータ部のデータ長 */
	PduIdType					nsdu_id;							/* NSDUID */
	uint8						padding_err = CANTP_FALSE;			/* DLCエラー有無 */
	CanTp_ReturnType			chk_can_dlc = CANTP_E_NOT_OK;			/* CANのDLCチェック結果 */
	
	/* [SWS_CanTp_00235] */
	SchM_Enter_CanTp_Reentrant_0();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_RxIndication, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [NCanTp_00014] IDチェック */
	CANTP_CHECK_PARAM((RxPduId < GET_PDU_NUM()), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
	nsdu_id = GET_NSDUID_FROM_PDUID(RxPduId);
	CANTP_CHECK_PARAM((nsdu_id < GET_NSDU_NUM()), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
	/* [SWS_CanTp_00322][SWS_CanTp_00352] NULLチェック */
	CANTP_CHECK_PARAM((PduInfoPtr != NULL_PTR), CanTpServiceId_RxIndication, CANTP_E_PARAM_POINTER);
	CANTP_CHECK_PARAM((PduInfoPtr->SduDataPtr != NULL_PTR), CanTpServiceId_RxIndication, CANTP_E_PARAM_POINTER);
	/* CAN_DL0チェック */
	CANTP_CHECK_PARAM((PduInfoPtr->SduLength != (PduLengthType) CANTP_ZERO), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);

	p_nsdu_inib = GET_NSDU_INIB(nsdu_id);	/* NSDU初期化ブロック */
	
	/* [SWS_CanTp_00345][SWS_CanTp_00346][SWS_CanTp_00349][SWS_CanTp_00350] */
	/* CAN_DLチェック */
	if (PduInfoPtr->SduLength < (PduLengthType) CANTP_CAN_DL) {
		/* Paddingありの場合8未満はエラー */
		if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
			/* DETエラー */
			padding_err = CANTP_TRUE;
			CANTP_SWITCH_DET_ERROR(CanTpServiceId_RxIndication, CANTP_E_PADDING);
		}
	}
	else {
		chk_can_dlc = chk_dlc(PduInfoPtr->SduLength, p_nsdu_inib->CanTpTaType);
		if (chk_can_dlc == CANTP_E_NOT_OK) {
			CANTP_SWITCH_DET_ERROR(CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
			goto error_exit;
		}
	}
	
	/* アドレスフォーマットに応じてN_TA,N_AEの確認 */
	p_can_frame = (CanTp_Frame_Normal*)chk_address_info(p_nsdu_inib, PduInfoPtr->SduDataPtr, &len);
	len = (PduInfoPtr->SduLength) - len;
	
	if (p_can_frame != NULL_PTR) {
		n_pci = (p_can_frame->Common.n_pci) & CANTP_UINT8_MASK_F0;
		
		/* 受信N PDUに応じて処理分岐 */
		switch (n_pci) {
		case CANTP_NPCI_SF :	/* SF */
			/* Paddingエラー未発生 */
			if (padding_err == CANTP_FALSE) {
				/* 受信NSDUチェック */
				CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
				/* SF受信処理 */
				rcv_sf(nsdu_id, p_can_frame, PduInfoPtr->SduLength);
			}
			break;
		case CANTP_NPCI_FF :	/* FF */
			/* Paddingエラー未発生 */
			if (padding_err == CANTP_FALSE) {
				/* 受信NSDUチェック */
				CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
				/* [SWS_CanTp_00092] 機能アドレスチェック */
				if ((p_nsdu_inib->CanTpTaType == CANTP_FUNCTIONAL) ||
					(p_nsdu_inib->CanTpTaType == CANTP_CANFD_FUNCTIONAL)) {
					/* [SWS_CanTp_00093] 機能アドレスかつFF受信の場合 */
					CANTP_SWITCH_DET_ERROR(CanTpServiceId_RxIndication, CANTP_E_INVALID_TATYPE);
					goto error_exit;
				}
				/* FF受信処理 */
				rcv_ff(nsdu_id, p_can_frame, len);
			}
			break;
		case CANTP_NPCI_CF :	/* CF */
			/* 受信NSDUチェック */
			CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
			/* CF受信処理 */
			rcv_cf(nsdu_id, p_can_frame, len, padding_err);
			break;
		case CANTP_NPCI_FC :	/* FC */
			/* 送信NSDUチェック */
			CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_SEND), CanTpServiceId_RxIndication, CANTP_E_PARAM_ID);
			/* FC受信処理 */
			rcv_fc(nsdu_id, p_can_frame, len, padding_err);
			break;
		default :
			/* 無視 */
			break;
		}
	}

  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return;
}

/*
 *  [SWS_CanTp_00215][SWS_CanTp_00076] CanTp_TxConfirmation
 */
void
CanTp_TxConfirmation(PduIdType TxPduId)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduIdType					nsdu_id;							/* NSDUID */
	PduIdType					chk_id;								/* チェック用ID */
	
	/* [SWS_CanTp_00236] */
	SchM_Enter_CanTp_Reentrant_1();

	/* [SWS_CanTp_00031][SWS_CanTp_00293][SWS_CanTp_00199] 初期化確認 */
	CANTP_CHECK_PARAM((cantp_state == CANTP_INIT), CanTpServiceId_TxConfirmation, CANTP_E_UNINIT);

	/* パラメータチェック */
	/* [NCanTp_00015] IDチェック */
	CANTP_CHECK_PARAM((TxPduId < GET_PDU_NUM()), CanTpServiceId_TxConfirmation, CANTP_E_PARAM_ID);
	nsdu_id = GET_NSDUID_FROM_PDUID(TxPduId);
	CANTP_CHECK_PARAM((nsdu_id < GET_NSDU_NUM()), CanTpServiceId_TxConfirmation, CANTP_E_PARAM_ID);

	/* 情報取得 */
	ch = GET_CH_FROM_ID(nsdu_id);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(nsdu_id);
	
	switch (p_ch_tx_cb->tx_status) {
	case CANTP_STATUS_END_SF :	/* SF */
		/* 現在送信中のIDと一致しているかの確認 */
		if (p_ch_tx_cb->id == nsdu_id) {
			/* 送信NSDUチェック */
			CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_SEND), CanTpServiceId_TxConfirmation, CANTP_E_PARAM_ID);
			
			chk_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->CanTpId_Confirmation;
			if (TxPduId == chk_id) {
				PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
				
				/* [SWS_CanTp_00090][SWS_CanTp_00177][SWS_CanTp_00204] 送信完了通知 */
				PduR_CanTpTxConfirmation(PduR_id, E_OK);
				/* タイマ停止 */
				CANTP_CLR_TX_TIMER(p_ch_tx_cb);
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
			}
		}
		break;
	case CANTP_STATUS_END_FF :	/* FF */
		/* 現在送信中のIDと一致しているかの確認 */
		if (p_ch_tx_cb->id == nsdu_id) {
			/* 送信NSDUチェック */
			CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_SEND), CanTpServiceId_TxConfirmation, CANTP_E_PARAM_ID);
			
			chk_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->CanTpId_Confirmation;
			if (TxPduId == chk_id) {
				/* [SWS_CanTp_00315] N_Bsタイマ設定 */
				CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_BS, p_nsdu_inib->CanTpNb);
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_WAIT_FC;
			}
		}
		break;
	case CANTP_STATUS_END_CF :	/* CF */
		/* 現在送信中のIDと一致しているかの確認 */
		if (p_ch_tx_cb->id == nsdu_id) {
			/* 送信NSDUチェック */
			CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_SEND), CanTpServiceId_TxConfirmation, CANTP_E_PARAM_ID);
			
			chk_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->CanTpId_Confirmation;
			if (TxPduId == chk_id) {
				end_cf(p_ch_tx_cb, p_nsdu_inib);
			}
		}
		break;
	default :
		/* 上記以外はありえない */
		break;
	}
	
	
	switch (p_ch_rx_cb->rx_status) {
	case CANTP_STATUS_END_FC :	/* FC */
		/* 現在受信中のIDと一致しているかの確認 */
		if (p_ch_rx_cb->id == nsdu_id) {
			/* 受信NSDUチェック */
			CANTP_CHECK_PARAM((p_nsdu_inib->nsdu_direction == CANTP_RECEIVE), CanTpServiceId_TxConfirmation, CANTP_E_PARAM_ID);
			
			chk_id = ((const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->CanTpId_FcConfirmation;
			if (TxPduId == chk_id) {
				end_fc(p_ch_rx_cb, p_nsdu_inib);
			}
		}
		break;
	default :
		/* 上記以外はありえない */
		break;
	}


  error_exit:
	SchM_Exit_CanTp_Reentrant_1();
	return;
}

/*
 *  [SWS_CanTp_00213] CanTp_MainFunction
 */
/* [SWS_CanTp_00096] 同時にいくつかの通信をサポート */
void
CanTp_MainFunction(void)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	
	SchM_Enter_CanTp_Reentrant_0();
	
	/* [NCanTp_00016] 初期化されていない場合は何もせずにreturn */
	/* [SWS_CanTp_00238] CANTP_INIT状態でのみ，送信データの分割と受信データの結合ができる */
	if (cantp_state != CANTP_INIT) {
		goto error_exit;
	}
	
	for (ch = CANTP_ZERO; ch < GET_CH_NUM(); ch++) {
		/* 各情報取得 */
		p_ch_rx_cb = GET_CH_RX_CB(ch);
		p_ch_tx_cb = GET_CH_TX_CB(ch);
		
		/* 受信 */
		ch_rcv_main(p_ch_rx_cb);
		
		/* 送信 */
		ch_snd_main(p_ch_tx_cb);
	}
	
  error_exit:
	SchM_Exit_CanTp_Reentrant_0();
	return;
}


/*
 *  以下，内部関数
 */

/*
 *  内部変数初期化
 */
static void
init_internal(void)
{
	uint16						ch;									/* チャネル用ループカウンタ */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	uint16						nsdu_cnt;							/* NSDU用ループカウンタ */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */

	/* グローバル変数，内部変数を初期化 */
	for (ch = CANTP_ZERO; ch < GET_CH_NUM(); ch++) {
		/* 受信 */
		p_ch_rx_cb = GET_CH_RX_CB(ch);
		/* 管理ブロックのデータ初期化 */
		p_ch_rx_cb->id = CANTP_INVALID_ID;
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		p_ch_rx_cb->rx_time = CANTP_TIME_STOP;
		p_ch_rx_cb->rx_time_cnt = CANTP_TIMECNT_CLR;
		p_ch_rx_cb->sdu_len = (PduLengthType) CANTP_ZERO;
		p_ch_rx_cb->data_len = (PduLengthType) CANTP_ZERO;
		p_ch_rx_cb->cf_sn = (uint8) CANTP_ZERO;
		p_ch_rx_cb->fc_fs = CANTP_FS_WAIT;
		p_ch_rx_cb->fc_bs = (uint8) CANTP_ZERO;
		p_ch_rx_cb->fc_stmin = (uint8) CANTP_ZERO;
		p_ch_rx_cb->bs_cnt = (uint8) CANTP_ZERO;
		p_ch_rx_cb->wft_cnt = (uint8) CANTP_ZERO;

		/* 送信 */
		p_ch_tx_cb = GET_CH_TX_CB(ch);
		/* 管理ブロックのデータ初期化 */
		p_ch_tx_cb->id = CANTP_INVALID_ID;
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		p_ch_tx_cb->tx_time = CANTP_TIME_STOP;
		p_ch_tx_cb->tx_time_cnt = CANTP_TIMECNT_CLR;
		p_ch_tx_cb->sdu_len = (PduLengthType) CANTP_ZERO;
		p_ch_tx_cb->data_len = (PduLengthType) CANTP_ZERO;
		p_ch_tx_cb->cf_sn = (uint8) CANTP_ZERO;
		p_ch_tx_cb->fc_fs = CANTP_FS_WAIT;
		p_ch_tx_cb->fc_bs = (uint8) CANTP_ZERO;
		p_ch_tx_cb->fc_stmin = (uint8) CANTP_ZERO;
		p_ch_tx_cb->fc_cts = CANTP_FALSE;
		p_ch_tx_cb->bs_cnt = (uint8) CANTP_ZERO;
		p_ch_tx_cb->stmin_cnt = (uint16) CANTP_ZERO;
	}
	
	/* NSDU管理ブロック */
	for (nsdu_cnt = CANTP_ZERO; nsdu_cnt < GET_NSDU_NUM(); nsdu_cnt++) {
		p_nsdu_inib = GET_NSDU_INIB(nsdu_cnt);	/* NSDU初期化ブロック */
		p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
		if (p_nsdu_inib->nsdu_direction == CANTP_RECEIVE) {
			p_rx_inib->p_rx_cb->bs = p_rx_inib->CanTpBs;
			p_rx_inib->p_rx_cb->stmin = p_rx_inib->CanTpSTmin;
		}
	}
	
	return;
}


/* SF受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* p_can_frame: N_TA、N_AEを除いた受信データ */
/* can_dlc    : 受信CAN DLC */
LOCAL_INLINE void
rcv_sf(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType can_dlc)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	uint8						*data;								/* 受信フレームのデータ部の先頭 */
	PduLengthType				len = CANTP_ZERO;					/* 受信フレームのデータ部のデータ長 */
	PduLengthType				sf_dl;								/* SF_DL */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);	/* NSDU初期化ブロック */
	
	/* [SWS_CanTp_00288] チャネル使用中の場合は破棄 */
	/* 送受信状態確認 */
	retCanTp = chk_state_RcvSf(CanTpPduId);
	if (retCanTp == CANTP_E_OK) {
		/* CAN_DL <= 8 */
		if (can_dlc <= (PduLengthType) CANTP_CAN_DL) {
			/* SDUの全データ長 */
			sf_dl = (PduLengthType) ((p_can_frame->Sf_8Max.n_pci) & CANTP_UINT8_MASK_0F);
			/* SF_DLチェック */
			/* 0でないことは確認済みのためここでは確認しない */
			if (sf_dl <= p_nsdu_inib->sdu_max_sf) {
				/* N_PCIのデータ分データ長を減らす */
				len = len - CANTP_SF_8MAX_NPCI_LEN;
				/* データ設定 */
				data = p_can_frame->Sf_8Max.data;
				/* SF受信処理 */
				rcv_sf_sub(CanTpPduId, data, sf_dl);
			}
		}
		/* 8 < CAN_DL <=64 エラーチェック済み*/
		else {
			/* SDUの全データ長 */
			sf_dl = (PduLengthType) (p_can_frame->Sf_8Over.sf_dl);
			/* SF_DLチェック */
			/* 0でないことは確認済みのためここでは確認しない */
			if (sf_dl <= p_nsdu_inib->sdu_max_sf) {
				/* N_PCIのデータ分データ長を減らす */
				len = len - CANTP_SF_8OVER_NPCI_LEN;
				/* データ長の確認 */
				if (sf_dl <= len) {
					/* データ設定 */
					data = p_can_frame->Sf_8Over.data;
					/* SF受信処理 */
					rcv_sf_sub(CanTpPduId, data, sf_dl);
				}
			}
		}
	}
	
	return;
}

/* SF受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* data       : N_PCIを除いた受信データ */
/* sf_dl      : SF_DL */
LOCAL_INLINE void
rcv_sf_sub(PduIdType CanTpPduId, uint8* data, PduLengthType sf_dl)
{
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	BufReq_ReturnType			retBufReq = BUFREQ_E_NOT_OK;		/* PduR関数の戻り値 */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufSize = CANTP_ZERO;				/* PduRのAPI呼び出し時のデータ長の格納 */
	
	/* 各情報取得 */
	p_rx_inib = GET_RX_NSDU_INIB(CanTpPduId);
	PduR_id = p_rx_inib->PduRId_Indication;
	
	/* [SWS_CanTp_00079][SWS_CanTp_00329][SWS_CanTp_00080] PduR_CanTpStartOfReceptionの実施 */
	retBufReq = PduR_CanTpStartOfReception(PduR_id, (PduInfoType*)NULL_PTR, sf_dl, &bufSize);
	if (retBufReq == BUFREQ_OK) {
		/* 確保バッファサイズ < 受信データサイズ */
		if (bufSize < sf_dl) {
			/* [SWS_CanTp_00339] 受信失敗通知、受信中止 */
			PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
		}
		/* 確保バッファサイズ >= 受信データサイズ */
		else {
			/* 正常 */
			/* データ設定 */
			PduR_pduInfo.SduLength = sf_dl;
			PduR_pduInfo.SduDataPtr = data;
			
			/* PduR_CanTpCopyRxDataでデータコピー */
			retBufReq = PduR_CanTpCopyRxData(PduR_id, &PduR_pduInfo, &bufSize);
			if (retBufReq == BUFREQ_OK) {
				/* [SWS_CanTp_00084] 受信完了通知 */
				PduR_CanTpRxIndication(PduR_id, E_OK);
			}
			else {	/* (retBufReq == BUFREQ_E_NOT_OK) */
				/* [NCanTp_00006] 受信失敗通知 */
				PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
			}
		}
	}
	/* (retBufReq == BUFREQ_E_OVFL),(retBufReq == BUFREQ_E_NOT_OK) */
	/* [SWS_CanTp_00081][SWS_CanTp_00353]何もしない */
	
	return;
}

/* FF受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* p_can_frame: N_TA、N_AEを除いた受信データ */
/* len        : N_TA、N_AEを除いた受信データ長 */
LOCAL_INLINE void
rcv_ff(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType len)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	uint8						*data;								/* 受信フレームのデータ部の先頭 */
	PduLengthType				ff_dl;								/* FF_DL */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);	/* NSDU初期化ブロック */
	
	/* [SWS_CanTp_00288] チャネル使用中の場合は破棄 */
	/* 送受信状態確認 */
	retCanTp = chk_state_RcvFf(CanTpPduId);
	if (retCanTp == CANTP_E_OK) {
		/* SDUの全データ長 */
		ff_dl = ((PduLengthType) ((p_can_frame->Ff_4095Max.n_pci) & CANTP_UINT8_MASK_0F) << CANTP_SHIFT_8 )
				+ (PduLengthType) p_can_frame->Ff_4095Max.ff_dl_l;
		/* FF_DLの確認 */
		/* SF_DL < FF_DL <= 4095 */
		if (ff_dl > p_nsdu_inib->sdu_max_sf) {
			/* N_PCIのデータ分データ長を減らす */
			len = len - CANTP_FF_4095MAX_NPCI_LEN;
			/* データ設定 */
			data = p_can_frame->Ff_4095Max.data;
			/* FF受信処理 */
			rcv_ff_sub(CanTpPduId, data, len, ff_dl);
		}
		/* FF_DL > 4095の場合上記sdu_lenは0 */
		else {
			/* SDUの全データ長 */
			ff_dl = (((PduLengthType) (p_can_frame->Ff_4095Over.ff_dl_hh)) << CANTP_SHIFT_24 )
					+ (((PduLengthType) (p_can_frame->Ff_4095Over.ff_dl_hl)) << CANTP_SHIFT_16)
					+ (((PduLengthType) (p_can_frame->Ff_4095Over.ff_dl_lh)) << CANTP_SHIFT_8)
					+ (PduLengthType) (p_can_frame->Ff_4095Over.ff_dl_ll);
			/* FF_DL > 4095 */
			if (ff_dl > CANTP_THRESHOLD_FF) {
				/* N_PCIのデータ分データ長を減らす */
				len = len - CANTP_FF_4095OVER_NPCI_LEN;
				/* データ設定 */
				data = p_can_frame->Ff_4095Over.data;
				/* FF受信処理 */
				rcv_ff_sub(CanTpPduId, data, len, ff_dl);
			}
		}
	}
	
	return;
}

/* FF受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* data       : N_PCIを除いた受信データ */
/* len        : N_PCIを除いた受信データ長 */
/* ff_dl      : FF_DL */
LOCAL_INLINE  void
rcv_ff_sub(PduIdType CanTpPduId, uint8* data, PduLengthType len, PduLengthType ff_dl)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	BufReq_ReturnType			retBufReq = BUFREQ_E_NOT_OK;		/* PduR関数の戻り値 */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufSize = CANTP_ZERO;				/* PduRのAPI呼び出し時のデータ長の格納 */
	PduLengthType				next_block_size;					/* 次のブロックサイズ */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_rx_inib->PduRId_Indication;
	
	/* [SWS_CanTp_00277][SWS_CanTp_00064] FCの内容はPduR_CanTpStartOfReceptionの戻り値に依存する */
	
	/* [SWS_CanTp_00079][SWS_CanTp_00329][SWS_CanTp_00080] PduR_CanTpStartOfReceptionの実施 */
	retBufReq = PduR_CanTpStartOfReception(PduR_id, (PduInfoType*)NULL_PTR, ff_dl, &bufSize);
	if (retBufReq == BUFREQ_OK) {
		/* 確保バッファサイズ < 受信データサイズ */
		if (bufSize < len) {
			/* [SWS_CanTp_00339] 受信失敗通知 */
			PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
		}
		/* 確保バッファサイズ >= 受信データサイズ */
		else {
			/* 正常 */
			/* データ設定 */
			PduR_pduInfo.SduLength = len;
			PduR_pduInfo.SduDataPtr = data;
			
			/* PduR_CanTpCopyRxDataでデータコピー */
			retBufReq = PduR_CanTpCopyRxData(PduR_id, &PduR_pduInfo, &bufSize);
			if (retBufReq == BUFREQ_OK) {
				/* 受信データ情報更新 */
				p_ch_rx_cb->id = CanTpPduId;
				p_ch_rx_cb->sdu_len = ff_dl;
				p_ch_rx_cb->data_len = ff_dl - len;
				/* カウンタ初期化 */
				p_ch_rx_cb->cf_sn = CANTP_UINT8_1;
				p_ch_rx_cb->fc_stmin = p_rx_inib->p_rx_cb->stmin;
				p_ch_rx_cb->fc_bs = p_rx_inib->p_rx_cb->bs;
				p_ch_rx_cb->bs_cnt = p_ch_rx_cb->fc_bs;
				p_ch_rx_cb->wft_cnt = CANTP_ZERO;
				
				/* BS：0の場合 */
				if (p_ch_rx_cb->fc_bs == CANTP_ZERO) {
					/* 次のブロックサイズ：残りのデータ長 */
					next_block_size = p_ch_rx_cb->data_len;
				}
				else {
					/* 次のブロックサイズ：CFのデータサイズ×BS値 */
					next_block_size = (p_nsdu_inib->sdu_max_cf_data) * (p_ch_rx_cb->fc_bs);
					/* 残りのデータ長 < 次のブロックサイズの場合 */
					if (p_ch_rx_cb->data_len < next_block_size) {
						/* 次のブロックサイズ：残りのデータ長 */
						next_block_size = p_ch_rx_cb->data_len;
					}
				}
				
				/* 残りのバッファサイズ < 次のブロックサイズ */
				if (bufSize < next_block_size) {
					/* FC(WAIT)状態 */
					p_ch_rx_cb->fc_fs = CANTP_FS_WAIT;
					/* [SWS_CanTp_00166][SWS_CanTp_00082]N_Brタイマ設定 */
					CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_BR, p_nsdu_inib->CanTpNb);
					/* 受信状態更新 */
					p_ch_rx_cb->rx_status = CANTP_STATUS_SND_FC;
				}
				else {
					/* [SWS_CanTp_00224] FC(CTS)状態 */
					p_ch_rx_cb->fc_fs = CANTP_FS_CTS;
					/* 受信状態更新 */
					p_ch_rx_cb->rx_status = CANTP_STATUS_SND_FC;
				}
			}
			else {	/* (retBufReq == BUFREQ_E_NOT_OK) */
				/* [NCanTp_00007] 受信失敗通知 */
				PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
			}
		}
	}
	else if (retBufReq == BUFREQ_E_OVFL) {
		/* 受信データ情報更新 */
		p_ch_rx_cb->id = CanTpPduId;
		/* [SWS_CanTp_00318] FC(OVFLW)状態 */
		p_ch_rx_cb->fc_fs = CANTP_FS_OVFLW;
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_SND_FC;
	}
	else {	/* (retBufReq == BUFREQ_E_NOT_OK) */
		/* [SWS_CanTp_00081] 何もしない */
	}
	
	return;
}

/* CF受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* p_can_frame: N_TA、N_AEを除いた受信データ */
/* len        : N_TA、N_AEを除いた受信データ長 */
LOCAL_INLINE void
rcv_cf(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType len, uint8 padding_err)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	uint8						*data;								/* 受信フレームのデータ部の先頭 */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);	/* NSDU初期化ブロック */
	
	/* [SWS_CanTp_00288] チャネル使用中の場合は破棄 */
	/* 送受信状態確認 */
	retCanTp = chk_state_RcvCf(CanTpPduId);
	if (retCanTp == CANTP_E_OK) {
		/* 受信チャネル情報取得 */
		ch = GET_CH_FROM_ID(CanTpPduId);
		p_ch_rx_cb = GET_CH_RX_CB(ch);
		
		/* Paddingエラー未発生 */
		if (padding_err == CANTP_FALSE) {
			/* SNチェック */
			if (((p_can_frame->Cf.n_pci) & CANTP_UINT8_MASK_0F) == p_ch_rx_cb->cf_sn) {
				/* N_PCIのデータ分データ長を減らす */
				len = len - CANTP_CF_NPCI_LEN;
				/* データ設定 */
				data = p_can_frame->Cf.data;
				rcv_cf_sub(CanTpPduId, data, len);
				if (p_ch_rx_cb->cf_sn < CANTP_SN_MAX) {
					p_ch_rx_cb->cf_sn++;
				}
				else {
					p_ch_rx_cb->cf_sn = CANTP_ZERO;
				}
			}
			else
			{
				/* [SWS_CanTp_00314] SN異常 */
				/* DETエラー */
				PduR_id = ((const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Indication;
				PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_RxIndication, CANTP_E_COM);
				/* タイマ停止 */
				CANTP_CLR_RX_TIMER(p_ch_rx_cb);
				/* 受信状態更新 */
				p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
			}
		}
		/* Paddingエラー発生 */
		else {
			/* [SWS_CanTp_00346] 受信失敗通知 */
			PduR_id = ((const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Indication;
			PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
			/* タイマ停止 */
			CANTP_CLR_RX_TIMER(p_ch_rx_cb);
			/* 受信状態更新 */
			p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		}
	}
	
	return;
}

/* CF受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* data       : N_PCIを除いた受信データ */
/* len        : N_PCIを除いた受信データ長 */
LOCAL_INLINE  void
rcv_cf_sub(PduIdType CanTpPduId, uint8* data, PduLengthType len)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	BufReq_ReturnType			retBufReq = BUFREQ_E_NOT_OK;		/* PduR関数の戻り値 */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufSize = CANTP_ZERO;				/* PduRのAPI呼び出し時のデータ長の格納 */
	PduLengthType				next_block_size;					/* 次のブロックサイズ */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_rx_inib->PduRId_Indication;
	
	/* データ設定 */
	/* 残りデータ長 >= 受信データ長の場合は受信したデータ長分コピー */
	if(p_ch_rx_cb->data_len >= len) {
		PduR_pduInfo.SduLength = len;
	}
	/* 残りデータ長 < 受信データ長の場合は残りのデータ長分コピー */
	else {
		PduR_pduInfo.SduLength = p_ch_rx_cb->data_len;
	}
	PduR_pduInfo.SduDataPtr = data;
	
	/* [SWS_CanTp_00269] PduR_CanTpCopyRxDataでデータコピー */
	retBufReq = PduR_CanTpCopyRxData(PduR_id, &PduR_pduInfo, &bufSize);
	if (retBufReq == BUFREQ_OK) {
		if(p_ch_rx_cb->data_len > len) {
			p_ch_rx_cb->data_len -= len;
		}
		else {
			p_ch_rx_cb->data_len = CANTP_ZERO;
		}
		
		/* データ途中 */
		if (p_ch_rx_cb->data_len != CANTP_ZERO) {
			/* BS==0 */
			if (p_ch_rx_cb->fc_bs == CANTP_ZERO) {
				/* [SWS_CanTp_00312] N_Crタイマ設定 */
				CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_CR, p_nsdu_inib->CanTpNc);
				/* 受信状態：CF受信待ち継続 */
				/* p_ch_rx_cb->rx_status = CANTP_STATUS_WAIT_CF; */
			}
			/* BS!=0 */
			else {
				(p_ch_rx_cb->bs_cnt)--;
				/* ブロック途中 */
				if (p_ch_rx_cb->bs_cnt != CANTP_ZERO) {
					/* [SWS_CanTp_00312] N_Crタイマ設定 */
					CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_CR, p_nsdu_inib->CanTpNc);
					/* 受信状態：CF受信待ち継続 */
					/* p_ch_rx_cb->rx_status = CANTP_STATUS_WAIT_CF; */
				}
				/* ブロック最終 */
				else {
					/* 次のブロックサイズ：CFのデータサイズ×BS値 */
					next_block_size = (p_nsdu_inib->sdu_max_cf_data) * (p_ch_rx_cb->fc_bs);
					/* 残りのデータ長 < 次のブロックサイズの場合 */
					if (p_ch_rx_cb->data_len < next_block_size) {
						/* 次のブロックサイズ：残りのデータ長 */
						next_block_size = p_ch_rx_cb->data_len;
					}
					
					/* 残りのバッファサイズ < 次のブロックサイズ */
					if (bufSize < next_block_size) {
						/* FC(WAIT)状態 */
						p_ch_rx_cb->fc_fs = CANTP_FS_WAIT;
						p_ch_rx_cb->wft_cnt = CANTP_ZERO;
						/* [SWS_CanTp_00166][SWS_CanTp_00325] N_Brタイマ設定 */
						CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_BR, p_nsdu_inib->CanTpNb);
						/* 受信状態更新 */
						p_ch_rx_cb->rx_status = CANTP_STATUS_SND_FC;
					}
					else {
						/* [SWS_CanTp_00224][SWS_CanTp_00278] FC(CTS)送信 */
						p_ch_rx_cb->fc_fs = CANTP_FS_CTS;
						/* 受信状態更新 */
						p_ch_rx_cb->rx_status = CANTP_STATUS_SND_FC;
					}
					/* BSカウンタ初期化 */
					p_ch_rx_cb->bs_cnt = p_ch_rx_cb->fc_bs;
				}
			}
		}
		/* 最終ブロック最終 */
		else {
			/* [SWS_CanTp_00084] 受信完了通知 */
			PduR_CanTpRxIndication(PduR_id, E_OK);
			/* タイマ停止 */
			CANTP_CLR_RX_TIMER(p_ch_rx_cb);
			/* 受信状態更新 */
			p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		}
	}
	else {	/* (retBufReq == BUFREQ_E_NOT_OK) */
		/* [SWS_CanTp_00271] 受信失敗通知 */
		PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
		/* タイマ停止 */
		CANTP_CLR_RX_TIMER(p_ch_rx_cb);
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
	}
	
	return;
}

/* FC受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* p_can_frame: N_TA、N_AEを除いた受信データ */
/* len        : N_TA、N_AEを除いた受信データ長 */
/* padding_err: Paddingエラーの発生有無 */
LOCAL_INLINE void
rcv_fc(PduIdType CanTpPduId, CanTp_Frame_Normal* p_can_frame, PduLengthType len, uint8 padding_err)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	uint8						*data;								/* 受信フレームのデータ部の先頭 */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);	/* NSDU初期化ブロック */
	
	/* [SWS_CanTp_00288] チャネル使用中の場合は破棄 */
	/* 送受信状態確認 */
	retCanTp = chk_state_RcvFc(CanTpPduId);
	if (retCanTp == CANTP_E_OK) {
		/* 送信チャネル情報取得 */
		ch = GET_CH_FROM_ID(CanTpPduId);
		p_ch_tx_cb = GET_CH_TX_CB(ch);
		
		/* Paddingエラー未発生 */
		if (padding_err == CANTP_FALSE) {
			/* FC受信処理 */
			/* N_PCIのデータ分データ長を減らす */
			len = len - CANTP_FC_NPCI_LEN;
			/* データ設定 */
			data = &(p_can_frame->Fc.bs);
			p_ch_tx_cb->fc_fs = (p_can_frame->Fc.n_pci) & CANTP_UINT8_MASK_0F;
			rcv_fc_sub(CanTpPduId, data, len);
		}
		/* Paddingエラー発生 */
		else {
			/* [SWS_CanTp_00349] 送信失敗通知 */
			PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
			PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
			/* タイマ停止 */
			CANTP_CLR_TX_TIMER(p_ch_tx_cb);
			/* 受信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		}
	}
	
	return;
}

/* FC受信処理 */
/* 受信完了割り込みから呼ばれる */
/* CanTpPduId : CanTpId */
/* data       : N_PCIを除いた受信データ */
/* len        : N_PCIを除いた受信データ長 */
LOCAL_INLINE void
rcv_fc_sub(PduIdType CanTpPduId, const uint8 data[], PduLengthType len)
{
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	
	switch (p_ch_tx_cb->fc_fs) {
	case CANTP_FS_CTS :		/* CTS */
		/* 1回目の受信の場合 */
		if (p_ch_tx_cb->fc_cts == CANTP_FALSE) {
			/* パラメータ保持 */
			p_ch_tx_cb->fc_bs = data[0];			/* BS */
			p_ch_tx_cb->fc_stmin = get_stmin_cnt(data[1]);			/* STmin */
			/* STminとN_Csタイムアウト値の判定 */
			if (p_ch_tx_cb->fc_stmin < p_nsdu_inib->CanTpNc) 
			{
				p_ch_tx_cb->fc_cts = CANTP_TRUE;		/* CF(CTS)受信済み */
				/* カウンタ初期化 */
				p_ch_tx_cb->bs_cnt = p_ch_tx_cb->fc_bs;
				p_ch_tx_cb->stmin_cnt = CANTP_ZERO;
				
				/* [SWS_CanTp_00167] N_Csタイマ設定 */
				CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_CS, p_nsdu_inib->CanTpNc);
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_SND_CF;
			}
			else {
				/* [NCanTp_00039] STmin >= N_Csタイムアウト値の場合送信中止 */
				PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
				/* 送信失敗通知 */
				PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
				/* タイマ停止 */
				CANTP_CLR_TX_TIMER(p_ch_tx_cb);
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
			}
		}
		else {
			/* カウンタ初期化 */
			p_ch_tx_cb->bs_cnt = p_ch_tx_cb->fc_bs;
			p_ch_tx_cb->stmin_cnt = CANTP_ZERO;
			
			/* [SWS_CanTp_00167] N_Csタイマ設定 */
			CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_CS, p_nsdu_inib->CanTpNc);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_SND_CF;
		}
		break;
	case CANTP_FS_WAIT :	/* WAIT */
		/* [SWS_CanTp_00315] N_Bsタイマ再設定 */
		CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_BS, p_nsdu_inib->CanTpNb);
		/* 送信状態：FC受信待ち継続 */
		/* p_ch_tx_cb->tx_status = CANTP_STATUS_WAIT_FC; */
		break;
	/* case CANTP_FS_OVFLW :*/	/* OVFLW */
	default :
		PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
		/* [SWS_CanTp_00309][SWS_CanTp_00317] 送信失敗通知 */
		PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
		/* タイマ停止 */
		CANTP_CLR_TX_TIMER(p_ch_tx_cb);
		/* 送信状態更新 */
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		break;
	}
	
	return;
}

/* アドレス情報確認 */
/* p_nsdu_inib : NSDU初期化ブロック */
/* data        : アドレス情報を確認するデータポインタ */
/* ret_len     : 確認したデータ長を格納 */
/* 戻り値      : 次のデータポインタ */
LOCAL_INLINE uint8*
chk_address_info(const NSDU_INIB *p_nsdu_inib, uint8 data[], PduLengthType *ret_len)
{
	uint8 						*p_ret_dat = NULL_PTR;				/* データ先頭アドレス */
	PduLengthType				can_dlc = CANTP_ZERO;				/* CAN_DL */
	
	/* 1byte目がN_TA、N_AEかの判定 */
	/* アドレスフォーマットで決まる */
	switch(p_nsdu_inib->CanTpAddressingFormat) {
	case CANTP_STANDARD :		/* Normal addressing format */
	case CANTP_NORMALFIXED :	/* Normal fixed addressing format */
		p_ret_dat = &data[CANTP_STANDARD_IND_DATA];
		break;
	case CANTP_EXTENDED :		/* Extended addressing format */
		/* [SWS_CanTp_00281][SWS_CanTp_00094] 最初のバイトはN_TAである */
		/* [SWS_CanTp_00284][SWS_CanTp_00095] 受信側ではN_TAの確認を行う */
		if (data[CANTP_EXTENDED_IND_NTA] == p_nsdu_inib->CanTpNTa) {
			p_ret_dat = &data[CANTP_EXTENDED_IND_DATA];
			can_dlc++;
		}
		break;
	case CANTP_MIXED :			/* Mixed 11 bit addressing format */
	case CANTP_MIXED29BIT :		/* Mixed 29 bit addressing format */
		/* [SWS_CanTp_00281][SWS_CanTp_00094] 最初のバイトはN_AEである */
		/* [SWS_CanTp_00284][SWS_CanTp_00095] 受信側ではN_AEの確認を行う */
		if (data[CANTP_MIXED_IND_NAE] == p_nsdu_inib->CanTpNAe) {
			p_ret_dat = &data[CANTP_MIXED_IND_DATA];
			can_dlc++;
		}
		break;
	default :
		/* ありえない */
		break;
	}
	
	*ret_len = can_dlc;
	
	return(p_ret_dat);
}

/* SF受信時状態確認 */
/* CanTpPduId : CanTpId */
/* 戻り値： CANTP_E_OK（状態正常）    */
/*          CANTP_E_NOT_OK（状態異常）*/
/* [SWS_CanTp_00057][SWS_CanTp_00290] */
LOCAL_INLINE CanTp_ReturnType
chk_state_RcvSf(PduIdType CanTpPduId)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	uint16						ch;									/* チャネル */
	const CH_INIB				*p_ch_inib = NULL_PTR;				/* チャネルブロック */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_inib = GET_CH_INIB(ch);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	
	/* 受信状態確認 */
	switch (p_ch_rx_cb->rx_status) {
	case CANTP_STATUS_IDLE :	/* IDLE */
		if (p_ch_inib->CanTpChannelMode == CANTP_MODE_FULL_DUPLEX)
		{
			/* 全二重方式の場合は送信状態は確認しない */
			retCanTp = CANTP_E_OK;
		}
		else {
			/* 半二重方式の場合は送信状態も確認する */
			if (p_ch_tx_cb->tx_status == CANTP_STATUS_IDLE) {
				retCanTp = CANTP_E_OK;
			}
		}
		break;
	case CANTP_STATUS_SND_FC :	/* FC送信待ち */
	case CANTP_STATUS_END_FC :	/* FC送信完了ち */
	case CANTP_STATUS_WAIT_CF :	/* CF受信待ち */
		/* 半二重方式の場合は送信状態がIDLEでないと遷移しないため送信状態の確認する必要なし */
		/* 全二重方式の場合は送信状態は確認しない */
		
		/* [SWS_CanTp_00124] 同じチャネルで同じN_AIを受信中の場合、前の受信は中止し、新たな受信として処理する */
		/* [SWS_CanTp_00124] 同じチャネルで異なるN_AIを受信中の場合、今受信したものは破棄する */
		if (p_ch_rx_cb->id == CanTpPduId) {
			p_rx_inib = GET_RX_NSDU_INIB(CanTpPduId);
			PduR_id = p_rx_inib->PduRId_Indication;
			
			/* 処理中の受信失敗通知 */
			PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
			
			/* 新たに受信処理を実施するため状態初期化 */
			CANTP_CLR_RX_TIMER(p_ch_rx_cb);			/* タイマ停止 */
			p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;	/* IDLE状態 */
			
			retCanTp = CANTP_E_OK;
		}
		break;
	default:
		/* ありえない */
		break;
	}
	
	return(retCanTp);
}

/* FF受信時状態確認 */
/* CanTpPduId : CanTpId */
/* 戻り値： CANTP_E_OK（状態正常）    */
/*          CANTP_E_NOT_OK（状態異常）*/
/* [SWS_CanTp_00057][SWS_CanTp_00290] */
LOCAL_INLINE CanTp_ReturnType
chk_state_RcvFf(PduIdType CanTpPduId)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	
	/* FF受信の状態確認はSFと同じ */
	retCanTp = chk_state_RcvSf(CanTpPduId);
	
	return(retCanTp);
}

/* CF受信時状態確認 */
/* CanTpPduId : CanTpId */
/* 戻り値： CANTP_E_OK（状態正常）    */
/*          CANTP_E_NOT_OK（状態異常）*/
/* [SWS_CanTp_00057][SWS_CanTp_00290] */
LOCAL_INLINE CanTp_ReturnType
chk_state_RcvCf(PduIdType CanTpPduId)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	
	/* 受信状態確認 */
	if (p_ch_rx_cb->rx_status == CANTP_STATUS_WAIT_CF) {	/* CF受信待ち */
		/* 全二重方式の場合は送信状態は確認しない */
		/* 半二重方式の場合は送信状態がIDLEでないと遷移しないため送信状態の確認する必要なし */
		if (p_ch_rx_cb->id == CanTpPduId) {
			retCanTp = CANTP_E_OK;
		}
	}
	
	return(retCanTp);
}

/* FC受信時状態確認 */
/* CanTpPduId : CanTpId */
/* 戻り値： CANTP_E_OK（状態正常）    */
/*          CANTP_E_NOT_OK（状態異常）*/
/* [SWS_CanTp_00057][SWS_CanTp_00290] */
LOCAL_INLINE CanTp_ReturnType
chk_state_RcvFc(PduIdType CanTpPduId)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	
	/* 送信状態確認 */
	if (p_ch_tx_cb->tx_status == CANTP_STATUS_WAIT_FC) {	/* FC受信待ち */
		/* 全二重方式の場合は受信状態は確認しない */
		/* 半二重方式の場合は受信状態がIDLEでないと遷移しないため送信状態の確認する必要なし */
		if (p_ch_tx_cb->id == CanTpPduId) {
			retCanTp = CANTP_E_OK;
		}
	}
	
	return(retCanTp);
}

/* DLCチェック処理 */
/* len        : DLC */
/* taType     : TAtype */
/* 戻り値： CANTP_E_OK（正常）    */
/*          CANTP_E_NOT_OK（異常）*/
LOCAL_INLINE CanTp_ReturnType
chk_dlc(PduLengthType len, uint8 taType)
{
	uint8						chk_canfd_dlc = CANTP_FALSE;		/* CANFDのDLCチェック結果 */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	
	/* [SWS_CanTp_00345][SWS_CanTp_00346][SWS_CanTp_00349][SWS_CanTp_00350] */
	/* CAN_DLチェック */
	if (len <= (PduLengthType) CANTP_CAN_DL) {
		/* [SWS_CanTp_00344] CAN,CAN FDともに正常 */
		retCanTp = CANTP_E_OK;
	}
	else if (len <= (PduLengthType) CANTP_CANFD_DL) {
		/* CANの場合は異常 */
		/* CAN FDの場合は以下のチェックを実施 */
		if ((taType == CANTP_CANFD_PHYSICAL) || (taType == CANTP_CANFD_FUNCTIONAL)) {
			chk_canfd_dlc = CHK_CANFD_DL(len);
			if (chk_canfd_dlc == CANTP_TRUE) {
				/* 12,16,20,24,32,48,64の場合正常 */
				retCanTp = CANTP_E_OK;
			}
		}
	}
	else {
		/* 64を超える場合はエラー */
	}
	
	return(retCanTp);
}

/* SF送信処理 */
/* CanTpPduId : CanTpId */
/* SduLen     : SDUデータ長 */
LOCAL_INLINE void
snd_sf(PduIdType CanTpPduId, PduLengthType SduLen)
{
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const TX_NSDU_INIB			*p_tx_inib = NULL_PTR;				/* NSDU送信初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduIdType					CanIf_id;							/* CanIfのAPI呼び出し時に使用するID */
	PduInfoType					CanIf_pduInfo;						/* CanIfのAPI呼び出し時に使用するPduInfo */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	Std_ReturnType				retStd = E_NOT_OK;					/* CanIf_Transmitの戻り値 */
	uint8						sndData[CANTP_CANFD_DL];			/* 送信データ */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_tx_inib = (const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_tx_inib->PduRId_Confirmation;
	CanIf_id = p_tx_inib->CanIfId_Send;
	
	/* データ設定 */
	CanIf_pduInfo.SduDataPtr = sndData;
	
	/* SF生成 */
	/* [SWS_CanTp_00086] PduR_CanTpCopyTxDataで送信データをコピー */
	p_ch_tx_cb->data_len = SduLen;
	retCanTp = make_sf(CanTpPduId, &(p_ch_tx_cb->data_len), CanIf_pduInfo.SduDataPtr, &CanIf_pduInfo.SduLength);
	
	/* [SWS_CanTp_00089] 処理成功 */
	if (retCanTp == CANTP_E_OK) {
		/* CanIf_Transmitの実施 */
		retStd = CanIf_Transmit(CanIf_id, &CanIf_pduInfo);
		/* 正常 */
		if (retStd == E_OK) {
			/* N_Asタイマ設定 */
			CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_AS, p_nsdu_inib->CanTpNa);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_END_SF;
		}
		/* 異常 */
		else {	/* (retStd == E_NOT_OK) */
			/* [SWS_CanTp_00343][SWS_CanTp_00205] 送信失敗通知、送信中止 */
			PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
			/* タイマ停止 */
			CANTP_CLR_TX_TIMER(p_ch_tx_cb);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		}
		
	}
	/* ビジー/処理失敗 */
	else {	/* (retCanTp == CANTP_E_BUSY) || (retCanTp == CANTP_E_NOT_OK) */
		/* [NCanTp_00036][SWS_CanTp_00087] 送信失敗通知、送信中止 */
		PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);	/* [SWS_CanTp_00205] */
		/* タイマ停止 */
		CANTP_CLR_TX_TIMER(p_ch_tx_cb);
		/* 送信状態更新 */
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
	}
	
	return;
}

/* SF送信データ生成 */
/* CanTpPduId : CanTpId */
/* sf_dl      : SF_DL */
/* data       : 生成データ格納ポインタ */
/* ret_len    : 生成したデータ長を格納 */
/* 戻り値     : CANTP_E_OK（正常）    */
/*              CANTP_E_NOT_OK（異常）*/
LOCAL_INLINE CanTp_ReturnType
make_sf(PduIdType CanTpPduId, PduLengthType *sf_dl, uint8 data[], PduLengthType *ret_len)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufSize = CANTP_ZERO;				/* PduRのAPI呼び出し時のデータ長の格納 */
	CanTp_Frame_Normal 			*p_can_frame = NULL_PTR;			/* CANフレームフォーマット変換 */
	BufReq_ReturnType			retBufReq = BUFREQ_E_NOT_OK;		/* PduR関数の戻り値 */
	uint8						can_dlc = CANTP_ZERO;				/* CAN_DL */
	uint8						canfd_dlc = CANTP_ZERO;				/* CANFD_DL */
	
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);	/* NSDU初期化ブロック */
	
	/* アドレス情報設定 */
	p_can_frame = (CanTp_Frame_Normal*)set_address_info(p_nsdu_inib, data, &can_dlc);
	
	/* SF */
	if (p_can_frame != NULL_PTR) {
		/* N_PCI設定 */
		p_can_frame->Common.n_pci = CANTP_NPCI_SF;

		/* CAN_DL <= 8 */
		if ((CANTP_SF_8MAX_NPCI_LEN + *sf_dl + can_dlc) <= CANTP_THRESHOLD_SF) {
			/* SF_DL */
			(p_can_frame->Sf_8Max.n_pci) |= (uint8) *sf_dl;
			/* PduR_CanTpCopyTxDataでコピーするデータ設定 */
			PduR_pduInfo.SduLength = *sf_dl;						/* コピーデータ長 */
			PduR_pduInfo.SduDataPtr = p_can_frame->Sf_8Max.data;	/* コピー先 */
			/* CAN DLC更新 */
			can_dlc += (uint8) (CANTP_SF_8MAX_NPCI_LEN + PduR_pduInfo.SduLength);
		}
		/* CAN_DL > 8 */
		else {
			/* SF_DL */
			p_can_frame->Sf_8Over.sf_dl = (uint8) *sf_dl;
			/* PduR_CanTpCopyTxDataでコピーするデータ設定 */
			PduR_pduInfo.SduLength = *sf_dl;						/* コピーデータ長 */
			PduR_pduInfo.SduDataPtr = p_can_frame->Sf_8Over.data;	/* コピー先 */
			/* CAN DLC更新 */
			can_dlc += (uint8) (CANTP_SF_8OVER_NPCI_LEN + PduR_pduInfo.SduLength);
		}

		PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
		
		/* [SWS_CanTp_00086][SWS_CanTp_00272][SWS_CanTp_00298] PduR_CanTpCopyTxDataで送信データコピー */
		retBufReq = PduR_CanTpCopyTxData(PduR_id, &PduR_pduInfo, NULL_PTR, &bufSize);
		if (retBufReq == BUFREQ_OK) {
			/* CANFDの場合 */
			if ((p_nsdu_inib->CanTpTaType == CANTP_CANFD_PHYSICAL) ||
				(p_nsdu_inib->CanTpTaType == CANTP_CANFD_FUNCTIONAL)) {
				/* Padding有効の場合 */
				if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
					if (can_dlc <= CANTP_CAN_DL) {
						/* [SWS_CanTp_00348] 未使用バイトは8でPaddingする */
						canfd_dlc = CANTP_CAN_DL;
					}
					else {
						/* [SWS_CanTp_00351] サイズに応じてPaddingする */
						canfd_dlc = GET_CANFD_DL(can_dlc);
					}
				}
				/* Padding無効の場合 */
				else {
					/* [SWS_CanTp_00351] サイズに応じてPaddingする */
					canfd_dlc = GET_CANFD_DL(can_dlc);
				}
				while(can_dlc < canfd_dlc) {
					/* [SWS_CanTp_00059][SWS_CanTp_00348][SWS_CanTp_00351] 未使用バイトはCanTpPaddingByteで更新する */
					data[can_dlc] = CANTP_PADDING_BYTE;
					can_dlc++;
				}
			}
			/* CANの場合 */
			else {
				/* Padding有効の場合 */
				if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
					while(can_dlc < CANTP_CAN_DL) {
						/* [SWS_CanTp_00059][SWS_CanTp_00348] 未使用バイトはCanTpPaddingByteで更新する */
						data[can_dlc] = CANTP_PADDING_BYTE;
						can_dlc++;
					}
				}
			}
			*ret_len = (PduLengthType)can_dlc;
			*sf_dl -= PduR_pduInfo.SduLength;
			retCanTp = CANTP_E_OK;
		}
		else if (retBufReq == BUFREQ_E_BUSY) {
			retCanTp = CANTP_E_BUSY;
		}
		else {	/* retBufReq == BUFREQ_E_NOT_OK; */
			/* 何も行わない */
			/* retCanTp == CANTP_E_NOT_OK; */
		}
	}
	return(retCanTp);
}

/* FF送信処理 */
/* CanTpPduId : CanTpId */
/* SduLen     : SDUデータ長 */
LOCAL_INLINE void
snd_ff(PduIdType CanTpPduId, PduLengthType SduLen)
{
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const TX_NSDU_INIB			*p_tx_inib = NULL_PTR;				/* NSDU送信初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduIdType					CanIf_id;							/* CanIfのAPI呼び出し時に使用するID */
	PduInfoType					CanIf_pduInfo;						/* CanIfのAPI呼び出し時に使用するPduInfo */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	Std_ReturnType				retStd = E_NOT_OK;					/* CanIf_Transmitの戻り値 */
	uint8						sndData[CANTP_CANFD_DL];			/* 送信データ */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_tx_inib = (const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_tx_inib->PduRId_Confirmation;
	CanIf_id = p_tx_inib->CanIfId_Send;
	
	/* データ設定 */
	CanIf_pduInfo.SduDataPtr = sndData;
	
	/* FF生成 */
	/* [SWS_CanTp_00086]PduR_CanTpCopyTxDataで送信データをコピー */
	p_ch_tx_cb->data_len = SduLen;
	retCanTp = make_ff(CanTpPduId, &(p_ch_tx_cb->data_len), CanIf_pduInfo.SduDataPtr, &CanIf_pduInfo.SduLength);
	
	/* [SWS_CanTp_00089] 処理成功 */
	if (retCanTp == CANTP_E_OK) {
		/* CanIf_Transmitの実施 */
		retStd = CanIf_Transmit(CanIf_id, &CanIf_pduInfo);
		/* 正常 */
		if (retStd == E_OK) {
			p_ch_tx_cb->cf_sn = CANTP_UINT8_1;
			/* N_Asタイマ設定 */
			CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_AS, p_nsdu_inib->CanTpNa);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_END_FF;
		}
		/* 異常 */
		else {	/* (retStd == E_NOT_OK) */
			/* [SWS_CanTp_00343] 送信中止 */
			/* 送信失敗通知 */
			PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);	/* [SWS_CanTp_00205] */
			/* タイマ停止 */
			CANTP_CLR_TX_TIMER(p_ch_tx_cb);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		}
		
	}
	/* ビジー/処理失敗 */
	else {	/* (retCanTp == CANTP_E_BUSY) || (retCanTp == CANTP_E_NOT_OK) */
		/* [NCanTp_00037][SWS_CanTp_00087] 送信失敗通知、送信中止 */
		PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);	/* [SWS_CanTp_00205] */
		/* タイマ停止 */
		CANTP_CLR_TX_TIMER(p_ch_tx_cb);
		/* 送信状態更新 */
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
	}
	
	return;
}

/* FF送信データ生成 */
/* CanTpPduId : CanTpId */
/* ff_dl      : FF_DL */
/* data       : 生成データ格納ポインタ */
/* ret_len    : 生成したデータ長を格納 */
/* 戻り値     : CANTP_E_OK（正常）    */
/*              CANTP_E_NOT_OK（異常）*/
LOCAL_INLINE CanTp_ReturnType
make_ff(PduIdType CanTpPduId, PduLengthType *ff_dl, uint8 data[], PduLengthType *ret_len)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufSize = CANTP_ZERO;				/* PduRのAPI呼び出し時のデータ長の格納 */
	CanTp_Frame_Normal 			*p_can_frame = NULL_PTR;			/* CANフレームフォーマット変換 */
	BufReq_ReturnType			retBufReq = BUFREQ_E_NOT_OK;		/* PduR関数の戻り値 */
	uint8						can_dlc = CANTP_ZERO;				/* CAN_DL */
	
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);	/* NSDU初期化ブロック */
	
	/* アドレス情報設定 */
	p_can_frame = (CanTp_Frame_Normal*)set_address_info(p_nsdu_inib, data, &can_dlc);
	
	/* FF */
	if (p_can_frame != NULL_PTR) {
		p_can_frame->Common.n_pci = CANTP_NPCI_FF;

		/* FF_DL <= 4095 */
		if (*ff_dl <= CANTP_THRESHOLD_FF) {
			/* FF_DL */
			p_can_frame->Ff_4095Max.n_pci |= (uint8) ((*ff_dl >> CANTP_SHIFT_8) & (PduLengthType)CANTP_UINT8_MASK_0F);
			p_can_frame->Ff_4095Max.ff_dl_l = (uint8) (*ff_dl & (PduLengthType)CANTP_UINT8_MASK_FF);
			/* PduR_CanTpCopyTxDataでコピーするデータ設定 */
			PduR_pduInfo.SduLength = p_nsdu_inib->sdu_max_ff_data;	/* コピーデータ長 */
			PduR_pduInfo.SduDataPtr = p_can_frame->Ff_4095Max.data;	/* コピー先 */
			/* CAN DLC更新 */
			can_dlc += (uint8) (CANTP_FF_4095MAX_NPCI_LEN + PduR_pduInfo.SduLength);
		}
		/* FF_DL > 4095 */
		else {
			p_can_frame->Ff_4095Over.reserve = CANTP_ZERO;
			/* FF_DL */
			p_can_frame->Ff_4095Over.ff_dl_hh = (uint8) ((*ff_dl >> CANTP_SHIFT_24) & (PduLengthType) CANTP_UINT8_MASK_FF);
			p_can_frame->Ff_4095Over.ff_dl_hl = (uint8) ((*ff_dl >> CANTP_SHIFT_16) & (PduLengthType) CANTP_UINT8_MASK_FF);
			p_can_frame->Ff_4095Over.ff_dl_lh = (uint8) ((*ff_dl >> CANTP_SHIFT_8) & (PduLengthType) CANTP_UINT8_MASK_FF);
			p_can_frame->Ff_4095Over.ff_dl_ll = (uint8) (*ff_dl & (PduLengthType) CANTP_UINT8_MASK_FF);
			/* PduR_CanTpCopyTxDataでコピーするデータ設定 */
			PduR_pduInfo.SduLength = (PduLengthType)((p_nsdu_inib->sdu_max_ff_data) - CANTP_UINT8_4);	/* コピーデータ長 */
			PduR_pduInfo.SduDataPtr = p_can_frame->Ff_4095Over.data;	/* コピー先 */
			/* CAN DLC更新 */
			can_dlc += (uint8) (CANTP_FF_4095OVER_NPCI_LEN + PduR_pduInfo.SduLength);
		}

		PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
		
		/* [SWS_CanTp_00086][SWS_CanTp_00272][SWS_CanTp_00298][SWS_CanTp_00299] PduR_CanTpCopyTxDataで送信データコピー */
		retBufReq = PduR_CanTpCopyTxData(PduR_id, &PduR_pduInfo, NULL_PTR, &bufSize);
		if (retBufReq == BUFREQ_OK) {
			*ret_len = (PduLengthType) can_dlc;
			*ff_dl -= PduR_pduInfo.SduLength;
			retCanTp = CANTP_E_OK;
		}
		else if (retBufReq == BUFREQ_E_BUSY) {
			retCanTp = CANTP_E_BUSY;
		}
		else {	/* retBufReq == BUFREQ_E_NOT_OK; */
			/* 何も行わない */
			/* retCanTp == CANTP_E_NOT_OK; */
		}
	}
	return(retCanTp);
}

/* CF送信処理 */
/* CanTpPduId : CanTpId */
/* SduLen     : SDUデータ長 */
/* [SWS_CanTp_00282] */
LOCAL_INLINE void
snd_cf(PduIdType CanTpPduId, PduLengthType SduLen)
{
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const TX_NSDU_INIB			*p_tx_inib = NULL_PTR;				/* NSDU送信初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduIdType					CanIf_id;							/* CanIfのAPI呼び出し時に使用するID */
	PduInfoType					CanIf_pduInfo;						/* CanIfのAPI呼び出し時に使用するPduInfo */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	Std_ReturnType				retStd = E_NOT_OK;					/* CanIf_Transmitの戻り値 */
	CanTp_ReturnType			retTimeout = CANTP_E_NOT_OK;		/* タイムアウト関数の戻り値 */
	uint8						sndData[CANTP_CANFD_DL];			/* 送信データ */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_tx_inib = (const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_tx_inib->PduRId_Confirmation;
	CanIf_id = p_tx_inib->CanIfId_Send;
	
	/* データ設定 */
	CanIf_pduInfo.SduDataPtr = sndData;
	
	/* CF生成 */
	/* [SWS_CanTp_00086] PduR_CanTpCopyTxDataで送信データをコピー */
	p_ch_tx_cb->data_len = SduLen;
	retCanTp = make_cf(CanTpPduId, &(p_ch_tx_cb->data_len), CanIf_pduInfo.SduDataPtr, &CanIf_pduInfo.SduLength);
	
	/* [SWS_CanTp_00089] 処理成功 */
	if (retCanTp == CANTP_E_OK) {
		/* CanIf_Transmitの実施 */
		retStd = CanIf_Transmit(CanIf_id, &CanIf_pduInfo);
		/* 正常 */
		if (retStd == E_OK) {
			/* N_Asタイマ設定 */
			CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_AS, p_nsdu_inib->CanTpNa);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_END_CF;
		}
		/* 異常 */
		else {	/* (retStd == E_NOT_OK) */
			/* [SWS_CanTp_00343] 送信中止 */
			/* 送信失敗通知 */
			PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);	/* [SWS_CanTp_00205] */
			/* タイマ停止 */
			CANTP_CLR_TX_TIMER(p_ch_tx_cb);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		}
		
	}
	/* ビジー */
	else if (retCanTp == CANTP_E_BUSY) {
		/* N_Csタイムアウト判定 */
		retTimeout = chk_timeout(p_ch_tx_cb->tx_time, &(p_ch_tx_cb->tx_time_cnt));	/* [SWS_CanTp_00164] */
		/* [SWS_CanTp_00167][SWS_CanTpa_00001][SWS_CanTpa_00002][SWS_CanTp_00280] N_Csタイムアウト発生 */
		if (retTimeout == CANTP_E_NOT_OK) {
			/* 送信失敗通知 */
			PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);	/* [SWS_CanTp_00205] */
			CANTP_SWITCH_DET_ERROR(CanTpServiceId_MainFunction, CANTP_E_TX_COM);	/* [SWS_CanTp_00229] */
			/* タイマ停止 */
			CANTP_CLR_TX_TIMER(p_ch_tx_cb);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
		}
		/* [SWS_CanTp_00184] リトライするため何もしない */
	}
	/* 処理失敗 */
	else {	/* (retCanTp == CANTP_E_NOT_OK) */
		/* [SWS_CanTp_00087] 送信失敗通知、送信中止 */
		PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);	/* [SWS_CanTp_00205] */
		/* タイマ停止 */
		CANTP_CLR_TX_TIMER(p_ch_tx_cb);
		/* 送信状態更新 */
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
	}
	
	return;
}

/* CF送信データ生成 */
/* CanTpPduId : CanTpId */
/* data_len   : データ長 */
/* data       : 生成データ格納ポインタ */
/* ret_len    : 生成したデータ長を格納 */
/* 戻り値     : CANTP_E_OK（正常）    */
/*              CANTP_E_NOT_OK（異常）*/
LOCAL_INLINE CanTp_ReturnType
make_cf(PduIdType CanTpPduId, PduLengthType *data_len, uint8 data[], PduLengthType *ret_len)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	uint16						ch;									/* チャネル */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufSize = CANTP_ZERO;				/* PduRのAPI呼び出し時のデータ長の格納 */
	CanTp_Frame_Normal 			*p_can_frame = NULL_PTR;			/* CANフレームフォーマット変換 */
	BufReq_ReturnType			retBufReq = BUFREQ_E_NOT_OK;		/* PduR関数の戻り値 */
	uint8						can_dlc = CANTP_ZERO;				/* CAN_DL */
	uint8						canfd_dlc = CANTP_ZERO;				/* CANFD_DL */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	
	/* アドレス情報設定 */
	p_can_frame = (CanTp_Frame_Normal*) set_address_info(p_nsdu_inib, data, &can_dlc);
	
	/* CF */
	if (p_can_frame != NULL_PTR) {
		p_can_frame->Common.n_pci = CANTP_NPCI_CF;

		/* SN */
		(p_can_frame->Cf.n_pci) |= p_ch_tx_cb->cf_sn;
		
		/* PduR_CanTpCopyTxDataでコピーするデータ設定 */
		/* 1フレームで送信できるCFデータ長より大きい */
		if (*data_len > p_nsdu_inib->sdu_max_cf_data) {
			PduR_pduInfo.SduLength = p_nsdu_inib->sdu_max_cf_data;	/* コピーデータ長 */
		}
		/* 1フレームで送信できるCFデータ長以下 */
		else {
			PduR_pduInfo.SduLength = *data_len;					/* コピーデータ長 */
		}
		PduR_pduInfo.SduDataPtr = p_can_frame->Cf.data;			/* コピー先 */
		/* CAN DLC更新 */
		can_dlc += (uint8) (CANTP_CF_NPCI_LEN + PduR_pduInfo.SduLength);
		
		PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
		
		/* [SWS_CanTp_00086][SWS_CanTp_00272][SWS_CanTp_00298][SWS_CanTp_00299] PduR_CanTpCopyTxDataで送信データコピー */
		retBufReq = PduR_CanTpCopyTxData(PduR_id, &PduR_pduInfo, NULL_PTR, &bufSize);
		if (retBufReq == BUFREQ_OK) {
			/* CANFDの場合 */
			if ((p_nsdu_inib->CanTpTaType == CANTP_CANFD_PHYSICAL) ||
				(p_nsdu_inib->CanTpTaType == CANTP_CANFD_FUNCTIONAL)) {
				/* Padding有効の場合 */
				if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
					if (can_dlc <= CANTP_CAN_DL) {
						/* [SWS_CanTp_00348] 未使用バイトは8でPaddingする */
						canfd_dlc = CANTP_CAN_DL;
					}
					else {
						/* [SWS_CanTp_00351] サイズに応じてPaddingする */
						canfd_dlc = GET_CANFD_DL(can_dlc);
					}
				}
				/* Padding無効の場合 */
				else {
					/* [SWS_CanTp_00351] サイズに応じてPaddingする */
					canfd_dlc = GET_CANFD_DL(can_dlc);
				}
				while(can_dlc < canfd_dlc) {
					/* [SWS_CanTp_00059][SWS_CanTp_00348][SWS_CanTp_00351] 未使用バイトはCanTpPaddingByteで更新する */
					data[can_dlc] = CANTP_PADDING_BYTE;
					can_dlc++;
				}
			}
			/* CANの場合 */
			else {
				/* Padding有効の場合 */
				if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
					while(can_dlc < CANTP_CAN_DL) {
						/* [SWS_CanTp_00059][SWS_CanTp_00348] 未使用バイトはCanTpPaddingByteで更新する */
						data[can_dlc] = CANTP_PADDING_BYTE;
						can_dlc++;
					}
				}
			}
			
			/* SNの更新 */
			if (p_ch_tx_cb->cf_sn < CANTP_SN_MAX) {
				p_ch_tx_cb->cf_sn++;
			}
			else {
				p_ch_tx_cb->cf_sn = CANTP_ZERO;
			}
			
			*ret_len = (PduLengthType)can_dlc;
			*data_len -= PduR_pduInfo.SduLength;
			retCanTp = CANTP_E_OK;
		}
		else if (retBufReq == BUFREQ_E_BUSY) {
			retCanTp = CANTP_E_BUSY;
		}
		else {	/* retBufReq == BUFREQ_E_NOT_OK; */
			/* 何も行わない */
			/* retCanTp == CANTP_E_NOT_OK; */
		}
	}
	return(retCanTp);
}

/* FC送信処理 */
/* CanTpPduId : CanTpId */
/* fs_type    : FS Type */
/* [SWS_CanTp_00067] */
LOCAL_INLINE void
snd_fc(PduIdType CanTpPduId, uint8 fs_type)
{
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduIdType					CanIf_id;							/* CanIfのAPI呼び出し時に使用するID */
	PduInfoType					CanIf_pduInfo;						/* CanIfのAPI呼び出し時に使用するPduInfo */
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* CanTp内部関数の戻り値 */
	Std_ReturnType				retStd = E_NOT_OK;					/* CanIf_Transmitの戻り値 */
	uint8						sndData[CANTP_CANFD_DL];			/* 送信データ */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_rx_inib->PduRId_Indication;
	CanIf_id = p_rx_inib->CanIfId_FcSend;
	
	/* データ設定 */
	CanIf_pduInfo.SduDataPtr = sndData;
	
	/* FC生成 */
	retCanTp = make_fc(CanTpPduId, fs_type, CanIf_pduInfo.SduDataPtr, &CanIf_pduInfo.SduLength);
	
	/* 処理成功 */
	if (retCanTp == CANTP_E_OK) {
		/* CanIf_Transmitの実施 */
		retStd = CanIf_Transmit(CanIf_id, &CanIf_pduInfo);
		/* 正常 */
		if (retStd == E_OK) {
			/* N_Arタイマ設定 */
			CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_AR, p_nsdu_inib->CanTpNa);
			/* 受信状態更新 */
			p_ch_rx_cb->rx_status = CANTP_STATUS_END_FC;
		}
		/* 異常 */
		else {	/* (retStd == E_NOT_OK) */
			/* [SWS_CanTp_00342] 受信失敗通知、受信中止 */
			PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
			/* タイマ停止 */
			CANTP_CLR_RX_TIMER(p_ch_rx_cb);
			/* 受信状態更新 */
			p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		}
		
	}
	/* 処理失敗 */
	else {	/* (retCanTp == CANTP_E_NOT_OK) */
		/* 受信失敗通知 */
		PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
		/* タイマ停止 */
		CANTP_CLR_RX_TIMER(p_ch_rx_cb);
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
	}
	
	return;
}

/* FC送信データ生成 */
/* CanTpPduId : CanTpId */
/* fs_type    : FS Type */
/* data       : 生成データ格納ポインタ */
/* ret_len    : 生成したデータ長を格納 */
/* 戻り値     : CANTP_E_OK（正常）    */
/*              CANTP_E_NOT_OK（異常）*/
LOCAL_INLINE CanTp_ReturnType
make_fc(PduIdType CanTpPduId, uint8 fs_type, uint8 data[], PduLengthType *ret_len)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	uint16						ch;									/* チャネル */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	CanTp_Frame_Normal 			*p_can_frame = NULL_PTR;			/* CANフレームフォーマット変換 */
	uint8						can_dlc = CANTP_ZERO;				/* CAN_DL */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_nsdu_inib = GET_NSDU_INIB(CanTpPduId);
	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	
	/* アドレス情報設定 */
	p_can_frame = (CanTp_Frame_Normal*)set_address_info(p_nsdu_inib, data, &can_dlc);
	
	/* FC */
	if (p_can_frame != NULL_PTR) {
		p_can_frame->Common.n_pci = CANTP_NPCI_FC;	/* FC設定 */
		can_dlc++;
		
		(p_can_frame->Fc.n_pci) |= fs_type;		/* FS設定 */
		p_ch_rx_cb->fc_fs = fs_type;			/* FC送信情報の保持 */
		
		/* CTSの場合 */
		if (fs_type == CANTP_FS_CTS) {
			p_can_frame->Fc.bs = p_ch_rx_cb->fc_bs;
			can_dlc++;
			p_can_frame->Fc.stmin = p_ch_rx_cb->fc_stmin;
			can_dlc++;
		}
		/* CTS以外の場合 */
		else {
			p_can_frame->Fc.bs = CANTP_ZERO;
			can_dlc++;
			p_can_frame->Fc.stmin = CANTP_ZERO;
			can_dlc++;
		}
		
		/* CANFDの場合 */
		if ((p_nsdu_inib->CanTpTaType == CANTP_CANFD_PHYSICAL) ||
			(p_nsdu_inib->CanTpTaType == CANTP_CANFD_FUNCTIONAL)) {
			/* Padding有効の場合 */
			if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
				while(can_dlc < CANTP_CAN_DL) {
					/* [SWS_CanTp_00059][SWS_CanTp_00351] 未使用バイトはCanTpPaddingByteで更新する */
					data[can_dlc] = CANTP_PADDING_BYTE;
					can_dlc++;
				}
			}
		}
		/* CANの場合 */
		else {
			/* Padding有効の場合 */
			if (p_nsdu_inib->CanTpPaddingActivation == CANTP_ON) {
				while(can_dlc < CANTP_CAN_DL) {
					/* [SWS_CanTp_00059][SWS_CanTp_00347] 未使用バイトはCanTpPaddingByteで更新する */
					data[can_dlc] = CANTP_PADDING_BYTE;
					can_dlc++;
				}
			}
		}
		*ret_len = (PduLengthType)can_dlc;
		retCanTp = CANTP_E_OK;
	}
	return(retCanTp);
}

/* アドレス情報設定 */
/* p_nsdu_inib : CanTpId */
/* data        : アドレス情報を設定するデータポインタ */
/* ret_len     : 生成したデータ長を格納 */
/* 戻り値      : 次のデータポインタ */
LOCAL_INLINE uint8*
set_address_info(const NSDU_INIB *p_nsdu_inib, uint8 data[], uint8 *ret_len)
{
	uint8 						*p_ret_dat = NULL_PTR;				/* データ先頭アドレス */
	uint8						can_dlc = CANTP_ZERO;				/* CAN_DL */
	
	/* 1byte目にN_TA、N_AEが必要かの判定 */
	/* アドレスフォーマットで決まる */
	switch(p_nsdu_inib->CanTpAddressingFormat) {
	case CANTP_STANDARD :		/* Normal addressing format */
	case CANTP_NORMALFIXED :	/* Normal fixed addressing format */
		p_ret_dat = &data[CANTP_STANDARD_IND_DATA];				/* すべてデータ */
		break;
	case CANTP_EXTENDED :		/* Extended addressing format */
		/* [SWS_CanTp_00281][SWS_CanTp_00094] 最初のバイトはN_TAである */
		data[CANTP_EXTENDED_IND_NTA] = p_nsdu_inib->CanTpNTa;	/* 1byte目：N_TA */
		p_ret_dat = &data[CANTP_EXTENDED_IND_DATA];				/* 以降データ */
		can_dlc++;
		break;
	case CANTP_MIXED :			/* Mixed 11 bit addressing format */
	case CANTP_MIXED29BIT :		/* Mixed 29 bit addressing format */
		/* [SWS_CanTp_00281][SWS_CanTp_00094] 最初のバイトはN_AEである */
		data[CANTP_MIXED_IND_NAE] = p_nsdu_inib->CanTpNAe;		/* 1byte目：N_AE */
		p_ret_dat = &data[CANTP_MIXED_IND_DATA];				/* 以降データ */
		can_dlc++;
		break;
	default :
		/* ありえない */
		break;
	}
	
	*ret_len = can_dlc;
	
	return(p_ret_dat);
}

/* 送信要求時状態確認 */
/* CanTpPduId : CanTpId */
/* 戻り値     : CANTP_E_OK（状態正常）    */
/*              CANTP_E_NOT_OK（状態異常）*/
LOCAL_INLINE CanTp_ReturnType
chk_state_Snd(PduIdType CanTpPduId)
{
	CanTp_ReturnType			retCanTp = CANTP_E_NOT_OK;			/* 戻り値 */
	uint16						ch;									/* チャネル */
	const CH_INIB				*p_ch_inib = NULL_PTR;				/* チャネルブロック */
	CH_RX_CB					*p_ch_rx_cb = NULL_PTR;				/* チャネル受信管理ブロック */
	CH_TX_CB					*p_ch_tx_cb = NULL_PTR;				/* チャネル送信管理ブロック */
	
	/* 各情報取得 */
	ch = GET_CH_FROM_ID(CanTpPduId);
	p_ch_inib = GET_CH_INIB(ch);
	p_ch_rx_cb = GET_CH_RX_CB(ch);
	p_ch_tx_cb = GET_CH_TX_CB(ch);
	
	/* [SWS_CanTp_00123] 送信状態確認 */
	if (p_ch_tx_cb->tx_status == CANTP_STATUS_IDLE) {	/* IDLE */
		if (p_ch_inib->CanTpChannelMode == CANTP_MODE_FULL_DUPLEX)
		{
			/* 全二重方式の場合は受信状態は確認しない */
			retCanTp = CANTP_E_OK;
		}
		else {
			/* 半二重方式の場合は受信状態も確認する */
			if (p_ch_rx_cb->rx_status == CANTP_STATUS_IDLE) {
				retCanTp = CANTP_E_OK;
			}
		}
	}
	
	return(retCanTp);
}

/* CF送信完了処理 */
/* p_ch_rx_cb  : チャネル受信管理ブロック */
/* p_nsdu_inib : NSDU初期化ブロック */
LOCAL_INLINE void
end_cf(CH_TX_CB *p_ch_tx_cb, const NSDU_INIB *p_nsdu_inib)
{
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	
	/* データ途中 */
	if (p_ch_tx_cb->data_len != CANTP_ZERO) {
		/* BS==0の場合 */
		if (p_ch_tx_cb->fc_bs == CANTP_ZERO) {
			p_ch_tx_cb->stmin_cnt = (uint16)((p_ch_tx_cb->fc_stmin) + CANTP_UINT8_1);		/* STmin初期化 */
			/* [SWS_CanTp_00167] N_Csタイマ設定 */
			/* N_CsタイマはSTminカウント中も動作しているためSTmin分引いておく */
			/* CanTpNc > STminであることはFC受信時に確認済み */
			CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_CS, (p_nsdu_inib->CanTpNc - p_ch_tx_cb->fc_stmin));
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_SND_CF;
		}
		/* BS!=0の場合 */
		else {
			/* ブロック途中 */
			(p_ch_tx_cb->bs_cnt)--;
			if (p_ch_tx_cb->bs_cnt != CANTP_ZERO) {
				p_ch_tx_cb->stmin_cnt = (uint16)((p_ch_tx_cb->fc_stmin) + CANTP_UINT8_1);		/* STmin初期化 */
				/* [SWS_CanTp_00167] N_Csタイマ設定 */
				/* N_CsタイマはSTminカウント中も動作しているためSTmin分引いておく */
				/* CanTpNc > STminであることはFC受信時に確認済み */
				CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_CS, (p_nsdu_inib->CanTpNc - p_ch_tx_cb->fc_stmin));
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_SND_CF;
			}
			/* ブロック最終 */
			else {
				/* [SWS_CanTp_00315] N_Bsタイマ設定 */
				CANTP_SET_TX_TIMER(p_ch_tx_cb, CANTP_TIME_BS, p_nsdu_inib->CanTpNb);
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_WAIT_FC;
			}
		}
	}
	/* 最終ブロック最終 */
	else {
		PduR_id = ((const TX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib))->PduRId_Confirmation;
		/* [SWS_CanTp_00090][SWS_CanTp_00177][SWS_CanTp_00204] 送信完了通知 */
		PduR_CanTpTxConfirmation(PduR_id, E_OK);
		/* タイマ停止 */
		CANTP_CLR_TX_TIMER(p_ch_tx_cb);
		/* 送信状態更新 */
		p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
	}
	return;
}

/* FC送信完了処理 */
/* p_ch_rx_cb  : チャネル受信管理ブロック */
/* p_nsdu_inib : NSDU初期化ブロック */
LOCAL_INLINE void
end_fc(CH_RX_CB *p_ch_rx_cb, const NSDU_INIB *p_nsdu_inib)
{
	switch (p_ch_rx_cb->fc_fs) {
	case CANTP_FS_CTS :
		/* [SWS_CanTp_00312] N_Crタイマ設定 */
		CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_CR, p_nsdu_inib->CanTpNc);
		/* [SWS_CanTp_00224] 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_WAIT_CF;
		break;
	case CANTP_FS_WAIT :
		/* [SWS_CanTp_00341] N_Brタイマ設定 */
		CANTP_SET_RX_TIMER(p_ch_rx_cb, CANTP_TIME_BR, p_nsdu_inib->CanTpNb);
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_SND_FC;
		break;
	case CANTP_FS_OVFLW :
		/* [SWS_CanTp_00318] 受信中止 */
		/* タイマ停止 */
		CANTP_CLR_RX_TIMER(p_ch_rx_cb);
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		break;
	default :
		/* 上記以外はありえない */
		/* タイマ停止 */
		CANTP_CLR_RX_TIMER(p_ch_rx_cb);
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
		break;
	}
	return;
}

/* 受信周期処理 */
/* p_ch_rx_cb : チャネル受信管理ブロック */
LOCAL_INLINE void
ch_rcv_main(CH_RX_CB *p_ch_rx_cb)
{
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	CanTp_ReturnType			retTimeout = CANTP_E_NOT_OK;		/* タイムアウト関数の戻り値 */
	
	/* 受信シーケンス */
	if (p_ch_rx_cb->rx_status != CANTP_STATUS_IDLE) {
		switch (p_ch_rx_cb->rx_status) {
		case CANTP_STATUS_SND_FC :		/* FC送信待ち */
			switch (p_ch_rx_cb->fc_fs) {
			case CANTP_FS_CTS :		/* CTS */
				/* [SWS_CanTp_00224] FC送信処理 */
				snd_fc(p_ch_rx_cb->id, CANTP_FS_CTS);
				break;
			case CANTP_FS_WAIT :	/* WAIT */
				/* 受信待機処理 */
				rcv_wait(p_ch_rx_cb);
				break;
			case CANTP_FS_OVFLW :	/* OVFLW */
				/* [SWS_CanTp_00318] FC送信処理 */
				snd_fc(p_ch_rx_cb->id, CANTP_FS_OVFLW);
				break;
			default :
				/* ありえない */
				/* タイマ停止 */
				CANTP_CLR_RX_TIMER(p_ch_rx_cb);
				/* 受信状態更新 */
				p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
				break;
			}
			break;
		case CANTP_STATUS_END_FC :
		case CANTP_STATUS_WAIT_CF :
			/* [SWS_CanTp_00164] N_Ar/N_Crタイムアウト判定 */
			retTimeout = chk_timeout(p_ch_rx_cb->rx_time, &(p_ch_rx_cb->rx_time_cnt));
			/* [SWS_CanTp_00311] N_Arタイムアウト発生(END_FC) */
			/* [SWS_CanTp_00313] N_Crタイムアウト発生(WAIT_CF) */
			if (retTimeout == CANTP_E_NOT_OK) {
				/* ID取得 */
				PduR_id = GET_RX_NSDU_INIB(p_ch_rx_cb->id)->PduRId_Indication;
				/* 受信失敗通知 */
				PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_MainFunction, CANTP_E_RX_COM);	/* [SWS_CanTp_00229] */
				
				/* タイマ停止 */
				CANTP_CLR_RX_TIMER(p_ch_rx_cb);
				
				/* 受信状態更新 */
				p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
			}
			break;
		/* case CANTP_STATUS_IDLE : */
		default:
			/* ありえない */
			/* タイマ停止 */
			CANTP_CLR_RX_TIMER(p_ch_rx_cb);
			/* 受信状態更新 */
			p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
			break;
		}
	}
	return;
}

/* 受信待機処理 */
/* p_ch_rx_cb : チャネル受信管理ブロック */
LOCAL_INLINE void
rcv_wait(CH_RX_CB *p_ch_rx_cb)
{
	const NSDU_INIB				*p_nsdu_inib = NULL_PTR;			/* NSDU初期化ブロック */
	const RX_NSDU_INIB			*p_rx_inib = NULL_PTR;				/* NSDU受信初期化ブロック */
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	PduInfoType					PduR_pduInfo;						/* PduRのAPI呼び出し時に使用するPduInfo */
	PduLengthType				bufsize = CANTP_ZERO;				/* PduRのAPI呼び出し時に使用するbufsize */
	BufReq_ReturnType			ret = BUFREQ_E_NOT_OK;				/* PduRのAPIの戻り値 */
	CanTp_ReturnType			retTimeout = CANTP_E_NOT_OK;		/* タイムアウト関数の戻り値 */
	uint32						next_block_size = CANTP_ZERO;		/* 次のブロックサイズ */
	
	/* 各情報取得 */
	p_nsdu_inib = GET_NSDU_INIB(p_ch_rx_cb->id);
	p_rx_inib = (const RX_NSDU_INIB*) (p_nsdu_inib->rxtx_inib);
	PduR_id = p_rx_inib->PduRId_Indication;
	
	/* [SWS_CanTp_00222] PduR_CanTpCopyRxDataで受信バッファの準備確認 */
	PduR_pduInfo.SduDataPtr = NULL_PTR;
	PduR_pduInfo.SduLength = (PduLengthType) CANTP_ZERO;
	ret = PduR_CanTpCopyRxData(PduR_id, &PduR_pduInfo, &bufsize);
	if (ret == BUFREQ_OK) {
		/* BS：0の場合 */
		if (p_ch_rx_cb->fc_bs == CANTP_ZERO) {
			/* 次のブロックサイズ：残りのデータ長 */
			next_block_size = p_ch_rx_cb->data_len;
		}
		else {
			/* 次のブロックサイズ：CFのデータサイズ×BS値 */
			next_block_size = (p_nsdu_inib->sdu_max_cf_data) * (p_ch_rx_cb->fc_bs);
			/* 残りのデータ長 < 次のブロックサイズの場合 */
			if (p_ch_rx_cb->data_len < next_block_size) {
				/* 次のブロックサイズ：残りのデータ長 */
				next_block_size = p_ch_rx_cb->data_len;
			}
		}
		
		/* 残りのバッファサイズ < 次のブロックサイズ */
		if (bufsize < next_block_size) {
			/* [SWS_CanTp_00164] N_Brタイムアウト判定 */
			retTimeout = chk_timeout(p_ch_rx_cb->rx_time, &(p_ch_rx_cb->rx_time_cnt));
			/* N_Brタイムアウト発生 */
			if (retTimeout == CANTP_E_NOT_OK) {
				/* FC(WAIT)送信回数確認 */
				if (p_ch_rx_cb->wft_cnt < p_rx_inib->CanTpRxWftMax) {
					/* [SWS_CanTp_00341] */
					(p_ch_rx_cb->wft_cnt)++;
					/* FC(WAIT)送信 */
					snd_fc(p_ch_rx_cb->id, CANTP_FS_WAIT);
				}
				else {
					/* [SWS_CanTp_00223] 受信失敗通知 */
					PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
					CANTP_SWITCH_DET_ERROR(CanTpServiceId_MainFunction, CANTP_E_RX_COM);	/* [SWS_CanTp_00229] */
					/* タイマ停止 */
					CANTP_CLR_RX_TIMER(p_ch_rx_cb);
					/* 受信状態更新 */
					p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
				}
			}
		}
		else {
			/* [SWS_CanTp_00224] */
			/* FC(CTS)送信 */
			p_ch_rx_cb->fc_fs = CANTP_FS_CTS;
			snd_fc(p_ch_rx_cb->id, CANTP_FS_CTS);
		}
	}
	else if (ret == BUFREQ_E_BUSY) {
		/* [SWS_CanTp_00164] N_Brタイムアウト判定 */
		retTimeout = chk_timeout(p_ch_rx_cb->rx_time, &(p_ch_rx_cb->rx_time_cnt));
		/* N_Brタイムアウト発生 */
		if (retTimeout == CANTP_E_NOT_OK) {
			if (p_ch_rx_cb->wft_cnt < p_rx_inib->CanTpRxWftMax) {
				p_ch_rx_cb->wft_cnt++;
				/* FC(WAIT)送信 */
				snd_fc(p_ch_rx_cb->id, CANTP_FS_WAIT);
			}
			else {
				/* 受信失敗通知 */
				PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_MainFunction, CANTP_E_RX_COM);	/* [SWS_CanTp_00229] */
				/* タイマ停止 */
				CANTP_CLR_RX_TIMER(p_ch_rx_cb);
				/* 受信状態更新 */
				p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
			}
		}
	}
	else {
		/* 受信失敗通知 */
		PduR_CanTpRxIndication(PduR_id, E_NOT_OK);
		CANTP_SWITCH_DET_ERROR(CanTpServiceId_MainFunction, CANTP_E_RX_COM);	/* [SWS_CanTp_00229] */
		/* タイマ停止 */
		CANTP_CLR_RX_TIMER(p_ch_rx_cb);
		/* 受信状態更新 */
		p_ch_rx_cb->rx_status = CANTP_STATUS_IDLE;
	}
	return;
}

/* 送信周期処理 */
/* p_ch_tx_cb : チャネル送信管理ブロック */
LOCAL_INLINE void
ch_snd_main(CH_TX_CB *p_ch_tx_cb)
{
	PduIdType					PduR_id;							/* PduRのAPI呼び出し時に使用するID */
	CanTp_ReturnType			retTimeout = CANTP_E_NOT_OK;		/* タイムアウト関数の戻り値 */
	
	/* 送信シーケンス */
	if (p_ch_tx_cb->tx_status != CANTP_STATUS_IDLE) {
		switch (p_ch_tx_cb->tx_status) {
		case CANTP_STATUS_SND_SF :
			/* SF送信処理 */
			snd_sf(p_ch_tx_cb->id, p_ch_tx_cb->sdu_len);
			break;
		case CANTP_STATUS_SND_FF :
			/* FF送信処理 */
			snd_ff(p_ch_tx_cb->id, p_ch_tx_cb->sdu_len);
			break;
		case CANTP_STATUS_SND_CF :
			/* STminカウンタ */
			if (p_ch_tx_cb->stmin_cnt != CANTP_ZERO) {
				(p_ch_tx_cb->stmin_cnt)--;
			}
			if (p_ch_tx_cb->stmin_cnt == CANTP_ZERO) {
				/* CF送信処理 */
				snd_cf(p_ch_tx_cb->id, p_ch_tx_cb->data_len);
			}
			break;
		case CANTP_STATUS_END_SF :
		case CANTP_STATUS_END_FF :
		case CANTP_STATUS_END_CF :
		case CANTP_STATUS_WAIT_FC :
			/* [SWS_CanTp_00164] N_As/N_Bsタイムアウト判定 */
			retTimeout = chk_timeout(p_ch_tx_cb->tx_time, &(p_ch_tx_cb->tx_time_cnt));
			/* [SWS_CanTp_00075][SWS_CanTp_00310] N_Asタイムアウト発生(END_SF，END_FF，END_CFの場合) */
			/* [SWS_CanTp_00316] N_Bsタイムアウト発生(WAIT_FCの場合) */
			if (retTimeout == CANTP_E_NOT_OK) {
				/* ID取得 */
				PduR_id = GET_TX_NSDU_INIB(p_ch_tx_cb->id)->PduRId_Confirmation;
				/* 送信失敗通知 */
				PduR_CanTpTxConfirmation(PduR_id, E_NOT_OK);
				CANTP_SWITCH_DET_ERROR(CanTpServiceId_MainFunction, CANTP_E_TX_COM);	/* [SWS_CanTp_00229] */
				
				/* タイマ停止 */
				CANTP_CLR_TX_TIMER(p_ch_tx_cb);
				
				/* 送信状態更新 */
				p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
			}
			break;
		/* case CANTP_STATUS_IDLE : */
		default:
			/* ありえない */
			/* タイマ停止 */
			CANTP_CLR_TX_TIMER(p_ch_tx_cb);
			/* 送信状態更新 */
			p_ch_tx_cb->tx_status = CANTP_STATUS_IDLE;
			break;
		}
	}
	return;
}

/* タイムアウト確認 */
/* timer      : タイマ状態（タイマ種別） */
/* time_cnt   : タイマカウンタ */
/* 戻り値     : CANTP_E_OK（タイムアウト未発生）  */
/*              CANTP_E_NOT_OK（タイムアウト発生）*/
LOCAL_INLINE CanTp_ReturnType
chk_timeout(uint8 timer, uint32 *time_cnt)
{
	CanTp_ReturnType			retCanTp = CANTP_E_OK;				/* 戻り値 */
	
	if (timer != CANTP_TIME_STOP) {
		if (*time_cnt > CANTP_TIMECNT_CLR) {
			(*time_cnt)--;
			if (*time_cnt == CANTP_TIMECNT_CLR) {
				/* タイムアウト発生 */
				retCanTp = CANTP_E_NOT_OK;
			}
		}
	}
	return(retCanTp);
}

/* STminカウント値取得処理 */
/* stmin      : STmin値 */
/* 戻り値     : STminカウント値  */
LOCAL_INLINE uint8
get_stmin_cnt(uint8 stmin)
{
	uint8						stmin_count;
	uint8						tmp;
	
	/* 0x00-0x7F:0ms-127ms */
	if (stmin <= CANTP_FC_STMIN_MS_MAX) {
		tmp = stmin;
	}
	/* [NCanTp_00034] 0xF1-0xF9:100us-900usのため1msとする */
	else if ((stmin >= CANTP_FC_STMIN_US_MIN) && (stmin <= CANTP_FC_STMIN_US_MAX)) {
		tmp = CANTP_FC_STMIN_MS_MIN;
	}
	/* Reserveのため127msとする */
	else {
		tmp = CANTP_FC_STMIN_MS_MAX;
	}
	stmin_count = (uint8) (tmp / GET_PERIOD());
	if((tmp % GET_PERIOD()) != CANTP_ZERO) {
		/* 周期時間で割り切れない場合はカウンタ+1 */
		stmin_count++;
	}
	
	return(stmin_count);
}

