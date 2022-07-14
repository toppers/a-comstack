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
 *  $Id: Com.c 797 2014-12-01 08:44:47Z panasonic-ayane $
 */

/* [COM584] Com.c */

/*
 *  開発方針
 *  - [COM010] APIはOSEK/VDX COMと同等のものとする
 *  - [COM011] OSEK仕様とAUTOSAR仕様で相違があるものはAUTOSAR仕様に準拠する
 *  - [COM012] AUTOSAR仕様でのみ規定されている仕様も実装する
 *  - [COM013] ネットワークメッセージ等の一部のOSEK仕様は実装が必須でないため，実装しない
 */

/* [COM220] */
#include "Com.h"
/*
 *  [NCOM032] SchM_Com.hはRTEジェネレータにより生成される
 *  [COM320][COM321] 本実装ではすべてのシステムサービスをリエントラントとする
 */
#include "SchM_Com.h"

#if COM_DEV_ERROR_DETECT == STD_ON
/* [COM670] */
#include "Det.h"
#endif /* COM_DEV_ERROR_DETECT == STD_ON */

/* [COM669] */
/* PduR_Com.hはPduRジェネレータにより生成される */
#include "PduR_Com.h"

/*
 *  内部関数のプロトタイプ宣言
 */
LOCAL_INLINE void set_signal_for_send(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void set_signal_for_receive(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void get_signal(const SIGNAL_INIB *p_signal_inib, void *p_data);
LOCAL_INLINE void set_filter_buffer(const SIGNAL_INIB	*p_signal_inib, const void *p_data);
LOCAL_INLINE void packing(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void pack_little_endian(uint8 p_buffer[], PduLengthType byte_index, uint8 pos_lsb, uint8 bitsize, uint32 signal_data);
LOCAL_INLINE void pack_big_endian(uint8 p_buffer[], PduLengthType byte_index, uint8 pos_lsb, uint8 bitsize, uint32 signal_data);
LOCAL_INLINE void ipdu_receive(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void unpacking(const SIGNAL_INIB *p_signal_inib, void *p_data);
LOCAL_INLINE void set_updatebit(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE void clear_updatebit(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE Std_ReturnType mdt_send(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void mdt_countdown(TX_IPDU_CB *p_tx_ipdu_cb);
LOCAL_INLINE void mdt_set(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE boolean changed_signal(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE boolean check_tms(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE uint32 copy_signal_to_uint32(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE sint32 cast_signal_to_sint32(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE boolean invalid_action(const SIGNAL_INIB *p_signal_inib, void *p_data);
LOCAL_INLINE void start_tx_dm(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void start_rx_dm(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void stop_rx_dm(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void check_signal_dm(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE void reset_signal_dm(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE boolean check_updatebit(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE Std_ReturnType direct_send(const IPDU_INIB *p_ipdu_inib, TX_IPDU_CB *p_tx_ipdu_cb);
LOCAL_INLINE Std_ReturnType periodic_send(const IPDU_INIB *p_ipdu_inib, TX_IPDU_CB *p_tx_ipdu_cb, Std_ReturnType send_flg);
LOCAL_INLINE Std_ReturnType trigger_send(const IPDU_INIB *p_ipdu_inib, Std_ReturnType send_flg);
static void ipdu_initialize(const IPDU_INIB *p_ipdu_inib);
static boolean filtering(const SIGNAL_INIB *p_signal_inib, const void *p_data);

/*
 *  現在実行中のComコンフィギュレーション情報
 */
static const Com_ConfigType	*p_cur_com_config;
static const SIGNAL_INIB	*p_cur_signal_inib;
static const IPDU_INIB		* const *pp_cur_all_ipdu_inib;
static const IPDU_INIB		*p_cur_rx_ipdu_inib;
static const IPDU_INIB		*p_cur_tx_ipdu_inib;

/*
 *  Comの初期化状態
 */
static Com_StatusType		com_state = COM_UNINIT;


/*
 *  [COM432] Com_Init
 */
void
Com_Init(const Com_ConfigType *config)
{
	PduIdType			i;
	PduLengthType		j;
	const IPDU_INIB		*p_ipdu_inib;
	const TX_IPDU_INIB	*p_tx_ipdu_inib;

	SchM_Enter_Com_Reentrant_0();

	/* [COM373] Com_Initによるポストビルドパラメータは未初期化(未使用)時のみ更新できる */
	COM_CHECK_UNINITIALIZED(COMServiceId_Init);

	/* [COM433] 不正なポインタへの対応は，NULL_PTRに対してのみ行う */
	if (config == NULL_PTR) {
		/* [NCOM040] NULL_PTRの場合，ComConfigurationIdが0のコンフィギュレーションを使う */
		config = &com_config[0];
	}

	/* [COM328][COM444] 現在実行中のコンフィグレーション情報を保持 */
	p_cur_com_config = config;
	p_cur_signal_inib = p_cur_com_config->p_signal_inib_table;
	pp_cur_all_ipdu_inib = p_cur_com_config->pp_ipdu_inib_table;
	p_cur_rx_ipdu_inib = p_cur_com_config->p_rx_ipdu_inib_list;
	p_cur_tx_ipdu_inib = p_cur_com_config->p_tx_ipdu_inib_list;

	/* [COM015] IPDUバッファを未使用データで初期化 */
	for (i = 0U; i < GET_TX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_TX_IPDU_INIB(i);
		p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
		for (j = 0U; j < p_ipdu_inib->PduLength; j++) {
			(p_ipdu_inib->p_ipdu_buffer)[j] = p_tx_ipdu_inib->ComTxIPduUnusedAreasDefault;
		}
	}

	/* 全IPDU共通の初期化処理 */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);

		/* [COM217][COM098][COM483][COM128][COM117] IPDUの初期化 */
		ipdu_initialize(p_ipdu_inib);

		/* [COM328][COM444]IPDUの停止 */
		IPDU_CLEAR_STARTED(p_ipdu_inib->p_state);
	}

	/* COMを初期化状態へ移行 */
	com_state = COM_INIT;

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM130] Com_DeInit
 */
void
Com_DeInit(void)
{
	PduIdType		i;
	const IPDU_INIB	*p_ipdu_inib;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_DeInit);

	/* [COM129] 全IPDUグループを停止 */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);
		IPDU_CLEAR_ALL(p_ipdu_inib->p_state);
	}

	/* COMを未初期化状態へ移行 */
	com_state = COM_UNINIT;

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM751] Com_IpduGroupControl
 */
void
Com_IpduGroupControl(Com_IpduGroupVector ipduGroupVector, boolean initialize)
{
	const IPDU_INIB			*p_ipdu_inib;
	const TX_IPDU_INIB		*p_tx_ipdu_inib;
	const SIGNAL_INIB		*p_signal_inib;
	const Com_ConfigType	*p_saved_config;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	Com_CbkTxErr			notification;
	boolean					start_flg;
	uint8					target, belong;
	PduIdType				i;
	Com_IpduGroupIdType		j;
	Com_SignalIdType		k;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_IpduGroupControl);

	/*
	 *  [COM771]
	 *  IPDU停止→少なくとも1つの所属IPDUグループを開始：開始
	 *  IPDU開始→すべての所属IPDUグループを停止       ：停止
	 *  IPDU停止→すべての所属IPDUグループを停止       ：何もしない
	 *  IPDU開始→少なくとも1つの所属IPDUグループを開始：何もしない
	 */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);

		start_flg = FALSE;
		for (j = 0U; j < GET_VECTOR_NUM(); j++) {
			/* 開始指示されたIPDUグループベクタ */
			target = ipduGroupVector[j];
			/* 対象IPDUの所属IPDUグループベクタ */
			belong = (*(p_ipdu_inib->p_ipdu_group_vector))[j];

			/* 1つでも所属IPDUグループが開始指示されているか */
			if ((target & belong) != 0U) {
				start_flg = TRUE;
				/* 1つでも開始指示されていればよい */
				break;
			}
		}

		/*
		 *  現在のIPDUの状態に合わせて処理を行う
		 *  [COM613] IPDUグループ自体の状態は不要のため管理しない
		 */
		if (start_flg != FALSE) {
			/* [COM614] 停止しているIPDUに対して，IPDUを開始する */
			if (!IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
				/*
				 *  [COM740] 本システムサービスがinitialize = FALSEで，Com_Init後に初めて呼び出され開始した場合，
				 *           initialize = TRUEで呼び出された場合と同じ結果になる
				 *  [COMa001] initialize = FALSEで開始された場合，周期のMF回数カウンタは初期化しない
				 */
				if (initialize != FALSE) {
					/* IPDUバッファを未使用データで初期化 */
					if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
						p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
						for (j = 0U; j < p_ipdu_inib->PduLength; j++) {
							(p_ipdu_inib->p_ipdu_buffer)[j] = p_tx_ipdu_inib->ComTxIPduUnusedAreasDefault;
						}
					}
					/* [COM222][COM217] IPDUの初期化 */
					ipdu_initialize(p_ipdu_inib);

#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
					/* [COM778] 保留された送信要求を無効にする */
					IPDU_CLEAR_RETRITED(p_ipdu_inib->p_state);
#endif
				}

				if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
					p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

					/* initialize = TRUEの場合，ipdu_initialize()の中でTMS判定をするため，ここではFALSEの場合のみ実施する */
					if (initialize == FALSE) {
						/* [COM229][COM223][COM032][COM238] TMSを決定し，送信モードを決定する */
						p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
						if (check_tms(p_ipdu_inib) != FALSE) {
							p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
						}
						else {
							p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
						}
					}

					/* カウンタの初期化 */
					p_tx_ipdu_cb->repeat_cnt = 0U;
					p_tx_ipdu_cb->interval_mf_cnt = 0U;
					p_tx_ipdu_cb->mdt_mf_cnt = 0U;
					p_tx_ipdu_cb->queuing_cnt = 0U;
					p_tx_ipdu_cb->dm_mf_cnt = 0U;
				}
				else {
					/* [COM787][COM733] DM開始 */
					start_rx_dm(p_ipdu_inib);
				}

				/* [COM612][COM114] IPDUの開始 */
				IPDU_SET_STARTED(p_ipdu_inib->p_state);
			}
			else {
				if ((p_ipdu_inib->ComIPduDirection == COM_RECEIVE) && (!IPDU_IS_DM(p_ipdu_inib->p_state))) {
					/* [COM787][COM733] DM開始 */
					start_rx_dm(p_ipdu_inib);
				}
			}

		}
		/* start_flg == FALSE かつ IPDUが開始  */
		else if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			/*
			 *  IPDUの停止
			 *  [COM115][COM684] 送信，受信処理を無効にする
			 *  [COM685] DM停止
			 */
			IPDU_CLEAR_ALL(p_ipdu_inib->p_state);
			p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
			for (k = 0U; k < p_ipdu_inib->tnum_signal; k++) {
				p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[k]);
				if ((p_signal_inib->ComErrorNotification != NULL_PTR) && (p_tx_ipdu_cb->queuing_cnt != 0U)) {
					/* 排他エリア内でコールバックのポインタを取り出す */
					notification = p_signal_inib->ComErrorNotification;
					/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
					p_saved_config = p_cur_com_config;

					/* [COM479] */
					SchM_Exit_Com_Reentrant_0();
					notification();
					SchM_Enter_Com_Reentrant_0();

					/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
					COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_IpduGroupControl);
				}
			}
		}
		else {
			/* [COM615] 状態が変わらない場合は何もしない */
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM752] Com_ReceptionDMControl
 */
void
Com_ReceptionDMControl(Com_IpduGroupVector ipduGroupVector)
{
	PduIdType			i;
	Com_IpduGroupIdType	j;
	uint8				target, belong;
	boolean				start_flg;
	const IPDU_INIB		*p_ipdu_inib;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_ReceptionDMControl);

	/* [COM534] 受信IPDUに対して処理を行う */
	for (i = 0U; i < GET_RX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_RX_IPDU_INIB(i);

		start_flg = FALSE;
		for (j = 0U; j < GET_VECTOR_NUM(); j++) {
			/* DM開始指示されたIPDUグループベクタ */
			target = ipduGroupVector[j];
			/* 対象IPDUの所属IPDUグループベクタ */
			belong = (*(p_ipdu_inib->p_ipdu_group_vector))[j];

			/* [COM772] 1つでも所属IPDUグループのDMが開始指示されているか */
			if ((target & belong) != 0U) {
				start_flg = TRUE;
				/* 1つでも開始指示されていればよい */
				break;
			}
		}

		/* [COM616][COM617] 受信DMを指定された状態に変更し，開始または停止する */
		if ((!IPDU_IS_DM(p_ipdu_inib->p_state)) && (start_flg != FALSE)) {
			/* DM開始 */
			start_rx_dm(p_ipdu_inib);
		}
		else if (IPDU_IS_DM(p_ipdu_inib->p_state) && (start_flg == FALSE)) {
			/* DM停止 */
			stop_rx_dm(p_ipdu_inib);
		}
		else {
			/* [COM618][COM225][COM486] 状態が変わらない場合は何もしない */
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM194] Com_GetStatus
 */
Com_StatusType
Com_GetStatus(void)
{
	return(com_state);
}

/*
 *  [COM375] Com_GetConfigurationId
 */
uint32
Com_GetConfigurationId(void)
{
	uint32 id;

	if (com_state != COM_INIT) {
		/* [NCOM001] */
		id = COM_INVALID_UINT32;
	}
	else {
		/* [COM619] */
		id = p_cur_com_config->ComConfigurationId;
	}

	return(id);
}

/* [COM425] Com_GetVersionInfoの有無はコンフィギュレーションで切り替え */
#if (COM_VERSION_INFO_API == STD_ON)
/*
 *  [COM426] Com_GetVersionInfo
 *  [COM434] マクロで実装してもよいがNULLポインタチェックのため関数とする
 */
void
Com_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	/* [NCOM039] */
	COM_CHECK_NULL_POINTER(versioninfo != NULL_PTR, COMServiceId_GetVersionInfo);

	/* [COM424] */
	versioninfo->vendorID = COM_VENDOR_ID;
	versioninfo->moduleID = COM_MODULE_ID;
	versioninfo->sw_major_version = COM_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = COM_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = COM_SW_PATCH_VERSION;

  error_exit:
	return;
}
#endif /* COM_VERSION_INFO_API */

/*
 *  [COM749] Com_ClearIpduGroupVector
 */
void
Com_ClearIpduGroupVector(Com_IpduGroupVector ipduGroupVector)
{
	Com_IpduGroupIdType	i;

	for (i = 0U; i < IPDU_GROUP_VECTOR_NUM; i++) {
		ipduGroupVector[i] = 0U;
	}

	return;
}

/*
 *  [COM750] Com_SetIpduGroup
 */
void
Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval)
{
	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_SetIpduGroup);
	COM_CHECK_PARAM(ipduGroupId < GET_IPDU_G_NUM(), COMServiceId_SetIpduGroup);

	/* [COM623] 指定されたIPDUが対応するビットをセット */
	if (bitval) {
		ipduGroupVector[ipduGroupId / 8U] |= (uint8) (1U << (ipduGroupId % 8U));
	}
	else {
		ipduGroupVector[ipduGroupId / 8U] &= (uint8) (~(uint8) (1U << (ipduGroupId % 8U)));
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();

	return;
}

/*
 *  [COM197] Com_SendSignal
 */
uint8
Com_SendSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
	const SIGNAL_INIB	*p_signal_inib;
	const IPDU_INIB		*p_ipdu_inib;
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_SIGNAL_CB		*p_tx_signal_cb;
	TX_IPDU_CB			*p_tx_ipdu_cb;
	boolean				changed;
	boolean				tms;
	boolean				never;
	uint8				ercd;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED_ERCD(COMServiceId_SendSignal);
	COM_CHECK_PARAM_ERCD(SignalId < GET_SIGNAL_NUM(), COMServiceId_SendSignal);
	COM_CHECK_NULL_POINTER_ERCD(SignalDataPtr != NULL_PTR, COMServiceId_SendSignal);

	/* [COM624] */
	p_signal_inib = GET_SIGNAL_INIB(SignalId);
	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
	p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

	COM_CHECK_PARAM_ERCD(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_SendSignal);

	/* シグナルデータを比較 */
	changed = changed_signal(p_signal_inib, SignalDataPtr);

	if (changed != FALSE) {
		/* シグナルバッファにシグナルデータを格納する */
		set_signal_for_send(p_signal_inib, SignalDataPtr);

		/* [COM334][COM221] IPDUが停止中でもバッファの更新(パッキング)を行う */
		packing(p_signal_inib, SignalDataPtr);
	}

	/* [COMa003] アップデートビット設定 */
	set_updatebit(p_signal_inib);

	/* [COM245] COM_NEVER以外のフィルタを持つ場合のみ，TMS判定を行う */
	if ((p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) && (p_signal_inib->ComFilterAlgorithm != COM_NEVER)) {
		/* [COM602] TMC判定 */
		p_tx_signal_cb->tmc = filtering(p_signal_inib, SignalDataPtr);

		/* [COM605] TMS判定 */
		tms = check_tms(p_ipdu_inib);
		never = FALSE;
	}
	else {
		never = TRUE;
	}

	/* COM_NEVERのシグナルによってTMSが切り替わることはない */
	if (never == FALSE) {
		if ((tms != FALSE) && (p_tx_ipdu_cb->p_cur_tx_mode_inib == p_tx_ipdu_inib->p_tx_mode_false_inib)) {
			/* [COM032] TMS切り替え(false -> true) */
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
			/* [COM244][COM495] タイマリセット */
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
		}
		else if ((tms == FALSE) && (p_tx_ipdu_cb->p_cur_tx_mode_inib == p_tx_ipdu_inib->p_tx_mode_true_inib)) {
			/* [COM032] TMS切り替え(true -> false) */
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
			/* [COM244][COM495] タイマリセット */
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
		}
		else {
			/* TMSが切り替わらない場合，何もしない */
		}
	}

	/* IPDU開始判定 */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

		COM_CHECK_PARAM_ERCD(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
							  (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
							 (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_SendSignal);

		/* [COM279] COM_DIRECT,COM_MIXED */
		if ((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_DIRECT) ||
			(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_MIXED)) {

			/* [COM330][COM734] 繰り返し回数カウンタ設定 */
			if ((p_signal_inib->ComTransferProperty == COM_TRIGGERED) ||
				((p_signal_inib->ComTransferProperty == COM_TRIGGERED_ON_CHANGE) && (changed != FALSE))) {

				p_tx_ipdu_cb->repeat_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions;

				/* バッファ更新ビットを設定 */
				IPDU_SET_UPDATED(p_ipdu_inib->p_state);
			}
			/* [COM767][COM768] */
			else if ((p_signal_inib->ComTransferProperty == COM_TRIGGERED_WITHOUT_REPETITION) ||
					 ((p_signal_inib->ComTransferProperty == COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION) && (changed != FALSE))) {

				/* [COM467] 1回のみ送信する */
				p_tx_ipdu_cb->repeat_cnt = 0U;

				IPDU_SET_WITHOUT_REPETITION(p_ipdu_inib->p_state);

				/* [NCOM006]バッファ更新ビットを設定 */
				IPDU_SET_UPDATED(p_ipdu_inib->p_state);
			}
			else {
				/* COM_PENDING: 何もしない */
			}

			p_tx_ipdu_cb->interval_mf_cnt = 0U;
			if (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_DIRECT) {
				/* COM_DIRECTはperiod_mf_cntを使用しないので初期化する */
				p_tx_ipdu_cb->period_mf_cnt = 0U;
			}
		}
		ercd = E_OK;
	}
	else {
		ercd = COM_SERVICE_NOT_AVAILABLE;
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();

	return(ercd);
}

/*
 *  [COM198] Com_ReceiveSignal
 */
uint8
Com_ReceiveSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
	const SIGNAL_INIB	*p_signal_inib;
	const IPDU_INIB		*p_ipdu_inib;
	uint8				ercd;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED_ERCD(COMServiceId_ReceiveSignal);
	COM_CHECK_PARAM_ERCD(SignalId < GET_SIGNAL_NUM(), COMServiceId_ReceiveSignal);
	COM_CHECK_NULL_POINTER_ERCD(SignalDataPtr != NULL_PTR, COMServiceId_ReceiveSignal);

	p_signal_inib = GET_SIGNAL_INIB(SignalId);
	p_ipdu_inib = p_signal_inib->p_ipdu_inib;

	COM_CHECK_PARAM_ERCD(p_ipdu_inib->ComIPduDirection == COM_RECEIVE, COMServiceId_ReceiveSignal);

	/* [COM631] SignalDataPtrにSignalIdのシグナルデータをコピーする */
	get_signal(p_signal_inib, SignalDataPtr);

	/* IPDU開始状態判定 */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
		ercd = E_OK;
	}
	else {
		ercd = COM_SERVICE_NOT_AVAILABLE;
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();

	return(ercd);
}

/*
 *  [COM203] Com_InvalidateSignal
 */
uint8
Com_InvalidateSignal(Com_SignalIdType SignalId)
{
	const SIGNAL_INIB	*p_signal_inib;
	const void			*p_invaild;
	uint8				ercd;

	SchM_Enter_Com_Reentrant_2();

	COM_CHECK_INITIALIZED_ERCD(COMServiceId_SendSignal);
	COM_CHECK_PARAM_ERCD(SignalId < GET_SIGNAL_NUM(), COMServiceId_InvalidateSignal);

	p_signal_inib = GET_SIGNAL_INIB(SignalId);
	/* 排他エリア内で無効値を取り出す */
	p_invaild = p_signal_inib->ComSignalDataInvalidValue;

	if (p_invaild != NULL_PTR) {
		/* [COM099][COM642] */
		ercd = Com_SendSignal(SignalId, p_invaild);
	}
	else {
		/* [COM643] */
		ercd = COM_SERVICE_NOT_AVAILABLE;
	}

  error_exit:
	SchM_Exit_Com_Reentrant_2();

	return(ercd);
}

/*
 *  [COM348] Com_TriggerIPDUSend
 */
void
Com_TriggerIPDUSend(PduIdType PduId)
{
	const IPDU_INIB	*p_ipdu_inib;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_TriggerIPDUSend);
	COM_CHECK_PARAM(PduId < GET_IPDU_NUM(), COMServiceId_TriggerIPDUSend);

	p_ipdu_inib = GET_TX_IPDU_INIB(PduId);
	COM_CHECK_PARAM(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_TriggerIPDUSend);

	/* IPDU停止時は何もしない */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
		/* [COM492]次回のMF送信時にコールアウトも呼び出す */
		IPDU_SET_TRIGGERED(p_ipdu_inib->p_state);
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM784] Com_SwitchIpduTxMode
 */
void
Com_SwitchIpduTxMode(PduIdType PduId, boolean Mode)
{
	const IPDU_INIB		*p_ipdu_inib;
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_SwitchIpduTxMode);
	COM_CHECK_PARAM(PduId < GET_IPDU_NUM(), COMServiceId_SwitchIpduTxMode);

	p_ipdu_inib = GET_TX_IPDU_INIB(PduId);
	COM_CHECK_PARAM(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_SwitchIpduTxMode);

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

	/* 次の開始時にフィルタ判定して結果が変わるため，IPDU停止時に実施する必要はない */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
		if (Mode != FALSE) {
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
		}
		else {
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM123] Com_RxIndication
 */
void
Com_RxIndication(PduIdType RxPduId, PduInfoType *PduInfoPtr)
{
	const IPDU_INIB			*p_ipdu_inib;
	const Com_ConfigType	*p_saved_config;
	Com_IpduCallout			callout;
	PduIdType				i;
	boolean					ret;

	/* [COM649] 割込みから呼び出される可能性があるので排他が必要 */
	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_RxIndication);
	COM_CHECK_PARAM(RxPduId < GET_IPDU_NUM(), COMServiceId_RxIndication);
	COM_CHECK_NULL_POINTER(PduInfoPtr != NULL_PTR, COMServiceId_RxIndication);

	p_ipdu_inib = GET_IPDU_INIB(RxPduId);

	COM_CHECK_PARAM((p_ipdu_inib->ComIPduDirection == COM_RECEIVE), COMServiceId_RxIndication);
	COM_CHECK_PARAM((p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) ||
					(p_ipdu_inib->ComIPduSignalProcessing == COM_DEFERRED), COMServiceId_RxIndication);

	/* [COMa005] 受信したIPDUのデータ長が設定値以上の場合，処理を実施する */
	if (PduInfoPtr->SduLength >= p_ipdu_inib->PduLength) {
		/* IPDU停止時は何もしない */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			/* [COM700] コールアウト処理 */
			if (p_ipdu_inib->ComIPduCallout != NULL_PTR) {
				/* 排他エリア内でコールアウトのポインタを取り出す */
				callout = p_ipdu_inib->ComIPduCallout;
				/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
				p_saved_config = p_cur_com_config;

				/* [COM381] Com_TriggerIPDUSend, Com_SendSignalはコールアウトから呼出し可能とする */
				SchM_Exit_Com_Reentrant_0();
				ret = callout(RxPduId, PduInfoPtr->SduDataPtr);
				SchM_Enter_Com_Reentrant_0();

				/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
				COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_RxIndication);

				if (ret == FALSE) {
					/* [COMa004] FALSEの場合，以降の処理を実施しない */
					goto error_exit;
				}
			}

			/* IPDUバッファに受信データをコピー */
			for (i = 0U; i < p_ipdu_inib->PduLength; i++) {
				(p_ipdu_inib->p_ipdu_buffer)[i] = (PduInfoPtr->SduDataPtr)[i];
			}

			if (p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) {
				/* [COM300] COM_IMMEDIATEならばここで受信処理 */
				ipdu_receive(p_ipdu_inib);
			}
			/* IPDUを受信状態に設定 */
			IPDU_SET_NOTICED(p_ipdu_inib->p_state);
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM124] Com_TxConfirmation
 */
void
Com_TxConfirmation(PduIdType TxPduId)
{
	const IPDU_INIB			*p_ipdu_inib;
	const TX_IPDU_INIB		*p_tx_ipdu_inib;
	const SIGNAL_INIB		*p_signal_inib;
	const Com_ConfigType	*p_saved_config;
	Com_CbkAck				notification;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	Com_SignalIdType		i;

	/* [COM652] 割込みから呼び出される可能性があるので排他が必要 */
	SchM_Enter_Com_Reentrant_1();

	COM_CHECK_INITIALIZED(COMServiceId_TxConfirmation);
	COM_CHECK_PARAM(TxPduId < GET_IPDU_NUM(), COMServiceId_TxConfirmation);

	p_ipdu_inib = GET_TX_IPDU_INIB(TxPduId);

	COM_CHECK_PARAM(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_TxConfirmation);

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

	/* PduR_ComTransmitを送信した場合のみ受け付ける */
	if (p_tx_ipdu_cb->queuing_cnt != 0U) {
		p_tx_ipdu_cb->queuing_cnt--;

		/* [COM577] */
		if (p_tx_ipdu_inib->ComTxIPduClearUpdateBit == COM_CONFIRMATION) {
			for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
				p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
				/* アップデートビットクリア */
				clear_updatebit(p_signal_inib);
			}
		}

		/* [COM469] MDTカウンタが0より大きい場合，MDTカウンタを再設定する */
		if (p_tx_ipdu_inib->ComMinimumDelayTime > 0U) {
			mdt_set(p_ipdu_inib);
		}

		if (p_tx_ipdu_cb->repeat_cnt > 0U) {
			p_tx_ipdu_cb->repeat_cnt--;
		}

		/* IPDU開始中 */
		/* [COMa002] IPDU停止時はRTEへ通知を行わない */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			/* 送信完了通知 */
			if (p_tx_ipdu_cb->repeat_cnt == 0U) {
				IPDU_CLEAR_UPDATED(p_ipdu_inib->p_state);
				/* 通知判定 */
				if (p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) {
					for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
						p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
						if (p_signal_inib->ComNotification != NULL_PTR) {
							/* 排他エリア内でコールバックのポインタを取り出す */
							notification = p_signal_inib->ComNotification;
							/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
							p_saved_config = p_cur_com_config;

							/* 送信完了通知 */
							SchM_Exit_Com_Reentrant_1();
							notification();
							SchM_Enter_Com_Reentrant_1();

							/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
							COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_TxConfirmation);
						}
					}
					/* [COM308] DM停止 */
					IPDU_CLEAR_DM(p_ipdu_inib->p_state);
				}
				else {
					/* Com_MainFunctionTxで通知する */
					IPDU_SET_NOTICED(p_ipdu_inib->p_state);
				}
			}
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_1();
	return;
}

/*
 *  [COM398] Com_MainFunctionRx
 */
void
Com_MainFunctionRx(void)
{
	PduIdType			i;
	uint16				j;
	const IPDU_INIB		*p_ipdu_inib;
	const SIGNAL_INIB	*p_signal_inib;

	SchM_Enter_Com_Reentrant_0();

	/* [COM664] 初期化されていない場合は何もせずにreturn */
	if (com_state != COM_INIT) {
		goto error_exit;
	}

	for (i = 0U; i < GET_RX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_RX_IPDU_INIB(i);

		/* IPDU状態判定(開始状態) */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			if (IPDU_IS_NOTICED(p_ipdu_inib->p_state)) {
				if (p_ipdu_inib->ComIPduSignalProcessing == COM_DEFERRED) {
					/* [COM301] 受信状態となっているCOM_DEFERREDのIPDUはここで受信処理をする */
					ipdu_receive(p_ipdu_inib);
				}

				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);

					if (check_updatebit(p_signal_inib) != FALSE) {
						/*
						 * [COM715][NCOM031][COM738] 受信DMカウンタリセット処理
						 * [NCOM034] 受信DMをリセットした場合，受信DMをチェックしない
						 */
						reset_signal_dm(p_signal_inib);
					}
					else {
						/* アップデートビットが更新されてないシグナルは受信DMをチェックする */
						check_signal_dm(p_signal_inib);
					}
				}

				/* IPDUの受信状態をクリア */
				IPDU_CLEAR_NOTICED(p_ipdu_inib->p_state);
			}
			else {
				/* [COM290][COM292][NCOM035]受信状態でない，IPDUは受信DMをチェックする */
				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
					check_signal_dm(p_signal_inib);
				}
			}
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  [COM399] Com_MainFunctionTx
 */
void
Com_MainFunctionTx(void)
{
	const IPDU_INIB			*p_ipdu_inib;
	const SIGNAL_INIB		*p_signal_inib;
	const Com_ConfigType	*p_saved_config;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	Com_CbkAck				notification;
	PduIdType				i;
	Com_SignalIdType		j;
	Std_ReturnType			send_flg;

	SchM_Enter_Com_Reentrant_0();

	/* [COM665] 初期化されていない場合は何もせずにreturn */
	if (com_state != COM_INIT) {
		goto error_exit;
	}

	for (i = 0U; i < GET_TX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_TX_IPDU_INIB(i);
		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

		/* IPDUが停止していても時間は経過する */
		mdt_countdown(p_tx_ipdu_cb);

		/* [COM777] IPDU開始判定 IPDUが停止している場合は，送信しない */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

			COM_CHECK_PARAM(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
							 (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
							(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_MainFunctionTx);

			/* 通知判定 */
			if (IPDU_IS_NOTICED(p_ipdu_inib->p_state)) {
				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
					if (p_signal_inib->ComNotification != NULL_PTR) {
						/* 排他エリア内でコールバックのポインタを取り出す */
						notification = p_signal_inib->ComNotification;
						/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
						p_saved_config = p_cur_com_config;

						/* 送信完了通知 */
						SchM_Exit_Com_Reentrant_0();
						notification();
						SchM_Enter_Com_Reentrant_0();

						/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
						COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_MainFunctionTx);
					}
				}
				IPDU_CLEAR_NOTICED(p_ipdu_inib->p_state);
				/* DM停止 */
				IPDU_CLEAR_DM(p_ipdu_inib->p_state);
			}
			/* DM制御処理 */
			else {
				if (p_tx_ipdu_cb->dm_mf_cnt > 0U) {
					p_tx_ipdu_cb->dm_mf_cnt--;
				}

				/* 送信タイムアウト発生 */
				if ((IPDU_IS_DM(p_ipdu_inib->p_state)) && (p_tx_ipdu_cb->dm_mf_cnt == 0U)) {

/* [COM670] */
#if COM_IPDU_CANCELLATION_SUPPORT == STD_ON
					/* [COM708] */
					if ((p_ipdu_inib->ComIPduCancellationSupport != FALSE) && (p_ipdu_inib->ComIPduType == COM_NORMAL)) {
						(void) PduR_ComCancelTransmit(p_ipdu_inib->PduRSourcePduHandleId);
					}
#endif /* COM_IPDU_CANCELLATION_SUPPORT == STD_ON */
					for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
						p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
						if (p_signal_inib->ComTimeoutNotification != NULL_PTR) {
							/* [COM304] */
							p_signal_inib->ComTimeoutNotification();
						}
					}
					/* [COM308] DM停止 */
					IPDU_CLEAR_DM(p_ipdu_inib->p_state);
					/* [COM392] 送信をしない */
					IPDU_CLEAR_UPDATED(p_ipdu_inib->p_state);
					/* キューイングを0で初期化する */
					p_tx_ipdu_cb->repeat_cnt = 0U;

#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
					/* [COM775] 保留された送信要求を無効にする */
					IPDU_CLEAR_RETRITED(p_ipdu_inib->p_state);
#endif
				}
			}

			/* [COM305] COM_DIRECT */
			if (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_DIRECT) {
				send_flg = direct_send(p_ipdu_inib, p_tx_ipdu_cb);
			}
			/* COM_PERIODIC */
			else if (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_PERIODIC) {
				send_flg = periodic_send(p_ipdu_inib, p_tx_ipdu_cb, E_NOT_SEND);
			}
			/* [COM305] COM_MIXED */
			else if (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_MIXED) {
				send_flg = direct_send(p_ipdu_inib, p_tx_ipdu_cb);
				send_flg = periodic_send(p_ipdu_inib, p_tx_ipdu_cb, send_flg);
			}
			/* [COM135] COM_NONE */
			else {
				/* 何もしない */
				send_flg = E_NOT_SEND;
			}

			/* Com_TriggerIPDUSendがコールされた場合 */
			if (IPDU_IS_TRIGGERED(p_ipdu_inib->p_state)) {
				send_flg = trigger_send(p_ipdu_inib, send_flg);
			}

			/* 送信成功の場合 */
			if (send_flg == E_OK) {
				/* キューイングする(上限0xFF) */
				if (p_tx_ipdu_cb->queuing_cnt != COM_INVALID_UINT8) {
					p_tx_ipdu_cb->queuing_cnt++;
				}

				/* [COM062] アップデートビットクリア */
				if (p_ipdu_inib->p_tx_ipdu_inib->ComTxIPduClearUpdateBit == COM_TRANSMIT) {
					for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
						p_signal_inib = GET_SIGNAL_INIB(p_ipdu_inib->p_signalid_list[j]);
						clear_updatebit(p_signal_inib);
					}
				}
			}
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}

/*
 *  シグナルバッファへのシグナルデータ格納(送信時)
 */
LOCAL_INLINE void
set_signal_for_send(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	uint16 i;

	/* シグナルバッファが不要なシグナルには格納しない */
	if (p_signal_inib->p_signal_buffer != NULL_PTR) {
		/* [COM353]送信側では符号拡張しない */
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			*((boolean *) p_signal_inib->p_signal_buffer) = *((const boolean *) p_data);
			break;
		case COM_SINT8:
			*((sint8 *) p_signal_inib->p_signal_buffer) = *((const sint8 *) p_data);
			break;
		case COM_SINT16:
			*((sint16 *) p_signal_inib->p_signal_buffer) = *((const sint16 *) p_data);
			break;
		case COM_SINT32:
			*((sint32 *) p_signal_inib->p_signal_buffer) = *((const sint32 *) p_data);
			break;
		case COM_UINT8:
			*((uint8 *) p_signal_inib->p_signal_buffer) = *((const uint8 *) p_data);
			break;
		case COM_UINT16:
			*((uint16 *) p_signal_inib->p_signal_buffer) = *((const uint16 *) p_data);
			break;
		case COM_UINT32:
			*((uint32 *) p_signal_inib->p_signal_buffer) = *((const uint32 *) p_data);
			break;
		case COM_UINT8_N:
			for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
				((uint8 *) p_signal_inib->p_signal_buffer)[i] = ((const uint8 *) p_data)[i];
			}
			break;
		case COM_FLOAT32:
			*((float32 *) p_signal_inib->p_signal_buffer) = *((const float32 *) p_data);
			break;
		case COM_FLOAT64:
			*((float64 *) p_signal_inib->p_signal_buffer) = *((const float64 *) p_data);
			break;
		default:
			/*
			 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
			 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_set_signal_for_send);
			break;
		}
	}

  error_exit:
	return;
}

/*
 *  シグナルバッファへのシグナルデータ格納(受信時)
 */
LOCAL_INLINE void
set_signal_for_receive(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	uint16 i;

	/* 受信側のシグナルバッファは必ず存在する */
	COM_CHECK_PARAM(p_signal_inib->p_signal_buffer != NULL_PTR, COMServiceId_set_signal_for_receive);

	switch (p_signal_inib->ComSignalType) {
	case COM_BOOLEAN:
		*((boolean *) p_signal_inib->p_signal_buffer) = *((const boolean *) p_data);
		break;
	case COM_SINT8:
		*((sint8 *) p_signal_inib->p_signal_buffer) = *((const sint8 *) p_data);
		break;
	case COM_SINT16:
		*((sint16 *) p_signal_inib->p_signal_buffer) = *((const sint16 *) p_data);
		break;
	case COM_SINT32:
		*((sint32 *) p_signal_inib->p_signal_buffer) = *((const sint32 *) p_data);
		break;
	case COM_UINT8:
		*((uint8 *) p_signal_inib->p_signal_buffer) = *((const uint8 *) p_data);
		break;
	case COM_UINT16:
		*((uint16 *) p_signal_inib->p_signal_buffer) = *((const uint16 *) p_data);
		break;
	case COM_UINT32:
		*((uint32 *) p_signal_inib->p_signal_buffer) = *((const uint32 *) p_data);
		break;
	case COM_UINT8_N:
		for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
			((uint8 *) p_signal_inib->p_signal_buffer)[i] = ((const uint8 *) p_data)[i];
		}
		break;
	case COM_FLOAT32:
		*((float32 *) p_signal_inib->p_signal_buffer) = *((const float32 *) p_data);
		break;
	case COM_FLOAT64:
		*((float64 *) p_signal_inib->p_signal_buffer) = *((const float64 *) p_data);
		break;
	default:
		/*
		 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
		 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_set_signal_for_receive);
		break;
	}

  error_exit:
	return;
}

/*
 *  シグナルデータを前回値と比較
 */
LOCAL_INLINE boolean
changed_signal(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	boolean	ret = FALSE;
	uint16	i;

	/* シグナルバッファが不要な場合は比較しない */
	if (p_signal_inib->p_signal_buffer != NULL_PTR) {
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			if (*((boolean *) p_signal_inib->p_signal_buffer) != *((const boolean *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_SINT8:
			if (*((sint8 *) p_signal_inib->p_signal_buffer) != *((const sint8 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_SINT16:
			if (*((sint16 *) p_signal_inib->p_signal_buffer) != *((const sint16 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_SINT32:
			if (*((sint32 *) p_signal_inib->p_signal_buffer) != *((const sint32 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_UINT8:
			if (*((uint8 *) p_signal_inib->p_signal_buffer) != *((const uint8 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_UINT16:
			if (*((uint16 *) p_signal_inib->p_signal_buffer) != *((const uint16 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_UINT32:
			if (*((uint32 *) p_signal_inib->p_signal_buffer) != *((const uint32 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_UINT8_N:
			for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
				if ((((uint8 *) p_signal_inib->p_signal_buffer)[i]) != (((const uint8 *) p_data)[i])) {
					ret = TRUE;
					break;
				}
			}
			break;
		case COM_FLOAT32:
			if (*((float32 *) p_signal_inib->p_signal_buffer) != *((const float32 *) p_data)) {
				ret = TRUE;
			}
			break;
		case COM_FLOAT64:
			if (*((float64 *) p_signal_inib->p_signal_buffer) != *((const float64 *) p_data)) {
				ret = TRUE;
			}
			break;
		default:
			/*
			 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
			 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_changed_signal);
			break;
		}
	}
	else {
		ret = TRUE;
	}

  error_exit:
	return(ret);
}

/*
 *  シグナルバッファからのシグナルデータ取り出し
 */
LOCAL_INLINE void
get_signal(const SIGNAL_INIB *p_signal_inib, void *p_data)
{
	uint16 i;

	/* シグナルデータの取り出しは受信時のみであるので必ずバッファは存在する */
	COM_CHECK_PARAM(p_signal_inib->p_signal_buffer != NULL_PTR, COMServiceId_get_signal);

	switch (p_signal_inib->ComSignalType) {
	case COM_BOOLEAN:
		*((boolean *) p_data) = *((boolean *) p_signal_inib->p_signal_buffer);
		break;
	case COM_SINT8:
		*((sint8 *) p_data) = *((sint8 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_SINT16:
		*((sint16 *) p_data) = *((sint16 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_SINT32:
		*((sint32 *) p_data) = *((sint32 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_UINT8:
		*((uint8 *) p_data) = *((uint8 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_UINT16:
		*((uint16 *) p_data) = *((uint16 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_UINT32:
		*((uint32 *) p_data) = *((uint32 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_UINT8_N:
		for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
			((uint8 *) p_data)[i] = ((uint8 *) p_signal_inib->p_signal_buffer)[i];
		}
		break;
	case COM_FLOAT32:
		*((float32 *) p_data) = *((float32 *) p_signal_inib->p_signal_buffer);
		break;
	case COM_FLOAT64:
		*((float64 *) p_data) = *((float64 *) p_signal_inib->p_signal_buffer);
		break;
	default:
		/*
		 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
		 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_get_signal);
		break;
	}

  error_exit:
	return;
}

/*
 * フィルタバッファシグナルデータ格納(送信)
 */
LOCAL_INLINE void
set_filter_buffer(const SIGNAL_INIB	*p_signal_inib, const void *p_data)
{
	const void *p_filter_inib;

	/* COM_MASKED_NEW_DIFFERS_MASKED_OLDしか前回値を使用しない */
	if (p_signal_inib->ComFilterAlgorithm == COM_MASKED_NEW_DIFFERS_MASKED_OLD) {
		p_filter_inib = p_signal_inib->p_filter_inib;
		COM_CHECK_PARAM(p_filter_inib != NULL_PTR, COMServiceId_set_filter_buffer);
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			COM_CHECK_PARAM(((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((boolean *) ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const boolean *) p_data);
			break;
		case COM_SINT8:
			COM_CHECK_PARAM(((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((sint8 *) ((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const sint8 *) p_data);
			break;
		case COM_SINT16:
			COM_CHECK_PARAM(((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((sint16 *) ((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const sint16 *) p_data);
			break;
		case COM_SINT32:
			COM_CHECK_PARAM(((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((sint32 *) ((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const sint32 *) p_data);
			break;
		case COM_UINT8:
			COM_CHECK_PARAM(((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((uint8 *) ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const uint8 *) p_data);
			break;
		case COM_UINT16:
			COM_CHECK_PARAM(((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((uint16 *) ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const uint16 *) p_data);
			break;
		case COM_UINT32:
			COM_CHECK_PARAM(((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer != NULL_PTR, COMServiceId_set_filter_buffer);
			*((uint32 *) ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer) = *((const uint32 *) p_data);
			break;
		default:
			/*
			 *  本関数の引数にCOM_UINT8_N，COM_FLOAT32，COM_FLOAT64が指定されることはない
			 *  ・[COM380] COM_UINT8_Nのシグナルがフィルタを持つ場合，ComFilterAlgorithmはCOM_NEVERまたはCOM_ALWAYSである
			 *  ・[COM319] COM_FLOAT32，COM_FLOAT64のシグナルの場合，フィルタを持たない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_set_filter_buffer);
			break;
		}
	}

  error_exit:
	return;
}

/*
 *  各データ型をuint32へコピー
 */
LOCAL_INLINE uint32
copy_signal_to_uint32(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	uint32 signal_data;

	switch (p_signal_inib->ComSignalType) {
	case COM_BOOLEAN:
		signal_data = (uint32) (*((const boolean *) p_data));
		break;
	case COM_SINT8:
		signal_data = (uint32) ((sint32) (*((const sint8 *) p_data)));
		break;
	case COM_SINT16:
		signal_data = (uint32) ((sint32) (*((const sint16 *) p_data)));
		break;
	case COM_SINT32:
		signal_data = *((const uint32 *) p_data);
		break;
	case COM_UINT8:
		signal_data = (uint32) (*((const uint8 *) p_data));
		break;
	case COM_UINT16:
		signal_data = (uint32) (*((const uint16 *) p_data));
		break;
	case COM_UINT32:
		signal_data = *((const uint32 *) p_data);
		break;
	case COM_FLOAT32:
		signal_data = *((const uint32 *) p_data);
		break;
	default:
		/* uninitialized警告抑止 */
		signal_data = 0U;
		/*
		 *  本関数の引数にCOM_FLOAT64が指定されることはない
		 *  ・packing関数では，ifでCOM_FLOAT64を分岐している
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_copy_signal_to_uint32);
		break;
	}

  error_exit:
	return(signal_data);
}

/*
 *  各データ型をsint32へキャストする
 */
LOCAL_INLINE sint32
cast_signal_to_sint32(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	sint32 signal_data;

	switch (p_signal_inib->ComSignalType) {
	case COM_SINT8:
		signal_data = (sint32) (*((const sint8 *) p_data));
		break;
	case COM_SINT16:
		signal_data = (sint32) (*((const sint16 *) p_data));
		break;
	case COM_SINT32:
		signal_data = (*((const sint32 *) p_data));
		break;
	default:
		/* uninitialized警告抑止 */
		signal_data = 0;
		/*
		 *  本関数の引数にCOM_BOOLEAN，COM_UINT8，COM_UINT16，COM_UINT32，COM_FLOAT32，COM_FLOAT64が指定されることはない
		 *  ・[COM319] filtering関数では，float型を使用しない
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_cast_signal_to_sint32);
		break;
	}

  error_exit:
	return(signal_data);
}

/*
 * 無効値に対する処理
 */
LOCAL_INLINE boolean
invalid_action(const SIGNAL_INIB *p_signal_inib, void *p_data)
{
	const Com_ConfigType	*p_saved_config;
	Com_CbkInv				notification;
	boolean					is_invalid;
	boolean					is_notified = TRUE;
	uint16					i;

	COM_CHECK_PARAM((p_signal_inib->ComDataInvalidAction == COM_NOTIFY) ||
					(p_signal_inib->ComDataInvalidAction == COM_REPLACE) ||
					(p_signal_inib->ComDataInvalidAction == COM_INVALID_UINT8), COMServiceId_invalid_action);

	if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
		is_invalid = TRUE;
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			if (*((const boolean *) p_signal_inib->ComSignalDataInvalidValue) != *((boolean *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_SINT8:
			if (*((const sint8 *) p_signal_inib->ComSignalDataInvalidValue) != *((sint8 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_SINT16:
			if (*((const sint16 *) p_signal_inib->ComSignalDataInvalidValue) != *((sint16 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_SINT32:
			if (*((const sint32 *) p_signal_inib->ComSignalDataInvalidValue) != *((sint32 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_UINT8:
			if (*((const uint8 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint8 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_UINT16:
			if (*((const uint16 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint16 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_UINT32:
			if (*((const uint32 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint32 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_UINT8_N:
			for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
				if ((((const uint8 *) p_signal_inib->ComSignalDataInvalidValue)[i]) != (((uint8 *) p_data)[i])) {
					is_invalid = FALSE;
					break;
				}
			}
			break;
		case COM_FLOAT32:
			if (*((const float32 *) p_signal_inib->ComSignalDataInvalidValue) != *((float32 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		case COM_FLOAT64:
			if (*((const float64 *) p_signal_inib->ComSignalDataInvalidValue) != *((float64 *) p_data)) {
				is_invalid = FALSE;
			}
			break;
		default:
			/*
			 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
			 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_invalid_action);
			break;
		}
	}
	else {
		/* NULL_PTRの場合，無効値ではないものとして扱う */
		is_invalid = FALSE;
	}

	if (is_invalid != FALSE) {
		if (p_signal_inib->ComDataInvalidAction == COM_NOTIFY) {
			/* [COM680][COM717] ComInvalidNotificationにてRTEへ通知し，フィルタリング，シグナル通知，シグナルバッファへの格納は実施しない */
			if (p_signal_inib->ComInvalidNotification != NULL_PTR) {
				/* 排他エリア内でコールバックのポインタを取り出す */
				notification = p_signal_inib->ComInvalidNotification;
				/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
				p_saved_config = p_cur_com_config;

				/* 送信完了通知 */
				SchM_Exit_Com_Reentrant_0();
				notification();
				SchM_Enter_Com_Reentrant_0();

				/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
				COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_invalid_action);
			}
			is_notified = FALSE;
		}
		else if (p_signal_inib->ComDataInvalidAction == COM_REPLACE) {
			/* [COM681] COM_REPLACEの場合，ComSignalInitValueでシグナルを更新する */
			switch (p_signal_inib->ComSignalType) {
			case COM_BOOLEAN:
				*((boolean *) p_data) = *((const boolean *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_SINT8:
				*((sint8 *) p_data) = *((const sint8 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_SINT16:
				*((sint16 *) p_data) = *((const sint16 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_SINT32:
				*((sint32 *) p_data) = *((const sint32 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_UINT8:
				*((uint8 *) p_data) = *((const uint8 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_UINT16:
				*((uint16 *) p_data) = *((const uint16 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_UINT32:
				*((uint32 *) p_data) = *((const uint32 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_UINT8_N:
				for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
					((uint8 *) p_data)[i] = ((const uint8 *) p_signal_inib->ComSignalInitValue)[i];
				}
				break;
			case COM_FLOAT32:
				*((float32 *) p_data) = *((const float32 *) p_signal_inib->ComSignalInitValue);
				break;
			case COM_FLOAT64:
				*((float64 *) p_data) = *((const float64 *) p_signal_inib->ComSignalInitValue);
				break;
			default:
				/*
				 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
				 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
				 */
				COM_CHECK_PARAM(FALSE, COMServiceId_invalid_action);
				break;
			}
		}
		else {
			/*
			 *  無効値である(p_signal_inib->ComDataInvalidAction == COM_INVALID_UINT8)
			 *  [COM736] ComDataInvalidActionが設定されていなければ，有効な値が受信されているものとみなす
			 */
		}
	}

  error_exit:
	return(is_notified);
}

/*
 *  IPDUの初期化
 */
static void
ipdu_initialize(const IPDU_INIB *p_ipdu_inib)
{
	Com_SignalIdType				i;
	const TX_IPDU_INIB				*p_tx_ipdu_inib;
	const SIGNAL_INIB				*p_signal_inib;
	const FILTER_ONE_EVERY_N_INIB	*p_filter_one_every_n_inib;
	TX_IPDU_CB						*p_tx_ipdu_cb;
	TX_SIGNAL_CB					*p_tx_signal_cb;
	RX_SIGNAL_CB					*p_rx_signal_cb;

	if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
		for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
			p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);

			/* [COM604] IPDUバッファにComSignalInitValueを設定する */
			packing(p_signal_inib, p_signal_inib->ComSignalInitValue);
			/* [COM228] シグナルバッファにComSignalInitValueを格納する */
			set_signal_for_send(p_signal_inib, p_signal_inib->ComSignalInitValue);
			/* [COM603] フィルタバッファにComSignalInitValueを格納する */
			set_filter_buffer(p_signal_inib, p_signal_inib->ComSignalInitValue);

			p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
			if ((p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) && (p_tx_signal_cb != NULL_PTR)) {
				if (p_signal_inib->ComFilterAlgorithm == COM_ONE_EVERY_N) {
					p_filter_one_every_n_inib = (const FILTER_ONE_EVERY_N_INIB *) p_signal_inib->p_filter_inib;
					COM_CHECK_PARAM((p_filter_one_every_n_inib != NULL_PTR) &&
									(p_filter_one_every_n_inib->p_occur != NULL_PTR), COMServiceId_ipdu_initialize);
					/* [COM231] OCCURRENCEを0に設定する */
					*(p_filter_one_every_n_inib->p_occur) = 0U;
				}
				/* TMC判定 */
				p_tx_signal_cb->tmc = filtering(p_signal_inib, p_signal_inib->ComSignalInitValue);
			}

			/* アップデートビットクリア */
			clear_updatebit(p_signal_inib);
		}

		p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

		/* TMSを決定し，送信モードを決定する */
		if (check_tms(p_ipdu_inib) != FALSE) {
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
		}
		else {
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
		}

		/* [COM222] 送信モードがCOM_PERIODICとCOM_MIXEDのIPDUの周期のMF回数カウンタをComTxModeTimeOffsetで初期化 */
		if ((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_PERIODIC) ||
			(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_MIXED)) {
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
		}
	}
	else {
		for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
			p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);

			/* シグナルバッファにComSignalInitValueを格納する */
			set_signal_for_receive(p_signal_inib, p_signal_inib->ComSignalInitValue);

			if (p_signal_inib->ComFilterAlgorithm == COM_ONE_EVERY_N) {
				p_filter_one_every_n_inib = (const FILTER_ONE_EVERY_N_INIB *) p_signal_inib->p_filter_inib;
				COM_CHECK_PARAM((p_filter_one_every_n_inib != NULL_PTR) &&
								(p_filter_one_every_n_inib->p_occur != NULL_PTR), COMServiceId_ipdu_initialize);
				/* ComFilterOffsetが0の場合を考慮し，OCCURRENCEを0で初期化する */
				*(p_filter_one_every_n_inib->p_occur) = 0U;
			}

			/* DM停止 */
			p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
			if (p_rx_signal_cb != NULL_PTR) {
				p_rx_signal_cb->dm_state = COM_STOP;
			}

			/* [COM603] フィルタバッファにComSignalInitValueを格納する */
			set_filter_buffer(p_signal_inib, p_signal_inib->ComSignalInitValue);
		}
	}

	/* IPDU_STARTED_BIT以外をCLEARする */
	IPDU_CLEAR_EXCEPT_STARTED(p_ipdu_inib->p_state);

  error_exit:
	return;
}

/*
 *  シグナルパッキング
 *  [COM007][COM580] エンディアン変換
 */
LOCAL_INLINE void
packing(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	const IPDU_INIB	*p_ipdu_inib;
	const uint8		*p_signal_data;     /* シグナルデータのポインタ */
	PduLengthType	byte_index;         /* ComBitPositionが所属するIPDUのByte位置 */
	uint8			pos_lsb;            /* LSBのBit位置 */
	uint16			i;
	uint32			signal_data;        /* シグナルデータ */
	uint32			low_signal_data;    /* COM_FLOAT64の場合，シグナルデータ下位32bit */
	uint32			high_signal_data;   /* COM_FLOAT64の場合，シグナルデータ上位32bit */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	byte_index = p_signal_inib->ComBitPosition / 8U;
	pos_lsb = (uint8) (p_signal_inib->ComBitPosition % 8U);

	COM_CHECK_PARAM((p_signal_inib->ComSignalEndianness >= COM_BIG_ENDIAN) &&
					(p_signal_inib->ComSignalEndianness <= COM_OPAQUE), COMServiceId_packing);
	COM_CHECK_PARAM((p_signal_inib->ComSignalType >= COM_BOOLEAN) &&
					(p_signal_inib->ComSignalType <= COM_FLOAT64), COMServiceId_packing);

	if (p_signal_inib->ComSignalEndianness == COM_OPAQUE) {
		/* COM_OPAQUEの場合，ComBitPositionが8の倍数である必要がる */
		COM_CHECK_PARAM(pos_lsb == 0U, COMServiceId_packing);

		p_signal_data = (const uint8 *) p_data;

		/* [COM443][COM472] COM_OPAQUEはCOM_UINT8_Nのみ */
		for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
			/* IPDUバッファにシグナルデータを格納 */
			(p_ipdu_inib->p_ipdu_buffer)[byte_index] = p_signal_data[i];

			/* [COM259_Conf] COM_OPAQUEはCOM_LITTLE_ENDIANとする */
			byte_index++;
		}
	}
	else {
		if (p_signal_inib->ComSignalType == COM_FLOAT64) {
			/* 下位32bitを取りだす */
			low_signal_data = (uint32) ((*(const uint64 *) p_data) & ((uint32) 0xFFFFFFFF));

			/* 上位32bitを取りだす */
			high_signal_data = (uint32) (((*(const uint64 *) p_data) >> 32U) & ((uint32) 0xFFFFFFFF));

			if (p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) {
				pack_little_endian(p_ipdu_inib->p_ipdu_buffer, byte_index, pos_lsb, 32U, low_signal_data);
				pack_little_endian(p_ipdu_inib->p_ipdu_buffer, byte_index + 4U, pos_lsb, 32U, high_signal_data);
			}
			else {
				pack_big_endian(p_ipdu_inib->p_ipdu_buffer, byte_index, pos_lsb, 32U, low_signal_data);
				pack_big_endian(p_ipdu_inib->p_ipdu_buffer, byte_index - 4U, pos_lsb, 32U, high_signal_data);
			}
		}
		else {
			/* 受信したデータを対象データ型へ変換 */
			signal_data = copy_signal_to_uint32(p_signal_inib, p_data);

			if (p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) {
				pack_little_endian(p_ipdu_inib->p_ipdu_buffer, byte_index, pos_lsb, p_signal_inib->ComBitSize, signal_data);
			}
			else {
				pack_big_endian(p_ipdu_inib->p_ipdu_buffer, byte_index, pos_lsb, p_signal_inib->ComBitSize, signal_data);
			}
		}
	}

  error_exit:
	return;
}

LOCAL_INLINE void
pack_little_endian(uint8 p_buffer[], PduLengthType byte_index, uint8 pos_lsb, uint8 bitsize, uint32 signal_data)
{
	uint8	mask;
	uint8	pos_msb;    /* MSBのBit位置 */

	/* 格納範囲が1Byte以内である場合 */
	if ((pos_lsb + bitsize) <= 8U) {
		pos_msb = (pos_lsb + bitsize) - 1U;
		mask = ((uint8) (0xFFU << pos_lsb)) & (0xFFU >> ((uint8) (7U - pos_msb)));

		/* IPDUバッファにシグナルデータを格納 */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
	}
	else {
		mask = (uint8) (0xFFU << pos_lsb);

		/* IPDUバッファにシグナルデータを格納 */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
		signal_data >>= 8U - pos_lsb;
		bitsize -= 8U - pos_lsb;

		byte_index++;

		/* シグナルの残りサイズが1Byte以上である場合 */
		while (bitsize >= 8U) {
			/* IPDUバッファにシグナルデータを格納 */
			p_buffer[byte_index] = (uint8) signal_data;
			signal_data >>= 8U;
			bitsize -= 8U;

			byte_index++;
		}

		/* シグナルの残りサイズがある場合 */
		if (bitsize != 0U) {
			mask = (uint8) (0xFFU >> (8U - bitsize));
			/* IPDUバッファにシグナルデータを格納 */
			p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) (signal_data & ((uint32) mask)));
		}
	}

	return;
}

LOCAL_INLINE void
pack_big_endian(uint8 p_buffer[], PduLengthType byte_index, uint8 pos_lsb, uint8 bitsize, uint32 signal_data)
{
	uint8	mask;
	uint8	pos_msb;    /* MSBのBit位置 */

	/* 格納範囲が1Byte以内である場合 */
	if ((pos_lsb + bitsize) <= 8U) {
		pos_msb = (pos_lsb + bitsize) - 1U;
		mask = ((uint8) (0xFFU << pos_lsb)) & (0xFFU >> ((uint8) (7U - pos_msb)));

		/* IPDUバッファにシグナルデータを格納 */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
	}
	else {
		mask = (uint8) (0xFFU << pos_lsb);

		/* IPDUバッファにシグナルデータを格納 */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
		signal_data >>= 8U - pos_lsb;
		bitsize -= 8U - pos_lsb;

		byte_index--;

		/* シグナルの残りサイズが1Byte以上である場合 */
		while (bitsize >= 8U) {
			/* IPDUバッファにシグナルデータを格納 */
			p_buffer[byte_index] = (uint8) signal_data;
			signal_data >>= 8U;
			bitsize -= 8U;

			byte_index--;
		}

		/* シグナルの残りサイズがある場合 */
		if (bitsize != 0U) {
			mask = (uint8) (0xFFU >> (8U - bitsize));
			/* IPDUバッファにシグナルデータを格納 */
			p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) (signal_data & ((uint32) mask)));
		}
	}

	return;
}

/*
 *  受信処理
 */
LOCAL_INLINE void
ipdu_receive(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB		*p_signal_inib;
	const Com_ConfigType	*p_saved_config;
	void					*p_unpack_data;
	uint64					temp_data;      /* 最大サイズはCOM_FLOAT64 */
	Com_CbkAck				notification;
	uint16					i;

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);

		/* [COM324] アップデートビットが更新されている場合，フィルタリング，通知，アンパッキング等の処理を実施する */
		if (check_updatebit(p_signal_inib) != FALSE) {

			if (p_signal_inib->ComSignalEndianness == COM_OPAQUE) {
				/* COM_UINT8_NはバイトアラインされているのでIPDUバッファをそのまま使用する */
				p_unpack_data = (void *) &((p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComBitPosition / 8U]);
			}
			else {
				/* COM_UINT8_N以外は一時バッファにアンパッキング */
				unpacking(p_signal_inib, &temp_data);
				p_unpack_data = (void *) &temp_data;
			}

			/*
			 *  [COM396] 受信したシグナルに対して以下の順で処理する
			 *           1) 無効値処理
			 *           2) フィルタリング
			 *           3) 通知
			 */
			/* 無効値処理([COM680][COM717]RTEへ通知する場合は後続の処理をしない) */
			if (invalid_action(p_signal_inib, p_unpack_data) != FALSE) {
				/* [COM273][COM695] フィルタリング結果がfalseの場合，シグナルを破棄し，そのシグナルに対する処理を行わない */
				if ((p_signal_inib->ComFilterAlgorithm == COM_INVALID_UINT8) || (filtering(p_signal_inib, p_unpack_data) != FALSE)) {
					/* シグナルバッファにアンパックしたデータを格納 */
					set_signal_for_receive(p_signal_inib, p_unpack_data);

					/* [COM574] 完全に受信したシグナルに対してComNotificationに設定した関数を呼ぶ */
					if (p_signal_inib->ComNotification != NULL_PTR) {
						/* 排他エリア内でコールバックのポインタを取り出す */
						notification = p_signal_inib->ComNotification;
						/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
						p_saved_config = p_cur_com_config;

						SchM_Exit_Com_Reentrant_0();
						notification();
						SchM_Enter_Com_Reentrant_0();

						/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
						COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_ipdu_receive);
					}
				}
			}
		}
	}

  error_exit:
	return;
}

/*
 *  シグナルアンパッキング
 *  [COM007] エンディアン変換，符号拡張
 */
LOCAL_INLINE void
unpacking(const SIGNAL_INIB *p_signal_inib, void *p_data)
{
	const IPDU_INIB	*p_ipdu_inib;
	PduLengthType	byte_index;             /* ComBitPositionが所属するIPDUのByte位置 */
	uint8			pos_lsb;                /* LSBのBit位置 */
	uint8			bitsize;
	uint8			left_size;              /* アンパックするシグナルの残りサイズ */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	pos_lsb = (uint8) (p_signal_inib->ComBitPosition % 8U);
	byte_index = p_signal_inib->ComBitPosition / 8U;

	COM_CHECK_PARAM((p_signal_inib->ComSignalEndianness != COM_OPAQUE) &&
					((p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) ||
					 (p_signal_inib->ComSignalEndianness == COM_BIG_ENDIAN)), COMServiceId_unpacking);

	/* アンパッキング */
	/* [COM352] フィルタリングと通知検出を行う前に符号拡張とエンディアン変換を行う */
	bitsize = p_signal_inib->ComBitSize;

	/* 格納範囲が1Byte以内である場合 */
	if ((pos_lsb + bitsize) <= 8U) {
		/* シグナルデータにIPDUバッファのデータを格納 */
		*(uint64 *) p_data = (uint64) (((p_ipdu_inib->p_ipdu_buffer)[byte_index] >> pos_lsb) & (0xFFU >> (8U - bitsize)));
	}
	else {
		/* シグナルデータにIPDUバッファのデータを格納 */
		*(uint64 *) p_data = (uint64) ((p_ipdu_inib->p_ipdu_buffer)[byte_index] >> pos_lsb);

		/* シグナルの残りサイズを算出 */
		left_size = bitsize - (8U - pos_lsb);

		if (p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) {
			byte_index++;
		}
		else {
			byte_index--;
		}

		/* シグナルの残りサイズが1Byte以上である場合 */
		while (left_size >= 8U) {
			/* シグナルデータにIPDUバッファのデータを，ここまでに格納したビット分左シフトして格納 */
			*(uint64 *) p_data += (((uint64) ((p_ipdu_inib->p_ipdu_buffer)[byte_index])) << (bitsize - left_size));
			left_size -= 8U;

			if (p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) {
				byte_index++;
			}
			else {
				byte_index--;
			}
		}

		/* シグナルの残りサイズがある場合 */
		if (left_size != 0U) {
			/* シグナルデータにIPDUバッファのデータを，ここまでに格納したビット分左シフトして格納 */
			*(uint64 *) p_data += ((uint64) (((p_ipdu_inib->p_ipdu_buffer)[byte_index]) & (0xFFU >> (8U - left_size))) << (bitsize - left_size));
		}
	}

	/* [COM008] 受信側では符号拡張する */
	switch (p_signal_inib->ComSignalType) {
	case COM_SINT8:
		if ((*((uint8 *) p_data) & ((uint8) (0x01U << (p_signal_inib->ComBitSize - 1U)))) != 0U) {
			*((uint8 *) p_data) |= (uint8) (0xFFU << p_signal_inib->ComBitSize);
		}
		break;
	case COM_SINT16:
		if ((*((uint16 *) p_data) & (((uint16) 0x0001) << (p_signal_inib->ComBitSize - 1U))) != 0U) {
			*((uint16 *) p_data) |= (0xFFFFU << p_signal_inib->ComBitSize);
		}
		break;
	case COM_SINT32:
		if ((*((uint32 *) p_data) & (((uint32) 0x00000001) << (p_signal_inib->ComBitSize - 1U))) != 0U) {
			*((uint32 *) p_data) |= (((uint32) 0xFFFFFFFF) << p_signal_inib->ComBitSize);
		}
		break;
	default:
		/*
		 *  アンパッキング処理はCOM_UINT型を用いて行っているため，COM_UINT型の符号拡張は不要
		 *  [COM579] COM_FLOAT型は符号拡張は行わない
		 */
		break;
	}

  error_exit:
	return;
}

/*
 *  アップデートビット設定
 */
LOCAL_INLINE void
set_updatebit(const SIGNAL_INIB *p_signal_inib)
{
	const IPDU_INIB	*p_ipdu_inib;

	if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
		p_ipdu_inib = p_signal_inib->p_ipdu_inib;
		/* [COM059] 0:更新なし，1:更新あり */
		(p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComUpdateBitPosition / 8U] |= (uint8) (1U << (p_signal_inib->ComUpdateBitPosition % 8U));
	}

	return;
}

/*
 *  アップデートビットクリア
 */
LOCAL_INLINE void
clear_updatebit(const SIGNAL_INIB *p_signal_inib)
{
	const IPDU_INIB	*p_ipdu_inib;

	if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
		p_ipdu_inib = p_signal_inib->p_ipdu_inib;
		/* [COM059] 0:更新なし，1:更新あり */
		(p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComUpdateBitPosition / 8U] &= (uint8) (~((uint8) (1U << (p_signal_inib->ComUpdateBitPosition % 8U))));
	}

	return;
}

/*
 *  PduRへの送信
 *  [COM495] PduRへの送信は必ずmdt_sendを使用するため，TMS切替時もMDTが考慮される
 */
LOCAL_INLINE Std_ReturnType
mdt_send(const IPDU_INIB *p_ipdu_inib)
{
	const Com_ConfigType	*p_saved_config;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	uint8					*p_pdubuffer;
	Com_IpduCallout			callout;
	PduInfoType				pduinfo;
	Std_ReturnType			ret_transmit;
	boolean					ret_callout;
	PduIdType				pduid;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	/* [COM625] */
	if (p_tx_ipdu_cb->mdt_mf_cnt == 0U) {
		/* [COM346][COM719] コールアウト処理 */
		if (p_ipdu_inib->ComIPduCallout != NULL_PTR) {
			/* 排他エリア内で各情報を取り出す */
			callout = p_ipdu_inib->ComIPduCallout;
			pduid = p_ipdu_inib->PduRSourcePduHandleId;
			p_pdubuffer = p_ipdu_inib->p_ipdu_buffer;

			/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
			p_saved_config = p_cur_com_config;

			/* [COM381] Com_TriggerIPDUSend, Com_SendSignalはコールアウトから呼出し可能とする */
			SchM_Exit_Com_Reentrant_0();
			ret_callout = callout(pduid, p_pdubuffer);
			SchM_Enter_Com_Reentrant_0();

			/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
			COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_mdt_send);

			if (ret_callout == FALSE) {
				ret_transmit = E_OK;
				/* [COMa004] FALSEの場合，以降の処理を実施しない */
				goto no_error_exit;
			}
		}

		/* IPDU情報設定 */
		pduinfo.SduDataPtr = p_ipdu_inib->p_ipdu_buffer;
		pduinfo.SduLength = p_ipdu_inib->PduLength;

		/* [COM138][COM239] IPDU送信 */
		ret_transmit = PduR_ComTransmit(p_ipdu_inib->PduRSourcePduHandleId, &pduinfo);

/* [COM773][COM779] 失敗した送信要求のリトライ */
#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
		if (ret_transmit != E_NOT_OK) {
			/* IPDU送信が成功した場合のみMDTを設定する */
			mdt_set(p_ipdu_inib);
		}
#else
		/* COM_RETRY_FAILED_TRANSMIT_REQUESTSがSTD_OFFの場合は，一律MDTを設定する */
		mdt_set(p_ipdu_inib);
#endif
	}
	else {
		ret_transmit = E_NOT_OK;
	}

	/* 送信DM開始 */
	start_tx_dm(p_ipdu_inib);

  no_error_exit:
	return(ret_transmit);

  error_exit:
	ret_transmit = E_NOT_OK;
	goto no_error_exit;
}

/*
 *  MDTカウンタ操作
 */
LOCAL_INLINE void
mdt_countdown(TX_IPDU_CB *p_tx_ipdu_cb)
{
	if (p_tx_ipdu_cb->mdt_mf_cnt > 0U) {
		p_tx_ipdu_cb->mdt_mf_cnt--;
	}

	return;
}

/*
 *  MDTカウンタをセット
 */
LOCAL_INLINE void
mdt_set(const IPDU_INIB *p_ipdu_inib)
{
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

/* [COM789] 最小遅延時間モニタリングを行わない(ComTransferPropertyがWITHOUT_REPETITION以外の場合) */
#if COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION == STD_OFF
	if (IPDU_IS_WITHOUT_REPETITION(p_ipdu_inib->p_state)) {
		p_tx_ipdu_cb->mdt_mf_cnt = p_tx_ipdu_inib->ComMinimumDelayTime;
	}
	else {
		p_tx_ipdu_cb->mdt_mf_cnt = 0U;
	}
#else
	/* [COM471][COM698] MDTカウンタ設定 0の場合はMDTモニタリングしない */
	p_tx_ipdu_cb->mdt_mf_cnt = p_tx_ipdu_inib->ComMinimumDelayTime;
#endif

	return;
}

/*
 *  フィルタリング処理
 *  [COM132][COM674] 符号付きデータに対してもフィルタリングを行う
 */
static boolean
filtering(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	const void		*p_filter_inib;
	boolean			result = FALSE;
	uint32			new_uint_data;
	uint32			old_uint_data;
	sint32			new_sint_data;
	sint32			old_sint_data;

	/* [COM325] すべてのフィルタアルゴリズムをサポート */
	if (p_signal_inib->ComFilterAlgorithm == COM_ALWAYS) {
		result = TRUE;
	}
	else if (p_signal_inib->ComFilterAlgorithm == COM_NEVER) {
		result = FALSE;
	}
	else {
		COM_CHECK_PARAM((p_signal_inib->ComSignalType >= COM_BOOLEAN) &&
						(p_signal_inib->ComSignalType <= COM_SINT32) &&
						(p_signal_inib->p_filter_inib != NULL_PTR), COMServiceId_filtering);

		/*
		 *  [COM319] COM_FLOAT32，COM_FLOAT64のシグナルの場合，フィルタを持たない
		 *  [COM380] COM_UINT8_Nのシグナルがフィルタを持つ場合，ComFilterAlgorithmはCOM_NEVERまたはCOM_ALWAYSである
		 */

		p_filter_inib = p_signal_inib->p_filter_inib;
		switch (p_signal_inib->ComFilterAlgorithm) {
		case COM_MASKED_NEW_EQUALS_X:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalTypeがUINT系の場合，FILTER_UINT_MASKED_INIBにキャストする */
				if ((new_uint_data & ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) == ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalTypeがSINT系の場合，FILTER_SINT_MASKED_INIBにキャストする */
				if ((new_sint_data & ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) == ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			break;
		case COM_MASKED_NEW_DIFFERS_X:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalTypeがUINT系の場合，FILTER_UINT_MASKED_INIBにキャストする */
				if ((new_uint_data & ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) != ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalTypeがSINT系の場合，FILTER_SINT_MASKED_INIBにキャストする */
				if ((new_sint_data & ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) != ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			break;
		case COM_MASKED_NEW_DIFFERS_MASKED_OLD:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalTypeがUINT系の場合，FILTER_UINT_MASKED_OLD_INIBにキャストする */
				old_uint_data = copy_signal_to_uint32(p_signal_inib, ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer);
				/* [COM763] */
				if ((new_uint_data & ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->ComFilterMask) != (old_uint_data & ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->ComFilterMask)) {
					result = TRUE;

					/* [COM302][COM303] */
					set_filter_buffer(p_signal_inib, p_data);
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalTypeがSINT系の場合，FILTER_SINT_MASKED_OLD_INIBにキャストする */
				old_sint_data = cast_signal_to_sint32(p_signal_inib, ((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer);
				/* [COM763] */
				if ((new_sint_data & ((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->ComFilterMask) != (old_sint_data & ((const FILTER_SINT_MASKED_OLD_INIB *) p_filter_inib)->ComFilterMask)) {
					result = TRUE;

					/* [COM302][COM303] */
					set_filter_buffer(p_signal_inib, p_data);
				}
			}
			break;
		case COM_NEW_IS_WITHIN:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalTypeがUINT系の場合，FILTER_UINT_NEW_IS_INIBにキャストする */
				if ((((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin <= new_uint_data) && (new_uint_data <= ((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax)) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalTypeがSINT系の場合，FILTER_SINT_NEW_IS_INIBにキャストする */
				if ((((const FILTER_SINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin <= new_sint_data) && (new_sint_data <= ((const FILTER_SINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax)) {
					result = TRUE;
				}
			}
			break;
		case COM_NEW_IS_OUTSIDE:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalTypeがUINT系の場合，FILTER_UINT_NEW_IS_INIBにキャストする */
				if ((new_uint_data < ((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin) || (((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax < new_uint_data)) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalTypeがSINT系の場合，FILTER_SINT_NEW_IS_INIBにキャストする */
				if ((new_sint_data < ((const FILTER_SINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin) || (((const FILTER_SINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax < new_sint_data)) {
					result = TRUE;
				}
			}
			break;
		case COM_ONE_EVERY_N:
			/* [COM231] */
			if (*(((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->p_occur) == ((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->ComFilterPeriod) {
				*(((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->p_occur) = 0U;
			}
			/* COM231により，下記条件文は(occurrence % period == offset)と同等となる */
			if (*(((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->p_occur) == ((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->ComFilterOffset) {
				result = TRUE;
			}
			(*(((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->p_occur))++;
			break;
		default:
			/*
			 *  本関数の引数にCOM_MASKED_NEW_EQUALS_X，COM_MASKED_NEW_DIFFERS_X，COM_MASKED_NEW_DIFFERS_MASKED_OLD，COM_NEW_IS_WITHIN，
			 *  COM_NEW_IS_OUTSIDE，COM_ONE_EVERY_N，COM_NEVER，COM_ALWAYS，COM_INVALID_UINT8以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_filtering);
			break;
		}
	}

  error_exit:
	/* [COM694] */
	return(result);
}


/*
 *  TMS判定
 */
LOCAL_INLINE boolean
check_tms(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB	*p_signal_inib;
	Com_SignalIdType	i;
	boolean				filter = FALSE;
	boolean				tms = FALSE;

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		/* [COM676] フィルタを持つシグナルのみTMCを判定する */
		if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
			filter = TRUE;

			/* [COM678][COM679] TMCが1つでもTRUEの場合は，TMSはTRUEとする */
			if (((TX_SIGNAL_CB *) p_signal_inib->p_signal_cb)->tmc != FALSE) {
				tms = TRUE;
				break;
			}
		}
	}

	/* [COM677] フィルタを持つシグナルが存在しない場合は，TMSはTRUEとする */
	if (filter == FALSE) {
		tms = TRUE;
	}

	return(tms);
}

/*
 *  送信DM開始
 */
LOCAL_INLINE void
start_tx_dm(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB	*p_signal_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	/* シグナル値取得 ComTimeout値は同じIPDUのシグナルで変化はないので最初のシグナルの値を取得する */
	p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[0]);
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	if (!IPDU_IS_DM(p_ipdu_inib->p_state)) {
		/* [COM333] ComTimeoutが0または，省略されている場合，そのシグナルのDM監視はしない */
		if (p_signal_inib->ComTimeout != 0U) {
			/* [COM481][COM739][[COM774]] */
			IPDU_SET_DM(p_ipdu_inib->p_state);
			p_tx_ipdu_cb->dm_mf_cnt = p_signal_inib->ComTimeout;
		}
	}

	return;
}

/*
 *  受信DM開始
 */
LOCAL_INLINE void
start_rx_dm(const IPDU_INIB *p_ipdu_inib)
{
	Com_SignalIdType	i;
	const SIGNAL_INIB	*p_signal_inib;
	RX_SIGNAL_CB		*p_rx_signal_cb;
	boolean				is_dm = FALSE;

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

		/* [COM333] ComTimeoutが0または，省略されている場合，そのシグナルのDM監視はしない */
		if (p_rx_signal_cb != NULL_PTR) {
			if (p_signal_inib->ComFirstTimeout == 0U) {
				/* [COM716] ComFirstTimeoutが0または，省略されている場合，最初の受信が行われるまで，そのシグナルのDM監視はしない */
				p_rx_signal_cb->dm_state = COM_WAIT;
			}
			else {
				/* [COM224] ComFirstTimeoutを設定する */
				p_rx_signal_cb->dm_mf_cnt = p_signal_inib->ComFirstTimeout;
				p_rx_signal_cb->dm_state = COM_START;
			}

			is_dm = TRUE;
		}
	}

	if (is_dm == TRUE) {
		IPDU_SET_DM(p_ipdu_inib->p_state);
	}

	return;
}

/*
 *  受信DM停止
 */
LOCAL_INLINE void
stop_rx_dm(const IPDU_INIB *p_ipdu_inib)
{
	Com_SignalIdType	i;
	const SIGNAL_INIB	*p_signal_inib;
	RX_SIGNAL_CB		*p_rx_signal_cb;

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

		if (p_rx_signal_cb != NULL_PTR) {
			/* シグナルのDM監視を停止する */
			p_rx_signal_cb->dm_state = COM_STOP;
		}
	}

	/* DM停止 */
	IPDU_CLEAR_DM(p_ipdu_inib->p_state);

	return;
}
/*
 *  受信シグナルDM判定
 */
LOCAL_INLINE void
check_signal_dm(const SIGNAL_INIB *p_signal_inib)
{
	const Com_ConfigType	*p_saved_config;
	RX_SIGNAL_CB			*p_rx_signal_cb;
	Com_CbkTOut				notification;

	p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

	if (p_rx_signal_cb != NULL_PTR) {
		if (p_rx_signal_cb->dm_state == COM_START) {
			/* dm_mf_cntは必ず0より大きい値が設定されている */
			p_rx_signal_cb->dm_mf_cnt--;

			/* シグナルの受信DMが有効なDMカウンタを判定する */
			if (p_rx_signal_cb->dm_mf_cnt == 0U) {
				if (p_signal_inib->ComRxDataTimeoutAction == COM_REPLACE) {
					/* [COM470] シグナルの値をComSignalInitValueに置き換える */
					set_signal_for_receive(p_signal_inib, p_signal_inib->ComSignalInitValue);
				}
				/* [COM500] COM_NONEまたは省略されている場合は，何もしない */

				/* [COM744] タイムアウト通知 */
				if (p_signal_inib->ComTimeoutNotification != NULL_PTR) {
					/* 排他エリア内でコールバックのポインタを取り出す */
					notification = p_signal_inib->ComTimeoutNotification;
					/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
					p_saved_config = p_cur_com_config;

					/* 送信完了通知 */
					SchM_Exit_Com_Reentrant_0();
					notification();
					SchM_Enter_Com_Reentrant_0();

					/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
					COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_TxConfirmation);
				}
				p_rx_signal_cb->dm_mf_cnt = p_signal_inib->ComTimeout;
			}
		}
	}

  error_exit:
	return;
}

/*
 *  受信シグナルDMリセット
 */
LOCAL_INLINE void
reset_signal_dm(const SIGNAL_INIB *p_signal_inib)
{
	RX_SIGNAL_CB *p_rx_signal_cb;

	p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

	if (p_rx_signal_cb != NULL_PTR) {
		if (p_rx_signal_cb->dm_state != COM_STOP) {
			/* シグナルの受信デッドラインタイマが有効であればリセットする */
			p_rx_signal_cb->dm_mf_cnt = p_signal_inib->ComTimeout;

			if (p_rx_signal_cb->dm_state == COM_WAIT) {
				p_rx_signal_cb->dm_state = COM_START;
			}
		}
	}

	return;
}

/*
 *  アップデートビット更新チェック
 */
LOCAL_INLINE boolean
check_updatebit(const SIGNAL_INIB *p_signal_inib)
{
	const IPDU_INIB	*p_ipdu_inib;
	PduLengthType	index_update;       /* ComUpdateBitPositionが所属するIPDUのByte位置 */
	uint8			pos_update;         /* ComUpdateBitPositionのBit位置 */
	boolean			updated;

	if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
		index_update = p_signal_inib->ComUpdateBitPosition / 8U;
		pos_update = (uint8) (p_signal_inib->ComUpdateBitPosition % 8U);
		p_ipdu_inib = p_signal_inib->p_ipdu_inib;

		/* [COM067] アップデートビットに値が設定されていれば，シグナルは更新されたものとする */
		if (((p_ipdu_inib->p_ipdu_buffer)[index_update] & ((uint8) (1U << pos_update))) != 0U) {
			updated = TRUE;
		}
		else {
			updated = FALSE;
		}
	}
	else {
		/* アップデートビットを持たない場合は，更新されたものとする */
		updated = TRUE;
	}

	return(updated);
}

/*
 *  COM_DIRECT送信
 */
static Std_ReturnType
direct_send(const IPDU_INIB *p_ipdu_inib, TX_IPDU_CB *p_tx_ipdu_cb)
{
	Std_ReturnType ret;

	if (p_tx_ipdu_cb->interval_mf_cnt > 0U) {
		p_tx_ipdu_cb->interval_mf_cnt--;
	}

	/* IPDU送信リトライする場合 */
	if (IPDU_IS_DIRECT_RETRITED(p_ipdu_inib->p_state)) {
		/* [COM582][COM478] IPDU送信 */
		ret = mdt_send(p_ipdu_inib);
	}
	/* 送信する間隔のMF回数カウンタが0の場合 */
	else if (IPDU_IS_UPDATED(p_ipdu_inib->p_state) && (p_tx_ipdu_cb->interval_mf_cnt == 0U)) {
		/* [COM582][COM478] IPDU送信 */
		ret = mdt_send(p_ipdu_inib);
		/* 送信失敗の場合 */
		if (ret == E_NOT_OK) {
			IPDU_SET_DIRECT_RETRITED(p_ipdu_inib->p_state);
		}
	}
	else {
		ret = E_NOT_SEND;
	}

	/* 送信成功の場合 */
	if (ret == E_OK) {
		IPDU_CLEAR_DIRECT_RETRITED(p_ipdu_inib->p_state);
		p_tx_ipdu_cb->interval_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeRepetitionPeriod;

		/* 1回のみ送信する場合 */
		if (IPDU_IS_WITHOUT_REPETITION(p_ipdu_inib->p_state) ||
			(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions == 0U)) {
			IPDU_CLEAR_WITHOUT_REPETITION(p_ipdu_inib->p_state);
			IPDU_CLEAR_UPDATED(p_ipdu_inib->p_state);
		}
	}

	return(ret);
}

/*
 *  COM_PERIODIC送信
 */
static Std_ReturnType
periodic_send(const IPDU_INIB *p_ipdu_inib, TX_IPDU_CB *p_tx_ipdu_cb, Std_ReturnType send_flg)
{
	if (p_tx_ipdu_cb->period_mf_cnt > 0U) {
		p_tx_ipdu_cb->period_mf_cnt--;
	}

	/* IPDU送信リトライする場合 */
	if (IPDU_IS_PERIODIC_RETRITED(p_ipdu_inib->p_state)) {
		/* 未送信の場合 */
		if (send_flg == E_NOT_SEND) {
			/* [COM478] IPDU送信 */
			send_flg = mdt_send(p_ipdu_inib);
		}
		/* 送信成功の場合 */
		if (send_flg == E_OK) {
			IPDU_CLEAR_PERIODIC_RETRITED(p_ipdu_inib->p_state);
		}
	}

	/* 周期のMF回数カウンタが0の場合 */
	if (p_tx_ipdu_cb->period_mf_cnt == 0U) {
		/* [COM776] 周期時間の位相は変わらない */
		p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimePeriod;

		/* [COM494] COM_DIRECTで送信済みの場合，送信しない */
		if (send_flg == E_NOT_SEND) {
			/* [COM388] IPDU送信 */
			send_flg = mdt_send(p_ipdu_inib);
			/* 送信失敗の場合 */
			if (send_flg == E_NOT_OK) {
				IPDU_SET_PERIODIC_RETRITED(p_ipdu_inib->p_state);
			}
		}
	}

	return(send_flg);
}

/*
 *  Com_TriggerIPDUSendがコールされた場合
 */
static Std_ReturnType
trigger_send(const IPDU_INIB *p_ipdu_inib, Std_ReturnType send_flg)
{
	/* 未送信の場合 */
	if (send_flg == E_NOT_SEND) {
		/* [COM388] IPDU送信(MDTのみを考慮) */
		send_flg = mdt_send(p_ipdu_inib);
	}

	/* 送信成功の場合 */
	if (send_flg == E_OK) {
		IPDU_CLEAR_TRIGGERED(p_ipdu_inib->p_state);
	}

	return(send_flg);
}


/*
 *  以下，未サポート機能
 */

/* <COM627><COM628><COM629><COM630> */
uint8
Com_SendDynSignal(Com_SignalIdType SignalId, const void *SignalDataPtr, uint16 Length)
{
	return(0U);
}
/* <COM690><COM711><COM712><COM724> */
uint8
Com_ReceiveDynSignal(Com_SignalIdType SignalId, void *SignalDataPtr, uint16 *Length)
{
	return(0U);
}
/* <COM199><COM632><COM633><COM634> */
void
Com_UpdateShadowSignal(Com_SignalIdType SignalId, const void *SignalDataPtr)
{
}
/* <COM200><COM635><COM636><COM637> */
uint8
Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
	return(0U);
}
/* <COM201><COM638><COM639><COM461> */
uint8
Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
	return(0U);
}
/* <COM202><COM640><COM641> */
void
Com_ReceiveShadowSignal(Com_SignalIdType SignalId, void *SignalDataPtr)
{
}
/* <COM288><COM644> */
void
Com_InvalidateShadowSignal(Com_SignalIdType SignalId)
{
}
/* <COM557><COM645> */
uint8
Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
	return(0U);
}
/* <COM400><COM666><COM667><COM668> */
void
Com_MainFunctionRouteSignals(void)
{
}
/* <COM001><COM647><COM475><COM260><COM648><COM395><COM578><COM766> */
Std_ReturnType
Com_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr)
{
	return(0U);
}
/* <COM650><COM651> */
void
Com_TpRxIndication(PduIdType PduId, NotifResultType Result)
{
}
/* <COM725> */
void
Com_TpTxConfirmation(PduIdType PduId, NotifResultType Result)
{
}
/* <COM691><COM654><COM655><COM656><COM657><COM721> */
BufReq_ReturnType
Com_StartOfReception(PduIdType ComRxPduId, PduLengthType TpSduLength, PduLengthType *RxBufferSizePtr)
{
	return(BUFREQ_OK);
}
/* <COM692><COM658><COM782> */
BufReq_ReturnType
Com_CopyRxData(PduIdType PduId, const PduInfoType *PduInfoPtr, PduLengthType *RxBufferSizePtr)
{
	return(BUFREQ_OK);
}
/* <COM693><COM663><COM783> */
BufReq_ReturnType
Com_CopyTxData(PduIdType PduId, PduInfoType *PduInfoPtr, RetryInfoType *RetryInfoPtr, PduLengthType *TxDataCntPtr)
{
	return(BUFREQ_OK);
}
