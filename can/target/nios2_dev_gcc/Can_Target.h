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
 *  $Id: Can_Target.h 599 2014-10-17 01:27:58Z shigihara $
 */

#ifndef TOPPERS_CAN_TARGET_H
#define TOPPERS_CAN_TARGET_H

#include "Can.h"
#include "prc_sil.h"


#define CANC_0_BASE		0x08020000U    /* CAN����ȥ���0�Υ١������ɥ쥹 */

#define EXTEND_CAN_ID_LENGTH	18U             /* ��ĥʬ��CAN-ID�� */
#define ACCEPTANCE_OFFSET		21U             /* �������ץ��󥹥쥸�����Υ��ե��å� */
#define NO_MASK_VAL				0x001FFFFFU     /* �������ץ��󥹥ޥ����쥸����������(�ޥ�������̵) */

/* �⡼�ɥ쥸���� */
#define RESET_MODE			0x00000001U                                                                 /* ư��⡼�ɤ�RESET_MODE�ˤ��� */
#define OPERATING_MODE		0x00000000U                                                                 /* ư��⡼�ɤ�OPERATING_MODE�ˤ��� */
#define LISTEN_ONLY_MODE	0x00000002U                                                                 /* �����ػ� */
#define NO_LISTEN_ONLY_MODE	0x00000000U                                                                 /* �������� */
#define NO_SEND_ACK_MODE	0x00000004U                                                                 /* ACK�����ػ� */
#define SEND_ACK_MODE		0x00000000U                                                                 /* ACK���� */
#define SINGLE_FILTER_MODE	0x00000008U                                                                 /* Single filter mode */
#define DUAL_FILTER_MODE	0x00000000U                                                                 /* Dual filter mode */
#define CANC_MODE_START		(OPERATING_MODE | NO_LISTEN_ONLY_MODE | SEND_ACK_MODE | SINGLE_FILTER_MODE) /* CAN����ȥ����START���� */
#define CANC_MODE_STOP		(RESET_MODE     | NO_LISTEN_ONLY_MODE | SEND_ACK_MODE | SINGLE_FILTER_MODE) /* CAN����ȥ����STOP���� */

/* ������׵� */
#define RECEIVE_IRQ			0x00000001U     /* ������λ */
#define TRANSMIT_IRQ		0x00000002U     /* ������λ */

#define IRQ_SET_DISABLE		0x00000000U     /* [����ߵ��ĥ쥸����]��������׵��ػ� */
#define IRQ_SET_ENABLE		0x00000003U     /* [����ߵ��ĥ쥸����]����γ�����׵����� */
#define TXABORT_CLEAR		0x0000FFFFU     /* [��������󥻥�쥸����]����å������ܥå�����������󥻥� */
#define TXCMP_CLEAR			0x0000FFFFU     /* [������λ�쥸����]������λ�ӥåȥ��ꥢ */
#define TXABORTCMP_CLEAR	0x0000FFFFU     /* [��������󥻥봰λ�쥸����]��������󥻥봰λ�ӥåȥ��ꥢ */
#define RXWAIT_OFF			0x00000000U     /* [�����������ȥ쥸����]�������Ƚ���OFF */
#define RXCMP_CLEAR			0xFFFFFFFFU     /* [������λ�쥸����]������λ�ӥåȥ��ꥢ */
#define RXSELFREQ_CLEAR		0x00000000U     /* [����ռ����׵�쥸����]�������׵�ʤ� */
#define ERROR_CNT_CLEAR		0x00000060U     /* [���顼�����󥿥쥸����]���顼�����󥿤����ͤˤ��� */
#define BAUDRATE_250		0x80007F03U     /* [����å����桤�Х������ߥ󥰥쥸����]�ܡ��졼��:250kbps */
#define BAUDRATE_500		0x80007F01U     /* [����å����桤�Х������ߥ󥰥쥸����]�ܡ��졼��:500kbps */

#define MASK_CAN_ID_MASK	0x1FFFFFFFU     /* CanId�����ޥ��� */
#define MASK_4BIT			0x0000000FU     /* 4�ӥåȥޥ��� */
#define MASK_8BIT			0x000000FFU     /* 8�ӥåȥޥ��� */

/* �ƥ쥸�����ޤǤΥ��ե��åȥ��ɥ쥹 */
#define CANC_MODE_REG							0x0000U     /* �⡼�� */
#define CANC_TXREQ_REG							0x0004U
#define CANC_TXABORT_REG						0x0008U     /* ��������󥻥�쥸���� */
#define CANC_TXCMP_REG							0x000CU
#define CANC_TXABORTCMP_REG						0x0010U
#define CANC_RXWAIT_REG							0x0014U
#define CANC_RXCMP_REG							0x0018U
#define CANC_RXOVERWRITE_REG					0x001CU
#define CANC_RXSELFREQ_REG						0x0020U
#define CANC_STATUS_REG							0x0024U
#define CANC_IRQ_REG							0x0028U
#define CANC_IRQ_EN_REG							0x002CU     /* ����ߵ��ĥ쥸���� */
#define CANC_IRQ_RXEN_REG						0x0030U
#define CANC_CLKDIV_BUSTIM_REG					0x0034U     /* ����å����桤�Х������ߥ� */
#define CANC_ACCEPTANCE_CODE_REG				0x0038U     /* �������ץ��󥹥����ɥ쥸���� */
#define CANC_ACCEPTANCE_MASK_REG				0x003CU     /* �������ץ��󥹥ޥ����쥸���� */
#define CANC_ARBITRATION_LOST_CAPTURE_REG		0x0040U
#define CANC_ERROR_CAPTURE_CODE_REG				0x0044U
#define CANC_ERROR_CNT_REG						0x0048U
#define CANC_MBOXWIN_REG						0x004CU     /* ��å������ܥå���������ɥ��쥸���� */
#define CANC_RXMBOX_ACCEPTANCE_CODE_REG			0x0070U     /* ������å������ܥå����Υ������ץ��󥹥����ɥ쥸���� */
#define CANC_RXMBOX_ACCEPTANCE_MASK_REG			0x0074U     /* ������å������ܥå����Υ������ץ��󥹥ޥ����쥸���� */
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

/* �ɼ���ѥ쥸�������������ޥ��� */
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

/* ������ѥ쥸�������������ޥ��� */
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
 * [CAN077][CAN284][CAN385][CAN386] �������åȰ�¸������
 */
#define BYTE_LENGTH		4U

extern const CAN_CTRL_INIB	*p_cur_can_ctrl_inib_table;
extern uint8				can_interrupt_nested_cnt[];

/* �����ؿ��ץ�ȥ�������� */
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

/* [CAN407] Can_Init��unit_phase1 */
LOCAL_INLINE boolean
can_target_init_unit_phase1(const Can_ConfigType *p_can_config)
{
	/* ��˥åȤ˴ؤ���������̵�� */
	return(TRUE);
}

/* [CAN407] Can_Init��controller_phase1 */
LOCAL_INLINE boolean
can_target_init_controller_phase1(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN259] ����ȥ������߾��֤ǽ���� */
	CANC_WR_MODE_REG(CANC_MODE_STOP);

	return(TRUE);
}

/* [CAN407] Can_Init��controller_phase2 */
LOCAL_INLINE boolean
can_target_init_controller_phase2(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* ����߶ػ� */
	can_target_disable_controller_interrupts(ctrl_id);

	/* �������ץ��󥹥ե��륿������ */
	/* ���ΤΥ������ץ��󥹥����ɥ쥸����(���Ƶ���)������ */
	CANC_WR_ACCEPTANCE_CODE_REG(0xFFFFFFFFU);

	/* ���ΤΥ������ץ��󥹥ޥ����쥸����(���Ƶ���)������ */
	CANC_WR_ACCEPTANCE_MASK_REG(0xFFFFFFFFU);

	return(TRUE);
}

/* [CAN407] Can_Init��controller_phase3 */
LOCAL_INLINE boolean
can_target_init_controller_phase3(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	uint8	i;
	uint32	irq_rxen_reg_set_bit = 1U;
	uint32	bit_offset = 1U;

	/* [CAN236][CAN237][CAN419] �쥸�����ν���� */
	/* ̤�����Υ�å������򥭥�󥻥뤹�� */
	CANC_WR_TXABORT_REG(TXABORT_CLEAR);

	/* ���顼�����󥿥쥸�������ͤ���������(�����������Ȥ���ͤ�0��̵����硤�������顼�����󥿤��ѹ����Բ�) */
	CANC_WR_ERROR_CNT_REG(ERROR_CNT_CLEAR);

	/* ������������׵�쥸�������������׵��̵���ˤ��� */
	CANC_WR_RXSELFREQ_REG(RXSELFREQ_CLEAR);

	/* �����������ȥ쥸�����򥦥����Ƚ������դˤ��� */
	CANC_WR_RXWAIT_REG(RXWAIT_OFF);

	/* ������λ�쥸����������̤��λ�ˤ��� */
	CANC_WR_TXCMP_REG(TXCMP_CLEAR);

	/* ��������󥻥봰λ�쥸��������������󥻥�̤��λ�ˤ��� */
	CANC_WR_TXABORTCMP_REG(TXABORTCMP_CLEAR);

	/* ������λ�쥸����������ǡ���̵���ˤ��� */
	CANC_WR_RXCMP_REG(RXCMP_CLEAR);

	/* ���������С��饤�ȥ쥸��������̤ȯ���ˤ��� */
	CANC_RD_RXOVERWRITE_REG();

	/* ��������ߵ��ĥ쥸����������ߵ��Ĥˤ��� */
	for (i = 0U; i < p_ctrl_inib->tnum_hrh; i++) {
		CANC_WR_IRQ_RXEN_REG(irq_rxen_reg_set_bit);
		irq_rxen_reg_set_bit <<= bit_offset;
		irq_rxen_reg_set_bit += bit_offset;
	}

	/* �������׵�쥸�����������̤ȯ���ˤ��� */
	CANC_RD_IRQ_REG();

	return(TRUE);
}

/* [CAN407] Can_Init�������᡼��ܥå�������� */
LOCAL_INLINE boolean
can_target_rbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hrh_idx)
{
	uint32	can_id_reg;
	uint32	filtermask_val;

	/* �оݤ����ꤹ�� */
	CANC_WR_MBOXWIN_REG(hrh_idx);

	/* �Ƽ�����å������ܥå����Υ������ץ��󥹥����ɥ쥸���������� */
	can_id_reg = ((uint32) GET_RBOX_CAN_ID(ctrl_id, hrh_idx)) << ACCEPTANCE_OFFSET;
	CANC_WR_RXMBOX_ACCEPTANCE_CODE_REG(can_id_reg);

	/* �оݤμ�����å������ܥå����Υե��륿�ޥ���̵ͭȽ�� */
	if (GET_RBOX_FILTER_MASK_IDX(ctrl_id, hrh_idx) != CAN_NO_MASK_IDX) {
		/* �оݤΥե��륿�ޥ��������� */
		filtermask_val = ((uint32) p_ctrl_inib->p_filtermask_table[hrh_idx]) << ACCEPTANCE_OFFSET;
		CANC_WR_RXMBOX_ACCEPTANCE_MASK_REG(filtermask_val);
	}
	else {
		/* �оݤΥե��륿�ޥ����ͤ�CAN_NO_MASK_IDX */
		CANC_WR_RXMBOX_ACCEPTANCE_MASK_REG(NO_MASK_VAL);
	}

	return(TRUE);
}

/* [CAN407] Can_Init�������᡼��ܥå�������� */
LOCAL_INLINE boolean
can_target_tbox_initialize(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib, Can_HwHandleType hth_idx)
{
	return(TRUE);
}

/* [CAN407] Can_Init��unit_phase2 */
LOCAL_INLINE boolean
can_target_init_unit_phase2(const Can_ConfigType *p_can_config)
{
	/* ��˥åȤ˴ؤ���������̵�� */
	return(TRUE);
}

/* Can_ChangeBaudrate */
LOCAL_INLINE boolean
can_target_change_baudrate(uint8 ctrl_id, const Can_ControllerBaudrateConfigType *p_baudrate_table)
{
	/* [CAN255] �ܡ��졼�Ȥ����� */
	if (p_baudrate_table->CanControllerBaudRate == 250U) {
		CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_250);
	}
	else {
		CANC_WR_CLKDIV_BUSTIM_REG(BAUDRATE_500);
	}

	return(TRUE);
}

/* Can_SetControllerMode��CAN_T_START */
LOCAL_INLINE boolean
can_target_start_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN261] �⡼�����ؽ��� */
	CANC_WR_MODE_REG(CANC_MODE_START);

	/* [CAN204][CAN425] ����߶ػߥͥ��ȥ������Ƚ�� */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/* [CAN196] ����ߵ��Ľ��� */
		can_target_enable_controller_interrupts(ctrl_id);
	}

	return(TRUE);
}

/* Can_SetControllerMode��CAN_T_STOP */
LOCAL_INLINE boolean
can_target_stop_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* [CAN204][CAN426] ����߶ػߥͥ��ȥ������Ƚ�� */
	if (can_interrupt_nested_cnt[ctrl_id] == 0U) {
		/* [CAN197] ����߶ػ߽��� */
		can_target_disable_controller_interrupts(ctrl_id);
	}

	/* [CAN263] �⡼�����ؽ��� */
	CANC_WR_MODE_REG(CANC_MODE_STOP);

	return(TRUE);
}

/* Can_SetControllerMode��CAN_T_SLEEP */
LOCAL_INLINE boolean
can_target_sleep_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* CAN_T_SLEEP��̤���ݡ��� */
	return(FALSE);
}

/* Can_SetControllerMode��CAN_T_WAKEUP */
LOCAL_INLINE boolean
can_target_wakeup_controller_and_change_interrupt(uint8 ctrl_id, const CAN_CTRL_INIB *p_ctrl_inib)
{
	/* CAN_T_WAKEUP��̤���ݡ��� */
	return(FALSE);
}

/* Can_DisableControllerInterrupts */
LOCAL_INLINE boolean
can_target_disable_controller_interrupts(uint8 ctrl_id)
{
	/* ����߶ػ߽��� */
	CANC_WR_IRQ_EN_REG(IRQ_SET_DISABLE);

	return(TRUE);
}

/* Can_EnableControllerInterrupts */
LOCAL_INLINE boolean
can_target_enable_controller_interrupts(uint8 ctrl_id)
{
	/* ����ߵ��Ľ��� */
	CANC_WR_IRQ_EN_REG(IRQ_SET_ENABLE);

	return(TRUE);
}

/* Can_CheckWakeup */
LOCAL_INLINE boolean
can_target_check_wakeup(uint8 ctrl_id)
{
	/* �����������åפ�̤���ݡ��� */
	return(FALSE);
}

/* Can_Write�������ǡ����ڤ������׵����� */
LOCAL_INLINE Can_ReturnType
can_target_transmit(uint8 ctrl_id, uint8 mb_idx, const Can_PduType *PduInfo)
{
	uint8	i, j;
	uint32	temp_data1 = 0;         /* �ǡ���(1��4byte)��Ǽ�� */
	uint32	temp_data2 = 0;         /* �ǡ���(5��8byte)��Ǽ�� */
	uint32	request_bit;

	if (PduInfo->length > BYTE_LENGTH) {
		/* 5��8byte�Υǡ����򥳥ԡ����� */
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

	/* ��å������Υǡ�����1byte�ʾ�ʤ顤1byte�ܰʹߤ�������� */
	if (PduInfo->length > 0) {
		/* 1��4byte�Υǡ����򥳥ԡ����� */
		for (j = i; j < PduInfo->length; j++) {
			if (j > i) {
				temp_data1 = temp_data1 << 8U;
			}
			temp_data1 = (temp_data1 | PduInfo->sdu[PduInfo->length - (1U + j)]);
		}
	}

	/* CAN-ID�γ�Ǽ */
	CANC_WR_TXMBOX_DATA0_REG((PduInfo->id << EXTEND_CAN_ID_LENGTH), mb_idx);

	/* �ǡ���Ĺ�γ�Ǽ */
	CANC_WR_TXMBOX_DATA1_REG(PduInfo->length, mb_idx);

	/* [CAN059][CAN427] �ǡ�����Ǽ */
	if (PduInfo->length > 0) {
		/* �ǡ���(1��4)�γ�Ǽ */
		CANC_WR_TXMBOX_DATA2_REG(temp_data1, mb_idx);
	}
	/* �ǡ�����5byte�ʾ�ʤ��Ǽ */
	if (PduInfo->length > BYTE_LENGTH) {
		/* �ǡ���(5��8)�γ�Ǽ */
		CANC_WR_TXMBOX_DATA3_REG(temp_data2, mb_idx);
	}

	/* �����׵� */
	request_bit = 1U << mb_idx;
	CANC_WR_TXREQ_REG(request_bit);

	return(CAN_OK);
}

/* Can_IsrRx�������᡼��ܥå������� */
LOCAL_INLINE boolean
can_target_check_and_get_rbox(uint8 ctrl_id, Can_HwHandleType *p_rbox_idx)
{
	boolean	ret;
	uint8	i;
	uint32	cmp_reg;

	/* HRH�����(DET�����ǥ��顼���ΤǤ���褦0xFF�ǽ��������) */
	*p_rbox_idx = 0xFFU;

	/* ������λ������� */
	cmp_reg = CANC_RD_RXCMP_REG();

	/* ������å�����̵ͭȽ�� */
	if (cmp_reg != 0x00000000U) {
		for (i = 0U; i < GET_HRH_NUM(ctrl_id); i++) {
			if ((cmp_reg & 1U) != 0U) {

				/* HRH���� */
				*p_rbox_idx = i;
				break;
			}
			else {
				cmp_reg >>= 1U;
			}
		}
		/* ������å�����ͭ�� */
		ret = TRUE;
	}
	else {
		/* ������å�����̵�� */
		ret = FALSE;
	}

	return(ret);
}

/* Can_IsrRx������ID�Υǡ������� */
LOCAL_INLINE boolean
can_target_get_rdata(uint8 ctrl_id, Can_HwHandleType rbox_id, Can_IdType *p_can_id, uint8 *p_can_dlc, uint8 can_sdu[])
{
	uint8	j;
	uint8	local_can_dlc;
	uint32	temp_data;
	uint32	clear_bit;

	/* ������λ���ꥢ�ӥå����� */
	clear_bit = 1U;
	clear_bit <<= (uint32) rbox_id;

	/* CAN-ID��Ф� */
	*p_can_id = ((CANC_RD_RXMBOX_DATA0_REG(rbox_id) &MASK_CAN_ID_MASK) >> EXTEND_CAN_ID_LENGTH);

	/* DLC�μ��Ф� */
	local_can_dlc = (uint8) (CANC_RD_RXMBOX_DATA1_REG(rbox_id) &MASK_4BIT);
	*p_can_dlc = local_can_dlc;

	/* [CAN012][CAN060][CAN299][CAN300] �ǡ������Ф�*/
	if (local_can_dlc > BYTE_LENGTH) {
		/* 5byte�ʾ�ξ�硤5byte�ܰʹߤΥ쥸�������ɤ߹��� */
		/* SDU(1��4byte)�μ��Ф� */
		temp_data = CANC_RD_RXMBOX_DATA2_REG(rbox_id);
		for (j = 0U; j < BYTE_LENGTH; j++) {
			can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
			temp_data >>= 8U;
		}
		/* SDU(5��8byte)�μ��Ф� */
		temp_data = CANC_RD_RXMBOX_DATA3_REG(rbox_id);
		for (j = BYTE_LENGTH; j < local_can_dlc; j++) {
			can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
			temp_data >>= 8U;
		}
	}
	else {
		/* 4byte�ʲ��ξ�硤5byte�ܰʹߤΥ쥸�������ɤ߹��ޤʤ� */
		/* SDU(1��4byte)�μ��Ф� */
		temp_data = CANC_RD_RXMBOX_DATA2_REG(rbox_id);
		for (j = 0U; j < local_can_dlc; j++) {
			can_sdu[j] = (uint8) (temp_data & MASK_8BIT);
			temp_data >>= 8U;
		}
	}

	/* [CAN420] ������λ�ӥåȥ��ꥢ */
	CANC_WR_RXCMP_REG(clear_bit);

	return(TRUE);
}

/* Can_IsrTx�������᡼��ܥå��������å����� */
LOCAL_INLINE boolean
can_target_check_and_get_tbox(uint8 ctrl_id, Can_HwHandleType *p_tbox_idx)
{
	boolean	ret;
	uint8	i;
	uint32	cmp_reg;
	uint32	clear_bit;

	/* HTH�����(DET�����ǥ��顼���ΤǤ���褦0xFF�ǽ��������) */
	*p_tbox_idx = 0xFFU;

	/* ������λ���ꥢ�ӥå����� */
	clear_bit = 1U;

	/* ������λ������� */
	cmp_reg = CANC_RD_TXCMP_REG();

	/* ������å�����̵ͭȽ�� */
	if (cmp_reg != 0x00000000U) {
		for (i = 0U; i < GET_HTH_NUM(ctrl_id); i++) {
			if ((cmp_reg & 1U) != 0U) {
				/* [CAN420] ������λ�ӥåȤΥ��ꥢ */
				CANC_WR_TXCMP_REG(clear_bit);

				/* HTH���� */
				*p_tbox_idx = i;
				break;
			}
			else {
				cmp_reg >>= 1U;
				clear_bit <<= 1U;
			}
		}
		/* ������å�����ͭ�� */
		ret = TRUE;
	}
	else {
		/* ������å�����̵�� */
		ret = FALSE;
	}

	return(ret);
}

LOCAL_INLINE Can_StateTransitionType
can_target_get_mode(uint8 ctrl_id)
{
	Can_StateTransitionType	ret;
	uint32					mode_reg;

	/* ư��⡼�ɼ��� */
	mode_reg = CANC_RD_MODE_REG();

	/* [CAN384][CAN409][CAN410] ư��⡼��Ƚ�� */
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

	/* �ӥ����������Ƚ��� */
	for (i = 0U; i < 100000U; i++) {
	}
}

/*
 *  ����¸���Ǥ�̤���ݡ��ȵ�ǽ
 *    <CAN048><CAN294><CAN361><CAN461> �����������åפ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN257><CAN265><CAN267><CAN411><CAN412> �ϡ��ɥ�������SLEEP�⡼�ɤ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN282><CAN283> ��������󥻥��̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN238><CAN242><CAN391><CAN244> nios2�Ǥ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN258><CAN290><CAN404><CAN405>����Ū��SLEEP�⡼�ɤ�̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN062><CAN256><CAN260><CAN422><CAN453> �ܡ��졼�Ȥ�����ϸ���Τ��ᡤ�б����ʤ�
 *    <CAN272><CAN273><CAN274> �Х����ս�����̤���ݡ��ȤΤ��ᡤ�б����ʤ�
 *    <CAN239> I/O�ݡ��Ȥν������OS¦���б����Ƥ��뤿�ᡤ��¸���Ǥ��б����ʤ�
 */

#endif /* TOPPERS_CAN_TARGET_H */
