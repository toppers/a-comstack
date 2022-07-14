/*
 *  TOPPERS/A-CAN
 *      Automotive CAN
 *
 *  Copyright (C) 2014 by FUJI SOFT INCORPORATED, JAPAN
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
 *  $Id: Can.c 1388 2015-06-04 05:48:42Z fsi-kaitori $
 */

/* [CAN034][CAN036][CAN394][CAN397][CAN390] */
/* [CAN222] Canモジュールで必要なデータ型が定義されたヘッダファイル */
#include "Os.h"
#include "ComStack_Types.h"
#include "Can.h"
#include "CanIf_Cbk.h"
#include "MemMap.h"
#include "EcuM_Cbk.h"

/*
 * (CAN077) CANコントローラ仕様に依存した実装を行う
 * (CAN284) 1つECUで複数の異なるCANコントローラを使用する場合も，1つの依存部で対応する
 * (CAN385) 1つECUで複数の異なるCANコントローラを使用する場合，AUTOSAR規定のネーミングコンベンションに従う
 * (CAN386) 1種類のCANコントローラのみを使用する場合，独自のネーミングコンベンションでよい
 * (CAN238) オンチップのCANコントローラを使用する場合，他のドライバのサービスを使用しない
 * (CAN242) オフチップのCANコントローラを使用する場合，MCALのサービスを使用する
 * (CAN244) MCALから呼び出されるようなコールバックは提供しない
 * (CAN391) オフチップのCANコントローラを使用する場合，Spi.hをincludeする
 * (CAN204) 依存部の各関数内で割込み禁止許可を行う場合，
 *          ネスト呼出し回数管理に従い，正しい割込み禁止状態を維持する
 */
#include "Can_Target.h"

/* SchM_Can.hはRTEジェネレータにより生成される */
/* [CAN034][CAN406] */
#include "SchM_Can.h"

#if CAN_DEV_ERROR_DETECT == STD_ON
/* [CAN034][CAN393] */
#include "Det.h"
#endif /* CAN_DEV_ERROR_DETECT == STD_ON */


/*
 *  現在実行中のCanコンフィギュレーション情報
 */
const Can_ConfigType			*p_cur_can_config;
const Can_HohBoxType			*p_cur_hoh_box_table;
const CAN_CTRL_INIB				*p_cur_can_ctrl_inib_table;

/* [CAN103] Canの初期化状態(CAN_UNINITで初期化) */
static uint8					can_init_flg = CAN_UNINIT;

/* 割込み禁止ネストカウント */
extern uint8					can_interrupt_nested_cnt[];

/* コールアウト関数 */
#ifdef USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION
extern const Can_LpduCallout	CanLpduCalloutFunction;
#endif /* USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION */

/* Can_SetControllerMode動作状態フラグ */
extern boolean					can_set_controller_mode_flg[];

/* CANコントローラ状態情報 */
extern Can_StateTransitionType	can_current_state[];

/*
 *  内部関数プロトタイプ宣言
 */
static boolean can_check_timeout_duration(uint8 Controller, Can_StateTransitionType Transition);

/*
 *  [CAN223] Can_Init
 */
void
Can_Init(const Can_ConfigType *Config)
{
	Can_HwHandleType	hth_idx;
	Can_HwHandleType	hrh_idx;
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN026] 既に初期化済みの場合はエラー */
	if (can_init_flg == CAN_READY) {
		goto error_exit;
	}

	/* [CAN175] NULLチェック */
	if (Config == NULL_PTR) {
		/* [NCAN003] NULL_PTRの場合，先頭のコンフィギュレーション情報を使用する */
		Config = &can_config[0];
	}

	/* [CAN056] 引数から実行するコンフィグレーション情報を取得 */
	p_cur_can_config = Config;
	p_cur_hoh_box_table = Config->p_hoh_box_table;
	p_cur_can_ctrl_inib_table = Config->p_can_ctrl_inib_table;

	/*
	 * (CAN407) 以下，各依存部関数で必要なレジスタの初期化を行う
	 * (CAN419) 使用しない全てのCAN割込みは無効にする
	 * (CAN236)(CAN237) リモート送信要求を無視するように初期化を行う
	 * (CAN239) CANコントローラで使用する全てのハードウェアリソースを初期化する
	 * (CAN259) コントローラをSTOPPED状態にする
	 */

	/* [CAN245][CAN250] unit_phase1 */
	if (can_target_init_unit_phase1(p_cur_can_config) == FALSE) {
		goto error_exit;
	}

	/* [CAN245][CAN250][CAN053] 使用する全てのコントローラに対する初期化処理 */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* CANコントローラ管理ブロック取得 */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);

		/* controller_phase1 */
		if (can_target_init_controller_phase1(ctrl_id, p_ctrl_inib) == FALSE) {
			goto error_exit;
		}

		/* デフォルトボーレートを設定する */
		can_target_change_baudrate(ctrl_id, p_ctrl_inib->p_default_baudrate);

		/* controller_phase2 */
		if (can_target_init_controller_phase2(ctrl_id, p_ctrl_inib) == FALSE) {
			goto error_exit;
		}

		/* 受信メールボックス初期化 */
		for (hrh_idx = 0U; hrh_idx < GET_HRH_NUM(ctrl_id); hrh_idx++) {
			if (can_target_rbox_initialize(ctrl_id, p_ctrl_inib, hrh_idx) == FALSE) {
				goto error_exit;
			}
		}

		/* 送信メールボックス初期化 */
		for (hth_idx = 0U; hth_idx < GET_HTH_NUM(ctrl_id); hth_idx++) {
			if (can_target_tbox_initialize(ctrl_id, p_ctrl_inib, hth_idx) == FALSE) {
				goto error_exit;
			}

			/* HTHのミューテックス初期化 */
			p_ctrl_inib->p_can_hth_cb_table[hth_idx].mutex = FALSE;
		}

		/* controller_phase3 */
		if (can_target_init_controller_phase3(ctrl_id, p_ctrl_inib) == FALSE) {
			goto error_exit;
		}

		/* 割込み禁止ネストカウント初期化 */
		can_interrupt_nested_cnt[ctrl_id] = 0U;

		/*  Can_SetControllerMode動作状態フラグ初期化 */
		can_set_controller_mode_flg[ctrl_id] = FALSE;

		/* CANコントローラ状態情報初期化 */
		can_current_state[ctrl_id] = CAN_T_STOP;
	}

	/* [CAN245][CAN250] unit_phase2 */
	if (can_target_init_unit_phase2(p_cur_can_config) == FALSE) {
		goto error_exit;
	}

	/* [CAN246] 全ての処理完了後に，Canの初期化状態を設定する */
	can_init_flg = CAN_READY;

  normal_exit:
	return;

  error_exit:
	/* [CAN104][CAN174][CAN408] */
	CAN_DET_REPORT_ERROR(CANServiceId_Init, CAN_E_TRANSITION);
	/* [CAN091] */
	goto normal_exit;
}


/*
 *  [CAN224] Can_GetVersionInfo
 */
/* [CAN252] Can_GetVersionInfoの有無はコンフィギュレーションで切り替え */
#if CAN_VERSION_INFO_API == STD_ON
/* [CAN251] マクロで実装してもよいがNULLポインタチェックのため関数とする */
void
Can_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
	/* [CAN177] */
	if (versioninfo == NULL_PTR) {
		CAN_DET_REPORT_ERROR(CANServiceId_GetVersionInfo, CAN_E_PARAM_POINTER);
	}

	/* [CAN105] 各バージョンを返す */
	versioninfo->vendorID = CAN_VENDOR_ID;
	versioninfo->moduleID = CAN_MODULE_ID;
	versioninfo->sw_major_version = CAN_SW_MAJOR_VERSION;
	versioninfo->sw_minor_version = CAN_SW_MINOR_VERSION;
	versioninfo->sw_patch_version = CAN_SW_PATCH_VERSION;
}
#endif /* CAN_VERSION_INFO_API */

/* [CAN460] Can_CheckBaudrateの有無はコンフィギュレーションで切り替え */
#if CAN_CHANGE_BAUDRATE_API == STD_ON
/*
 *  [CAN454] Can_CheckBaudrate
 */
Std_ReturnType
Can_CheckBaudrate(uint8 Controller, const uint16 Baudrate)
{
	uint8				i;
	Std_ReturnType		ercd = E_NOT_OK;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN456] */
	CAN_CHECK_INITIALIZED_ERCD_STD_RETERN_TYPE(CANServiceId_CheckBaudrate);

	/* [CAN104][CAN457] */
	CAN_CHECK_CONTROLLER_ERCD_STD_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_CheckBaudrate);

	/* CANコントローラ管理ブロック取得 */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* サポートボーレートの判定 */
	for (i = 0U; i < p_ctrl_inib->tnum_baudrate; i++) {
		if (p_ctrl_inib->p_baudrate_table[i].CanControllerBaudRate == Baudrate) {
			ercd = E_OK;
			break;
		}
	}

	/* [CAN458] 未サポートのボーレートが指定された場合，DETエラー */
	if (ercd == E_NOT_OK) {
		CAN_DET_REPORT_ERROR(CANServiceId_CheckBaudrate, CAN_E_PARAM_BAUDRATE);
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}

/*
 *  [CAN449] Can_ChangeBaudrate
 */
Std_ReturnType
Can_ChangeBaudrate(uint8 Controller, const uint16 Baudrate)
{
	uint8									i;
	Std_ReturnType							ercd = E_NOT_OK;
	const CAN_CTRL_INIB						*p_ctrl_inib;
	const Can_ControllerBaudrateConfigType	*p_baudrate_config;

	/* [CAN104][CAN026][CAN450] */
	CAN_CHECK_INITIALIZED_ERCD_STD_RETERN_TYPE(CANServiceId_ChangeBaudrate);

	/* [CAN104][CAN452] */
	CAN_CHECK_CONTROLLER_ERCD_STD_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_ChangeBaudrate);

	/* CANコントローラ管理ブロック取得 */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* サポートボーレートの判定 */
	for (i = 0U; i < p_ctrl_inib->tnum_baudrate; i++) {
		if (p_ctrl_inib->p_baudrate_table[i].CanControllerBaudRate == Baudrate) {
			ercd = E_OK;

			/* 対象のボーレートリスト取得 */
			p_baudrate_config = &p_ctrl_inib->p_baudrate_table[i];
			break;
		}
	}

	if (ercd == E_OK) {
		/* ボーレートの設定処理 */
		/* (CAN062) 必要に応じて，コントローラの再初期化を行う */
		/* (CAN461) 初期化中にウェイクアップイベントが発生した場合，EcuMモジュールへ通知する */
		/* (CAN255) 対象のコントローラに関するレジスタのみ操作する */
		/* (CAN256) 対象のコントローラがSTOPPED状態の場合のみ，ボーレートを変更する */
		/* (CAN260) ボーレート変更中，対象のコントローラのSTOPPED状態を維持する */
		/* (CAN422) ボーレート変更によって，対象のコントローラがネットワークに参加することはない */
		if (can_target_change_baudrate(Controller, p_baudrate_config) == FALSE) {
			ercd = E_NOT_OK;
			/* (CAN453) CANコントローラがボーレートを変更できない状態の場合，DETエラー */
			CAN_DET_REPORT_ERROR(CANServiceId_ChangeBaudrate, CAN_E_TRANSITION);
		}
	}
	else {
		/* [CAN451] 未サポートのボーレートが指定された場合，DETエラー */
		CAN_DET_REPORT_ERROR(CANServiceId_ChangeBaudrate, CAN_E_PARAM_BAUDRATE);
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}
#endif /* CAN_CHANGE_BAUDRATE_API == STD_ON */

/*
 *  [CAN230] Can_SetControllerMode
 */
Can_ReturnType
Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition)
{
	Can_ReturnType		ercd = CAN_OK;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN198] 初期化チェック */
	CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(CANServiceId_SetControllerMode);

	/* [CAN104][CAN199] コントローラIDチェック */
	CAN_CHECK_CONTROLLER_ERCD_CAN_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_SetControllerMode);

	/* Can_SetControllerMode動作フラグを動作中(TRUE)に設定 */
	can_set_controller_mode_flg[Controller] = TRUE;

	/* CANコントローラ管理ブロック取得 */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* [CAN017] 指定されたCANコントローラ状態へ移行 */
	/* [CAN398] ブロッキング防止のために，GetCounterValueを使用し，モード変更完了を判別する */
	/* [CAN371] CanTimeoutDurationで指定された時間を上限値として，ポーリングを行う */
	/* [CAN372] CanTimeoutDurationが経過してもモードが切り替わらなかった場合， */
	/*          Can_SetControllerModeは開放され，Can_Mainfunction_Modeによるポーリングを続ける */
	/* (CAN196) 必要に応じて割込み禁止/許可状態を変更する */
	/* (CAN197) 移行後の状態で許可されない割込みを禁止する */
	/* (CAN425) Can_DisableControllerInterruptsが呼ばれている場合，割込みを許可しない */
	/* (CAN426) 既にCan_DisableControllerInterruptsが呼ばれている場合，再度割込みを禁止しない */
	switch (Transition) {
	case CAN_T_START:
		/*
		 * STOPPED -> STARTED
		 * (CAN261) CANコントローラをネットワークに参加させる
		 * (CAN409) CANコントローラがSTOPPED状態でない場合に，CAN_T_STARTを
		 *          指定された場合，DETエラーとする
		 * (CAN384) 事前にCan_InitやCan_ChangeBaudrateで初期化された内容で再初期化する
		 */
		if (can_target_start_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CANコントローラの状態の監視 */
			if (can_check_timeout_duration(Controller, CAN_T_START) == TRUE) {
				/* [CAN373] 上位レイヤへの通知 */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STARTED);

				/* 対象のコントローラの状態を更新する */
				can_current_state[Controller] = CAN_T_START;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	case CAN_T_STOP:
		/*
		 * STARTED -> STOPPED
		 * (CAN263) CANコントローラをネットワークへの参加を終了する
		 * (CAN282) ペンディング中のメッセージが存在する場合，キャンセルする
		 * (CAN283) ペンディング中のメッセージに対するキャンセル通知は行わない
		 * (CAN410) CANコントローラがSTARTでもSTOPPED状態でもない場合に，
		 *          CAN_T_STOPを指定された場合，DETエラーとする
		 */
		if (can_target_stop_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CANコントローラの状態の監視 */
			if (can_check_timeout_duration(Controller, CAN_T_STOP) == TRUE) {
				/* [CAN373] 上位レイヤへの通知 */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

				/* 対象のコントローラの状態を更新する */
				can_current_state[Controller] = CAN_T_STOP;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	case CAN_T_SLEEP:
		/*
		 * STOPPED -> SLEEP
		 * (CAN265) CANコントローラをSLEEP状態に切り替える
		 * (CAN290) ハードウェアがSLEEPモードをサポートしない場合，論理的なSLEEP状態とする
		 * (CAN405) 論理的なSLEEP状態は，Can_SetControllerMode(CAN_T_WAKEUP)呼出しにより開放される
		 * (CAN411) CANコントローラがSTOPPEDでもSLEEP状態でもない場合に，
		 *          CAN_T_SLEEPを指定された場合，DETエラーとする
		 */
		if (can_target_sleep_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CANコントローラの状態の監視 */
			if (can_check_timeout_duration(Controller, CAN_T_SLEEP) == TRUE) {
				/* [CAN373] 上位レイヤへの通知 */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_SLEEP);

				/* 対象のコントローラの状態を更新する */
				can_current_state[Controller] = CAN_T_SLEEP;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	case CAN_T_WAKEUP:
		/*
		 * SLEEP -> STOPPED
		 * (CAN267) ハードウェアがSLEEPモードをサポートしない場合，論理的な
		 *          SLEEP状態を開放し，コントローラへの処理は何も行わない
		 * (CAN412) CANコントローラがSLEEPでもSTOPPED状態でもない場合に，
		 *          CAN_T_SLEEPを指定された場合，DETエラーとする
		 */
		/* (CAN294) ウェイクアップ状態をチェックする際は，ウェイクアップ割込みを禁止する */
		/* (CAN048) SLEEP中にウェイクアップした場合，本システムサービスでCAN_T_WAKEUPを指定されてもCAN_NOT_OKを返す */
		if (can_target_wakeup_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
			/* [CAN281] CANコントローラの状態の監視 */
			if (can_check_timeout_duration(Controller, CAN_T_WAKEUP) == TRUE) {
				/* [CAN373] 上位レイヤへの通知 */
				CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

				/* 対象のコントローラの状態を更新する */
				can_current_state[Controller] = CAN_T_WAKEUP;
			}
		}
		else {
			ercd = CAN_NOT_OK;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		}
		break;
	default:
		/* [CAN200] 引数が異常の場合 */
		ercd = CAN_NOT_OK;
		CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_TRANSITION);
		break;
	}

  error_exit:
	/* [CAN091] */

	/* Can_SetControllerMode動作フラグを停止中(FALSE)に設定 */
	can_set_controller_mode_flg[Controller] = FALSE;

	return(ercd);
}

/*
 *  [CAN231] Can_DisableControllerInterrupts
 */
void
Can_DisableControllerInterrupts(uint8 Controller)
{
	/* [CAN104][CAN026][CAN205] */
	CAN_CHECK_INITIALIZED(CANServiceId_DisableControllerInterrupts);

	/* [CAN104][CAN206] */
	CAN_CHECK_CONTROLLER((Controller < GET_CONTROLLER_NUM()), CANServiceId_DisableControllerInterrupts);

	/* ネストカウント判定 */
	if (can_interrupt_nested_cnt[Controller] == CAN_INTERRUPT_NESTED_CNT_MAX) {
		/*上限値超過 */
		CAN_DET_REPORT_ERROR(CANServiceId_DisableControllerInterrupts, CAN_E_FATAL);
		goto error_exit;
	}

	/*
	 * 割込み禁止処理
	 * [CAN049] 割込み許可状態のコントローラの場合のみ処理する
	 */
	if (can_interrupt_nested_cnt[Controller] == 0U) {
		if (can_target_disable_controller_interrupts(Controller) == FALSE) {
			CAN_DET_REPORT_ERROR(CANServiceId_DisableControllerInterrupts, CAN_E_FATAL);
		}
	}

	/* [CAN202] ネスト呼出し回数管理を行って，意図せず割込み許可にならないようにする */
	can_interrupt_nested_cnt[Controller]++;

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN232] Can_EnableControllerInterrupts
 */
void
Can_EnableControllerInterrupts(uint8 Controller)
{
	/* [CAN104][CAN026][CAN209] */
	CAN_CHECK_INITIALIZED(CANServiceId_EnableControllerInterrupts);

	/* [CAN104][CAN210] */
	CAN_CHECK_CONTROLLER((Controller < GET_CONTROLLER_NUM()), CANServiceId_EnableControllerInterrupts);

	/*
	 * ネストカウント判定
	 * [CAN208] Disableが呼ばれていない場合はなにもしない
	 */
	if (can_interrupt_nested_cnt[Controller] != 0U) {
		/*
		 * ネストカウントデクリメント
		 * [CAN050] ネスト呼出し回数管理を行って，意図せず割込み許可にならないようにする
		 */
		can_interrupt_nested_cnt[Controller]--;

		if (can_interrupt_nested_cnt[Controller] == 0U) {
			/* 割込み許可処理 */
			if (can_target_enable_controller_interrupts(Controller) == FALSE) {
				CAN_DET_REPORT_ERROR(CANServiceId_EnableControllerInterrupts, CAN_E_FATAL);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN360] Can_CheckWakeup
 */
Can_ReturnType
Can_CheckWakeup(uint8 Controller)
{
	Can_ReturnType ercd;

	/* [CAN104][CAN026][CAN362] */
	CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(CANServiceId_CheckWakeup);

	/* [CAN104][CAN363] */
	CAN_CHECK_CONTROLLER_ERCD_CAN_RETERN_TYPE((Controller < GET_CONTROLLER_NUM()), CANServiceId_CheckWakeup);

	/* (CAN361) 前回SLEEP状態へ移行してからウェイクアップを検出したかどうかを返す */
	if (can_target_check_wakeup(Controller) != FALSE) {
		ercd = CAN_OK;
	}
	else {
		ercd = CAN_NOT_OK;
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}

/*
 *  [CAN233] Can_Write
 */
Can_ReturnType
Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
	Can_ReturnType		ercd;
	uint8				ctrl_id;
	Can_HwHandleType	tbox_index;

	/* [CAN104][CAN026][CAN216] */
	CAN_CHECK_INITIALIZED_ERCD_CAN_RETERN_TYPE(CANServiceId_Write);

	/* [CAN104][CAN217] */
	CAN_CHECK_HTH_ERCD_CAN_RETERN_TYPE(((Hth < GET_HOH_NUM()) && (GET_BOX_OBJ_TYPE(Hth) == CAN_TRANSMIT)), CANServiceId_Write);

	/* [CAN104][CAN218] */
	CAN_CHECK_DLC_ERCD_CAN_RETERN_TYPE((PduInfo->length <= CAN_MAX_DLC), CANServiceId_Write);

	/* [CAN104][CAN219] */
	CAN_CHECK_SDU_ERCD_CAN_RETERN_TYPE((PduInfo->sdu != NULL_PTR), CANServiceId_Write);

	/* コントローラID取得 */
	ctrl_id = GET_CONTROLLER_ID(Hth);

	/* 送信メールボックスのインデックス取得 */
	tbox_index = GET_BOX_IDX(Hth);

	/* [CAN011] データ一貫性を保持するために書き込み中は排他する */
	/* 排他開始 */
	SchM_Enter_Can_Reentrant();

	/* [CAN212] HTHのミューテックス判定 */
	if (GET_HTH_MUTEX(ctrl_id, tbox_index) == FALSE) {
		/* HTHのミューテックス獲得 */
		SET_HTH_MUTEX(ctrl_id, tbox_index, TRUE);

		ercd = CAN_OK;
	}
	else {
		/* [CAN213][CAN214][CAN215][CAN434] ミューテックスが獲得済みの場合は，CAN_BUSYを返す */
		ercd = CAN_BUSY;
	}

	/* 排他終了 */
	SchM_Exit_Can_Reentrant();

	if (ercd == CAN_OK) {
		/* [CAN276] 正常時は送信完了通知用にPDU-IDを保持する */
		SET_SAVED_PDU_ID(ctrl_id, tbox_index, PduInfo->swPduHandle);

		/*
		 * 送信データ及び送信要求設定
		 * [CAN275] 送信処理自体は排他処理を実施しない
		 * (CAN059) データ配列の0番目の要素から送信し，7番目の要素を最後に送信する
		 * (CAN427) ハードウェア上のバッファ表現に関わらず，Can_PduType型に含まれるデータ配列を使用する
		 */
		ercd = can_target_transmit(ctrl_id, Hth, tbox_index, PduInfo);

		/* HTHのミューテックス解放 */
		SET_HTH_MUTEX(ctrl_id, tbox_index, FALSE);
	}

  error_exit:
	/* [CAN091] */
	return(ercd);
}

/*
 *  [CAN007][CAN099][CAN280][CAN225][NCAN002] Can_MainFunction_Write
 */
/* [CAN178] ポーリングによる送信を使用しない場合，本関数は定義しない */
#ifdef USE_CAN_TX_POLLING
void
Can_MainFunction_Write(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN179] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Write);

	/* [CAN031] 送信完了通知のポーリングを行う */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* 対象コントローラがポーリングの場合にのみ実行 */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_TX) != 0x00U) {
			if (can_target_polling_tx(ctrl_id) != FALSE) {
				Can_IsrTx(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_TX_POLLING */

/*
 *  [CAN007][CAN099][CAN280][CAN226][NCAN001] Can_MainFunction_Read
 */
/* [CAN180] ポーリングによる受信を使用しない場合，本関数は定義しない */
#ifdef USE_CAN_RX_POLLING
void
Can_MainFunction_Read(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN181] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Read);

	/* [CAN108] 受信完了通知のポーリングを行う */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* 対象コントローラがポーリングの場合にのみ実行 */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_RX) != 0x00U) {
			if (can_target_polling_rx(ctrl_id) != FALSE) {
				/* [CAN396] 共通受信処理 */
				Can_IsrRx(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_RX_POLLING */

/*
 *  [CAN007][CAN099][CAN280][CAN227] Can_MainFunction_BusOff
 */
/* [CAN183] ポーリングによるバスオフ通知を使用しない場合，本関数は定義しない */
#ifdef USE_CAN_BUSOFF_POLLING
void
Can_MainFunction_BusOff(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN184] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_BusOff);

	/* [CAN109] バスオフ通知のポーリングを行う */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* 対象コントローラがポーリングの場合にのみ実行 */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_BUSOFF) != 0x00U) {
			if (can_target_polling_busoff(ctrl_id) != FALSE) {
				Can_IsrBusoff(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_BUSOFF_POLLING */

/*
 *  [CAN007][CAN099][CAN280][CAN228] Can_MainFunction_Wakeup
 */
/* [CAN185] ポーリングによるウェイクアップ通知を使用しない場合，本関数は定義しない */
#ifdef USE_CAN_WAKEUP_POLLING
void
Can_MainFunction_Wakeup(void)
{
	uint8				ctrl_id;
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* [CAN104][CAN026][CAN186] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Wakeup);

	/* [CAN112] ウェイクアップ通知のポーリングを行う */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* 対象コントローラがポーリングの場合にのみ実行 */
		p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);
		if ((p_ctrl_inib->use_polling & CAN_USE_POLLING_WAKEUP) != 0x00U) {
			if (can_target_polling_wakeup(ctrl_id) != FALSE) {
				Can_IsrWakeup(ctrl_id);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}
#endif /* USE_CAN_WAKEUP_POLLING */

/*
 *  [CAN368] Can_MainFunction_Mode
 */
void
Can_MainFunction_Mode(void)
{
	uint8					ctrl_id;
	Can_StateTransitionType	ret_state;
	const CAN_CTRL_INIB		*p_ctrl_inib;

	/* [CAN104][CAN026][CAN379] */
	CAN_CHECK_INITIALIZED_MF(CANServiceId_MainFunction_Mode);

	/* [CAN369] モード切り替わり検出のポーリングを行う */
	for (ctrl_id = 0U; ctrl_id < GET_CONTROLLER_NUM(); ctrl_id++) {
		/* Can_SetControllerMode動作状態フラグ判定 */
		if (can_set_controller_mode_flg[ctrl_id] == FALSE) {
			/*
			 * [CAN370] CANコントローラの状態が変化したことをチェックし，
			 *          正しく変更されたら，CanIf_ControllerModeIndicationで通知して
			 *          CANコントローラの状態を更新する
			 */
			ret_state = can_target_get_mode(ctrl_id);

			if (ret_state != can_current_state[ctrl_id]) {
				/* CANコントローラ管理ブロック取得 */
				p_ctrl_inib = GET_CAN_CTRL_INIB(ctrl_id);

				/* CANコントローラ状態判定 */
				switch (ret_state) {
				case CAN_T_START:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STARTED);

					can_current_state[ctrl_id] = CAN_T_START;
					break;
				case CAN_T_STOP:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

					can_current_state[ctrl_id] = CAN_T_STOP;
					break;
				case CAN_T_SLEEP:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_SLEEP);

					can_current_state[ctrl_id] = CAN_T_SLEEP;
					break;
				case CAN_T_WAKEUP:
					CanIf_ControllerModeIndication(p_ctrl_inib->CanIfCtrlId, CANIF_CS_STOPPED);

					can_current_state[ctrl_id] = CAN_T_WAKEUP;
					break;
				default:
					CAN_DET_REPORT_ERROR(CANServiceId_MainFunction_Mode, CAN_E_TRANSITION);
					break;
				}
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN099][CAN035][CAN033] CAN受信完了通知割込みサービスルーチン
 */
void
Can_IsrRx(uint8 Controller)
{
	Can_IdType			can_id;
	uint8				can_dlc;
	uint8				can_sdu[CAN_MAX_DLC];
	Can_HwHandleType	rbox_idx;
	boolean				ret = TRUE;

	/* (CAN420) 割込み要求のクリアは，必要に応じてC2ISR側で対応する */

	while (1) {
		/* 受信メールボックス取得 */
		if (can_target_check_and_get_rbox(Controller, &rbox_idx) == FALSE) {
			/* 受信メッセージ無し */
			break;
		}

		/* 受信メールボックスのインデックスをチェック */
		CAN_CHECK_MAILBOX_INDEX_NUM((rbox_idx <= GET_HRH_NUM(Controller)), CANServiceId_IsrRx);

		/*
		 * 受信IDのデータ取得
		 * (CAN012) 受信データの一貫性を保証する
		 * (CAN060) 先頭の受信データをデータ配列の0番目の要素に格納し，
		 *          末尾の受信データを7番目の要素に格納する
		 * (CAN299)(CAN300) 一律受信したデータをローカル変数(can_sdu)にコピーする
		 */
		if (can_target_get_rdata(Controller, rbox_idx, &can_id, &can_dlc, &can_sdu[0]) == TRUE) {
#ifdef USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION
			/* [CAN443] コールアウト処理 */
			ret = CanLpduCalloutFunction(rbox_idx, can_id, can_dlc, can_sdu);
#endif /* USE_CAN_LPDU_RECEIVE_CALLOUT_FUNCTION */
			/* [CAN444] コールアウト処理がFALSEの場合，受信処理を継続しない */
			if (ret == TRUE) {
				/* [CAN279][CAN396] 上位通知 */
				CanIf_RxIndication(GET_RBOX_CAN_OBJ_ID(Controller, rbox_idx), can_id, can_dlc, &can_sdu[0]);
			}
		}
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN099][CAN035][CAN033] CAN送信完了通知割込みサービスルーチン
 */
void
Can_IsrTx(uint8 Controller)
{
	Can_HwHandleType tbox_idx;

	/* (CAN420) 割込み要求のクリアは，必要に応じてC2ISR側で対応する */

	while (1) {
		/* 送信メールボックス取得 */
		if (can_target_check_and_get_tbox(Controller, &tbox_idx) == FALSE) {
			/* 送信メッセージ無し */
			break;
		}

		/* 送信メールボックスのインデックスをチェック */
		CAN_CHECK_MAILBOX_INDEX_NUM((tbox_idx <= GET_HTH_NUM(Controller)), CANServiceId_IsrTx);

		/* [CAN016] 上位レイヤへの通知 */
		CanIf_TxConfirmation(GET_SAVED_PDU_ID(Controller, tbox_idx));
	}

  error_exit:
	/* [CAN091] */
	return;
}

/*
 *  [CAN099][CAN035][CAN033] CANバスオフ通知割込みサービスルーチン
 */
void
Can_IsrBusoff(uint8 Controller)
{
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* (CAN420) 割込み要求のクリアは，必要に応じてC2ISR側で対応する */

	/* CANコントローラ管理ブロック取得 */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* [CAN020] 状態をSTOPPEDへ移行し，上位レイヤへ通知 */
	/* (CAN272) STOPPEDへ移行後は対象コントローラがCANネットワークに関与しないことを保証する */
	/* (CAN273) 送信待ちメッセージがある場合，上位レイヤへキャンセル通知をせずに，送信をキャンセルする */
	/* (CAN274) ハードウェアによる自動バスオフ復帰は無効にする */
	if (can_target_stop_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
		CanIf_ControllerBusOff(Controller);
	}
	else {
		CAN_DET_REPORT_ERROR(CANServiceId_IsrBusoff, CAN_E_FATAL);
	}
}

/*
 *  [CAN099][CAN035][CAN033] CANウェイクアップ通知割込みサービスルーチン
 */
void
Can_IsrWakeup(uint8 Controller)
{
	const CAN_CTRL_INIB	*p_ctrl_inib;

	/* (CAN420) 割込み要求のクリアは，必要に応じてC2ISR側で対応する */

	/* CANコントローラ管理ブロック取得 */
	p_ctrl_inib = GET_CAN_CTRL_INIB(Controller);

	/* [CAN270] 状態をSTOPPEDへ移行する */
	if (can_target_stop_controller_and_change_interrupt(Controller, p_ctrl_inib) != FALSE) {
		/* [CAN271][CAN364] EcuMへ通知 */
		if (p_ctrl_inib->CanWakeupSupport != FALSE) {
			EcuM_CheckWakeup(p_ctrl_inib->EcuMWakeupSourceId);
		}
	}
	else {
		CAN_DET_REPORT_ERROR(CANServiceId_IsrWakeup, CAN_E_FATAL);
	}

	/* [CAN269] ウェイクアップ対象のコントローラに対して，これ以上何もしない */
}

/*
 *  CANコントローラの状態監視処理
 */
boolean
can_check_timeout_duration(uint8 Controller, Can_StateTransitionType Transition)
{
	boolean		ret = TRUE;
	TickType	start_time;
	TickType	eval_time;
	TickType	total_eval_time = 0U;
	StatusType	ercd;

	/* カウント値取得 */
	ercd = GetCounterValue(CAN_COUNTER, &start_time);

	/* カウント値取得判定 */
	if (ercd != E_OK) {
		ret = FALSE;
		CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_FATAL);
		goto error_exit;
	}

	/* CANコントローラのモード取得 */
	while (can_target_get_mode(Controller) != Transition) {
		/* ウェイト処理 */
		can_target_busy_wait();

		/* 経過カウント値取得 */
		ercd = GetElapsedValue(CAN_COUNTER, &start_time, &eval_time);

		/* 経過カウント値取得判定 */
		if (ercd != E_OK) {
			ret = FALSE;
			CAN_DET_REPORT_ERROR(CANServiceId_SetControllerMode, CAN_E_FATAL);
			goto error_exit;
		}

		/* 経過カウント値の差分加算 */
		total_eval_time += eval_time;

		/* [CAN262][CAN264][CAN266][CAN268] CANコントローラのモード取得処理が完了するのを上限時間まで待つ */
		if ((CAN_COUNTER_TICKS2SEC(total_eval_time)) > CAN_TIMEOUT_DURATION) {
			ret = FALSE;
			break;
		}
	}

  error_exit:
	return(ret);
}


/*
 *  ■非依存部での未サポート機能
 *    <CAN395> エラー検出タイミングはターゲット依存のため依存部で対応する
 *    <CAN365><CAN366><CAN367> R4.1で削除されたため，デバッグに関する要求は対応しない
 *    <CAN079> R4.1でC言語実装ルールが削除されたため，対応しない
 *    <CAN423> 拡張フォーマットには未対応
 *    <CAN277><CAN401><CAN402><CAN403><CAN076> マルチ送信は未サポート
 *    <CAN278><CAN432><CAN285><CAN286><CAN433><CAN399><CAN400><CAN287><CAN288> 送信キャンセルは未サポート
 *    <CAN441><CAN442> メッセージボックス毎のポーリング用MainFunctionは未サポート
 *    <CAN445><CAN446><CAN447> Icuモジュールに関する仕様は未サポート
 *    <CAN392> Demへ送信するエラー処理は存在しないため，未サポート
 *
 *  ■ハードウェアをトリガーとするSLEEP状態移行処理に対する要求
 *    (CAN257) ハードウェアがSLEEPモードをサポートする場合，コントローラをSLEEP状態に切り替える
 *    (CAN258) ハードウェアがSLEEPモードをサポートしない場合，論理的にSLEEP状態を
 *             エミュレートし，コントローラをSTOPPED状態にする
 *    (CAN404) 論理的なSLEEPモードの間は，コントローラはSTOPPED状態を維持する
 *
 *  ■その他の仕様説明
 *    [CAN240] Mcuモジュールへの要求事項である
 *    [CAN455] CanIfモジュールへの要求事項である
 *    [CAN058][CAN234][CAN235] 関連する外部I/Fへの要求事項である
 *    [CAN459] ユーザへの注意事項である
 *    [CAN110] MainFunctionの実行順序への要求がないため，実装上の対応は不要
 *    (CAN239) I/Oポートの初期化はPortモジュールで行うと規定されているが，
 *             Portモジュールを省略して，OSあるいは各依存部で初期化可能とする
 *    <CAN418> Canモジュールのみで使用する定数やグローバル変数，関数は本ファイルでのみ
 *             定義すると規定されているが，ターゲット依存部/非依存部切り分けのため，
 *             別ファイルでも定義可能とする
 *    [CAN448][CAN999] 要求仕様ではない
 */
