/*
 *  TOPPERS/A-COM
 *      Automotive COM
 *
 *  Copyright (C) 2013-2016 by Center for Embedded Computing Systems
 *                             Graduate School of Information Science, Nagoya Univ., JAPAN
 *  Copyright (C) 2014-2016 by AISIN COMCRUISE Co., Ltd., JAPAN
 *  Copyright (C) 2015-2016 by eSOL Co.,Ltd., JAPAN
 *  Copyright (C) 2013-2016 by FUJI SOFT INCORPORATED, JAPAN
 *  Copyright (C) 2014-2016 by NEC Communication Systems, Ltd., JAPAN
 *  Copyright (C) 2013-2016 by Panasonic Advanced Technology Development Co., Ltd., JAPAN
 *  Copyright (C) 2013-2014 by Renesas Electronics Corporation, JAPAN
 *  Copyright (C) 2014-2016 by SCSK Corporation, JAPAN
 *  Copyright (C) 2013-2016 by Sunny Giken Inc., JAPAN
 *  Copyright (C) 2015-2016 by SUZUKI MOTOR CORPORATION
 *  Copyright (C) 2013-2016 by TOSHIBA CORPORATION, JAPAN
 *  Copyright (C) 2013-2016 by Witz Corporation
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
 *  $Id: Com.c 3266 2016-03-31 04:41:02Z sunnygiken-yamawaki $
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
 *  最大サイズ型の定義
 */
#ifdef INT64_MAX
typedef uint64	UINT_MAX;
typedef sint64	SINT_MAX;
#else
typedef uint32	UINT_MAX;
typedef sint32	SINT_MAX;
#endif /* INT64_MAX */

/*
 *  内部関数のプロトタイプ宣言
 */
/* 共通 */
static void init_ipdu(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void clear_occurrence(const IPDU_INIB *p_ipdu_inib);
static boolean filtering(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void set_filter_buffer(const SIGNAL_INIB	*p_signal_inib, const void *p_data);
LOCAL_INLINE UINT_MAX copy_signal_to_uint(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE sint32 cast_signal_to_sint32(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void set_buffer(void *write_buffer, uint8 type, uint16 length, const void *p_data);
LOCAL_INLINE void get_buffer(const void *read_buffer, uint8 type, uint16 length, void *p_data);
LOCAL_INLINE void init_send_signal(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE void call_cbk(void (*cbk_notification)(void), uint8 serviceid);

/* 送信 */
LOCAL_INLINE void send_ipdu(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE Std_ReturnType send_ipdu_respect_mdt(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void set_mdt(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void start_tx_dm(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void packing(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void set_updatebit(uint8 *p_buffer, uint16 updatebitposition);
LOCAL_INLINE void clear_updatebit(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE boolean check_tx_signal(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE boolean check_tms(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void switch_tx_mode(const IPDU_INIB *p_ipdu_inib, boolean tms);
LOCAL_INLINE void set_tx_mode(const IPDU_INIB *p_ipdu_inib, boolean tms);
LOCAL_INLINE void check_signal_filtering(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE void set_repeat_cnt(const IPDU_INIB *p_ipdu_inib, uint8 trans_property, boolean change_signal);
LOCAL_INLINE boolean check_count_tms(uint16 true_count);

/* 受信 */
LOCAL_INLINE void init_receive_signal(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE void receive_ipdu(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void unpacking(const SIGNAL_INIB *p_signal_inib, void *p_data);
LOCAL_INLINE boolean check_invalid(const SIGNAL_INIB *p_signal_inib, const void *p_data);
LOCAL_INLINE boolean check_updatebit(const uint8 *read_buffer, uint16 bitposition);
LOCAL_INLINE void start_rx_dm(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void stop_rx_dm(const IPDU_INIB *p_ipdu_inib);
LOCAL_INLINE void check_rx_dm(const SIGNAL_INIB *p_signal_inib);
LOCAL_INLINE void check_rx_g_dm(const SIGNAL_G_INIB *p_signal_g_inib);
LOCAL_INLINE void reset_rx_dm(uint8 *dm_state, uint32 *dm_mf_cnt, uint32 comtimeout);
LOCAL_INLINE void get_ipdu_buffer(const SIGNAL_INIB *p_signal_inib, const UINT_MAX *buffer, void **p_data);

/*
 *  現在実行中のComコンフィギュレーション情報
 */
static const Com_ConfigType			*p_cur_com_config;
static const SIGNAL_INIB			*p_cur_signal_inib;
static const SIGNAL_G_INIB			*p_cur_signal_g_inib;
static const IPDU_INIB		* const	*pp_cur_all_ipdu_inib;
static const IPDU_INIB				*p_cur_rx_ipdu_inib;
static const IPDU_INIB				*p_cur_tx_ipdu_inib;

/*
 *  Comの初期化状態
 */
static Com_StatusType				com_state = COM_UNINIT;

/*
 *  [COM432] Com_Init
 */
void
Com_Init(const Com_ConfigType *config)
{
	const IPDU_INIB	*p_ipdu_inib;
	PduIdType		i;
	uint32			j;
	boolean			config_invalid = TRUE;

	SchM_Enter_Com_Reentrant_0();

	/* [COM373] Com_Initによるポストビルドパラメータは未初期化(未使用)時のみ更新できる */
	COM_CHECK_UNINITIALIZED(COMServiceId_Init);

	/* [NCOM040] NULL_PTRの場合，ComConfigurationIdが0のコンフィギュレーションを使う */
	if (config == NULL_PTR) {
		config = &com_config[0];
	}
	else {
		/* [COM433][NCOM056] 引数configが不正 */
		for (j = 0U; j < COM_CONFIG_NUM; j++) {
			if (config == &com_config[j]) {
				config_invalid = FALSE;
				break;
			}
		}
		COM_CHECK_PARAM(config_invalid == FALSE, COMServiceId_Init);
	}

	/* 現在実行中のコンフィグレーション情報を保持 */
	p_cur_com_config = config;
	p_cur_signal_inib = p_cur_com_config->p_signal_inib_table;
	p_cur_signal_g_inib = p_cur_com_config->p_signal_g_inib_table;
	pp_cur_all_ipdu_inib = p_cur_com_config->pp_ipdu_inib_table;
	p_cur_rx_ipdu_inib = p_cur_com_config->p_rx_ipdu_inib_list;
	p_cur_tx_ipdu_inib = p_cur_com_config->p_tx_ipdu_inib_list;

	/* [COM128] 全IPDUの初期化 */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);

		/* [COM217][COM098][COM483][COM117] IPDUの初期化 */
		init_ipdu(p_ipdu_inib);

		/* [COM328][COM444] IPDU停止 */
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

	/* [NCOM068] 初期化未実施 */
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
	const SIGNAL_G_INIB		*p_signal_g_inib;
	const SIGNAL_INIB		*p_signal_inib;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	boolean					start_flg;
	uint8					target, belong;
	PduIdType				i;
	Com_IpduGroupIdType		j;
	Com_SignalIdType		k;
	Com_SignalGroupIdType	l;

	SchM_Enter_Com_Reentrant_0();

	/* [NCOM069] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_IpduGroupControl);
	/* [NCOM091] NULLポインタが指定 */
	COM_CHECK_NULL_POINTER(ipduGroupVector != NULL_PTR, COMServiceId_IpduGroupControl);

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
		/* [COM614] 停止しているIPDUを開始させる */
		if ((start_flg != FALSE) && (!IPDU_IS_STARTED(p_ipdu_inib->p_state))) {
			/*
			 *  [COM222][COMa001] initializeがFALSEであり，かつIPDUが開始された場合，
			 *  周期送信のためののMF回数カウンタは初期化しない
			 *  [COM740] Com_Init後に初めてCom_IpduGroupControlを呼び出す際に，
			 *  initializeへFALSEを指定した場合，TRUEを指定した場合と同じ結果になる
			 */
			if (initialize != FALSE) {
				/* [COM222] IPDUの初期化 */
				init_ipdu(p_ipdu_inib);
			}
			else {
				/* [COM787] OCCURRENCEクリア */
				clear_occurrence(p_ipdu_inib);
			}

			if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
				p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
				COM_CHECK_NULL_POINTER(p_tx_ipdu_cb != NULL_PTR, COMServiceId_IpduGroupControl);

				/* カウンタの初期化 */
				p_tx_ipdu_cb->mdt_mf_cnt = 0U;
				p_tx_ipdu_cb->queuing_cnt = 0U;
				p_tx_ipdu_cb->dm_mf_cnt = 0U;

				/* [COM787][COM217] アップデートビットクリア */
				clear_updatebit(p_ipdu_inib);

				/* [COM229][COM223][COM032][COM238][NCOM053] TMSを決定し，送信モードを決定する */
				switch_tx_mode(p_ipdu_inib, check_tms(p_ipdu_inib));
			}
			else {
				/* [COM787][COM733] DM開始 */
				start_rx_dm(p_ipdu_inib);
			}

			/* [COM612][COM114] IPDUの開始 */
			IPDU_SET_STARTED(p_ipdu_inib->p_state);
		}
		/* 開始しているIPDUを停止させる */
		else if ((start_flg == FALSE) && (IPDU_IS_STARTED(p_ipdu_inib->p_state))) {
			/* 真っ先にIPDUを停止状態にする */
			IPDU_CLEAR_STARTED(p_ipdu_inib->p_state);
			if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
				p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
				COM_CHECK_NULL_POINTER(p_tx_ipdu_cb != NULL_PTR, COMServiceId_IpduGroupControl);

				/* [COM479] 停止されたIPDUに対する送信完了通知が届いていない場合，エラー通知を行う */
				if (p_tx_ipdu_cb->queuing_cnt != 0U) {
					/* 単独シグナル処理 */
					for (k = 0U; k < p_ipdu_inib->tnum_signal; k++) {
						p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[k]);
						COM_CHECK_NULL_POINTER(p_signal_inib != NULL_PTR, COMServiceId_IpduGroupControl);
						call_cbk(p_signal_inib->ComErrorNotification, COMServiceId_IpduGroupControl);
					}
					/* シグナルグループ処理 */
					for (l = 0U; l < p_ipdu_inib->tnum_signal_g; l++) {
						p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[l]);
						COM_CHECK_NULL_POINTER(p_signal_g_inib != NULL_PTR, COMServiceId_IpduGroupControl);
						call_cbk(p_signal_g_inib->ComErrorNotification, COMServiceId_IpduGroupControl);
					}
					p_tx_ipdu_cb->queuing_cnt = 0U;
				}
				/* [COM115] 送信DMをキャンセルし，以降の送信完了通知を無視する */
				IPDU_CLEAR_DM(p_ipdu_inib->p_state);
			}
			else {
				/* [COM685] 受信DM停止 */
				stop_rx_dm(p_ipdu_inib);
			}
			/* [COM684] 送信，受信処理を無効にする */
			IPDU_CLEAR_ALL(p_ipdu_inib->p_state);
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

	/* [NCOM070] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_ReceptionDMControl);
	/* [NCOM092] NULL_PTRチェック */
	COM_CHECK_NULL_POINTER(ipduGroupVector != NULL_PTR, COMServiceId_ReceptionDMControl);

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
 *  [COM434] マクロで実装してもよいがNULLポインタが指定のため関数とする
 */
void
Com_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	/* [NCOM039] NULLポインタが指定 */
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

	/* [NCOM093] NULLポインタが指定 */
	COM_CHECK_NULL_POINTER(ipduGroupVector != NULL_PTR, COMServiceId_ClearIpduGroupVector);

	for (i = 0U; i < IPDU_GROUP_VECTOR_NUM; i++) {
		ipduGroupVector[i] = 0U;
	}

  error_exit:
	return;
}

/*
 *  [COM750] Com_SetIpduGroup
 */
void
Com_SetIpduGroup(Com_IpduGroupVector ipduGroupVector, Com_IpduGroupIdType ipduGroupId, boolean bitval)
{
	SchM_Enter_Com_Reentrant_0();

	/* [NCOM071] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_SetIpduGroup);
	/* [NCOM057] 不正な値が指定 */
	COM_CHECK_PARAM(ipduGroupId < GET_IPDU_G_NUM(), COMServiceId_SetIpduGroup);
	/* [NCOM094] NULLポインタが指定 */
	COM_CHECK_NULL_POINTER(ipduGroupVector != NULL_PTR, COMServiceId_SetIpduGroup);

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
	TX_SIGNAL_G_CB		*p_tx_signal_g_cb;
	TX_SIGNAL_CB		*p_tx_signal_cb;
	TX_IPDU_CB			*p_tx_ipdu_cb;
	uint8				ercd;

	SchM_Enter_Com_Reentrant_0();

	/* [NCOM072] 初期化未実施 */
	COM_CHECK_INITIALIZED_ERCD(COMServiceId_SendSignal);
	/* [NCOM058] 不正な値が指定 */
	COM_CHECK_PARAM_ERCD(SignalId < GET_SIGNAL_NUM(), COMServiceId_SendSignal);
	/* [NCOM073] NULLポインタが指定 */
	COM_CHECK_NULL_POINTER_ERCD(SignalDataPtr != NULL_PTR, COMServiceId_SendSignal);

	/* [COM624] */
	p_signal_inib = GET_SIGNAL_INIB(SignalId);
	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
	p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
	p_tx_signal_g_cb = (TX_SIGNAL_G_CB *) p_signal_inib->p_signal_g_cb;

	COM_CHECK_PARAM_ERCD(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_SendSignal);
	COM_CHECK_NULL_POINTER_ERCD(p_tx_signal_cb != NULL_PTR, COMServiceId_SendSignal);

	check_signal_filtering(p_signal_inib, SignalDataPtr);

	if (p_signal_inib->p_shadow_buffer == NULL_PTR) {

		/* [COMa003] アップデートビット設定 */
		set_updatebit(p_ipdu_inib->p_ipdu_buffer, p_signal_inib->ComUpdateBitPosition);

		/* IPDU開始判定 */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

			COM_CHECK_PARAM_ERCD(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
								  (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
								 (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_SendSignal);

			set_repeat_cnt(p_ipdu_inib, p_signal_inib->ComTransferProperty, p_tx_signal_cb->change_signal_flg);

			ercd = E_OK;
			p_tx_signal_cb->change_signal_flg = FALSE;
		}
		else {
			ercd = COM_SERVICE_NOT_AVAILABLE;
		}
	}
	else {
		ercd = E_OK;
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

	/* [NCOM074] 初期化未実施 */
	COM_CHECK_INITIALIZED_ERCD(COMServiceId_ReceiveSignal);
	/* [NCOM059] 不正な値が指定 */
	COM_CHECK_PARAM_ERCD(SignalId < GET_SIGNAL_NUM(), COMServiceId_ReceiveSignal);
	/* [NCOM075] NULLポインタが指定 */
	COM_CHECK_NULL_POINTER_ERCD(SignalDataPtr != NULL_PTR, COMServiceId_ReceiveSignal);

	p_signal_inib = GET_SIGNAL_INIB(SignalId);
	p_ipdu_inib = p_signal_inib->p_ipdu_inib;

	COM_CHECK_PARAM_ERCD(p_ipdu_inib->ComIPduDirection == COM_RECEIVE, COMServiceId_ReceiveSignal);

	/* [COM631] SignalDataPtrにSignalIdのシグナルデータをコピーする */

	/* [COMa019] 単独シグナル処理 */
	if (p_signal_inib->p_shadow_buffer == NULL_PTR) {
		get_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, SignalDataPtr);
	}
	/* グループシグナル処理
	 *  [NCOM051] グループシグナルを受信する前に本システムサービスが呼び出された場合，初期値(ComSignalInitValue) を返す
	 *  [NCOM052] シャドウバッファを更新する前に本システムサービスが呼び出された場合，更新前のシャドウバッファの値を返す
	 */
	else {
		get_buffer(p_signal_inib->p_shadow_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, SignalDataPtr);
	}

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
 *  [COM200] Com_SendSignalGroup
 */
uint8
Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
	/* [COM637] コンフィギュレーション時にシグナルグループを設定する */
	/* [COM636] Com_SendSignalを呼び出してシャドウバッファを更新する */

	const SIGNAL_G_INIB	*p_signal_g_inib;
	const SIGNAL_INIB	*p_signal_inib;
	const IPDU_INIB		*p_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;
	TX_SIGNAL_G_CB		*p_tx_signal_g_cb;
	TX_SIGNAL_CB		*p_tx_signal_cb;
	Com_SignalIdType	i;
	uint8				ercd;
	boolean				tms;
	boolean				old_tmc;

	SchM_Enter_Com_Reentrant_0();

	/* [NCOM076] 初期化未実施 */
	COM_CHECK_INITIALIZED_ERCD(COMServiceId_SendSignalGroup);
	/* [NCOM060] 不正な値が指定 */
	COM_CHECK_PARAM_ERCD(SignalGroupId < GET_SIGNAL_G_NUM(), COMServiceId_SendSignalGroup);

	p_signal_g_inib = GET_SIGNAL_G_INIB(SignalGroupId);
	p_tx_signal_g_cb = (TX_SIGNAL_G_CB *) p_signal_g_inib->p_signal_g_cb;
	p_ipdu_inib = p_signal_g_inib->p_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	COM_CHECK_PARAM_ERCD(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_SendSignal);
	COM_CHECK_NULL_POINTER_ERCD(p_tx_signal_g_cb != NULL_PTR, COMServiceId_SendSignalGroup);

	for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);

		/* [COM635] グループシグナルをまとめてIPDUにパッキングする */
		/* [COM334] IPDUが停止中でもバッファの更新(パッキング)を行う */
		/* [COM050] シャドウバッファの値がIPDUバッファにパッキングされる */
		packing(p_signal_inib, p_signal_inib->p_shadow_buffer);

		if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
			p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

			old_tmc = p_tx_signal_cb->tmc;
			p_tx_signal_cb->tmc = filtering(p_signal_inib, p_signal_inib->p_shadow_buffer);

			if (p_tx_signal_cb->tmc != old_tmc) {
				if (p_tx_signal_cb->tmc != FALSE) {
					p_tx_ipdu_cb->tmc_true_cnt++;
				}
				else {
					p_tx_ipdu_cb->tmc_true_cnt--;
				}
			}
		}
		/* [COM353]送信側では符号拡張しない */
		set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->p_shadow_buffer);
	}

	/* [COM061]シグナルグループアップデート設定 */
	set_updatebit(p_ipdu_inib->p_ipdu_buffer, p_signal_g_inib->ComUpdateBitPosition);

	/* [COM245] */
	tms = check_count_tms(p_tx_ipdu_cb->tmc_true_cnt);

	/* 送信モード切り替え */
	switch_tx_mode(p_ipdu_inib, tms);

	/* IPDU開始判定 */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

		COM_CHECK_PARAM_ERCD(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
							  (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
							  (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_SendSignalGroup);

		set_repeat_cnt(p_ipdu_inib, p_signal_g_inib->ComTransferProperty, p_tx_signal_g_cb->change_signal_g_flg);

		ercd = E_OK;
		p_tx_signal_g_cb->change_signal_g_flg = FALSE;
	}
	else {
		ercd = COM_SERVICE_NOT_AVAILABLE;
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();

	return(ercd);
}

/*
 *  [COM201] Com_ReceiveSignalGroup
 */
uint8
Com_ReceiveSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
	uint8				ercd;
	const IPDU_INIB		*p_ipdu_inib;
	const SIGNAL_INIB	*p_signal_inib;
	const SIGNAL_G_INIB	*p_signal_g_inib;
	uint16				j;
	RX_SIGNAL_G_CB		*p_rx_signal_g_cb;

	SchM_Enter_Com_Reentrant_0();

	/* [NCOM077] 初期化未実施 */
	COM_CHECK_INITIALIZED_ERCD(COMServiceId_ReceiveSignalGroup);
	/* [NCOM061] 不正な値が指定 */
	COM_CHECK_PARAM_ERCD(SignalGroupId < GET_SIGNAL_G_NUM(), COMServiceId_ReceiveSignalGroup);

	/*
	 * [COM638]引数SignalGroupIdで指定されたシグナルグループが所属するIPDUからデータを取り出し，対応するシャドウバッファを更新する
	 */
	p_signal_g_inib = GET_SIGNAL_G_INIB(SignalGroupId);
	p_rx_signal_g_cb = (RX_SIGNAL_G_CB *) p_signal_g_inib->p_signal_g_cb;

	/* [COM051]無効値フラグが無しの場合，シグナルバッファのデータをシャドウバッファにコピーする */
	for (j = 0U; j < p_signal_g_inib->tnum_g_signal; j++) {
		p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[j]);

		get_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->p_shadow_buffer);
	}

	p_ipdu_inib = p_signal_g_inib->p_ipdu_inib;

	/* [COM461] シグナルバッファのグループシグナルをシャドウバッファに格納 */
	/* [COM201] IPDUが開始状態の場合 */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
		ercd = E_OK;
	}
	/* [COM201] IPDUが停止状態の場合 */
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
	const void			*p_invalid;
	uint8				ercd;

	SchM_Enter_Com_Reentrant_2();

	/* [NCOM078] 初期化未実施 */
	COM_CHECK_INITIALIZED_ERCD(COMServiceId_InvalidateSignal);
	/* [NCOM062] 不正な値が指定 */
	COM_CHECK_PARAM_ERCD(SignalId < GET_SIGNAL_NUM(), COMServiceId_InvalidateSignal);

	p_signal_inib = GET_SIGNAL_INIB(SignalId);
	/* 排他エリア内で無効値を取り出す */
	p_invalid = p_signal_inib->ComSignalDataInvalidValue;

	if (p_invalid != NULL_PTR) {
		/* [COM099][COM642] */
		ercd = Com_SendSignal(SignalId, p_invalid);
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
 *  [COM557] Com_InvalidateSignalGroup
 */
uint8
Com_InvalidateSignalGroup(Com_SignalGroupIdType SignalGroupId)
{
	const SIGNAL_INIB	*p_signal_inib;
	const SIGNAL_G_INIB	*p_signal_g_inib;
	TX_SIGNAL_G_CB		*p_tx_signal_g_cb;
	uint8				ercd = E_OK;
	Com_SignalIdType	i;

	SchM_Enter_Com_Reentrant_2();

	/* [NCOM079] 初期化未実施 */
	COM_CHECK_INITIALIZED_ERCD(COMServiceId_InvalidateSignalGroup);
	/* [NCOM063] 不正な値が指定 */
	COM_CHECK_PARAM_ERCD(SignalGroupId < GET_SIGNAL_G_NUM(), COMServiceId_InvalidateSignalGroup);

	p_signal_g_inib = GET_SIGNAL_G_INIB(SignalGroupId);

	for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);
		p_tx_signal_g_cb = (TX_SIGNAL_G_CB *) p_signal_inib->p_signal_g_cb;

		if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
			/* シグナルバッファにComSignalDataInvalidValueを格納する */
			check_signal_filtering(p_signal_inib, p_signal_inib->ComSignalDataInvalidValue);
		}
		else {
			ercd = COM_SERVICE_NOT_AVAILABLE;
			break;
		}
	}

	/* 指定されたシグナルグループに所属しているグループシグナルのいずれかに無効値が設定されていない */
	if (ercd != COM_SERVICE_NOT_AVAILABLE) {
		/* [COM645] 無効値送信 */
		ercd = Com_SendSignalGroup(SignalGroupId);
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

	/* [NCOM080] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_TriggerIPDUSend);
	/* [NCOM064] 不正な値が指定 */
	COM_CHECK_PARAM(PduId < GET_IPDU_NUM(), COMServiceId_TriggerIPDUSend);

	p_ipdu_inib = GET_IPDU_INIB(PduId);
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
	const IPDU_INIB	*p_ipdu_inib;

	SchM_Enter_Com_Reentrant_0();

	/* [NCOM081] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_SwitchIpduTxMode);
	/* [NCOM065] 不正な値が指定 */
	COM_CHECK_PARAM(PduId < GET_IPDU_NUM(), COMServiceId_SwitchIpduTxMode);

	p_ipdu_inib = GET_IPDU_INIB(PduId);
	COM_CHECK_PARAM(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_SwitchIpduTxMode);

	/* 次の開始時にフィルタ判定して結果が変わるため，IPDU停止時に実施する必要はない */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
		switch_tx_mode(p_ipdu_inib, Mode);
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

	/* [NCOM082] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_RxIndication);
	/* [NCOM066] 不正な値が指定 */
	COM_CHECK_PARAM(RxPduId < GET_IPDU_NUM(), COMServiceId_RxIndication);
	/* [NCOM083] NULLポインタが指定 */
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

				/* [COM381] Com_TriggerIPDUSend, Com_SendSignal，Com_SendSignalGroupはコールアウトから呼出し可能とする */
				SchM_Exit_Com_Reentrant_0();
				/* [NCOM096] 受信した全てのデータをIPDUに格納 */
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
				receive_ipdu(p_ipdu_inib);
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
	const SIGNAL_G_INIB		*p_signal_g_inib;
	const SIGNAL_INIB		*p_signal_inib;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	Com_SignalIdType		i;
	Com_SignalGroupIdType	j;

	/* [COM652] 割込みから呼び出される可能性があるので排他が必要 */
	SchM_Enter_Com_Reentrant_1();

	/* [NCOM084] 初期化未実施 */
	COM_CHECK_INITIALIZED(COMServiceId_TxConfirmation);
	/* [NCOM067] 不正な値が指定 */
	COM_CHECK_PARAM(TxPduId < GET_IPDU_NUM(), COMServiceId_TxConfirmation);

	p_ipdu_inib = GET_IPDU_INIB(TxPduId);

	COM_CHECK_PARAM(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_TxConfirmation);

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

	/* PduR_ComTransmitを送信した場合のみ受け付ける */
	if (p_tx_ipdu_cb->queuing_cnt != 0U) {
		p_tx_ipdu_cb->queuing_cnt--;

		/* [COM577] */
		if (p_tx_ipdu_inib->ComTxIPduClearUpdateBit == COM_CONFIRMATION) {
			/* アップデートビットクリア */
			clear_updatebit(p_ipdu_inib);
		}

		/* [COM469] MDTカウンタが0より大きい場合，MDTカウンタを再設定する */
		if (p_tx_ipdu_inib->ComMinimumDelayTime > 0U) {
			set_mdt(p_ipdu_inib);
		}

		if (p_tx_ipdu_cb->repeat_cnt > 0U) {
			p_tx_ipdu_cb->repeat_cnt--;
		}

		/* IPDU開始中 */
		/* [COMa002] IPDU停止時はRTEへ通知を行わない */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			IPDU_CLEAR_FIRST_DIRECT_SEND(p_ipdu_inib->p_state);

			/* 送信完了通知 */
			if (p_tx_ipdu_cb->repeat_cnt == 0U) {
				IPDU_CLEAR_DIRECT_SEND(p_ipdu_inib->p_state);

				/*
				 * [COM308] IPDU送信を繰り返した回数分の送信完了通知を受け取った後に
				 * 送信DMを停止する(直接N回送信以外の場合は送信完了通知の度に停止)
				 */
				IPDU_CLEAR_DM(p_ipdu_inib->p_state);

				/* 通知判定 */
				if (p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) {
					/* 単独シグナル処理 */
					for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
						p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
						COM_CHECK_NULL_POINTER(p_signal_inib != NULL_PTR, COMServiceId_TxConfirmation);
						call_cbk(p_signal_inib->ComNotification, COMServiceId_TxConfirmation);
					}
					/* シグナルグループ処理 */
					for (j = 0U; j < p_ipdu_inib->tnum_signal_g; j++) {
						p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[j]);
						COM_CHECK_NULL_POINTER(p_signal_g_inib != NULL_PTR, COMServiceId_TxConfirmation);
						call_cbk(p_signal_g_inib->ComNotification, COMServiceId_TxConfirmation);
					}
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
	const SIGNAL_G_INIB	*p_signal_g_inib;
	RX_SIGNAL_CB		*p_rx_signal_cb;
	RX_SIGNAL_G_CB		*p_rx_signal_g_cb;

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
					receive_ipdu(p_ipdu_inib);
				}

				/* IPDUに所属するシグナルの処理 */
				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);

					if (check_updatebit(p_ipdu_inib->p_ipdu_buffer, p_signal_inib->ComUpdateBitPosition) != FALSE) {
						/*
						 * [COM715][NCOM031][COM738] 受信DMカウンタリセット処理
						 * [NCOM034] 受信DMをリセットした場合，受信DMをチェックしない
						 */
						p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
						if (p_rx_signal_cb != NULL_PTR) {
							reset_rx_dm(&p_rx_signal_cb->dm_state, &p_rx_signal_cb->dm_mf_cnt, p_signal_inib->ComTimeout);
						}
					}
					else {
						/* アップデートビットが更新されてないシグナルは受信DMをチェックする */
						check_rx_dm(p_signal_inib);
					}
				}

				/* IPDUに所属するシグナルグループの処理 */
				for (j = 0U; j < p_ipdu_inib->tnum_signal_g; j++) {
					p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[j]);

					if (check_updatebit(p_ipdu_inib->p_ipdu_buffer, p_signal_g_inib->ComUpdateBitPosition) != FALSE) {
						/*
						 * [COM715][NCOM031][COM738] 受信DMカウンタリセット処理
						 * [NCOM034] 受信DMをリセットした場合，受信DMをチェックしない
						 */
						p_rx_signal_g_cb = (RX_SIGNAL_G_CB *) p_signal_g_inib->p_signal_g_cb;
						if (p_rx_signal_g_cb != NULL_PTR) {
							reset_rx_dm(&p_rx_signal_g_cb->dm_state, &p_rx_signal_g_cb->dm_mf_cnt, p_signal_g_inib->ComTimeout);
						}
					}
					else {
						/* アップデートビットが更新されてないシグナルグループは受信DMをチェックする */
						check_rx_g_dm(p_signal_g_inib);
					}
				}

				/* IPDUの受信状態をクリア */
				IPDU_CLEAR_NOTICED(p_ipdu_inib->p_state);
			}
			else {
				/* [COM290][COM292][NCOM035]受信状態でない，IPDUは受信DMをチェックする */
				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
					check_rx_dm(p_signal_inib);
				}
				for (j = 0U; j < p_ipdu_inib->tnum_signal_g; j++) {
					p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[j]);
					check_rx_g_dm(p_signal_g_inib);
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
	const SIGNAL_G_INIB		*p_signal_g_inib;
	const SIGNAL_INIB		*p_signal_inib;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	PduIdType				i;
	Com_SignalIdType		j;
	Com_SignalGroupIdType	k;

	SchM_Enter_Com_Reentrant_0();

	/* [COM665] 初期化されていない場合は何もせずにreturn */
	if (com_state != COM_INIT) {
		goto error_exit;
	}

	for (i = 0U; i < GET_TX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_TX_IPDU_INIB(i);
		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

		/* [COM777] IPDU開始判定 IPDUが停止している場合は，送信しない */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

			COM_CHECK_PARAM(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
							 (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
							(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_MainFunctionTx);

			/* IPDU開始時にMDTを初期化するため，IPDUが開始している場合のみMDTを更新 */
			if (p_tx_ipdu_cb->mdt_mf_cnt > 0U) {
				p_tx_ipdu_cb->mdt_mf_cnt--;
			}

			/* 通知判定 */
			if (IPDU_IS_NOTICED(p_ipdu_inib->p_state)) {
				/* 単独シグナル処理 */
				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
					COM_CHECK_NULL_POINTER(p_signal_inib != NULL_PTR, COMServiceId_MainFunctionTx);
					call_cbk(p_signal_inib->ComNotification, COMServiceId_MainFunctionTx);

				}
				/* シグナルグループ処理 */
				for (k = 0U; k < p_ipdu_inib->tnum_signal_g; k++) {
					p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[k]);
					COM_CHECK_NULL_POINTER(p_signal_g_inib != NULL_PTR, COMServiceId_MainFunctionTx);
					call_cbk(p_signal_g_inib->ComNotification, COMServiceId_MainFunctionTx);
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
					/* 単独シグナル処理 */
					for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
						p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
						COM_CHECK_NULL_POINTER(p_signal_inib != NULL_PTR, COMServiceId_MainFunctionTx);
						/* [COM304] */
						call_cbk(p_signal_inib->ComTimeoutNotification, COMServiceId_MainFunctionTx);
					}
					/* シグナルグループ処理 */
					for (k = 0U; k < p_ipdu_inib->tnum_signal_g; k++) {
						p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[k]);
						COM_CHECK_NULL_POINTER(p_signal_g_inib != NULL_PTR, COMServiceId_MainFunctionTx);
						/* [COM304] */
						call_cbk(p_signal_g_inib->ComTimeoutNotification, COMServiceId_MainFunctionTx);
					}
					/* DM停止 */
					IPDU_CLEAR_DM(p_ipdu_inib->p_state);
					/* [COM392] 送信を停止する */
					IPDU_CLEAR_DIRECT_SEND(p_ipdu_inib->p_state);
					IPDU_CLEAR_FIRST_DIRECT_SEND(p_ipdu_inib->p_state);
					p_tx_ipdu_cb->repeat_cnt = 0U;
					/* キューイングを0で初期化する */
					p_tx_ipdu_cb->queuing_cnt = 0U;
					/* [COMa006] MDTカウンタを0にし，MDT待ち状態のIPDUがある場合は即時送信 */
					p_tx_ipdu_cb->mdt_mf_cnt = 0U;

#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
					/* [COM775] 保留された送信要求を無効にする */
					IPDU_CLEAR_RETRY(p_ipdu_inib->p_state);
#endif
				}
			}

			/* IPDUの送信処理 */
			send_ipdu(p_ipdu_inib);
		}
	}

  error_exit:
	SchM_Exit_Com_Reentrant_0();
	return;
}


/*
 *  IPDUの初期化
 */
static void
init_ipdu(const IPDU_INIB *p_ipdu_inib)
{
	const TX_IPDU_INIB		*p_tx_ipdu_inib;
	const SIGNAL_G_INIB		*p_signal_g_inib;
	const SIGNAL_INIB		*p_signal_inib;
	TX_IPDU_CB				*p_tx_ipdu_cb;
	Com_SignalIdType		i;
	PduLengthType			j;
	Com_SignalGroupIdType	k;
	boolean					signal_algorithm;

	COM_CHECK_NULL_POINTER(p_ipdu_inib != NULL_PTR, COMServiceId_init_ipdu);

	if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
		p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
		COM_CHECK_NULL_POINTER(p_tx_ipdu_inib != NULL_PTR, COMServiceId_init_ipdu);
		/* [COM015][COM217] 送信IPDUバッファを未使用データで初期化 */
		for (j = 0U; j < p_ipdu_inib->PduLength; j++) {
			(p_ipdu_inib->p_ipdu_buffer)[j] = p_tx_ipdu_inib->ComTxIPduUnusedAreasDefault;
		}

		/* [COM484] グループシグナルの初期値をシャドウバッファに格納 */
		for (k = 0U; k < p_ipdu_inib->tnum_signal_g; k++) {
			p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[k]);

			for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
				p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);
				/* シャドウバッファにComSignalInitValueを格納 */
				set_buffer(p_signal_inib->p_shadow_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
			}
		}

		/* filteringの前にもOCCURRENCEをクリア */
		clear_occurrence(p_ipdu_inib);

		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
		p_tx_ipdu_cb->tmc_true_cnt = 0U;
		signal_algorithm = FALSE;

		/* 単独シグナル処理 */
		for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
			p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
			init_send_signal(p_signal_inib);
			if ((p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) && (signal_algorithm == FALSE)) {
				signal_algorithm = TRUE;
			}
		}
		/* シグナルグループ処理 */
		for (k = 0U; k < p_ipdu_inib->tnum_signal_g; k++) {
			p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[k]);
			for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
				p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);
				init_send_signal(p_signal_inib);
				if ((p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) && (signal_algorithm == FALSE)) {
					signal_algorithm = TRUE;
				}
			}
		}

		if (signal_algorithm == FALSE) {
			p_tx_ipdu_cb->tmc_true_cnt = 1U;
		}

		/* [COM217] アップデートビットクリア */
		clear_updatebit(p_ipdu_inib);

		/* 送信モード設定 */
		set_tx_mode(p_ipdu_inib, check_tms(p_ipdu_inib));
	}
	else {
		/* 単独シグナル処理 */
		for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
			p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);

			init_receive_signal(p_signal_inib);
		}
		/* シグナルグループ処理 */
		for (k = 0U; k < p_ipdu_inib->tnum_signal_g; k++) {
			p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[k]);
			for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
				p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);

				init_receive_signal(p_signal_inib);
			}
		}

		/* 受信シグナルグループ管理ブロックの無効値フラグを初期化 */
		for (i = 0U; i < p_ipdu_inib->tnum_signal_g; i++) {
			p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[i]);
		}

		/* OCCURRENCEをクリア */
		clear_occurrence(p_ipdu_inib);

		/* 受信DM停止 */
		stop_rx_dm(p_ipdu_inib);
	}

	/* [COM778] IPDU_STARTED_BIT以外をクリアする */
	IPDU_CLEAR_EXCEPT_STARTED(p_ipdu_inib->p_state);

  error_exit:
	return;
}

/*
 *  OCCURRENCEクリア
 */
LOCAL_INLINE void
clear_occurrence(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB				*p_signal_inib;
	const SIGNAL_G_INIB				*p_signal_g_inib;
	const FILTER_ONE_EVERY_N_INIB	*p_filter_one_every_n_inib;
	Com_SignalIdType				i;
	Com_SignalGroupIdType			j;

	COM_CHECK_NULL_POINTER(p_ipdu_inib != NULL_PTR, COMServiceId_clear_occurrence);

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		COM_CHECK_NULL_POINTER(p_signal_inib != NULL_PTR, COMServiceId_clear_occurrence);

		/* COM_ONE_EVERY_Nのフィルタを持つシグナルである場合のみ処理する */
		if (p_signal_inib->ComFilterAlgorithm == COM_ONE_EVERY_N) {
			p_filter_one_every_n_inib = (const FILTER_ONE_EVERY_N_INIB *) p_signal_inib->p_filter_inib;
			COM_CHECK_NULL_POINTER((p_filter_one_every_n_inib != NULL_PTR) &&
								   (p_filter_one_every_n_inib->p_occur != NULL_PTR), COMServiceId_clear_occurrence);

			/* [COM231] OCCURRENCEを0に設定する */
			*(p_filter_one_every_n_inib->p_occur) = 0U;
		}
	}

	for (j = 0U; j < p_ipdu_inib->tnum_signal_g; j++) {
		p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[j]);
		for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
			p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);
			COM_CHECK_NULL_POINTER(p_signal_inib != NULL_PTR, COMServiceId_clear_occurrence);

			/* COM_ONE_EVERY_Nのフィルタを持つシグナルである場合のみ処理する */
			if (p_signal_inib->ComFilterAlgorithm == COM_ONE_EVERY_N) {
				p_filter_one_every_n_inib = (const FILTER_ONE_EVERY_N_INIB *) p_signal_inib->p_filter_inib;
				COM_CHECK_NULL_POINTER((p_filter_one_every_n_inib != NULL_PTR) &&
									   (p_filter_one_every_n_inib->p_occur != NULL_PTR), COMServiceId_clear_occurrence);

				/* [COM231] OCCURRENCEを0に設定する */
				*(p_filter_one_every_n_inib->p_occur) = 0U;
			}
		}
	}

  error_exit:
	return;
}

/*
 *  フィルタリング処理
 *  [COM132][COM674] 符号付きデータに対してもフィルタリングを行う
 */
static boolean
filtering(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	const void	*p_filter_inib;
	boolean		result = FALSE;
	UINT_MAX	new_uint_data;
	UINT_MAX	old_uint_data;
	SINT_MAX	new_sint_data;
	boolean		signal_type_range;

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

		if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
			signal_type_range = TRUE;
		}
		else {
			signal_type_range = FALSE;
		}

		p_filter_inib = p_signal_inib->p_filter_inib;
		switch (p_signal_inib->ComFilterAlgorithm) {
		case COM_MASKED_NEW_EQUALS_X:
			new_uint_data = copy_signal_to_uint(p_signal_inib, p_data);
			/* ComSignalTypeがUINT系の場合，FILTER_UINT_MASKED_INIBにキャストする */
			if ((new_uint_data & ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) == ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
				result = TRUE;
			}
			break;
		case COM_MASKED_NEW_DIFFERS_X:
			new_uint_data = copy_signal_to_uint(p_signal_inib, p_data);
			/* ComSignalTypeがUINT系の場合，FILTER_UINT_MASKED_INIBにキャストする */
			if ((new_uint_data & ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) != ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
				result = TRUE;
			}
			break;
		case COM_MASKED_NEW_DIFFERS_MASKED_OLD:
			new_uint_data = copy_signal_to_uint(p_signal_inib, p_data);
			/* ComSignalTypeがUINT系の場合，FILTER_UINT_MASKED_OLD_INIBにキャストする */
			old_uint_data = copy_signal_to_uint(p_signal_inib, ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->p_filter_buffer);
			/* [COM763] */
			if ((new_uint_data & ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->ComFilterMask) != (old_uint_data & ((const FILTER_UINT_MASKED_OLD_INIB *) p_filter_inib)->ComFilterMask)) {
				result = TRUE;

				/* [COM302][COM303] */
				set_filter_buffer(p_signal_inib, p_data);
			}
			break;
		case COM_NEW_IS_WITHIN:
			if (signal_type_range != FALSE) {
				new_uint_data = copy_signal_to_uint(p_signal_inib, p_data);
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
			if (signal_type_range != FALSE) {
				new_uint_data = copy_signal_to_uint(p_signal_inib, p_data);
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
 *  各データ型をUINT_MAX(uint64 or uint32)へコピー
 */
LOCAL_INLINE UINT_MAX
copy_signal_to_uint(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	UINT_MAX signal_data;

	switch (p_signal_inib->ComSignalType) {
	case COM_BOOLEAN:
		signal_data = (UINT_MAX) (*((const boolean *) p_data));
		break;
	case COM_SINT8:
		signal_data = (UINT_MAX) ((SINT_MAX) (*((const sint8 *) p_data)));
		break;
	case COM_SINT16:
		signal_data = (UINT_MAX) ((SINT_MAX) (*((const sint16 *) p_data)));
		break;
	case COM_SINT32:
		signal_data = (UINT_MAX) *((const sint64 *) p_data);
		break;
	case COM_UINT8:
		signal_data = (UINT_MAX) (*((const uint8 *) p_data));
		break;
	case COM_UINT16:
		signal_data = (UINT_MAX) (*((const uint16 *) p_data));
		break;
	case COM_UINT32:
		signal_data = (UINT_MAX) *((const uint32 *) p_data);
		break;
	case COM_FLOAT32:
		signal_data = (UINT_MAX) *((const uint32 *) p_data);
		break;
	case COM_FLOAT64:
		signal_data = *((const UINT_MAX *) p_data);
		break;
	default:
		/* uninitialized警告抑止 */
		signal_data = 0U;
		COM_CHECK_PARAM(FALSE, COMServiceId_copy_signal_to_uint);
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
 *  送信処理
 */
LOCAL_INLINE void
send_ipdu(const IPDU_INIB *p_ipdu_inib)
{
	const TX_MODE_INIB	*p_tx_mode_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;
	Std_ReturnType		send_flg;
	boolean				direct_req;
	boolean				periodic_req;
	boolean				trigger_req;
	boolean				send_req = FALSE;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_mode_inib = p_tx_ipdu_cb->p_cur_tx_mode_inib;

	/* 送信モード判定 */
	switch (p_tx_mode_inib->ComTxModeMode) {
	/* [COM305] COM_DIRECT */
	case COM_DIRECT:
		direct_req = TRUE;
		periodic_req = FALSE;
		break;
	/* COM_PERIODIC */
	case COM_PERIODIC:
		direct_req = FALSE;
		periodic_req = TRUE;
		break;
	/* [COM305] COM_MIXED */
	case COM_MIXED:
		direct_req = TRUE;
		periodic_req = TRUE;
		break;
	/* [COM135] COM_NONE */
	/* [COMa021] COM_NONEは送信しない */
	default:
		direct_req = FALSE;
		periodic_req = FALSE;
		break;
	}

	/* トリガ送信判定 */
	if (IPDU_IS_TRIGGERED(p_ipdu_inib->p_state)) {
		IPDU_CLEAR_TRIGGERED(p_ipdu_inib->p_state);
		trigger_req = TRUE;
	}
	else {
		trigger_req = FALSE;
	}

	/* 送信判定 */
	if (IPDU_IS_MDT_WAIT(p_ipdu_inib->p_state)) {
		send_req = TRUE;
	}
#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
	if (IPDU_IS_RETRY(p_ipdu_inib->p_state)) {
		send_req = TRUE;
	}
#endif
	if (direct_req != FALSE) {
		if (p_tx_ipdu_cb->interval_mf_cnt > 0U) {
			p_tx_ipdu_cb->interval_mf_cnt--;
		}
		/* 送信する間隔のMF回数カウンタが0の場合 */
		if ((IPDU_IS_DIRECT_SEND(p_ipdu_inib->p_state) && (p_tx_ipdu_cb->interval_mf_cnt == 0U))) {
			send_req = TRUE;
		}
		else {
			/* DIRECTで送信するタイミングではない */
			direct_req = FALSE;
		}
	}
	if (periodic_req != FALSE) {
		if (p_tx_ipdu_cb->period_mf_cnt > 0U) {
			p_tx_ipdu_cb->period_mf_cnt--;
		}
		/* 周期のMF回数カウンタが0の場合 */
		if (p_tx_ipdu_cb->period_mf_cnt == 0U) {
			/* [COM776] 周期時間の位相は変わらない */
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimePeriod;
			send_req = TRUE;
		}
		else {
			/* PERIODICで送信するタイミングではない */
			periodic_req = FALSE;
		}
	}
	if (trigger_req != FALSE) {
		send_req = TRUE;
	}

	/* 送信 */
	if (send_req != FALSE) {
		/* [COM582][COM478][COM388] IPDU送信 */
		/* [COM494] 直接送信と周期送信のタイミングが重なった場合も1回だけ送信 */
		send_flg = send_ipdu_respect_mdt(p_ipdu_inib);

		/* 送信結果判定 */
		/* PduR_ComTransmitが呼ばれたか */
		if (send_flg == E_OK) {
			if (direct_req != FALSE) {
				/* 繰り返し送信が残っている場合 */
				if (p_tx_ipdu_cb->repeat_cnt != 0U) {
					/* [NCOM097] 直接N回送信タイミングはリトライの影響を受けない */
					p_tx_ipdu_cb->interval_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeRepetitionPeriod;
				}
				else {
					IPDU_CLEAR_DIRECT_SEND(p_ipdu_inib->p_state);
				}
			}
		}
	}
}

/*
 *  PduRへの送信
 *  [COM495] PduRへの送信は必ずsend_ipdu_respect_mdtを使用するため，TMS切替時もMDTが考慮される
 */
LOCAL_INLINE Std_ReturnType
send_ipdu_respect_mdt(const IPDU_INIB *p_ipdu_inib)
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

		/* PduR_ComTransmitをコールしたら，MDT待ちは解除 */
		IPDU_CLEAR_MDT_WAIT(p_ipdu_inib->p_state);

		if (ret_transmit == E_OK) {
			/* IPDU送信が成功した場合のみMDTを設定する */
			set_mdt(p_ipdu_inib);
#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
			/* E_OKであれば，リトライは解除 */
			IPDU_CLEAR_RETRY(p_ipdu_inib->p_state);
#endif
			/* キューイングする(上限0xFF) */
			if (p_tx_ipdu_cb->queuing_cnt != COM_INVALID_UINT8) {
				p_tx_ipdu_cb->queuing_cnt++;
			}

			/* [COM062] アップデートビットクリア */
			if (p_ipdu_inib->p_tx_ipdu_inib->ComTxIPduClearUpdateBit == COM_TRANSMIT) {
				clear_updatebit(p_ipdu_inib);
			}
		}
		else {
#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
			/* [COM773][COM779][COMa020] 失敗した送信要求のリトライ */
			IPDU_SET_RETRY(p_ipdu_inib->p_state);
#endif
		}

		/* PduR_ComTransmitが呼ばれた場合，ret_transmitをE_OKにする */
		ret_transmit = E_OK;
	}
	else {
		IPDU_SET_MDT_WAIT(p_ipdu_inib->p_state);
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
 *  MDTカウンタをセット
 */
LOCAL_INLINE void
set_mdt(const IPDU_INIB *p_ipdu_inib)
{
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

#if COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION == STD_OFF
	/* [COM789][COM698] DIRECT送信の一回目のみMDT監視する */
	if (IPDU_IS_FIRST_DIRECT_SEND(p_ipdu_inib->p_state)) {
		p_tx_ipdu_cb->mdt_mf_cnt = p_tx_ipdu_inib->ComMinimumDelayTime;
	}
	else {
		/* [COM471] MDTカウンタ設定 0の場合はMDT監視しない */
		p_tx_ipdu_cb->mdt_mf_cnt = 0U;
	}
#else
	p_tx_ipdu_cb->mdt_mf_cnt = p_tx_ipdu_inib->ComMinimumDelayTime;
#endif

	return;
}

/*
 *  送信DM開始
 */
LOCAL_INLINE void
start_tx_dm(const IPDU_INIB *p_ipdu_inib)
{
	TX_IPDU_CB *p_tx_ipdu_cb;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	if ((!IPDU_IS_DM(p_ipdu_inib->p_state)) && (p_ipdu_inib->ipdu_timeout != 0U)) {
		/* [COM481][COM774][NCOM100] */
		IPDU_SET_DM(p_ipdu_inib->p_state);
		p_tx_ipdu_cb->dm_mf_cnt = p_ipdu_inib->ipdu_timeout;
	}
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
	uint8			mask;
	PduLengthType	byte_index;         /* LSBのByte位置 */
	uint8			pos_lsb;            /* LSBのBit位置 */
	uint8			pos_msb;            /* MSBのBit位置 */
	uint16			i;
	UINT_MAX		signal_data;        /* シグナルデータ */
	uint8			bitsize;
	sint8			byte_direction;     /* byte_indexの移動方向 */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	byte_index = p_signal_inib->ComBitPositionLsb / 8U;
	pos_lsb = (uint8) (p_signal_inib->ComBitPositionLsb % 8U);
	bitsize = p_signal_inib->ComBitSize;

	COM_CHECK_PARAM((p_signal_inib->ComSignalEndianness >= COM_BIG_ENDIAN) &&
					(p_signal_inib->ComSignalEndianness <= COM_OPAQUE), COMServiceId_packing);
#ifdef INT64_MAX
	COM_CHECK_PARAM((p_signal_inib->ComSignalType >= COM_BOOLEAN) &&
					(p_signal_inib->ComSignalType <= COM_FLOAT64), COMServiceId_packing);
#else
	COM_CHECK_PARAM((p_signal_inib->ComSignalType >= COM_BOOLEAN) &&
					(p_signal_inib->ComSignalType <= COM_FLOAT32), COMServiceId_packing);
#endif /* INT64_MAX */

	if (p_signal_inib->ComSignalEndianness == COM_BIG_ENDIAN) {
		byte_direction = -1;
	}
	else {
		byte_direction = 1;
	}

	if (p_signal_inib->ComSignalEndianness == COM_OPAQUE) {
		/* COM_OPAQUEの場合，LSBが8の倍数でなければならない */
		COM_CHECK_PARAM(pos_lsb == 0U, COMServiceId_packing);

		p_signal_data = (const uint8 *) p_data;

		/* [COM443][COM472] COM_OPAQUEはCOM_UINT8_Nのみ */
		for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
			/* IPDUバッファにシグナルデータを格納 */
			(p_ipdu_inib->p_ipdu_buffer)[byte_index] = p_signal_data[i];

			/* [COM259_Conf] COM_OPAQUEはCOM_LITTLE_ENDIANとする */
			byte_index += (PduLengthType) byte_direction;
		}
	}
	else {
		/* 受信したデータを対象データ型へ変換 */
		signal_data = copy_signal_to_uint(p_signal_inib, p_data);

		/* 格納範囲が1Byte以内である場合 */
		if ((pos_lsb + bitsize) <= 8U) {
			pos_msb = (pos_lsb + bitsize) - 1U;
			mask = ((uint8) (0xFFU << pos_lsb)) & (0xFFU >> ((uint8) (7U - pos_msb)));

			/* IPDUバッファにシグナルデータを格納 */
			p_ipdu_inib->p_ipdu_buffer[byte_index] = (p_ipdu_inib->p_ipdu_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
		}
		else {
			mask = (uint8) (0xFFU << pos_lsb);

			/* IPDUバッファにシグナルデータを格納 */
			p_ipdu_inib->p_ipdu_buffer[byte_index] = (p_ipdu_inib->p_ipdu_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
			signal_data >>= 8U - pos_lsb;
			bitsize -= 8U - pos_lsb;

			byte_index += (PduLengthType) byte_direction;

			/* シグナルの残りサイズが1Byteより上回る場合 */
			while (bitsize > 8U) {
				/* IPDUバッファにシグナルデータを格納 */
				p_ipdu_inib->p_ipdu_buffer[byte_index] = (uint8) signal_data;
				signal_data >>= 8U;
				bitsize -= 8U;

				byte_index += (PduLengthType) byte_direction;
			}

			/* シグナルの残りデータ格納*/
			mask = (uint8) (0xFFU >> (8U - bitsize));
			/* IPDUバッファにシグナルデータを格納 */
			p_ipdu_inib->p_ipdu_buffer[byte_index] = (p_ipdu_inib->p_ipdu_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) (signal_data & ((uint32) mask)));
		}
	}

  error_exit:
	return;
}

/*
 *  アップデートビット設定
 */
LOCAL_INLINE void
set_updatebit(uint8 *p_buffer, uint16 updatebitposition)
{
	if (updatebitposition != COM_INVALID_UINT16) {
		p_buffer[updatebitposition / 8U] |= (uint8) (1U << (updatebitposition % 8U));
	}
}

/*
 *  アップデートビットクリア
 */
LOCAL_INLINE void
clear_updatebit(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB	*p_signal_inib;
	const SIGNAL_G_INIB	*p_signal_g_inib;
	Com_SignalIdType	i;

	COM_CHECK_NULL_POINTER(p_ipdu_inib != NULL_PTR, COMServiceId_clear_updatebit);

	/* 単独シグナル */
	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		COM_CHECK_NULL_POINTER((p_signal_inib != NULL_PTR) &&
							   (p_ipdu_inib->p_ipdu_buffer != NULL_PTR), COMServiceId_clear_updatebit);

		if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
			/* [COM059] 0:更新なし，1:更新あり */
			(p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComUpdateBitPosition / 8U] &= (uint8) (~((uint8) (1U << (p_signal_inib->ComUpdateBitPosition % 8U))));
		}
	}

	/* グループシグナル */
	for (i = 0U; i < p_ipdu_inib->tnum_signal_g; i++) {
		p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[i]);
		COM_CHECK_NULL_POINTER((p_signal_g_inib != NULL_PTR) &&
							   (p_ipdu_inib->p_ipdu_buffer != NULL_PTR), COMServiceId_clear_updatebit);

		if (p_signal_g_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
			/* [COM059] 0:更新なし，1:更新あり */
			(p_ipdu_inib->p_ipdu_buffer)[p_signal_g_inib->ComUpdateBitPosition / 8U] &= (uint8) (~((uint8) (1U << (p_signal_g_inib->ComUpdateBitPosition % 8U))));
		}
	}

  error_exit:
	return;
}

/*
 *  シグナルデータを前回値と比較
 */
LOCAL_INLINE boolean
check_tx_signal(const SIGNAL_INIB *p_signal_inib, const void *p_data)
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
			if (*((uint32 *) p_signal_inib->p_signal_buffer) != *((const uint32 *) p_data)) {
				ret = TRUE;
			}
			break;
#ifdef INT64_MAX
		case COM_FLOAT64:
			if (*((uint64 *) p_signal_inib->p_signal_buffer) != *((const uint64 *) p_data)) {
				ret = TRUE;
			}
			break;
#endif /* INT64_MAX */
		default:
			/*
			 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
			 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_check_tx_signal);
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
 *  バッファへのシグナルデータ格納
 */
LOCAL_INLINE void
set_buffer(void *write_buffer, uint8 type, uint16 length, const void *p_data)
{
	Com_SignalIdType i;

	if (write_buffer != NULL_PTR) {
		switch (type) {
		case COM_BOOLEAN:
			*((boolean *) write_buffer) = *((const boolean *) p_data);
			break;
		case COM_SINT8:
			*((sint8 *) write_buffer) = *((const sint8 *) p_data);
			break;
		case COM_SINT16:
			*((sint16 *) write_buffer) = *((const sint16 *) p_data);
			break;
		case COM_SINT32:
			*((sint32 *) write_buffer) = *((const sint32 *) p_data);
			break;
		case COM_UINT8:
			*((uint8 *) write_buffer) = *((const uint8 *) p_data);
			break;
		case COM_UINT16:
			*((uint16 *) write_buffer) = *((const uint16 *) p_data);
			break;
		case COM_UINT32:
			*((uint32 *) write_buffer) = *((const uint32 *) p_data);
			break;
		case COM_UINT8_N:
			for (i = 0U; i < length; i++) {
				((uint8 *) write_buffer)[i] = ((const uint8 *) p_data)[i];
			}
			break;
		case COM_FLOAT32:
			*((uint32 *) write_buffer) = *((const uint32 *) p_data);
			break;
#ifdef INT64_MAX
		case COM_FLOAT64:
			*((uint64 *) write_buffer) = *((const uint64 *) p_data);
			break;
#endif /* INT64_MAX */
		default:
			/*
			 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
			 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_set_buffer);
			break;
		}
	}

  error_exit:
	return;
}

/*
 *  TMS判定
 */
LOCAL_INLINE boolean
check_tms(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_G_INIB		*p_signal_g_inib;
	const SIGNAL_INIB		*p_signal_inib;
	const TX_SIGNAL_CB		*p_tx_signal_cb;
	Com_SignalIdType		i;
	Com_SignalGroupIdType	j;
	boolean					filter = FALSE;
	boolean					tms = FALSE;

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		/* [COM676] フィルタを持つシグナルのみTMCを判定する */
		if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
			filter = TRUE;

			p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
			COM_CHECK_NULL_POINTER(p_tx_signal_cb != NULL_PTR, COMServiceId_check_tms);

			/* [COM678][COM679] TMCが1つでもTRUEの場合は，TMSはTRUEとする */
			if (p_tx_signal_cb->tmc != FALSE) {
				tms = TRUE;
				break;
			}
		}
	}

	if (tms != TRUE) {
		for (j = 0U; j < p_ipdu_inib->tnum_signal_g; j++) {
			p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[j]);
			for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
				p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);
				/* [COM676] フィルタを持つシグナルのみTMCを判定する */
				if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
					filter = TRUE;
					p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
					COM_CHECK_NULL_POINTER(p_tx_signal_cb != NULL_PTR, COMServiceId_check_tms);

					/* [COM678][COM679] TMCが1つでもTRUEの場合は，TMSはTRUEとする */
					if (p_tx_signal_cb->tmc != FALSE) {
						tms = TRUE;
						break;
					}
				}
			}
			if (tms != FALSE) {
				break;
			}
		}
	}

	/* [COM677] フィルタを持つシグナルが存在しない場合は，TMSはTRUEとする */
	if (filter == FALSE) {
		tms = TRUE;
	}

  error_exit:
	return(tms);
}

/*
 *  送信モード切り替え
 */
LOCAL_INLINE void
switch_tx_mode(const IPDU_INIB *p_ipdu_inib, boolean tms)
{
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;
	TX_MODE_INIB		*p_cur_tx_mode_inib;
	uint8				transmit_mode;

	COM_CHECK_NULL_POINTER(p_ipdu_inib != NULL_PTR, COMServiceId_switch_tx_mode);

	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_cur_tx_mode_inib = (TX_MODE_INIB *) p_tx_ipdu_cb->p_cur_tx_mode_inib;

	transmit_mode = p_cur_tx_mode_inib->ComTxModeMode;

	COM_CHECK_NULL_POINTER(p_tx_ipdu_inib != NULL_PTR, COMServiceId_switch_tx_mode);
	COM_CHECK_NULL_POINTER(p_tx_ipdu_cb != NULL_PTR, COMServiceId_switch_tx_mode);

	/* [COM495][COM582] 送信モードが切り替わってもMDTには影響しない */
	/* [COM773] 送信モードが切り替わっても失敗送信リトライには影響しない */

	if ((tms != FALSE) && (p_cur_tx_mode_inib != p_tx_ipdu_inib->p_tx_mode_true_inib)) {
		/* [COM032] FALSEモード→TRUEモード */
		set_tx_mode(p_ipdu_inib, TRUE);
		p_cur_tx_mode_inib = (TX_MODE_INIB *) p_tx_ipdu_inib->p_tx_mode_true_inib;
	}
	else if ((tms == FALSE) && (p_cur_tx_mode_inib != p_tx_ipdu_inib->p_tx_mode_false_inib)) {
		/* [COM032] TRUEモード→FALSEモード */
		set_tx_mode(p_ipdu_inib, FALSE);
		p_cur_tx_mode_inib = (TX_MODE_INIB *) p_tx_ipdu_inib->p_tx_mode_false_inib;
	}
	else {
		/* [COMa018] 送信モードが切り替わらない場合，何もしない */
	}

  error_exit:
	return;
}

/*
 *  送信モード設定
 */
LOCAL_INLINE void
set_tx_mode(const IPDU_INIB *p_ipdu_inib, boolean tms)
{
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	COM_CHECK_NULL_POINTER(p_ipdu_inib != NULL_PTR, COMServiceId_set_tx_mode);

	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	COM_CHECK_NULL_POINTER(p_tx_ipdu_inib != NULL_PTR, COMServiceId_set_tx_mode);
	COM_CHECK_NULL_POINTER(p_tx_ipdu_cb != NULL_PTR, COMServiceId_set_tx_mode);

	if (tms != FALSE) {
		COM_CHECK_NULL_POINTER(p_tx_ipdu_inib->p_tx_mode_true_inib != NULL_PTR, COMServiceId_set_tx_mode);
		p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
	}
	else {
		COM_CHECK_NULL_POINTER(p_tx_ipdu_inib->p_tx_mode_false_inib != NULL_PTR, COMServiceId_set_tx_mode);
		p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
	}

	/* [COM244][COM495] 送信モード関連カウンタをリセット */
	p_tx_ipdu_cb->interval_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeRepetitionPeriod;
	p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
	p_tx_ipdu_cb->repeat_cnt = 0U;
	p_tx_ipdu_cb->queuing_cnt = 0U;
	p_tx_ipdu_cb->dm_mf_cnt = 0U;

	/* IPDUの状態をリセット */
	IPDU_CLEAR_NOTICED(p_ipdu_inib->p_state);
	IPDU_CLEAR_DIRECT_SEND(p_ipdu_inib->p_state);
	IPDU_CLEAR_FIRST_DIRECT_SEND(p_ipdu_inib->p_state);
	IPDU_CLEAR_DM(p_ipdu_inib->p_state);

  error_exit:
	return;
}

/*
 *  受信処理
 */
LOCAL_INLINE void
receive_ipdu(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB	*p_signal_inib;
	const SIGNAL_G_INIB	*p_signal_g_inib;
	uint16				i;
	uint16				j;
	boolean				is_invalid;
	UINT_MAX			unpack_data;            /* 最大サイズ */
	void				*p_unpack_data;         /* ipduから取得したデータを入れるポインタ */

	/*
	 * シグナル処理
	 */
	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		/* [COM324] アップデートビットが更新されている場合，フィルタリング，通知，アンパッキング等の処理を実施する */
		if (check_updatebit(p_ipdu_inib->p_ipdu_buffer, p_signal_inib->ComUpdateBitPosition) != FALSE) {
			/*シグナルをIPDUバッファから取り出してアンパッキング*/
			get_ipdu_buffer(p_signal_inib, &unpack_data, &p_unpack_data);
			/*
			 *  [COM396] 受信したシグナルに対して以下の順で処理する
			 *           1) 無効値処理
			 *           2) フィルタリング
			 *           3) 通知
			 */
			/*
			 * 無効値処理([COM680][COM717] RTEへ通知する場合は受信処理や受信完了通知を行わない)
			 * [COM736] ComDataInvalidActionが設定されていなければ，有効な値が受信されているものとみなす
			 */
			if ((p_signal_inib->ComDataInvalidAction == COM_INVALID_UINT8) || (check_invalid(p_signal_inib, p_unpack_data) != FALSE)) {
				/* [COM273][COM695] フィルタリング結果がfalseの場合，シグナルを破棄し，そのシグナルに対する処理を行わない */
				if ((p_signal_inib->ComFilterAlgorithm == COM_INVALID_UINT8) || (filtering(p_signal_inib, p_unpack_data) != FALSE)) {
					/* データが有効値 */
					set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_unpack_data);
					/* [COM574] 完全に受信したシグナルに対してComNotificationに設定した関数を呼ぶ */
					call_cbk(p_signal_inib->ComNotification, COMServiceId_receive_ipdu);
				}
			}
			else {
				/* [COM680][COM717] ComInvalidNotificationにてRTEへ通知し，フィルタリング，シグナル通知，シグナルバッファへの格納は実施しない */
				if (p_signal_inib->ComDataInvalidAction == COM_NOTIFY) {
					call_cbk(p_signal_inib->ComInvalidNotification, COMServiceId_receive_ipdu);
				}
				/* [COM681] COM_REPLACEの場合，ComSignalInitValueでシグナルを更新する */
				else if (p_signal_inib->ComDataInvalidAction == COM_REPLACE) {
					set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
					/* [COM681] 有効な値を受信したかのように受信完了通知を行う */
					call_cbk(p_signal_inib->ComNotification, COMServiceId_receive_ipdu);
				}
				else {
					/* ComDataInvalidActionがCOM_INVALID_UINT8のときはこの条件には当てはまらない． */
				}
			}
		}
	}

	/*
	 * シグナルグループ処理
	 */
	for (i = 0U; i < p_ipdu_inib->tnum_signal_g; i++) {
		/* 無効値有りフラグを初期化 */
		is_invalid = FALSE;
		p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[i]);

		/* [COM324] シグナルグループのアップデートビットが更新されている場合通知の処理を実施する */
		if (check_updatebit(p_ipdu_inib->p_ipdu_buffer, p_signal_g_inib->ComUpdateBitPosition) != FALSE) {
			/* 無効値判定 [COM682][COM683][COM718][COM737] */
			/* グループシグナルが1つでも無効値であればシグナルグループ全体に無効値処理を実施する */
			if (p_signal_g_inib->ComDataInvalidAction != COM_INVALID_UINT8) {
				for (j = 0U; j < p_signal_g_inib->tnum_g_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[j]);
					if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
						/*グループシグナルデータをIPDUバッファから取り出してアンパッキング*/
						get_ipdu_buffer(p_signal_inib, &unpack_data, &p_unpack_data);
						if (check_invalid(p_signal_inib, p_unpack_data) == FALSE) {
							is_invalid = TRUE;
							break;
						}
					}
				}
			}

			/* シグナルグループ内の全グループシグナルが有効値（無効値が無い） */
			if (is_invalid == FALSE) {
				for (j = 0U; j < p_signal_g_inib->tnum_g_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[j]);
					/*グループシグナルデータをIPDUバッファから取り出してアンパッキング*/
					get_ipdu_buffer(p_signal_inib, &unpack_data, &p_unpack_data);
					p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[j]);
					set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_unpack_data);
				}
				/* [COM575][COM053] 完全に受信したシグナルグループに対してComNotificationに設定した関数を呼ぶ */
				call_cbk(p_signal_g_inib->ComNotification, COMServiceId_receive_ipdu);
			}
			/* シグナルグループ内のグループシグナルのいずれかが無効値 */
			else {
				/* [COM682][COM718]RTEに通知する */
				if (p_signal_g_inib->ComDataInvalidAction == COM_NOTIFY) {
					/* [COM680][COM717] ComInvalidNotificationにてRTEへ通知し，シグナル通知，シグナルバッファへの格納は実施しない */
					call_cbk(p_signal_g_inib->ComInvalidNotification, COMServiceId_receive_ipdu);
				}
				/* [COM683] グループシグナルの初期値をシグナルバッファに格納 */
				else if (p_signal_g_inib->ComDataInvalidAction == COM_REPLACE) {
					for (j = 0U; j < p_signal_g_inib->tnum_g_signal; j++) {
						p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[j]);
						set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
					}
					/* [COM683] 有効な値を受信したかのように受信完了通知を行う */
					call_cbk(p_signal_g_inib->ComNotification, COMServiceId_receive_ipdu);
				}
				else {
					/*
					 * ComDataInvalidActionが設定されていない場合，is_invalidがtrueとなることはないので，この条件に当てはまることはない．
					 */
				}
			}
		}
	}

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
	PduLengthType	byte_index;     /* LSBのByte位置 */
	uint8			pos_lsb;        /* LSBのBit位置 */
	uint8			bitsize;
	uint8			left_size;      /* アンパックするシグナルの残りサイズ */
	sint8			byte_direction; /* byte_indexの移動方向 */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	pos_lsb = (uint8) (p_signal_inib->ComBitPositionLsb % 8U);
	byte_index = p_signal_inib->ComBitPositionLsb / 8U;
	bitsize = p_signal_inib->ComBitSize;

	COM_CHECK_PARAM((p_signal_inib->ComSignalEndianness != COM_OPAQUE) &&
					((p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) ||
					 (p_signal_inib->ComSignalEndianness == COM_BIG_ENDIAN)), COMServiceId_unpacking);

	/* byte_indexの移動方向を算出 */
	if (p_signal_inib->ComSignalEndianness == COM_BIG_ENDIAN) {
		byte_direction = -1;
	}
	else {
		byte_direction = 1;
	}

	/* 格納範囲が1Byte以内である場合 */
	if ((pos_lsb + bitsize) <= 8U) {
		/* シグナルデータにIPDUバッファのデータを格納 */
		*(UINT_MAX *) p_data = (UINT_MAX) (((p_ipdu_inib->p_ipdu_buffer)[byte_index] >> pos_lsb) & (0xFFU >> (8U - bitsize)));
	}
	else {
		/* シグナルデータにIPDUバッファのデータを格納 */
		*(UINT_MAX *) p_data = (UINT_MAX) ((p_ipdu_inib->p_ipdu_buffer)[byte_index] >> pos_lsb);

		/* シグナルの残りサイズを算出 */
		left_size = bitsize - (8U - pos_lsb);

		byte_index += (PduLengthType) byte_direction;

		/* シグナルの残りサイズが1Byte以上である場合 */
		while (left_size >= 8U) {
			/* シグナルデータにIPDUバッファのデータを，ここまでに格納したビット分左シフトして格納 */
			*(UINT_MAX *) p_data += (((UINT_MAX) ((p_ipdu_inib->p_ipdu_buffer)[byte_index])) << (bitsize - left_size));

			left_size -= 8U;

			byte_index += (PduLengthType) byte_direction;
		}

		/* シグナルの残りサイズがある場合 */
		if (left_size != 0U) {
			/* シグナルデータにIPDUバッファのデータを，ここまでに格納したビット分左シフトして格納 */
			*(UINT_MAX *) p_data += ((UINT_MAX) (((p_ipdu_inib->p_ipdu_buffer)[byte_index]) & (0xFFU >> (8U - left_size))) << (bitsize - left_size));
		}
	}

	/* [COM008] 受信側では符号拡張する */
	/* [COM352] フィルタリングと通知検出を行う前に符号拡張とエンディアン変換を行う */
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
 * 無効値に対する処理（シグナル）
 */
LOCAL_INLINE boolean
check_invalid(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	boolean	is_invalid = FALSE;
	uint16	i;

	COM_CHECK_PARAM((p_signal_inib->ComDataInvalidAction == COM_NOTIFY) ||
					(p_signal_inib->ComDataInvalidAction == COM_REPLACE) ||
					(p_signal_inib->ComDataInvalidAction == COM_INVALID_UINT8), COMServiceId_check_invalid);

	if (p_signal_inib->ComSignalDataInvalidValue != NULL_PTR) {
		switch (p_signal_inib->ComSignalType) {
		case COM_BOOLEAN:
			if (*((const boolean *) p_signal_inib->ComSignalDataInvalidValue) != *((boolean *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_SINT8:
			if (*((const sint8 *) p_signal_inib->ComSignalDataInvalidValue) != *((sint8 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_SINT16:
			if (*((const sint16 *) p_signal_inib->ComSignalDataInvalidValue) != *((sint16 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_SINT32:
			if (*((const sint32 *) p_signal_inib->ComSignalDataInvalidValue) != *((sint32 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_UINT8:
			if (*((const uint8 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint8 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_UINT16:
			if (*((const uint16 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint16 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_UINT32:
			if (*((const uint32 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint32 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
		case COM_UINT8_N:
			for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
				if ((((const uint8 *) p_signal_inib->ComSignalDataInvalidValue)[i]) != (((uint8 *) p_data)[i])) {
					is_invalid = TRUE;
					break;
				}
			}
			break;
		case COM_FLOAT32:
			if (*((const uint32 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint32 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
#ifdef INT64_MAX
		case COM_FLOAT64:
			if (*((const uint64 *) p_signal_inib->ComSignalDataInvalidValue) != *((uint64 *) p_data)) {
				is_invalid = TRUE;
			}
			break;
#endif /* INT64_MAX */
		default:
			/*
			 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
			 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_check_invalid);
			break;
		}
	}
	else {
		/* NULL_PTRの場合，無効値ではないものとして扱う */
		is_invalid = TRUE;
	}

  error_exit:
	return(is_invalid);
}

/*
 *  アップデートビット更新チェック
 */
LOCAL_INLINE boolean
check_updatebit(const uint8 *read_buffer, uint16 bitposition)
{
	PduLengthType	index_update;               /* ComUpdateBitPositionが所属するIPDUのByte位置 */
	uint8			pos_update;                 /* ComUpdateBitPositionのBit位置 */
	boolean			updated;

	/* シグナル */
	if (bitposition != COM_INVALID_UINT16) {
		index_update = bitposition / 8U;
		pos_update = (uint8) (bitposition % 8U);
		/* [COM067] アップデートビットに値が設定されていれば，シグナルは更新されたものとする */
		if (((read_buffer)[index_update] & ((uint8) (1U << pos_update))) != 0U) {
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
 *  バッファからのシグナルデータ取り出し
 */
LOCAL_INLINE void
get_buffer(const void *read_buffer, uint8 type, uint16 length, void *p_data)
{
	uint16 i;

	/* シグナルデータの取り出しは受信時のみであるので必ずバッファは存在する */
	COM_CHECK_PARAM(read_buffer != NULL_PTR, COMServiceId_get_buffer);

	switch (type) {
	case COM_BOOLEAN:
		*((boolean *) p_data) = *((boolean *) read_buffer);
		break;
	case COM_SINT8:
		*((sint8 *) p_data) = *((sint8 *) read_buffer);
		break;
	case COM_SINT16:
		*((sint16 *) p_data) = *((sint16 *) read_buffer);
		break;
	case COM_SINT32:
		*((sint32 *) p_data) = *((sint32 *) read_buffer);
		break;
	case COM_UINT8:
		*((uint8 *) p_data) = *((uint8 *) read_buffer);
		break;
	case COM_UINT16:
		*((uint16 *) p_data) = *((uint16 *) read_buffer);
		break;
	case COM_UINT32:
		*((uint32 *) p_data) = *((uint32 *) read_buffer);
		break;
	case COM_UINT8_N:
		for (i = 0U; i < length; i++) {
			((uint8 *) p_data)[i] = ((uint8 *) read_buffer)[i];
		}
		break;
	case COM_FLOAT32:
		*((float32 *) p_data) = *((float32 *) read_buffer);
		break;
#ifdef INT64_MAX
	case COM_FLOAT64:
		*((float64 *) p_data) = *((float64 *) read_buffer);
		break;
#endif /* INT64_MAX */
	default:
		/*
		 *  本関数の引数にCOM_BOOLEAN，COM_SINT8，COM_SINT16，COM_SINT32，COM_UINT8，COM_UINT16，
		 *  COM_UINT32，COM_UINT8_N，COM_FLOAT32，COM_FLOAT64以外が指定されることはない
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_get_buffer);
		break;
	}

  error_exit:
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
	const SIGNAL_G_INIB	*p_signal_g_inib;
	RX_SIGNAL_CB		*p_rx_signal_cb;
	RX_SIGNAL_G_CB		*p_rx_signal_g_cb;
	boolean				is_dm = FALSE;

	/* シグナル処理 */
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

	/* シグナルグループ処理 */
	for (i = 0U; i < p_ipdu_inib->tnum_signal_g; i++) {
		p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[i]);
		p_rx_signal_g_cb = (RX_SIGNAL_G_CB *) p_signal_g_inib->p_signal_g_cb;

		/* [COM333] ComTimeoutが0または，省略されている場合，そのシグナルグループのDM監視はしない */
		if (p_rx_signal_g_cb != NULL_PTR) {
			if (p_signal_g_inib->ComFirstTimeout == 0U) {
				/* [COM716] ComFirstTimeoutが0または，省略されている場合，最初の受信が行われるまで，そのシグナルグループのDM監視はしない */
				p_rx_signal_g_cb->dm_state = COM_WAIT;
			}
			else {
				/* [COM224] ComFirstTimeoutを設定する */
				p_rx_signal_g_cb->dm_mf_cnt = p_signal_g_inib->ComFirstTimeout;
				p_rx_signal_g_cb->dm_state = COM_START;
			}

			is_dm = TRUE;
		}
	}

	if (is_dm != FALSE) {
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
	const SIGNAL_G_INIB	*p_signal_g_inib;
	RX_SIGNAL_CB		*p_rx_signal_cb;
	RX_SIGNAL_G_CB		*p_rx_signal_g_cb;

	/* シグナル処理 */
	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
		p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

		if (p_rx_signal_cb != NULL_PTR) {
			/* シグナルのDM監視を停止する */
			p_rx_signal_cb->dm_state = COM_STOP;
		}
	}

	/* シグナルグループ処理 */
	for (i = 0U; i < p_ipdu_inib->tnum_signal_g; i++) {
		p_signal_g_inib = GET_SIGNAL_G_INIB((p_ipdu_inib->p_signalgid_list)[i]);
		p_rx_signal_g_cb = (RX_SIGNAL_G_CB *) p_signal_g_inib->p_signal_g_cb;

		if (p_rx_signal_g_cb != NULL_PTR) {
			/* シグナルグループのDM監視を停止する */
			p_rx_signal_g_cb->dm_state = COM_STOP;
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
check_rx_dm(const SIGNAL_INIB *p_signal_inib)
{
	RX_SIGNAL_CB *p_rx_signal_cb;

	/* シグナル用処理 */
	p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

	if (p_rx_signal_cb != NULL_PTR) {
		if (p_rx_signal_cb->dm_state == COM_START) {
			/* dm_mf_cntは必ず0より大きい値が設定されている */
			p_rx_signal_cb->dm_mf_cnt--;

			/* シグナルの受信DMが有効なDMカウンタを判定する */
			if (p_rx_signal_cb->dm_mf_cnt == 0U) {
				if (p_signal_inib->ComRxDataTimeoutAction == COM_REPLACE) {
					/* [COM470] シグナルの値をComSignalInitValueに置き換える */
					set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
				}
				/* [COM500] COM_NONEまたは省略されている場合は，何もしない */

				/* [COM744] タイムアウト通知 */
				call_cbk(p_signal_inib->ComTimeoutNotification, COMServiceId_check_rx_dm);

				p_rx_signal_cb->dm_mf_cnt = p_signal_inib->ComTimeout;
			}
		}
	}

	return;
}

/*
 *  受信シグナルグループDM判定
 */
LOCAL_INLINE void
check_rx_g_dm(const SIGNAL_G_INIB *p_signal_g_inib)
{
	const SIGNAL_INIB	*p_signal_inib;
	RX_SIGNAL_G_CB		*p_rx_signal_g_cb;
	Com_SignalIdType	i;

	p_rx_signal_g_cb = (RX_SIGNAL_G_CB *) p_signal_g_inib->p_signal_g_cb;

	if (p_rx_signal_g_cb != NULL_PTR) {
		if (p_rx_signal_g_cb->dm_state == COM_START) {
			/* dm_mf_cntは必ず0より大きい値が設定されている */
			p_rx_signal_g_cb->dm_mf_cnt--;

			/* シグナルグループの受信DMが有効なDMカウンタを判定する */
			if (p_rx_signal_g_cb->dm_mf_cnt == 0U) {
				if (p_signal_g_inib->ComRxDataTimeoutAction == COM_REPLACE) {

					for (i = 0U; i < p_signal_g_inib->tnum_g_signal; i++) {
						p_signal_inib = GET_SIGNAL_INIB((p_signal_g_inib->p_gsignalid_list)[i]);
						/* [COM393] 受信タイムアウト発生によりシグナルまたはシグナルグループの値を初期値(ComSignalInitValue) に置き換えたとしても，フィルタリングのための前回値(old_value)は更新しない */
						/* [COM470][COM513] シグナルバッファをComSignalInitValueに置き換える */
						set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
					}
					/* [COM500] COM_NONEまたは省略されている場合は，何もしない */

				}
				/* [COM744] タイムアウト通知 */
				call_cbk(p_signal_g_inib->ComTimeoutNotification, COMServiceId_check_rx_g_dm);

				p_rx_signal_g_cb->dm_mf_cnt = p_signal_g_inib->ComTimeout;

			}
		}
	}

	return;
}

LOCAL_INLINE void
check_signal_filtering(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{

	const IPDU_INIB		*p_ipdu_inib;
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;
	TX_SIGNAL_CB		*p_tx_signal_cb;
	TX_SIGNAL_G_CB		*p_tx_signal_g_cb;
	boolean				changed;
	boolean				change_tmc;
	boolean				tms;

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
	p_tx_signal_g_cb = (TX_SIGNAL_G_CB *) p_signal_inib->p_signal_g_cb;

	/* シグナルデータを比較 */
	changed = check_tx_signal(p_signal_inib, p_data);

	if (changed != FALSE) {
		if (p_signal_inib->p_shadow_buffer == NULL_PTR) {
			/* [COM334][COM221] IPDUが停止中でもバッファの更新(パッキング)を行う */
			packing(p_signal_inib, p_data);
			/* [COM353]送信側では符号拡張しない */
			set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_data);

			p_tx_signal_cb->change_signal_flg = TRUE;
		}
		else {
			/* [COMa010] シャドウバッファにシグナルデータを格納 */
			set_buffer(p_signal_inib->p_shadow_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_data);
			if (p_signal_inib->ComTransferProperty == COM_TRIGGERED_ON_CHANGE) {
				p_tx_signal_g_cb->change_signal_g_flg = TRUE;
			}
		}
	}

	if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
		/* 単独シグナル処理 */
		if (p_signal_inib->p_shadow_buffer == NULL_PTR) {
			change_tmc = p_tx_signal_cb->tmc;

			/* [COM602] TMC判定 */
			p_tx_signal_cb->tmc = filtering(p_signal_inib, p_data);

			/* [COM605][COM326] TMS判定 */
			if (change_tmc != p_tx_signal_cb->tmc) {
				if (p_tx_signal_cb->tmc != FALSE) {
					p_tx_ipdu_cb->tmc_true_cnt++;
				}
				else {
					p_tx_ipdu_cb->tmc_true_cnt--;
				}
			}
			/* [COM245] */
			tms = check_count_tms(p_tx_ipdu_cb->tmc_true_cnt);
			switch_tx_mode(p_ipdu_inib, tms);
		}
	}

	return;
}

LOCAL_INLINE void
call_cbk(void (*cbk_notification)(void), uint8 serviceid)
{
	const Com_ConfigType *p_saved_config;

	if (cbk_notification != NULL_PTR) {
		/* 排他エリア内でコールバックのポインタを取り出す */
		/* 再初期化チェック用に現在のコンフィギュレーション情報を保持 */
		p_saved_config = p_cur_com_config;

		/* 送信エラー通知 */
		SchM_Exit_Com_Reentrant_0();
		(*cbk_notification)();
		SchM_Enter_Com_Reentrant_0();

		/* 排他エリア外でコンフィギュレーション情報が変化していないかチェックする */
		COM_CHECK_PARAM(p_saved_config == p_cur_com_config, serviceid);
	}
  error_exit:
	return;
}

LOCAL_INLINE void
init_send_signal(const SIGNAL_INIB *p_signal_inib)
{

	const IPDU_INIB	*p_ipdu_inib;
	TX_IPDU_CB		*p_tx_ipdu_cb;
	TX_SIGNAL_CB	*p_tx_signal_cb;

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	/* [COM217] IPDUバッファにComSignalInitValueを設定する */
	packing(p_signal_inib, p_signal_inib->ComSignalInitValue);
	/* [COM228] シグナルバッファにComSignalInitValueを格納する */
	/* [COM353] 送信側では符号拡張しない */
	set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
	/* [COM603][COM604] フィルタバッファにComSignalInitValueを格納する */
	set_filter_buffer(p_signal_inib, p_signal_inib->ComSignalInitValue);

	/* tmc初期化 */
	if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
		p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
		COM_CHECK_NULL_POINTER(p_tx_signal_cb != NULL_PTR, COMServiceId_init_send_signal);
		if (p_signal_inib->ComFilterAlgorithm != COM_ONE_EVERY_N) {
			p_tx_signal_cb->tmc = filtering(p_signal_inib, p_signal_inib->ComSignalInitValue);
		}
		else {
			p_tx_signal_cb->tmc = FALSE;
		}
		if (p_tx_signal_cb->tmc != FALSE) {
			p_tx_ipdu_cb->tmc_true_cnt++;
		}
	}

  error_exit:
	return;
}

LOCAL_INLINE void
init_receive_signal(const SIGNAL_INIB *p_signal_inib)
{
	/* シグナルバッファにComSignalInitValueを格納する */
	set_buffer(p_signal_inib->p_signal_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);

	if (p_signal_inib->p_shadow_buffer != NULL_PTR) {
		/* [COM461] シャドウバッファにComSignalInitValueを格納する */
		set_buffer(p_signal_inib->p_shadow_buffer, p_signal_inib->ComSignalType, p_signal_inib->ComSignalLength, p_signal_inib->ComSignalInitValue);
	}

	/* [COM603] フィルタバッファにComSignalInitValueを格納する */
	set_filter_buffer(p_signal_inib, p_signal_inib->ComSignalInitValue);

	return;
}

/*
 *  受信シグナルDMリセット
 */
LOCAL_INLINE void
reset_rx_dm(uint8 *dm_state, uint32 *dm_mf_cnt, uint32 comtimeout)
{
	/* [NCOM031] アップデートビットがセットされているシグナルを受信した場合，そのシグナルの受信DMタイマはリセットされる */
	if (*dm_state != COM_STOP) {
		/* シグナルの受信デッドラインタイマが有効であればリセットする */
		*dm_mf_cnt = comtimeout;

		if (*dm_state == COM_WAIT) {
			*dm_state = COM_START;
		}
	}
}

/*
 * IPDUバッファからデータ取得
 */
LOCAL_INLINE void
get_ipdu_buffer(const SIGNAL_INIB *p_signal_inib, const UINT_MAX *buffer, void **p_data)
{
	const IPDU_INIB	*p_ipdu_inib;

	typedef union {
		uint8 u8;
		uint16 u16;
		uint32 u32;
		sint8 s8;
		sint16 s16;
		sint32 s32;
		boolean b;
		float32 f32;
		float64 f64;
	} signal_type;

	UINT_MAX		temp_data;      /* 最大サイズ */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;

	if (p_signal_inib->ComSignalEndianness == COM_OPAQUE) {
		/* COM_UINT8_NはバイトアラインされているのでIPDUバッファをそのまま使用する */
		*p_data = (void *)&((p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComBitPositionLsb / 8U]);
	}
	else {
		/* COM_UINT8_N以外は一時バッファにアンパッキング */
		unpacking(p_signal_inib, &temp_data);
		*p_data = (void *) buffer;

		switch (p_signal_inib->ComSignalType)
		{
		case COM_UINT8:
			**(uint8 **)p_data = (((signal_type*)(&temp_data))->u8);
			break;
		case COM_UINT16:
			**(uint16 **)p_data = (((signal_type*)(&temp_data))->u16);
			break;
		case COM_UINT32:
			**(uint32 **)p_data = (((signal_type*)(&temp_data))->u32);
			break;
		case COM_SINT8:
			**(sint8 **)p_data = (((signal_type*)(&temp_data))->s8);
			break;
		case COM_SINT16:
			**(sint16 **)p_data = (((signal_type*)(&temp_data))->s16);
			break;
		case COM_SINT32:
			**(sint32 **)p_data = (((signal_type*)(&temp_data))->s32);
			break;
		case COM_BOOLEAN:
			**(boolean **)p_data = (((signal_type*)(&temp_data))->b);
			break;
		case COM_FLOAT32:
			**(float32 **)p_data = (((signal_type*)(&temp_data))->f32);
			break;
#ifdef INT64_MAX
		case COM_FLOAT64:
			**(float64 **)p_data = (((signal_type*)(&temp_data))->f64);
			break;
#endif
		default:
			break;
		}
	}

	return;
}

LOCAL_INLINE void
set_repeat_cnt(const IPDU_INIB *p_ipdu_inib, uint8 trans_property, boolean change_signal)
{

	TX_IPDU_CB *p_tx_ipdu_cb;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	/* [COM279] COM_DIRECT,COM_MIXED */
	if ((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_DIRECT) ||
		(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_MIXED)) {

		/* [COM742] 送信グループシグナルの送信プロパティの多重度は1なので実装しない */
		/* [COM330][COM734][COM741][COM743] */
		if ((trans_property == COM_TRIGGERED) ||
			((trans_property == COM_TRIGGERED_ON_CHANGE) &&
			 (change_signal != FALSE))) {

			/*
			 * 現状の実装では，ComTxModeNumberOfRepetitionsが0の場合は，繰り返し送信を行わないが，
			 * 1の場合においても，繰り返し送信を行わないことを想定（0の場合と同等と）している．
			 * MFTxでの送信成功後において，repeat_cntが0であることで，以降の繰り返し送信が無いことを
			 * 判定しているため，ComTxModeNumberOfRepetitionsが1の場合は，repeat_cntに0を設定しておく．
			 */
			if (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions != 1U) {
				p_tx_ipdu_cb->repeat_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions;
			}
			else {
				p_tx_ipdu_cb->repeat_cnt = 0U;
			}

			p_tx_ipdu_cb->interval_mf_cnt = 0U;

			/* [NCOM006] 直接送信ビットを設定 */
			IPDU_SET_DIRECT_SEND(p_ipdu_inib->p_state);
			IPDU_SET_FIRST_DIRECT_SEND(p_ipdu_inib->p_state);

			/*
			 * [COM739] 送信モードがDIRECTであり，かつ，繰り返し送信を行う場合，
			 * 新しい送信要求が起こった際に送信DMをリセットする
			 */
			if ((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
				(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions > 0U)) {
				IPDU_CLEAR_DM(p_ipdu_inib->p_state);
			}
		}
		/* [COM767][COM768][COM769][COM770][NCOM098] */
		else if ((trans_property == COM_TRIGGERED_WITHOUT_REPETITION) ||
				 ((trans_property == COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION) &&
				  (change_signal != FALSE))) {

			/*
			 * [COM467] 1回のみ送信する
			 * N回送信設定の場合は1回のみ送信を設定しない
			 */
			if (!(p_tx_ipdu_cb->repeat_cnt > 0U)) {
				p_tx_ipdu_cb->repeat_cnt = 0U;
			}

			p_tx_ipdu_cb->interval_mf_cnt = 0U;

			/* [NCOM006] 直接送信ビットを設定 */
			IPDU_SET_DIRECT_SEND(p_ipdu_inib->p_state);
			IPDU_SET_FIRST_DIRECT_SEND(p_ipdu_inib->p_state);
		}
		else {
			/* [NCOM099] COM_PENDING: 何もしない */
		}
	}
	return;
}

LOCAL_INLINE
boolean
check_count_tms(uint16 true_count)
{
	boolean tms;

	if (true_count == 0U) {
		tms = FALSE;
	}
	else {
		tms = TRUE;
	}

	return(tms);
}

/*
 *  以下，未サポート機能
 */

/* <COM627><COM628><COM629><COM630><NCOM085><NCOM086><NCOM087> */
uint8
Com_SendDynSignal(Com_SignalIdType SignalId, const void *SignalDataPtr, uint16 Length)
{
	return(0U);
}
/* <COM690><COM711><COM712><COM724><NCOM088><NCOM089><NCOM090> */
uint8
Com_ReceiveDynSignal(Com_SignalIdType SignalId, void *SignalDataPtr, uint16 *Length)
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
