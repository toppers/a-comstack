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
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 *
 *  �ܥ��եȥ������ϡ�AUTOSAR��AUTomotive Open System ARchitecture�˻�
 *  �ͤ˴�Ť��Ƥ��롥�嵭�ε����ϡ�AUTOSAR����Ū�⻺������������Τ�
 *  �Ϥʤ���AUTOSAR�ϡ�AUTOSAR���ͤ˴�Ť������եȥ�����������Ū����
 *  �Ѥ���Ԥ��Ф��ơ�AUTOSAR�ѡ��ȥʡ��ˤʤ뤳�Ȥ���Ƥ��롥
 *
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 *
 *  $Id: Com.c 797 2014-12-01 08:44:47Z panasonic-ayane $
 */

/* [COM584] Com.c */

/*
 *  ��ȯ����
 *  - [COM010] API��OSEK/VDX COM��Ʊ���Τ�ΤȤ���
 *  - [COM011] OSEK���ͤ�AUTOSAR���ͤ���㤬�����Τ�AUTOSAR���ͤ˽�򤹤�
 *  - [COM012] AUTOSAR���ͤǤΤߵ��ꤵ��Ƥ�����ͤ��������
 *  - [COM013] �ͥåȥ����å��������ΰ�����OSEK���ͤϼ�����ɬ�ܤǤʤ����ᡤ�������ʤ�
 */

/* [COM220] */
#include "Com.h"
/*
 *  [NCOM032] SchM_Com.h��RTE�����ͥ졼���ˤ�����������
 *  [COM320][COM321] �ܼ����ǤϤ��٤ƤΥ����ƥॵ���ӥ���ꥨ��ȥ��ȤȤ���
 */
#include "SchM_Com.h"

#if COM_DEV_ERROR_DETECT == STD_ON
/* [COM670] */
#include "Det.h"
#endif /* COM_DEV_ERROR_DETECT == STD_ON */

/* [COM669] */
/* PduR_Com.h��PduR�����ͥ졼���ˤ����������� */
#include "PduR_Com.h"

/*
 *  �����ؿ��Υץ�ȥ��������
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
 *  ���߼¹����Com����ե�����졼��������
 */
static const Com_ConfigType	*p_cur_com_config;
static const SIGNAL_INIB	*p_cur_signal_inib;
static const IPDU_INIB		* const *pp_cur_all_ipdu_inib;
static const IPDU_INIB		*p_cur_rx_ipdu_inib;
static const IPDU_INIB		*p_cur_tx_ipdu_inib;

/*
 *  Com�ν��������
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

	/* [COM373] Com_Init�ˤ��ݥ��ȥӥ�ɥѥ�᡼����̤�����(̤����)���Τ߹����Ǥ��� */
	COM_CHECK_UNINITIALIZED(COMServiceId_Init);

	/* [COM433] �����ʥݥ��󥿤ؤ��б��ϡ�NULL_PTR���Ф��ƤΤ߹Ԥ� */
	if (config == NULL_PTR) {
		/* [NCOM040] NULL_PTR�ξ�硤ComConfigurationId��0�Υ���ե�����졼������Ȥ� */
		config = &com_config[0];
	}

	/* [COM328][COM444] ���߼¹���Υ���ե����졼����������ݻ� */
	p_cur_com_config = config;
	p_cur_signal_inib = p_cur_com_config->p_signal_inib_table;
	pp_cur_all_ipdu_inib = p_cur_com_config->pp_ipdu_inib_table;
	p_cur_rx_ipdu_inib = p_cur_com_config->p_rx_ipdu_inib_list;
	p_cur_tx_ipdu_inib = p_cur_com_config->p_tx_ipdu_inib_list;

	/* [COM015] IPDU�Хåե���̤���ѥǡ����ǽ���� */
	for (i = 0U; i < GET_TX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_TX_IPDU_INIB(i);
		p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
		for (j = 0U; j < p_ipdu_inib->PduLength; j++) {
			(p_ipdu_inib->p_ipdu_buffer)[j] = p_tx_ipdu_inib->ComTxIPduUnusedAreasDefault;
		}
	}

	/* ��IPDU���̤ν�������� */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);

		/* [COM217][COM098][COM483][COM128][COM117] IPDU�ν���� */
		ipdu_initialize(p_ipdu_inib);

		/* [COM328][COM444]IPDU����� */
		IPDU_CLEAR_STARTED(p_ipdu_inib->p_state);
	}

	/* COM���������֤ذܹ� */
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

	/* [COM129] ��IPDU���롼�פ���� */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);
		IPDU_CLEAR_ALL(p_ipdu_inib->p_state);
	}

	/* COM��̤��������֤ذܹ� */
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
	 *  IPDU��ߢ����ʤ��Ȥ�1�Ĥν�°IPDU���롼�פ򳫻ϡ�����
	 *  IPDU���Ϣ����٤Ƥν�°IPDU���롼�פ����       �����
	 *  IPDU��ߢ����٤Ƥν�°IPDU���롼�פ����       �����⤷�ʤ�
	 *  IPDU���Ϣ����ʤ��Ȥ�1�Ĥν�°IPDU���롼�פ򳫻ϡ����⤷�ʤ�
	 */
	for (i = 0U; i < GET_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_IPDU_INIB(i);

		start_flg = FALSE;
		for (j = 0U; j < GET_VECTOR_NUM(); j++) {
			/* ���ϻؼ����줿IPDU���롼�ץ٥��� */
			target = ipduGroupVector[j];
			/* �о�IPDU�ν�°IPDU���롼�ץ٥��� */
			belong = (*(p_ipdu_inib->p_ipdu_group_vector))[j];

			/* 1�ĤǤ��°IPDU���롼�פ����ϻؼ�����Ƥ��뤫 */
			if ((target & belong) != 0U) {
				start_flg = TRUE;
				/* 1�ĤǤⳫ�ϻؼ�����Ƥ���Ф褤 */
				break;
			}
		}

		/*
		 *  ���ߤ�IPDU�ξ��֤˹�碌�ƽ�����Ԥ�
		 *  [COM613] IPDU���롼�׼��Τξ��֤����פΤ���������ʤ�
		 */
		if (start_flg != FALSE) {
			/* [COM614] ��ߤ��Ƥ���IPDU���Ф��ơ�IPDU�򳫻Ϥ��� */
			if (!IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
				/*
				 *  [COM740] �ܥ����ƥॵ���ӥ���initialize = FALSE�ǡ�Com_Init��˽��ƸƤӽФ��쳫�Ϥ�����硤
				 *           initialize = TRUE�ǸƤӽФ��줿����Ʊ����̤ˤʤ�
				 *  [COMa001] initialize = FALSE�ǳ��Ϥ��줿��硤������MF��������󥿤Ͻ�������ʤ�
				 */
				if (initialize != FALSE) {
					/* IPDU�Хåե���̤���ѥǡ����ǽ���� */
					if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
						p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
						for (j = 0U; j < p_ipdu_inib->PduLength; j++) {
							(p_ipdu_inib->p_ipdu_buffer)[j] = p_tx_ipdu_inib->ComTxIPduUnusedAreasDefault;
						}
					}
					/* [COM222][COM217] IPDU�ν���� */
					ipdu_initialize(p_ipdu_inib);

#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
					/* [COM778] ��α���줿�����׵��̵���ˤ��� */
					IPDU_CLEAR_RETRITED(p_ipdu_inib->p_state);
#endif
				}

				if (p_ipdu_inib->ComIPduDirection == COM_SEND) {
					p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

					/* initialize = TRUE�ξ�硤ipdu_initialize()�����TMSȽ��򤹤뤿�ᡤ�����Ǥ�FALSE�ξ��Τ߼»ܤ��� */
					if (initialize == FALSE) {
						/* [COM229][COM223][COM032][COM238] TMS����ꤷ�������⡼�ɤ���ꤹ�� */
						p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
						if (check_tms(p_ipdu_inib) != FALSE) {
							p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
						}
						else {
							p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
						}
					}

					/* �����󥿤ν���� */
					p_tx_ipdu_cb->repeat_cnt = 0U;
					p_tx_ipdu_cb->interval_mf_cnt = 0U;
					p_tx_ipdu_cb->mdt_mf_cnt = 0U;
					p_tx_ipdu_cb->queuing_cnt = 0U;
					p_tx_ipdu_cb->dm_mf_cnt = 0U;
				}
				else {
					/* [COM787][COM733] DM���� */
					start_rx_dm(p_ipdu_inib);
				}

				/* [COM612][COM114] IPDU�γ��� */
				IPDU_SET_STARTED(p_ipdu_inib->p_state);
			}
			else {
				if ((p_ipdu_inib->ComIPduDirection == COM_RECEIVE) && (!IPDU_IS_DM(p_ipdu_inib->p_state))) {
					/* [COM787][COM733] DM���� */
					start_rx_dm(p_ipdu_inib);
				}
			}

		}
		/* start_flg == FALSE ���� IPDU������  */
		else if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			/*
			 *  IPDU�����
			 *  [COM115][COM684] ����������������̵���ˤ���
			 *  [COM685] DM���
			 */
			IPDU_CLEAR_ALL(p_ipdu_inib->p_state);
			p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
			for (k = 0U; k < p_ipdu_inib->tnum_signal; k++) {
				p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[k]);
				if ((p_signal_inib->ComErrorNotification != NULL_PTR) && (p_tx_ipdu_cb->queuing_cnt != 0U)) {
					/* ��¾���ꥢ��ǥ�����Хå��Υݥ��󥿤���Ф� */
					notification = p_signal_inib->ComErrorNotification;
					/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
					p_saved_config = p_cur_com_config;

					/* [COM479] */
					SchM_Exit_Com_Reentrant_0();
					notification();
					SchM_Enter_Com_Reentrant_0();

					/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
					COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_IpduGroupControl);
				}
			}
		}
		else {
			/* [COM615] ���֤��Ѥ��ʤ����ϲ��⤷�ʤ� */
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

	/* [COM534] ����IPDU���Ф��ƽ�����Ԥ� */
	for (i = 0U; i < GET_RX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_RX_IPDU_INIB(i);

		start_flg = FALSE;
		for (j = 0U; j < GET_VECTOR_NUM(); j++) {
			/* DM���ϻؼ����줿IPDU���롼�ץ٥��� */
			target = ipduGroupVector[j];
			/* �о�IPDU�ν�°IPDU���롼�ץ٥��� */
			belong = (*(p_ipdu_inib->p_ipdu_group_vector))[j];

			/* [COM772] 1�ĤǤ��°IPDU���롼�פ�DM�����ϻؼ�����Ƥ��뤫 */
			if ((target & belong) != 0U) {
				start_flg = TRUE;
				/* 1�ĤǤⳫ�ϻؼ�����Ƥ���Ф褤 */
				break;
			}
		}

		/* [COM616][COM617] ����DM����ꤵ�줿���֤��ѹ��������Ϥޤ�����ߤ��� */
		if ((!IPDU_IS_DM(p_ipdu_inib->p_state)) && (start_flg != FALSE)) {
			/* DM���� */
			start_rx_dm(p_ipdu_inib);
		}
		else if (IPDU_IS_DM(p_ipdu_inib->p_state) && (start_flg == FALSE)) {
			/* DM��� */
			stop_rx_dm(p_ipdu_inib);
		}
		else {
			/* [COM618][COM225][COM486] ���֤��Ѥ��ʤ����ϲ��⤷�ʤ� */
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

/* [COM425] Com_GetVersionInfo��̵ͭ�ϥ���ե�����졼�������ڤ��ؤ� */
#if (COM_VERSION_INFO_API == STD_ON)
/*
 *  [COM426] Com_GetVersionInfo
 *  [COM434] �ޥ���Ǽ������Ƥ�褤��NULL�ݥ��󥿥����å��Τ���ؿ��Ȥ���
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

	/* [COM623] ���ꤵ�줿IPDU���б�����ӥåȤ򥻥å� */
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

	/* �����ʥ�ǡ�������� */
	changed = changed_signal(p_signal_inib, SignalDataPtr);

	if (changed != FALSE) {
		/* �����ʥ�Хåե��˥����ʥ�ǡ������Ǽ���� */
		set_signal_for_send(p_signal_inib, SignalDataPtr);

		/* [COM334][COM221] IPDU�������Ǥ�Хåե��ι���(�ѥå���)��Ԥ� */
		packing(p_signal_inib, SignalDataPtr);
	}

	/* [COMa003] ���åץǡ��ȥӥå����� */
	set_updatebit(p_signal_inib);

	/* [COM245] COM_NEVER�ʳ��Υե��륿����ľ��Τߡ�TMSȽ���Ԥ� */
	if ((p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) && (p_signal_inib->ComFilterAlgorithm != COM_NEVER)) {
		/* [COM602] TMCȽ�� */
		p_tx_signal_cb->tmc = filtering(p_signal_inib, SignalDataPtr);

		/* [COM605] TMSȽ�� */
		tms = check_tms(p_ipdu_inib);
		never = FALSE;
	}
	else {
		never = TRUE;
	}

	/* COM_NEVER�Υ����ʥ�ˤ�ä�TMS���ڤ��ؤ�뤳�ȤϤʤ� */
	if (never == FALSE) {
		if ((tms != FALSE) && (p_tx_ipdu_cb->p_cur_tx_mode_inib == p_tx_ipdu_inib->p_tx_mode_false_inib)) {
			/* [COM032] TMS�ڤ��ؤ�(false -> true) */
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
			/* [COM244][COM495] �����ޥꥻ�å� */
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
		}
		else if ((tms == FALSE) && (p_tx_ipdu_cb->p_cur_tx_mode_inib == p_tx_ipdu_inib->p_tx_mode_true_inib)) {
			/* [COM032] TMS�ڤ��ؤ�(true -> false) */
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
			/* [COM244][COM495] �����ޥꥻ�å� */
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
		}
		else {
			/* TMS���ڤ��ؤ��ʤ���硤���⤷�ʤ� */
		}
	}

	/* IPDU����Ƚ�� */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

		COM_CHECK_PARAM_ERCD(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
							  (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
							 (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_SendSignal);

		/* [COM279] COM_DIRECT,COM_MIXED */
		if ((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_DIRECT) ||
			(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_MIXED)) {

			/* [COM330][COM734] �����֤�������������� */
			if ((p_signal_inib->ComTransferProperty == COM_TRIGGERED) ||
				((p_signal_inib->ComTransferProperty == COM_TRIGGERED_ON_CHANGE) && (changed != FALSE))) {

				p_tx_ipdu_cb->repeat_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions;

				/* �Хåե������ӥåȤ����� */
				IPDU_SET_UPDATED(p_ipdu_inib->p_state);
			}
			/* [COM767][COM768] */
			else if ((p_signal_inib->ComTransferProperty == COM_TRIGGERED_WITHOUT_REPETITION) ||
					 ((p_signal_inib->ComTransferProperty == COM_TRIGGERED_ON_CHANGE_WITHOUT_REPETITION) && (changed != FALSE))) {

				/* [COM467] 1��Τ��������� */
				p_tx_ipdu_cb->repeat_cnt = 0U;

				IPDU_SET_WITHOUT_REPETITION(p_ipdu_inib->p_state);

				/* [NCOM006]�Хåե������ӥåȤ����� */
				IPDU_SET_UPDATED(p_ipdu_inib->p_state);
			}
			else {
				/* COM_PENDING: ���⤷�ʤ� */
			}

			p_tx_ipdu_cb->interval_mf_cnt = 0U;
			if (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_DIRECT) {
				/* COM_DIRECT��period_mf_cnt����Ѥ��ʤ��Τǽ�������� */
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

	/* [COM631] SignalDataPtr��SignalId�Υ����ʥ�ǡ����򥳥ԡ����� */
	get_signal(p_signal_inib, SignalDataPtr);

	/* IPDU���Ͼ���Ƚ�� */
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
	/* ��¾���ꥢ���̵���ͤ���Ф� */
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

	/* IPDU��߻��ϲ��⤷�ʤ� */
	if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
		/* [COM492]�����MF�������˥����륢���Ȥ�ƤӽФ� */
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

	/* ���γ��ϻ��˥ե��륿Ƚ�ꤷ�Ʒ�̤��Ѥ�뤿�ᡤIPDU��߻��˼»ܤ���ɬ�פϤʤ� */
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

	/* [COM649] ����ߤ���ƤӽФ�����ǽ��������Τ���¾��ɬ�� */
	SchM_Enter_Com_Reentrant_0();

	COM_CHECK_INITIALIZED(COMServiceId_RxIndication);
	COM_CHECK_PARAM(RxPduId < GET_IPDU_NUM(), COMServiceId_RxIndication);
	COM_CHECK_NULL_POINTER(PduInfoPtr != NULL_PTR, COMServiceId_RxIndication);

	p_ipdu_inib = GET_IPDU_INIB(RxPduId);

	COM_CHECK_PARAM((p_ipdu_inib->ComIPduDirection == COM_RECEIVE), COMServiceId_RxIndication);
	COM_CHECK_PARAM((p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) ||
					(p_ipdu_inib->ComIPduSignalProcessing == COM_DEFERRED), COMServiceId_RxIndication);

	/* [COMa005] ��������IPDU�Υǡ���Ĺ�������Ͱʾ�ξ�硤������»ܤ��� */
	if (PduInfoPtr->SduLength >= p_ipdu_inib->PduLength) {
		/* IPDU��߻��ϲ��⤷�ʤ� */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			/* [COM700] �����륢���Ƚ��� */
			if (p_ipdu_inib->ComIPduCallout != NULL_PTR) {
				/* ��¾���ꥢ��ǥ����륢���ȤΥݥ��󥿤���Ф� */
				callout = p_ipdu_inib->ComIPduCallout;
				/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
				p_saved_config = p_cur_com_config;

				/* [COM381] Com_TriggerIPDUSend, Com_SendSignal�ϥ����륢���Ȥ���ƽФ���ǽ�Ȥ��� */
				SchM_Exit_Com_Reentrant_0();
				ret = callout(RxPduId, PduInfoPtr->SduDataPtr);
				SchM_Enter_Com_Reentrant_0();

				/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
				COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_RxIndication);

				if (ret == FALSE) {
					/* [COMa004] FALSE�ξ�硤�ʹߤν�����»ܤ��ʤ� */
					goto error_exit;
				}
			}

			/* IPDU�Хåե��˼����ǡ����򥳥ԡ� */
			for (i = 0U; i < p_ipdu_inib->PduLength; i++) {
				(p_ipdu_inib->p_ipdu_buffer)[i] = (PduInfoPtr->SduDataPtr)[i];
			}

			if (p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) {
				/* [COM300] COM_IMMEDIATE�ʤ�Ф����Ǽ������� */
				ipdu_receive(p_ipdu_inib);
			}
			/* IPDU��������֤����� */
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

	/* [COM652] ����ߤ���ƤӽФ�����ǽ��������Τ���¾��ɬ�� */
	SchM_Enter_Com_Reentrant_1();

	COM_CHECK_INITIALIZED(COMServiceId_TxConfirmation);
	COM_CHECK_PARAM(TxPduId < GET_IPDU_NUM(), COMServiceId_TxConfirmation);

	p_ipdu_inib = GET_TX_IPDU_INIB(TxPduId);

	COM_CHECK_PARAM(p_ipdu_inib->ComIPduDirection == COM_SEND, COMServiceId_TxConfirmation);

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

	/* PduR_ComTransmit�������������Τ߼����դ��� */
	if (p_tx_ipdu_cb->queuing_cnt != 0U) {
		p_tx_ipdu_cb->queuing_cnt--;

		/* [COM577] */
		if (p_tx_ipdu_inib->ComTxIPduClearUpdateBit == COM_CONFIRMATION) {
			for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
				p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
				/* ���åץǡ��ȥӥåȥ��ꥢ */
				clear_updatebit(p_signal_inib);
			}
		}

		/* [COM469] MDT�����󥿤�0����礭����硤MDT�����󥿤�����ꤹ�� */
		if (p_tx_ipdu_inib->ComMinimumDelayTime > 0U) {
			mdt_set(p_ipdu_inib);
		}

		if (p_tx_ipdu_cb->repeat_cnt > 0U) {
			p_tx_ipdu_cb->repeat_cnt--;
		}

		/* IPDU������ */
		/* [COMa002] IPDU��߻���RTE�����Τ�Ԥ�ʤ� */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			/* ������λ���� */
			if (p_tx_ipdu_cb->repeat_cnt == 0U) {
				IPDU_CLEAR_UPDATED(p_ipdu_inib->p_state);
				/* ����Ƚ�� */
				if (p_ipdu_inib->ComIPduSignalProcessing == COM_IMMEDIATE) {
					for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
						p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);
						if (p_signal_inib->ComNotification != NULL_PTR) {
							/* ��¾���ꥢ��ǥ�����Хå��Υݥ��󥿤���Ф� */
							notification = p_signal_inib->ComNotification;
							/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
							p_saved_config = p_cur_com_config;

							/* ������λ���� */
							SchM_Exit_Com_Reentrant_1();
							notification();
							SchM_Enter_Com_Reentrant_1();

							/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
							COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_TxConfirmation);
						}
					}
					/* [COM308] DM��� */
					IPDU_CLEAR_DM(p_ipdu_inib->p_state);
				}
				else {
					/* Com_MainFunctionTx�����Τ��� */
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

	/* [COM664] ���������Ƥ��ʤ����ϲ��⤻����return */
	if (com_state != COM_INIT) {
		goto error_exit;
	}

	for (i = 0U; i < GET_RX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_RX_IPDU_INIB(i);

		/* IPDU����Ƚ��(���Ͼ���) */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {
			if (IPDU_IS_NOTICED(p_ipdu_inib->p_state)) {
				if (p_ipdu_inib->ComIPduSignalProcessing == COM_DEFERRED) {
					/* [COM301] �������֤ȤʤäƤ���COM_DEFERRED��IPDU�Ϥ����Ǽ��������򤹤� */
					ipdu_receive(p_ipdu_inib);
				}

				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);

					if (check_updatebit(p_signal_inib) != FALSE) {
						/*
						 * [COM715][NCOM031][COM738] ����DM�����󥿥ꥻ�åȽ���
						 * [NCOM034] ����DM��ꥻ�åȤ�����硤����DM������å����ʤ�
						 */
						reset_signal_dm(p_signal_inib);
					}
					else {
						/* ���åץǡ��ȥӥåȤ���������Ƥʤ������ʥ�ϼ���DM������å����� */
						check_signal_dm(p_signal_inib);
					}
				}

				/* IPDU�μ������֤򥯥ꥢ */
				IPDU_CLEAR_NOTICED(p_ipdu_inib->p_state);
			}
			else {
				/* [COM290][COM292][NCOM035]�������֤Ǥʤ���IPDU�ϼ���DM������å����� */
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

	/* [COM665] ���������Ƥ��ʤ����ϲ��⤻����return */
	if (com_state != COM_INIT) {
		goto error_exit;
	}

	for (i = 0U; i < GET_TX_IPDU_NUM(); i++) {
		p_ipdu_inib = GET_TX_IPDU_INIB(i);
		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

		/* IPDU����ߤ��Ƥ��Ƥ���֤Ϸв᤹�� */
		mdt_countdown(p_tx_ipdu_cb);

		/* [COM777] IPDU����Ƚ�� IPDU����ߤ��Ƥ�����ϡ��������ʤ� */
		if (IPDU_IS_STARTED(p_ipdu_inib->p_state)) {

			COM_CHECK_PARAM(((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode >= COM_DIRECT) &&
							 (p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode <= COM_MIXED)) ||
							(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_NONE), COMServiceId_MainFunctionTx);

			/* ����Ƚ�� */
			if (IPDU_IS_NOTICED(p_ipdu_inib->p_state)) {
				for (j = 0U; j < p_ipdu_inib->tnum_signal; j++) {
					p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[j]);
					if (p_signal_inib->ComNotification != NULL_PTR) {
						/* ��¾���ꥢ��ǥ�����Хå��Υݥ��󥿤���Ф� */
						notification = p_signal_inib->ComNotification;
						/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
						p_saved_config = p_cur_com_config;

						/* ������λ���� */
						SchM_Exit_Com_Reentrant_0();
						notification();
						SchM_Enter_Com_Reentrant_0();

						/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
						COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_MainFunctionTx);
					}
				}
				IPDU_CLEAR_NOTICED(p_ipdu_inib->p_state);
				/* DM��� */
				IPDU_CLEAR_DM(p_ipdu_inib->p_state);
			}
			/* DM������� */
			else {
				if (p_tx_ipdu_cb->dm_mf_cnt > 0U) {
					p_tx_ipdu_cb->dm_mf_cnt--;
				}

				/* ���������ॢ����ȯ�� */
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
					/* [COM308] DM��� */
					IPDU_CLEAR_DM(p_ipdu_inib->p_state);
					/* [COM392] �����򤷤ʤ� */
					IPDU_CLEAR_UPDATED(p_ipdu_inib->p_state);
					/* ���塼���󥰤�0�ǽ�������� */
					p_tx_ipdu_cb->repeat_cnt = 0U;

#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
					/* [COM775] ��α���줿�����׵��̵���ˤ��� */
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
				/* ���⤷�ʤ� */
				send_flg = E_NOT_SEND;
			}

			/* Com_TriggerIPDUSend�������뤵�줿��� */
			if (IPDU_IS_TRIGGERED(p_ipdu_inib->p_state)) {
				send_flg = trigger_send(p_ipdu_inib, send_flg);
			}

			/* ���������ξ�� */
			if (send_flg == E_OK) {
				/* ���塼���󥰤���(���0xFF) */
				if (p_tx_ipdu_cb->queuing_cnt != COM_INVALID_UINT8) {
					p_tx_ipdu_cb->queuing_cnt++;
				}

				/* [COM062] ���åץǡ��ȥӥåȥ��ꥢ */
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
 *  �����ʥ�Хåե��ؤΥ����ʥ�ǡ�����Ǽ(������)
 */
LOCAL_INLINE void
set_signal_for_send(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	uint16 i;

	/* �����ʥ�Хåե������פʥ����ʥ�ˤϳ�Ǽ���ʤ� */
	if (p_signal_inib->p_signal_buffer != NULL_PTR) {
		/* [COM353]����¦�Ǥ�����ĥ���ʤ� */
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
			 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_SINT8��COM_SINT16��COM_SINT32��COM_UINT8��COM_UINT16��
			 *  COM_UINT32��COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�ʳ������ꤵ��뤳�ȤϤʤ�
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_set_signal_for_send);
			break;
		}
	}

  error_exit:
	return;
}

/*
 *  �����ʥ�Хåե��ؤΥ����ʥ�ǡ�����Ǽ(������)
 */
LOCAL_INLINE void
set_signal_for_receive(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	uint16 i;

	/* ����¦�Υ����ʥ�Хåե���ɬ��¸�ߤ��� */
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
		 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_SINT8��COM_SINT16��COM_SINT32��COM_UINT8��COM_UINT16��
		 *  COM_UINT32��COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�ʳ������ꤵ��뤳�ȤϤʤ�
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_set_signal_for_receive);
		break;
	}

  error_exit:
	return;
}

/*
 *  �����ʥ�ǡ����������ͤ����
 */
LOCAL_INLINE boolean
changed_signal(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	boolean	ret = FALSE;
	uint16	i;

	/* �����ʥ�Хåե������פʾ�����Ӥ��ʤ� */
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
			 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_SINT8��COM_SINT16��COM_SINT32��COM_UINT8��COM_UINT16��
			 *  COM_UINT32��COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�ʳ������ꤵ��뤳�ȤϤʤ�
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
 *  �����ʥ�Хåե�����Υ����ʥ�ǡ������Ф�
 */
LOCAL_INLINE void
get_signal(const SIGNAL_INIB *p_signal_inib, void *p_data)
{
	uint16 i;

	/* �����ʥ�ǡ����μ��Ф��ϼ������ΤߤǤ���Τ�ɬ���Хåե���¸�ߤ��� */
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
		 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_SINT8��COM_SINT16��COM_SINT32��COM_UINT8��COM_UINT16��
		 *  COM_UINT32��COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�ʳ������ꤵ��뤳�ȤϤʤ�
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_get_signal);
		break;
	}

  error_exit:
	return;
}

/*
 * �ե��륿�Хåե������ʥ�ǡ�����Ǽ(����)
 */
LOCAL_INLINE void
set_filter_buffer(const SIGNAL_INIB	*p_signal_inib, const void *p_data)
{
	const void *p_filter_inib;

	/* COM_MASKED_NEW_DIFFERS_MASKED_OLD���������ͤ���Ѥ��ʤ� */
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
			 *  �ܴؿ��ΰ�����COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�����ꤵ��뤳�ȤϤʤ�
			 *  ��[COM380] COM_UINT8_N�Υ����ʥ뤬�ե��륿����ľ�硤ComFilterAlgorithm��COM_NEVER�ޤ���COM_ALWAYS�Ǥ���
			 *  ��[COM319] COM_FLOAT32��COM_FLOAT64�Υ����ʥ�ξ�硤�ե��륿������ʤ�
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_set_filter_buffer);
			break;
		}
	}

  error_exit:
	return;
}

/*
 *  �ƥǡ�������uint32�إ��ԡ�
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
		/* uninitialized�ٹ��޻� */
		signal_data = 0U;
		/*
		 *  �ܴؿ��ΰ�����COM_FLOAT64�����ꤵ��뤳�ȤϤʤ�
		 *  ��packing�ؿ��Ǥϡ�if��COM_FLOAT64��ʬ�����Ƥ���
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_copy_signal_to_uint32);
		break;
	}

  error_exit:
	return(signal_data);
}

/*
 *  �ƥǡ�������sint32�إ��㥹�Ȥ���
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
		/* uninitialized�ٹ��޻� */
		signal_data = 0;
		/*
		 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_UINT8��COM_UINT16��COM_UINT32��COM_FLOAT32��COM_FLOAT64�����ꤵ��뤳�ȤϤʤ�
		 *  ��[COM319] filtering�ؿ��Ǥϡ�float������Ѥ��ʤ�
		 */
		COM_CHECK_PARAM(FALSE, COMServiceId_cast_signal_to_sint32);
		break;
	}

  error_exit:
	return(signal_data);
}

/*
 * ̵���ͤ��Ф������
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
			 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_SINT8��COM_SINT16��COM_SINT32��COM_UINT8��COM_UINT16��
			 *  COM_UINT32��COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�ʳ������ꤵ��뤳�ȤϤʤ�
			 */
			COM_CHECK_PARAM(FALSE, COMServiceId_invalid_action);
			break;
		}
	}
	else {
		/* NULL_PTR�ξ�硤̵���ͤǤϤʤ���ΤȤ��ư��� */
		is_invalid = FALSE;
	}

	if (is_invalid != FALSE) {
		if (p_signal_inib->ComDataInvalidAction == COM_NOTIFY) {
			/* [COM680][COM717] ComInvalidNotification�ˤ�RTE�����Τ����ե��륿��󥰡������ʥ����Ρ������ʥ�Хåե��ؤγ�Ǽ�ϼ»ܤ��ʤ� */
			if (p_signal_inib->ComInvalidNotification != NULL_PTR) {
				/* ��¾���ꥢ��ǥ�����Хå��Υݥ��󥿤���Ф� */
				notification = p_signal_inib->ComInvalidNotification;
				/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
				p_saved_config = p_cur_com_config;

				/* ������λ���� */
				SchM_Exit_Com_Reentrant_0();
				notification();
				SchM_Enter_Com_Reentrant_0();

				/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
				COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_invalid_action);
			}
			is_notified = FALSE;
		}
		else if (p_signal_inib->ComDataInvalidAction == COM_REPLACE) {
			/* [COM681] COM_REPLACE�ξ�硤ComSignalInitValue�ǥ����ʥ�򹹿����� */
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
				 *  �ܴؿ��ΰ�����COM_BOOLEAN��COM_SINT8��COM_SINT16��COM_SINT32��COM_UINT8��COM_UINT16��
				 *  COM_UINT32��COM_UINT8_N��COM_FLOAT32��COM_FLOAT64�ʳ������ꤵ��뤳�ȤϤʤ�
				 */
				COM_CHECK_PARAM(FALSE, COMServiceId_invalid_action);
				break;
			}
		}
		else {
			/*
			 *  ̵���ͤǤ���(p_signal_inib->ComDataInvalidAction == COM_INVALID_UINT8)
			 *  [COM736] ComDataInvalidAction�����ꤵ��Ƥ��ʤ���С�ͭ�����ͤ���������Ƥ����ΤȤߤʤ�
			 */
		}
	}

  error_exit:
	return(is_notified);
}

/*
 *  IPDU�ν����
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

			/* [COM604] IPDU�Хåե���ComSignalInitValue�����ꤹ�� */
			packing(p_signal_inib, p_signal_inib->ComSignalInitValue);
			/* [COM228] �����ʥ�Хåե���ComSignalInitValue���Ǽ���� */
			set_signal_for_send(p_signal_inib, p_signal_inib->ComSignalInitValue);
			/* [COM603] �ե��륿�Хåե���ComSignalInitValue���Ǽ���� */
			set_filter_buffer(p_signal_inib, p_signal_inib->ComSignalInitValue);

			p_tx_signal_cb = (TX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
			if ((p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) && (p_tx_signal_cb != NULL_PTR)) {
				if (p_signal_inib->ComFilterAlgorithm == COM_ONE_EVERY_N) {
					p_filter_one_every_n_inib = (const FILTER_ONE_EVERY_N_INIB *) p_signal_inib->p_filter_inib;
					COM_CHECK_PARAM((p_filter_one_every_n_inib != NULL_PTR) &&
									(p_filter_one_every_n_inib->p_occur != NULL_PTR), COMServiceId_ipdu_initialize);
					/* [COM231] OCCURRENCE��0�����ꤹ�� */
					*(p_filter_one_every_n_inib->p_occur) = 0U;
				}
				/* TMCȽ�� */
				p_tx_signal_cb->tmc = filtering(p_signal_inib, p_signal_inib->ComSignalInitValue);
			}

			/* ���åץǡ��ȥӥåȥ��ꥢ */
			clear_updatebit(p_signal_inib);
		}

		p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;
		p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

		/* TMS����ꤷ�������⡼�ɤ���ꤹ�� */
		if (check_tms(p_ipdu_inib) != FALSE) {
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_true_inib;
		}
		else {
			p_tx_ipdu_cb->p_cur_tx_mode_inib = p_tx_ipdu_inib->p_tx_mode_false_inib;
		}

		/* [COM222] �����⡼�ɤ�COM_PERIODIC��COM_MIXED��IPDU�μ�����MF��������󥿤�ComTxModeTimeOffset�ǽ���� */
		if ((p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_PERIODIC) ||
			(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeMode == COM_MIXED)) {
			p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimeOffset;
		}
	}
	else {
		for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
			p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);

			/* �����ʥ�Хåե���ComSignalInitValue���Ǽ���� */
			set_signal_for_receive(p_signal_inib, p_signal_inib->ComSignalInitValue);

			if (p_signal_inib->ComFilterAlgorithm == COM_ONE_EVERY_N) {
				p_filter_one_every_n_inib = (const FILTER_ONE_EVERY_N_INIB *) p_signal_inib->p_filter_inib;
				COM_CHECK_PARAM((p_filter_one_every_n_inib != NULL_PTR) &&
								(p_filter_one_every_n_inib->p_occur != NULL_PTR), COMServiceId_ipdu_initialize);
				/* ComFilterOffset��0�ξ����θ����OCCURRENCE��0�ǽ�������� */
				*(p_filter_one_every_n_inib->p_occur) = 0U;
			}

			/* DM��� */
			p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;
			if (p_rx_signal_cb != NULL_PTR) {
				p_rx_signal_cb->dm_state = COM_STOP;
			}

			/* [COM603] �ե��륿�Хåե���ComSignalInitValue���Ǽ���� */
			set_filter_buffer(p_signal_inib, p_signal_inib->ComSignalInitValue);
		}
	}

	/* IPDU_STARTED_BIT�ʳ���CLEAR���� */
	IPDU_CLEAR_EXCEPT_STARTED(p_ipdu_inib->p_state);

  error_exit:
	return;
}

/*
 *  �����ʥ�ѥå���
 *  [COM007][COM580] ����ǥ������Ѵ�
 */
LOCAL_INLINE void
packing(const SIGNAL_INIB *p_signal_inib, const void *p_data)
{
	const IPDU_INIB	*p_ipdu_inib;
	const uint8		*p_signal_data;     /* �����ʥ�ǡ����Υݥ��� */
	PduLengthType	byte_index;         /* ComBitPosition����°����IPDU��Byte���� */
	uint8			pos_lsb;            /* LSB��Bit���� */
	uint16			i;
	uint32			signal_data;        /* �����ʥ�ǡ��� */
	uint32			low_signal_data;    /* COM_FLOAT64�ξ�硤�����ʥ�ǡ�������32bit */
	uint32			high_signal_data;   /* COM_FLOAT64�ξ�硤�����ʥ�ǡ������32bit */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	byte_index = p_signal_inib->ComBitPosition / 8U;
	pos_lsb = (uint8) (p_signal_inib->ComBitPosition % 8U);

	COM_CHECK_PARAM((p_signal_inib->ComSignalEndianness >= COM_BIG_ENDIAN) &&
					(p_signal_inib->ComSignalEndianness <= COM_OPAQUE), COMServiceId_packing);
	COM_CHECK_PARAM((p_signal_inib->ComSignalType >= COM_BOOLEAN) &&
					(p_signal_inib->ComSignalType <= COM_FLOAT64), COMServiceId_packing);

	if (p_signal_inib->ComSignalEndianness == COM_OPAQUE) {
		/* COM_OPAQUE�ξ�硤ComBitPosition��8���ܿ��Ǥ���ɬ�פ��� */
		COM_CHECK_PARAM(pos_lsb == 0U, COMServiceId_packing);

		p_signal_data = (const uint8 *) p_data;

		/* [COM443][COM472] COM_OPAQUE��COM_UINT8_N�Τ� */
		for (i = 0U; i < p_signal_inib->ComSignalLength; i++) {
			/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
			(p_ipdu_inib->p_ipdu_buffer)[byte_index] = p_signal_data[i];

			/* [COM259_Conf] COM_OPAQUE��COM_LITTLE_ENDIAN�Ȥ��� */
			byte_index++;
		}
	}
	else {
		if (p_signal_inib->ComSignalType == COM_FLOAT64) {
			/* ����32bit������� */
			low_signal_data = (uint32) ((*(const uint64 *) p_data) & ((uint32) 0xFFFFFFFF));

			/* ���32bit������� */
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
			/* ���������ǡ������оݥǡ��������Ѵ� */
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
	uint8	pos_msb;    /* MSB��Bit���� */

	/* ��Ǽ�ϰϤ�1Byte����Ǥ����� */
	if ((pos_lsb + bitsize) <= 8U) {
		pos_msb = (pos_lsb + bitsize) - 1U;
		mask = ((uint8) (0xFFU << pos_lsb)) & (0xFFU >> ((uint8) (7U - pos_msb)));

		/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
	}
	else {
		mask = (uint8) (0xFFU << pos_lsb);

		/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
		signal_data >>= 8U - pos_lsb;
		bitsize -= 8U - pos_lsb;

		byte_index++;

		/* �����ʥ�λĤꥵ������1Byte�ʾ�Ǥ����� */
		while (bitsize >= 8U) {
			/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
			p_buffer[byte_index] = (uint8) signal_data;
			signal_data >>= 8U;
			bitsize -= 8U;

			byte_index++;
		}

		/* �����ʥ�λĤꥵ������������ */
		if (bitsize != 0U) {
			mask = (uint8) (0xFFU >> (8U - bitsize));
			/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
			p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) (signal_data & ((uint32) mask)));
		}
	}

	return;
}

LOCAL_INLINE void
pack_big_endian(uint8 p_buffer[], PduLengthType byte_index, uint8 pos_lsb, uint8 bitsize, uint32 signal_data)
{
	uint8	mask;
	uint8	pos_msb;    /* MSB��Bit���� */

	/* ��Ǽ�ϰϤ�1Byte����Ǥ����� */
	if ((pos_lsb + bitsize) <= 8U) {
		pos_msb = (pos_lsb + bitsize) - 1U;
		mask = ((uint8) (0xFFU << pos_lsb)) & (0xFFU >> ((uint8) (7U - pos_msb)));

		/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
	}
	else {
		mask = (uint8) (0xFFU << pos_lsb);

		/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
		p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) ((signal_data << pos_lsb) & ((uint32) mask)));
		signal_data >>= 8U - pos_lsb;
		bitsize -= 8U - pos_lsb;

		byte_index--;

		/* �����ʥ�λĤꥵ������1Byte�ʾ�Ǥ����� */
		while (bitsize >= 8U) {
			/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
			p_buffer[byte_index] = (uint8) signal_data;
			signal_data >>= 8U;
			bitsize -= 8U;

			byte_index--;
		}

		/* �����ʥ�λĤꥵ������������ */
		if (bitsize != 0U) {
			mask = (uint8) (0xFFU >> (8U - bitsize));
			/* IPDU�Хåե��˥����ʥ�ǡ������Ǽ */
			p_buffer[byte_index] = (p_buffer[byte_index] & ((uint8) (~mask))) | ((uint8) (signal_data & ((uint32) mask)));
		}
	}

	return;
}

/*
 *  ��������
 */
LOCAL_INLINE void
ipdu_receive(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB		*p_signal_inib;
	const Com_ConfigType	*p_saved_config;
	void					*p_unpack_data;
	uint64					temp_data;      /* ���祵������COM_FLOAT64 */
	Com_CbkAck				notification;
	uint16					i;

	for (i = 0U; i < p_ipdu_inib->tnum_signal; i++) {
		p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[i]);

		/* [COM324] ���åץǡ��ȥӥåȤ���������Ƥ����硤�ե��륿��󥰡����Ρ�����ѥå������ν�����»ܤ��� */
		if (check_updatebit(p_signal_inib) != FALSE) {

			if (p_signal_inib->ComSignalEndianness == COM_OPAQUE) {
				/* COM_UINT8_N�ϥХ��ȥ��饤�󤵤�Ƥ���Τ�IPDU�Хåե��򤽤Τޤ޻��Ѥ��� */
				p_unpack_data = (void *) &((p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComBitPosition / 8U]);
			}
			else {
				/* COM_UINT8_N�ʳ��ϰ���Хåե��˥���ѥå��� */
				unpacking(p_signal_inib, &temp_data);
				p_unpack_data = (void *) &temp_data;
			}

			/*
			 *  [COM396] �������������ʥ���Ф��ưʲ��ν�ǽ�������
			 *           1) ̵���ͽ���
			 *           2) �ե��륿���
			 *           3) ����
			 */
			/* ̵���ͽ���([COM680][COM717]RTE�����Τ�����ϸ�³�ν����򤷤ʤ�) */
			if (invalid_action(p_signal_inib, p_unpack_data) != FALSE) {
				/* [COM273][COM695] �ե��륿��󥰷�̤�false�ξ�硤�����ʥ���˴��������Υ����ʥ���Ф��������Ԥ�ʤ� */
				if ((p_signal_inib->ComFilterAlgorithm == COM_INVALID_UINT8) || (filtering(p_signal_inib, p_unpack_data) != FALSE)) {
					/* �����ʥ�Хåե��˥���ѥå������ǡ������Ǽ */
					set_signal_for_receive(p_signal_inib, p_unpack_data);

					/* [COM574] �����˼������������ʥ���Ф���ComNotification�����ꤷ���ؿ���Ƥ� */
					if (p_signal_inib->ComNotification != NULL_PTR) {
						/* ��¾���ꥢ��ǥ�����Хå��Υݥ��󥿤���Ф� */
						notification = p_signal_inib->ComNotification;
						/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
						p_saved_config = p_cur_com_config;

						SchM_Exit_Com_Reentrant_0();
						notification();
						SchM_Enter_Com_Reentrant_0();

						/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
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
 *  �����ʥ륢��ѥå���
 *  [COM007] ����ǥ������Ѵ�������ĥ
 */
LOCAL_INLINE void
unpacking(const SIGNAL_INIB *p_signal_inib, void *p_data)
{
	const IPDU_INIB	*p_ipdu_inib;
	PduLengthType	byte_index;             /* ComBitPosition����°����IPDU��Byte���� */
	uint8			pos_lsb;                /* LSB��Bit���� */
	uint8			bitsize;
	uint8			left_size;              /* ����ѥå����륷���ʥ�λĤꥵ���� */

	p_ipdu_inib = p_signal_inib->p_ipdu_inib;
	pos_lsb = (uint8) (p_signal_inib->ComBitPosition % 8U);
	byte_index = p_signal_inib->ComBitPosition / 8U;

	COM_CHECK_PARAM((p_signal_inib->ComSignalEndianness != COM_OPAQUE) &&
					((p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) ||
					 (p_signal_inib->ComSignalEndianness == COM_BIG_ENDIAN)), COMServiceId_unpacking);

	/* ����ѥå��� */
	/* [COM352] �ե��륿��󥰤����θ��Ф�Ԥ���������ĥ�ȥ���ǥ������Ѵ���Ԥ� */
	bitsize = p_signal_inib->ComBitSize;

	/* ��Ǽ�ϰϤ�1Byte����Ǥ����� */
	if ((pos_lsb + bitsize) <= 8U) {
		/* �����ʥ�ǡ�����IPDU�Хåե��Υǡ������Ǽ */
		*(uint64 *) p_data = (uint64) (((p_ipdu_inib->p_ipdu_buffer)[byte_index] >> pos_lsb) & (0xFFU >> (8U - bitsize)));
	}
	else {
		/* �����ʥ�ǡ�����IPDU�Хåե��Υǡ������Ǽ */
		*(uint64 *) p_data = (uint64) ((p_ipdu_inib->p_ipdu_buffer)[byte_index] >> pos_lsb);

		/* �����ʥ�λĤꥵ�����򻻽� */
		left_size = bitsize - (8U - pos_lsb);

		if (p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) {
			byte_index++;
		}
		else {
			byte_index--;
		}

		/* �����ʥ�λĤꥵ������1Byte�ʾ�Ǥ����� */
		while (left_size >= 8U) {
			/* �����ʥ�ǡ�����IPDU�Хåե��Υǡ����򡤤����ޤǤ˳�Ǽ�����ӥå�ʬ�����եȤ��Ƴ�Ǽ */
			*(uint64 *) p_data += (((uint64) ((p_ipdu_inib->p_ipdu_buffer)[byte_index])) << (bitsize - left_size));
			left_size -= 8U;

			if (p_signal_inib->ComSignalEndianness == COM_LITTLE_ENDIAN) {
				byte_index++;
			}
			else {
				byte_index--;
			}
		}

		/* �����ʥ�λĤꥵ������������ */
		if (left_size != 0U) {
			/* �����ʥ�ǡ�����IPDU�Хåե��Υǡ����򡤤����ޤǤ˳�Ǽ�����ӥå�ʬ�����եȤ��Ƴ�Ǽ */
			*(uint64 *) p_data += ((uint64) (((p_ipdu_inib->p_ipdu_buffer)[byte_index]) & (0xFFU >> (8U - left_size))) << (bitsize - left_size));
		}
	}

	/* [COM008] ����¦�Ǥ�����ĥ���� */
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
		 *  ����ѥå��󥰽�����COM_UINT�����Ѥ��ƹԤäƤ��뤿�ᡤCOM_UINT��������ĥ������
		 *  [COM579] COM_FLOAT��������ĥ�ϹԤ�ʤ�
		 */
		break;
	}

  error_exit:
	return;
}

/*
 *  ���åץǡ��ȥӥå�����
 */
LOCAL_INLINE void
set_updatebit(const SIGNAL_INIB *p_signal_inib)
{
	const IPDU_INIB	*p_ipdu_inib;

	if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
		p_ipdu_inib = p_signal_inib->p_ipdu_inib;
		/* [COM059] 0:�����ʤ���1:�������� */
		(p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComUpdateBitPosition / 8U] |= (uint8) (1U << (p_signal_inib->ComUpdateBitPosition % 8U));
	}

	return;
}

/*
 *  ���åץǡ��ȥӥåȥ��ꥢ
 */
LOCAL_INLINE void
clear_updatebit(const SIGNAL_INIB *p_signal_inib)
{
	const IPDU_INIB	*p_ipdu_inib;

	if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
		p_ipdu_inib = p_signal_inib->p_ipdu_inib;
		/* [COM059] 0:�����ʤ���1:�������� */
		(p_ipdu_inib->p_ipdu_buffer)[p_signal_inib->ComUpdateBitPosition / 8U] &= (uint8) (~((uint8) (1U << (p_signal_inib->ComUpdateBitPosition % 8U))));
	}

	return;
}

/*
 *  PduR�ؤ�����
 *  [COM495] PduR�ؤ�������ɬ��mdt_send����Ѥ��뤿�ᡤTMS���ػ���MDT����θ�����
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
		/* [COM346][COM719] �����륢���Ƚ��� */
		if (p_ipdu_inib->ComIPduCallout != NULL_PTR) {
			/* ��¾���ꥢ��ǳƾ������Ф� */
			callout = p_ipdu_inib->ComIPduCallout;
			pduid = p_ipdu_inib->PduRSourcePduHandleId;
			p_pdubuffer = p_ipdu_inib->p_ipdu_buffer;

			/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
			p_saved_config = p_cur_com_config;

			/* [COM381] Com_TriggerIPDUSend, Com_SendSignal�ϥ����륢���Ȥ���ƽФ���ǽ�Ȥ��� */
			SchM_Exit_Com_Reentrant_0();
			ret_callout = callout(pduid, p_pdubuffer);
			SchM_Enter_Com_Reentrant_0();

			/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
			COM_CHECK_PARAM(p_saved_config == p_cur_com_config, COMServiceId_mdt_send);

			if (ret_callout == FALSE) {
				ret_transmit = E_OK;
				/* [COMa004] FALSE�ξ�硤�ʹߤν�����»ܤ��ʤ� */
				goto no_error_exit;
			}
		}

		/* IPDU�������� */
		pduinfo.SduDataPtr = p_ipdu_inib->p_ipdu_buffer;
		pduinfo.SduLength = p_ipdu_inib->PduLength;

		/* [COM138][COM239] IPDU���� */
		ret_transmit = PduR_ComTransmit(p_ipdu_inib->PduRSourcePduHandleId, &pduinfo);

/* [COM773][COM779] ���Ԥ��������׵�Υ�ȥ饤 */
#if COM_RETRY_FAILED_TRANSMIT_REQUESTS == STD_ON
		if (ret_transmit != E_NOT_OK) {
			/* IPDU�����������������Τ�MDT�����ꤹ�� */
			mdt_set(p_ipdu_inib);
		}
#else
		/* COM_RETRY_FAILED_TRANSMIT_REQUESTS��STD_OFF�ξ��ϡ���ΧMDT�����ꤹ�� */
		mdt_set(p_ipdu_inib);
#endif
	}
	else {
		ret_transmit = E_NOT_OK;
	}

	/* ����DM���� */
	start_tx_dm(p_ipdu_inib);

  no_error_exit:
	return(ret_transmit);

  error_exit:
	ret_transmit = E_NOT_OK;
	goto no_error_exit;
}

/*
 *  MDT���������
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
 *  MDT�����󥿤򥻥å�
 */
LOCAL_INLINE void
mdt_set(const IPDU_INIB *p_ipdu_inib)
{
	const TX_IPDU_INIB	*p_tx_ipdu_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;
	p_tx_ipdu_inib = p_ipdu_inib->p_tx_ipdu_inib;

/* [COM789] �Ǿ��ٱ���֥�˥���󥰤�Ԥ�ʤ�(ComTransferProperty��WITHOUT_REPETITION�ʳ��ξ��) */
#if COM_ENABLE_MDT_FOR_CYCLIC_TRANSMISSION == STD_OFF
	if (IPDU_IS_WITHOUT_REPETITION(p_ipdu_inib->p_state)) {
		p_tx_ipdu_cb->mdt_mf_cnt = p_tx_ipdu_inib->ComMinimumDelayTime;
	}
	else {
		p_tx_ipdu_cb->mdt_mf_cnt = 0U;
	}
#else
	/* [COM471][COM698] MDT���������� 0�ξ���MDT��˥���󥰤��ʤ� */
	p_tx_ipdu_cb->mdt_mf_cnt = p_tx_ipdu_inib->ComMinimumDelayTime;
#endif

	return;
}

/*
 *  �ե��륿��󥰽���
 *  [COM132][COM674] ����դ��ǡ������Ф��Ƥ�ե��륿��󥰤�Ԥ�
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

	/* [COM325] ���٤ƤΥե��륿���르�ꥺ��򥵥ݡ��� */
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
		 *  [COM319] COM_FLOAT32��COM_FLOAT64�Υ����ʥ�ξ�硤�ե��륿������ʤ�
		 *  [COM380] COM_UINT8_N�Υ����ʥ뤬�ե��륿����ľ�硤ComFilterAlgorithm��COM_NEVER�ޤ���COM_ALWAYS�Ǥ���
		 */

		p_filter_inib = p_signal_inib->p_filter_inib;
		switch (p_signal_inib->ComFilterAlgorithm) {
		case COM_MASKED_NEW_EQUALS_X:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalType��UINT�Ϥξ�硤FILTER_UINT_MASKED_INIB�˥��㥹�Ȥ��� */
				if ((new_uint_data & ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) == ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalType��SINT�Ϥξ�硤FILTER_SINT_MASKED_INIB�˥��㥹�Ȥ��� */
				if ((new_sint_data & ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) == ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			break;
		case COM_MASKED_NEW_DIFFERS_X:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalType��UINT�Ϥξ�硤FILTER_UINT_MASKED_INIB�˥��㥹�Ȥ��� */
				if ((new_uint_data & ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) != ((const FILTER_UINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalType��SINT�Ϥξ�硤FILTER_SINT_MASKED_INIB�˥��㥹�Ȥ��� */
				if ((new_sint_data & ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterMask) != ((const FILTER_SINT_MASKED_INIB *) p_filter_inib)->ComFilterX) {
					result = TRUE;
				}
			}
			break;
		case COM_MASKED_NEW_DIFFERS_MASKED_OLD:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalType��UINT�Ϥξ�硤FILTER_UINT_MASKED_OLD_INIB�˥��㥹�Ȥ��� */
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
				/* ComSignalType��SINT�Ϥξ�硤FILTER_SINT_MASKED_OLD_INIB�˥��㥹�Ȥ��� */
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
				/* ComSignalType��UINT�Ϥξ�硤FILTER_UINT_NEW_IS_INIB�˥��㥹�Ȥ��� */
				if ((((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin <= new_uint_data) && (new_uint_data <= ((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax)) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalType��SINT�Ϥξ�硤FILTER_SINT_NEW_IS_INIB�˥��㥹�Ȥ��� */
				if ((((const FILTER_SINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin <= new_sint_data) && (new_sint_data <= ((const FILTER_SINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax)) {
					result = TRUE;
				}
			}
			break;
		case COM_NEW_IS_OUTSIDE:
			if ((p_signal_inib->ComSignalType >= COM_BOOLEAN) && (p_signal_inib->ComSignalType <= COM_UINT32)) {
				new_uint_data = copy_signal_to_uint32(p_signal_inib, p_data);
				/* ComSignalType��UINT�Ϥξ�硤FILTER_UINT_NEW_IS_INIB�˥��㥹�Ȥ��� */
				if ((new_uint_data < ((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMin) || (((const FILTER_UINT_NEW_IS_INIB *) p_filter_inib)->ComFilterMax < new_uint_data)) {
					result = TRUE;
				}
			}
			else {
				new_sint_data = cast_signal_to_sint32(p_signal_inib, p_data);
				/* ComSignalType��SINT�Ϥξ�硤FILTER_SINT_NEW_IS_INIB�˥��㥹�Ȥ��� */
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
			/* COM231�ˤ�ꡤ�������ʸ��(occurrence % period == offset)��Ʊ���Ȥʤ� */
			if (*(((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->p_occur) == ((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->ComFilterOffset) {
				result = TRUE;
			}
			(*(((const FILTER_ONE_EVERY_N_INIB *) p_filter_inib)->p_occur))++;
			break;
		default:
			/*
			 *  �ܴؿ��ΰ�����COM_MASKED_NEW_EQUALS_X��COM_MASKED_NEW_DIFFERS_X��COM_MASKED_NEW_DIFFERS_MASKED_OLD��COM_NEW_IS_WITHIN��
			 *  COM_NEW_IS_OUTSIDE��COM_ONE_EVERY_N��COM_NEVER��COM_ALWAYS��COM_INVALID_UINT8�ʳ������ꤵ��뤳�ȤϤʤ�
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
 *  TMSȽ��
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
		/* [COM676] �ե��륿����ĥ����ʥ�Τ�TMC��Ƚ�ꤹ�� */
		if (p_signal_inib->ComFilterAlgorithm != COM_INVALID_UINT8) {
			filter = TRUE;

			/* [COM678][COM679] TMC��1�ĤǤ�TRUE�ξ��ϡ�TMS��TRUE�Ȥ��� */
			if (((TX_SIGNAL_CB *) p_signal_inib->p_signal_cb)->tmc != FALSE) {
				tms = TRUE;
				break;
			}
		}
	}

	/* [COM677] �ե��륿����ĥ����ʥ뤬¸�ߤ��ʤ����ϡ�TMS��TRUE�Ȥ��� */
	if (filter == FALSE) {
		tms = TRUE;
	}

	return(tms);
}

/*
 *  ����DM����
 */
LOCAL_INLINE void
start_tx_dm(const IPDU_INIB *p_ipdu_inib)
{
	const SIGNAL_INIB	*p_signal_inib;
	TX_IPDU_CB			*p_tx_ipdu_cb;

	/* �����ʥ��ͼ��� ComTimeout�ͤ�Ʊ��IPDU�Υ����ʥ���Ѳ��Ϥʤ��ΤǺǽ�Υ����ʥ���ͤ�������� */
	p_signal_inib = GET_SIGNAL_INIB((p_ipdu_inib->p_signalid_list)[0]);
	p_tx_ipdu_cb = (TX_IPDU_CB *) p_ipdu_inib->p_ipdu_cb;

	if (!IPDU_IS_DM(p_ipdu_inib->p_state)) {
		/* [COM333] ComTimeout��0�ޤ��ϡ���ά����Ƥ����硤���Υ����ʥ��DM�ƻ�Ϥ��ʤ� */
		if (p_signal_inib->ComTimeout != 0U) {
			/* [COM481][COM739][[COM774]] */
			IPDU_SET_DM(p_ipdu_inib->p_state);
			p_tx_ipdu_cb->dm_mf_cnt = p_signal_inib->ComTimeout;
		}
	}

	return;
}

/*
 *  ����DM����
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

		/* [COM333] ComTimeout��0�ޤ��ϡ���ά����Ƥ����硤���Υ����ʥ��DM�ƻ�Ϥ��ʤ� */
		if (p_rx_signal_cb != NULL_PTR) {
			if (p_signal_inib->ComFirstTimeout == 0U) {
				/* [COM716] ComFirstTimeout��0�ޤ��ϡ���ά����Ƥ����硤�ǽ�μ������Ԥ���ޤǡ����Υ����ʥ��DM�ƻ�Ϥ��ʤ� */
				p_rx_signal_cb->dm_state = COM_WAIT;
			}
			else {
				/* [COM224] ComFirstTimeout�����ꤹ�� */
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
 *  ����DM���
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
			/* �����ʥ��DM�ƻ����ߤ��� */
			p_rx_signal_cb->dm_state = COM_STOP;
		}
	}

	/* DM��� */
	IPDU_CLEAR_DM(p_ipdu_inib->p_state);

	return;
}
/*
 *  ���������ʥ�DMȽ��
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
			/* dm_mf_cnt��ɬ��0����礭���ͤ����ꤵ��Ƥ��� */
			p_rx_signal_cb->dm_mf_cnt--;

			/* �����ʥ�μ���DM��ͭ����DM�����󥿤�Ƚ�ꤹ�� */
			if (p_rx_signal_cb->dm_mf_cnt == 0U) {
				if (p_signal_inib->ComRxDataTimeoutAction == COM_REPLACE) {
					/* [COM470] �����ʥ���ͤ�ComSignalInitValue���֤������� */
					set_signal_for_receive(p_signal_inib, p_signal_inib->ComSignalInitValue);
				}
				/* [COM500] COM_NONE�ޤ��Ͼ�ά����Ƥ�����ϡ����⤷�ʤ� */

				/* [COM744] �����ॢ�������� */
				if (p_signal_inib->ComTimeoutNotification != NULL_PTR) {
					/* ��¾���ꥢ��ǥ�����Хå��Υݥ��󥿤���Ф� */
					notification = p_signal_inib->ComTimeoutNotification;
					/* �ƽ���������å��Ѥ˸��ߤΥ���ե�����졼����������ݻ� */
					p_saved_config = p_cur_com_config;

					/* ������λ���� */
					SchM_Exit_Com_Reentrant_0();
					notification();
					SchM_Enter_Com_Reentrant_0();

					/* ��¾���ꥢ���ǥ���ե�����졼���������Ѳ����Ƥ��ʤ��������å����� */
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
 *  ���������ʥ�DM�ꥻ�å�
 */
LOCAL_INLINE void
reset_signal_dm(const SIGNAL_INIB *p_signal_inib)
{
	RX_SIGNAL_CB *p_rx_signal_cb;

	p_rx_signal_cb = (RX_SIGNAL_CB *) p_signal_inib->p_signal_cb;

	if (p_rx_signal_cb != NULL_PTR) {
		if (p_rx_signal_cb->dm_state != COM_STOP) {
			/* �����ʥ�μ����ǥåɥ饤�󥿥��ޤ�ͭ���Ǥ���Хꥻ�åȤ��� */
			p_rx_signal_cb->dm_mf_cnt = p_signal_inib->ComTimeout;

			if (p_rx_signal_cb->dm_state == COM_WAIT) {
				p_rx_signal_cb->dm_state = COM_START;
			}
		}
	}

	return;
}

/*
 *  ���åץǡ��ȥӥåȹ��������å�
 */
LOCAL_INLINE boolean
check_updatebit(const SIGNAL_INIB *p_signal_inib)
{
	const IPDU_INIB	*p_ipdu_inib;
	PduLengthType	index_update;       /* ComUpdateBitPosition����°����IPDU��Byte���� */
	uint8			pos_update;         /* ComUpdateBitPosition��Bit���� */
	boolean			updated;

	if (p_signal_inib->ComUpdateBitPosition != COM_INVALID_UINT16) {
		index_update = p_signal_inib->ComUpdateBitPosition / 8U;
		pos_update = (uint8) (p_signal_inib->ComUpdateBitPosition % 8U);
		p_ipdu_inib = p_signal_inib->p_ipdu_inib;

		/* [COM067] ���åץǡ��ȥӥåȤ��ͤ����ꤵ��Ƥ���С������ʥ�Ϲ������줿��ΤȤ��� */
		if (((p_ipdu_inib->p_ipdu_buffer)[index_update] & ((uint8) (1U << pos_update))) != 0U) {
			updated = TRUE;
		}
		else {
			updated = FALSE;
		}
	}
	else {
		/* ���åץǡ��ȥӥåȤ�����ʤ����ϡ��������줿��ΤȤ��� */
		updated = TRUE;
	}

	return(updated);
}

/*
 *  COM_DIRECT����
 */
static Std_ReturnType
direct_send(const IPDU_INIB *p_ipdu_inib, TX_IPDU_CB *p_tx_ipdu_cb)
{
	Std_ReturnType ret;

	if (p_tx_ipdu_cb->interval_mf_cnt > 0U) {
		p_tx_ipdu_cb->interval_mf_cnt--;
	}

	/* IPDU������ȥ饤������ */
	if (IPDU_IS_DIRECT_RETRITED(p_ipdu_inib->p_state)) {
		/* [COM582][COM478] IPDU���� */
		ret = mdt_send(p_ipdu_inib);
	}
	/* ��������ֳ֤�MF��������󥿤�0�ξ�� */
	else if (IPDU_IS_UPDATED(p_ipdu_inib->p_state) && (p_tx_ipdu_cb->interval_mf_cnt == 0U)) {
		/* [COM582][COM478] IPDU���� */
		ret = mdt_send(p_ipdu_inib);
		/* �������Ԥξ�� */
		if (ret == E_NOT_OK) {
			IPDU_SET_DIRECT_RETRITED(p_ipdu_inib->p_state);
		}
	}
	else {
		ret = E_NOT_SEND;
	}

	/* ���������ξ�� */
	if (ret == E_OK) {
		IPDU_CLEAR_DIRECT_RETRITED(p_ipdu_inib->p_state);
		p_tx_ipdu_cb->interval_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeRepetitionPeriod;

		/* 1��Τ����������� */
		if (IPDU_IS_WITHOUT_REPETITION(p_ipdu_inib->p_state) ||
			(p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeNumberOfRepetitions == 0U)) {
			IPDU_CLEAR_WITHOUT_REPETITION(p_ipdu_inib->p_state);
			IPDU_CLEAR_UPDATED(p_ipdu_inib->p_state);
		}
	}

	return(ret);
}

/*
 *  COM_PERIODIC����
 */
static Std_ReturnType
periodic_send(const IPDU_INIB *p_ipdu_inib, TX_IPDU_CB *p_tx_ipdu_cb, Std_ReturnType send_flg)
{
	if (p_tx_ipdu_cb->period_mf_cnt > 0U) {
		p_tx_ipdu_cb->period_mf_cnt--;
	}

	/* IPDU������ȥ饤������ */
	if (IPDU_IS_PERIODIC_RETRITED(p_ipdu_inib->p_state)) {
		/* ̤�����ξ�� */
		if (send_flg == E_NOT_SEND) {
			/* [COM478] IPDU���� */
			send_flg = mdt_send(p_ipdu_inib);
		}
		/* ���������ξ�� */
		if (send_flg == E_OK) {
			IPDU_CLEAR_PERIODIC_RETRITED(p_ipdu_inib->p_state);
		}
	}

	/* ������MF��������󥿤�0�ξ�� */
	if (p_tx_ipdu_cb->period_mf_cnt == 0U) {
		/* [COM776] �������֤ΰ�����Ѥ��ʤ� */
		p_tx_ipdu_cb->period_mf_cnt = p_tx_ipdu_cb->p_cur_tx_mode_inib->ComTxModeTimePeriod;

		/* [COM494] COM_DIRECT�������Ѥߤξ�硤�������ʤ� */
		if (send_flg == E_NOT_SEND) {
			/* [COM388] IPDU���� */
			send_flg = mdt_send(p_ipdu_inib);
			/* �������Ԥξ�� */
			if (send_flg == E_NOT_OK) {
				IPDU_SET_PERIODIC_RETRITED(p_ipdu_inib->p_state);
			}
		}
	}

	return(send_flg);
}

/*
 *  Com_TriggerIPDUSend�������뤵�줿���
 */
static Std_ReturnType
trigger_send(const IPDU_INIB *p_ipdu_inib, Std_ReturnType send_flg)
{
	/* ̤�����ξ�� */
	if (send_flg == E_NOT_SEND) {
		/* [COM388] IPDU����(MDT�Τߤ��θ) */
		send_flg = mdt_send(p_ipdu_inib);
	}

	/* ���������ξ�� */
	if (send_flg == E_OK) {
		IPDU_CLEAR_TRIGGERED(p_ipdu_inib->p_state);
	}

	return(send_flg);
}


/*
 *  �ʲ���̤���ݡ��ȵ�ǽ
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
